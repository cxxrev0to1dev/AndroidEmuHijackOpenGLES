#ifndef REDFINGER_EGL_INFO_H_
#define REDFINGER_EGL_INFO_H_

#include <memory>
#include "renderControl_enc.h"
#include "renderControl_dec.h"
#include "redfinger_egl_stream.h"
#include "FbConfig.h"
#include "OpenglRender/Renderer.h"
#include "OpenglRender/render_api.h"
#include <utils/KeyedVector.h>
using namespace android;
#include <ui/PixelFormat.h>
#include "eglDisplay.h"

#define ATTRIBUTE_NONE (-1)
#define PLATFORM_SDK_VERSION 22 // FIXME

#if PLATFORM_SDK_VERSION >= 16
#include <system/window.h>
#else // PLATFORM_SDK_VERSION >= 16
#include <private/ui/android_natives_priv.h>
#endif // PLATFORM_SDK_VERSION >= 16

#if PLATFORM_SDK_VERSION <= 16
#define queueBuffer_DEPRECATED queueBuffer
#define dequeueBuffer_DEPRECATED dequeueBuffer
#define cancelBuffer_DEPRECATED cancelBuffer
#endif // PLATFORM_SDK_VERSION <= 16

enum class SyncImpl {
    SYNC_IMPL_NONE = 0,
    SYNC_IMPL_NATIVE_SYNC = 1
};

class ExtendedRCEncoderContext : public renderControl_encoder_context_t {
public:
    ExtendedRCEncoderContext(IOStream *stream)
        : renderControl_encoder_context_t(stream) { }
    void setSyncImpl(SyncImpl syncImpl) { m_syncImpl = syncImpl; }
    bool hasNativeSync() const { return m_syncImpl == SyncImpl::SYNC_IMPL_NATIVE_SYNC; }
    renderControl_client_context_t* RenderControlClientContextPtr(){
        return (dynamic_cast<renderControl_client_context_t*>(this));
    }
private:
    SyncImpl m_syncImpl;
};

class RedFingerEGLInfo:public ExtendedRCEncoderContext,renderControl_decoder_context_t
{
public:
    static bool IsFrameBufferInit();
    static void FrameBufferInit();
    static emugl::RenderLib* GetRenderLibPtr();
    static emugl::Renderer* GetRendererPtr();
    static eglDisplay* eglDisplayInstance();
	RedFingerEGLInfo(void* impl_so,RedFingerEGLStream *stream);
	virtual ~RedFingerEGLInfo();
	ExtendedRCEncoderContext* GetRenderControlEncoderContext(){
		return (dynamic_cast<ExtendedRCEncoderContext*>(this));
	}
	renderControl_decoder_context_t* GetRenderControlDecoderContext(){
		return (dynamic_cast<renderControl_decoder_context_t*>(this));
	}
    renderControl_client_context_t* GetRenderControlClientContext(){
        return (dynamic_cast<renderControl_client_context_t*>(GetRenderControlEncoderContext()->RenderControlClientContextPtr()));
    }
    renderControl_server_context_t* GetRenderControlServerContext(){
        return (dynamic_cast<renderControl_server_context_t*>(GetRenderControlDecoderContext()));
    }
    void flush() {
        if (m_stream) {
            m_stream->flush();
        }
    }
    void setGrallocOnly(bool gralloc_only) {
        m_grallocOnly = gralloc_only;
    }
    bool isGrallocOnly() const { return m_grallocOnly; }
private:
    IOStream *m_stream;
    RedFingerEGLStream *stream_;
    static emugl::RenderLib* sRenderLib;
    static emugl::Renderer* sRenderer;
    bool m_grallocOnly;
};
// class DisplayFramework
// {
// public:
//     static DisplayFramework* GetInstance();
//     DisplayFramework();
//     virtual ~DisplayFramework();
//     void InitializeDisplay(EGLDisplay dpy);
//     EGLint ChooseConfig(const EGLint* attribs,EGLint* configs,EGLint configsSize);
//     EGLint ChooseConfig(EGLDisplay dpy,const EGLint* attribs,EGLint* configs,EGLint configsSize);
//     EGLConfig IndexOfConfig(EGLConfig index);
//     EGLConfig IndexOfConfig(EGLint index);
//     void GetPackInfo(EGLint* numConfigs, EGLint* numAttribs);
//     size_t ConfigsSize() { return configs_->size();}
//     FbConfigList* configs() { return configs_;}
//     EGLBoolean  getConfigAttrib(EGLConfig config, EGLint attrib, EGLint * value);
//     EGLBoolean  setConfigAttrib(EGLConfig config, EGLint attrib, EGLint value);
//     EGLBoolean getConfigGLPixelFormat(EGLConfig config, GLenum * format);
//     EGLBoolean getConfigNativePixelFormat(EGLConfig config, PixelFormat * format);
// private:
//     EGLBoolean getAttribValue(EGLConfig config, EGLint attribIdxi, EGLint * value);
//     EGLBoolean setAttribValue(EGLConfig config, EGLint attribIdxi, EGLint value);
//     void     processConfigs();
//     FbConfigList* configs_;
//     EGLint  numConfigs_;
//     EGLint  numConfigAttribs_;
//     DefaultKeyedVector<EGLint, EGLint>    m_attribs;
//     EGLint *m_configs;
//     pthread_mutex_t m_lock;
//     bool m_initialized;
// };


#endif