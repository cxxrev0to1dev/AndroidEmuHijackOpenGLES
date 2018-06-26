#include "GLESv2DispatchInternal.h"
#include <sys/mman.h>
#include "glUtils.h"
#include "ErrorLog.h"
#include "gles_opcodes.h"

static GLubyte *gVersionString= (GLubyte *) "OpenGL ES 2.0";
static GLubyte *gExtensionsString= (GLubyte *) "GL_EXT_debug_marker GL_OES_EGL_image GL_OES_depth24 GL_OES_depth32 GL_OES_element_index_uint GL_OES_texture_float GL_OES_texture_float_linear GL_OES_compressed_paletted_texture GL_OES_compressed_ETC1_RGB8_texture GL_IMG_texture_compression_pvrtc GL_OES_depth_texture GL_OES_texture_half_float GL_OES_texture_half_float_linear GL_OES_packed_depth_stencil GL_OES_vertex_half_float GL_EXT_texture_format_BGRA8888 GL_OES_EGL_image_external GL_IMG_texture_compression_pvrtc GL_OES_EGL_image_external";

static inline void* SafePointerFromUInt(GLuint value) {
  return (void*)(uintptr_t)value;
}
template <typename T1>
T1 ReadPointerArg(T1 s1,unsigned char* ptr){
	T1 tmp;
	memmove(&tmp,ptr,sizeof(T1));
	return tmp;
}
EGLConfig ReadEGLConfig(unsigned char* ptr){
	EGLConfig s1;
	return ReadPointerArg(s1,ptr);
}
EGLContext ReadEGLContext(unsigned char* ptr){
	EGLContext s1;
	return ReadPointerArg(s1,ptr);
}
EGLDisplay ReadEGLDisplay(unsigned char* ptr){
	EGLDisplay s1;
	return ReadPointerArg(s1,ptr);
}
EGLSurface ReadEGLSurface(unsigned char* ptr){
	EGLSurface s1;
	return ReadPointerArg(s1,ptr);
}
EGLClientBuffer ReadEGLClientBuffer(unsigned char* ptr){
	EGLClientBuffer s1;
	return ReadPointerArg(s1,ptr);
}
EGLSyncKHR ReadEGLSyncKHR(unsigned char* ptr){
	EGLSyncKHR s1;
	return ReadPointerArg(s1,ptr);
}
EGLImageKHR ReadEGLImageKHR(unsigned char* ptr){
	EGLImageKHR s1;
	return ReadPointerArg(s1,ptr);
}
EGLTimeKHR ReadEGLTimeKHR(unsigned char* ptr){
	EGLTimeKHR s1;
	return ReadPointerArg(s1,ptr);
}
EGLNativePixmapType ReadEGLNativePixmapType(unsigned char* ptr){
	EGLNativePixmapType s1;
	return ReadPointerArg(s1,ptr);
}
EGLNativeWindowType ReadEGLNativeWindowType(unsigned char* ptr){
	EGLNativeWindowType s1;
	return ReadPointerArg(s1,ptr);
}
EGLNativeDisplayType ReadEGLNativeDisplayType(unsigned char* ptr){
	EGLNativeDisplayType s1;
	return ReadPointerArg(s1,ptr);
}
EGLenum ReadEGLenum(unsigned char* ptr){
	EGLenum s1;
	return ReadPointerArg(s1,ptr);
}
EGLint ReadEGLint(unsigned char* ptr){
	EGLint s1;
	return ReadPointerArg(s1,ptr);
}
EGLuint ReadEGLuint(unsigned char* ptr){
	EGLuint s1;
	return ReadPointerArg(s1,ptr);
}
EGLBoolean ReadEGLBoolean(unsigned char* ptr){
	EGLBoolean s1;
	return ReadPointerArg(s1,ptr);
}
GLuint ReadGLuint(unsigned char* ptr){
	GLuint s1;
	return ReadPointerArg(s1,ptr);
}
GLint ReadGLint(unsigned char* ptr){
	GLint s1;
	return ReadPointerArg(s1,ptr);
}
GLenum ReadGLenum(unsigned char* ptr){
	GLenum s1;
	return ReadPointerArg(s1,ptr);
}
GLboolean ReadGLboolean(unsigned char* ptr){
	GLboolean s1;
	return ReadPointerArg(s1,ptr);
}
GLsizei ReadGLsizei(unsigned char* ptr){
	GLsizei s1;
	return ReadPointerArg(s1,ptr);
}



template <typename T1>
unsigned char* WritePointerArg(T1 s1,unsigned char* ptr){
	memmove(ptr,&s1,sizeof(T1));
	return (ptr + sizeof(T1));
}
unsigned char* WriteEGLConfig(EGLConfig s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLContext(EGLContext s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLDisplay(EGLDisplay s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLSurface(EGLSurface s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLClientBuffer(EGLClientBuffer s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLSyncKHR(EGLSyncKHR s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLImageKHR(EGLImageKHR s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLTimeKHR(EGLTimeKHR s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLenum(EGLenum s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLint(EGLint s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLuint(EGLuint s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLBoolean(EGLBoolean s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteGLuint(GLuint s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteGLint(GLint s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteGLenum(GLenum s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteGLboolean(GLboolean s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteGLsizei(GLsizei s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}


unsigned char* WriteEGLNativePixmapType(EGLNativePixmapType s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLNativeWindowType(NativeWindowType s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLNativeDisplayType(EGLNativeDisplayType s1,unsigned char* ptr){
	return WritePointerArg(s1,ptr);
}
unsigned char* WriteEGLintArray(const EGLint* attrib_list,EGLuint len,unsigned char* ptr){
	if (!attrib_list)
	{
		return ptr;
	}
	unsigned char* buf = ptr;
	for (int i = 0; i < len; i++)
	{
		memmove(&buf[0],&attrib_list[i],sizeof(EGLint));
		buf += sizeof(EGLint);
	}
	return (ptr + (len * sizeof(EGLint)));
}
unsigned char* WriteEGLConfigArray(EGLConfig* config_list,EGLuint len,unsigned char* ptr){
	if (!config_list)
	{
		return ptr;
	}
	unsigned char* buf = ptr;
	for (int i = 0; i < len; i++)
	{
		memmove(&buf[0],&config_list[i],sizeof(EGLConfig));
		buf += sizeof(EGLint);
	}
	return (ptr + (len * sizeof(EGLConfig)));
}



GLESv2DispatchInternal::GLESv2DispatchInternal(IOStream *stream) : 
	GLESv2Encoder(stream),
	RedFingerEGLDispatch(stream){
	ALOGE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
	GetGLESv2EncPtr()->initGL();
	GetGLESv2EncPtr()->glGetString = RedFingerGLInterception::s_glGetString_enc;
	GetGLESv2EncPtr()->glGetStringi = RedFingerGLInterception::s_glGetStringi_enc;
	GetGLESv2EncPtr()->glShaderSource = RedFingerGLInterception::s_glShaderSource_enc;
	GetGLESv2EncPtr()->glVertexAttribPointer = RedFingerGLInterception::s_glVertexAttribPointer_enc;
	GetGLESv2EncPtr()->glGetVertexAttribPointerv = RedFingerGLInterception::s_glGetVertexAttribPointerv_enc;
	GetGLESv2DecPtr()->initGL();
	// GL extensions
	GetGLESv2EncPtr()->glEGLImageTargetTexture2DOES = RedFingerGLInterception::s_glEGLImageTargetTexture2DOES_ext;
	GetGLESv2EncPtr()->glEGLImageTargetRenderbufferStorageOES = RedFingerGLInterception::s_glEGLImageTargetRenderbufferStorageOES_ext;
	if (RedFinger::Debug::IsOverrideGLESv2FuncWithNativeFuncCall()){
		GetGLESv2NativeFuncCall()->initGL(GetEncoder());
	}
}
GLESv2DispatchInternal::~GLESv2DispatchInternal(){
	ALOGE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
}

#undef GET_CONTEXT_client_glInterception
#ifndef GET_CONTEXT_client_glInterception
static RedFingerGLInterception::CONTEXT_ACCESSOR_TYPE *getCurrentContext_gl_client = NULL;
void RedFingerGLInterception::setContextAccessor(CONTEXT_ACCESSOR_TYPE *f) { getCurrentContext_gl_client = f; }
#define GET_CONTEXT_client_glInterception RedFingerGLInterception* ctxGLInterception = getCurrentContext_gl_client() 
#endif

#ifndef GL_TRUE
extern "C"{
		// FIXME
		// called unimplemented OpenGL ES API
    void GL_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){
    	GET_CONTEXT_client_glInterception;
    	ctxGLInterception->GetCallGLOrigin()->glTexStorage2DEXT(target,levels,internalformat,width,height);
    }
}
#endif

RedFingerGLInterception::RedFingerGLInterception(){
	SetInitialize(false);
	GetCallGLOrigin()->Init();
}
RedFingerGLInterception::~RedFingerGLInterception(){
	SetInitialize(false);
}
RedFingerGLInterception::RedFingerCallGLOrigin::RedFingerCallGLOrigin(){
	Reset();
}
RedFingerGLInterception::RedFingerCallGLOrigin::~RedFingerCallGLOrigin(){
	Reset();
}
void RedFingerGLInterception::RedFingerCallGLOrigin::Init(){
	static const char* kHardwareGLESLibrary = "/system/vendor/lib/egl/rk3288/libGLES_mali.so.bak";
	void *gles_android = dlopen(kHardwareGLESLibrary, RTLD_NOW | RTLD_LOCAL);
	glVertexPointer = (glVertexPointer_server_proc_t)dlsym(gles_android,"glVertexPointer");
	glNormalPointer = (glNormalPointer_server_proc_t)dlsym(gles_android,"glNormalPointer");
	glColorPointer = (glColorPointer_server_proc_t)dlsym(gles_android,"glColorPointer");
	glPointSizePointerOES = (glPointSizePointerOES_server_proc_t)dlsym(gles_android,"glPointSizePointerOES");
	glTexCoordPointer = (glTexCoordPointer_server_proc_t)dlsym(gles_android,"glTexCoordPointer");
	glClientActiveTexture = (glClientActiveTexture_server_proc_t)dlsym(gles_android,"glClientActiveTexture");
	glMatrixIndexPointerOES = (glMatrixIndexPointerOES_server_proc_t)dlsym(gles_android,"glMatrixIndexPointerOES");
	glWeightPointerOES = (glWeightPointerOES_server_proc_t)dlsym(gles_android,"glWeightPointerOES");
	glEnableClientState = (glEnableClientState_server_proc_t)dlsym(gles_android,"glEnableClientState");
	glDisableClientState = (glDisableClientState_server_proc_t)dlsym(gles_android,"glDisableClientState");

	glEGLImageTargetTexture2DOES = (glEGLImageTargetTexture2DOES_server_proc_t)dlsym(gles_android,"glEGLImageTargetTexture2DOES");
	glEGLImageTargetRenderbufferStorageOES = (glEGLImageTargetRenderbufferStorageOES_server_proc_t)dlsym(gles_android,"glEGLImageTargetRenderbufferStorageOES");

	glGetString = (glGetString_server_proc_t)dlsym(gles_android,"glGetString");
	glGetStringi = (glGetStringi_server_proc_t)dlsym(gles_android,"glGetStringi");
	glShaderSource = (glShaderSource_server_proc_t)dlsym(gles_android,"glShaderSource");
	glVertexAttribPointer = (glVertexAttribPointer_server_proc_t)dlsym(gles_android,"glVertexAttribPointer");
	glGetVertexAttribPointerv = (glGetVertexAttribPointerv_server_proc_t)dlsym(gles_android,"glGetVertexAttribPointerv");
	glTexStorage2DEXT = (glTexStorage2DEXT_typedef)dlsym(gles_android,"glTexStorage2DEXT");
	glTextureStorage2DEXT = (glTextureStorage2DEXT_typedef)dlsym(gles_android,"glTextureStorage2DEXT");
}
void RedFingerGLInterception::RedFingerCallGLOrigin::Reset(){
	glVertexPointer = NULL;
	glNormalPointer = NULL;
	glColorPointer = NULL;
	glPointSizePointerOES = NULL;
	glTexCoordPointer = NULL;
	glClientActiveTexture = NULL;
	glMatrixIndexPointerOES = NULL;
	glWeightPointerOES = NULL;
	glEnableClientState = NULL;
	glDisableClientState = NULL;
	glGetString = NULL;
	glShaderSource = NULL;
	glVertexAttribPointer = NULL;
	glGetVertexAttribPointerv = NULL;
	glEGLImageTargetTexture2DOES = NULL;
	glEGLImageTargetRenderbufferStorageOES = NULL;
	glTexStorage2DEXT = NULL;
	glTextureStorage2DEXT = NULL;
}
size_t RedFingerGLInterception::decode(void *buf, size_t len, IOStream *stream){
	size_t pos = 0;
	if (len < (sizeof(EGLuint) * 2)) return pos; 
	unsigned char *ptr = (unsigned char *)buf;
	bool unknownOpcode = false; 
#ifdef CHECK_GL_ERROR 
	char lastCall[256] = {0}; 
#endif 
	while ((len - pos >= (sizeof(EGLuint) * 2)) && !unknownOpcode) {  
		EGLuint opcode = RedFingerEGLDispatch::GETDWORD(ptr);  
		EGLuint packetLen = RedFingerEGLDispatch::GETDWORD(ptr + sizeof(EGLuint));
		const EGLuint sb = (sizeof(EGLuint) * 2);
		if (len - pos < packetLen) return pos; 
		switch(opcode) {
			case OP_glGetString:{
				const EGLuint name = ReadEGLuint(ptr + sb);
				const EGLuint __size_buf = ReadEGLuint(ptr + sb + sizeof(EGLuint));
				const EGLuint buflen = ReadEGLuint(ptr + sb + sizeof(EGLuint) + sizeof(EGLuint));
				size_t totalTmpSize = sizeof(EGLint) + __size_buf;

				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[sizeof(EGLint)];
				unsigned char *tmpReturnPtr = &tmpBuf[0];
				WriteEGLint(s_glGetString_server(name,tmpPtr3,buflen),&tmpReturnPtr[0]);
				stream->writeback();
				pos += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				ptr += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				break;
			}
			case OP_glGetStringi:{
				const EGLuint name = ReadEGLuint(ptr + sb);
				const EGLuint index = ReadEGLuint(ptr + sb + sizeof(EGLuint));
				const EGLuint __size_buf = ReadEGLuint(ptr + sb + sizeof(EGLuint) + sizeof(EGLuint));
				const EGLuint buflen = ReadEGLuint(ptr + sb + sizeof(EGLuint) + sizeof(EGLuint) + sizeof(EGLuint));
				size_t totalTmpSize = sizeof(EGLint) + __size_buf;

				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[sizeof(EGLint)];
				unsigned char *tmpReturnPtr = &tmpBuf[0];
				WriteEGLint(s_glGetStringi_server(name,index,tmpPtr3,buflen),&tmpReturnPtr[0]);
				stream->writeback();
				pos += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				ptr += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				break;
			}
			case OP_glShaderSource:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				const GLint shader = ReadGLint(ptr + sb);
				const GLint len = ReadGLint(ptr + sb + sizeof(GLint));
				char* shader_string = new char[len + sizeof(char)];
				memset(shader_string,0,(len + sizeof(char)));
				memmove(shader_string,(ptr + sb + sizeof(GLint) + sizeof(GLint)),len);
				WriteEGLBoolean(s_glShaderSource_server(shader,shader_string,len),&tmpBuf[0]);
				stream->writeback();
				delete[] shader_string;
				pos += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				ptr += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				break;
			}
			case OP_glVertexAttribPointerOffsetOverride:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				GLuint indx = ReadGLuint(ptr + sb);
				GLint size = ReadGLint(ptr + sb + sizeof(GLuint));
				GLenum type = ReadGLenum(ptr + sb + sizeof(GLuint) + sizeof(GLint));
				GLboolean normalized = (GLboolean)ReadGLuint(ptr + sb + sizeof(GLuint) + sizeof(GLint) + sizeof(GLenum));// GLboolean
				GLsizei stride = ReadGLsizei(ptr + sb + sizeof(GLuint) + sizeof(GLint) + sizeof(GLenum) + sizeof(GLuint));
				GLuint p = ReadGLuint(ptr + sb + sizeof(GLuint) + sizeof(GLint) + sizeof(GLenum) + sizeof(GLuint) + sizeof(GLsizei));
				// if (RedFinger::Debug::IsDebugPrint()){
				// 	ALOGD("OP_glVertexAttribPointerOffset:%s:%s:%d:GLuint indx %p, GLint size %p, GLenum type %p, GLboolean normalized %p, GLsizei stride %p, const GLvoid* ptr %p\n", 
		  //       		__FILE__, __FUNCTION__, __LINE__, indx,size,type,normalized,stride,p);
				// }
				s_glVertexAttribPointerOffset_server(indx,size,type,normalized,stride,(const GLvoid*)p);
				pos += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				ptr += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				break;
			}
			case OP_glVertexAttribPointerDataOverride:{
				break;
			}
			case OP_glGetVertexAttribPointervOverride:{
				size_t totalTmpSize = sizeof(EGLuint);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				GLuint index = ReadGLuint(ptr + sb);
				GLenum pname = ReadGLenum(ptr + sb + sizeof(GLuint));
				EGLuint tmpPtr3Size = ReadEGLuint(ptr + sb + sizeof(GLuint) + sizeof(GLenum));
				s_glGetVertexAttribPointerv_server(index,pname,(tmpPtr3Size == 0 ? NULL : (GLvoid**)&tmpBuf));
				stream->writeback();
				pos += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				ptr += RedFingerEGLDispatch::GETDWORD(ptr + 4);
				break;
			}
			default:
			unknownOpcode = true;
			break;
		}
	}
	return pos;
}
bool RedFingerGLInterception::IsInterceptionTargetOpcode(void *buf, size_t len){
	if (len < 8) return false;
	unsigned char *ptr = (unsigned char *)buf;
	EGLuint opcode = RedFingerEGLDispatch::GETDWORD(ptr);
	return (opcode==OP_glGetString||opcode==OP_glGetStringi||opcode==OP_glShaderSource||(opcode>OP_glBeginOpcode&&opcode<OP_glEndOpcode));
}
const GLubyte* RedFingerGLInterception::s_glGetString_enc(void *self, GLenum name){	
	if (name==GL_EXTENSIONS){
		return gExtensionsString;
	}
	// else if (name==GL_VERSION){
	// 	return gVersionString;
	// }
	GET_CONTEXT_client_glInterception;
	RedFingerGLInterception::RedFingerGLDescribing* gl_describing = ctxGLInterception->GetGLDescribing();

	gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	GLubyte *retval =  (GLubyte *) "";// NOTE:no be NULL
	if (RedFingerEGLDispatch::IsOpenAPIAccelerator()){
		const char* retstr = gl_describing->GetGLString(name);
		if (retstr==NULL){
			char tmp[10000] = {0};
			if(s_glGetString_client(self,name,gl_describing->ResetTmp(10000),10000)>0){
				gl_describing->AddGLString(name);
				retstr = gl_describing->GetGLString(name);
				if (retstr!=NULL){
					retval = (GLubyte *) retstr;
				}
			}
			return retval;
		}
		retval = (GLubyte *)retstr;
	}
    return retval;
}
EGLint RedFingerGLInterception::s_glGetString_client(void * self,EGLint name,void* buf,EGLuint buflen){
	GET_CONTEXT_client_glInterception;
	gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint __size_buf =  buflen;
	const EGLuint packetSize = __size_base + (3 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_glGetString;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLuint(name,ptr);
		ptr = WriteEGLuint(__size_buf,ptr);
		ptr = WriteEGLuint(buflen,ptr);

	EGLint retval;
	stream->readback(&retval, sizeof(EGLint));
	if (retval<=0){
		return 0;
	}
	stream->readback(buf, retval);/*FIXME,please verify buf result*/
	if(RedFinger::Debug::IsDebugPrint()){
		ALOGD("DebuginggggggggggggggggggggggggggggggggBuf:%s:%p:%s:%p",__FUNCTION__,name,buf,retval);
	}
	return retval;
}

std::string Replace(std::string &s,
    				const std::string &toReplace,
    				const std::string &replaceWith) {
  return(s.replace(s.find(toReplace), toReplace.length(), replaceWith));
}
EGLint RedFingerGLInterception::s_glGetString_server(EGLint name,void* buf,EGLuint buflen){
	GET_CONTEXT_client_glInterception;
	RedFingerGLInterception::RedFingerGLDescribing* gl_describing = ctxGLInterception->GetGLDescribing();
	char* str = const_cast<char*>(ctxGLInterception->GetGLDescribing()->GetGLString(name));
	if (str==NULL){
		if(RedFinger::Debug::IsDebugPrint()){
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:%s",__FUNCTION__,(const char*)ctxGLInterception->GetCallGLOrigin()->glGetString(name));
		}
		str = (char*)ctxGLInterception->GetCallGLOrigin()->glGetString(name);
	    if (!str) {
        	return 0;
    	}
    	std::string sss((char*)str);// FIXME:GL_OES_mapbuffer not support
    	if (sss.find(" GL_OES_mapbuffer ")!=std::string::npos){
    		sss = Replace(sss,std::string(" GL_OES_mapbuffer "),std::string(" "));
    	}
    	if (sss.find(" GL_OES_get_program_binary ")!=std::string::npos){// FIXME:glGetProgramBinaryOES glProgramBinaryOES not support
    		sss = Replace(sss,std::string(" GL_OES_get_program_binary "),std::string(" "));
    	}
    	ctxGLInterception->GetGLDescribing()->AddGLString(name,sss.c_str());
	}
	std::string glStr(str);
	EGLint len = glStr.size() + 1;
    if (!buf || len > buflen) {
        return -len;
    }
    strcpy((char *)buf, glStr.c_str());
    return len;
}
const GLubyte* RedFingerGLInterception::s_glGetStringi_enc(void * self, GLenum name, GLuint index){
	GET_CONTEXT_client_glInterception;
	RedFingerGLInterception::RedFingerGLDescribing* glStringiP = ctxGLInterception->GetGLStringiPtr();

	gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	GLubyte *retval =  (GLubyte *) "";// NOTE:no be NULL
	if (RedFingerEGLDispatch::IsOpenAPIAccelerator()){
		const char* retstr = glStringiP->GetGLStringi(name,index);
		if (retstr==NULL){
			std::vector<char> v;
			v.resize(10000);
			if(s_glGetStringi_client(self,name,index,&v[0],10000)>0){
				char* tmpp = &v[0];
				if(RedFinger::Debug::IsDebugPrint()){
					ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:%s",__FUNCTION__,(char*)&v[0]);
				}
				glStringiP->AddGLStringi(name,index,tmpp);
				retstr = glStringiP->GetGLStringi(name,index);
				if (retstr!=NULL){
					retval = (GLubyte *) retstr;
					if(RedFinger::Debug::IsDebugPrint()){
						ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:%s",__FUNCTION__,(char*)retval);
					}
				}
			}
			return retval;
		}
		retval = (GLubyte *)retstr;
	}
    return retval;
}
EGLint RedFingerGLInterception::s_glGetStringi_client(void * self,GLenum name,GLuint index,void* buf,EGLuint buflen){
	GET_CONTEXT_client_glInterception;
	gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint __size_buf =  buflen;
	const EGLuint packetSize = __size_base + (4 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_glGetStringi;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLuint(name,ptr);
		ptr = WriteEGLuint(index,ptr);
		ptr = WriteEGLuint(__size_buf,ptr);
		ptr = WriteEGLuint(buflen,ptr);
	EGLint retval;
	stream->readback(&retval, sizeof(EGLint));
	if (retval<=0){
		return 0;
	}
	stream->readback(buf, retval);/*FIXME,please verify buf result*/
	return retval;
}
EGLint RedFingerGLInterception::s_glGetStringi_server(GLenum name,GLuint index,void* buf,EGLuint buflen){
	GET_CONTEXT_client_glInterception;
	char* str = const_cast<char*>(ctxGLInterception->GetGLStringiPtr()->GetGLStringi(name,index));
	if (str==NULL){
		str = (char*)ctxGLInterception->GetCallGLOrigin()->glGetStringi(name,index);
	    if (!str) {
        	return 0;
    	}
    	if(RedFinger::Debug::IsDebugPrint()){
    		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:%s",__FUNCTION__,(char*)ctxGLInterception->GetCallGLOrigin()->glGetStringi(name,index));
    	}
    	ctxGLInterception->GetGLDescribing()->AddGLStringi(name,index,const_cast<const char*>(str));
	}
	std::string glStr(str);
	EGLint len = glStr.size() + 1;
    if (!buf || len > buflen) {
        return -len;
    }
    strcpy((char *)buf, glStr.c_str());
    return len;
}

void RedFingerGLInterception::s_glShaderSource_enc(void *self, GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length){

 //    GET_CONTEXT_client_glInterception;
 //    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
	// ShaderData* shaderData = ctx->shared_static()->getShaderData(shader);
	// std::vector<std::string> orig_sources;
 //    for (int i = 0; i < count && string && string[i]; i++) {
 //        orig_sources.push_back(std::string((const char*)(string[i])));
 //    }
 //    shaderData->sources = orig_sources;


    int len = glUtilsCalcShaderSourceLen((char**)string, (GLint*)length, count);
    char *str = new char[len + 1];
    glUtilsPackStrings(str, (char**)string, (GLint*)length, count);
    s_glShaderSource_client(self,shader,str,len);
    delete[] str;
}
EGLBoolean RedFingerGLInterception::s_glShaderSource_client(void *self, GLuint shader, const GLchar* string, GLsizei len){
	GET_CONTEXT_client_glInterception;
	gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (2 * sizeof(EGLuint)) + len;
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_glShaderSource;
		ptr = WriteGLuint(tmp,ptr);
		ptr = WriteGLuint(packetSize,ptr);
		ptr = WriteGLint(shader,ptr);
		ptr = WriteGLint(len,ptr);
		memmove(ptr,string,len);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:arg1 %p:arg2 %s:arg3 %p",__FUNCTION__,shader,string,len);
	}
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerGLInterception::s_glShaderSource_server(GLuint shader, const GLchar* string, GLsizei len){
	GET_CONTEXT_client_glInterception;
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:arg1 %p:arg2 %s:arg3 %p",__FUNCTION__,shader,string,len);
	}
	ctxGLInterception->GetCallGLOrigin()->glShaderSource(shader, 1, &string, NULL);
	return EGL_TRUE;
}
void RedFingerGLInterception::s_glVertexAttribPointer_enc(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized, 
	GLsizei stride, const GLvoid* ptr){
	GET_CONTEXT_client_glInterception;
	if (RedFingerCallGLOrigin::IsCallNativeFunction()){
		GLESv2Encoder *ctxxx = (GLESv2Encoder *)self;
		// ALOGD("%s:%s:%d:GLuint indx %p, GLint size %p, GLenum type %p, GLboolean normalized %p, GLsizei stride %p, const GLvoid* ptr %p\n", 
  //       		__FILE__, __FUNCTION__, __LINE__,indx,size,type,normalized,stride,ptr);
		GLESv2Encoder::s_glVertexAttribPointer(self,indx,size,type,normalized,stride,ptr);
		ctxGLInterception->GetCallGLOrigin()->glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
		return;
	}
	gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	if (false/*RedFingerGLInterception::IsOffsetPointer(ptr)*/){
		// if (RedFinger::Debug::IsDebugPrint()){
		// 	ALOGD("glVertexAttribPointerOffset:%s:%s:%d:GLuint indx %p, GLint size %p, GLenum type %p, GLboolean normalized %p, GLsizei stride %p, const GLvoid* ptr %p\n", 
  //       		__FILE__, __FUNCTION__, __LINE__,indx,size,type,normalized,stride,ptr);
		// }
		EGLuint tmp = OP_glVertexAttribPointerOffsetOverride;
		const EGLuint packetSize = __size_base + sizeof(GLuint) + sizeof(GLint) + sizeof(GLenum) + sizeof(GLuint) + sizeof(GLsizei) + sizeof(GLuint);
		unsigned char *pointer = stream->alloc(packetSize);
		pointer = WriteEGLuint(tmp,pointer);
		pointer = WriteEGLuint(packetSize,pointer);
		pointer = WriteGLuint(indx,pointer);
		pointer = WriteGLint(size,pointer);
		pointer = WriteGLenum(type,pointer);
		pointer = WriteGLuint(normalized,pointer);// GLboolean
		pointer = WriteGLsizei(stride,pointer);
		pointer = WriteGLuint(reinterpret_cast<GLuint>(ptr),pointer);
		stream->flush();
	}
	else{
	    // ALOGD("%s:%s:%d:GLuint indx %p, GLint size %p, GLenum type %p, GLboolean normalized %p, GLsizei stride %p, const GLvoid* ptr %p\n", 
	    //     __FILE__, __FUNCTION__, __LINE__, indx,size,type,normalized,stride,ptr);
		GLESv2Encoder::s_glVertexAttribPointer(self,indx,size,type,normalized,stride,ptr);
		return;
	}
}
EGLBoolean RedFingerGLInterception::s_glVertexAttribPointerOffset_server(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr){
	GET_CONTEXT_client_glInterception;
	ctxGLInterception->GetCallGLOrigin()->glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
	return EGL_TRUE;
}
void RedFingerGLInterception::s_glGetVertexAttribPointerv_enc(void *self, GLuint index, GLenum pname, GLvoid **pointer){
	GET_CONTEXT_client_glInterception;
	if (RedFingerCallGLOrigin::IsCallNativeFunction()){
		gles_encoder_context_t *ctx = (gles_encoder_context_t *)self;
		IOStream *stream = ctx->m_stream;
		const EGLuint __size_base = (sizeof(EGLuint) * 2);
		const EGLuint packetSize = __size_base + (3 * sizeof(EGLuint));
		const EGLuint __size_pointer = ((pointer != NULL) ?  (sizeof(EGLuint)) : 0);
		unsigned char *ptr = stream->alloc(packetSize);
		EGLuint tmp = OP_glGetVertexAttribPointervOverride;
			ptr = WriteEGLuint(tmp,ptr);
			ptr = WriteEGLuint(packetSize,ptr);
			ptr = WriteGLuint(index,ptr);
			ptr = WriteGLenum(pname,ptr);
			ptr = WriteEGLuint(__size_pointer,ptr);
		EGLuint ret_pointer;
		stream->readback(&ret_pointer, sizeof(EGLuint));
		*pointer = (GLvoid*)ret_pointer;
		return;
	}
	else{
		GLESv2Encoder::s_glGetVertexAttribPointerv(self,index,pname,pointer);
		return;
	}
}
void RedFingerGLInterception::s_glGetVertexAttribPointerv_server(GLuint index, GLenum pname, GLvoid **pointer){
	GET_CONTEXT_client_glInterception;
	ctxGLInterception->GetCallGLOrigin()->glGetVertexAttribPointerv(index,pname,pointer);
}
void RedFingerGLInterception::s_glEGLImageTargetTexture2DOES_ext(void * self, GLenum target, GLeglImageOES image){
    GET_CONTEXT_client_glInterception;
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    if (RedFinger::Debug::IsDebugPrint()){
    	ALOGD("s_glEGLImageTargetTexture2DOES_ext target=%#x image=%p", target, image);
	}
    ctx->override2DTextureTarget(target);
    ctxGLInterception->GetCallGLOrigin()->glEGLImageTargetTexture2DOES(target,image);
    ctx->restore2DTextureTarget(target);
    return;
}
void RedFingerGLInterception::s_glEGLImageTargetRenderbufferStorageOES_ext(void *self, GLenum target, GLeglImageOES image){
    GET_CONTEXT_client_glInterception;
    if (RedFinger::Debug::IsDebugPrint()){
    	ALOGD("s_glEGLImageTargetRenderbufferStorageOES_ext target=%#x image=%p", target, image);
	}
    ctxGLInterception->GetCallGLOrigin()->glEGLImageTargetRenderbufferStorageOES(target,image);
    return;
}

#undef GET_CONTEXT_client_egl
#ifndef GET_CONTEXT_client_egl
static RedFingerEGLDispatch::CONTEXT_ACCESSOR_TYPE *getCurrentContext_client = NULL;
void RedFingerEGLDispatch::setContextAccessor(CONTEXT_ACCESSOR_TYPE *f) { getCurrentContext_client = f; }
#define GET_CONTEXT_client_egl RedFingerEGLDispatch* ctxxxxxxx = getCurrentContext_client() 
#endif

int RedFingerEGLDispatch::marjor_version_number = 4;
int RedFingerEGLDispatch::minor_version_number = 4;
int RedFingerEGLDispatch::build_number = 2;

RedFingerEGLDispatch::RedFingerEGLDispatch(IOStream *stream):RedFingerEGLEncoder_(stream){
	
}
RedFingerEGLDispatch::~RedFingerEGLDispatch(){

}
RedFingerEGLDispatch::RedFingerEGLDescribing::RedFingerEGLDescribing(){
	egl_describing_.clear();
	egl_client_apis_len_ = 0;
	egl_vendor_len_ = 0;
	egl_version_len_ = 0;
	egl_extensions_len_ = 0;
}
RedFingerEGLDispatch::RedFingerEGLDescribing::~RedFingerEGLDescribing(){
	egl_describing_.clear();
	egl_client_apis_len_ = 0;
	egl_vendor_len_ = 0;
	egl_version_len_ = 0;
	egl_extensions_len_ = 0;
}
RedFingerEGLDispatch::RedFingerEGLDecoder::RedFingerEGLDecoder(){
	ClearFunctionAddr();
	Init();
}
RedFingerEGLDispatch::RedFingerEGLDecoder::~RedFingerEGLDecoder(){
	ClearFunctionAddr();
}
RedFingerEGLDispatch::RedFingerEGLEncoder::RedFingerEGLEncoder(IOStream *stream):stream_(stream){
	ClearFunctionAddr();
	Init();
}
RedFingerEGLDispatch::RedFingerEGLEncoder::~RedFingerEGLEncoder(){
	ClearFunctionAddr();
}

void RedFingerEGLDispatch::RedFingerEGLDecoder::ClearFunctionAddr(){
	eglInitialize_server = NULL;
	eglCreateWindowSurface_server = NULL;
	eglCreatePbufferSurface_server = NULL;
	eglCreatePixmapSurface_server = NULL;
	eglBindAPI_server = NULL;
	eglQueryAPI_server = NULL;
	eglCreatePbufferFromClientBuffer_server = NULL;
	eglSurfaceAttrib_server = NULL;
	eglReleaseTexImage_server = NULL;
	eglWaitNative_server = NULL;
	eglCopyBuffers_server = NULL;
	eglLockSurfaceKHR_server = NULL;
	eglUnlockSurfaceKHR_server = NULL;
	eglCreateImageKHR_server = NULL;
	eglDestroyImageKHR_server = NULL;
	eglDestroySyncKHR_server = NULL;
	eglClientWaitSyncKHR_server = NULL;
	eglGetSyncAttribKHR_server = NULL;
	eglGetConfigAttrib_server = NULL;
	eglCreateContext_server = NULL;
	eglCreateSyncKHR_server = NULL;
	eglQuerySurface_server = NULL;
	eglQueryContext_server = NULL;

	eglGetError_server = NULL;
	eglGetConfigs_server = NULL;
	eglChooseConfig_server = NULL;
	eglGetDisplay_server = NULL;
	eglTerminate_server = NULL;
	eglQueryString_server = NULL;
	eglDestroySurface_server = NULL;
	eglWaitClient_server = NULL;
	eglReleaseThread_server = NULL;
	eglBindTexImage_server = NULL;
	eglSwapInterval_server = NULL;
	eglDestroyContext_server = NULL;
	eglMakeCurrent_server = NULL;
	eglGetCurrentContext_server = NULL;
	eglGetCurrentSurface_server = NULL;
	eglGetCurrentDisplay_server = NULL;
	eglSwapBuffers_server = NULL;
	eglGetProcAddress_server = NULL;
	eglSignalSyncKHR_server = NULL;
	eglWaitSyncKHR_server = NULL;
	eglGetRenderBufferANDROID_server = NULL;
	eglDupNativeFenceFDANDROID_server = NULL;
	eglRenderBufferModifiedANDROID_server = NULL;
	eglGetSystemTimeFrequencyNV_server = NULL;
	eglGetSystemTimeNV_server = NULL;
	eglHibernateProcessIMG_server = NULL;
	eglAwakenProcessIMG_server = NULL;

}
bool RedFingerEGLDispatch::RedFingerEGLDecoder::IsEGLOPCODE(void *buf, size_t len){
	if (len < 8) return false;
	unsigned char *ptr = (unsigned char *)buf;
	EGLuint opcode = GETDWORD(ptr);
	return (opcode>(EGLuint)OP_eglBegin&&opcode<(EGLuint)OP_eglEnd);
}

extern "C"{
EGLBoolean CALLRealRedFingerStaticDescribing(EGLuint buflen_state,EGLuint buflen,unsigned char* buf,EGLuint *len,EGLint name){
	GET_CONTEXT_client_egl;
	RedFingerEGLDispatch::RedFingerEGLDecoder* egl_decoder = ctxxxxxxx->GetRedFingerEGLDecoder();
	// if (RedFinger::Debug::IsDebugPrint()){
	// 	ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RealRedFingerStaticDescribing %p",__FUNCTION__,egl_decoder->GetEGLDescribing()->GetLength(name));
	// 	ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RealRedFingerStaticDescribing %s",__FUNCTION__,egl_decoder->GetEGLDescribing()->GetEGLString(name));
	// }
	if (!buflen_state){
		WriteEGLuint(egl_decoder->GetEGLDescribing()->GetLength(name),(unsigned char*)len);
	}
	else{
		memmove(buf,egl_decoder->GetEGLDescribing()->GetEGLString(name),egl_decoder->GetEGLDescribing()->GetLength(name));
		WriteEGLuint(egl_decoder->GetEGLDescribing()->GetLength(name),(unsigned char*)len);
	}
	return EGL_TRUE;
}
EGLBoolean CALLRealEGLInitialize(EGLDisplay display,EGLint* major,EGLint* minor){
	GET_CONTEXT_client_egl;
	RedFingerEGLDispatch::RedFingerEGLDecoder* egl_decoder = ctxxxxxxx->GetRedFingerEGLDecoder();
	EGLBoolean retval = egl_decoder->eglInitialize_server(display, major, minor);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglInitialize %p:arg1 %p:arg2 %p:arg3 %p:retval %p",__FUNCTION__,
			egl_decoder->eglInitialize_server,display,*major,*minor,retval);
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglQueryString %s",__FUNCTION__,egl_decoder->eglQueryString_server(display,EGL_CLIENT_APIS));
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglQueryString %s",__FUNCTION__,egl_decoder->eglQueryString_server(display,EGL_VENDOR));
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglQueryString %s",__FUNCTION__,egl_decoder->eglQueryString_server(display,EGL_VERSION));
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglQueryString %s",__FUNCTION__,egl_decoder->eglQueryString_server(display,EGL_EXTENSIONS));
	}
	egl_decoder->GetEGLDescribing()->AddEGLString(EGL_CLIENT_APIS,egl_decoder->eglQueryString_server(display,EGL_CLIENT_APIS));
	egl_decoder->GetEGLDescribing()->AddEGLString(EGL_VENDOR,egl_decoder->eglQueryString_server(display,EGL_VENDOR));
	egl_decoder->GetEGLDescribing()->AddEGLString(EGL_VERSION,egl_decoder->eglQueryString_server(display,EGL_VERSION));
	egl_decoder->GetEGLDescribing()->AddEGLString(EGL_EXTENSIONS,egl_decoder->eglQueryString_server(display,EGL_EXTENSIONS));
	return retval;
}
EGLSurface CALLRealEGLCreateWindowSurface(EGLDisplay display,EGLConfig config,NativeWindowType native_window,EGLint const * attrib_list){
	GET_CONTEXT_client_egl;
	EGLSurface retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateWindowSurface_server(display, config, native_window, attrib_list);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateWindowSurface %p:arg1 %p:arg2 %p:arg3 %u:arg4 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateWindowSurface_server,display,config,native_window,attrib_list,retval);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateWindowSurface %p:index %u<len %u:arg4 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateWindowSurface_server,i,__size_attrib_list,attrib_list[i]);
		}
	}
	return retval;
}
EGLSurface CALLRealEGLCreatePbufferSurface(EGLDisplay display,EGLConfig config,EGLint const * attrib_list){
	GET_CONTEXT_client_egl;
	EGLSurface retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePbufferSurface_server(display, config, attrib_list);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreatePbufferSurface %p:arg1 %p:arg2 %p:arg3 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePbufferSurface_server,display,config,retval);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreatePbufferSurface %p:index %u<len %u:arg3 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePbufferSurface_server,i,__size_attrib_list,attrib_list[i]);
		}
	}
	return retval;
}
EGLSurface CALLRealEGLCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	EGLSurface retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePixmapSurface_server(dpy, config, pixmap, attrib_list);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreatePixmapSurface %p:arg1 %p:arg2 %p:arg3 %u:arg4 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePixmapSurface_server,dpy,config,pixmap,attrib_list,retval);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreatePixmapSurface %p:index %u<len %u:arg4 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePixmapSurface_server,i,__size_attrib_list,attrib_list[i]);
		}
	}
	return retval;
}
EGLBoolean CALLRealEGLBindAPI(EGLenum api){
	GET_CONTEXT_client_egl;
	EGLBoolean retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglBindAPI_server(api);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglBindAPI %p:arg1 %u:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglBindAPI_server,api,retval);
	}
	return retval;
}
EGLenum CALLRealEGLQueryAPI(){
	GET_CONTEXT_client_egl;
	EGLenum retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglQueryAPI_server();
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglQueryAPI %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglQueryAPI_server,retval);
	}
	return retval;
}
EGLSurface CALLRealEGLCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreatePbufferFromClientBuffer_server(dpy,buftype,buffer,config,attrib_list);
}
EGLBoolean CALLRealEGLSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value){
	GET_CONTEXT_client_egl;
	EGLBoolean retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglSurfaceAttrib_server(dpy,surface,attribute,value);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglSurfaceAttrib %p:arg1 %p:arg2 %p:arg3 %u:arg4 %u:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglSurfaceAttrib_server,dpy,surface,attribute,value,retval);
	}
	return retval;
}
EGLBoolean CALLRealEGLReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglReleaseTexImage_server(dpy,surface,buffer);
}
EGLBoolean CALLRealEGLWaitNative(EGLint engine){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglWaitNative_server(engine);
}
EGLBoolean CALLRealEGLCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglCopyBuffers_server(dpy,surface,target);
}
EGLBoolean CALLRealEGLLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglLockSurfaceKHR_server(display,surface,attrib_list);
}
EGLBoolean CALLRealEGLUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglUnlockSurfaceKHR_server(display,surface);
}
EGLImageKHR CALLRealEGLCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	EGLImageKHR retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateImageKHR_server(dpy,ctx,target,buffer,attrib_list);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateImageKHR %p:arg1 %p:arg2 %p:arg3 %u:arg4 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglBindAPI_server,dpy,ctx,target,buffer,retval);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateImageKHR %p:index %u<len %u:arg5 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglBindAPI_server,i,__size_attrib_list,attrib_list[i]);
		}
	}
	return retval;
}
EGLBoolean CALLRealEGLDestroyImageKHR(EGLDisplay dpy, EGLImageKHR img){
	GET_CONTEXT_client_egl;
	EGLBoolean retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglDestroyImageKHR_server(dpy,img);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglDestroyImageKHR %p:arg1 %p:arg2 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglDestroyImageKHR_server,dpy,img,retval);
	}
	return retval;
}	
EGLBoolean CALLRealEGLDestroySyncKHR(EGLDisplay dpy, EGLSyncKHR sync){
	GET_CONTEXT_client_egl;
	EGLBoolean retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglDestroySyncKHR_server(dpy,sync);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglDestroySyncKHR %p:arg1 %p:arg2 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglDestroySyncKHR_server,dpy,sync,retval);
	}
	return retval;
}
EGLint CALLRealEGLClientWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout){
	GET_CONTEXT_client_egl;
	EGLint retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglClientWaitSyncKHR_server(dpy,sync,flags,timeout);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglClientWaitSyncKHR %p:arg1 %p:arg2 %p:arg3 %u:arg4 %lld:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglClientWaitSyncKHR_server,dpy,sync,flags,timeout,retval);
	}
	return retval;
}
EGLBoolean CALLRealEGLGetSyncAttribKHR(EGLDisplay dpy, EGLSyncKHR sync,EGLint attribute, EGLint *value){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetSyncAttribKHR_server(dpy,sync,attribute,value);
}
EGLBoolean CALLRealEGLGetConfigAttrib(EGLDisplay display,EGLConfig config,EGLint attribute,EGLint* value){
	GET_CONTEXT_client_egl;
	EGLBoolean retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetConfigAttrib_server(display,config,attribute,value);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglGetConfigAttrib %p:arg1 %p:arg2 %p:arg3 %u:arg4 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglClientWaitSyncKHR_server,display,config,attribute,*value,retval);
	}
	return retval;
}
EGLContext CALLRealEGLCreateContext(EGLDisplay display,EGLConfig config,EGLContext share_context,const EGLint * attrib_list){
	GET_CONTEXT_client_egl;
	EGLContext retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateContext_server(display,config,share_context,attrib_list);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateContext %p:arg1 %p:arg2 %p:arg3 %p:arg4 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateContext_server,display,config,share_context,attrib_list,retval);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateContext %p:index %u<len %u:arg4 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateContext_server,i,__size_attrib_list,attrib_list[i]);
		}
	}
	return retval;
}
EGLSyncKHR CALLRealEGLCreateSyncKHR(EGLDisplay dpy, EGLenum type, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	EGLSyncKHR retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateSyncKHR_server(dpy,type,attrib_list);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateSyncKHR %p:arg1 %p:arg2 %p:arg3 %p:retval %p",__FUNCTION__,
			ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateSyncKHR_server,dpy,type,attrib_list,retval);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglCreateSyncKHR %p:index %u<len %u:arg3 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglCreateSyncKHR_server,i,__size_attrib_list,attrib_list[i]);
		}
	}
	return retval;
}
EGLBoolean CALLRealEGLQuerySurface(EGLDisplay display,EGLSurface surface,EGLint attribute,EGLint* value){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglQuerySurface_server(display,surface,attribute,value);
}
EGLBoolean CALLRealEGLQueryContext(EGLDisplay display,EGLContext context,EGLint attribute,EGLint* value){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglQueryContext_server(display,context,attribute,value);
}
EGLint CallRealEGLGetError(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetError_server();
}
EGLBoolean CallRealEGLGetConfigs(EGLDisplay display,EGLConfig* configs,EGLint config_size,EGLint* num_config){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetConfigs_server(display,configs,config_size,num_config);
}
EGLBoolean CallRealEGLChooseConfig(EGLDisplay display,const EGLint* attrib_list,EGLConfig * configs,EGLint config_size,EGLint * num_config){
	GET_CONTEXT_client_egl;
	EGLBoolean retval = ctxxxxxxx->GetRedFingerEGLDecoder()->eglChooseConfig_server(display,attrib_list,configs,config_size,num_config);
	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglChooseConfig:arg1 %p:arg2 %p:arg3 %p:arg4 %p:arg5 %p",__FUNCTION__,
			display,attrib_list,configs,config_size,num_config);
		const EGLuint __size_attrib_list = RedFingerEGLDispatch::GetAttribLen(attrib_list);
		for (EGLuint i = 0; i < __size_attrib_list; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglChooseConfig %p:index %p<len %p:arg2 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglChooseConfig_server,i,__size_attrib_list,attrib_list[i]);
		}
		for (EGLuint i = 0; i < config_size; i++)
		{
			ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:eglChooseConfig %p:index %p<len %p:arg3 %p",__FUNCTION__,
				ctxxxxxxx->GetRedFingerEGLDecoder()->eglChooseConfig_server,i,config_size,(EGLuint)configs[i]);
		}
	}
	return retval;
}
EGLDisplay CallRealEGLGetDisplay(EGLNativeDisplayType display_id){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetDisplay_server(display_id);
}
EGLBoolean CallRealEGLTerminate(EGLDisplay dpy){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglTerminate_server(dpy);
}
const char* CallRealEGLQueryString(EGLDisplay dpy, EGLint name){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglQueryString_server(dpy, name);
}
EGLBoolean CallRealEGLDestroySurface(EGLDisplay dpy, EGLSurface surface){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglDestroySurface_server(dpy, surface);
}
EGLBoolean CallRealEGLWaitClient(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglWaitClient_server();
}
EGLBoolean CallRealEGLReleaseThread(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglReleaseThread_server();
}
EGLBoolean CallRealEGLBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglBindTexImage_server(dpy, surface, buffer);
}
EGLBoolean CallRealEGLSwapInterval(EGLDisplay dpy, EGLint interval){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglSwapInterval_server(dpy, interval);
}
EGLBoolean CallRealEGLDestroyContext(EGLDisplay dpy, EGLContext ctx){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglDestroyContext_server(dpy, ctx);
}
EGLBoolean CallRealEGLMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglMakeCurrent_server(dpy, draw, read, ctx);
}
EGLContext CallRealEGLGetCurrentContext(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetCurrentContext_server();
}
EGLSurface CallRealEGLGetCurrentSurface(EGLint readdraw){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetCurrentSurface_server(readdraw);
}
EGLDisplay CallRealEGLGetCurrentDisplay(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetCurrentDisplay_server();
}
EGLBoolean CallRealEGLSwapBuffers(EGLDisplay dpy, EGLSurface surface){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglSwapBuffers_server(dpy,surface);
}
__eglMustCastToProperFunctionPointerType CallRealEGLGetProcAddress(const char *procname){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetProcAddress_server(procname);
}
EGLBoolean CallRealEGLSignalSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglSignalSyncKHR_server(dpy,sync,mode);
}
EGLint CallRealEGLWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglWaitSyncKHR_server(dpy,sync,flags);
}
EGLClientBuffer CallRealEGLGetRenderBufferANDROID(EGLDisplay dpy, EGLSurface draw){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetRenderBufferANDROID_server(dpy,draw);
}
EGLint CallRealEGLDupNativeFenceFDANDROID(EGLDisplay dpy, EGLSyncKHR sync){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglDupNativeFenceFDANDROID_server(dpy,sync);
}
EGLBoolean CallRealEGLRenderBufferModifiedANDROID(EGLDisplay dpy, EGLSurface draw){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglRenderBufferModifiedANDROID_server(dpy,draw);
}
EGLuint64NV CallRealEGLGetSystemTimeFrequencyNV(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetSystemTimeFrequencyNV_server();
}
EGLuint64NV CallRealEGLGetSystemTimeNV(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglGetSystemTimeNV_server();
}
EGLBoolean CallRealEGLHibernateProcessIMG(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglHibernateProcessIMG_server();
}
EGLBoolean CallRealEGLAwakenProcessIMG(){
	GET_CONTEXT_client_egl;
	return ctxxxxxxx->GetRedFingerEGLDecoder()->eglAwakenProcessIMG_server();
}

}
size_t RedFingerEGLDispatch::RedFingerEGLDecoder::decode(void *buf, size_t len, IOStream *stream){
	size_t pos = 0;
	if (len < (sizeof(EGLuint) * 2)) return pos; 
	unsigned char *ptr = (unsigned char *)buf;
	bool unknownOpcode = false; 
#ifdef CHECK_GL_ERROR 
	char lastCall[256] = {0}; 
#endif 
	while ((len - pos >= (sizeof(EGLuint) * 2)) && !unknownOpcode) {  
		EGLuint opcode = GETDWORD(ptr);  
		EGLuint packetLen = GETDWORD(ptr + sizeof(EGLuint));
		const EGLuint sb = (sizeof(EGLuint) * 2);
		if (len - pos < packetLen) return pos; 
		switch(opcode) {
			case OP_RedFingerStaticEescribing:{
				const EGLuint buflen_state = ReadEGLuint(ptr + sb);
				const EGLuint buflen = ReadEGLuint(ptr + sb + sizeof(EGLuint));
				const EGLuint name = ReadEGLuint(ptr + sb + sizeof(EGLuint) + sizeof(EGLuint));
				// if (RedFinger::Debug::IsDebugPrint()){
				// 	ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:OP_RedFingerStaticEescribing:buflen_state %p:buflen %p:name %p:packetLen %p",
				// 		__FUNCTION__,buflen_state,buflen,name,packetLen);
				// }
				size_t totalTmpSize = sizeof(EGLBoolean) + sizeof(EGLuint) + buflen;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				unsigned char *tmpPtr4 = &tmpBuf[sizeof(EGLuint)];
				unsigned char *tmpReturnPtr = &tmpBuf[0 + sizeof(EGLint) + buflen];
				WriteEGLBoolean(CALLRealRedFingerStaticDescribing(buflen_state,buflen,tmpPtr4,(EGLuint*)tmpPtr3,name),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglInitialize:
			{
				EGLuint tmpPtr3Size = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) );
				EGLuint tmpPtr4Size = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLint*));
				size_t totalTmpSize = sizeof(EGLBoolean) + tmpPtr3Size;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				memset(tmpPtr3, 0, tmpPtr3Size);
				unsigned char *tmpPtr4 = &tmpBuf[sizeof(EGLint*)];
				memset(tmpPtr4, 0, tmpPtr4Size);
				unsigned char *tmpReturnPtr = &tmpBuf[0 + tmpPtr3Size + tmpPtr4Size];
				WriteEGLBoolean(CALLRealEGLInitialize(ReadEGLDisplay(ptr + sb), 
								(EGLint*)(tmpPtr3Size == 0 ? NULL : (GLsizei*)(tmpPtr3)),
								(EGLint*)(tmpPtr4Size == 0 ? NULL : (GLsizei*)(tmpPtr4))),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglCreateWindowSurface:
			{
				size_t totalTmpSize = sizeof(EGLSurface);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(NativeWindowType));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(NativeWindowType) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLSurface(CALLRealEGLCreateWindowSurface(ReadEGLDisplay(ptr + sb), 
								ReadEGLConfig(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLNativeWindowType(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglCreatePbufferSurface:
			{
				size_t totalTmpSize = sizeof(EGLSurface);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLSurface(CALLRealEGLCreatePbufferSurface(ReadEGLDisplay(ptr + sb), 
								ReadEGLConfig(ptr + sb + sizeof(EGLDisplay)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglCreatePixmapSurface:
			{
				size_t totalTmpSize = sizeof(EGLSurface);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLNativePixmapType));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLNativePixmapType) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLSurface(CALLRealEGLCreatePixmapSurface(ReadEGLDisplay(ptr + sb), 
								ReadEGLConfig(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLNativePixmapType(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglBindAPI:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLBindAPI(ReadEGLint(ptr + sb)),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglQueryAPI:
			{
				size_t totalTmpSize = sizeof(EGLenum);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLenum(CALLRealEGLQueryAPI(),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglCreatePbufferFromClientBuffer:
			{
				size_t totalTmpSize = sizeof(EGLSurface);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLenum) + sizeof(EGLClientBuffer) + sizeof(EGLConfig));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLenum) + sizeof(EGLClientBuffer) + sizeof(EGLConfig) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLSurface(CALLRealEGLCreatePbufferFromClientBuffer(ReadEGLDisplay(ptr + sb), 
								ReadEGLenum(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLClientBuffer(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLenum)), 
								ReadEGLConfig(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLenum) + sizeof(EGLClientBuffer)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglSurfaceAttrib:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLSurfaceAttrib(ReadEGLDisplay(ptr + sb), 
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLint))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglReleaseTexImage:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLReleaseTexImage(ReadEGLDisplay(ptr + sb), 
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglWaitNative:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLWaitNative(ReadEGLint(ptr + sb)),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglCopyBuffers:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLCopyBuffers(ReadEGLDisplay(ptr + sb), 
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLNativePixmapType(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglLockSurfaceKHR:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLBoolean(CALLRealEGLLockSurfaceKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglUnlockSurfaceKHR:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLUnlockSurfaceKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglCreateImageKHR:
			{
				size_t totalTmpSize = sizeof(EGLImageKHR);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLContext) + sizeof(EGLenum) + sizeof(EGLClientBuffer));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLContext) + sizeof(EGLenum) + sizeof(EGLClientBuffer) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLImageKHR(CALLRealEGLCreateImageKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLContext(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLenum(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLContext)), 
								ReadEGLClientBuffer(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLContext) + sizeof(EGLenum)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglDestroyImageKHR:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLDestroyImageKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLImageKHR(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglDestroySyncKHR:
			{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CALLRealEGLDestroySyncKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLSyncKHR(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglClientWaitSyncKHR:
			{
				size_t totalTmpSize = sizeof(EGLint);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLint(CALLRealEGLClientWaitSyncKHR(ReadEGLDisplay(ptr + sb), 
							ReadEGLSyncKHR(ptr + sb + sizeof(EGLDisplay)), 
							ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSyncKHR)), 
							ReadEGLTimeKHR(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + sizeof(EGLint))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglGetSyncAttribKHR:
			{
				EGLuint tmpPtr3Size = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + sizeof(EGLint));
				size_t totalTmpSize = sizeof(EGLBoolean) + tmpPtr3Size;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				memset(tmpPtr3, 0, tmpPtr3Size);
				unsigned char *tmpReturnPtr = &tmpBuf[0 + tmpPtr3Size];
				WriteEGLBoolean(CALLRealEGLGetSyncAttribKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLSyncKHR(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSyncKHR)), 
								(EGLint*)(tmpPtr3Size == 0 ? NULL : (GLsizei*)(tmpPtr3))),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglGetConfigAttrib:
			{
				EGLuint tmpPtr3Size = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLint));
				size_t totalTmpSize = sizeof(EGLBoolean) + tmpPtr3Size;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				memset(tmpPtr3, 0, tmpPtr3Size);
				unsigned char *tmpReturnPtr = &tmpBuf[0 + tmpPtr3Size];
				WriteEGLBoolean(CALLRealEGLGetConfigAttrib(ReadEGLDisplay(ptr + sb), 
								ReadEGLConfig(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig)), 
								(EGLint*)(tmpPtr3Size == 0 ? NULL : (GLsizei*)(tmpPtr3))),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglCreateContext:
			{
				size_t totalTmpSize = sizeof(EGLContext);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLContext));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLContext) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLContext(CALLRealEGLCreateContext(ReadEGLDisplay(ptr + sb), 
								ReadEGLConfig(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLContext(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLConfig)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglCreateSyncKHR:
			{
				size_t totalTmpSize = sizeof(EGLSyncKHR);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				EGLuint __size_attrib_list = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLenum));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLenum) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				WriteEGLSyncKHR(CALLRealEGLCreateSyncKHR(ReadEGLDisplay(ptr + sb), 
								ReadEGLenum(ptr + sb + sizeof(EGLDisplay)), 
								alist),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglQuerySurface:
			{
				EGLuint tmpPtr3Size = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLint));
				size_t totalTmpSize = sizeof(EGLBoolean) + tmpPtr3Size;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				memset(tmpPtr3, 0, tmpPtr3Size);
				unsigned char *tmpReturnPtr = &tmpBuf[0 + tmpPtr3Size];
				WriteEGLBoolean(CALLRealEGLQuerySurface(ReadEGLDisplay(ptr + sb), 
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface)), 
								(EGLint*)(tmpPtr3Size == 0 ? NULL : (GLsizei*)(tmpPtr3))),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglQueryContext:
			{
				EGLuint tmpPtr3Size = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLContext) + sizeof(EGLint));
				size_t totalTmpSize = sizeof(EGLBoolean) + tmpPtr3Size;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				memset(tmpPtr3, 0, tmpPtr3Size);
				unsigned char *tmpReturnPtr = &tmpBuf[0 + tmpPtr3Size];
				WriteEGLBoolean(CALLRealEGLQueryContext(ReadEGLDisplay(ptr + sb), 
								ReadEGLContext(ptr + sb + sizeof(EGLDisplay)), 
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLContext)), 
								(EGLint*)(tmpPtr3Size == 0 ? NULL : (GLsizei*)(tmpPtr3))),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglGetError:{
				size_t totalTmpSize = sizeof(EGLint);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLint(CallRealEGLGetError(),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglGetDisplay:{
				size_t totalTmpSize = sizeof(EGLDisplay);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLDisplay(CallRealEGLGetDisplay(ReadEGLNativeDisplayType(ptr + sb)),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglTerminate:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLTerminate(ReadEGLDisplay(ptr + sb)),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglDestroySurface:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLDestroySurface(ReadEGLDisplay(ptr + sb),ReadEGLSurface(ptr + sb + sizeof(EGLSurface))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglWaitClient:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLWaitClient(),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglReleaseThread:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLReleaseThread(),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglBindTexImage:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLBindTexImage(ReadEGLDisplay(ptr + sb),
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)),
								ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglSwapInterval:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLSwapInterval(ReadEGLDisplay(ptr + sb),
								ReadEGLint(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglDestroyContext:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLDestroyContext(ReadEGLDisplay(ptr + sb),
								ReadEGLContext(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglMakeCurrent:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLMakeCurrent(ReadEGLDisplay(ptr + sb),
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay)),
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface)),
								ReadEGLContext(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLSurface))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglGetCurrentContext:{
				size_t totalTmpSize = sizeof(EGLContext);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLContext(CallRealEGLGetCurrentContext(),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglGetCurrentSurface:{
				size_t totalTmpSize = sizeof(EGLSurface);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLSurface(CallRealEGLGetCurrentSurface(ReadEGLint(ptr + sb)),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglGetCurrentDisplay:{
				size_t totalTmpSize = sizeof(EGLDisplay);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLDisplay(CallRealEGLGetCurrentDisplay(),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglSwapBuffers:{
				size_t totalTmpSize = sizeof(EGLBoolean);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLBoolean(CallRealEGLSwapBuffers(ReadEGLDisplay(ptr + sb),
								ReadEGLSurface(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglWaitSyncKHR:{
				size_t totalTmpSize = sizeof(EGLint);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLint(CallRealEGLWaitSyncKHR(ReadEGLDisplay(ptr + sb),
							ReadEGLSyncKHR(ptr + sb + sizeof(EGLDisplay)),
							ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLSyncKHR))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}	
			case OP_eglDupNativeFenceFDANDROID:{
				size_t totalTmpSize = sizeof(EGLint);
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				WriteEGLint(CallRealEGLDupNativeFenceFDANDROID(ReadEGLDisplay(ptr + sb),
							ReadEGLSurface(ptr + sb + sizeof(EGLDisplay))),&tmpBuf[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglGetConfigs:{
				const EGLuint __size_config =     ReadEGLuint(ptr + sb + sizeof(EGLDisplay));
				const EGLint  config_size =       ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLuint));
				const EGLuint __size_num_config = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLuint) + sizeof(EGLint));
				size_t totalTmpSize = sizeof(EGLBoolean) + __size_config + __size_num_config;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				if (__size_config)
					memset(tmpPtr3, 0, __size_config);
				else
					tmpPtr3 = NULL;
				unsigned char *tmpPtr4 = &tmpBuf[__size_config];
				if (__size_num_config)
					memset(tmpPtr4, 0, __size_num_config);
				else
					tmpPtr4 = NULL;
				unsigned char *tmpReturnPtr = &tmpBuf[0 + __size_config + __size_num_config];
				WriteEGLBoolean(CallRealEGLGetConfigs(ReadEGLDisplay(ptr + sb), (EGLConfig*)tmpPtr3,
								config_size, (EGLint*)tmpPtr4),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			case OP_eglChooseConfig:{
				EGLuint __size_attrib_list = (ReadEGLuint(ptr + sb + sizeof(EGLDisplay)) * sizeof(EGLuint));
				EGLint* attrib_list = (EGLint*)(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLuint));
				if (!__size_attrib_list){
					attrib_list = NULL;
				}
				const EGLint* alist = (const EGLint*)attrib_list;
				const EGLuint __size_config =     ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLuint) + __size_attrib_list);
				const EGLint  config_size =       ReadEGLint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLuint) + __size_attrib_list + sizeof(EGLuint));
				const EGLuint __size_num_config = ReadEGLuint(ptr + sb + sizeof(EGLDisplay) + sizeof(EGLuint) + __size_attrib_list + sizeof(EGLuint) + sizeof(EGLint));
				size_t totalTmpSize = sizeof(EGLBoolean) + __size_config + __size_num_config;
				unsigned char *tmpBuf = stream->alloc(totalTmpSize);
				unsigned char *tmpPtr3 = &tmpBuf[0];
				if (__size_config)
					memset(tmpPtr3, 0, __size_config);
				else
					tmpPtr3 = NULL;
				unsigned char *tmpPtr4 = &tmpBuf[__size_config];
				if (__size_num_config)
					memset(tmpPtr4, 0, __size_num_config);
				else
					tmpPtr4 = NULL;
				unsigned char *tmpReturnPtr = &tmpBuf[0 + __size_config + __size_num_config];
				WriteEGLBoolean(CallRealEGLChooseConfig(ReadEGLDisplay(ptr + sb),alist, (EGLConfig*)tmpPtr3, 
								config_size, (EGLint*)tmpPtr4),&tmpReturnPtr[0]);
				stream->writeback();
				pos += GETDWORD(ptr + 4);
				ptr += GETDWORD(ptr + 4);
				break;
			}
			default:
			unknownOpcode = true;
			break;
		}
	}
	return pos;
}
void RedFingerEGLDispatch::RedFingerEGLDecoder::Init(){
	static const char* kHardwareGLESLibrary = "/system/vendor/lib/egl/rk3288/libGLES_mali.so.bak";
  void *gles_android = dlopen(kHardwareGLESLibrary, RTLD_NOW | RTLD_LOCAL);
  eglInitialize_server =  (eglInitialize_server_proc_t)dlsym(gles_android,"eglInitialize");
  eglCreateWindowSurface_server =  (eglCreateWindowSurface_server_proc_t)dlsym(gles_android,"eglCreateWindowSurface");
  eglCreatePbufferSurface_server =  (eglCreatePbufferSurface_server_proc_t)dlsym(gles_android,"eglCreatePbufferSurface");
  eglCreatePixmapSurface_server =  (eglCreatePixmapSurface_server_proc_t)dlsym(gles_android,"eglCreatePixmapSurface");
	eglBindAPI_server =  (eglBindAPI_server_proc_t)dlsym(gles_android,"eglBindAPI");
	eglQueryAPI_server =  (eglQueryAPI_server_proc_t)dlsym(gles_android,"eglQueryAPI");
	eglCreatePbufferFromClientBuffer_server =  (eglCreatePbufferFromClientBuffer_server_proc_t)dlsym(gles_android,"eglCreatePbufferFromClientBuffer");
	eglSurfaceAttrib_server =  (eglSurfaceAttrib_server_proc_t)dlsym(gles_android,"eglSurfaceAttrib");
	eglReleaseTexImage_server =  (eglReleaseTexImage_server_proc_t)dlsym(gles_android,"eglReleaseTexImage");
	eglWaitNative_server =  (eglWaitNative_server_proc_t)dlsym(gles_android,"eglWaitNative");
	eglCopyBuffers_server =  (eglCopyBuffers_server_proc_t)dlsym(gles_android,"eglCopyBuffers");
	eglLockSurfaceKHR_server =  (eglLockSurfaceKHR_server_proc_t)dlsym(gles_android,"eglLockSurfaceKHR");
	eglUnlockSurfaceKHR_server =  (eglUnlockSurfaceKHR_server_proc_t)dlsym(gles_android,"eglUnlockSurfaceKHR");
	eglCreateImageKHR_server =  (eglCreateImageKHR_server_proc_t)dlsym(gles_android,"eglCreateImageKHR");
	eglDestroyImageKHR_server =  (eglDestroyImageKHR_server_proc_t)dlsym(gles_android,"eglDestroyImageKHR");
	eglDestroySyncKHR_server =  (eglDestroySyncKHR_server_proc_t)dlsym(gles_android,"eglDestroySyncKHR");
	eglClientWaitSyncKHR_server =  (eglClientWaitSyncKHR_server_proc_t)dlsym(gles_android,"eglClientWaitSyncKHR");
	eglGetSyncAttribKHR_server =  (eglGetSyncAttribKHR_server_proc_t)dlsym(gles_android,"eglGetSyncAttribKHR");
	eglGetConfigAttrib_server =  (eglGetConfigAttrib_server_proc_t)dlsym(gles_android,"eglGetConfigAttrib");
	eglCreateContext_server =  (eglCreateContext_server_proc_t)dlsym(gles_android,"eglCreateContext");
	eglCreateSyncKHR_server =  (eglCreateSyncKHR_server_proc_t)dlsym(gles_android,"eglCreateSyncKHR");
	eglQuerySurface_server =  (eglQuerySurface_server_proc_t)dlsym(gles_android,"eglQuerySurface");
	eglQueryContext_server =  (eglQueryContext_server_proc_t)dlsym(gles_android,"eglQueryContext");

	eglGetError_server =  (eglGetError_server_proc_t)dlsym(gles_android,"eglGetError");
	eglGetConfigs_server = (eglGetConfigs_server_proc_t)dlsym(gles_android,"eglGetConfigs");
	eglChooseConfig_server = (eglChooseConfig_server_proc_t)dlsym(gles_android,"eglChooseConfig");
	eglGetDisplay_server =  (eglGetDisplay_server_proc_t)dlsym(gles_android,"eglGetDisplay");
	eglTerminate_server =  (eglTerminate_server_proc_t)dlsym(gles_android,"eglTerminate");
	eglQueryString_server =  (eglQueryString_server_proc_t)dlsym(gles_android,"eglQueryString");
	eglDestroySurface_server =  (eglDestroySurface_server_proc_t)dlsym(gles_android,"eglDestroySurface");
	eglWaitClient_server =  (eglWaitClient_server_proc_t)dlsym(gles_android,"eglWaitClient");
	eglReleaseThread_server =  (eglReleaseThread_server_proc_t)dlsym(gles_android,"eglReleaseThread");
	eglBindTexImage_server =  (eglBindTexImage_server_proc_t)dlsym(gles_android,"eglBindTexImage");
	eglSwapInterval_server =  (eglSwapInterval_server_proc_t)dlsym(gles_android,"eglSwapInterval");
	eglDestroyContext_server =  (eglDestroyContext_server_proc_t)dlsym(gles_android,"eglDestroyContext");
	eglMakeCurrent_server =  (eglMakeCurrent_server_proc_t)dlsym(gles_android,"eglMakeCurrent");
	eglGetCurrentContext_server =  (eglGetCurrentContext_server_proc_t)dlsym(gles_android,"eglGetCurrentContext");
	eglGetCurrentSurface_server =  (eglGetCurrentSurface_server_proc_t)dlsym(gles_android,"eglGetCurrentSurface");
	eglGetCurrentDisplay_server =  (eglGetCurrentDisplay_server_proc_t)dlsym(gles_android,"eglGetCurrentDisplay");
	eglSwapBuffers_server =  (eglSwapBuffers_server_proc_t)dlsym(gles_android,"eglSwapBuffers");
	eglGetProcAddress_server =  (eglGetProcAddress_server_proc_t)dlsym(gles_android,"eglGetProcAddress");
	eglSignalSyncKHR_server =  (eglSignalSyncKHR_server_proc_t)dlsym(gles_android,"eglSignalSyncKHR");
	eglWaitSyncKHR_server =  (eglWaitSyncKHR_server_proc_t)dlsym(gles_android,"eglWaitSyncKHR");
    if(!eglWaitSyncKHR_server){
        eglWaitSyncKHR_server = (eglWaitSyncKHR_server_proc_t)eglGetProcAddress_server("eglWaitSyncKHR");
    }
	eglGetRenderBufferANDROID_server =  (eglGetRenderBufferANDROID_server_proc_t)dlsym(gles_android,"eglGetRenderBufferANDROID");
    if(!eglGetRenderBufferANDROID_server){
        eglGetRenderBufferANDROID_server = (eglGetRenderBufferANDROID_server_proc_t)eglGetProcAddress_server("eglGetRenderBufferANDROID");
    }
	eglDupNativeFenceFDANDROID_server =  (eglDupNativeFenceFDANDROID_server_proc_t)dlsym(gles_android,"eglDupNativeFenceFDANDROID");
    if(!eglDupNativeFenceFDANDROID_server){
        eglDupNativeFenceFDANDROID_server = (eglDupNativeFenceFDANDROID_server_proc_t)eglGetProcAddress_server("eglDupNativeFenceFDANDROID");
    }
	eglRenderBufferModifiedANDROID_server =  (eglRenderBufferModifiedANDROID_server_proc_t)dlsym(gles_android,"eglRenderBufferModifiedANDROID");
    if(!eglRenderBufferModifiedANDROID_server){
        eglRenderBufferModifiedANDROID_server = (eglRenderBufferModifiedANDROID_server_proc_t)eglGetProcAddress_server("eglDupNativeFenceFDANDROID");
    }
	eglGetSystemTimeFrequencyNV_server =  (eglGetSystemTimeFrequencyNV_server_proc_t)dlsym(gles_android,"eglGetSystemTimeFrequencyNV");
    if(!eglGetSystemTimeFrequencyNV_server){
        eglGetSystemTimeFrequencyNV_server = (eglGetSystemTimeFrequencyNV_server_proc_t)eglGetProcAddress_server("eglGetSystemTimeFrequencyNV");
    }
	eglGetSystemTimeNV_server =  (eglGetSystemTimeNV_server_proc_t)dlsym(gles_android,"eglGetSystemTimeNV");
    if(!eglGetSystemTimeNV_server){
        eglGetSystemTimeNV_server = (eglGetSystemTimeNV_server_proc_t)eglGetProcAddress_server("eglGetSystemTimeNV");
    }
	eglHibernateProcessIMG_server =  (eglHibernateProcessIMG_server_proc_t)dlsym(gles_android,"eglHibernateProcessIMG");
    if(!eglHibernateProcessIMG_server){
        eglHibernateProcessIMG_server = (eglHibernateProcessIMG_server_proc_t)eglGetProcAddress_server("eglHibernateProcessIMG");
    }
	eglAwakenProcessIMG_server =  (eglAwakenProcessIMG_server_proc_t)dlsym(gles_android,"eglAwakenProcessIMG");
    if(!eglAwakenProcessIMG_server){
        eglAwakenProcessIMG_server = (eglAwakenProcessIMG_server_proc_t)eglGetProcAddress_server("eglAwakenProcessIMG");
    }
}

void RedFingerEGLDispatch::RedFingerEGLEncoder::ClearFunctionAddr(){
	RedFingerStaticDescribing_client = NULL;
	eglInitialize_client = NULL;
	eglCreateWindowSurface_client =  NULL;
	eglCreatePbufferSurface_client =  NULL;
	eglCreatePixmapSurface_client =  NULL;
	eglBindAPI_client =  NULL;
	eglQueryAPI_client =  NULL;
	eglCreatePbufferFromClientBuffer_client =  NULL;
	eglSurfaceAttrib_client =  NULL;
	eglReleaseTexImage_client =  NULL;
	eglWaitNative_client =  NULL;
	eglCopyBuffers_client =  NULL;
	eglLockSurfaceKHR_client =  NULL;
	eglUnlockSurfaceKHR_client =  NULL;
	eglCreateImageKHR_client =  NULL;
	eglDestroyImageKHR_client =  NULL;
	eglDestroySyncKHR_client =  NULL;
	eglClientWaitSyncKHR_client =  NULL;
	eglGetSyncAttribKHR_client =  NULL;
	eglGetConfigAttrib_client =  NULL;
	eglCreateContext_client = NULL;
	eglCreateSyncKHR_client = NULL;
	eglQuerySurface_client = NULL;
	eglQueryContext_client = NULL;

	eglGetError_client = NULL;
	eglGetConfigs_client = NULL;
	eglChooseConfig_client = NULL;
	eglGetDisplay_client = NULL;
	eglTerminate_client = NULL;
	eglQueryString_client = NULL;
	eglDestroySurface_client = NULL;
	eglWaitClient_client = NULL;
	eglReleaseThread_client = NULL;
	eglBindTexImage_client = NULL;
	eglSwapInterval_client = NULL;
	eglDestroyContext_client = NULL;
	eglMakeCurrent_client = NULL;
	eglGetCurrentContext_client = NULL;
	eglGetCurrentSurface_client = NULL;
	eglGetCurrentDisplay_client = NULL;
	eglSwapBuffers_client = NULL;
	eglGetProcAddress_client = NULL;
	eglSignalSyncKHR_client = NULL;
	eglWaitSyncKHR_client = NULL;
	eglGetRenderBufferANDROID_client = NULL;
	eglDupNativeFenceFDANDROID_client = NULL;
	eglRenderBufferModifiedANDROID_client = NULL;
	eglGetSystemTimeFrequencyNV_client = NULL;
	eglGetSystemTimeNV_client = NULL;
	eglHibernateProcessIMG_client = NULL;
	eglAwakenProcessIMG_client = NULL;
}
void RedFingerEGLDispatch::RedFingerEGLEncoder::Init(){
	RedFingerStaticDescribing_client = s_RedFingerStaticDescribing_client;
	eglInitialize_client = s_eglInitialize_client;
	eglCreateWindowSurface_client =  s_eglCreateWindowSurface_client;
	eglCreatePbufferSurface_client =  s_eglCreatePbufferSurface_client;
	eglCreatePixmapSurface_client =  s_eglCreatePixmapSurface_client;
	eglBindAPI_client =  s_eglBindAPI_client;
	eglQueryAPI_client =  s_eglQueryAPI_client;
	eglCreatePbufferFromClientBuffer_client =  s_eglCreatePbufferFromClientBuffer_client;
	eglSurfaceAttrib_client =  s_eglSurfaceAttrib_client;
	eglReleaseTexImage_client =  s_eglReleaseTexImage_client;
	eglWaitNative_client =  s_eglWaitNative_client;
	eglCopyBuffers_client =  s_eglCopyBuffers_client;
	eglLockSurfaceKHR_client =  s_eglLockSurfaceKHR_client;
	eglUnlockSurfaceKHR_client =  s_eglUnlockSurfaceKHR_client;
	eglCreateImageKHR_client =  s_eglCreateImageKHR_client;
	eglDestroyImageKHR_client =  s_eglDestroyImageKHR_client;
	eglDestroySyncKHR_client =  s_eglDestroySyncKHR_client;
	eglClientWaitSyncKHR_client =  s_eglClientWaitSyncKHR_client;
	eglGetSyncAttribKHR_client =  s_eglGetSyncAttribKHR_client;
	eglGetConfigAttrib_client =  s_eglGetConfigAttrib_client;
	eglCreateContext_client = s_eglCreateContext_client;
	eglCreateSyncKHR_client = s_eglCreateSyncKHR_client;
	eglQuerySurface_client = s_eglQuerySurface_client;
	eglQueryContext_client = s_eglQueryContext_client;

	eglGetError_client = s_eglGetError_client;
	eglGetConfigs_client = s_eglGetConfigs_client;
	eglChooseConfig_client = s_eglChooseConfig_client;
	eglGetDisplay_client = s_eglGetDisplay_client;
	eglTerminate_client = s_eglTerminate_client;
	eglQueryString_client = s_eglQueryString_client;
	eglDestroySurface_client = s_eglDestroySurface_client;
	eglWaitClient_client = s_eglWaitClient_client;
	eglReleaseThread_client = s_eglReleaseThread_client;
	eglBindTexImage_client = s_eglBindTexImage_client;
	eglSwapInterval_client = s_eglSwapInterval_client;
	eglDestroyContext_client = s_eglDestroyContext_client;
	eglMakeCurrent_client = s_eglMakeCurrent_client;
	eglGetCurrentContext_client = s_eglGetCurrentContext_client;
	eglGetCurrentSurface_client = s_eglGetCurrentSurface_client;
	eglGetCurrentDisplay_client = s_eglGetCurrentDisplay_client;
	eglSwapBuffers_client = s_eglSwapBuffers_client;
	eglGetProcAddress_client = s_eglGetProcAddress_client;
	eglSignalSyncKHR_client = s_eglSignalSyncKHR_client;
	eglWaitSyncKHR_client = s_eglWaitSyncKHR_client;
	eglGetRenderBufferANDROID_client = s_eglGetRenderBufferANDROID_client;
	eglDupNativeFenceFDANDROID_client = s_eglDupNativeFenceFDANDROID_client;
	eglRenderBufferModifiedANDROID_client = s_eglRenderBufferModifiedANDROID_client;
	eglGetSystemTimeFrequencyNV_client = s_eglGetSystemTimeFrequencyNV_client;
	eglGetSystemTimeNV_client = s_eglGetSystemTimeNV_client;
	eglHibernateProcessIMG_client = s_eglHibernateProcessIMG_client;
	eglAwakenProcessIMG_client = s_eglAwakenProcessIMG_client;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_RedFingerStaticDescribing_client(void * self,char* buf,EGLuint *len,EGLint name){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (3 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_RedFingerStaticEescribing;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLuint((buf==NULL?0:1),ptr);
		ptr = WriteEGLuint(len[0],ptr);
		ptr = WriteEGLuint(name,ptr);
	// if (RedFinger::Debug::IsDebugPrint()){
	// 	ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RedFingerStaticEescribing:buflen_state %p:buflen %p:name %p:packetSize %p",
	// 		__FUNCTION__,buf,len,name);
	// }
	stream->readback(len, sizeof(EGLuint));
	if (buf){
		stream->readback(buf, len[0]);
	}
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglInitialize_client(void * self,EGLDisplay display,EGLint* major,EGLint* minor){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLint*) + sizeof(EGLint*) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	const EGLuint __size_major = ((major != NULL) ?  (sizeof(EGLint)) : 0);
	const EGLuint __size_minor = ((minor != NULL) ?  (sizeof(EGLint)) : 0);
	int tmp = OP_eglInitialize; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLint(__size_major,ptr); // EGLint
			ptr = WriteEGLint(__size_minor,ptr); // EGLint
	if (major != NULL)
		stream->readback(major, __size_major);
	if (minor != NULL)
		stream->readback(minor, __size_minor);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLSurface RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreateWindowSurface_client(void * self,EGLDisplay display,EGLConfig config,
	NativeWindowType native_window,
	EGLint const * attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(NativeWindowType) +  
		(__size_attrib_list * sizeof(EGLint)) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreateWindowSurface; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLConfig(config,ptr); // EGLConfig
			ptr = WriteEGLNativeWindowType(native_window,ptr); // NativeWindowType
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr);
	EGLSurface retval;
	stream->readback(&retval, sizeof(EGLSurface));
	return retval;
}
EGLSurface RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreatePbufferSurface_client(void * self,EGLDisplay display,EGLConfig config,
	EGLint const * attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLConfig) + (__size_attrib_list * sizeof(EGLint)) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreatePbufferSurface; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLConfig(config,ptr); // EGLConfig
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr);
	EGLSurface retval;
	stream->readback(&retval, sizeof(EGLSurface));
	return retval;
}
EGLSurface RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreatePixmapSurface_client(void * self,EGLDisplay dpy, EGLConfig config, 
	EGLNativePixmapType pixmap, const EGLint *attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLNativePixmapType) +  
		(__size_attrib_list * sizeof(EGLint)) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreatePixmapSurface; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLConfig(config,ptr); // EGLConfig
			ptr = WriteEGLNativePixmapType(pixmap,ptr); // EGLNativePixmapType
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr);
			// memcpy(ptr, &pixmap, 4); ptr += 4;
			// memcpy(ptr, &__size_attrib_list, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			// memcpy(ptr, &attrib_list, __size_attrib_list); ptr += __size_attrib_list;
	EGLSurface retval;
	stream->readback(&retval, sizeof(EGLSurface));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglBindAPI_client(void * self,EGLenum api){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLenum) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglBindAPI; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLenum(api,ptr); // EGLenum
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLenum RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglQueryAPI_client(void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglQueryAPI; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
	EGLenum retval;
	stream->readback(&retval, sizeof(EGLenum));
	return retval;
}
EGLSurface RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreatePbufferFromClientBuffer_client(void * self,EGLDisplay dpy, EGLenum buftype, 
																					EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLenum) + sizeof(EGLClientBuffer) + sizeof(EGLConfig) + 
		(__size_attrib_list * sizeof(EGLint)) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreatePbufferFromClientBuffer; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			// memcpy(ptr, &buftype, 4); ptr += 4;
			ptr = WriteEGLenum(buftype,ptr); // EGLenum
			ptr = WriteEGLClientBuffer(buffer,ptr); // EGLClientBuffer
			ptr = WriteEGLConfig(config,ptr); // EGLConfig
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr);
			// memcpy(ptr, &__size_attrib_list, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			// memcpy(ptr, &attrib_list, __size_attrib_list); ptr += __size_attrib_list;
	EGLSurface retval;
	stream->readback(&retval, sizeof(EGLSurface));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglSurfaceAttrib_client(void * self,EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLint) + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglSurfaceAttrib; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLSurface(surface, ptr); // EGLSurface
			ptr = WriteEGLint(attribute,ptr); // EGLint
			ptr = WriteEGLint(value,ptr); // EGLint
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglReleaseTexImage_client(void * self,EGLDisplay dpy, EGLSurface surface, EGLint buffer){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglReleaseTexImage; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLSurface(surface, ptr); // EGLSurface
			ptr = WriteEGLint(buffer,ptr); // EGLint
			// memcpy(ptr, &buffer, 4); ptr += 4;
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglWaitNative_client(void * self,EGLint engine){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglWaitNative; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			// memcpy(ptr, &engine, 4); ptr += 4;
			ptr = WriteEGLint(engine,ptr); // EGLint
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCopyBuffers_client(void * self,EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + 4 + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCopyBuffers; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLSurface(surface, ptr); // EGLSurface
			// memcpy(ptr, &target, 4); ptr += 4;
			ptr = WriteEGLNativePixmapType(target,ptr); // EGLint
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglLockSurfaceKHR_client(void * self,EGLDisplay display, EGLSurface surface, 
																					const EGLint *attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) +  (__size_attrib_list * sizeof(EGLint)) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglLockSurfaceKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLSurface(surface, ptr); // EGLSurface
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr);
			// memcpy(ptr, &__size_attrib_list, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			// memcpy(ptr, &attrib_list, __size_attrib_list); ptr += __size_attrib_list;
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglUnlockSurfaceKHR_client(void * self,EGLDisplay display, EGLSurface surface){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglUnlockSurfaceKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLSurface(surface, ptr); // EGLSurface
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLImageKHR RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreateImageKHR_client(void * self,EGLDisplay dpy, EGLContext ctx, EGLenum target, 
																					EGLClientBuffer buffer, const EGLint *attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLContext) + sizeof(EGLenum) + sizeof(EGLClientBuffer) + 
		 (__size_attrib_list * sizeof(EGLint)) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreateImageKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLContext(ctx,ptr); // EGLContext
			ptr = WriteEGLenum(target,ptr); // EGLenum
			ptr = WriteEGLClientBuffer(buffer,ptr); // EGLClientBuffer
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			// memcpy(ptr, &__size_attrib_list, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr); // const EGLint*
	EGLImageKHR retval;
	stream->readback(&retval, sizeof(EGLImageKHR));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglDestroyImageKHR_client(void * self,EGLDisplay dpy, EGLImageKHR img){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLImageKHR) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglDestroyImageKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLImageKHR(img,ptr); // EGLImageKHR
	GLenum retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglDestroySyncKHR_client(void * self,EGLDisplay dpy, EGLSyncKHR sync){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglDestroySyncKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLSyncKHR(sync,ptr); // EGLSyncKHR
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLint RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglClientWaitSyncKHR_client(void * self,EGLDisplay dpy, EGLSyncKHR sync, 
																				EGLint flags, EGLTimeKHR timeout){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + sizeof(EGLint) + sizeof(EGLTimeKHR) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglClientWaitSyncKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLSyncKHR(sync,ptr); // EGLSyncKHR
			ptr = WriteEGLint(flags,ptr); // EGLint
			ptr = WriteEGLTimeKHR(timeout,ptr); // EGLTimeKHR
	EGLint retval;
	stream->readback(&retval, sizeof(EGLint));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetSyncAttribKHR_client(void * self,EGLDisplay dpy, EGLSyncKHR sync,
																					EGLint attribute, EGLint *value){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + sizeof(EGLint) + sizeof(EGLint*) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	const EGLuint __size_value = ((value != NULL) ?  (sizeof(EGLint)) : 0);
	int tmp = OP_eglGetSyncAttribKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLSyncKHR(sync,ptr); // EGLSyncKHR
			ptr = WriteEGLint(attribute,ptr); // EGLint
			ptr = WriteEGLint(__size_value,ptr); // EGLint
			// memcpy(ptr, &__size_value, 4); ptr += 4;
	if (value != NULL)
		stream->readback(value, __size_value);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetConfigAttrib_client(void * self,EGLDisplay display,EGLConfig config,EGLint attribute,EGLint* value){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLint) + sizeof(EGLint*) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	const EGLuint __size_value = ((value != NULL) ?  (sizeof(EGLint)) : 0);
	int tmp = OP_eglGetConfigAttrib; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLConfig(config,ptr); // EGLConfig
			ptr = WriteEGLint(attribute,ptr); // EGLint
			ptr = WriteEGLuint(__size_value,ptr); // EGLint
			// memcpy(ptr, &__size_value, 4); ptr += 4;
	if (value != NULL)
		stream->readback(value, __size_value);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLContext RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreateContext_client(void * self,EGLDisplay display,EGLConfig config,
	EGLContext share_context,const EGLint * attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLConfig) + sizeof(EGLContext) + (__size_attrib_list * sizeof(EGLint)) + 
		(1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreateContext;
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLConfig(config,ptr); // EGLConfig
			ptr = WriteEGLContext(share_context,ptr); // EGLContext
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr); // const EGLint*
	EGLContext retval;
	stream->readback(&retval, sizeof(EGLContext));
	return retval;
}
EGLSyncKHR RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglCreateSyncKHR_client(void * self,EGLDisplay dpy, EGLenum type, const EGLint *attrib_list){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list =  RedFingerEGLDispatch::EGLAttribListLength(attrib_list);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLenum) + (__size_attrib_list * sizeof(EGLint)) + 
		(1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	int tmp = OP_eglCreateSyncKHR; 
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(dpy,ptr); // EGLDisplay
			ptr = WriteEGLenum(type,ptr); // EGLenum
			ptr = WriteEGLuint(__size_attrib_list,ptr); // EGLuint
			ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr); // const EGLint*
	EGLSyncKHR retval;
	stream->readback(&retval, sizeof(EGLSyncKHR));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglQuerySurface_client(void * self,EGLDisplay display,EGLSurface surface,
	EGLint attribute,EGLint* value){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLint) + sizeof(EGLint*) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	const EGLuint __size_value = ((value != NULL) ?  (sizeof(EGLint)) : 0);
	int tmp = OP_eglQuerySurface;
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLSurface(surface,ptr); // EGLSurface
			ptr = WriteEGLint(attribute,ptr); // EGLint
			ptr = WriteEGLint(__size_value,ptr); // EGLint
	if (value != NULL)
		stream->readback(value, __size_value);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglQueryContext_client(void * self,EGLDisplay display,EGLContext context,
	EGLint attribute,EGLint* value){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const size_t packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLContext) + sizeof(EGLint) + sizeof(EGLint*) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	const EGLuint __size_value = ((value != NULL) ?  (sizeof(EGLint)) : 0);
	int tmp = OP_eglQueryContext;
		memcpy(ptr, &tmp, sizeof(EGLuint)); ptr += sizeof(EGLuint);
		memcpy(ptr, &packetSize, sizeof(EGLuint)); ptr += sizeof(EGLuint);
			ptr = WriteEGLDisplay(display,ptr); // EGLDisplay
			ptr = WriteEGLContext(context,ptr); // EGLContext
			ptr = WriteEGLint(attribute,ptr); // EGLint
			ptr = WriteEGLint(__size_value,ptr); // EGLint
	if (value != NULL)
		stream->readback(value, __size_value);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLint RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetError_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetError;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLint retval;
	stream->readback(&retval, sizeof(EGLint));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetConfigs_client (void * self,EGLDisplay display,EGLConfig* configs,
	EGLint config_size,EGLint* num_config){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_config = (configs == NULL) ? 0 : (config_size * sizeof(EGLConfig));
	const EGLuint __size_num_config = ((num_config != NULL) ?  (sizeof(EGLint)) : 0);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLuint) + sizeof(EGLint) + sizeof(EGLint*)+ (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetConfigs;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(display,ptr);
		ptr = WriteEGLuint(__size_config,ptr);
		ptr = WriteEGLint(config_size,ptr);
		ptr = WriteEGLint(__size_num_config,ptr);
	if (configs!=NULL)
		stream->readback(configs, __size_config);
	if (num_config!=NULL)
		stream->readback(num_config, sizeof(EGLint*));
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglChooseConfig_client (void * self,EGLDisplay display,const EGLint* attrib_list,
	EGLConfig * configs,EGLint config_size,EGLint * num_config){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_attrib_list = RedFingerEGLDispatch::GetAttribLen(attrib_list);
	const EGLuint __size_config = (configs == NULL) ? 0 : (config_size * sizeof(EGLConfig));
	const EGLuint __size_num_config = ((num_config != NULL) ?  (sizeof(EGLint)) : 0);
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + (__size_attrib_list * sizeof(EGLint)) + sizeof(EGLuint) + 
		sizeof(EGLint) + sizeof(EGLint*) + (1 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglChooseConfig;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(display,ptr);
		ptr = WriteEGLuint(__size_attrib_list,ptr);
		ptr = WriteEGLintArray(attrib_list,__size_attrib_list,ptr);
		ptr = WriteEGLuint(__size_config,ptr);
		ptr = WriteEGLint(config_size,ptr);
		ptr = WriteEGLuint(__size_num_config,ptr);
	if (configs!=NULL)
		stream->readback(configs, __size_config);
	if (num_config!=NULL)
		stream->readback(num_config, sizeof(EGLint*));
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLDisplay RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetDisplay_client (void * self,EGLNativeDisplayType display_id){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLNativeDisplayType) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetDisplay;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLNativeDisplayType(display_id,ptr);
	EGLDisplay retval;
	stream->readback(&retval, sizeof(EGLDisplay));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglTerminate_client (void * self,EGLDisplay dpy){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglTerminate;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
char* RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglQueryString_client (void * self,EGLDisplay dpy, EGLint name){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglQueryString;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLint(name,ptr);
	EGLuint retval_len;
	stream->readback(&retval_len, sizeof(EGLuint));
	return NULL;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglDestroySurface_client (void * self,EGLDisplay dpy, EGLSurface surface){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglDestroySurface;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSurface(surface,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglWaitClient_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglWaitClient;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglReleaseThread_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglReleaseThread;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglBindTexImage_client (void * self,EGLDisplay dpy, EGLSurface surface, EGLint buffer){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglBindTexImage;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSurface(surface,ptr);
		ptr = WriteEGLint(buffer,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglSwapInterval_client (void * self,EGLDisplay dpy, EGLint interval){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLDisplay) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglSwapInterval;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLint(interval,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglDestroyContext_client (void * self,EGLDisplay dpy, EGLContext ctx){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLContext) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglDestroyContext;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLContext(ctx,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglMakeCurrent_client (void * self,EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + sizeof(EGLSurface) + sizeof(EGLContext) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglMakeCurrent;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSurface(draw,ptr);
		ptr = WriteEGLSurface(read,ptr);
		ptr = WriteEGLContext(ctx,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLContext RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetCurrentContext_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetCurrentContext;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLContext retval;
	stream->readback(&retval, sizeof(EGLContext));
	return retval;
}
EGLSurface RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetCurrentSurface_client (void * self,EGLint readdraw){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetCurrentSurface;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLint(readdraw,ptr);
	EGLSurface retval;
	stream->readback(&retval, sizeof(EGLSurface));
	return retval;
}
EGLDisplay RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetCurrentDisplay_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetCurrentDisplay;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLDisplay retval;
	stream->readback(&retval, sizeof(EGLDisplay));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglSwapBuffers_client (void * self,EGLDisplay dpy, EGLSurface surface){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglSwapBuffers;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSurface(surface,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
__eglMustCastToProperFunctionPointerType RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetProcAddress_client (void * self,const char *procname){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetProcAddress;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	__eglMustCastToProperFunctionPointerType retval;
	stream->readback(&retval, sizeof(__eglMustCastToProperFunctionPointerType));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglSignalSyncKHR_client (void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + sizeof(EGLenum) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglSignalSyncKHR;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSyncKHR(sync,ptr);
		ptr = WriteEGLenum(mode,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLint RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglWaitSyncKHR_client (void * self,EGLDisplay dpy, EGLSyncKHR sync, EGLint flags){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + sizeof(EGLint) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglWaitSyncKHR;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSyncKHR(sync,ptr);
		ptr = WriteEGLint(flags,ptr);
	EGLint retval;
	stream->readback(&retval, sizeof(EGLint));
	return retval;
}
EGLClientBuffer RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetRenderBufferANDROID_client (void * self,EGLDisplay dpy, EGLSurface draw){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetRenderBufferANDROID;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSurface(draw,ptr);
	EGLClientBuffer retval;
	stream->readback(&retval, sizeof(EGLClientBuffer));
	return retval;
}
EGLint RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglDupNativeFenceFDANDROID_client (void * self,EGLDisplay dpy, EGLSyncKHR sync){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSyncKHR) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglDupNativeFenceFDANDROID;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSyncKHR(sync,ptr);
	EGLint retval;
	stream->readback(&retval, sizeof(EGLint));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglRenderBufferModifiedANDROID_client (void * self,EGLDisplay dpy, EGLSurface draw){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + sizeof(EGLDisplay) + sizeof(EGLSurface) + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglRenderBufferModifiedANDROID;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
		ptr = WriteEGLDisplay(dpy,ptr);
		ptr = WriteEGLSurface(draw,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLuint64NV RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetSystemTimeFrequencyNV_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetSystemTimeFrequencyNV;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLuint64NV retval;
	stream->readback(&retval, sizeof(EGLuint64NV));
	return retval;
}
EGLuint64NV RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglGetSystemTimeNV_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglGetSystemTimeNV;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLuint64NV retval;
	stream->readback(&retval, sizeof(EGLuint64NV));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglHibernateProcessIMG_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglHibernateProcessIMG;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}
EGLBoolean RedFingerEGLDispatch::RedFingerEGLEncoder::s_eglAwakenProcessIMG_client (void * self){
	RedFingerEGLEncoder *ctxxx = (RedFingerEGLEncoder *)self;
	IOStream *stream = ctxxx->stream_;
	const EGLuint __size_base = (sizeof(EGLuint) * 2);
	const EGLuint packetSize = __size_base + (0 * sizeof(EGLuint));
	unsigned char *ptr = stream->alloc(packetSize);
	EGLuint tmp = OP_eglAwakenProcessIMG;
		ptr = WriteEGLuint(tmp,ptr);
		ptr = WriteEGLuint(packetSize,ptr);
	EGLBoolean retval;
	stream->readback(&retval, sizeof(EGLBoolean));
	return retval;
}

extern "C"{

EGLBoolean eglInitialize(EGLDisplay display,EGLint* major,EGLint* minor){
	GET_CONTEXT_client_egl;
	RedFingerEGLDispatch::RedFingerEGLEncoder* egl_encoder = ctxxxxxxx->GetRedFingerEGLEncoder();
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglInitialize)){
		CALLRealEGLInitialize(display, major, minor);
	}
	EGLBoolean retval = egl_encoder->eglInitialize_client(egl_encoder,display, major, minor);
	RedFingerEGLDispatch::RedFingerEGLDescribing* egl_describing = egl_encoder->GetEGLDescribing();

	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,NULL,egl_describing->EGLClientApisLenPtr(),EGL_CLIENT_APIS);
	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,egl_describing->ResetTmp(egl_describing->EGLClientApisLen()),
		egl_describing->EGLClientApisLenPtr(),EGL_CLIENT_APIS);
	egl_describing->AddEGLString(EGL_CLIENT_APIS);

	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,NULL,egl_describing->EGLVendoLenPtr(),EGL_VENDOR);
	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,egl_describing->ResetTmp(egl_describing->EGLVendoLen()),
		egl_describing->EGLVendoLenPtr(),EGL_VENDOR);
	egl_describing->AddEGLString(EGL_VENDOR);

	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,NULL,egl_describing->EGLVersionLenPtr(),EGL_VERSION);
	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,egl_describing->ResetTmp(egl_describing->EGLVersionLen()),
		egl_describing->EGLVersionLenPtr(),EGL_VERSION);
	egl_describing->AddEGLString(EGL_VERSION);

	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,NULL,egl_describing->EGLExtensionsLenPtr(),EGL_EXTENSIONS);
	egl_encoder->RedFingerStaticDescribing_client(egl_encoder,egl_describing->ResetTmp(egl_describing->EGLExtensionsLen()),
		egl_describing->EGLExtensionsLenPtr(),EGL_EXTENSIONS);
	egl_describing->AddEGLString(EGL_EXTENSIONS);

	if (RedFinger::Debug::IsDebugPrint()){
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RedFingerStaticDescribing %s",__FUNCTION__,egl_describing->GetEGLString(EGL_CLIENT_APIS));
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RedFingerStaticDescribing %s",__FUNCTION__,egl_describing->GetEGLString(EGL_VENDOR));
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RedFingerStaticDescribing %s",__FUNCTION__,egl_describing->GetEGLString(EGL_VERSION));
		ALOGD("Debugingggggggggggggggggggggggggggggggg:%s:RedFingerStaticDescribing %s",__FUNCTION__,egl_describing->GetEGLString(EGL_EXTENSIONS));
	}
	return retval;
}
EGLSurface eglCreateWindowSurface(EGLDisplay display,EGLConfig config,NativeWindowType native_window,EGLint const * attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglCreateWindowSurface)){
		CALLRealEGLCreateWindowSurface(display, config, native_window, attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreateWindowSurface_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display, config, native_window, attrib_list);
}
EGLSurface eglCreatePbufferSurface(EGLDisplay display,EGLConfig config,EGLint const * attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglCreatePbufferSurface)){
		CALLRealEGLCreatePbufferSurface(display, config, attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreatePbufferSurface_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display, config, attrib_list);
}
EGLSurface eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglCreatePixmapSurface)){
		CALLRealEGLCreatePixmapSurface(dpy, config, pixmap, attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreatePixmapSurface_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, config, pixmap, attrib_list);
}
EGLBoolean eglBindAPI(EGLenum api){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglBindAPI)){
		CALLRealEGLBindAPI(api);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglBindAPI_client(ctxxxxxxx->GetRedFingerEGLEncoder(),api);
}
EGLenum eglQueryAPI(){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglQueryAPI)){
		CALLRealEGLQueryAPI();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglQueryAPI_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLSurface eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLCreatePbufferFromClientBuffer(dpy,buftype,buffer,config,attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreatePbufferFromClientBuffer_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,buftype,buffer,config,attrib_list);
}
EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglSurfaceAttrib)){
		CALLRealEGLSurfaceAttrib(dpy,surface,attribute,value);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglSurfaceAttrib_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,surface,attribute,value);
}
EGLBoolean eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLReleaseTexImage(dpy,surface,buffer);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglReleaseTexImage_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,surface,buffer);
}
EGLBoolean eglWaitNative(EGLint engine){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLWaitNative(engine);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglWaitNative_client(ctxxxxxxx->GetRedFingerEGLEncoder(),engine);
}
EGLBoolean eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLCopyBuffers(dpy,surface,target);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCopyBuffers_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,surface,target);
}
EGLBoolean eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLLockSurfaceKHR(display,surface,attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglLockSurfaceKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,surface,attrib_list);
}
EGLBoolean eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLUnlockSurfaceKHR(display,surface);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglUnlockSurfaceKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,surface);
}
EGLImageKHR eglCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglCreateImageKHR)){
		CALLRealEGLCreateImageKHR(dpy,ctx,target,buffer,attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreateImageKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,ctx,target,buffer,attrib_list);
}

EGLBoolean eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR img){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglDestroyImageKHR)){
		CALLRealEGLDestroyImageKHR(dpy,img);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglDestroyImageKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,img);
}	
EGLBoolean eglDestroySyncKHR(EGLDisplay dpy, EGLSyncKHR sync){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglDestroySyncKHR)){
		CALLRealEGLDestroySyncKHR(dpy,sync);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglDestroySyncKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,sync);
}
EGLint eglClientWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglClientWaitSyncKHR)){
		CALLRealEGLClientWaitSyncKHR(dpy,sync,flags,timeout);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglClientWaitSyncKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,sync,flags,timeout);
}
EGLBoolean eglGetSyncAttribKHR(EGLDisplay dpy, EGLSyncKHR sync,EGLint attribute, EGLint *value){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CALLRealEGLGetSyncAttribKHR(dpy,sync,attribute,value);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetSyncAttribKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,sync,attribute,value);
}
EGLBoolean eglGetConfigAttrib(EGLDisplay display,EGLConfig config,EGLint attribute,EGLint* value){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetConfigAttrib)){
		CALLRealEGLGetConfigAttrib(display,config,attribute,value);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetConfigAttrib_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,config,attribute,value);
}
EGLContext eglCreateContext(EGLDisplay display,EGLConfig config,EGLContext share_context,const EGLint * attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglCreateContext)){
		CALLRealEGLCreateContext(display,config,share_context,attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreateContext_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,config,share_context,attrib_list);
}
EGLSyncKHR eglCreateSyncKHR(EGLDisplay dpy, EGLenum type, const EGLint *attrib_list){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglCreateSyncKHR)){
		CALLRealEGLCreateSyncKHR(dpy,type,attrib_list);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglCreateSyncKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,type,attrib_list);
}
EGLBoolean eglQuerySurface(EGLDisplay display,EGLSurface surface,EGLint attribute,EGLint* value){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglQuerySurface)){
		CALLRealEGLQuerySurface(display,surface,attribute,value);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglQuerySurface_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,surface,attribute,value);
}
EGLBoolean eglQueryContext(EGLDisplay display,EGLContext context,EGLint attribute,EGLint* value){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglQueryContext)){
		CALLRealEGLQueryContext(display,context,attribute,value);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglQueryContext_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,context,attribute,value);
}

EGLint eglGetError(){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetError)){
		CallRealEGLGetError();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetError_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLBoolean eglGetConfigs(EGLDisplay display,EGLConfig* configs,EGLint config_size,EGLint* num_config){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetConfigs)){
		CallRealEGLGetConfigs(display,configs,config_size,num_config);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetConfigs_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,configs,config_size,num_config);
}
EGLBoolean eglChooseConfig(EGLDisplay display,EGLint const * attrib_list,EGLConfig * configs,EGLint config_size,EGLint * num_config){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglChooseConfig)){
		CallRealEGLChooseConfig(display,attrib_list,configs,config_size,num_config);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglChooseConfig_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display,attrib_list,configs,config_size,num_config);
}
EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetDisplay)){
		CallRealEGLGetDisplay(display_id);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetDisplay_client(ctxxxxxxx->GetRedFingerEGLEncoder(),display_id);
}
EGLBoolean eglTerminate(EGLDisplay dpy){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglTerminate)){
		CallRealEGLTerminate(dpy);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglTerminate_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy);
}
const char* eglQueryString(EGLDisplay dpy, EGLint name){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsOpenAPIAccelerator()){
		RedFingerEGLDispatch::RedFingerEGLEncoder* egl_encoder = ctxxxxxxx->GetRedFingerEGLEncoder();
		RedFingerEGLDispatch::RedFingerEGLDescribing* egl_describing = egl_encoder->GetEGLDescribing();
		return egl_describing->GetEGLString(name);
	}
	if (RedFinger::Debug::IsDebugPrint()){
		return CallRealEGLQueryString(dpy, name);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglQueryString_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, name);
}
EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglDestroySurface)){
		CallRealEGLDestroySurface(dpy, surface);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglDestroySurface_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, surface);
}
EGLBoolean eglWaitClient(){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglWaitClient)){
		CallRealEGLWaitClient();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglWaitClient_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLBoolean eglReleaseThread(){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglReleaseThread)){
		CallRealEGLReleaseThread();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglReleaseThread_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLBoolean eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglBindTexImage)){
		CallRealEGLBindTexImage(dpy, surface, buffer);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglBindTexImage_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, surface, buffer);
}
EGLBoolean eglSwapInterval(EGLDisplay dpy, EGLint interval){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglSwapInterval)){
		CallRealEGLSwapInterval(dpy, interval);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglSwapInterval_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, interval);
}
EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglDestroyContext)){
		CallRealEGLDestroyContext(dpy, ctx);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglDestroyContext_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, ctx);
}
EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglMakeCurrent)){
		CallRealEGLMakeCurrent(dpy, draw, read, ctx);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglMakeCurrent_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy, draw, read, ctx);
}
EGLContext eglGetCurrentContext(){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetCurrentContext)){
		CallRealEGLGetCurrentContext();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetCurrentContext_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLSurface eglGetCurrentSurface(EGLint readdraw){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetCurrentSurface)){
		CallRealEGLGetCurrentSurface(readdraw);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetCurrentSurface_client(ctxxxxxxx->GetRedFingerEGLEncoder(),readdraw);
}
EGLDisplay eglGetCurrentDisplay(){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglGetCurrentDisplay)){
		CallRealEGLGetCurrentDisplay();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetCurrentDisplay_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglSwapBuffers)){
		CallRealEGLSwapBuffers(dpy,surface);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglSwapBuffers_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,surface);
}
__eglMustCastToProperFunctionPointerType eglGetProcAddress(const char *procname){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLGetProcAddress(procname);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetProcAddress_client(ctxxxxxxx->GetRedFingerEGLEncoder(),procname);
}
EGLBoolean eglSignalSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLSignalSyncKHR(dpy,sync,mode);
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLSignalSyncKHR(dpy,sync,mode);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglSignalSyncKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,sync,mode);
}
EGLint eglWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglWaitSyncKHR)){
		CallRealEGLWaitSyncKHR(dpy,sync,flags);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglWaitSyncKHR_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,sync,flags);
}
EGLClientBuffer eglGetRenderBufferANDROID(EGLDisplay dpy, EGLSurface draw){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLGetRenderBufferANDROID(dpy,draw);
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLGetRenderBufferANDROID(dpy,draw);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetRenderBufferANDROID_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,draw);
}
EGLint eglDupNativeFenceFDANDROID(EGLDisplay dpy, EGLSyncKHR sync){
	GET_CONTEXT_client_egl;
	if (RedFinger::Debug::IsDebugPrint()&&!RedFingerEGLDispatch::IsDebugOK(RedFingerEGLDispatch::OP_eglDupNativeFenceFDANDROID)){
		CallRealEGLDupNativeFenceFDANDROID(dpy,sync);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglDupNativeFenceFDANDROID_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,sync);
}
EGLBoolean eglRenderBufferModifiedANDROID(EGLDisplay dpy, EGLSurface draw){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLRenderBufferModifiedANDROID(dpy,draw);
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLRenderBufferModifiedANDROID(dpy,draw);
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglRenderBufferModifiedANDROID_client(ctxxxxxxx->GetRedFingerEGLEncoder(),dpy,draw);
}
EGLuint64NV eglGetSystemTimeFrequencyNV(){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLGetSystemTimeFrequencyNV();
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLGetSystemTimeFrequencyNV();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetSystemTimeFrequencyNV_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLuint64NV eglGetSystemTimeNV(){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLGetSystemTimeNV();
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLGetSystemTimeNV();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglGetSystemTimeNV_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLBoolean eglHibernateProcessIMG(){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLHibernateProcessIMG();
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLHibernateProcessIMG();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglHibernateProcessIMG_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}
EGLBoolean eglAwakenProcessIMG(){
	GET_CONTEXT_client_egl;
	if (RedFingerEGLDispatch::IsAndroid4_4_2())
	{
		return CallRealEGLAwakenProcessIMG();
	}
	if (RedFinger::Debug::IsDebugPrint()){
		CallRealEGLAwakenProcessIMG();
	}
	return ctxxxxxxx->GetRedFingerEGLEncoder()->eglAwakenProcessIMG_client(ctxxxxxxx->GetRedFingerEGLEncoder());
}

}