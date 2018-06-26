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

#include "GLESv2NativeFuncCall.h"
#include <dlfcn.h>
#include "gles_dec.h"

#include <string>
#include <map>

#include <assert.h>
#include <ctype.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include "GLESv2ThreadInfo.h"
#include "GLESv2Validation.h"
#include "GLESv2Decoder.h"

GLESv2NativeFuncCall::GLESv2NativeFuncCall(){
    ALOGE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
}

GLESv2NativeFuncCall::~GLESv2NativeFuncCall(){
    ALOGE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
}

void GLESv2NativeFuncCall::initGL(gles_encoder_context_t* enc_ptr){

    // You must run here code
    enc_ptr->glGetString = s_glGetString;
    enc_ptr->glGetStringi = s_glGetStringi;
    
    enc_ptr->glEGLImageTargetTexture2DOES = s_glEGLImageTargetTexture2DOES;
    enc_ptr->glEGLImageTargetRenderbufferStorageOES = s_glEGLImageTargetRenderbufferStorageOES;
    enc_ptr->glMapBufferOES = s_glMapBufferOES;

    enc_ptr->glGetCompressedTextureFormats = s_glGetCompressedTextureFormats;
    enc_ptr->glVertexAttribPointer = s_glVertexAttribPointer;
    enc_ptr->glShaderSource = s_glShaderSource;

    enc_ptr->glDrawArrays = s_glDrawArrays;
    enc_ptr->glDrawArraysInstanced = s_glDrawArraysInstanced;
    enc_ptr->glDrawRangeElements = s_glDrawRangeElements;
    enc_ptr->glDrawElements = s_glDrawElements;
    enc_ptr->glFinishRoundTrip = s_glFinishRoundTrip;
    enc_ptr->glMapBufferRange = s_glMapBufferRange;
    enc_ptr->glUnmapBuffer = s_glUnmapBuffer;
    enc_ptr->glFlushMappedBufferRange = s_glFlushMappedBufferRange;
    enc_ptr->glCompressedTexImage2D = s_glCompressedTexImage2D;
    enc_ptr->glCompressedTexSubImage2D = s_glCompressedTexSubImage2D;
    enc_ptr->glTexImage2D = s_glTexImage2D;
    enc_ptr->glTexSubImage2D = s_glTexSubImage2D;
    enc_ptr->glGetUniformIndices = s_glGetUniformIndices;
    enc_ptr->glVertexAttribIPointer = s_glVertexAttribIPointer;
    enc_ptr->glTransformFeedbackVaryings = s_glTransformFeedbackVaryings;
    enc_ptr->glTexImage3D = s_glTexImage3D;
    enc_ptr->glTexSubImage3D = s_glTexSubImage3D;
    enc_ptr->glCompressedTexImage3D = s_glCompressedTexImage3D;
    enc_ptr->glCompressedTexSubImage3D = s_glCompressedTexSubImage3D;
    enc_ptr->glDrawElementsInstanced = s_glDrawElementsInstanced;
    enc_ptr->glReadPixels = s_glReadPixels;

    enc_ptr->glCreateShaderProgramv = s_glCreateShaderProgramv;

    enc_ptr->glDrawArraysIndirect = s_glDrawArraysIndirect;

    enc_ptr->glDrawElementsIndirect = s_glDrawElementsIndirect;

    enc_ptr->glFenceSync = s_glFenceSync;
    enc_ptr->glClientWaitSync = s_glClientWaitSync;
    enc_ptr->glWaitSync = s_glWaitSync;
    enc_ptr->glIsSync = s_glIsSync;
    enc_ptr->glGetSynciv = s_glGetSynciv;
    enc_ptr->glDeleteSync = s_glDeleteSync;
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define OVERRIDE_DEC(func) enc_ptr->func = s_##func;
    // OVERRIDE_DEC(glCreateShader)
    // OVERRIDE_DEC(glCreateProgram)

    // OVERRIDE_DEC(glGenBuffers)

    // OVERRIDE_DEC(glGenFramebuffers)
    // OVERRIDE_DEC(glGenRenderbuffers)
    // OVERRIDE_DEC(glGenTextures)

    // OVERRIDE_DEC(glGenVertexArraysOES)
    // OVERRIDE_DEC(glGenVertexArrays)

    // OVERRIDE_DEC(glGenTransformFeedbacks)
    // OVERRIDE_DEC(glGenSamplers)
    // OVERRIDE_DEC(glGenQueries)
    // OVERRIDE_DEC(glGenProgramPipelines)

    // OVERRIDE_DEC(glDeleteShader)
    // OVERRIDE_DEC(glDeleteProgram)

    // OVERRIDE_DEC(glDeleteBuffers)
    // OVERRIDE_DEC(glDeleteFramebuffers)
    // OVERRIDE_DEC(glDeleteRenderbuffers)
    // OVERRIDE_DEC(glDeleteTextures)

    // OVERRIDE_DEC(glDeleteVertexArraysOES)
    // OVERRIDE_DEC(glDeleteVertexArrays)

    // OVERRIDE_DEC(glDeleteTransformFeedbacks)
    // OVERRIDE_DEC(glDeleteSamplers)
    // OVERRIDE_DEC(glDeleteQueries)
    // OVERRIDE_DEC(glDeleteProgramPipelines)

    // Shaders and programs
    // OVERRIDE_DEC(glCompileShader)
    // OVERRIDE_DEC(glAttachShader)
    // OVERRIDE_DEC(glDetachShader)
    // OVERRIDE_DEC(glLinkProgram)
    // OVERRIDE_DEC(glUseProgram)
    // OVERRIDE_DEC(glValidateProgram)
    // OVERRIDE_DEC(glIsShader)
    // OVERRIDE_DEC(glIsProgram)
    // OVERRIDE_DEC(glGetShaderiv)
    // OVERRIDE_DEC(glGetProgramiv)
    // OVERRIDE_DEC(glGetShaderInfoLog)
    // OVERRIDE_DEC(glGetProgramInfoLog)
    // OVERRIDE_DEC(glGetShaderSource)
    // OVERRIDE_DEC(glBindAttribLocation)
    // OVERRIDE_DEC(glGetActiveAttrib)
    // OVERRIDE_DEC(glGetActiveUniform)
    // OVERRIDE_DEC(glGetAttachedShaders)
    // OVERRIDE_DEC(glGetAttribLocation)
    // OVERRIDE_DEC(glGetUniformfv)
    // OVERRIDE_DEC(glGetUniformiv)
    // OVERRIDE_DEC(glGetUniformLocation)
    // OVERRIDE_DEC(glGetProgramBinaryOES)
    // OVERRIDE_DEC(glProgramBinaryOES)
    // OVERRIDE_DEC(glUniformBlockBinding)
    // OVERRIDE_DEC(glGetUniformBlockIndex)
    // OVERRIDE_DEC(glGetActiveUniformBlockiv)
    // OVERRIDE_DEC(glGetActiveUniformBlockName)
    // OVERRIDE_DEC(glGetUniformuiv)
    // OVERRIDE_DEC(glGetActiveUniformsiv)
    // OVERRIDE_DEC(glTransformFeedbackVaryings)
    // OVERRIDE_DEC(glGetTransformFeedbackVarying)
    // OVERRIDE_DEC(glProgramParameteri)
    // OVERRIDE_DEC(glProgramBinary)
    // OVERRIDE_DEC(glGetProgramBinary)
    // OVERRIDE_DEC(glGetFragDataLocation)
    // OVERRIDE_DEC(glUseProgramStages)
    // OVERRIDE_DEC(glActiveShaderProgram)
    // OVERRIDE_DEC(glProgramUniform1f)
    // OVERRIDE_DEC(glProgramUniform2f)
    // OVERRIDE_DEC(glProgramUniform3f)
    // OVERRIDE_DEC(glProgramUniform4f)
    // OVERRIDE_DEC(glProgramUniform1i)
    // OVERRIDE_DEC(glProgramUniform2i)
    // OVERRIDE_DEC(glProgramUniform3i)
    // OVERRIDE_DEC(glProgramUniform4i)
    // OVERRIDE_DEC(glProgramUniform1ui)
    // OVERRIDE_DEC(glProgramUniform2ui)
    // OVERRIDE_DEC(glProgramUniform3ui)
    // OVERRIDE_DEC(glProgramUniform4ui)
    // OVERRIDE_DEC(glProgramUniform1fv)
    // OVERRIDE_DEC(glProgramUniform2fv)
    // OVERRIDE_DEC(glProgramUniform3fv)
    // OVERRIDE_DEC(glProgramUniform4fv)
    // OVERRIDE_DEC(glProgramUniform1iv)
    // OVERRIDE_DEC(glProgramUniform2iv)
    // OVERRIDE_DEC(glProgramUniform3iv)
    // OVERRIDE_DEC(glProgramUniform4iv)
    // OVERRIDE_DEC(glProgramUniform1uiv)
    // OVERRIDE_DEC(glProgramUniform2uiv)
    // OVERRIDE_DEC(glProgramUniform3uiv)
    // OVERRIDE_DEC(glProgramUniform4uiv)
    // OVERRIDE_DEC(glProgramUniformMatrix2fv)
    // OVERRIDE_DEC(glProgramUniformMatrix3fv)
    // OVERRIDE_DEC(glProgramUniformMatrix4fv)
    // OVERRIDE_DEC(glProgramUniformMatrix2x3fv)
    // OVERRIDE_DEC(glProgramUniformMatrix3x2fv)
    // OVERRIDE_DEC(glProgramUniformMatrix2x4fv)
    // OVERRIDE_DEC(glProgramUniformMatrix4x2fv)
    // OVERRIDE_DEC(glProgramUniformMatrix3x4fv)
    // OVERRIDE_DEC(glProgramUniformMatrix4x3fv)
    // OVERRIDE_DEC(glGetProgramInterfaceiv)
    // OVERRIDE_DEC(glGetProgramResourceiv)
    // OVERRIDE_DEC(glGetProgramResourceIndex)
    // OVERRIDE_DEC(glGetProgramResourceLocation)
    // OVERRIDE_DEC(glGetProgramResourceName)
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OVERRIDE_DEC(glTexStorage3D)
    // OVERRIDE_DEC(glEnable)
    // OVERRIDE_DEC(glDisable)
    // OVERRIDE_DEC(glClearBufferiv)
    // OVERRIDE_DEC(glClearBufferuiv)
    // OVERRIDE_DEC(glClearBufferfv)
    // OVERRIDE_DEC(glBlitFramebuffer)
    // OVERRIDE_DEC(glGetInternalformativ)
    // OVERRIDE_DEC(glGenerateMipmap)
    // OVERRIDE_DEC(glBindSampler)
    // OVERRIDE_DEC(glGetIntegeri_v)
    // OVERRIDE_DEC(glGetInteger64i_v)
    // OVERRIDE_DEC(glGetProgramPipelineInfoLog)
        // OVERRIDE_DEC(glVertexAttribFormat)
        // OVERRIDE_DEC(glVertexAttribIFormat)
        // OVERRIDE_DEC(glVertexBindingDivisor)
        // OVERRIDE_DEC(glVertexAttribBinding)
        // OVERRIDE_DEC(glBindVertexBuffer)
        // OVERRIDE_DEC(glTexStorage2DMultisample)
        // OVERRIDE_DEC(glGetError)
        // OVERRIDE_DEC(glFlush)
            // OVERRIDE_DEC(glGetIntegerv)
            // OVERRIDE_DEC(glGetFloatv)
            // OVERRIDE_DEC(glGetBooleanv)
        // OVERRIDE_DEC(glGetInteger64v)
        // OVERRIDE_DEC(glGetBooleani_v)
        // OVERRIDE_DEC(glEnableVertexAttribArray)
        // OVERRIDE_DEC(glDisableVertexAttribArray)
    // OVERRIDE_DEC(glGetVertexAttribiv)
    // OVERRIDE_DEC(glGetVertexAttribfv)
    // OVERRIDE_DEC(glGetVertexAttribPointerv)
    // OVERRIDE_DEC(glFinish)
    // OVERRIDE_DEC(glUniform1f)
    // OVERRIDE_DEC(glUniform1fv)
    // OVERRIDE_DEC(glUniform1i)
    // OVERRIDE_DEC(glUniform1iv)
    // OVERRIDE_DEC(glUniform2f)
    // OVERRIDE_DEC(glUniform2fv)
    // OVERRIDE_DEC(glUniform2i)
    // OVERRIDE_DEC(glUniform2iv)
    // OVERRIDE_DEC(glUniform3f)
    // OVERRIDE_DEC(glUniform3fv)
    // OVERRIDE_DEC(glUniform3i)
    // OVERRIDE_DEC(glUniform3iv)
    // OVERRIDE_DEC(glUniform4f)
    // OVERRIDE_DEC(glUniform4fv)
    // OVERRIDE_DEC(glUniform4i)
    // OVERRIDE_DEC(glUniform4iv)
    // OVERRIDE_DEC(glUniformMatrix2fv)
    // OVERRIDE_DEC(glUniformMatrix3fv)
    // OVERRIDE_DEC(glUniformMatrix4fv)
    // OVERRIDE_DEC(glActiveTexture)
    // OVERRIDE_DEC(glBindTexture)
    // OVERRIDE_DEC(glGetTexParameterfv)
    // OVERRIDE_DEC(glGetTexParameteriv)
    // OVERRIDE_DEC(glTexParameterf)
    // OVERRIDE_DEC(glTexParameterfv)
    // OVERRIDE_DEC(glTexParameteri)
    // OVERRIDE_DEC(glTexParameteriv)
    // OVERRIDE_DEC(glCopyTexImage2D)
    // OVERRIDE_DEC(glBindRenderbuffer)
    // OVERRIDE_DEC(glRenderbufferStorage)
    // OVERRIDE_DEC(glFramebufferRenderbuffer)
    // OVERRIDE_DEC(glBindFramebuffer)
    // OVERRIDE_DEC(glFramebufferTexture2D)
    // OVERRIDE_DEC(glFramebufferTexture3DOES)
    // OVERRIDE_DEC(glGetFramebufferAttachmentParameteriv)
    // OVERRIDE_DEC(glCheckFramebufferStatus)
    // OVERRIDE_DEC(glBindVertexArray)
    // OVERRIDE_DEC(glBindBufferRange)
    // OVERRIDE_DEC(glBindBufferBase)
    // OVERRIDE_DEC(glCopyBufferSubData)
    // OVERRIDE_DEC(glGetBufferParameteriv)
    // OVERRIDE_DEC(glGetBufferParameteri64v)
    // OVERRIDE_DEC(glGetBufferPointerv)
    // OVERRIDE_DEC(glUniform1ui)
    // OVERRIDE_DEC(glUniform2ui)
    // OVERRIDE_DEC(glUniform3ui)
    // OVERRIDE_DEC(glUniform4ui)
    // OVERRIDE_DEC(glUniform1uiv)
    // OVERRIDE_DEC(glUniform2uiv)
    // OVERRIDE_DEC(glUniform3uiv)
    // OVERRIDE_DEC(glUniform4uiv)
    // OVERRIDE_DEC(glUniformMatrix2x3fv)
    // OVERRIDE_DEC(glUniformMatrix3x2fv)
    // OVERRIDE_DEC(glUniformMatrix2x4fv)
    // OVERRIDE_DEC(glUniformMatrix4x2fv)
    // OVERRIDE_DEC(glUniformMatrix3x4fv)
    // OVERRIDE_DEC(glUniformMatrix4x3fv)
    // OVERRIDE_DEC(glGetVertexAttribIiv)
    // OVERRIDE_DEC(glGetVertexAttribIuiv)
    // OVERRIDE_DEC(glVertexAttribDivisor)
    // OVERRIDE_DEC(glRenderbufferStorageMultisample)
    // OVERRIDE_DEC(glDrawBuffers)
    // OVERRIDE_DEC(glReadBuffer)
    // OVERRIDE_DEC(glFramebufferTextureLayer)
    // OVERRIDE_DEC(glTexStorage2D)
    // OVERRIDE_DEC(glBeginTransformFeedback)
    // OVERRIDE_DEC(glEndTransformFeedback)
    // OVERRIDE_DEC(glPauseTransformFeedback)
    // OVERRIDE_DEC(glResumeTransformFeedback)
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // You must run here code
    OVERRIDE_DEC(glPixelStorei)
    OVERRIDE_DEC(glBindBuffer)
    OVERRIDE_DEC(glBufferData)
    OVERRIDE_DEC(glBufferSubData)
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void GLESv2NativeFuncCall::s_glTexStorage3D(void* self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexStorage3D( target, levels, internalformat, width, height, depth);
}
void GLESv2NativeFuncCall::s_glEnable(void* self, GLenum what){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glEnable( what);
}
void GLESv2NativeFuncCall::s_glDisable(void* self, GLenum what){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDisable( what);
}
void GLESv2NativeFuncCall::s_glClearBufferiv(void* self, GLenum buffer, GLint drawBuffer, const GLint* value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glClearBufferiv( buffer, drawBuffer, value);
}
void GLESv2NativeFuncCall::s_glClearBufferuiv(void* self, GLenum buffer, GLint drawBuffer, const GLuint* value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glClearBufferuiv( buffer,  drawBuffer,  value);
}
void GLESv2NativeFuncCall::s_glClearBufferfv(void* self, GLenum buffer, GLint drawBuffer, const GLfloat* value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glClearBufferfv( buffer,  drawBuffer, value);
}
void GLESv2NativeFuncCall::s_glBlitFramebuffer(void* self, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, 
    GLbitfield mask, GLenum filter){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBlitFramebuffer( srcX0,  srcY0,  srcX1,  srcY1,  dstX0,  dstY0,  dstX1,  dstY1,  mask,  filter);
}
void GLESv2NativeFuncCall::s_glGetInternalformativ(void* self, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetInternalformativ( target,  internalformat,  pname,  bufSize,  params);
}
void GLESv2NativeFuncCall::s_glGenerateMipmap(void* self, GLenum target){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenerateMipmap( target);
}
void GLESv2NativeFuncCall::s_glBindSampler(void* self, GLuint unit, GLuint sampler){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindSampler( unit,  sampler);
}
void GLESv2NativeFuncCall::s_glGetIntegeri_v(void* self, GLenum target, GLuint index, GLint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetIntegeri_v( target, index,  params);
}
void GLESv2NativeFuncCall::s_glGetInteger64i_v(void* self, GLenum target, GLuint index, GLint64* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetInteger64i_v( target,  index,  params);
}
void GLESv2NativeFuncCall::s_glGetProgramPipelineInfoLog(void* self, GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetProgramPipelineInfoLog( pipeline,  bufSize,  length,  infoLog);
}
void GLESv2NativeFuncCall::s_glVertexAttribFormat(void* self, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribFormat( attribindex,  size,  type,  normalized,  relativeoffset);
}
void GLESv2NativeFuncCall::s_glVertexAttribIFormat(void* self, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribIFormat( attribindex,  size,  type,  relativeoffset);
}
void GLESv2NativeFuncCall::s_glVertexBindingDivisor(void* self, GLuint bindingindex, GLuint divisor){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexBindingDivisor( bindingindex,  divisor);
}
void GLESv2NativeFuncCall::s_glVertexAttribBinding(void* self, GLuint attribindex, GLuint bindingindex){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribBinding( attribindex,  bindingindex);
}
void GLESv2NativeFuncCall::s_glBindVertexBuffer(void* self, GLuint bindingindex, GLuint buffer, GLintptr offset, GLintptr stride){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindVertexBuffer( bindingindex,  buffer,  offset,  stride);
}
void GLESv2NativeFuncCall::s_glTexStorage2DMultisample(void* self, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, 
    GLboolean fixedsamplelocations){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexStorage2DMultisample( target,  samples,  internalformat,  width,  height,  fixedsamplelocations);
}
GLenum GLESv2NativeFuncCall::s_glGetError(void * self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glGetError();
}
void GLESv2NativeFuncCall::s_glFlush(void * self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFlush();
}
void GLESv2NativeFuncCall::s_glGetIntegerv(void *self, GLenum pname, GLint *ptr){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetIntegerv(pname, ptr);
}
void GLESv2NativeFuncCall::s_glGetFloatv(void *self, GLenum pname, GLfloat *ptr){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetFloatv( pname, ptr);
}
void GLESv2NativeFuncCall::s_glGetBooleanv(void *self, GLenum pname, GLboolean *ptr){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetBooleanv(pname, ptr);
}
void GLESv2NativeFuncCall::s_glGetInteger64v(void* self, GLenum param, GLint64* val){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetInteger64v( param, val);
}
void GLESv2NativeFuncCall::s_glGetBooleani_v(void* self, GLenum param, GLuint index, GLboolean* val){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetBooleani_v( param,  index,  val);
}
void GLESv2NativeFuncCall::s_glEnableVertexAttribArray(void *self, GLuint index){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glEnableVertexAttribArray( index);
}
void GLESv2NativeFuncCall::s_glDisableVertexAttribArray(void *self, GLuint index){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDisableVertexAttribArray( index);
}
void GLESv2NativeFuncCall::s_glGetVertexAttribiv(void *self, GLuint index, GLenum pname, GLint *params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetVertexAttribiv( index,  pname,  params);
}
void GLESv2NativeFuncCall::s_glGetVertexAttribfv(void *self, GLuint index, GLenum pname, GLfloat *params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetVertexAttribfv( index,  pname,  params);
}
void GLESv2NativeFuncCall::s_glGetVertexAttribPointerv(void *self, GLuint index, GLenum pname, GLvoid **pointer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetVertexAttribPointerv( index,  pname, pointer);
}
void GLESv2NativeFuncCall::s_glFinish(void *self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFinish();
}
void GLESv2NativeFuncCall::s_glUniform1f(void *self , GLint location, GLfloat x){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform1f( location,  x);
}
void GLESv2NativeFuncCall::s_glUniform1fv(void *self , GLint location, GLsizei count, const GLfloat* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform1fv( location,  count,  v);
}
void GLESv2NativeFuncCall::s_glUniform1i(void *self , GLint location, GLint x){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform1i( location,  x);
}
void GLESv2NativeFuncCall::s_glUniform1iv(void *self , GLint location, GLsizei count, const GLint* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform1iv( location,  count,  v);
}
void GLESv2NativeFuncCall::s_glUniform2f(void *self , GLint location, GLfloat x, GLfloat y){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform2f( location,  x,  y);
}
void GLESv2NativeFuncCall::s_glUniform2fv(void *self , GLint location, GLsizei count, const GLfloat* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform2fv( location,  count, v);
}
void GLESv2NativeFuncCall::s_glUniform2i(void *self , GLint location, GLint x, GLint y){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform2i( location,  x,  y);
}
void GLESv2NativeFuncCall::s_glUniform2iv(void *self , GLint location, GLsizei count, const GLint* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform2iv( location,  count, v);
}
void GLESv2NativeFuncCall::s_glUniform3f(void *self , GLint location, GLfloat x, GLfloat y, GLfloat z){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform3f( location,  x,  y,  z);
}
void GLESv2NativeFuncCall::s_glUniform3fv(void *self , GLint location, GLsizei count, const GLfloat* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform3fv( location,  count,  v);
}
void GLESv2NativeFuncCall::s_glUniform3i(void *self , GLint location, GLint x, GLint y, GLint z){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform3i( location,  x,  y, z);
}
void GLESv2NativeFuncCall::s_glUniform3iv(void *self , GLint location, GLsizei count, const GLint* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform3iv( location,  count,  v);
}
void GLESv2NativeFuncCall::s_glUniform4f(void *self , GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform4f( location,  x,  y,  z,  w);
}
void GLESv2NativeFuncCall::s_glUniform4fv(void *self , GLint location, GLsizei count, const GLfloat* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform4fv( location,  count,  v);
}
void GLESv2NativeFuncCall::s_glUniform4i(void *self , GLint location, GLint x, GLint y, GLint z, GLint w){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform4i( location,  x,  y,  z,  w);
}
void GLESv2NativeFuncCall::s_glUniform4iv(void *self , GLint location, GLsizei count, const GLint* v){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform4iv( location,  count, v);
}
void GLESv2NativeFuncCall::s_glUniformMatrix2fv(void *self , GLint location, GLsizei count, GLboolean transpose, const GLfloat* value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix2fv( location,  count,  transpose,  value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix3fv(void *self , GLint location, GLsizei count, GLboolean transpose, const GLfloat* value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix3fv( location,  count, transpose, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix4fv(void *self , GLint location, GLsizei count, GLboolean transpose, const GLfloat* value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix4fv( location,  count, transpose,  value);
}
void GLESv2NativeFuncCall::s_glActiveTexture(void* self, GLenum texture){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glActiveTexture( texture);
}
void GLESv2NativeFuncCall::s_glBindTexture(void* self, GLenum target, GLuint texture){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindTexture( target,  texture);
}
void GLESv2NativeFuncCall::s_glGetTexParameterfv(void* self, GLenum target, GLenum pname, GLfloat* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetTexParameterfv( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glGetTexParameteriv(void* self, GLenum target, GLenum pname, GLint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetTexParameteriv( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glTexParameterf(void* self, GLenum target, GLenum pname, GLfloat param){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexParameterf( target,  pname,  param);
}
void GLESv2NativeFuncCall::s_glTexParameterfv(void* self, GLenum target, GLenum pname, const GLfloat* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexParameterfv( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glTexParameteri(void* self, GLenum target, GLenum pname, GLint param){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexParameteri( target,  pname,  param);
}
void GLESv2NativeFuncCall::s_glTexParameteriv(void* self, GLenum target, GLenum pname, const GLint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexParameteriv( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glCopyTexImage2D(void* self, GLenum target, GLint level, GLenum internalformat,GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glCopyTexImage2D( target,  level,  internalformat, x,  y,  width,  height,  border);
}
void GLESv2NativeFuncCall::s_glBindRenderbuffer(void* self, GLenum target, GLuint renderbuffer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindRenderbuffer( target,  renderbuffer);
}
void GLESv2NativeFuncCall::s_glRenderbufferStorage(void* self, GLenum target, GLenum internalformat, GLsizei width, GLsizei height){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glRenderbufferStorage( target,  internalformat,  width,  height);
}
void GLESv2NativeFuncCall::s_glFramebufferRenderbuffer(void* self, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFramebufferRenderbuffer( target,  attachment,  renderbuffertarget,  renderbuffer);
}
void GLESv2NativeFuncCall::s_glBindFramebuffer(void* self, GLenum target, GLuint framebuffer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindFramebuffer( target,  framebuffer);
}
void GLESv2NativeFuncCall::s_glFramebufferTexture2D(void* self, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFramebufferTexture2D( target,  attachment,  textarget,  texture,  level);
}
void GLESv2NativeFuncCall::s_glFramebufferTexture3DOES(void* self, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFramebufferTexture3DOES( target,  attachment,  textarget,  texture,  level,  zoffset);
}
void GLESv2NativeFuncCall::s_glGetFramebufferAttachmentParameteriv(void* self, GLenum target, GLenum attachment, GLenum pname, GLint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetFramebufferAttachmentParameteriv( target,  attachment,  pname,  params);
}
GLenum GLESv2NativeFuncCall::s_glCheckFramebufferStatus(void* self,GLenum target){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glCheckFramebufferStatus( target);
}
void GLESv2NativeFuncCall::s_glBindVertexArray(void *self , GLuint array){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindVertexArray( array);
}
void GLESv2NativeFuncCall::s_glBindBufferRange(void *self , GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindBufferRange( target,  index,  buffer,  offset,  size);
}
void GLESv2NativeFuncCall::s_glBindBufferBase(void *self , GLenum target, GLuint index, GLuint buffer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindBufferBase( target,  index,  buffer);
}
void GLESv2NativeFuncCall::s_glCopyBufferSubData(void *self , GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glCopyBufferSubData( readtarget,  writetarget,  readoffset,  writeoffset,  size);
}
void GLESv2NativeFuncCall::s_glGetBufferParameteriv(void* self, GLenum target, GLenum pname, GLint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetBufferParameteriv( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glGetBufferParameteri64v(void* self, GLenum target, GLenum pname, GLint64* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetBufferParameteri64v( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glGetBufferPointerv(void* self, GLenum target, GLenum pname, GLvoid** params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetBufferPointerv( target,  pname,  params);
}
void GLESv2NativeFuncCall::s_glUniform1ui(void* self, GLint location, GLuint v0){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform1ui( location,  v0);
}
void GLESv2NativeFuncCall::s_glUniform2ui(void* self, GLint location, GLuint v0, GLuint v1){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform2ui( location,  v0,  v1);
}
void GLESv2NativeFuncCall::s_glUniform3ui(void* self, GLint location, GLuint v0, GLuint v1, GLuint v2){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform3ui( location,  v0,  v1,  v2);
}
void GLESv2NativeFuncCall::s_glUniform4ui(void* self, GLint location, GLint v0, GLuint v1, GLuint v2, GLuint v3){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform4ui( location,  v0,  v1,  v2,  v3);
}
void GLESv2NativeFuncCall::s_glUniform1uiv(void* self, GLint location, GLsizei count, const GLuint *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform1uiv( location,  count, value);
}
void GLESv2NativeFuncCall::s_glUniform2uiv(void* self, GLint location, GLsizei count, const GLuint *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform2uiv( location,  count, value);
}
void GLESv2NativeFuncCall::s_glUniform3uiv(void* self, GLint location, GLsizei count, const GLuint *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform3uiv( location,  count, value);
}
void GLESv2NativeFuncCall::s_glUniform4uiv(void* self, GLint location, GLsizei count, const GLuint *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniform4uiv( location,  count, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix2x3fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix2x3fv( location,  count,  transpose, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix3x2fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix3x2fv( location,  count,  transpose, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix2x4fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix2x4fv( location,  count,  transpose, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix4x2fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix4x2fv( location,  count,  transpose, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix3x4fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix3x4fv( location,  count,  transpose, value);
}
void GLESv2NativeFuncCall::s_glUniformMatrix4x3fv(void* self, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glUniformMatrix4x3fv( location,  count,  transpose, value);
}
void GLESv2NativeFuncCall::s_glGetVertexAttribIiv(void* self, GLuint index, GLenum pname, GLint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetVertexAttribIiv( index,  pname,  params);
}
void GLESv2NativeFuncCall::s_glGetVertexAttribIuiv(void* self, GLuint index, GLenum pname, GLuint* params){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetVertexAttribIuiv( index,  pname,  params);
}
void GLESv2NativeFuncCall::s_glVertexAttribDivisor(void* self, GLuint index, GLuint divisor){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribDivisor( index,  divisor);
}
void GLESv2NativeFuncCall::s_glRenderbufferStorageMultisample(void* self, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glRenderbufferStorageMultisample( target,  samples,  internalformat,  width,  height);
}
void GLESv2NativeFuncCall::s_glDrawBuffers(void* self, GLsizei n, const GLenum* bufs){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawBuffers( n,  bufs);
}
void GLESv2NativeFuncCall::s_glReadBuffer(void* self, GLenum src){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glReadBuffer( src);
}
void GLESv2NativeFuncCall::s_glFramebufferTextureLayer(void* self, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFramebufferTextureLayer( target,  attachment,  texture,  level,  layer);
}
void GLESv2NativeFuncCall::s_glTexStorage2D(void* self, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexStorage2D( target,  levels,  internalformat,  width,  height);
}
void GLESv2NativeFuncCall::s_glBeginTransformFeedback(void* self, GLenum primitiveMode){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBeginTransformFeedback( primitiveMode);
}
void GLESv2NativeFuncCall::s_glEndTransformFeedback(void* self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glEndTransformFeedback();
}
void GLESv2NativeFuncCall::s_glPauseTransformFeedback(void* self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glPauseTransformFeedback();
}
void GLESv2NativeFuncCall::s_glResumeTransformFeedback(void* self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glResumeTransformFeedback();
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void GLESv2NativeFuncCall::s_glPixelStorei(void *self, GLenum param, GLint value){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glPixelStorei(param, value);
}
void GLESv2NativeFuncCall::s_glBindBuffer(void *self, GLenum target, GLuint id){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBindBuffer(target, id);
}
void GLESv2NativeFuncCall::s_glBufferData(void *self, GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBufferData(target, size,  data, usage);
}
void GLESv2NativeFuncCall::s_glBufferSubData(void *self, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glBufferSubData(target, offset, size, data);
}
const GLubyte* GLESv2NativeFuncCall::s_glGetString(void *self, GLenum name){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glGetString(name);
}
const GLubyte* GLESv2NativeFuncCall::s_glGetStringi(void * self, GLenum name, GLuint index){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glGetStringi(name, index);
}
void GLESv2NativeFuncCall::s_glEGLImageTargetTexture2DOES(void * self, GLenum target, GLeglImageOES image){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glEGLImageTargetTexture2DOES(target,image);
}
void GLESv2NativeFuncCall::s_glEGLImageTargetRenderbufferStorageOES(void *self, GLenum target, GLeglImageOES image){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glEGLImageTargetRenderbufferStorageOES(target,image);
}
void* GLESv2NativeFuncCall::s_glMapBufferOES(void *self, GLenum target, GLenum access){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glMapBufferOES(target, access);
}
void GLESv2NativeFuncCall::s_glGetCompressedTextureFormats(void *self, int count, GLint *formats){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetCompressedTextureFormats(count, formats);
}
void GLESv2NativeFuncCall::s_glVertexAttribPointer(void *self, GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}
void GLESv2NativeFuncCall::s_glDrawArrays(void *self, GLenum mode, GLint first, GLsizei count){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawArrays( mode,  first,  count);
}
void GLESv2NativeFuncCall::s_glDrawArraysInstanced(void *self, GLenum mode, GLint first, GLsizei count, GLsizei primcount){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawArraysInstanced( mode,  first,  count,  primcount);
}
void GLESv2NativeFuncCall::s_glDrawRangeElements(void *self, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawRangeElements( mode,  start,  end,  count,  type,  indices);
}
void GLESv2NativeFuncCall::s_glDrawElements(void *self, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElements(mode, count, type, indices);
}
int  GLESv2NativeFuncCall::s_glFinishRoundTrip(void *self){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glFinishRoundTrip();
}
void* GLESv2NativeFuncCall::s_glMapBufferRange(void* self, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glMapBufferRange(target, offset, length, access);
}
GLboolean GLESv2NativeFuncCall::s_glUnmapBuffer(void* self, GLenum target){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glUnmapBuffer(target);
}
void GLESv2NativeFuncCall::s_glFlushMappedBufferRange(void* self, GLenum target, GLintptr offset, GLsizeiptr length){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFlushMappedBufferRange(target, offset, length);
}
void GLESv2NativeFuncCall::s_glCompressedTexImage2D(void* self, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, 
    GLsizei imageSize, const GLvoid* data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glCompressedTexImage2D( target,  level,  internalformat,  width,  height,  border,  imageSize,  data);
}
void GLESv2NativeFuncCall::s_glCompressedTexSubImage2D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, 
    GLenum format, GLsizei imageSize, const GLvoid* data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glCompressedTexSubImage2D( target,  level,  xoffset,  yoffset,  width,  height,  format,  imageSize,  data);
}
void GLESv2NativeFuncCall::s_glTexImage2D(void* self, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, 
    GLenum type, const GLvoid* pixels){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexImage2D( target,  level,  internalformat,  width,  height,  border,  format,  type,  pixels);
}
void GLESv2NativeFuncCall::s_glTexSubImage2D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, 
    GLenum type, const GLvoid* pixels){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexSubImage2D( target,  level,  xoffset,  yoffset,  width,  height,  format,  type,  pixels);
}
void GLESv2NativeFuncCall::s_glVertexAttribIPointer(void *self, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribIPointer( index,  size,  type,  stride, pointer);
}
void GLESv2NativeFuncCall::s_glTexImage3D(void* self, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, 
    GLenum format, GLenum type, const GLvoid* data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexImage3D( target,  level,  internalFormat,  width,  height,  depth,  border,  format,  type,  data);
}
void GLESv2NativeFuncCall::s_glTexSubImage3D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, 
    GLsizei depth, GLenum format, GLenum type, const GLvoid* data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glTexSubImage3D( target,  level,  xoffset,  yoffset,  zoffset,  width,  height,  depth,  format, type,  data);
}
void GLESv2NativeFuncCall::s_glCompressedTexImage3D(void* self, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, 
    GLint border, GLsizei imageSize, const GLvoid* data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glCompressedTexImage3D( target,  level,  internalformat,  width,  height,  depth,  border,  imageSize,  data);
}
void GLESv2NativeFuncCall::s_glCompressedTexSubImage3D(void* self, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, 
    GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glCompressedTexSubImage3D( target,  level,  xoffset,  yoffset,  zoffset,  width,  height,  depth,  format,  imageSize, data);
}
void GLESv2NativeFuncCall::s_glDrawElementsInstanced(void* self, GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElementsInstanced( mode,  count,  type, indices, primcount);
}
void GLESv2NativeFuncCall::s_glGetUniformIndices(void* self, GLuint program, GLsizei uniformCount, const GLchar** var3, GLuint* uniformIndices){
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetUniformIndices( program,  uniformCount, var3, uniformIndices);
}

void GLESv2NativeFuncCall::s_glReadPixels(void* self, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glReadPixels(x, y, width, height, format, type, pixels);
}
GLuint GLESv2NativeFuncCall::s_glCreateShaderProgramv(void* self, GLenum type, GLsizei count, const char** var3) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glCreateShaderProgramv(type, count, var3);
}
void GLESv2NativeFuncCall::s_glDrawArraysIndirect(void* self, GLenum mode, const void* indirect) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawArraysIndirect(mode, indirect);
}
void GLESv2NativeFuncCall::s_glDrawElementsIndirect(void* self, GLenum mode, GLenum type, const void* indirect) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElementsIndirect(mode, type, indirect);
}
GLsync GLESv2NativeFuncCall::s_glFenceSync(void* self, GLenum condition, GLbitfield flags) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glFenceSync(condition, flags);
}
GLenum GLESv2NativeFuncCall::s_glClientWaitSync(void* self, GLsync wait_on, GLbitfield flags, GLuint64 timeout) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glClientWaitSync(wait_on, flags, timeout);
}
void GLESv2NativeFuncCall::s_glWaitSync(void* self, GLsync wait_on, GLbitfield flags, GLuint64 timeout) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glWaitSync(wait_on, flags, timeout);
}
void GLESv2NativeFuncCall::s_glDeleteSync(void* self, GLsync to_delete) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteSync(to_delete);
}
GLboolean GLESv2NativeFuncCall::s_glIsSync(void* self, GLsync sync) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glIsSync(sync);
}
void GLESv2NativeFuncCall::s_glGetSynciv(void* self, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetSynciv(sync, pname, bufSize, length, values);
}
GLuint GLESv2NativeFuncCall::s_glCreateShader(void* self, GLenum shaderType) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    GLuint shader = ctx->glCreateShader(shaderType);

    return shader;
}
GLuint GLESv2NativeFuncCall::s_glCreateProgram(void* self) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glCreateProgram();
}
void GLESv2NativeFuncCall::s_glGenBuffers(void* self, GLsizei n, GLuint* buffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenBuffers(n, buffers);
}
void GLESv2NativeFuncCall::s_glGenFramebuffers(void* self, GLsizei n, GLuint* framebuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenFramebuffers(n, framebuffers);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glGenRenderbuffers(void* self, GLsizei n, GLuint* renderbuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenRenderbuffers(n, renderbuffers);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glGenTextures(void* self, GLsizei n, GLuint* textures) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenTextures(n, textures);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glGenVertexArraysOES(void* self, GLsizei n, GLuint* arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenVertexArraysOES(n, arrays);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glGenVertexArrays(void* self, GLsizei n, GLuint* arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenVertexArrays(n, arrays);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glGenTransformFeedbacks(void* self, GLsizei n, GLuint* transformFeedbacks) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenTransformFeedbacks(n, transformFeedbacks);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glGenSamplers(void* self, GLsizei n, GLuint* samplers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenSamplers(n, samplers);
    // TODO: Snapshot names

}
void GLESv2NativeFuncCall::s_glGenQueries(void* self, GLsizei n, GLuint* queries) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenQueries(n, queries);
    // TODO: Snapshot names

}
void GLESv2NativeFuncCall::s_glGenProgramPipelines(void* self, GLsizei n, GLuint* pipelines) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenProgramPipelines(n, pipelines);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteShader(void* self, GLuint shader) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteShader(shader);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteProgram(void* self, GLuint program) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteProgram(program);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteBuffers(void* self, GLsizei n, const GLuint *buffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteBuffers(n, buffers);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteFramebuffers(void* self, GLsizei n, const GLuint *framebuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteFramebuffers(n, framebuffers);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteRenderbuffers(void* self, GLsizei n, const GLuint *renderbuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteRenderbuffers(n, renderbuffers);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteTextures(void* self, GLsizei n, const GLuint *textures) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteTextures(n, textures);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteVertexArraysOES(void* self, GLsizei n, const GLuint *arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteVertexArraysOES(n, arrays);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteVertexArrays(void* self, GLsizei n, const GLuint *arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteVertexArrays(n, arrays);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteTransformFeedbacks(void* self, GLsizei n, const GLuint *transformFeedbacks) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteTransformFeedbacks(n, transformFeedbacks);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteSamplers(void* self, GLsizei n, const GLuint *samplers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteSamplers(n, samplers);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteQueries(void* self, GLsizei n, const GLuint *queries) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteQueries(n, queries);
    // TODO: Snapshot names
}
void GLESv2NativeFuncCall::s_glDeleteProgramPipelines(void* self, GLsizei n, const GLuint *pipelines) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteProgramPipelines(n, pipelines);
    // TODO: Snapshot names
}

#define SNAPSHOT_PROGRAM_NAME(x) \
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr(); \


#define SNAPSHOT_PROGRAM_NAME2(x,y) \
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr(); \


#define SNAPSHOT_SHADER_CALL(funcname,argtypes,args) \
void GLESv2NativeFuncCall::s_##funcname argtypes { \
    SNAPSHOT_PROGRAM_NAME(shader) \
    ctx-> funcname args ; \
} \

#define SNAPSHOT_PROGRAM_CALL(funcname,argtypes,args) \
void GLESv2NativeFuncCall::s_##funcname argtypes  { \
    SNAPSHOT_PROGRAM_NAME(program) \
    ctx-> funcname args ; \
} \


#define SNAPSHOT_PROGRAM_CALL_RET(rettype, funcname, argtypes, args) \
rettype GLESv2NativeFuncCall::s_##funcname argtypes  { \
    SNAPSHOT_PROGRAM_NAME(program) \
    return ctx-> funcname args; \
} \


void GLESv2NativeFuncCall::s_glShaderSource(void *self, GLuint shader, GLsizei count, const GLchar*const* string, const GLint* length)
{
    SNAPSHOT_PROGRAM_NAME(shader);

    ctx->glShaderSource(shader, count, string, length);
}
void GLESv2NativeFuncCall::s_glAttachShader(void* self, GLuint program, GLuint shader) {
    SNAPSHOT_PROGRAM_NAME2(program, shader)
    ctx->glAttachShader(program, shader);
}
void GLESv2NativeFuncCall::s_glDetachShader(void* self, GLuint program, GLuint shader) {
    SNAPSHOT_PROGRAM_NAME2(program, shader)
    ctx->glDetachShader(program, shader);
}
GLboolean GLESv2NativeFuncCall::s_glIsShader(void* self, GLuint shader) {
    SNAPSHOT_PROGRAM_NAME(shader);
    return ctx->glIsShader(shader);
}
GLboolean GLESv2NativeFuncCall::s_glIsProgram(void* self, GLuint program) {
    SNAPSHOT_PROGRAM_NAME(program);
    return ctx->glIsProgram(program);
}
SNAPSHOT_SHADER_CALL(glCompileShader, (void* self,  GLuint shader), (shader))
SNAPSHOT_SHADER_CALL(glGetShaderiv, (void* self,  GLuint shader, GLenum pname, GLint* params), (shader, pname, params))
SNAPSHOT_SHADER_CALL(glGetShaderInfoLog, (void* self,  GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog), (shader, bufsize, length, infolog))
SNAPSHOT_SHADER_CALL(glGetShaderSource, (void* self,  GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source), (shader, bufsize, length, source))
SNAPSHOT_PROGRAM_CALL(glLinkProgram, (void* self,  GLuint program), (program))
SNAPSHOT_PROGRAM_CALL(glUseProgram, (void* self,  GLuint program), (program))
SNAPSHOT_PROGRAM_CALL(glValidateProgram, (void* self,  GLuint program), (program))
SNAPSHOT_PROGRAM_CALL(glGetProgramiv, (void* self,  GLuint program, GLenum pname, GLint* params), (program, pname, params))
SNAPSHOT_PROGRAM_CALL(glGetProgramInfoLog, (void* self,  GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog), (program, bufsize, length, infolog))
SNAPSHOT_PROGRAM_CALL(glBindAttribLocation, (void* self,  GLuint program, GLuint index, const GLchar* name), (program, index, name))
SNAPSHOT_PROGRAM_CALL(glGetActiveAttrib, (void* self,  GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name), (program, index, bufsize, length, size, type, name))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniform, (void* self,  GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name), (program, index, bufsize, length, size, type, name))
SNAPSHOT_PROGRAM_CALL(glGetAttachedShaders, (void* self,  GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders), (program, maxcount, count, shaders))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetAttribLocation, (void* self,  GLuint program, const GLchar* name), (program, name))
SNAPSHOT_PROGRAM_CALL(glGetUniformfv, (void* self,  GLuint program, GLint location, GLfloat* params), (program, location, params))
SNAPSHOT_PROGRAM_CALL(glGetUniformiv, (void* self,  GLuint program, GLint location, GLint* params), (program, location, params))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetUniformLocation, (void* self,  GLuint program, const GLchar* name), (program, name))
SNAPSHOT_PROGRAM_CALL(glGetProgramBinaryOES, (void* self,  GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary), (program, bufSize, length, binaryFormat, binary))
SNAPSHOT_PROGRAM_CALL(glProgramBinaryOES, (void* self,  GLuint program, GLenum binaryFormat, const GLvoid* binary, GLint length), (program, binaryFormat, binary, length))
SNAPSHOT_PROGRAM_CALL(glUniformBlockBinding, (void* self,  GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding), (program, uniformBlockIndex, uniformBlockBinding))
SNAPSHOT_PROGRAM_CALL_RET(GLuint, glGetUniformBlockIndex, (void* self,  GLuint program, const GLchar* uniformBlockName), (program, uniformBlockName))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniformBlockiv, (void* self,  GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params), (program, uniformBlockIndex, pname, params))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniformBlockName, (void* self,  GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName), (program, uniformBlockIndex, bufSize, length, uniformBlockName))
SNAPSHOT_PROGRAM_CALL(glGetUniformuiv, (void* self,  GLuint program, GLint location, GLuint* params), (program, location, params))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniformsiv, (void* self,  GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params), (program, uniformCount, uniformIndices, pname, params))
SNAPSHOT_PROGRAM_CALL(glTransformFeedbackVaryings, (void* self,  GLuint program, GLsizei count, const char** var3, GLenum bufferMode), (program, count, var3, bufferMode))
SNAPSHOT_PROGRAM_CALL(glGetTransformFeedbackVarying, (void* self,  GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, char* name), (program, index, bufSize, length, size, type, name))
SNAPSHOT_PROGRAM_CALL(glProgramParameteri, (void* self,  GLuint program, GLenum pname, GLint value), (program, pname, value))
SNAPSHOT_PROGRAM_CALL(glProgramBinary, (void* self,  GLuint program, GLenum binaryFormat, const void* binary, GLsizei length), (program, binaryFormat, binary, length))
SNAPSHOT_PROGRAM_CALL(glGetProgramBinary, (void* self,  GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary), (program, bufSize, length, binaryFormat, binary))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetFragDataLocation, (void* self,  GLuint program, const char* name), (program, name))
SNAPSHOT_PROGRAM_CALL(glUseProgramStages, (void* self,  GLuint pipeline, GLbitfield stages, GLuint program), (pipeline, stages, program))
SNAPSHOT_PROGRAM_CALL(glActiveShaderProgram, (void* self,  GLuint pipeline, GLuint program), (pipeline, program))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1f, (void* self,  GLuint program, GLint location, GLfloat v0), (program, location, v0))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2f, (void* self,  GLuint program, GLint location, GLfloat v0, GLfloat v1), (program, location, v0, v1))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3f, (void* self,  GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2), (program, location, v0, v1, v2))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4f, (void* self,  GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3), (program, location, v0, v1, v2, v3))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1i, (void* self,  GLuint program, GLint location, GLint v0), (program, location, v0))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2i, (void* self,  GLuint program, GLint location, GLint v0, GLint v1), (program, location, v0, v1))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3i, (void* self,  GLuint program, GLint location, GLint v0, GLint v1, GLint v2), (program, location, v0, v1, v2))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4i, (void* self,  GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3), (program, location, v0, v1, v2, v3))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1ui, (void* self,  GLuint program, GLint location, GLuint v0), (program, location, v0))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2ui, (void* self,  GLuint program, GLint location, GLint v0, GLuint v1), (program, location, v0, v1))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3ui, (void* self,  GLuint program, GLint location, GLint v0, GLint v1, GLuint v2), (program, location, v0, v1, v2))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4ui, (void* self,  GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLuint v3), (program, location, v0, v1, v2, v3))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1fv, (void* self,  GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2fv, (void* self,  GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3fv, (void* self,  GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4fv, (void* self,  GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1iv, (void* self,  GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2iv, (void* self,  GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3iv, (void* self,  GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4iv, (void* self,  GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1uiv, (void* self,  GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2uiv, (void* self,  GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3uiv, (void* self,  GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4uiv, (void* self,  GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix2fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix3fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix4fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix2x3fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix3x2fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix2x4fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix4x2fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix3x4fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix4x3fv, (void* self,  GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glGetProgramInterfaceiv, (void* self,  GLuint program, GLenum programInterface, GLenum pname, GLint* params), (program, programInterface, pname, params))
SNAPSHOT_PROGRAM_CALL(glGetProgramResourceiv, (void* self,  GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params), (program, programInterface, index, propCount, props, bufSize, length, params))
SNAPSHOT_PROGRAM_CALL_RET(GLuint, glGetProgramResourceIndex, (void* self, GLuint program, GLenum programInterface, const char * name), (program, programInterface, name))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetProgramResourceLocation, (void* self, GLuint program, GLenum programInterface, const char * name), (program, programInterface, name))
SNAPSHOT_PROGRAM_CALL(glGetProgramResourceName, (void* self,  GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, char* name), (program, programInterface, index, bufSize, length, name))
