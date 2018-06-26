/*
* Copyright (C) 2011 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

//
// WARNING -------------------------- WARNING
// This code meant to be used for testing purposes only. It is not production
// level quality.
// Use on your own risk !!
//
#include <link.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "egl_dispatch.h"
#include "egl_ftable.h"
#include <cutils/process_name.h>
#include <cutils/log.h>
#include "ThreadInfo.h"
#include <pthread.h>
#include "egl_test.cpp"
#include "gles_wrapper_context.h"
#include "gles1_wrapper_context.h"
#include "FbConfig.h"
#include "redfinger_egl_stream.h"
#include "renderControl_wrapper_entry.h"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
#include "FrameBuffer.h"

#define GLESv1_DRIVER "/system/lib/egl/libGLESv1_CM_RedFinger.so"
#define GLESv2_DRIVER "/system/lib/egl/libGLESv2_RedFinger.so"

#if PLATFORM_SDK_VERSION <= 16
#define queueBuffer_DEPRECATED queueBuffer
#define dequeueBuffer_DEPRECATED dequeueBuffer
#define cancelBuffer_DEPRECATED cancelBuffer
#endif // PLATFORM_SDK_VERSION <= 16

#define DEBUG_EGL 0

#if DEBUG_EGL
#define DPRINT(fmt,...) ALOGD("%s: " fmt, __FUNCTION__, ##__VA_ARGS__);
#else
#define DPRINT(...)
#endif

template<typename T>
static T setErrorFunc(GLint error, T returnValue) {
    getEGLThreadInfo()->eglError = error;
    return returnValue;
}

const char *  eglStrError(EGLint err)
{
    switch (err){
        case EGL_SUCCESS:           return "EGL_SUCCESS";
        case EGL_NOT_INITIALIZED:   return "EGL_NOT_INITIALIZED";
        case EGL_BAD_ACCESS:        return "EGL_BAD_ACCESS";
        case EGL_BAD_ALLOC:         return "EGL_BAD_ALLOC";
        case EGL_BAD_ATTRIBUTE:     return "EGL_BAD_ATTRIBUTE";
        case EGL_BAD_CONFIG:        return "EGL_BAD_CONFIG";
        case EGL_BAD_CONTEXT:       return "EGL_BAD_CONTEXT";
        case EGL_BAD_CURRENT_SURFACE: return "EGL_BAD_CURRENT_SURFACE";
        case EGL_BAD_DISPLAY:       return "EGL_BAD_DISPLAY";
        case EGL_BAD_MATCH:         return "EGL_BAD_MATCH";
        case EGL_BAD_NATIVE_PIXMAP: return "EGL_BAD_NATIVE_PIXMAP";
        case EGL_BAD_NATIVE_WINDOW: return "EGL_BAD_NATIVE_WINDOW";
        case EGL_BAD_PARAMETER:     return "EGL_BAD_PARAMETER";
        case EGL_BAD_SURFACE:       return "EGL_BAD_SURFACE";
        case EGL_CONTEXT_LOST:      return "EGL_CONTEXT_LOST";
        default: return "UNKNOWN";
    }
}

#define LOG_EGL_ERRORS 1

#ifdef LOG_EGL_ERRORS

#define setErrorReturn(error, retVal)     \
    {                                                \
        ALOGE("tid %d: %s(%d): error 0x%x (%s)", gettid(), __FUNCTION__, __LINE__, error, eglStrError(error));     \
        return setErrorFunc(error, retVal);            \
    }

#define RETURN_ERROR(ret,err)           \
    ALOGE("tid %d: %s(%d): error 0x%x (%s)", gettid(), __FUNCTION__, __LINE__, err, eglStrError(err));    \
    getEGLThreadInfo()->eglError = err;    \
    return ret;

#else //!LOG_EGL_ERRORS

#define setErrorReturn(error, retVal) return setErrorFunc(error, retVal);

#define RETURN_ERROR(ret,err)           \
    getEGLThreadInfo()->eglError = err; \
    return ret;

#endif //LOG_EGL_ERRORS

#define VALIDATE_CONFIG(cfg,ret) \
    if(((intptr_t)(cfg)<0)||((intptr_t)(cfg)>RedFingerEGLInfo::eglDisplayInstance()->getNumConfigs())) { \
        RETURN_ERROR(ret,EGL_BAD_CONFIG); \
    }

#define VALIDATE_DISPLAY(dpy,ret) \
    if ((dpy) != (EGLDisplay)RedFingerEGLInfo::eglDisplayInstance()) { \
        RETURN_ERROR(ret, EGL_BAD_DISPLAY);    \
    }

#define VALIDATE_DISPLAY_INIT(dpy,ret) \
    VALIDATE_DISPLAY(dpy, ret)    \
    if (!RedFingerEGLInfo::eglDisplayInstance()->initialized()) {        \
        RETURN_ERROR(ret, EGL_NOT_INITIALIZED);    \
    }

#define DEFINE_HOST_CONNECTION \
    RedFingerEGLInfo *hostCon = getEGLThreadInfo()->EGLInfo; \
    ExtendedRCEncoderContext *rcEnc = (hostCon ? hostCon->GetRenderControlEncoderContext() : NULL)

#define DEFINE_AND_VALIDATE_HOST_CONNECTION(ret) \
    RedFingerEGLInfo *hostCon = getEGLThreadInfo()->EGLInfo; \
    if (!hostCon) { \
        ALOGE("egl: Failed to get host connection\n"); \
        return ret; \
    } \
    ExtendedRCEncoderContext *rcEnc = hostCon->GetRenderControlEncoderContext(); \
    if (!rcEnc) { \
        ALOGE("egl: Failed to get renderControl encoder context\n"); \
        return ret; \
    }

#define VALIDATE_CONTEXT_RETURN(context,ret)  \
    if (!(context)) {                         \
        RETURN_ERROR(ret,EGL_BAD_CONTEXT);    \
    }

#define VALIDATE_SURFACE_RETURN(surface, ret)    \
    if ((surface) != EGL_NO_SURFACE) {    \
        egl_surface_t* s( static_cast<egl_surface_t*>(surface) );    \
        if (s->dpy != (EGLDisplay)RedFingerEGLInfo::eglDisplayInstance())    \
            setErrorReturn(EGL_BAD_DISPLAY, EGL_FALSE);    \
    }

EGLContext_t::EGLContext_t(EGLDisplay dpy, EGLContext context, EGLConfig config, EGLContext_t* shareCtx, EGLint maj, EGLint min) :
    dpy(dpy),
    context(context),
    config(config),
    read(EGL_NO_SURFACE),
    draw(EGL_NO_SURFACE),
    shareCtx(shareCtx),
    versionString(NULL),
    vendorString(NULL),
    rendererString(NULL),
    extensionString(NULL),
    deletePending(0),
    goldfishSyncFd(-1),
    decoder_context_data()
{
    flags = 0;
    version = 1;
    majorVersion = maj;
    minorVersion = min;
    deviceMajorVersion = maj;
    deviceMinorVersion = min;
    clientState = new GLClientState(majorVersion,minorVersion);
    if (shareCtx){
        sharedGroup = shareCtx->getSharedGroup();
    }
    else{
        sharedGroup = GLSharedGroupPtr(new GLSharedGroup());
    }
};
EGLContext_t::~EGLContext_t(){
    if (goldfishSyncFd > 0) {
        goldfish_sync_close(goldfishSyncFd);
        goldfishSyncFd = -1;
    }
    delete clientState;
    delete [] versionString;
    delete [] vendorString;
    delete [] rendererString;
    delete [] extensionString;
}
void EGLContext_t::AddVersionString(const char* str){
    if (str&&str[0]&&versionString==NULL){
        size_t slen = strlen(str);
        versionString = new char[slen + sizeof(char)];
        memset(versionString,0,slen + sizeof(char));
        memmove(versionString,str,slen);
    }
}
void EGLContext_t::AddVendorString(const char* str){
    if (str&&str[0]&&vendorString==NULL){
        size_t slen = strlen(str);
        vendorString = new char[slen + sizeof(char)];
        memset(vendorString,0,slen + sizeof(char));
        memmove(vendorString,str,slen);
    }
}
void EGLContext_t::AddExtensionString(const char* str){
    if (str&&str[0]&&extensionString==NULL){
        size_t slen = strlen(str);
        extensionString = new char[slen + sizeof(char)];
        memset(extensionString,0,slen + sizeof(char));
        memmove(extensionString,str,slen);
    }
}
// ----------------------------------------------------------------------------
//egl_surface_t

//we don't need to handle depth since it's handled when window created on the host

struct egl_surface_t {

    EGLDisplay          dpy;
    EGLConfig           config;


    egl_surface_t(EGLDisplay dpy, EGLConfig config, EGLint surfaceType);
    virtual     ~egl_surface_t();

    virtual     void        setSwapInterval(int interval) = 0;
    virtual     EGLBoolean  swapBuffers() = 0;

    EGLint      getSwapBehavior() const;
    uint32_t    getRcSurface()   { return rcSurface; }
    EGLint      getSurfaceType() { return surfaceType; }

    EGLint      getWidth(){ return width; }
    EGLint      getHeight(){ return height; }
    EGLint      getNativeWidth(){ return nativeWidth; }
    EGLint      getNativeHeight(){ return nativeHeight; }
    void        setTextureFormat(EGLint _texFormat) { texFormat = _texFormat; }
    EGLint      getTextureFormat() { return texFormat; }
    void        setTextureTarget(EGLint _texTarget) { texTarget = _texTarget; }
    EGLint      getTextureTarget() { return texTarget; }

private:
    //
    //Surface attributes
    //
    EGLint      width;
    EGLint      height;
    EGLint      texFormat;
    EGLint      texTarget;

    // Width of the actual window being presented (not the EGL texture)
    // Give it some default values.
    int nativeWidth;
    int nativeHeight;

protected:
    void        setWidth(EGLint w)  { width = w;  }
    void        setHeight(EGLint h) { height = h; }
    void        setNativeWidth(int w)  { nativeWidth = w;  }
    void        setNativeHeight(int h) { nativeHeight = h; }

    EGLint      surfaceType;
    uint32_t    rcSurface; //handle to surface created via remote control
};

egl_surface_t::egl_surface_t(EGLDisplay dpy, EGLConfig config, EGLint surfaceType)
    : dpy(dpy), config(config), surfaceType(surfaceType), rcSurface(0)
{
    width = 0;
    height = 0;
    // prevent div by 0 in EGL_(HORIZONTAL|VERTICAL)_RESOLUTION queries.
    nativeWidth = 1;
    nativeHeight = 1;
    texFormat = EGL_NO_TEXTURE;
    texTarget = EGL_NO_TEXTURE;
    assert(dpy == (EGLDisplay)RedFingerEGLInfo::eglDisplayInstance());
    RedFingerEGLInfo::eglDisplayInstance()->onCreateSurface((EGLSurface)this);
}

EGLint egl_surface_t::getSwapBehavior() const {
    return EGL_BUFFER_PRESERVED;
}

egl_surface_t::~egl_surface_t()
{
    assert(dpy == (EGLDisplay)RedFingerEGLInfo::eglDisplayInstance());
    RedFingerEGLInfo::eglDisplayInstance()->onDestroySurface((EGLSurface)this);
}

// ----------------------------------------------------------------------------
// egl_window_surface_t

struct egl_window_surface_t : public egl_surface_t {
    static egl_window_surface_t* create(
            EGLDisplay dpy, EGLConfig config, EGLint surfType,
            ANativeWindow* window);

    virtual ~egl_window_surface_t();

    virtual void       setSwapInterval(int interval);
    virtual EGLBoolean swapBuffers();

private:
    egl_window_surface_t(
            EGLDisplay dpy, EGLConfig config, EGLint surfType,
            ANativeWindow* window);
    EGLBoolean init();

    ANativeWindow*              nativeWindow;
    android_native_buffer_t*    buffer;
};

egl_window_surface_t::egl_window_surface_t (
        EGLDisplay dpy, EGLConfig config, EGLint surfType,
        ANativeWindow* window)
:   egl_surface_t(dpy, config, surfType),
    nativeWindow(window),
    buffer(NULL)
{
    // keep a reference on the window
    nativeWindow->common.incRef(&nativeWindow->common);
}


EGLBoolean egl_window_surface_t::init()
{
    if (nativeWindow->dequeueBuffer_DEPRECATED(nativeWindow, &buffer) != NO_ERROR) {
        setErrorReturn(EGL_BAD_ALLOC, EGL_FALSE);
    }
    setWidth(buffer->width);
    setHeight(buffer->height);

    int nativeWidth, nativeHeight;
          nativeWindow->query(nativeWindow, NATIVE_WINDOW_WIDTH, &nativeWidth);
          nativeWindow->query(nativeWindow, NATIVE_WINDOW_HEIGHT, &nativeHeight);

    setNativeWidth(nativeWidth);
    setNativeHeight(nativeHeight);

    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
    rcSurface = rcEnc->rcCreateWindowSurface(rcEnc, (uintptr_t)config,
            getWidth(), getHeight());
    if (!rcSurface) {
        ALOGE("rcCreateWindowSurface returned 0");
        return EGL_FALSE;
    }
    rcEnc->rcSetWindowColorBuffer(rcEnc, rcSurface,
            ((cb_handle_t*)(buffer->handle))->hostHandle);

    return EGL_TRUE;
}

egl_window_surface_t* egl_window_surface_t::create(
        EGLDisplay dpy, EGLConfig config, EGLint surfType,
        ANativeWindow* window)
{
    egl_window_surface_t* wnd = new egl_window_surface_t(
            dpy, config, surfType, window);
    if (wnd && !wnd->init()) {
        delete wnd;
        wnd = NULL;
    }
    return wnd;
}

egl_window_surface_t::~egl_window_surface_t() {
    DEFINE_HOST_CONNECTION;
    if (rcSurface && rcEnc) {
        rcEnc->rcDestroyWindowSurface(rcEnc, rcSurface);
    }
    if (buffer) {
        nativeWindow->cancelBuffer_DEPRECATED(nativeWindow, buffer);
    }
    nativeWindow->common.decRef(&nativeWindow->common);
}

void egl_window_surface_t::setSwapInterval(int interval)
{
    nativeWindow->setSwapInterval(nativeWindow, interval);
}

// createNativeSync() creates an OpenGL sync object on the host
// using rcCreateSyncKHR. If necessary, a native fence FD will
// also be created through the goldfish sync device.
// Returns a handle to the host-side FenceSync object.
static uint64_t createNativeSync(EGLenum type,
                                 const EGLint* attrib_list,
                                 int num_actual_attribs,
                                 bool destroy_when_signaled,
                                 int fd_in,
                                 int* fd_out) {
    DEFINE_HOST_CONNECTION;

    uint64_t sync_handle;
    uint64_t thread_handle;

    EGLint* actual_attribs =
        (EGLint*)(num_actual_attribs == 0 ? NULL : attrib_list);

    rcEnc->rcCreateSyncKHR(rcEnc, type,
                           actual_attribs,
                           num_actual_attribs * sizeof(EGLint),
                           destroy_when_signaled,
                           &sync_handle,
                           &thread_handle);

    if (type == EGL_SYNC_NATIVE_FENCE_ANDROID && fd_in < 0) {
        int queue_work_err =
            goldfish_sync_queue_work(
                    getEGLThreadInfo()->current_context->getGoldfishSyncFd(),
                    sync_handle,
                    thread_handle,
                    fd_out);

        DPRINT("got native fence fd=%d queue_work_err=%d",
               *fd_out, queue_work_err);
    }

    return sync_handle;
}

// createGoldfishOpenGLNativeSync() is for creating host-only sync objects
// that are needed by only this goldfish opengl driver,
// such as in swapBuffers().
// The guest will not see any of these, and these sync objects will be
// destroyed on the host when signaled.
// A native fence FD is possibly returned.
static void createGoldfishOpenGLNativeSync(int* fd_out) {
    createNativeSync(EGL_SYNC_NATIVE_FENCE_ANDROID,
                     NULL /* empty attrib list */,
                     0 /* 0 attrib count */,
                     true /* destroy when signaled. this is host-only
                             and there will only be one waiter */,
                     -1 /* we want a new fd */,
                     fd_out);
}

EGLBoolean egl_window_surface_t::swapBuffers()
{

    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);

    // Follow up flushWindowColorBuffer with a fence command.
    // When the fence command finishes,
    // we're sure that the buffer on the host
    // has been blitted.
    //
    // |presentFenceFd| guards the presentation of the
    // current frame with a goldfish sync fence fd.
    //
    // When |presentFenceFd| is signaled, the recipient
    // of the buffer that was sent through queueBuffer
    // can be sure that the buffer is current.
    //
    // If we don't take care of this synchronization,
    // an old frame can be processed by surfaceflinger,
    // resulting in out of order frames.

    int presentFenceFd = -1;

#if PLATFORM_SDK_VERSION <= 16
    rcEnc->rcFlushWindowColorBuffer(rcEnc, rcSurface);
    // equivalent to glFinish if no native sync
    eglWaitClient();
    nativeWindow->queueBuffer(nativeWindow, buffer);
#else
    if (rcEnc->hasNativeSync()) {
        rcEnc->rcFlushWindowColorBufferAsync(rcEnc, rcSurface);
        createGoldfishOpenGLNativeSync(&presentFenceFd);
    } else {
        rcEnc->rcFlushWindowColorBuffer(rcEnc, rcSurface);
        // equivalent to glFinish if no native sync
        eglWaitClient();
    }

    DPRINT("queueBuffer with fence %d", presentFenceFd);
    nativeWindow->queueBuffer(nativeWindow, buffer, presentFenceFd);
#endif

    DPRINT("calling dequeueBuffer...");

#if PLATFORM_SDK_VERSION <= 16
    if (nativeWindow->dequeueBuffer(nativeWindow, &buffer)) {
        buffer = NULL;
        setErrorReturn(EGL_BAD_SURFACE, EGL_FALSE);
    }
#else
    int acquireFenceFd = -1;
    if (nativeWindow->dequeueBuffer(nativeWindow, &buffer, &acquireFenceFd)) {
        buffer = NULL;
        setErrorReturn(EGL_BAD_SURFACE, EGL_FALSE);
    }

    DPRINT("dequeueBuffer with fence %d", acquireFenceFd);

    if (acquireFenceFd > 0) {
        close(acquireFenceFd);
    }
#endif

    rcEnc->rcSetWindowColorBuffer(rcEnc, rcSurface,
            ((cb_handle_t *)(buffer->handle))->hostHandle);

    setWidth(buffer->width);
    setHeight(buffer->height);

    return EGL_TRUE;
}

// ----------------------------------------------------------------------------
//egl_pbuffer_surface_t

struct egl_pbuffer_surface_t : public egl_surface_t {
    static egl_pbuffer_surface_t* create(EGLDisplay dpy, EGLConfig config,
            EGLint surfType, int32_t w, int32_t h, GLenum pixelFormat);

    virtual ~egl_pbuffer_surface_t();

    virtual void       setSwapInterval(int interval) { (void)interval; }
    virtual EGLBoolean swapBuffers() { return EGL_TRUE; }

    uint32_t getRcColorBuffer() { return rcColorBuffer; }

private:
    egl_pbuffer_surface_t(EGLDisplay dpy, EGLConfig config, EGLint surfType,
            int32_t w, int32_t h);
    EGLBoolean init(GLenum format);

    uint32_t rcColorBuffer;
};

egl_pbuffer_surface_t::egl_pbuffer_surface_t(EGLDisplay dpy, EGLConfig config,
        EGLint surfType, int32_t w, int32_t h)
:   egl_surface_t(dpy, config, surfType),
    rcColorBuffer(0)
{
    setWidth(w);
    setHeight(h);
}

egl_pbuffer_surface_t::~egl_pbuffer_surface_t()
{
    DEFINE_HOST_CONNECTION;
    if (rcEnc) {
        if (rcColorBuffer) rcEnc->rcCloseColorBuffer(rcEnc, rcColorBuffer);
        if (rcSurface)     rcEnc->rcDestroyWindowSurface(rcEnc, rcSurface);
    }
}

EGLBoolean egl_pbuffer_surface_t::init(GLenum pixelFormat)
{
    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);

    rcSurface = rcEnc->rcCreateWindowSurface(rcEnc, (uintptr_t)config,
            getWidth(), getHeight());
    if (!rcSurface) {
        ALOGE("rcCreateWindowSurface returned 0");
        return EGL_FALSE;
    }

    rcColorBuffer = rcEnc->rcCreateColorBuffer(rcEnc, getWidth(), getHeight(),
            pixelFormat);
    if (!rcColorBuffer) {
        ALOGE("rcCreateColorBuffer returned 0");
        return EGL_FALSE;
    }

    rcEnc->rcSetWindowColorBuffer(rcEnc, rcSurface, rcColorBuffer);

    return EGL_TRUE;
}

egl_pbuffer_surface_t* egl_pbuffer_surface_t::create(EGLDisplay dpy,
        EGLConfig config, EGLint surfType, int32_t w, int32_t h,
        GLenum pixelFormat)
{
    egl_pbuffer_surface_t* pb = new egl_pbuffer_surface_t(dpy, config, surfType,
            w, h);
    if (pb && !pb->init(pixelFormat)) {
        delete pb;
        pb = NULL;
    }
    return pb;
}

template <class T>
T* initApi(const char *driverLibName,const char *implLibName, T *(*accessor)())
{
    ALOGE("start load %s : %s!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", driverLibName, dlerror());
    void *driverLib = dlopen(driverLibName, RTLD_NOW | RTLD_LOCAL);
    if (driverLib == NULL) {
        ALOGE("failed to load %s : %s\n", driverLibName, dlerror());
        return NULL;
    }
    ALOGE("start load %s : %s OK!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n", driverLibName, dlerror());
    typedef T *(*createFcn_t)(void *,T *(*accessor)());
    createFcn_t createFcn;
    createFcn = (createFcn_t) dlsym(driverLib, "createFromLib");
    if (createFcn == NULL) {
        ALOGE("failed to load createFromLib constructor function\n");
        return NULL;
    }
    ALOGE("start load %s : %s!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", implLibName, dlerror());
    void *implLib = dlopen(implLibName, RTLD_NOW | RTLD_LOCAL);
    if (implLib == NULL) {
        ALOGE("couldn't open %s", implLibName);
        return NULL;
    }
    ALOGE("start load %s : %sOK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", implLibName, dlerror());
    T* dispatchTable = createFcn(implLib,accessor);
    if (dispatchTable == NULL) {
        return NULL;
    }

    // XXX - we do close the impl library since it doesn't have data, as far as we concern.
    // dlclose(implLib);

    // XXX - we do not dlclose the driver library, so its not initialized when
    // later loaded by android - is this required?
    ALOGD("loading %s into %s complete\n", implLibName, driverLibName);
    return dispatchTable;

}
static GLESv1ThreadInfo *eglGLESv1ThreadInfo()
{
    return getEGLThreadInfo()->GLESv1;
}
static GLESv2ThreadInfo *eglGLESv2ThreadInfo()
{
    return getEGLThreadInfo()->GLESv2;
}

const char *getProcName()
{
    static const char *procname = NULL;

    if (procname == NULL) {
        const char *str = get_process_name();
        if (strcmp(str, "unknown") != 0) {
            procname = str;
        } else {
            // we need to obtain our process name from the command line;
            FILE *fp = fopen("/proc/self/cmdline", "rt");
            if (fp == NULL) {
                ALOGE("couldn't open /proc/self/cmdline\n");
                return NULL;
            }

            char line[1000];
            if (fgets(line, sizeof(line), fp) == NULL) {
                ALOGE("couldn't read the self cmdline from \n");
                fclose(fp);
                return NULL;
            }
            fclose(fp);

            if (line[0] == '\0') {
                ALOGE("cmdline is empty\n");
                return NULL;
            }

            //obtain the basename;
            line[sizeof(line) - 1] = '\0';
            char *p = line;
            while (*p != '\0' &&
                   *p != '\t' &&
                   *p != ' ' &&
                   *p != '\n') {
                p++;
            }

            *p = '\0'; p--;
            while (p > line && *p != '/') p--;
            if (*p == '/') p++;
            procname = strdup(p);
        }
    }

    return procname;
}

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {
  ALOGD("[%s] %s\n", __FUNCTION__, getProcName());
  ALOGD("Dump path: %s,%p,%p\n", descriptor.path(),context,succeeded);
  return succeeded;
}

void SetupMinidumpDescriptor(){
    static bool is_initia = false;
    if (!is_initia){
        is_initia = true;
        static google_breakpad::MinidumpDescriptor descriptor("/tmp");
        static google_breakpad::ExceptionHandler eh(descriptor, NULL, DumpCallback, NULL, true, -1);
    }
}


EGLBoolean initDispatchTables()
{
    if (getEGLThreadInfo()->GLESv1&&getEGLThreadInfo()->GLESv2&&getEGLThreadInfo()->EGLDisp){
        return EGL_TRUE;
    }
    SetupMinidumpDescriptor();
    ALOGD("Loading egl dispatch for %s\n", getProcName());
    const char* hardware_gles = "/system/vendor/lib/egl/rk3288/libGLES_mali.so.bak";
    void *gles_android = dlopen(hardware_gles, RTLD_NOW | RTLD_LOCAL);
    if (!gles_android) {
        fprintf(stderr,"FATAL ERROR: Could not load libGLES_android lib\n");
        return EGL_FALSE;
    }
    // if(getEGLThreadInfo()->EGLDisp!=NULL){
    //     delete getEGLThreadInfo()->EGLDisp;
    //     getEGLThreadInfo()->EGLDisp = NULL;
    // }
    getEGLThreadInfo()->EGLDisp = create_egl_dispatch( gles_android );
    if (!getEGLThreadInfo()->EGLDisp) {
        fprintf(stderr,"FATAL ERROR: Could not create egl dispatch\n");
        return EGL_FALSE;
    }
    if (getEGLThreadInfo()->EGLDisp->eglSetBlobCacheFuncsANDROID==NULL){
        getEGLThreadInfo()->EGLDisp->eglSetBlobCacheFuncsANDROID = (eglSetBlobCacheFuncsANDROID_t)dlsym(gles_android,"eglSetBlobCacheFuncsANDROID");
    }
    ALOGD("Initializing native opengl for %s\n",getProcName());
    
    // load glesv1
    getEGLThreadInfo()->GLESv1 = initApi<GLESv1ThreadInfo>(GLESv1_DRIVER, hardware_gles,eglGLESv1ThreadInfo);
    void *driverLib = dlopen(GLESv1_DRIVER, RTLD_NOW | RTLD_LOCAL);
    getEGLThreadInfo()->EGLDisp->SetGLESv1EGLContext = (void(*)(void*))dlsym(driverLib,"SetGLESv1EGLContext");
    getEGLThreadInfo()->EGLDisp->GetGLESv1CurrentEGLContext = (void*(*)())dlsym(driverLib,"GetGLESv1CurrentEGLContext");
    getEGLThreadInfo()->EGLDisp->SetGLESv1DecodeContext = (void (*)(void*))dlsym(driverLib,"SetGLESv1DecodeContext");
    getEGLThreadInfo()->EGLDisp->SetGLESv1EncodeContext = (void (*)(void*))dlsym(driverLib,"SetGLESv1EncodeContext");

    // load glesv2
    getEGLThreadInfo()->GLESv2 = initApi<GLESv2ThreadInfo>(GLESv2_DRIVER, hardware_gles,eglGLESv2ThreadInfo);
    driverLib = dlopen(GLESv2_DRIVER, RTLD_NOW | RTLD_LOCAL);
    getEGLThreadInfo()->EGLDisp->SetGLClientContext = (void(*)(void*))dlsym(driverLib,"SetGLClientContext");
    getEGLThreadInfo()->EGLDisp->SetGL2ClientContext = (void(*)(void*))dlsym(driverLib,"SetGL2ClientContext");
    getEGLThreadInfo()->EGLDisp->SetGL2ClientStateMakeCurrent = (void(*)(void*,void*,int,int,int,int))dlsym(driverLib,"SetGL2ClientStateMakeCurrent");
    getEGLThreadInfo()->EGLDisp->SetServerContext = (void(*)(void*))dlsym(driverLib,"SetServerContext");
    getEGLThreadInfo()->EGLDisp->InitState = (void (*)(int,int,int,int,GLClientState*))dlsym(driverLib,"InitState");
    getEGLThreadInfo()->EGLInfo = new RedFingerEGLInfo(gles_android,new RedFingerEGLStream);
    if (RedFinger::Debug::IsOverrideEGLWithRedFingerImpl()){
        void *egl_android = dlopen(GLESv2_DRIVER, RTLD_NOW | RTLD_LOCAL);
        void *ptr = dlsym(egl_android,"eglBindAPI"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglBindAPI((eglBindAPI_t)ptr);
        }
        ptr = dlsym(egl_android,"eglQueryAPI");
        if (ptr){
            getEGLThreadInfo()->EGLDisp->set_eglQueryAPI((eglQueryAPI_t)ptr);
        }
        ptr = dlsym(egl_android,"eglCreateImageKHR"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglCreateImageKHR((eglCreateImageKHR_t)ptr);
        }
        ptr = dlsym(egl_android,"eglDestroyImageKHR"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglDestroyImageKHR((eglDestroyImageKHR_t)ptr);
        }
        ptr = dlsym(egl_android,"eglDestroySyncKHR"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglDestroySyncKHR((eglDestroySyncKHR_t)ptr);
        }
        ptr = dlsym(egl_android,"eglClientWaitSyncKHR"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglClientWaitSyncKHR((eglClientWaitSyncKHR_t)ptr);
        }
        ptr = dlsym(egl_android,"eglCreateWindowSurface"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglCreateWindowSurface((eglCreateWindowSurface_t)ptr);
        }
        ptr = dlsym(egl_android,"eglCreatePbufferSurface"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglCreatePbufferSurface((eglCreatePbufferSurface_t)ptr);
        }
        ptr = dlsym(egl_android,"eglCreatePixmapSurface"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglCreatePixmapSurface((eglCreatePixmapSurface_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetConfigAttrib"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetConfigAttrib((eglGetConfigAttrib_t)ptr);
        }
        ptr = dlsym(egl_android,"eglInitialize"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglInitialize((eglInitialize_t)ptr);
        }
        ptr = dlsym(egl_android,"eglCreateContext"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglCreateContext((eglCreateContext_t)ptr);
        }
        ptr = dlsym(egl_android,"eglCreateSyncKHR"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglCreateSyncKHR((eglCreateSyncKHR_t)ptr);
        }
        ptr = dlsym(egl_android,"eglQuerySurface"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglQuerySurface((eglQuerySurface_t)ptr);
        }
        ptr = dlsym(egl_android,"eglQueryContext"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglQueryContext((eglQueryContext_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetError"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetError((eglGetError_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetDisplay"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetDisplay((eglGetDisplay_t)ptr);
        }
        ptr = dlsym(egl_android,"eglTerminate"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglTerminate((eglTerminate_t)ptr);
        }
        ptr = dlsym(egl_android,"eglDestroySurface"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglDestroySurface((eglDestroySurface_t)ptr);
        }
        ptr = dlsym(egl_android,"eglWaitClient"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglWaitClient((eglWaitClient_t)ptr);
        }
        ptr = dlsym(egl_android,"eglReleaseThread"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglReleaseThread((eglReleaseThread_t)ptr);
        }
        ptr = dlsym(egl_android,"eglBindTexImage"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglBindTexImage((eglBindTexImage_t)ptr);
        }
        ptr = dlsym(egl_android,"eglSwapInterval"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglSwapInterval((eglSwapInterval_t)ptr);
        }
        ptr = dlsym(egl_android,"eglDestroyContext"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglDestroyContext((eglDestroyContext_t)ptr);
        }
        ptr = dlsym(egl_android,"eglMakeCurrent"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglMakeCurrent((eglMakeCurrent_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetCurrentContext"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetCurrentContext((eglGetCurrentContext_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetCurrentSurface"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetCurrentSurface((eglGetCurrentSurface_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetCurrentDisplay"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetCurrentDisplay((eglGetCurrentDisplay_t)ptr);
        }
        ptr = dlsym(egl_android,"eglSwapBuffers"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglSwapBuffers((eglSwapBuffers_t)ptr);
        }
        ptr = dlsym(egl_android,"eglWaitSyncKHR"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglWaitSyncKHR((eglWaitSyncKHR_t)ptr);
        }
        ptr = dlsym(egl_android,"eglDupNativeFenceFDANDROID"); 
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglDupNativeFenceFDANDROID((eglDupNativeFenceFDANDROID_t)ptr);
        }
        ptr = dlsym(egl_android,"eglGetConfigs");
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglGetConfigs((eglGetConfigs_t)ptr);
        }
        ptr = dlsym(egl_android,"eglChooseConfig");
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglChooseConfig((eglChooseConfig_t)ptr);
        }
        ptr = dlsym(egl_android,"eglQueryString");
        if(ptr){
            getEGLThreadInfo()->EGLDisp->set_eglQueryString((eglQueryString_t)ptr);
        }
    }
    return (getEGLThreadInfo()->GLESv1!=NULL&&getEGLThreadInfo()->GLESv2!=NULL&&getEGLThreadInfo()->EGLDisp!=NULL);
}
static pthread_mutex_t sInitDriverMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t dispatchTablesInitialized = PTHREAD_ONCE_INIT;

static EGLBoolean EGLInitGlobalTLS(){
    EGLBoolean res;
    pthread_mutex_lock(&sInitDriverMutex);
    res = initDispatchTables();
    pthread_mutex_unlock(&sInitDriverMutex);
    return res;
}
static EGLThreadInfo *GetEGLGlobalTLS(){
    return getEGLThreadInfo();
}
static void InitDispatchTables(){
    EGLInitGlobalTLS();
}
static struct egl_dispatch *getDispatch()
{
    pthread_once(&dispatchTablesInitialized, InitDispatchTables);
    return getEGLThreadInfo()->EGLDisp;
}
////////////////  Path through functions //////////
EGLint eglGetError()
{
    EGLInitGlobalTLS();
    return getDispatch()->eglGetError();
}

EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id)
{
    EGLInitGlobalTLS();
    if (RedFinger::Debug::IsDdgEGL()){
        //
        // we support only EGL_DEFAULT_DISPLAY.
        //
        if (display_id != EGL_DEFAULT_DISPLAY) {
            return EGL_NO_DISPLAY;
        }
        // return RedFingerEGLInfo::eglDisplayInstance();
    }
    return getDispatch()->eglGetDisplay(display_id);
}

EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    EGLInitGlobalTLS();
    if (RedFinger::Debug::IsDdgEGL()){
        if (!RedFingerEGLInfo::IsFrameBufferInit()){
            RedFingerEGLInfo::FrameBufferInit();
        }
        if (!RedFingerEGLInfo::eglDisplayInstance()->initialized()){
            RedFingerEGLInfo::eglDisplayInstance()->initialize();
        }
        if (major!=NULL)
            *major = RedFingerEGLInfo::eglDisplayInstance()->getVersionMajor();
        if (minor!=NULL)
            *minor = RedFingerEGLInfo::eglDisplayInstance()->getVersionMinor();
        return EGL_TRUE;
    }
    return getDispatch()->eglInitialize(dpy, major, minor);
}

EGLBoolean eglTerminate(EGLDisplay dpy)
{
    EGLInitGlobalTLS();
    if (RedFinger::Debug::IsDdgEGL()){
        if(RedFingerEGLInfo::eglDisplayInstance()->initialized()){
            RedFingerEGLInfo::eglDisplayInstance()->terminate();
        }
        return EGL_TRUE;
    }
    return getDispatch()->eglTerminate(dpy);
}

const char* eglQueryString(EGLDisplay dpy, EGLint name)
{
    EGLInitGlobalTLS();
    if (name==EGL_EXTENSIONS){
        static char* apis = "EGL_KHR_get_all_proc_addresses EGL_ANDROID_presentation_time EGL_KHR_image_base EGL_KHR_fence_sync EGL_ANDROID_image_native_buffer";
        return apis;
    }
    if (RedFinger::Debug::IsDdgEGL()){
        const char* retval =  RedFingerEGLInfo::eglDisplayInstance()->queryString(name);
        if (RedFinger::Debug::IsDdgEGL()){
            ALOGD("[%s] name %p:retval %s\n", __FUNCTION__, name,retval);
        }
        return retval;
    }
    return getDispatch()->eglQueryString(dpy, name);
}

EGLBoolean eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config){
    if (RedFinger::Debug::IsDdgEGL()){
        if(!num_config) {
            RETURN_ERROR(EGL_FALSE,EGL_BAD_PARAMETER);
        }
        GLint numConfigs = RedFingerEGLInfo::eglDisplayInstance()->getNumConfigs();
        if (!configs) {
            *num_config = numConfigs;
            return EGL_TRUE;
        }
        EGLint i;
        for (i = 0 ; i < numConfigs && i < config_size ; i++) {
            *configs++ = FrameBuffer::getFB()->getConfigs()->get(i)->getEglConfig();
        }
        *num_config = i;
        return EGL_TRUE;
    }
    return getDispatch()->eglGetConfigs(dpy, configs, config_size, num_config);
}

EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    if (RedFinger::Debug::IsDdgEGL()){
        // FIXME
        if (!num_config) {
            setErrorReturn(EGL_BAD_PARAMETER, EGL_FALSE);
        }

        int attribs_size = 0;
        if (attrib_list) {
            const EGLint * attrib_p = attrib_list;
            while (attrib_p[0] != EGL_NONE) {
                attribs_size += 2;
                attrib_p += 2;
            }
            attribs_size++; //for the terminating EGL_NONE
        }

        // API 19 passes EGL_SWAP_BEHAVIOR_PRESERVED_BIT to surface type,
        // while the host never supports it.
        // We remove the bit here.
        EGLint* local_attrib_list = NULL;
        if (PLATFORM_SDK_VERSION <= 19) {
            local_attrib_list = new EGLint[attribs_size];
            memcpy(local_attrib_list, attrib_list, attribs_size * sizeof(EGLint));
            EGLint* local_attrib_p = local_attrib_list;
            while (local_attrib_p[0] != EGL_NONE) {
                if (local_attrib_p[0] == EGL_SURFACE_TYPE) {
                    local_attrib_p[1] &= ~(EGLint)EGL_SWAP_BEHAVIOR_PRESERVED_BIT;
                }
                local_attrib_p += 2;
            }
        }

        uint32_t* tempConfigs[config_size];
        DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
        *num_config = rcEnc->rcChooseConfig(rcEnc,
                local_attrib_list ? local_attrib_list:(EGLint*)attrib_list,
                attribs_size * sizeof(EGLint), (uint32_t*)tempConfigs, config_size);

        if (local_attrib_list) delete [] local_attrib_list;
        if (*num_config <= 0) {
            EGLint err = -(*num_config);
            *num_config = 0;
            switch (err) {
                case EGL_BAD_ATTRIBUTE:
                    setErrorReturn(EGL_BAD_ATTRIBUTE, EGL_FALSE);
                default:
                    return EGL_FALSE;
            }
        }

        if (configs!=NULL) {
            EGLint i=0;
            for (i=0;i<(*num_config);i++) {
                 // *((uintptr_t*)configs+i) = *((uint32_t*)tempConfigs+i);
                *configs++ = FrameBuffer::getFB()->getConfigs()->get(i)->getEglConfig();
            }
        }

        return EGL_TRUE;
    }
    return getDispatch()->eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
}

EGLBoolean eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{   
    // if (RedFinger::Debug::IsDdgEGL()){
    //     if (RedFingerEGLInfo::eglDisplayInstance()->getConfigAttrib(config, attribute, value))
    //     {
    //         return EGL_TRUE;
    //     }
    //     else
    //     {
    //         RETURN_ERROR(EGL_FALSE, EGL_BAD_ATTRIBUTE);
    //     }
    // }
    return getDispatch()->eglGetConfigAttrib(dpy, config, attribute, value);
}

EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
    return getDispatch()->eglCreateWindowSurface(dpy, config, win, attrib_list);
}

EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
    return getDispatch()->eglCreatePbufferSurface(dpy, config, attrib_list);
}

// EGLSurface eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list)
// {
//     return NULL;
//     // CallTest
//     // return getDispatch()->eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
// }

EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    return getDispatch()->eglDestroySurface(dpy, surface);
}

EGLBoolean eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
    return getDispatch()->eglQuerySurface(dpy, surface, attribute, value);
}

EGLBoolean eglBindAPI(EGLenum api)
{
    EGLInitGlobalTLS();
    return getDispatch()->eglBindAPI(api);
}

EGLenum eglQueryAPI()
{
    EGLInitGlobalTLS();
    return getDispatch()->eglQueryAPI();
}

EGLBoolean eglWaitClient()
{
    return getDispatch()->eglWaitClient();
}

EGLBoolean eglReleaseThread()
{
    return getDispatch()->eglReleaseThread();
}

// EGLSurface eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
// {
//     return getDispatch()->eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
// }

EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
    return getDispatch()->eglSurfaceAttrib(dpy, surface, attribute, value);
}

EGLBoolean eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    return getDispatch()->eglBindTexImage(dpy, surface, buffer);
}

// EGLBoolean eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
// {
//     return EGL_FALSE;
//     // CallTest
//     // return getDispatch()->eglReleaseTexImage(dpy, surface, buffer);
// }

EGLBoolean eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
    return getDispatch()->eglSwapInterval(dpy, interval);
}

EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    if (RedFinger::Debug::IsCancelOverrideEGLContextType()){
        return getDispatch()->eglCreateContext( dpy,  config,  share_context, attrib_list);
    }
    EGLContext egl_context;
    
    EGLint version = 1; //default
    const EGLint *attrib_list_p1 = attrib_list;
    while (attrib_list_p1 && attrib_list_p1[0] != EGL_NONE) {
        if (attrib_list_p1[0] == EGL_CONTEXT_CLIENT_VERSION) {
            version = attrib_list_p1[1];
        } else { // Only the attribute EGL_CONTEXT_CLIENT_VERSION may be specified.
            return EGL_NO_CONTEXT;
        }
        attrib_list_p1+=2;
    }
    // Currently only support GLES1 and 2
    if (version != 1 && version != 2) {
        return EGL_NO_CONTEXT;
    }
    EGLint majorVersion = 1; //default
    EGLint minorVersion = 0;
    EGLint context_flags = 0;
    EGLint profile_mask = 0;
    EGLint reset_notification_strategy = 0;

    bool wantedMajorVersion = false;
    bool wantedMinorVersion = false;

    const EGLint *attrib_list_ptr = attrib_list;

    while (attrib_list && attrib_list[0] != EGL_NONE) {
           EGLint attrib_val = attrib_list[1];
        switch(attrib_list[0]) {
        case EGL_CONTEXT_MAJOR_VERSION_KHR:
            majorVersion = attrib_val;
            wantedMajorVersion = true;
            ALOGE("%s:%s:%p:%p:%s\n", __FILE__, __FUNCTION__, __LINE__,majorVersion,getProcName()); 
            break;
        case EGL_CONTEXT_MINOR_VERSION_KHR:
            minorVersion = attrib_val;
            wantedMinorVersion = true;
            ALOGE("%s:%s:%p:%p:%s\n", __FILE__, __FUNCTION__, __LINE__,minorVersion,getProcName()); 
            break;
        case EGL_CONTEXT_FLAGS_KHR:
            if ((attrib_val | EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR) ||
                (attrib_val | EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR)  ||
                (attrib_val | EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR)) {
                context_flags = attrib_val;
            } else {
                return EGL_NO_CONTEXT;
            }
            break;
        case EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR:
            if ((attrib_val | EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR) ||
                (attrib_val | EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR)) {
                profile_mask = attrib_val;
            } else {
                return EGL_NO_CONTEXT;
            }
            break;
        case EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR:
            switch (attrib_val) {
            case EGL_NO_RESET_NOTIFICATION_KHR:
            case EGL_LOSE_CONTEXT_ON_RESET_KHR:
                break;
            default:
                return EGL_NO_CONTEXT;
            }
            reset_notification_strategy = attrib_val;
            break;
        default:
            return EGL_NO_CONTEXT;
        }
        attrib_list+=2;
    }
    EGLContext rcShareCtx = share_context;
    EGLContext_t * shareCtx = NULL;
    if (share_context) {
        shareCtx = static_cast<EGLContext_t*>(share_context);
        if (shareCtx->dpy != dpy)
            return EGL_NO_CONTEXT;
        rcShareCtx = shareCtx->context;
    }
    egl_context = getDispatch()->eglCreateContext(dpy, config, rcShareCtx, attrib_list_ptr);
    if(egl_context==EGL_NO_CONTEXT){
        return EGL_NO_CONTEXT;
    }
    //refences:eglCreateOrLoadContext
    // FIXME
    // version from remote opengles
    switch (majorVersion) {
     case 1:
        // ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
        majorVersion = 1;
        minorVersion = 0;
        break;
     default:
        // if (!wantedMajorVersion) // FIXME
        majorVersion = 3;
        // if (!wantedMinorVersion) // FIXME
        minorVersion = 0;
        break;
    }
    EGLContext_t* context = new EGLContext_t(dpy,egl_context,config,shareCtx,majorVersion,minorVersion);
    context->AddVendorString(eglQueryString(dpy,EGL_VENDOR));
    context->AddVersionString(eglQueryString(dpy,EGL_VERSION));
    context->AddExtensionString(eglQueryString(dpy,EGL_EXTENSIONS));
    return context;
}

EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    if (RedFinger::Debug::IsCancelOverrideEGLContextType()){
        return getDispatch()->eglDestroyContext(dpy, ctx);
    }
    EGLContext_t* context = static_cast<EGLContext_t*>(ctx);
    if (!context) return EGL_TRUE;
    EGLContext_t* ctx_context = GetEGLGlobalTLS()->current_context; // (EGLContext_t*)getDispatch()->GetCurrentEGLContext();

    if (ctx_context == context) {
        ctx_context->deletePending = 1;
        return EGL_TRUE;
    }
    EGLBoolean R = getDispatch()->eglDestroyContext(dpy, context->context);
    delete context;
    return R;
}

EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    if (RedFinger::Debug::IsCancelOverrideEGLContextType()){
        return getDispatch()->eglMakeCurrent( dpy,  draw,  read,  ctx);
    }
    EGLContext_t * context = static_cast<EGLContext_t*>(ctx);
    EGLContext_t * ctx_context = GetEGLGlobalTLS()->current_context; // (EGLContext_t*)getDispatch()->GetCurrentEGLContext();
    if (ctx_context == context && (context == NULL || (context && context->draw == draw && context->read == read))) {
        return EGL_TRUE;
    }
    if (ctx_context && ctx_context->deletePending) {
        if (ctx_context != context) {
            EGLContext_t * contextToDelete = ctx_context;
            GetEGLGlobalTLS()->current_context = NULL; // getDispatch()->SetCurrentEGLContext(NULL);
            eglDestroyContext(dpy, contextToDelete);
        }
    }
    if (context && (context->flags & EGLContext_t::IS_CURRENT) && (context != ctx_context)) {
        // context is current to another thread
        ALOGE("%s: error: EGL_BAD_ACCESS: context %p current to another thread!\n", __FUNCTION__, context);
        return EGL_FALSE;
    }
    EGLBoolean retval = EGL_TRUE;
    if (context){
        ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
        retval = getDispatch()->eglMakeCurrent(dpy, draw, read, context->context);
    }
    else{
        ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
        retval = getDispatch()->eglMakeCurrent(dpy, draw, read, EGL_NO_CONTEXT);
    }
    if (retval==EGL_FALSE){
        return EGL_FALSE;
    }
    if (context){
        context->draw = draw;
        context->read = read;
        context->flags |= EGLContext_t::IS_CURRENT;
        if (context->majorVersion > 1) {
            getDispatch()->SetServerContext(context);

            getDispatch()->InitState(context->majorVersion,context->minorVersion,
                                    context->deviceMajorVersion,context->deviceMinorVersion,context->getClientState());
            getDispatch()->SetGL2ClientStateMakeCurrent(context,context->getClientState(),
                                                        context->majorVersion,
                                                        context->minorVersion,
                                                        context->deviceMajorVersion,
                                                        context->deviceMinorVersion);
        }
        else{
            ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
            getDispatch()->SetGLESv1DecodeContext(context);
            getDispatch()->SetGLESv1EncodeContext(context);
            ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
        }
    }
    else if (GetEGLGlobalTLS()->current_context){
        if (ctx_context->majorVersion > 1) {
            getDispatch()->SetServerContext(NULL);
            getDispatch()->SetGL2ClientContext(NULL);
        }
        else{
            ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
            getDispatch()->SetGLESv1EncodeContext(NULL);
            getDispatch()->SetGLESv1DecodeContext(NULL);
            ALOGE("%s:%s:%d:GLES_1_1:%s\n", __FILE__, __FUNCTION__, __LINE__,getProcName());
            // getDispatch()->SetGLClientContext(NULL);
        }
    }
    if(GetEGLGlobalTLS()->current_context){ // if (getDispatch()->GetCurrentEGLContext()){
        ctx_context->flags &= ~EGLContext_t::IS_CURRENT;
    }
    GetEGLGlobalTLS()->current_context = context; // getDispatch()->SetCurrentEGLContext(context);
    return retval;

}

EGLContext eglGetCurrentContext()
{
    if (RedFinger::Debug::IsCancelOverrideEGLContextType()){
        return getDispatch()->eglGetCurrentContext();
    }
    EGLContext_t* Ctx = GetEGLGlobalTLS()->current_context; // (EGLContext_t*)getDispatch()->GetCurrentEGLContext();
    return Ctx;
}

EGLSurface eglGetCurrentSurface(EGLint readdraw)
{
    return getDispatch()->eglGetCurrentSurface(readdraw);
}

EGLDisplay eglGetCurrentDisplay()
{
    return getDispatch()->eglGetCurrentDisplay();
}

EGLBoolean eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
    if (RedFinger::Debug::IsCancelOverrideEGLContextType()){
        return getDispatch()->eglQueryContext( dpy,  ctx,  attribute, value);
    }
    EGLContext_t * Ctx = static_cast<EGLContext_t*>(ctx);
    return getDispatch()->eglQueryContext(dpy, (Ctx ? Ctx->context : EGL_NO_CONTEXT), attribute, value);
}

// EGLBoolean eglWaitGL()
// {
//     return EGL_FALSE;
//     // CallTest
//     // return getDispatch()->eglWaitGL();
// }

// EGLBoolean eglWaitNative(EGLint engine)
// {
//     return EGL_FALSE;
//     // CallTest
//     // return getDispatch()->eglWaitNative(engine);
// }

EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    return getDispatch()->eglSwapBuffers(dpy, surface);
}

// EGLBoolean eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
// {
//     return EGL_FALSE;
//     // CallTest
//     // return getDispatch()->eglCopyBuffers(dpy, surface, target);
// }

/*EGLBoolean eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
    return getDispatch()->eglLockSurfaceKHR(display, surface, attrib_list);
}

EGLBoolean eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface)
{
    return getDispatch()->eglUnlockSurfaceKHR(display, surface);
}*/

EGLImageKHR eglCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
    if (RedFinger::Debug::IsCancelOverrideEGLContextType()){
        return getDispatch()->eglCreateImageKHR( dpy,  ctx,  target,  buffer, attrib_list);
    }
    EGLContext_t * Ctx = static_cast<EGLContext_t*>(ctx);
    return getDispatch()->eglCreateImageKHR(dpy, (Ctx ? Ctx->context : EGL_NO_CONTEXT), target, buffer, attrib_list);
}

EGLBoolean eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
    // return eglDestroyImageKHR_RedFingerTEST(dpy, image);
    return getDispatch()->eglDestroyImageKHR(dpy, image);
}

EGLSyncKHR eglCreateSyncKHR(EGLDisplay dpy, EGLenum type, const EGLint *attrib_list)
{
    return getDispatch()->eglCreateSyncKHR(dpy, type, attrib_list);
}

EGLBoolean eglDestroySyncKHR(EGLDisplay dpy, EGLSyncKHR sync)
{
    // return eglDestroySyncKHR_RedFingerTEST(dpy, sync);
    return getDispatch()->eglDestroySyncKHR(dpy, sync);
}

EGLint eglClientWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout)
{
    // return eglClientWaitSyncKHR_RedFingerTEST(dpy, sync, flags, timeout);
    return getDispatch()->eglClientWaitSyncKHR(dpy, sync, flags, timeout);
}

/*EGLBoolean eglSignalSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode)
{
    return getDispatch()->eglSignalSyncKHR(dpy, sync, mode);
}*/

// EGLBoolean eglGetSyncAttribKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *value)
// {
//     return EGL_FALSE;
//     // CallTest
//     // return getDispatch()->eglGetSyncAttribKHR(dpy, sync, attribute, value);
// }

/*EGLBoolean eglSetSwapRectangleANDROID(EGLDisplay dpy, EGLSurface draw, EGLint left, EGLint top, EGLint width, EGLint height)
{
    return getDispatch()->eglSetSwapRectangleANDROID(dpy, draw, left, top, width, height);
}*/

EGLint eglWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags)
{
    return getDispatch()->eglWaitSyncKHR(dpy,sync,flags);
}

/*EGLClientBuffer eglGetRenderBufferANDROID(EGLDisplay dpy, EGLSurface draw)
{
    return getDispatch()->eglGetRenderBufferANDROID(dpy,draw);
}*/

EGLint eglDupNativeFenceFDANDROID(EGLDisplay dpy, EGLSyncKHR sync)
{
    return getDispatch()->eglDupNativeFenceFDANDROID(dpy,sync);
}

/*EGLBoolean eglRenderBufferModifiedANDROID(EGLDisplay dpy, EGLSurface draw)
{
    return getDispatch()->eglRenderBufferModifiedANDROID(dpy,draw);
}*/

/*EGLuint64NV eglGetSystemTimeFrequencyNV ()
{
    EGLInitGlobalTLS();
    return getDispatch()->eglGetSystemTimeFrequencyNV();
}*/

/*EGLuint64NV eglGetSystemTimeNV()
{
    EGLInitGlobalTLS();
    return getDispatch()->eglGetSystemTimeNV();
}*/

/*EGLBoolean eglHibernateProcessIMG()
{
    return getDispatch()->eglHibernateProcessIMG();
}

EGLBoolean eglAwakenProcessIMG()
{
    return getDispatch()->eglAwakenProcessIMG();
}*/

/*void eglSetBlobCacheFuncsANDROID(EGLDisplay dpy, EGLSetBlobFuncANDROID_t set, EGLGetBlobFuncANDROID_t get)
{
    if (getDispatch()->eglSetBlobCacheFuncsANDROID!=NULL)
    {
        getDispatch()->eglSetBlobCacheFuncsANDROID(dpy,set,get);
    }
}*/
// EGLBoolean EGLAPIENTRY eglSwapBuffersWithDamageEXTMaliT76x(EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects){
//     ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
//     return EGL_TRUE;
// }
// EGLBoolean EGLAPIENTRY eglSwapBuffersWithDamageKHRMaliT76x(EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects){
//     ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
//     return EGL_TRUE;
// }
// EGLBoolean EGLAPIENTRY eglSetDamageRegionKHRMaliT76x(EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects){
//     ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
//     return EGL_TRUE;
// }
// EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXTMaliT76x(EGLenum platform, void *native_display, const EGLint *attrib_list){
//     ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
//     return NULL;
// }
// EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurfaceEXTMaliT76x(EGLDisplay dpy, EGLConfig config, void *native_window, const EGLint *attrib_list){
//     ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
//     return NULL;
// }
// EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXTMaliT76x(EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLint *attrib_list){
//     ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
//     return NULL;
// }
__eglMustCastToProperFunctionPointerType eglGetProcAddress(const char *procname)
{
    EGLInitGlobalTLS();
    // search in EGL function table
    for (int i=0; i<egl_num_funcs; i++) {
        /*if (!strcmp(procname,"eglGetRenderBufferANDROID")){
            return (__eglMustCastToProperFunctionPointerType)eglGetRenderBufferANDROID;
        }
        else if (!strcmp(procname,"eglRenderBufferModifiedANDROID")){
            return (__eglMustCastToProperFunctionPointerType)eglRenderBufferModifiedANDROID;
        }
        else if (!strcmp(procname,"eglHibernateProcessIMG")){
            return (__eglMustCastToProperFunctionPointerType)eglHibernateProcessIMG;
        }
        else if (!strcmp(procname,"eglAwakenProcessIMG")){
            return (__eglMustCastToProperFunctionPointerType)eglAwakenProcessIMG;
        }*/
        // if (!strcmp(procname,"eglSwapBuffersWithDamageEXT")){
        //     return (__eglMustCastToProperFunctionPointerType)eglSwapBuffersWithDamageEXTMaliT76x;
        // }
        // else if (!strcmp(procname,"eglSwapBuffersWithDamageKHR")){
        //     return (__eglMustCastToProperFunctionPointerType)eglSwapBuffersWithDamageKHRMaliT76x;
        // }
        // else if (!strcmp(procname,"eglSetDamageRegionKHR")){
        //     return (__eglMustCastToProperFunctionPointerType)eglSetDamageRegionKHRMaliT76x;
        // }
        // else if (!strcmp(procname,"eglGetPlatformDisplayEXT")){
        //     return (__eglMustCastToProperFunctionPointerType)eglGetPlatformDisplayEXTMaliT76x;
        // }
        // else if (!strcmp(procname,"eglCreatePlatformWindowSurfaceEXT")){
        //     return (__eglMustCastToProperFunctionPointerType)eglCreatePlatformWindowSurfaceEXTMaliT76x;
        // }
        // else if (!strcmp(procname,"eglCreatePlatformPixmapSurfaceEXT")){
        //     return (__eglMustCastToProperFunctionPointerType)eglCreatePlatformPixmapSurfaceEXTMaliT76x;
        // }
        if (!strcmp(egl_funcs_by_name[i].name, procname)) {
            return (__eglMustCastToProperFunctionPointerType)egl_funcs_by_name[i].proc;
        }
    }

    // we do not support eglGetProcAddress for GLESv1 & GLESv2. The loader
    // should be able to find this function through dynamic loading.
    return NULL;
}