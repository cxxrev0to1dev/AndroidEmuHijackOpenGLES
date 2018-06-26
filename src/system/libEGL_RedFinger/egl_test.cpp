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

#include <cutils/log.h>
#include "gralloc_cb.h"
#include "GLClientState.h"
#include "GLSharedGroup.h"
#include <system/window.h>
#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
#include "ErrorLog.h"

int eglError = 0;

const char* eglStrError_RedFingerTEST(EGLint err)
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

template<typename T>
static T setErrorFunc_RedFingerTEST(char* func_name,GLint error, T returnValue) {
    eglError = error;
    ALOGE("ssssssssssssssssssssssssssss:%s:%s:%d,%s,%s\n", __FILE__, __FUNCTION__, __LINE__,func_name,eglStrError_RedFingerTEST(error));
    return returnValue;
}


#define setErrorReturn_RedFingerTEST(func_name, error, retVal) return setErrorFunc_RedFingerTEST(func_name, error, retVal);

EGLSurface eglCreatePixmapSurface_RedFingerTEST(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list)
{
    //XXX: Pixmap not supported. The host cannot render to a pixmap resource
    //     located on host. In order to support Pixmaps we should either punt
    //     to s/w rendering -or- let the host render to a buffer that will be
    //     copied back to guest at some sync point. None of those methods not
    //     implemented and pixmaps are not used with OpenGL anyway ...
    (void)dpy;
    (void)config;
    (void)pixmap;
    (void)attrib_list;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return EGL_NO_SURFACE;
}

EGLBoolean eglBindAPI_RedFingerTEST(EGLenum api)
{
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    if (api != EGL_OPENGL_ES_API)
        setErrorReturn_RedFingerTEST("eglBindAPI_RedFingerTEST", EGL_BAD_PARAMETER, EGL_FALSE);
    return EGL_TRUE;
}

EGLenum eglQueryAPI_RedFingerTEST()
{
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return EGL_OPENGL_ES_API;
}

EGLSurface eglCreatePbufferFromClientBuffer_RedFingerTEST(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
    //TODO
    (void)dpy;
    (void)buftype;
    (void)buffer;
    (void)config;
    (void)attrib_list;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return 0;
}

EGLBoolean eglSurfaceAttrib_RedFingerTEST(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
    //TODO
    (void)dpy;
    (void)surface;
    (void)attribute;
    (void)value;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return 0;
}

EGLBoolean eglReleaseTexImage_RedFingerTEST(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    //TODO
    (void)dpy;
    (void)surface;
    (void)buffer;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return 0;
}

EGLBoolean eglWaitNative_RedFingerTEST(EGLint engine)
{
    (void)engine;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return EGL_TRUE;
}

EGLBoolean eglCopyBuffers_RedFingerTEST(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
    //TODO :later
    (void)dpy;
    (void)surface;
    (void)target;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return 0;
}

EGLBoolean eglLockSurfaceKHR_RedFingerTEST(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
    //TODO later
    (void)display;
    (void)surface;
    (void)attrib_list;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return 0;
}

EGLBoolean eglUnlockSurfaceKHR_RedFingerTEST(EGLDisplay display, EGLSurface surface)
{
    //TODO later
    (void)display;
    (void)surface;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    return 0;
}

EGLImageKHR eglCreateImageKHR_RedFingerTEST(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
    (void)attrib_list;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    if (ctx != EGL_NO_CONTEXT) {
        setErrorReturn_RedFingerTEST("eglCreateImageKHR_RedFingerTEST", EGL_BAD_CONTEXT, EGL_NO_IMAGE_KHR);
    }
    if (target != EGL_NATIVE_BUFFER_ANDROID) {
        setErrorReturn_RedFingerTEST("eglCreateImageKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_NO_IMAGE_KHR);
    }

    android_native_buffer_t* native_buffer = (android_native_buffer_t*)buffer;

    if (native_buffer->common.magic != ANDROID_NATIVE_BUFFER_MAGIC)
        setErrorReturn_RedFingerTEST("eglCreateImageKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_NO_IMAGE_KHR);

    if (native_buffer->common.version != sizeof(android_native_buffer_t))
        setErrorReturn_RedFingerTEST("eglCreateImageKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_NO_IMAGE_KHR);

    cb_handle_t *cb = (cb_handle_t *)(native_buffer->handle);

    switch (cb->format) {
        case HAL_PIXEL_FORMAT_RGBA_8888:
        case HAL_PIXEL_FORMAT_RGBX_8888:
        case HAL_PIXEL_FORMAT_RGB_888:
        case HAL_PIXEL_FORMAT_RGB_565:
        case HAL_PIXEL_FORMAT_BGRA_8888:
            break;
        default:
            setErrorReturn_RedFingerTEST("eglCreateImageKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_NO_IMAGE_KHR);
    }

    native_buffer->common.incRef(&native_buffer->common);
    return (EGLImageKHR)native_buffer;
}

EGLBoolean eglDestroyImageKHR_RedFingerTEST(EGLDisplay dpy, EGLImageKHR img)
{
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    android_native_buffer_t* native_buffer = (android_native_buffer_t*)img;

    if (native_buffer->common.magic != ANDROID_NATIVE_BUFFER_MAGIC)
        setErrorReturn_RedFingerTEST("eglDestroyImageKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_FALSE);

    if (native_buffer->common.version != sizeof(android_native_buffer_t))
        setErrorReturn_RedFingerTEST("eglDestroyImageKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_FALSE);

    native_buffer->common.decRef(&native_buffer->common);

    return EGL_TRUE;
}

#define FENCE_SYNC_HANDLE (EGLSyncKHR)0xFE4CE

EGLBoolean eglDestroySyncKHR_RedFingerTEST(EGLDisplay dpy, EGLSyncKHR sync)
{
    (void)dpy;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    if (sync != FENCE_SYNC_HANDLE) {
        setErrorReturn_RedFingerTEST("eglDestroySyncKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_FALSE);
    }

    return EGL_TRUE;
}

EGLint eglClientWaitSyncKHR_RedFingerTEST(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags,
        EGLTimeKHR timeout)
{
    (void)dpy;
    (void)flags;
    (void)timeout;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    if (sync != FENCE_SYNC_HANDLE) {
        setErrorReturn_RedFingerTEST("eglClientWaitSyncKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_FALSE);
    }

    return EGL_CONDITION_SATISFIED_KHR;
}

EGLBoolean eglGetSyncAttribKHR_RedFingerTEST(EGLDisplay dpy, EGLSyncKHR sync,
        EGLint attribute, EGLint *value)
{
    (void)dpy;
    ALOGW("ssssssssssssssssssssssssssssssssssssssss%s not implemented", __FUNCTION__);
    if (sync != FENCE_SYNC_HANDLE) {
        setErrorReturn_RedFingerTEST("eglGetSyncAttribKHR_RedFingerTEST", EGL_BAD_PARAMETER, EGL_FALSE);
    }

    switch (attribute) {
    case EGL_SYNC_TYPE_KHR:
        *value = EGL_SYNC_FENCE_KHR;
        return EGL_TRUE;
    case EGL_SYNC_STATUS_KHR:
        *value = EGL_SIGNALED_KHR;
        return EGL_TRUE;
    case EGL_SYNC_CONDITION_KHR:
        *value = EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR;
        return EGL_TRUE;
    default:
        setErrorReturn_RedFingerTEST("eglGetSyncAttribKHR_RedFingerTEST", EGL_BAD_ATTRIBUTE, EGL_FALSE);
    }
}
