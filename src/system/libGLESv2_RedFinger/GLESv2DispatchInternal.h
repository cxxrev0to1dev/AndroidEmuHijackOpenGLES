#ifndef __GLESV2_DISPATCHINTERNAL_H_
#define __GLESv2_DISPATCHINTERNAL_H_

#include <stdint.h>
#include <dlfcn.h>
#include <map>
#include <vector>
#include <string>
#include "GLClientState.h"
#include "gles_enc.h"
#include "gles_dec.h"
#include "IOStream.h"
#include "GLDecoderContextData.h"
#include "GLESv2Encoder.h"
#include "GLESv2Decoder.h"
#include "GLESv2NativeFuncCall.h"
#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
#include "DEBUG/redfinger_debug.h"
#include "gl_base_types.h"

#ifndef EGL_APIENTRY
#define EGL_APIENTRY
typedef uint32_t EGLuint;
typedef uint64_t EGLuint64;
#endif

/*
EGL Types 
EGLint is defined in eglplatform.h 
typedef unsigned int EGLBoolean;
typedef unsigned int EGLenum;
typedef void *EGLConfig;
typedef void *EGLContext;
typedef void *EGLDisplay;
typedef void *EGLSurface;
typedef void *EGLClientBuffer;
typedef void *EGLSyncKHR;
typedef void *EGLImageKHR;
typedef khronos_utime_nanoseconds_t EGLTimeKHR;
refences:/frameworks/native/opengl/libagl/egl.cpp
		https://cognitivewaves.wordpress.com/opengl-vbo-shader-vao/
*/

typedef EGLBoolean  (* eglInitialize_server_proc_t)(EGLDisplay display,EGLint* major,EGLint* minor);
typedef EGLSurface  (* eglCreateWindowSurface_server_proc_t)(EGLDisplay display,EGLConfig config,NativeWindowType native_window,EGLint const * attrib_list);
typedef EGLSurface  (* eglCreatePbufferSurface_server_proc_t)(EGLDisplay display,EGLConfig config,EGLint const * attrib_list);
typedef EGLSurface  (* eglCreatePixmapSurface_server_proc_t)(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list);
typedef EGLBoolean  (* eglBindAPI_server_proc_t)(EGLenum api);
typedef EGLenum     (* eglQueryAPI_server_proc_t)();
typedef EGLSurface  (* eglCreatePbufferFromClientBuffer_server_proc_t)(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
typedef EGLBoolean  (* eglSurfaceAttrib_server_proc_t)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
typedef EGLBoolean  (* eglReleaseTexImage_server_proc_t)(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean  (* eglWaitNative_server_proc_t)(EGLint engine);
typedef EGLBoolean  (* eglCopyBuffers_server_proc_t)(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
typedef EGLBoolean  (* eglLockSurfaceKHR_server_proc_t)(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list);
typedef EGLBoolean  (* eglUnlockSurfaceKHR_server_proc_t)(EGLDisplay display, EGLSurface surface);
typedef EGLImageKHR (* eglCreateImageKHR_server_proc_t)(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
typedef EGLBoolean  (* eglDestroyImageKHR_server_proc_t)(EGLDisplay dpy, EGLImageKHR img);
typedef EGLBoolean  (* eglDestroySyncKHR_server_proc_t)(EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLint      (* eglClientWaitSyncKHR_server_proc_t)(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
typedef EGLBoolean  (* eglGetSyncAttribKHR_server_proc_t)(EGLDisplay dpy, EGLSyncKHR sync,EGLint attribute, EGLint *value);
typedef EGLBoolean  (* eglGetConfigAttrib_server_proc_t)(EGLDisplay display,EGLConfig config,EGLint attribute,EGLint* value);
typedef EGLContext  (* eglCreateContext_server_proc_t)(EGLDisplay display,EGLConfig config,EGLContext share_context,const EGLint * attrib_list);
typedef EGLSyncKHR  (* eglCreateSyncKHR_server_proc_t)(EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
typedef EGLBoolean  (* eglQuerySurface_server_proc_t)(EGLDisplay display,EGLSurface surface,EGLint attribute,EGLint* value);
typedef EGLBoolean  (* eglQueryContext_server_proc_t)(EGLDisplay display,EGLContext context,EGLint attribute,EGLint* value);
typedef EGLint           (* eglGetError_server_proc_t) ();
typedef EGLBoolean       (* eglGetConfigs_server_proc_t) (EGLDisplay, EGLConfig*, EGLint, EGLint*);
typedef EGLBoolean       (* eglChooseConfig_server_proc_t) (EGLDisplay, const EGLint*, EGLConfig*, EGLint, EGLint*);
typedef EGLDisplay       (* eglGetDisplay_server_proc_t) (EGLNativeDisplayType);
typedef EGLBoolean       (* eglTerminate_server_proc_t) (EGLDisplay);
typedef char*            (* eglQueryString_server_proc_t) (EGLDisplay, EGLint);
typedef EGLBoolean       (* eglDestroySurface_server_proc_t) (EGLDisplay, EGLSurface);
typedef EGLBoolean       (* eglWaitClient_server_proc_t) ();
typedef EGLBoolean       (* eglReleaseThread_server_proc_t) ();
typedef EGLBoolean       (* eglBindTexImage_server_proc_t) (EGLDisplay, EGLSurface, EGLint);
typedef EGLBoolean       (* eglSwapInterval_server_proc_t) (EGLDisplay, EGLint);
typedef EGLBoolean       (* eglDestroyContext_server_proc_t) (EGLDisplay, EGLContext);
typedef EGLBoolean       (* eglMakeCurrent_server_proc_t) (EGLDisplay, EGLSurface, EGLSurface, EGLContext);
typedef EGLContext       (* eglGetCurrentContext_server_proc_t) ();
typedef EGLSurface       (* eglGetCurrentSurface_server_proc_t) (EGLint);
typedef EGLDisplay       (* eglGetCurrentDisplay_server_proc_t) ();
typedef EGLBoolean       (* eglSwapBuffers_server_proc_t) (EGLDisplay, EGLSurface);
typedef __eglMustCastToProperFunctionPointerType (* eglGetProcAddress_server_proc_t) (const char*);
typedef EGLBoolean       (* eglSignalSyncKHR_server_proc_t) (EGLDisplay, EGLSyncKHR, EGLenum);
typedef EGLint           (* eglWaitSyncKHR_server_proc_t) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
typedef EGLClientBuffer  (* eglGetRenderBufferANDROID_server_proc_t) (EGLDisplay, EGLSurface);
typedef EGLint           (* eglDupNativeFenceFDANDROID_server_proc_t) (EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLBoolean       (* eglRenderBufferModifiedANDROID_server_proc_t) (EGLDisplay dpy, EGLSurface draw);
typedef EGLuint64NV      (* eglGetSystemTimeFrequencyNV_server_proc_t) ();
typedef EGLuint64NV      (* eglGetSystemTimeNV_server_proc_t) ();
typedef EGLBoolean       (* eglHibernateProcessIMG_server_proc_t) ();
typedef EGLBoolean       (* eglAwakenProcessIMG_server_proc_t) ();

typedef EGLBoolean  (EGL_APIENTRY *eglInitialize_client_proc_t)(void * self,EGLDisplay display,EGLint* major,EGLint* minor);
typedef EGLSurface  (EGL_APIENTRY *eglCreateWindowSurface_client_proc_t)(void * self,EGLDisplay display,EGLConfig config,NativeWindowType native_window,EGLint const * attrib_list);
typedef EGLSurface  (EGL_APIENTRY *eglCreatePbufferSurface_client_proc_t)(void * self,EGLDisplay display,EGLConfig config,EGLint const * attrib_list);
typedef EGLSurface  (EGL_APIENTRY *eglCreatePixmapSurface_client_proc_t)(void * self,EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list);
typedef EGLBoolean  (EGL_APIENTRY *eglBindAPI_client_proc_t)(void * self,EGLenum api);
typedef EGLenum     (EGL_APIENTRY *eglQueryAPI_client_proc_t)(void * self);
typedef EGLSurface  (EGL_APIENTRY *eglCreatePbufferFromClientBuffer_client_proc_t)(void * self,EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
typedef EGLBoolean  (EGL_APIENTRY *eglSurfaceAttrib_client_proc_t)(void * self,EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
typedef EGLBoolean  (EGL_APIENTRY *eglReleaseTexImage_client_proc_t)(void * self,EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean  (EGL_APIENTRY *eglWaitNative_client_proc_t)(void * self,EGLint engine);
typedef EGLBoolean  (EGL_APIENTRY *eglCopyBuffers_client_proc_t)(void * self,EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
typedef EGLBoolean  (EGL_APIENTRY *eglLockSurfaceKHR_client_proc_t)(void * self,EGLDisplay display, EGLSurface surface, const EGLint *attrib_list);
typedef EGLBoolean  (EGL_APIENTRY *eglUnlockSurfaceKHR_client_proc_t)(void * self,EGLDisplay display, EGLSurface surface);
typedef EGLImageKHR (EGL_APIENTRY *eglCreateImageKHR_client_proc_t)(void * self,EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
typedef EGLBoolean  (EGL_APIENTRY *eglDestroyImageKHR_client_proc_t)(void * self,EGLDisplay dpy, EGLImageKHR img);
typedef EGLBoolean  (EGL_APIENTRY *eglDestroySyncKHR_client_proc_t)(void * self,EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLint      (EGL_APIENTRY *eglClientWaitSyncKHR_client_proc_t)(void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
typedef EGLBoolean  (EGL_APIENTRY *eglGetSyncAttribKHR_client_proc_t)(void * self,EGLDisplay dpy, EGLSyncKHR sync,EGLint attribute, EGLint *value);
typedef EGLBoolean  (EGL_APIENTRY *eglGetConfigAttrib_client_proc_t)(void * self,EGLDisplay display,EGLConfig config,EGLint attribute,EGLint* value);
typedef EGLContext  (EGL_APIENTRY *eglCreateContext_client_proc_t)(void * self,EGLDisplay display,EGLConfig config,EGLContext share_context,const EGLint * attrib_list);
typedef EGLSyncKHR  (EGL_APIENTRY *eglCreateSyncKHR_client_proc_t)(void * self,EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
typedef EGLBoolean  (EGL_APIENTRY *eglQuerySurface_client_proc_t)(void * self,EGLDisplay display,EGLSurface surface,EGLint attribute,EGLint* value);
typedef EGLBoolean  (EGL_APIENTRY *eglQueryContext_client_proc_t)(void * self,EGLDisplay display,EGLContext context,EGLint attribute,EGLint* value);
typedef EGLint           (EGL_APIENTRY *eglGetError_client_proc_t) (void * self);
typedef EGLBoolean       (EGL_APIENTRY *eglGetConfigs_client_proc_t) (void * self,EGLDisplay, EGLConfig*, EGLint, EGLint*);
typedef EGLBoolean       (EGL_APIENTRY *eglChooseConfig_client_proc_t) (void * self,EGLDisplay, const EGLint*, EGLConfig*, EGLint, EGLint*);
typedef EGLDisplay       (EGL_APIENTRY *eglGetDisplay_client_proc_t) (void * self,EGLNativeDisplayType);
typedef EGLBoolean       (EGL_APIENTRY *eglTerminate_client_proc_t) (void * self,EGLDisplay);
typedef char*            (EGL_APIENTRY *eglQueryString_client_proc_t) (void * self,EGLDisplay, EGLint);
typedef EGLBoolean       (EGL_APIENTRY *eglDestroySurface_client_proc_t) (void * self,EGLDisplay, EGLSurface);
typedef EGLBoolean       (EGL_APIENTRY *eglWaitClient_client_proc_t) (void * self);
typedef EGLBoolean       (EGL_APIENTRY *eglReleaseThread_client_proc_t) (void * self);
typedef EGLBoolean       (EGL_APIENTRY *eglBindTexImage_client_proc_t) (void * self,EGLDisplay, EGLSurface, EGLint);
typedef EGLBoolean       (EGL_APIENTRY *eglSwapInterval_client_proc_t) (void * self,EGLDisplay, EGLint);
typedef EGLBoolean       (EGL_APIENTRY *eglDestroyContext_client_proc_t) (void * self,EGLDisplay, EGLContext);
typedef EGLBoolean       (EGL_APIENTRY *eglMakeCurrent_client_proc_t) (void * self,EGLDisplay, EGLSurface, EGLSurface, EGLContext);
typedef EGLContext       (EGL_APIENTRY *eglGetCurrentContext_client_proc_t) (void * self);
typedef EGLSurface       (EGL_APIENTRY *eglGetCurrentSurface_client_proc_t) (void * self,EGLint);
typedef EGLDisplay       (EGL_APIENTRY *eglGetCurrentDisplay_client_proc_t) (void * self);
typedef EGLBoolean       (EGL_APIENTRY *eglSwapBuffers_client_proc_t) (void * self,EGLDisplay, EGLSurface);
typedef __eglMustCastToProperFunctionPointerType (EGL_APIENTRY *eglGetProcAddress_client_proc_t) (void * self,const char*);
typedef EGLBoolean       (EGL_APIENTRY *eglSignalSyncKHR_client_proc_t) (void * self,EGLDisplay, EGLSyncKHR, EGLenum);
typedef EGLint           (EGL_APIENTRY *eglWaitSyncKHR_client_proc_t) (void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
typedef EGLClientBuffer  (EGL_APIENTRY *eglGetRenderBufferANDROID_client_proc_t) (void * self,EGLDisplay, EGLSurface);
typedef EGLint           (EGL_APIENTRY *eglDupNativeFenceFDANDROID_client_proc_t) (void * self,EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLBoolean       (EGL_APIENTRY *eglRenderBufferModifiedANDROID_client_proc_t) (void * self,EGLDisplay dpy, EGLSurface draw);
typedef EGLuint64NV      (EGL_APIENTRY *eglGetSystemTimeFrequencyNV_client_proc_t) (void * self);
typedef EGLuint64NV      (EGL_APIENTRY *eglGetSystemTimeNV_client_proc_t) (void * self);
typedef EGLBoolean       (EGL_APIENTRY *eglHibernateProcessIMG_client_proc_t) (void * self);
typedef EGLBoolean       (EGL_APIENTRY *eglAwakenProcessIMG_client_proc_t) (void * self);


typedef EGLBoolean (EGL_APIENTRY *RedFingerStaticDescribing_client_proc_t) (void * self,char* buf,EGLuint *len,EGLint name);

typedef void (*glTexStorage2DEXT_typedef)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*glTextureStorage2DEXT_typedef)(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);

class RedFingerEGLDispatch
{
public:
	enum API_OPCODE
	{
		OP_eglBegin = 0x9876,
		OP_RedFingerStaticEescribing,
		OP_eglInitialize,
		OP_eglCreateWindowSurface,
		OP_eglCreatePbufferSurface,
		OP_eglCreatePixmapSurface,
		OP_eglBindAPI,
		OP_eglQueryAPI,
		OP_eglCreatePbufferFromClientBuffer,
		OP_eglSurfaceAttrib,
		OP_eglReleaseTexImage,
		OP_eglWaitNative,
		OP_eglCopyBuffers,
		OP_eglLockSurfaceKHR,
		OP_eglUnlockSurfaceKHR,
		OP_eglCreateImageKHR,
		OP_eglDestroyImageKHR,
		OP_eglDestroySyncKHR,
		OP_eglClientWaitSyncKHR,
		OP_eglGetSyncAttribKHR,
		OP_eglGetConfigAttrib,
		OP_eglCreateContext,
		OP_eglCreateSyncKHR,
		OP_eglQuerySurface,
		OP_eglQueryContext,
		OP_eglGetError,
		OP_eglGetConfigs,
		OP_eglChooseConfig,
		OP_eglGetDisplay,
		OP_eglTerminate,
		OP_eglQueryString,
		OP_eglDestroySurface,
		OP_eglWaitClient,
		OP_eglReleaseThread,
		OP_eglBindTexImage,
		OP_eglSwapInterval,
		OP_eglDestroyContext,
		OP_eglMakeCurrent,
		OP_eglGetCurrentContext,
		OP_eglGetCurrentSurface,
		OP_eglGetCurrentDisplay,
		OP_eglSwapBuffers,
		OP_eglGetProcAddress,
		OP_eglSignalSyncKHR,
		OP_eglWaitSyncKHR,
		OP_eglGetRenderBufferANDROID,
		OP_eglDupNativeFenceFDANDROID,
		OP_eglRenderBufferModifiedANDROID,
		OP_eglGetSystemTimeFrequencyNV,
		OP_eglGetSystemTimeNV,
		OP_eglHibernateProcessIMG,
		OP_eglAwakenProcessIMG,
		OP_eglEnd
	};
	class RedFingerEGLDescribing
	{
	public:
		RedFingerEGLDescribing();
		virtual ~RedFingerEGLDescribing();
		void AddEGLString(EGLint name,const char* str){
			if (egl_describing_.find(name)==egl_describing_.end()){
				if (str){
					static const char systemStaticEGLExtensions[] =
            "EGL_ANDROID_image_native_buffer "
            "EGL_KHR_fence_sync "
            "EGL_KHR_image_base "
            "EGL_KHR_gl_texture_2d_image ";
            egl_describing_[name] = std::string(str);
				} 
				else{
					egl_describing_[name] = "";
				}
			}
		}
		void AddEGLString(EGLint name){
			std::string ss;
			ss.resize(strlen((const char*)&tmp_[0]) + sizeof(char));
			AddEGLString(name,ss.c_str());
		}
		EGLuint GetLength(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = egl_describing_.find(name);
			if (it==egl_describing_.end())
				return 0;
			return it->second.length();
		}
		const char* GetEGLString(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = egl_describing_.find(name);
			if (it==egl_describing_.end())
				return NULL;
			return it->second.c_str();
		}
		EGLuint* EGLClientApisLenPtr(){
			return &egl_client_apis_len_;
		}
		EGLuint* EGLVendoLenPtr(){
			return &egl_vendor_len_;
		}
		EGLuint* EGLVersionLenPtr(){
			return &egl_version_len_;
		}
		EGLuint* EGLExtensionsLenPtr(){
			return &egl_extensions_len_;
		}
		EGLuint EGLClientApisLen(){
			return egl_client_apis_len_;
		}
		EGLuint EGLVendoLen(){
			return egl_vendor_len_;
		}
		EGLuint EGLVersionLen(){
			return egl_version_len_;
		}
		EGLuint EGLExtensionsLen(){
			return egl_extensions_len_;
		}
		char* ResetTmp(const EGLuint len){
			tmp_.resize(len + 1);
			return (char*)&tmp_[0];
		}
	private:
		EGLuint egl_client_apis_len_;
		EGLuint egl_vendor_len_;
		EGLuint egl_version_len_;
		EGLuint egl_extensions_len_;
		std::map<EGLint,std::string> egl_describing_;
		std::vector<unsigned char> tmp_;	
	};
	class RedFingerEGLDecoder
	{
	public:
		RedFingerEGLDecoder();
		virtual ~RedFingerEGLDecoder();
		void ClearFunctionAddr();
		bool IsEGLOPCODE(void *buf, size_t len);
		size_t decode(void *buf, size_t len, IOStream *stream);
		void Init();
		RedFingerEGLDescribing* GetEGLDescribing(){
			return (dynamic_cast<RedFingerEGLDescribing*>(&egl_describing_));
		}
		eglInitialize_server_proc_t eglInitialize_server;
		eglCreateWindowSurface_server_proc_t eglCreateWindowSurface_server;
		eglCreatePbufferSurface_server_proc_t eglCreatePbufferSurface_server;
		eglCreatePixmapSurface_server_proc_t eglCreatePixmapSurface_server;
		eglBindAPI_server_proc_t eglBindAPI_server;
		eglQueryAPI_server_proc_t eglQueryAPI_server;
		eglCreatePbufferFromClientBuffer_server_proc_t eglCreatePbufferFromClientBuffer_server;
		eglSurfaceAttrib_server_proc_t eglSurfaceAttrib_server;
		eglReleaseTexImage_server_proc_t eglReleaseTexImage_server;
		eglWaitNative_server_proc_t eglWaitNative_server;
		eglCopyBuffers_server_proc_t eglCopyBuffers_server;
		eglLockSurfaceKHR_server_proc_t eglLockSurfaceKHR_server;
		eglUnlockSurfaceKHR_server_proc_t eglUnlockSurfaceKHR_server;
		eglCreateImageKHR_server_proc_t eglCreateImageKHR_server;
		eglDestroyImageKHR_server_proc_t eglDestroyImageKHR_server;
		eglDestroySyncKHR_server_proc_t eglDestroySyncKHR_server;
		eglClientWaitSyncKHR_server_proc_t eglClientWaitSyncKHR_server;
		eglGetSyncAttribKHR_server_proc_t eglGetSyncAttribKHR_server;
		eglGetConfigAttrib_server_proc_t eglGetConfigAttrib_server;
		eglCreateContext_server_proc_t eglCreateContext_server;
		eglCreateSyncKHR_server_proc_t eglCreateSyncKHR_server;
		eglQuerySurface_server_proc_t eglQuerySurface_server;
		eglQueryContext_server_proc_t eglQueryContext_server;

		eglGetError_server_proc_t eglGetError_server;
		eglGetConfigs_server_proc_t eglGetConfigs_server;
		eglChooseConfig_server_proc_t eglChooseConfig_server;
		eglGetDisplay_server_proc_t eglGetDisplay_server;
		eglTerminate_server_proc_t eglTerminate_server;
		eglQueryString_server_proc_t eglQueryString_server;
		eglDestroySurface_server_proc_t eglDestroySurface_server;
		eglWaitClient_server_proc_t eglWaitClient_server;
		eglReleaseThread_server_proc_t eglReleaseThread_server;
		eglBindTexImage_server_proc_t eglBindTexImage_server;
		eglSwapInterval_server_proc_t eglSwapInterval_server;
		eglDestroyContext_server_proc_t eglDestroyContext_server;
		eglMakeCurrent_server_proc_t eglMakeCurrent_server;
		eglGetCurrentContext_server_proc_t eglGetCurrentContext_server;
		eglGetCurrentSurface_server_proc_t eglGetCurrentSurface_server;
		eglGetCurrentDisplay_server_proc_t eglGetCurrentDisplay_server;
		eglSwapBuffers_server_proc_t eglSwapBuffers_server;
		eglGetProcAddress_server_proc_t eglGetProcAddress_server;
		eglSignalSyncKHR_server_proc_t eglSignalSyncKHR_server;
		eglWaitSyncKHR_server_proc_t eglWaitSyncKHR_server;
		eglGetRenderBufferANDROID_server_proc_t eglGetRenderBufferANDROID_server;
		eglDupNativeFenceFDANDROID_server_proc_t eglDupNativeFenceFDANDROID_server;
		eglRenderBufferModifiedANDROID_server_proc_t eglRenderBufferModifiedANDROID_server;
		eglGetSystemTimeFrequencyNV_server_proc_t eglGetSystemTimeFrequencyNV_server;
		eglGetSystemTimeNV_server_proc_t eglGetSystemTimeNV_server;
		eglHibernateProcessIMG_server_proc_t eglHibernateProcessIMG_server;
		eglAwakenProcessIMG_server_proc_t eglAwakenProcessIMG_server;
	private:
		RedFingerEGLDescribing egl_describing_;
	};
	class RedFingerEGLEncoder
	{
	public:
		explicit RedFingerEGLEncoder(IOStream *stream);
		virtual ~RedFingerEGLEncoder();
		void ClearFunctionAddr();
		void Init();
		RedFingerEGLDescribing* GetEGLDescribing(){
			return (dynamic_cast<RedFingerEGLDescribing*>(&egl_describing_));
		}
		RedFingerStaticDescribing_client_proc_t RedFingerStaticDescribing_client;
		eglInitialize_client_proc_t eglInitialize_client;
		eglCreateWindowSurface_client_proc_t eglCreateWindowSurface_client;
		eglCreatePbufferSurface_client_proc_t eglCreatePbufferSurface_client;
		eglCreatePixmapSurface_client_proc_t eglCreatePixmapSurface_client;
		eglBindAPI_client_proc_t eglBindAPI_client;
		eglQueryAPI_client_proc_t eglQueryAPI_client;
		eglCreatePbufferFromClientBuffer_client_proc_t eglCreatePbufferFromClientBuffer_client;
		eglSurfaceAttrib_client_proc_t eglSurfaceAttrib_client;
		eglReleaseTexImage_client_proc_t eglReleaseTexImage_client;
		eglWaitNative_client_proc_t eglWaitNative_client;
		eglCopyBuffers_client_proc_t eglCopyBuffers_client;
		eglLockSurfaceKHR_client_proc_t eglLockSurfaceKHR_client;
		eglUnlockSurfaceKHR_client_proc_t eglUnlockSurfaceKHR_client;
		eglCreateImageKHR_client_proc_t eglCreateImageKHR_client;
		eglDestroyImageKHR_client_proc_t eglDestroyImageKHR_client;
		eglDestroySyncKHR_client_proc_t eglDestroySyncKHR_client;
		eglClientWaitSyncKHR_client_proc_t eglClientWaitSyncKHR_client;
		eglGetSyncAttribKHR_client_proc_t eglGetSyncAttribKHR_client;
		eglGetConfigAttrib_client_proc_t eglGetConfigAttrib_client;
		eglCreateContext_client_proc_t eglCreateContext_client;
		eglCreateSyncKHR_client_proc_t eglCreateSyncKHR_client;
		eglQuerySurface_client_proc_t eglQuerySurface_client;
		eglQueryContext_client_proc_t eglQueryContext_client;

		eglGetError_client_proc_t eglGetError_client;
		eglGetConfigs_client_proc_t eglGetConfigs_client;
		eglChooseConfig_client_proc_t eglChooseConfig_client;
		eglGetDisplay_client_proc_t eglGetDisplay_client;
		eglTerminate_client_proc_t eglTerminate_client;
		eglQueryString_client_proc_t eglQueryString_client;
		eglDestroySurface_client_proc_t eglDestroySurface_client;
		eglWaitClient_client_proc_t eglWaitClient_client;
		eglReleaseThread_client_proc_t eglReleaseThread_client;
		eglBindTexImage_client_proc_t eglBindTexImage_client;
		eglSwapInterval_client_proc_t eglSwapInterval_client;
		eglDestroyContext_client_proc_t eglDestroyContext_client;
		eglMakeCurrent_client_proc_t eglMakeCurrent_client;
		eglGetCurrentContext_client_proc_t eglGetCurrentContext_client;
		eglGetCurrentSurface_client_proc_t eglGetCurrentSurface_client;
		eglGetCurrentDisplay_client_proc_t eglGetCurrentDisplay_client;
		eglSwapBuffers_client_proc_t eglSwapBuffers_client;
		eglGetProcAddress_client_proc_t eglGetProcAddress_client;
		eglSignalSyncKHR_client_proc_t eglSignalSyncKHR_client;
		eglWaitSyncKHR_client_proc_t eglWaitSyncKHR_client;
		eglGetRenderBufferANDROID_client_proc_t eglGetRenderBufferANDROID_client;
		eglDupNativeFenceFDANDROID_client_proc_t eglDupNativeFenceFDANDROID_client;
		eglRenderBufferModifiedANDROID_client_proc_t eglRenderBufferModifiedANDROID_client;
		eglGetSystemTimeFrequencyNV_client_proc_t eglGetSystemTimeFrequencyNV_client;
		eglGetSystemTimeNV_client_proc_t eglGetSystemTimeNV_client;
		eglHibernateProcessIMG_client_proc_t eglHibernateProcessIMG_client;
		eglAwakenProcessIMG_client_proc_t eglAwakenProcessIMG_client;
	private:
		static EGLBoolean  EGL_APIENTRY s_RedFingerStaticDescribing_client(void * self,char* buf,EGLuint *len,EGLint name);
		static EGLBoolean  EGL_APIENTRY s_eglInitialize_client(void * self,EGLDisplay display,EGLint* major,EGLint* minor);
		static EGLSurface  EGL_APIENTRY s_eglCreateWindowSurface_client(void * self,EGLDisplay display,EGLConfig config,NativeWindowType native_window,EGLint const * attrib_list);
		static EGLSurface  EGL_APIENTRY s_eglCreatePbufferSurface_client(void * self,EGLDisplay display,EGLConfig config,EGLint const * attrib_list);
		static EGLSurface  EGL_APIENTRY s_eglCreatePixmapSurface_client(void * self,EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list);
		static EGLBoolean  EGL_APIENTRY s_eglBindAPI_client(void * self,EGLenum api);
		static EGLenum     EGL_APIENTRY s_eglQueryAPI_client(void * self);
		static EGLSurface  EGL_APIENTRY s_eglCreatePbufferFromClientBuffer_client(void * self,EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
		static EGLBoolean  EGL_APIENTRY s_eglSurfaceAttrib_client(void * self,EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
		static EGLBoolean  EGL_APIENTRY s_eglReleaseTexImage_client(void * self,EGLDisplay dpy, EGLSurface surface, EGLint buffer);
		static EGLBoolean  EGL_APIENTRY s_eglWaitNative_client(void * self,EGLint engine);
		static EGLBoolean  EGL_APIENTRY s_eglCopyBuffers_client(void * self,EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
		static EGLBoolean  EGL_APIENTRY s_eglLockSurfaceKHR_client(void * self,EGLDisplay display, EGLSurface surface, const EGLint *attrib_list);
		static EGLBoolean  EGL_APIENTRY s_eglUnlockSurfaceKHR_client(void * self,EGLDisplay display, EGLSurface surface);
		static EGLImageKHR EGL_APIENTRY s_eglCreateImageKHR_client(void * self,EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
		static EGLBoolean  EGL_APIENTRY s_eglDestroyImageKHR_client(void * self,EGLDisplay dpy, EGLImageKHR img);
		static EGLBoolean  EGL_APIENTRY s_eglDestroySyncKHR_client(void * self,EGLDisplay dpy, EGLSyncKHR sync);
		static EGLint      EGL_APIENTRY s_eglClientWaitSyncKHR_client(void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
		static EGLBoolean  EGL_APIENTRY s_eglGetSyncAttribKHR_client(void * self,EGLDisplay dpy, EGLSyncKHR sync,EGLint attribute, EGLint *value);
		static EGLBoolean  EGL_APIENTRY s_eglGetConfigAttrib_client(void * self,EGLDisplay display,EGLConfig config,EGLint attribute,EGLint* value);
		static EGLContext  EGL_APIENTRY s_eglCreateContext_client(void * self,EGLDisplay display,EGLConfig config,EGLContext share_context,const EGLint * attrib_list);
		static EGLSyncKHR  EGL_APIENTRY s_eglCreateSyncKHR_client(void * self,EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
		static EGLBoolean  EGL_APIENTRY s_eglQuerySurface_client(void * self,EGLDisplay display,EGLSurface surface,EGLint attribute,EGLint* value);
		static EGLBoolean  EGL_APIENTRY s_eglQueryContext_client(void * self,EGLDisplay display,EGLContext context,EGLint attribute,EGLint* value);
		static EGLint           EGL_APIENTRY s_eglGetError_client (void * self);
		static EGLBoolean       EGL_APIENTRY s_eglGetConfigs_client (void * self,EGLDisplay display,EGLConfig* configs,EGLint config_size,EGLint* num_config);
		static EGLBoolean       EGL_APIENTRY s_eglChooseConfig_client (void * self,EGLDisplay display,const EGLint* attrib_list,EGLConfig * configs,EGLint config_size,EGLint * num_config);
		static EGLDisplay       EGL_APIENTRY s_eglGetDisplay_client (void * self,EGLNativeDisplayType display_id);
		static EGLBoolean       EGL_APIENTRY s_eglTerminate_client (void * self,EGLDisplay dpy);
		static char*            EGL_APIENTRY s_eglQueryString_client (void * self,EGLDisplay dpy, EGLint name);
		static EGLBoolean       EGL_APIENTRY s_eglDestroySurface_client (void * self,EGLDisplay dpy, EGLSurface surface);
		static EGLBoolean       EGL_APIENTRY s_eglWaitClient_client (void * self);
		static EGLBoolean       EGL_APIENTRY s_eglReleaseThread_client (void * self);
		static EGLBoolean       EGL_APIENTRY s_eglBindTexImage_client (void * self,EGLDisplay dpy, EGLSurface surface, EGLint buffer);
		static EGLBoolean       EGL_APIENTRY s_eglSwapInterval_client (void * self,EGLDisplay dpy, EGLint interval);
		static EGLBoolean       EGL_APIENTRY s_eglDestroyContext_client (void * self,EGLDisplay dpy, EGLContext ctx);
		static EGLBoolean       EGL_APIENTRY s_eglMakeCurrent_client (void * self,EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
		static EGLContext       EGL_APIENTRY s_eglGetCurrentContext_client (void * self);
		static EGLSurface       EGL_APIENTRY s_eglGetCurrentSurface_client (void * self,EGLint readdraw);
		static EGLDisplay       EGL_APIENTRY s_eglGetCurrentDisplay_client (void * self);
		static EGLBoolean       EGL_APIENTRY s_eglSwapBuffers_client (void * self,EGLDisplay dpy, EGLSurface surface);
		static __eglMustCastToProperFunctionPointerType EGL_APIENTRY s_eglGetProcAddress_client (void * self,const char *procname);
		static EGLBoolean       EGL_APIENTRY s_eglSignalSyncKHR_client (void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
		static EGLint           EGL_APIENTRY s_eglWaitSyncKHR_client (void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
		static EGLClientBuffer  EGL_APIENTRY s_eglGetRenderBufferANDROID_client (void * self,EGLDisplay dpy, EGLSurface draw);
		static EGLint           EGL_APIENTRY s_eglDupNativeFenceFDANDROID_client (void * self,EGLDisplay dpy, EGLSyncKHR sync);
		static EGLBoolean       EGL_APIENTRY s_eglRenderBufferModifiedANDROID_client (void * self,EGLDisplay dpy, EGLSurface draw);
		static EGLuint64NV      EGL_APIENTRY s_eglGetSystemTimeFrequencyNV_client (void * self);
		static EGLuint64NV      EGL_APIENTRY s_eglGetSystemTimeNV_client (void * self);
		static EGLBoolean       EGL_APIENTRY s_eglHibernateProcessIMG_client (void * self);
		static EGLBoolean       EGL_APIENTRY s_eglAwakenProcessIMG_client (void * self);

		IOStream *stream_;
		RedFingerEGLDescribing egl_describing_;
	};
	static unsigned int GETDWORD(unsigned char *ptr)
	{
	    return *(unsigned char *)(ptr+0)
	        |(*(unsigned char *)(ptr+1)<<8)
	        |(*(unsigned char *)(ptr+2)<<16)
	        |(*(unsigned char *)(ptr+3)<<24);
	}
	static unsigned short GETWORD(unsigned char *ptr)
	{
	    return *(unsigned char *)(ptr+0)
	        |(*(unsigned char *)(ptr+1)<<8);
	}
	static unsigned char GETBYTE(unsigned char *ptr)
	{
	    return *(unsigned char *)(ptr+0);
	}
	static khronos_float_t GETFLOAT(unsigned char *ptr)
	{
	    khronos_float_t tmp;
	    memcpy(&tmp,ptr,sizeof(khronos_float_t));
	    return tmp;
	}
	static int EGLAttribListLength(const EGLint *attrib_list){
		// int i = 0;
		// if (!attrib_list)
		// {
		// 	return i;
		// }
  //       while(attrib_list[i] != EGL_NONE) {
  //       	i += 2;
  //       }
  //       i += 1;
  //       return i;
		int i = 0;
		if (!attrib_list)
		{
			return i;
		}
        while(attrib_list[i] != EGL_NONE) {
        	i++;
        }
        i += 1;
        while (attrib_list[i] == EGL_NONE)
        {
	        i += 1;
        }
        // note:last EGL_NONE,EGL_NONE,EGL_NONE,EGL_NONE
        return i;
	}
	static int GetAttribLen(const EGLint *attrib_list){
		int i = 0;
		if (!attrib_list)
		{
			return i;
		}
        while(attrib_list[i] != EGL_NONE) {
        	i += 2;
        }
        i += 1;
        return i;
	}
	explicit RedFingerEGLDispatch(IOStream *stream);
	virtual ~RedFingerEGLDispatch();
	typedef RedFingerEGLDispatch *CONTEXT_ACCESSOR_TYPE(void);
	static void setContextAccessor(CONTEXT_ACCESSOR_TYPE *f);
	static bool IsOpenAPIAccelerator(){
		return true;
	}
	static bool IsAndroid4_4_2(){
		return (marjor_version_number==4&&minor_version_number==4&&build_number==2);
	}
	static bool IsDebugOK(const API_OPCODE& opcode){
		// eglCreatePixmapSurface
		// eglReleaseTexImage
		// eglWaitGL
		// eglWaitNative
		// eglCopyBuffers
		// eglLockSurfaceKHR
		// eglUnlockSurfaceKHR
		// eglGetSyncAttribKHR
		// eglSignalSyncKHR
		// eglGetRenderBufferANDROID
		// eglRenderBufferModifiedANDROID
		// eglGetSystemTimeFrequencyNV
		// eglGetSystemTimeNV
		// eglHibernateProcessIMG
		// eglAwakenProcessIMG

		if (opcode==OP_eglBindAPI) return true;
		else if (opcode==OP_eglQueryAPI) return true;
		else if (opcode==OP_eglCreateImageKHR) return true;
		else if(opcode==OP_eglDestroyImageKHR) return true;
		else if(opcode==OP_eglDestroySyncKHR) return true;
		else if(opcode==OP_eglClientWaitSyncKHR) return true;
		else if(opcode==OP_eglSurfaceAttrib) return true;
		else if(opcode==OP_eglCreateWindowSurface) return true;
		else if(opcode==OP_eglCreatePbufferSurface) return true;
		else if(opcode==OP_eglCreatePixmapSurface) return true;
		else if(opcode==OP_eglGetConfigAttrib) return true;
		else if(opcode==OP_eglInitialize) return true;
		else if(opcode==OP_eglCreateContext) return true;
		else if(opcode==OP_eglCreateSyncKHR) return true;
		else if(opcode==OP_eglQuerySurface) return true;
		else if(opcode==OP_eglQueryContext) return true;
		else if(opcode==OP_eglGetError) return true;
		else if(opcode==OP_eglGetDisplay) return true;
		else if(opcode==OP_eglTerminate) return true;
		else if(opcode==OP_eglDestroySurface) return true;
		else if(opcode==OP_eglWaitClient) return true;
		else if(opcode==OP_eglReleaseThread) return true;
		else if(opcode==OP_eglBindTexImage) return true;
		else if(opcode==OP_eglSwapInterval) return true;
		else if(opcode==OP_eglDestroyContext) return true;
		else if(opcode==OP_eglMakeCurrent) return true;
		else if(opcode==OP_eglGetCurrentContext) return true;
		else if(opcode==OP_eglGetCurrentSurface) return true;
		else if(opcode==OP_eglGetCurrentDisplay) return true;
		else if(opcode==OP_eglSwapBuffers) return true;
		else if(opcode==OP_eglWaitSyncKHR) return true;
		else if(opcode==OP_eglDupNativeFenceFDANDROID) return true;
		else if(opcode==OP_eglGetConfigs) return true;
		else if(opcode==OP_eglChooseConfig) return true;
		return false;
	}
	RedFingerEGLEncoder* GetRedFingerEGLEncoder(){
		return (dynamic_cast<RedFingerEGLEncoder*>(&RedFingerEGLEncoder_));
	}
	RedFingerEGLDecoder* GetRedFingerEGLDecoder(){
		return (dynamic_cast<RedFingerEGLDecoder*>(&RedFingerEGLDecoder_));
	}
private:
	static int marjor_version_number;
	static int minor_version_number;
	static int build_number;
	RedFingerEGLDecoder RedFingerEGLDecoder_;
	RedFingerEGLEncoder RedFingerEGLEncoder_;
};

class RedFingerGLInterception
{
public:
	enum API_OPCODE
	{
		OP_glBeginOpcode = 0x12345,
		OP_glVertexAttribPointerOffsetOverride,
		OP_glVertexAttribPointerDataOverride,
		OP_glGetVertexAttribPointervOverride,
		OP_glEndOpcode
	};
	class RedFingerGLDescribing
	{
	public:
		typedef std::map<EGLint,std::string> GLStringiType;
		typedef std::map<EGLint,std::string>::iterator GLStringiTypeIterator;
		RedFingerGLDescribing(){
			gl_describing_.clear();
			gl_vendor_len_ = 0;
			gl_renderer_len_ = 0;
			gl_version_len_ = 0;
			gl_extensions_len_ = 0;
		}
		virtual ~RedFingerGLDescribing(){
			gl_describing_.clear();
			gl_vendor_len_ = 0;
			gl_renderer_len_ = 0;
			gl_version_len_ = 0;
			gl_extensions_len_ = 0;
		}
		void AddGLString(EGLint name,const char* str){
			if (gl_describing_.find(name)==gl_describing_.end()){
				if (str) gl_describing_[name] = str;
				else gl_describing_[name] = "";
			}
		}
		void AddGLString(EGLint name){
			AddGLString(name,(const char*)&tmp_[0]);
		}
		EGLuint GetLength(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = gl_describing_.find(name);
			if (it==gl_describing_.end())
				return 0;
			return it->second.length();
		}
		const char* GetGLString(const EGLuint name){
			std::map<EGLint,std::string>::iterator it = gl_describing_.find(name);
			if (it==gl_describing_.end())
				return NULL;
			return it->second.c_str();
		}

		void AddGLStringi(GLenum name,GLuint index,const char* str){
			if (glStringi_desc_.find(name)==glStringi_desc_.end()){
				if (str&&str[0]){
					GLStringiType sss;
					sss[index] = std::string(str);
					glStringi_desc_[name] = sss;
				}
			}
		}
		const EGLuint GetLengthi(GLenum name,GLuint index){
			std::map<GLenum,GLStringiType>::iterator it = glStringi_desc_.find(name);
			if (it==glStringi_desc_.end())
				return 0;
			GLStringiTypeIterator it1 = it->second.find(index);
			if (it1==it->second.end())
				return 0;
			return it1->second.length();
		}
		const char* GetGLStringi(GLenum name,GLuint index){
			std::map<GLenum,GLStringiType>::iterator it = glStringi_desc_.find(name);
			if (it==glStringi_desc_.end())
				return NULL;
			GLStringiTypeIterator it1 = it->second.find(index);
			if (it1==it->second.end())
				return NULL;
			return it1->second.c_str();
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
		std::map<GLenum,GLStringiType> glStringi_desc_;
		std::vector<unsigned char> tmp_;	
	};
	class RedFingerCallGLOrigin
	{
	public:
		static bool IsCallNativeFunction(){
			return false;
		}
		RedFingerCallGLOrigin();
		virtual ~RedFingerCallGLOrigin();
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
	    glGetStringi_server_proc_t glGetStringi;
	    glShaderSource_server_proc_t glShaderSource;
	    glVertexAttribPointer_server_proc_t glVertexAttribPointer;
	    glGetVertexAttribPointerv_server_proc_t glGetVertexAttribPointerv;
	    glEnableClientState_server_proc_t glEnableClientState;
	    glDisableClientState_server_proc_t glDisableClientState;
	    glEGLImageTargetTexture2DOES_server_proc_t glEGLImageTargetTexture2DOES;
	    glEGLImageTargetRenderbufferStorageOES_server_proc_t glEGLImageTargetRenderbufferStorageOES;
	    glTexStorage2DEXT_typedef glTexStorage2DEXT;
	    glTextureStorage2DEXT_typedef glTextureStorage2DEXT;
	};
	RedFingerGLInterception();
	virtual ~RedFingerGLInterception();
	size_t decode(void *buf, size_t len, IOStream *stream);
	void SetInitialize(bool initialized){
		initialized_ = initialized;
	}
	bool IsInitialize(){
		return initialized_;
	}
	RedFingerGLDescribing* GetGLDescribing(){
		return (dynamic_cast<RedFingerGLDescribing*>(&gl_describing_));
	}
	RedFingerGLDescribing* GetGLStringiPtr(){
		return (dynamic_cast<RedFingerGLDescribing*>(&glGetStringi_desc_));
	}
	RedFingerCallGLOrigin* GetCallGLOrigin(){
		return (dynamic_cast<RedFingerCallGLOrigin*>(&call_gl_origin_));
	}
	typedef RedFingerGLInterception *CONTEXT_ACCESSOR_TYPE(void);
	static void setContextAccessor(CONTEXT_ACCESSOR_TYPE *f);
public:
	static bool IsInterceptionTargetOpcode(void *buf, size_t len);
	static bool IsOffsetPointer(const void* ptr){
		return ((EGLuint)ptr<=0x400000);
	}
	static const GLubyte* s_glGetString_enc(void *self, GLenum name);
	static EGLint s_glGetString_client(void * self,EGLint name,void* buf,EGLuint buflen);
	EGLint s_glGetString_server(EGLint name,void* buf,EGLuint buflen);

	static const GLubyte* s_glGetStringi_enc(void * self, GLenum name, GLuint index);
	static EGLint s_glGetStringi_client(void * self,GLenum name,GLuint index,void* buf,EGLuint buflen);
	EGLint s_glGetStringi_server(GLenum name,GLuint index,void* buf,EGLuint buflen);

	static void s_glShaderSource_enc(void *self, GLuint shader, GLsizei count, const GLchar * const *strings, const GLint *length);
	static EGLBoolean s_glShaderSource_client(void *self, GLuint shader, const GLchar* string, GLsizei len);
	EGLBoolean s_glShaderSource_server(GLuint shader, const GLchar* string, GLsizei len);

	static void s_glVertexAttribPointer_enc(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
	EGLBoolean s_glVertexAttribPointerOffset_server(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);

	static void s_glGetVertexAttribPointerv_enc(void *self, GLuint index, GLenum pname, GLvoid **pointer);
	void s_glGetVertexAttribPointerv_server(GLuint index, GLenum pname, GLvoid **pointer);

	//GL extensions
	static void s_glEGLImageTargetTexture2DOES_ext(void * self, GLenum target, GLeglImageOES image);
	static void s_glEGLImageTargetRenderbufferStorageOES_ext(void *self, GLenum target, GLeglImageOES image);
private:
	RedFingerGLDescribing glGetStringi_desc_;
	RedFingerGLDescribing gl_describing_;
	RedFingerCallGLOrigin call_gl_origin_;
	bool initialized_;
};

class GLESv2DispatchInternal : 
	public GLESv2Decoder,GLESv2Encoder,
			RedFingerEGLDispatch,
			RedFingerGLInterception
{
public:
	GLESv2DispatchInternal(IOStream *stream);
	virtual ~GLESv2DispatchInternal();
	GLESv2Encoder* GetGLESv2EncPtr(){
		return (dynamic_cast<GLESv2Encoder*>(this));
	}
	GLESv2Decoder* GetGLESv2DecPtr(){
		return (dynamic_cast<GLESv2Decoder*>(this));
	}
	RedFingerEGLDispatch* GetEGLDispatch(){
		return (dynamic_cast<RedFingerEGLDispatch*>(this));
	}
	RedFingerGLInterception* GetGLInterception(){
		return (dynamic_cast<RedFingerGLInterception*>(this));
	}
	gles_encoder_context_t* GetEncoder(){
		return GetGLESv2EncPtr()->GetEncoder();
	}
	gles_decoder_context_t* GetDecoder(){
		return GetGLESv2DecPtr()->GetDecoder();
	}
private:
	GLESv2NativeFuncCall* GetGLESv2NativeFuncCall(){
		return (dynamic_cast<GLESv2NativeFuncCall*>(&glesv2_native_func_call_));
	}
	GLESv2NativeFuncCall glesv2_native_func_call_;
};

#endif