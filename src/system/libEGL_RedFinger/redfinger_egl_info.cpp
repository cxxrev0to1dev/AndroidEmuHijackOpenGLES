#include "redfinger_egl_info.h"
#include <pthread.h>
#include <sys/mman.h>
#include "gralloc_cb.h"
#include "ThreadInfo.h"
#include "RenderControl.h"
#include "FrameBuffer.h"
#include "emugl/common/misc.h"
#include "eglDisplay.h"

template<typename T>
static T setErrorFunc(GLint error, T returnValue){
    getEGLThreadInfo()->eglError = error;
    return returnValue;
}

#define setErrorReturn(error, retVal) return setErrorFunc(error, retVal);

renderControl_client_context_t *RenderControlClientContextAccessorType(void){
    return getEGLThreadInfo()->EGLInfo->GetRenderControlClientContext();
}

class ApiInitializer {
public:
    ApiInitializer(void *dso) :
        m_dso(dso) {
    }
    static void *s_getProc(const char *name, void *userData) {
        ApiInitializer *self = (ApiInitializer *)userData;
        return self->getProc(name);
    }
private:
    void *m_dso;
    void *getProc(const char *name) {
        void *symbol = NULL;
        if (m_dso) {
            symbol = dlsym(m_dso, name);
        }
        //ALOGD("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxfunction:%s,%p\n",name,symbol);
        return symbol;
    }
};

static eglDisplay sEGLDisplay;
static pthread_mutex_t sFrameBufferInitLock = PTHREAD_MUTEX_INITIALIZER;
emugl::RenderLib* RedFingerEGLInfo::sRenderLib = NULL;
emugl::Renderer* RedFingerEGLInfo::sRenderer = NULL;

bool RedFingerEGLInfo::IsFrameBufferInit(){
    return (sRenderLib!=NULL&&sRenderer!=NULL);
}
void RedFingerEGLInfo::FrameBufferInit(){
    pthread_mutex_lock(&sFrameBufferInitLock);
    if (sRenderLib==NULL&&sRenderer==NULL)
    {
        ALOGD("initLibrary:%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
        sRenderLib = initLibrary();
        sRenderLib->setRenderer((SelectedRenderer)5);
        sRenderer = sRenderLib->initRenderer(1920, 1080, false);
    }
    pthread_mutex_unlock(&sFrameBufferInitLock);
}
emugl::RenderLib* RedFingerEGLInfo::GetRenderLibPtr(){
    return sRenderLib;
}
emugl::Renderer* RedFingerEGLInfo::GetRendererPtr(){
    return sRenderer;
}
eglDisplay* RedFingerEGLInfo::eglDisplayInstance(){
    return &sEGLDisplay;
}
RedFingerEGLInfo::RedFingerEGLInfo(void* impl_so,RedFingerEGLStream *stream):m_stream(stream),
    stream_(stream),
    ExtendedRCEncoderContext(stream){
    ApiInitializer *initializer = new ApiInitializer(impl_so);
    initRenderControlContext(GetRenderControlDecoderContext());
    stream->InitDecode((void*)GetRenderControlDecoderContext());
    GetRenderControlDecoderContext()->initDispatchByName(ApiInitializer::s_getProc, initializer);
    renderControl_client_context_t::setContextAccessor(RenderControlClientContextAccessorType);
    delete initializer;
}
RedFingerEGLInfo::~RedFingerEGLInfo(){
    if (stream_){
        delete stream_;
        stream_ = NULL;
    }
}
// static DisplayFramework sDisplayFramework;
// DisplayFramework* DisplayFramework::GetInstance(){
//     return &sDisplayFramework;
// }
// DisplayFramework::DisplayFramework():configs_(NULL),m_initialized(false),m_configs(NULL),numConfigs_(0),numConfigAttribs_(0){
//     pthread_mutex_init(&m_lock, NULL);
// }
// DisplayFramework::~DisplayFramework(){
//     if (configs_){
//         delete configs_;
//         configs_ = NULL;
//     }
//     if (m_configs){
//         // delete[] m_configs;
//         free(m_configs);
//         m_configs = NULL;
//     }
//     pthread_mutex_destroy(&m_lock);
// }
// void DisplayFramework::InitializeDisplay(EGLDisplay dpy){
//     assert(dpy!=EGL_NO_DISPLAY);
//     pthread_mutex_lock(&m_lock);
//     if (!m_initialized){
//         configs_ = new FbConfigList(dpy);
//         configs_->getPackInfo(&numConfigs_,&numConfigAttribs_);
//         uint32_t nInts = numConfigAttribs_ * (numConfigs_ + 1);
//         EGLint tmp_buf[nInts];
//         // m_configs = new EGLint[nInts-numConfigAttribs_];
//         // RedFinger:bug:20171118[16:10]:eglDisplay.cpp:getConfigNativePixelFormat:fix new
//         m_configs = reinterpret_cast<EGLint*>(malloc(sizeof(EGLint)*(nInts-numConfigAttribs_)));
//         if (RedFinger::Debug::IsDebugPrint()){
//             ALOGE("[%s] m_configs %p\n", __FUNCTION__,m_configs);
//             if ((mprotect(m_configs,(sizeof(EGLint)*(nInts-numConfigAttribs_)),PROT_READ|PROT_WRITE)==-1)){
//                 ALOGE("[%s] m_configs %p\n", __FUNCTION__,m_configs);
//             }
//             else{
//                 ALOGE("[%s] m_configs OK%p\n", __FUNCTION__,m_configs);
//             }
//         }
//         configs_->packConfigs(nInts*sizeof(EGLint), (GLuint*)tmp_buf);
//         for (int i=0; i<numConfigAttribs_; i++) {
//             m_attribs.add(tmp_buf[i], i);
//         }
//         memcpy(m_configs, tmp_buf + numConfigAttribs_, numConfigs_*numConfigAttribs_*sizeof(EGLint));
//         m_initialized = true;
//     }
//     pthread_mutex_unlock(&m_lock);
//     if (!m_initialized){
//         processConfigs();// NOTE: lock
//     }
//     return;
// }
// EGLint DisplayFramework::ChooseConfig(const EGLint* attribs,EGLint* configs,EGLint configsSize){
//     // pthread_mutex_lock(&m_lock);
//     EGLint r = configs_->chooseConfig(attribs, configs, configsSize);
//     // pthread_mutex_unlock(&m_lock);
//     return r;
// }
// EGLint DisplayFramework::ChooseConfig(EGLDisplay dpy,const EGLint* attribs,EGLint* configs,EGLint configsSize){
//     // pthread_mutex_lock(&m_lock);
//     // RedFinger:bug:20171118[19:29]:eglDisplay.cpp:ResetChooseConfig:add ResetChooseConfig
//     configs_->ResetChooseConfig(dpy);
//     EGLint r = configs_->chooseConfig(attribs, configs, configsSize);
//     // pthread_mutex_unlock(&m_lock);
//     return r;
// }
// EGLConfig DisplayFramework::IndexOfConfig(EGLConfig index){
//     // pthread_mutex_lock(&m_lock);
//     EGLint k = reinterpret_cast<EGLint>(index);
//     EGLConfig r = configs_->get(k)->getEglConfig();
//     // pthread_mutex_unlock(&m_lock);
//     return r;
// }
// EGLConfig DisplayFramework::IndexOfConfig(EGLint index){
//     EGLConfig r = configs_->get(index)->getEglConfig();
//     return r;
// }
// void DisplayFramework::GetPackInfo(EGLint* numConfigs, EGLint* numAttribs){
//     // pthread_mutex_lock(&m_lock);
//     configs_->getPackInfo(numConfigs,numAttribs);
//     // pthread_mutex_unlock(&m_lock);
// }
// EGLBoolean DisplayFramework::setConfigAttrib(EGLConfig config, EGLint attrib, EGLint value)
// {
//     //Though it seems that valueFor() is thread-safe, we don't take chanses
//     pthread_mutex_lock(&m_lock);
//     EGLBoolean ret = setAttribValue(config, m_attribs.valueFor(attrib), value);
//     pthread_mutex_unlock(&m_lock);
//     return ret;
// }


// EGLBoolean DisplayFramework::getConfigNativePixelFormat(EGLConfig config, PixelFormat * format)
// {
//     EGLint redSize, blueSize, greenSize, alphaSize;
//     // RedFinger:bug:20171118[16:10]:eglDisplay.cpp:getConfigNativePixelFormat:add lock
//     pthread_mutex_lock(&m_lock);
//     if ( !(getAttribValue(config, m_attribs.valueFor(EGL_RED_SIZE), &redSize) &&
//         getAttribValue(config, m_attribs.valueFor(EGL_BLUE_SIZE), &blueSize) &&
//         getAttribValue(config, m_attribs.valueFor(EGL_GREEN_SIZE), &greenSize) &&
//         getAttribValue(config, m_attribs.valueFor(EGL_ALPHA_SIZE), &alphaSize)) )
//     {
//         pthread_mutex_unlock(&m_lock);
//         ALOGE("Couldn't find value for one of the pixel format attributes");
//         return EGL_FALSE;
//     }
//     pthread_mutex_unlock(&m_lock);
//     //calculate the GL internal format
//     if ((redSize==8)&&(greenSize==8)&&(blueSize==8)&&(alphaSize==8)) *format = PIXEL_FORMAT_RGBA_8888; //XXX: BGR?
//     else if ((redSize==8)&&(greenSize==8)&&(blueSize==8)&&(alphaSize==0)) *format = PIXEL_FORMAT_RGBX_8888; //XXX or PIXEL_FORMAT_RGB_888
//     else if ((redSize==5)&&(greenSize==6)&&(blueSize==5)&&(alphaSize==0)) *format = PIXEL_FORMAT_RGB_565;
//     else if ((redSize==5)&&(greenSize==5)&&(blueSize==5)&&(alphaSize==1)) *format = PIXEL_FORMAT_RGBA_5551;
//     else if ((redSize==4)&&(greenSize==4)&&(blueSize==4)&&(alphaSize==4)) *format = PIXEL_FORMAT_RGBA_4444;
//     else {
//         return EGL_FALSE;
//     }
//     return EGL_TRUE;
// }
// EGLBoolean DisplayFramework::getConfigGLPixelFormat(EGLConfig config, GLenum * format)
// {
//     EGLint redSize, blueSize, greenSize, alphaSize;

//     if ( !(getAttribValue(config, m_attribs.valueFor(EGL_RED_SIZE), &redSize) &&
//         getAttribValue(config, m_attribs.valueFor(EGL_BLUE_SIZE), &blueSize) &&
//         getAttribValue(config, m_attribs.valueFor(EGL_GREEN_SIZE), &greenSize) &&
//         getAttribValue(config, m_attribs.valueFor(EGL_ALPHA_SIZE), &alphaSize)) )
//     {
//         ALOGE("Couldn't find value for one of the pixel format attributes");
//         return EGL_FALSE;
//     }

//     //calculate the GL internal format
//     if ((redSize == greenSize) && (redSize == blueSize) &&
//         ((redSize == 8) || (redSize == 16) || (redSize == 32)))
//     {
//         if (alphaSize == 0) *format = GL_RGB;
//         else *format = GL_RGBA;
//     }
//     else if ((redSize==5)&&(greenSize==6)&&(blueSize==5)&&(alphaSize==0)) *format = GL_RGB565_OES;
//     else if ((redSize==5)&&(greenSize==5)&&(blueSize==5)&&(alphaSize==1)) *format = GL_RGB5_A1_OES;
//     else if ((redSize==4)&&(greenSize==4)&&(blueSize==4)&&(alphaSize==4)) *format = GL_RGBA4_OES;
//     else return EGL_FALSE;

//     return EGL_TRUE;
// }
// EGLBoolean DisplayFramework::getConfigAttrib(EGLConfig config, EGLint attrib, EGLint * value)
// {
//     //Though it seems that valueFor() is thread-safe, we don't take chanses
//     pthread_mutex_lock(&m_lock);
//     EGLBoolean ret = getAttribValue(config, m_attribs.valueFor(attrib), value);
//     pthread_mutex_unlock(&m_lock);
//     return ret;
// }
// EGLBoolean DisplayFramework::getAttribValue(EGLConfig config, EGLint attribIdx, EGLint * value)
// {
//     if (attribIdx == ATTRIBUTE_NONE)
//     {
//         ALOGE("[%s] Bad attribute idx\n", __FUNCTION__);
//         return EGL_FALSE;
//     }
//     if (RedFinger::Debug::IsDebugPrint()){
//         if ((mprotect((m_configs + (intptr_t)config*numConfigAttribs_ + attribIdx),1,PROT_READ|PROT_WRITE)==-1)){
//             ALOGE("[%s] m_configs %p:config %p:numConfigAttribs_ %p:attribIdx %p\n", __FUNCTION__,m_configs,config,numConfigAttribs_,attribIdx);
//             return EGL_FALSE;
//         }
//     }
//     *value = *(m_configs + (intptr_t)config*numConfigAttribs_ + attribIdx);
//     return EGL_TRUE;
// }
// EGLBoolean DisplayFramework::setAttribValue(EGLConfig config, EGLint attribIdx, EGLint value)
// {
//     if (attribIdx == ATTRIBUTE_NONE)
//     {
//         ALOGE("[%s] Bad attribute idx\n", __FUNCTION__);
//         return EGL_FALSE;
//     }
//     *(m_configs + (intptr_t)config*numConfigAttribs_ + attribIdx) = value;
//     return EGL_TRUE;
// }


// void DisplayFramework::processConfigs()
// {
//     for (intptr_t i=0; i<numConfigs_; i++) {
//         EGLConfig config = (EGLConfig)i;
//         //Setup the EGL_NATIVE_VISUAL_ID attribute
//         PixelFormat format;
//         if (getConfigNativePixelFormat(config, &format)) {
//             setConfigAttrib(config, EGL_NATIVE_VISUAL_ID, format);
//         }
//     }
// }