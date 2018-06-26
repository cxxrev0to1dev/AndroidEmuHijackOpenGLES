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
#ifndef __GLESV2_NATIVE_FUNC_CALL_H_
#define __GLESV2_NATIVE_FUNC_CALL_H_

#include "gles_enc.h"
#include "GLClientState.h"
#include "GLSharedGroup.h"
#include "FixedBuffer.h"

#include <string>

class GLESv2NativeFuncCall {
public:
    GLESv2NativeFuncCall();
    virtual ~GLESv2NativeFuncCall();
    void initGL(gles_encoder_context_t* enc_ptr);
public:
    static void s_glTexStorage3D(void* self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
    static void s_glEnable(void* self, GLenum what);
    static void s_glDisable(void* self, GLenum what);
    static void s_glClearBufferiv(void* self, GLenum buffer, GLint drawBuffer, const GLint* value);
    static void s_glClearBufferuiv(void* self, GLenum buffer, GLint drawBuffer, const GLuint* value);
    static void s_glClearBufferfv(void* self, GLenum buffer, GLint drawBuffer, const GLfloat* value);
    static void s_glBlitFramebuffer(void* self, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
    static void s_glGetInternalformativ(void* self, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);
    static void s_glGenerateMipmap(void* self, GLenum target);
    static void s_glBindSampler(void* self, GLuint unit, GLuint sampler);
    static void s_glGetIntegeri_v(void* self, GLenum target, GLuint index, GLint* params);
    static void s_glGetInteger64i_v(void* self, GLenum target, GLuint index, GLint64* params);
    static void s_glGetProgramPipelineInfoLog(void* self, GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    static void s_glVertexAttribFormat(void* self, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
    static void s_glVertexAttribIFormat(void* self, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
    static void s_glVertexBindingDivisor(void* self, GLuint bindingindex, GLuint divisor);
    static void s_glVertexAttribBinding(void* self, GLuint attribindex, GLuint bindingindex);
    static void s_glBindVertexBuffer(void* self, GLuint bindingindex, GLuint buffer, GLintptr offset, GLintptr stride);
    static void s_glTexStorage2DMultisample(void* self, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);


    static GLenum s_glGetError(void * self);
    static void s_glFlush(void * self);
    static void s_glGetIntegerv(void *self, GLenum pname, GLint *ptr);
    static void s_glGetFloatv(void *self, GLenum pname, GLfloat *ptr);
    static void s_glGetBooleanv(void *self, GLenum pname, GLboolean *ptr);
    static void s_glGetInteger64v(void* self, GLenum param, GLint64* val);
    static void s_glGetBooleani_v(void* self, GLenum param, GLuint index, GLboolean* val);
    static void s_glEnableVertexAttribArray(void *self, GLuint index);
    static void s_glDisableVertexAttribArray(void *self, GLuint index);
    static void s_glGetVertexAttribiv(void *self, GLuint index, GLenum pname, GLint *params);
    static void s_glGetVertexAttribfv(void *self, GLuint index, GLenum pname, GLfloat *params);
    static void s_glGetVertexAttribPointerv(void *self, GLuint index, GLenum pname, GLvoid **pointer);
    static void s_glFinish(void *self);
    static void s_glUniform1f(void *self , GLint location, GLfloat x);
    static void s_glUniform1fv(void *self , GLint location, GLsizei count, const GLfloat* v);
    static void s_glUniform1i(void *self , GLint location, GLint x);
    static void s_glUniform1iv(void *self , GLint location, GLsizei count, const GLint* v);
    static void s_glUniform2f(void *self , GLint location, GLfloat x, GLfloat y);
    static void s_glUniform2fv(void *self , GLint location, GLsizei count, const GLfloat* v);
    static void s_glUniform2i(void *self , GLint location, GLint x, GLint y);
    static void s_glUniform2iv(void *self , GLint location, GLsizei count, const GLint* v);
    static void s_glUniform3f(void *self , GLint location, GLfloat x, GLfloat y, GLfloat z);
    static void s_glUniform3fv(void *self , GLint location, GLsizei count, const GLfloat* v);
    static void s_glUniform3i(void *self , GLint location, GLint x, GLint y, GLint z);
    static void s_glUniform3iv(void *self , GLint location, GLsizei count, const GLint* v);
    static void s_glUniform4f(void *self , GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static void s_glUniform4fv(void *self , GLint location, GLsizei count, const GLfloat* v);
    static void s_glUniform4i(void *self , GLint location, GLint x, GLint y, GLint z, GLint w);
    static void s_glUniform4iv(void *self , GLint location, GLsizei count, const GLint* v);
    static void s_glUniformMatrix2fv(void *self , GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static void s_glUniformMatrix3fv(void *self , GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static void s_glUniformMatrix4fv(void *self , GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static void s_glActiveTexture(void* self, GLenum texture);
    static void s_glBindTexture(void* self, GLenum target, GLuint texture);
    static void s_glGetTexParameterfv(void* self, GLenum target, GLenum pname, GLfloat* params);
    static void s_glGetTexParameteriv(void* self, GLenum target, GLenum pname, GLint* params);
    static void s_glTexParameterf(void* self, GLenum target, GLenum pname, GLfloat param);
    static void s_glTexParameterfv(void* self, GLenum target, GLenum pname, const GLfloat* params);
    static void s_glTexParameteri(void* self, GLenum target, GLenum pname, GLint param);
    static void s_glTexParameteriv(void* self, GLenum target, GLenum pname, const GLint* params);
    static void s_glCopyTexImage2D(void* self, GLenum target, GLint level, GLenum internalformat,GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    static void s_glBindRenderbuffer(void* self, GLenum target, GLuint renderbuffer);
    static void s_glRenderbufferStorage(void* self, GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    static void s_glFramebufferRenderbuffer(void* self, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
    static void s_glBindFramebuffer(void* self, GLenum target, GLuint framebuffer);
    static void s_glFramebufferTexture2D(void* self, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    static void s_glFramebufferTexture3DOES(void*self, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
    static void s_glGetFramebufferAttachmentParameteriv(void* self, GLenum target, GLenum attachment, GLenum pname, GLint* params);
    static GLenum s_glCheckFramebufferStatus(void* self,GLenum target);
    static void s_glBindVertexArray(void *self , GLuint array);
    static void s_glBindBufferRange(void *self , GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
    static void s_glBindBufferBase(void *self , GLenum target, GLuint index, GLuint buffer);
    static void s_glCopyBufferSubData(void *self , GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size);
    static void s_glGetBufferParameteriv(void* self, GLenum target, GLenum pname, GLint* params);
    static void s_glGetBufferParameteri64v(void* self, GLenum target, GLenum pname, GLint64* params);
    static void s_glGetBufferPointerv(void* self, GLenum target, GLenum pname, GLvoid** params);
    static void s_glUniform1ui(void* self, GLint location, GLuint v0);
    static void s_glUniform2ui(void* self, GLint location, GLuint v0, GLuint v1);
    static void s_glUniform3ui(void* self, GLint location, GLuint v0, GLuint v1, GLuint v2);
    static void s_glUniform4ui(void* self, GLint location, GLint v0, GLuint v1, GLuint v2, GLuint v3);
    static void s_glUniform1uiv(void* self, GLint location, GLsizei count, const GLuint *value);
    static void s_glUniform2uiv(void* self, GLint location, GLsizei count, const GLuint *value);
    static void s_glUniform3uiv(void* self, GLint location, GLsizei count, const GLuint *value);
    static void s_glUniform4uiv(void* self, GLint location, GLsizei count, const GLuint *value);
    static void s_glUniformMatrix2x3fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glUniformMatrix3x2fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glUniformMatrix2x4fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glUniformMatrix4x2fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glUniformMatrix3x4fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glUniformMatrix4x3fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glGetVertexAttribIiv(void* self, GLuint index, GLenum pname, GLint* params);
    static void s_glGetVertexAttribIuiv(void* self, GLuint index, GLenum pname, GLuint* params);
    static void s_glVertexAttribDivisor(void* self, GLuint index, GLuint divisor);
    static void s_glRenderbufferStorageMultisample(void* self, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
    static void s_glDrawBuffers(void* self, GLsizei n, const GLenum* bufs);
    static void s_glReadBuffer(void* self, GLenum src);
    static void s_glFramebufferTextureLayer(void* self, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
    static void s_glTexStorage2D(void* self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
    static void s_glBeginTransformFeedback(void* self, GLenum primitiveMode);
    static void s_glEndTransformFeedback(void* self);
    static void s_glPauseTransformFeedback(void* self);
    static void s_glResumeTransformFeedback(void* self);
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    static void s_glPixelStorei(void *self, GLenum param, GLint value);
    static void s_glBindBuffer(void *self, GLenum target, GLuint id);
    static void s_glBufferData(void *self, GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
    static void s_glBufferSubData(void *self, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data);

    static const GLubyte* s_glGetString(void *self, GLenum name);
    static const GLubyte* s_glGetStringi(void * self, GLenum name, GLuint index);
    static void s_glEGLImageTargetTexture2DOES(void * self, GLenum target, GLeglImageOES image);
    static void s_glEGLImageTargetRenderbufferStorageOES(void *self, GLenum target, GLeglImageOES image);
    static void* s_glMapBufferOES(void *self, GLenum target, GLenum access);

    static void s_glGetCompressedTextureFormats(void *self, int count, GLint *formats);
    static void s_glVertexAttribPointer(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);

    static void s_glDrawArrays(void *self, GLenum mode, GLint first, GLsizei count);
    static void s_glDrawArraysInstanced(void *self, GLenum mode, GLint first, GLsizei count, GLsizei primcount);
    static void s_glDrawRangeElements(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices);
    static void s_glDrawElements(void *self, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    static int  s_glFinishRoundTrip(void *self);

    static void* s_glMapBufferRange(void* self, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
    static GLboolean s_glUnmapBuffer(void* self, GLenum target);
    static void s_glFlushMappedBufferRange(void* self, GLenum target, GLintptr offset, GLsizeiptr length);

    static void s_glCompressedTexImage2D(void* self, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
    static void s_glCompressedTexSubImage2D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
    static void s_glTexImage2D(void* self, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    static void s_glTexSubImage2D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);

    static void s_glVertexAttribIPointer(void *self, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);

    static void s_glTexImage3D(void* self, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data);
    static void s_glTexSubImage3D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data);
    static void s_glCompressedTexImage3D(void* self, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data);
    static void s_glCompressedTexSubImage3D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data);
    static void s_glDrawElementsInstanced(void* self, GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount);
    static void s_glGetUniformIndices(void* self, GLuint program, GLsizei uniformCount, const GLchar** var3, GLuint* uniformIndices);
    //
    static void s_glReadPixels(void* self, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
    static GLuint s_glCreateShaderProgramv(void* self, GLenum type, GLsizei count, const char** var3);
    static void s_glDrawArraysIndirect(void* self, GLenum mode, const void* indirect);
    static void s_glDrawElementsIndirect(void* self, GLenum mode, GLenum type, const void* indirect);

    static GLsync s_glFenceSync(void* self, GLenum condition, GLbitfield flags);
    static GLenum s_glClientWaitSync(void* self, GLsync wait_on, GLbitfield flags, GLuint64 timeout);
    static void s_glWaitSync(void* self, GLsync wait_on, GLbitfield flags, GLuint64 timeout);
    static void s_glDeleteSync(void* self, GLsync to_delete);
    static GLboolean s_glIsSync(void* self, GLsync sync);
    static void s_glGetSynciv(void* self, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

    //============================================================
    // Snapshot state
    //============================================================

    // All generations============================================
    
    static GLuint s_glCreateShader(void* self, GLenum shaderType);
    static GLuint s_glCreateProgram(void* self);

    static void s_glGenBuffers(void* self, GLsizei n, GLuint* buffers);

    static void s_glGenFramebuffers(void* self, GLsizei n, GLuint* framebuffers);
    static void s_glGenRenderbuffers(void* self, GLsizei n, GLuint* renderbuffers);
    static void s_glGenTextures(void* self, GLsizei n, GLuint* textures);

    static void s_glGenVertexArraysOES(void* self, GLsizei n, GLuint* arrays);
    static void s_glGenVertexArrays(void* self, GLsizei n, GLuint* arrays);

    static void s_glGenTransformFeedbacks(void* self, GLsizei n, GLuint* transformFeedbacks);

    static void s_glGenSamplers(void* self, GLsizei n, GLuint* samplers);

    static void s_glGenQueries(void* self, GLsizei n, GLuint* queries);

    static void s_glGenProgramPipelines(void* self, GLsizei n, GLuint* pipelines);

    // All deletes================================================
    static void s_glDeleteShader(void* self, GLuint shader);
    static void s_glDeleteProgram(void* self, GLuint program);

    static void s_glDeleteBuffers(void* self, GLsizei n, const GLuint *buffers);
    static void s_glDeleteFramebuffers(void* self, GLsizei n, const GLuint *framebuffers);
    static void s_glDeleteRenderbuffers(void* self, GLsizei n, const GLuint *renderbuffers);
    static void s_glDeleteTextures(void* self, GLsizei n, const GLuint *textures);

    static void s_glDeleteVertexArraysOES(void* self, GLsizei n, const GLuint *arrays);
    static void s_glDeleteVertexArrays(void* self, GLsizei n, const GLuint *arrays);

    static void s_glDeleteTransformFeedbacks(void* self, GLsizei n, const GLuint *transformfeedbacks);
    static void s_glDeleteSamplers(void* self, GLsizei n, const GLuint *samplers);
    static void s_glDeleteQueries(void* self, GLsizei n, const GLuint *queries);
    static void s_glDeleteProgramPipelines(void* self, GLsizei n, const GLuint *pipelines);

    // Shaders and programs=======================================
    static void s_glShaderSource(void *self, GLuint shader, GLsizei count, const GLchar*const* string, const GLint* length);
    static void s_glCompileShader(void* self, GLuint shader);
    static void s_glAttachShader(void* self, GLuint program, GLuint shader);
    static void s_glDetachShader(void* self, GLuint program, GLuint shader);
    static void s_glLinkProgram(void* self, GLuint program);
    static void s_glUseProgram(void* self, GLuint program);
    static void s_glValidateProgram(void* self, GLuint program);

    static GLboolean s_glIsShader(void* self, GLuint shader);
    static GLboolean s_glIsProgram(void* self, GLuint program);

    static void s_glGetShaderiv(void* self, GLuint shader, GLenum pname, GLint* params);
    static void s_glGetProgramiv(void* self, GLuint program, GLenum pname, GLint* params);
    static void s_glGetShaderInfoLog(void* self, GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    static void s_glGetProgramInfoLog(void* self, GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    static void s_glGetShaderSource(void* self, GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);

    static void s_glBindAttribLocation(void* self, GLuint program, GLuint index, const GLchar* name);
    static void s_glGetActiveAttrib(void* self, GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    static void s_glGetActiveUniform(void* self, GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    static void s_glGetAttachedShaders(void* self, GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
    static GLint s_glGetAttribLocation(void* self, GLuint program, const GLchar* name);

    static void s_glGetUniformfv(void* self, GLuint program, GLint location, GLfloat* params);
    static void s_glGetUniformiv(void* self, GLuint program, GLint location, GLint* params);
    static GLint s_glGetUniformLocation(void* self, GLuint program,  const GLchar* name);

    static void s_glGetProgramBinaryOES(void* self, GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary);
    static void s_glProgramBinaryOES(void* self, GLuint program, GLenum binaryFormat, const GLvoid* binary, GLint length);

    static void s_glUniformBlockBinding(void* self, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
    static GLuint s_glGetUniformBlockIndex(void* self, GLuint program, const GLchar* uniformBlockName);

    static void s_glGetActiveUniformBlockiv(void* self, GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
    static void s_glGetActiveUniformBlockName(void* self, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);

    static void s_glGetUniformuiv(void* self, GLuint program, GLint location, GLuint *params);
    static void s_glGetActiveUniformsiv(void* self, GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);

    static void s_glTransformFeedbackVaryings(void* self, GLuint program, GLsizei count, const char** var3, GLenum bufferMode);
    static void s_glGetTransformFeedbackVarying(void* self, GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, char * name);

    static void s_glProgramParameteri(void* self, GLuint program, GLenum pname, GLint value);
    static void s_glProgramBinary(void* self, GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
    static void s_glGetProgramBinary(void* self, GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);

    static GLint s_glGetFragDataLocation(void* self, GLuint program, const char * name);

    static void s_glUseProgramStages(void* self, GLuint pipeline, GLbitfield stages, GLuint program);
    static void s_glActiveShaderProgram(void* self, GLuint pipeline, GLuint program);

    static void s_glProgramUniform1f(void* self, GLuint program, GLint location, GLfloat v0);
    static void s_glProgramUniform2f(void* self, GLuint program, GLint location, GLfloat v0, GLfloat v1);
    static void s_glProgramUniform3f(void* self, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static void s_glProgramUniform4f(void* self, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    static void s_glProgramUniform1i(void* self, GLuint program, GLint location, GLint v0);
    static void s_glProgramUniform2i(void* self, GLuint program, GLint location, GLint v0, GLint v1);
    static void s_glProgramUniform3i(void* self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
    static void s_glProgramUniform4i(void* self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    static void s_glProgramUniform1ui(void* self, GLuint program, GLint location, GLuint v0);
    static void s_glProgramUniform2ui(void* self, GLuint program, GLint location, GLint v0, GLuint v1);
    static void s_glProgramUniform3ui(void* self, GLuint program, GLint location, GLint v0, GLint v1, GLuint v2);
    static void s_glProgramUniform4ui(void* self, GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLuint v3);
    static void s_glProgramUniform1fv(void* self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void s_glProgramUniform2fv(void* self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void s_glProgramUniform3fv(void* self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void s_glProgramUniform4fv(void* self, GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void s_glProgramUniform1iv(void* self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void s_glProgramUniform2iv(void* self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void s_glProgramUniform3iv(void* self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void s_glProgramUniform4iv(void* self, GLuint program, GLint location, GLsizei count, const GLint *value);
    static void s_glProgramUniform1uiv(void* self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void s_glProgramUniform2uiv(void* self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void s_glProgramUniform3uiv(void* self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void s_glProgramUniform4uiv(void* self, GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void s_glProgramUniformMatrix2fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix3fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix4fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix2x3fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix3x2fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix2x4fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix4x2fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix3x4fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void s_glProgramUniformMatrix4x3fv(void* self, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

    static void s_glGetProgramInterfaceiv(void* self, GLuint program, GLenum programInterface, GLenum pname, GLint * params);
    static void s_glGetProgramResourceiv(void* self, GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params);
    static GLuint s_glGetProgramResourceIndex(void* self, GLuint program, GLenum programInterface, const char * name);
    static GLint s_glGetProgramResourceLocation(void* self, GLuint program, GLenum programInterface, const char * name);
    static void s_glGetProgramResourceName(void* self, GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, char * name);


};
#endif
