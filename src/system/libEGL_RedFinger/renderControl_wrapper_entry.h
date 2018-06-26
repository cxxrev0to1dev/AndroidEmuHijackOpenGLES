#ifndef __RENDERCONTROL_WRAPPER_ENTRY_H_
#define __RENDERCONTROL_WRAPPER_ENTRY_H_

extern "C" {
	GLint rcGetRendererVersion();
	EGLint rcGetEGLVersion(EGLint* major, EGLint* minor);
	EGLint rcQueryEGLString(EGLenum name, void* buffer, EGLint bufferSize);
	EGLint rcGetGLString(EGLenum name, void* buffer, EGLint bufferSize);
	EGLint rcGetNumConfigs(uint32_t* numAttribs);
	EGLint rcGetConfigs(uint32_t bufSize, GLuint* buffer);
	EGLint rcChooseConfig(EGLint* attribs, uint32_t attribs_size, uint32_t* configs, uint32_t configs_size);
	EGLint rcGetFBParam(EGLint param);
	uint32_t rcCreateContext(uint32_t config, uint32_t share, uint32_t glVersion);
	void rcDestroyContext(uint32_t context);
	uint32_t rcCreateWindowSurface(uint32_t config, uint32_t width, uint32_t height);
	void rcDestroyWindowSurface(uint32_t windowSurface);
	uint32_t rcCreateColorBuffer(uint32_t width, uint32_t height, GLenum internalFormat);
	void rcOpenColorBuffer(uint32_t colorbuffer);
	void rcCloseColorBuffer(uint32_t colorbuffer);
	void rcSetWindowColorBuffer(uint32_t windowSurface, uint32_t colorBuffer);
	int rcFlushWindowColorBuffer(uint32_t windowSurface);
	EGLint rcMakeCurrent(uint32_t context, uint32_t drawSurf, uint32_t readSurf);
	void rcFBPost(uint32_t colorBuffer);
	void rcFBSetSwapInterval(EGLint interval);
	void rcBindTexture(uint32_t colorBuffer);
	void rcBindRenderbuffer(uint32_t colorBuffer);
	EGLint rcColorBufferCacheFlush(uint32_t colorbuffer, EGLint postCount, int forRead);
	void rcReadColorBuffer(uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels);
	int rcUpdateColorBuffer(uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels);
	int rcOpenColorBuffer2(uint32_t colorbuffer);
	uint32_t rcCreateClientImage(uint32_t context, EGLenum target, GLuint buffer);
	int rcDestroyClientImage(uint32_t image);
	void rcSelectChecksumHelper(uint32_t newProtocol, uint32_t reserved);
	void rcCreateSyncKHR(EGLenum type, EGLint* attribs, uint32_t num_attribs, int destroy_when_signaled, uint64_t* glsync_out, uint64_t* syncthread_out);
	EGLint rcClientWaitSyncKHR(uint64_t sync, EGLint flags, uint64_t timeout);
	void rcFlushWindowColorBufferAsync(uint32_t windowSurface);
	int rcDestroySyncKHR(uint64_t sync);
	void rcSetPuid(uint64_t puid);
	int rcUpdateColorBufferDMA(uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels, uint32_t pixels_size);
	uint32_t rcCreateColorBufferDMA(uint32_t width, uint32_t height, GLenum internalFormat, int frameworkFormat);
};

#endif
