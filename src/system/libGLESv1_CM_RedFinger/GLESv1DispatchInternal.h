#ifndef __GLES_V1_DISPATCHINTERNAL_H_
#define __GLES_V1_DISPATCHINTERNAL_H_

#include <stdint.h>
#include <dlfcn.h>
#include <map>
#include <vector>
#include <string>
#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include "GLClientState.h"
#include "gles1_enc.h"
#include "gles1_dec.h"
#include "gles1_wrapper_context.h"
#include "IOStream.h"
#include "GLDecoderContextData.h"
#include "GLESv1Encoder.h"
#include "GLESv1Decoder.h"
#include "DEBUG/redfinger_debug.h"

#ifndef EGL_APIENTRY
#define EGL_APIENTRY
typedef uint32_t EGLuint;
typedef uint64_t EGLuint64;
#endif

class RedFingerGLESv1Interception
{
public:
	class RedFingerGLESv1Describing
	{
	public:
		RedFingerGLESv1Describing(){
			gl_describing_.clear();
			gl_vendor_len_ = 0;
			gl_renderer_len_ = 0;
			gl_version_len_ = 0;
			gl_extensions_len_ = 0;
		}
		virtual ~RedFingerGLESv1Describing(){
			gl_describing_.clear();
			gl_vendor_len_ = 0;
			gl_renderer_len_ = 0;
			gl_version_len_ = 0;
			gl_extensions_len_ = 0;
		}
		void AddGLEescribing(EGLint name,const char* str){
			if (gl_describing_.find(name)==gl_describing_.end()){
				if (str) gl_describing_[name] = str;
				else gl_describing_[name] = "";
			}
		}
		void AddGLEescribing(EGLint name){
			AddGLEescribing(name,(const char*)&tmp_[0]);
		}
		EGLuint GetLength(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = gl_describing_.find(name);
			if (it==gl_describing_.end())
				return 0;
			return it->second.length();
		}
		const char* GetString(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = gl_describing_.find(name);
			if (it==gl_describing_.end())
				return NULL;
			return it->second.c_str();
		}
		bool IsFound(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = gl_describing_.find(name);
			if (it==gl_describing_.end())
				return false;
			return true;
		}
		EGLuint* GLVendorLenPtr(){
			return &gl_vendor_len_;
		}
		EGLuint* GLRendererLenPtr(){
			return &gl_renderer_len_;
		}
		EGLuint* GLVersionLenPtr(){
			return &gl_version_len_;
		}
		EGLuint* GLExtensionsLenPtr(){
			return &gl_extensions_len_;
		}
		EGLuint GLVendorLen(){
			return gl_vendor_len_;
		}
		EGLuint GLRendererLen(){
			return gl_renderer_len_;
		}
		EGLuint GLVersionLen(){
			return gl_version_len_;
		}
		EGLuint GLExtensionsLen(){
			return gl_extensions_len_;
		}
		char* ResetTmp(const EGLuint len){
			tmp_.resize(len + 1);
			return (char*)&tmp_[0];
		}
	private:
		EGLuint gl_vendor_len_;
		EGLuint gl_renderer_len_;
		EGLuint gl_version_len_;
		EGLuint gl_extensions_len_;
		std::map<EGLint,std::string> gl_describing_;
		std::vector<unsigned char> tmp_;	
	};
	class RedFingerCallGLESv1NativeFunc
	{
	public:
		static bool IsCallNativeFunction(){
			return false;
		}
		RedFingerCallGLESv1NativeFunc();
		virtual ~RedFingerCallGLESv1NativeFunc();
		void Init();
		void Reset();
		glVertexPointer_server_proc_t glVertexPointer;
	    glNormalPointer_server_proc_t glNormalPointer;
	    glColorPointer_server_proc_t glColorPointer;
	    glPointSizePointerOES_server_proc_t glPointSizePointerOES;
	    glTexCoordPointer_server_proc_t glTexCoordPointer;
	    glClientActiveTexture_server_proc_t glClientActiveTexture;
	    glMatrixIndexPointerOES_server_proc_t glMatrixIndexPointerOES;
	    glWeightPointerOES_server_proc_t glWeightPointerOES;
	    glGetString_server_proc_t glGetString;
	    glShaderSource_server_proc_t glShaderSource;
	    glVertexAttribPointer_server_proc_t glVertexAttribPointer;
	    glGetVertexAttribPointerv_server_proc_t glGetVertexAttribPointerv;
	    glEnableClientState_server_proc_t glEnableClientState;
	    glDisableClientState_server_proc_t glDisableClientState;
	    glEGLImageTargetTexture2DOES_server_proc_t glEGLImageTargetTexture2DOES;
	    glEGLImageTargetRenderbufferStorageOES_server_proc_t glEGLImageTargetRenderbufferStorageOES;
	};
	RedFingerGLESv1Interception();
	virtual ~RedFingerGLESv1Interception();
	size_t decode(void *buf, size_t len, IOStream *stream);
	void SetInitialize(bool initialized){
		initialized_ = initialized;
	}
	bool IsInitialize(){
		return initialized_;
	}
	RedFingerGLESv1Describing* GetGLESv1DescribingPtr(){
		return (dynamic_cast<RedFingerGLESv1Describing*>(&gl_describing_));
	}
	RedFingerCallGLESv1NativeFunc* GetGLESv1NativeFuncPtr(){
		return (dynamic_cast<RedFingerCallGLESv1NativeFunc*>(&call_gl_origin_));
	}
	typedef RedFingerGLESv1Interception *CONTEXT_ACCESSOR_TYPE(void);
	static void setContextAccessor(CONTEXT_ACCESSOR_TYPE *f);
public:
	static bool IsInterceptionTargetOpcode(void *buf, size_t len);
	static bool IsOffsetPointer(const void* ptr){
		return ((EGLuint)ptr<=0x400000);
	}
	static const GLubyte* s_glGetString_enc(void *self, GLenum name);
	static EGLint s_glGetString_client(void * self,EGLint name,void* buf,EGLuint buflen);
	EGLint s_glGetString_server(EGLint name,void* buf,EGLuint buflen);
	//GL extensions
	static void s_glEGLImageTargetTexture2DOES_ext(void * self, GLenum target, GLeglImageOES image);
	static void s_glEGLImageTargetRenderbufferStorageOES_ext(void *self, GLenum target, GLeglImageOES image);

private:
	RedFingerGLESv1Describing gl_describing_;
	RedFingerCallGLESv1NativeFunc call_gl_origin_;
	bool initialized_;
};

class GLESv1DispatchInternal : 
	public GLESv1Encoder,GLESv1Decoder,gles1_wrapper_context_t,RedFingerGLESv1Interception
{
public:
	GLESv1DispatchInternal(IOStream *stream,void* impl_so);
	virtual ~GLESv1DispatchInternal();
	GLESv1Encoder* GetGLESv1Encoder(){
		return (dynamic_cast<GLESv1Encoder*>(this));
	}
	GLESv1Decoder* GetGLESv1Decoder(){
		return (dynamic_cast<GLESv1Decoder*>(this));
	}
	RedFingerGLESv1Interception* GetGLESv1Interception(){
		return (dynamic_cast<RedFingerGLESv1Interception*>(this));
	}
	gles1_encoder_context_t* GetGLESv1EncodeContext(){
		return GetGLESv1Encoder()->GetContext();
	}
	gles1_decoder_context_t* GetGLESv1DecodeContext(){
		return GetGLESv1Decoder()->GetContext();
	}
	gles1_wrapper_context_t* GetGLESv1WrapperContext(){
		return (dynamic_cast<gles1_wrapper_context_t*>(this));
	}
};

#endif