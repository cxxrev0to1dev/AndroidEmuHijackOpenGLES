#include "GLESv1DispatchInternal.h"
#include <sys/mman.h>
#include "glUtils.h"
// #include "GLESv2ThreadInfo.h"
#include "ErrorLog.h"
#include "gles_opcodes.h"


static GLubyte *gVendorString= (GLubyte *) "Android";
static GLubyte *gRendererString= (GLubyte *) "Android HW-GLES 2.0";
static GLubyte *gVersionString= (GLubyte *) "OpenGL ES 2.0";
static GLubyte *gExtensionsString= (GLubyte *) "GL_OES_byte_coordinates GL_OES_fixed_point GL_OES_single_precision GL_OES_matrix_get GL_OES_compressed_paletted_texture GL_OES_point_size_array GL_OES_point_sprite GL_OES_read_format GL_OES_compressed_ETC1_RGB8_texture GL_OES_depth24 GL_OES_stencil8 GL_OES_framebuffer_object GL_OES_packed_depth_stencil GL_OES_rgb8_rgba8 GL_EXT_read_format_bgra GL_OES_matrix_palette GL_OES_extended_matrix_palette GL_OES_draw_texture GL_OES_blend_equation_separate GL_OES_blend_func_separate GL_OES_blend_subtract GL_OES_stencil_wrap GL_OES_texture_mirrored_repeat GL_EXT_texture_format_BGRA8888 GL_OES_query_matrix GL_OES_EGL_image GL_OES_EGL_image_external GL_OES_EGL_sync GL_OES_texture_npot GL_OES_vertex_half_float GL_OES_required_internalformat GL_OES_vertex_array_object GL_OES_mapbuffer GL_OES_fbo_render_mipmap GL_OES_element_index_uint GL_ARM_rgba8 GL_EXT_blend_minmax GL_EXT_discard_framebuffer GL_EXT_texture_storage GL_OES_texture_compression_astc GL_KHR_texture_comp ";

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

GLESv1DispatchInternal::GLESv1DispatchInternal(IOStream *stream,void* impl_so) : GLESv1Encoder(stream){
	GetGLESv1Encoder()->initGL();
	GetGLESv1Encoder()->glGetString = RedFingerGLESv1Interception::s_glGetString_enc;
	GetGLESv1Decoder()->initGL();
}
GLESv1DispatchInternal::~GLESv1DispatchInternal(){
	ALOGE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
}
#undef GET_CONTEXT_CLIENT_GLESv1Interception
#ifndef GET_CONTEXT_CLIENT_GLESv1Interception
static RedFingerGLESv1Interception::CONTEXT_ACCESSOR_TYPE *getCurrentContext_gl_client = NULL;
void RedFingerGLESv1Interception::setContextAccessor(CONTEXT_ACCESSOR_TYPE *f) { getCurrentContext_gl_client = f; }
#define GET_CONTEXT_CLIENT_GLESv1Interception RedFingerGLESv1Interception* ctxGLInterception = getCurrentContext_gl_client() 
#endif

RedFingerGLESv1Interception::RedFingerGLESv1Interception(){
	SetInitialize(false);
	GetGLESv1NativeFuncPtr()->Init();
}
RedFingerGLESv1Interception::~RedFingerGLESv1Interception(){
	SetInitialize(false);
}
RedFingerGLESv1Interception::RedFingerCallGLESv1NativeFunc::RedFingerCallGLESv1NativeFunc(){
	Reset();
}
RedFingerGLESv1Interception::RedFingerCallGLESv1NativeFunc::~RedFingerCallGLESv1NativeFunc(){
	Reset();
}
void RedFingerGLESv1Interception::RedFingerCallGLESv1NativeFunc::Init(){
	static const char* kHardwareGLESLibrary = "/system/vendor/lib/egl/rk3288/libGLES_mali.so.bak";
	void *gles_android = dlopen(kHardwareGLESLibrary, RTLD_NOW | RTLD_LOCAL);
	glGetString = (glGetString_server_proc_t)dlsym(gles_android,"glGetString");
	glEGLImageTargetTexture2DOES = (glEGLImageTargetTexture2DOES_server_proc_t)dlsym(gles_android,"glEGLImageTargetTexture2DOES");
	glEGLImageTargetRenderbufferStorageOES = (glEGLImageTargetRenderbufferStorageOES_server_proc_t)dlsym(gles_android,"glEGLImageTargetRenderbufferStorageOES");
}
void RedFingerGLESv1Interception::RedFingerCallGLESv1NativeFunc::Reset(){
	glGetString = NULL;
	glEGLImageTargetTexture2DOES = NULL;
	glEGLImageTargetRenderbufferStorageOES = NULL;
}
size_t RedFingerGLESv1Interception::decode(void *buf, size_t len, IOStream *stream){
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
bool RedFingerGLESv1Interception::IsInterceptionTargetOpcode(void *buf, size_t len){
	if (len < 8) return false;
	unsigned char *ptr = (unsigned char *)buf;
	EGLuint opcode = GETDWORD(ptr);
	return (opcode==OP_glGetString);
}
const GLubyte* RedFingerGLESv1Interception::s_glGetString_enc(void *self, GLenum name){
	// if (name==GL_VERSION){
	// 	return (const GLubyte*)"OpenGL ES 2.0";
	// }
	GET_CONTEXT_CLIENT_GLESv1Interception;
	RedFingerGLESv1Interception::RedFingerGLESv1Describing* gl_describing = ctxGLInterception->GetGLESv1DescribingPtr();
	gles1_encoder_context_t *ctx = (gles1_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	GLubyte *retval =  (GLubyte *) "";
	const char* retstr = gl_describing->GetString(name);
	if (retstr==NULL){
		char tmp[10000] = {0};
		s_glGetString_client(self,name,gl_describing->ResetTmp(10000),10000);
		gl_describing->AddGLEescribing(name);
	}
	retval = (GLubyte *)gl_describing->GetString(name);
    return retval;
}
EGLint RedFingerGLESv1Interception::s_glGetString_client(void * self,EGLint name,void* buf,EGLuint buflen){
	GET_CONTEXT_CLIENT_GLESv1Interception;
	gles1_encoder_context_t *ctx = (gles1_encoder_context_t *)self;
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
	stream->readback(buf, retval);/*FIXME,please verify buf result*/
	return retval;
}
EGLint RedFingerGLESv1Interception::s_glGetString_server(EGLint name,void* buf,EGLuint buflen){
	GET_CONTEXT_CLIENT_GLESv1Interception;
	RedFingerGLESv1Interception::RedFingerGLESv1Describing* gl_describing = ctxGLInterception->GetGLESv1DescribingPtr();
	char* str = const_cast<char*>(ctxGLInterception->GetGLESv1DescribingPtr()->GetString(name));
	if (str==NULL){
		str = (char*)ctxGLInterception->GetGLESv1NativeFuncPtr()->glGetString(name);
	    if (!str) {
        	return 0;
    	}
    	ctxGLInterception->GetGLESv1DescribingPtr()->AddGLEescribing(name,const_cast<const char*>(str));
	}
	std::string glStr(str);
	EGLint len = glStr.size() + 1;
    if (!buf || len > buflen) {
        return -len;
    }
    strcpy((char *)buf, glStr.c_str());
    return len;
}
void RedFingerGLESv1Interception::s_glEGLImageTargetTexture2DOES_ext(void * self, GLenum target, GLeglImageOES image){
    GET_CONTEXT_CLIENT_GLESv1Interception;
    GLESv1Encoder *ctx = (GLESv1Encoder *)self;
    ctx->override2DTextureTarget(target);
    ctxGLInterception->GetGLESv1NativeFuncPtr()->glEGLImageTargetTexture2DOES(target,image);
    ctx->restore2DTextureTarget();
    return;
}
void RedFingerGLESv1Interception::s_glEGLImageTargetRenderbufferStorageOES_ext(void *self, GLenum target, GLeglImageOES image){
    GET_CONTEXT_CLIENT_GLESv1Interception;
    ctxGLInterception->GetGLESv1NativeFuncPtr()->glEGLImageTargetRenderbufferStorageOES(target,image);
    return;
}