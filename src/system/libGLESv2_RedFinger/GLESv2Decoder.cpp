/*
* Copyright 2011 The Android Open Source Project
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

#include "GLESv2Decoder.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>

#include <string>
#include <vector>

#include <string.h>
#include "GLESv2ThreadInfo.h"
#include "ErrorLog.h"

static inline void* SafePointerFromUInt(GLuint value) {
  return (void*)(uintptr_t)value;
}

GLESv2Decoder::GLESv2Decoder()
{
    m_contextData = NULL;
    m_snapshot = NULL;
    glVertexAttribPointerWithDataSize = NULL;
    
}

GLESv2Decoder::~GLESv2Decoder(){
}

#define OVERRIDE_DEC(func) func = s_##func;

int GLESv2Decoder::initGL()
{
    glGetCompressedTextureFormats = s_glGetCompressedTextureFormats;
    glVertexAttribPointerData = s_glVertexAttribPointerData;
    glVertexAttribPointerOffset = s_glVertexAttribPointerOffset;
    // glShaderString = s_glShaderString;

    glDrawElementsOffset = s_glDrawElementsOffset;
    glDrawElementsData = s_glDrawElementsData;
    glFinishRoundTrip = s_glFinishRoundTrip;
    glMapBufferRangeAEMU = s_glMapBufferRangeAEMU;
    glUnmapBufferAEMU = s_glUnmapBufferAEMU;
    glFlushMappedBufferRangeAEMU = s_glFlushMappedBufferRangeAEMU;
    glCompressedTexImage2DOffsetAEMU = s_glCompressedTexImage2DOffsetAEMU;
    glCompressedTexSubImage2DOffsetAEMU = s_glCompressedTexSubImage2DOffsetAEMU;
    glTexImage2DOffsetAEMU = s_glTexImage2DOffsetAEMU;
    glTexSubImage2DOffsetAEMU = s_glTexSubImage2DOffsetAEMU;
    glGetUniformIndicesAEMU = s_glGetUniformIndicesAEMU;
    glVertexAttribIPointerDataAEMU = s_glVertexAttribIPointerDataAEMU;
    glVertexAttribIPointerOffsetAEMU = s_glVertexAttribIPointerOffsetAEMU;
    glTransformFeedbackVaryingsAEMU = s_glTransformFeedbackVaryingsAEMU;
    glTexImage3DOffsetAEMU = s_glTexImage3DOffsetAEMU;
    glTexSubImage3DOffsetAEMU = s_glTexSubImage3DOffsetAEMU;
    glCompressedTexImage3DOffsetAEMU = s_glCompressedTexImage3DOffsetAEMU;
    glCompressedTexSubImage3DOffsetAEMU = s_glCompressedTexSubImage3DOffsetAEMU;
    glDrawElementsInstancedOffsetAEMU = s_glDrawElementsInstancedOffsetAEMU;
    glDrawElementsInstancedDataAEMU = s_glDrawElementsInstancedDataAEMU;
    glReadPixelsOffsetAEMU = s_glReadPixelsOffsetAEMU;

    glCreateShaderProgramvAEMU = s_glCreateShaderProgramvAEMU;

    glDrawArraysIndirectDataAEMU = s_glDrawArraysIndirectDataAEMU;
    glDrawArraysIndirectOffsetAEMU = s_glDrawArraysIndirectOffsetAEMU;

    glDrawElementsIndirectDataAEMU = s_glDrawElementsIndirectDataAEMU;
    glDrawElementsIndirectOffsetAEMU = s_glDrawElementsIndirectOffsetAEMU;

    glFenceSyncAEMU = s_glFenceSyncAEMU;
    glClientWaitSyncAEMU = s_glClientWaitSyncAEMU;
    glWaitSyncAEMU = s_glWaitSyncAEMU;
    glIsSyncAEMU = s_glIsSyncAEMU;
    glGetSyncivAEMU = s_glGetSyncivAEMU;
    glDeleteSyncAEMU = s_glDeleteSyncAEMU;

    OVERRIDE_DEC(glCreateShader)
    OVERRIDE_DEC(glCreateProgram)

    OVERRIDE_DEC(glGenBuffers)

    OVERRIDE_DEC(glGenFramebuffers)
    OVERRIDE_DEC(glGenRenderbuffers)
    OVERRIDE_DEC(glGenTextures)

    OVERRIDE_DEC(glGenVertexArraysOES)
    OVERRIDE_DEC(glGenVertexArrays)

    OVERRIDE_DEC(glGenTransformFeedbacks)
    OVERRIDE_DEC(glGenSamplers)
    OVERRIDE_DEC(glGenQueries)
    OVERRIDE_DEC(glGenProgramPipelines)

    OVERRIDE_DEC(glDeleteShader)
    OVERRIDE_DEC(glDeleteProgram)

    OVERRIDE_DEC(glDeleteBuffers)
    OVERRIDE_DEC(glDeleteFramebuffers)
    OVERRIDE_DEC(glDeleteRenderbuffers)
    OVERRIDE_DEC(glDeleteTextures)

    OVERRIDE_DEC(glDeleteVertexArraysOES)
    OVERRIDE_DEC(glDeleteVertexArrays)

    OVERRIDE_DEC(glDeleteTransformFeedbacks)
    OVERRIDE_DEC(glDeleteSamplers)
    OVERRIDE_DEC(glDeleteQueries)
    OVERRIDE_DEC(glDeleteProgramPipelines)

    // Shaders and programs
    OVERRIDE_DEC(glCompileShader)
    OVERRIDE_DEC(glAttachShader)
    OVERRIDE_DEC(glDetachShader)
    OVERRIDE_DEC(glLinkProgram)
    OVERRIDE_DEC(glUseProgram)
    OVERRIDE_DEC(glValidateProgram)
    OVERRIDE_DEC(glIsShader)
    OVERRIDE_DEC(glIsProgram)
    OVERRIDE_DEC(glGetShaderiv)
    OVERRIDE_DEC(glGetProgramiv)
    OVERRIDE_DEC(glGetShaderInfoLog)
    OVERRIDE_DEC(glGetProgramInfoLog)
    OVERRIDE_DEC(glGetShaderSource)
    OVERRIDE_DEC(glBindAttribLocation)
    OVERRIDE_DEC(glGetActiveAttrib)
    OVERRIDE_DEC(glGetActiveUniform)
    OVERRIDE_DEC(glGetAttachedShaders)
    OVERRIDE_DEC(glGetAttribLocation)
    OVERRIDE_DEC(glGetUniformfv)
    OVERRIDE_DEC(glGetUniformiv)
    OVERRIDE_DEC(glGetUniformLocation)
    OVERRIDE_DEC(glGetProgramBinaryOES)
    OVERRIDE_DEC(glProgramBinaryOES)
    OVERRIDE_DEC(glUniformBlockBinding)
    OVERRIDE_DEC(glGetUniformBlockIndex)
    OVERRIDE_DEC(glGetActiveUniformBlockiv)
    OVERRIDE_DEC(glGetActiveUniformBlockName)
    OVERRIDE_DEC(glGetUniformuiv)
    OVERRIDE_DEC(glGetActiveUniformsiv)
    OVERRIDE_DEC(glTransformFeedbackVaryings)
    OVERRIDE_DEC(glGetTransformFeedbackVarying)
    OVERRIDE_DEC(glProgramParameteri)
    OVERRIDE_DEC(glProgramBinary)
    OVERRIDE_DEC(glGetProgramBinary)
    OVERRIDE_DEC(glGetFragDataLocation)
    OVERRIDE_DEC(glUseProgramStages)
    OVERRIDE_DEC(glActiveShaderProgram)
    OVERRIDE_DEC(glProgramUniform1f)
    OVERRIDE_DEC(glProgramUniform2f)
    OVERRIDE_DEC(glProgramUniform3f)
    OVERRIDE_DEC(glProgramUniform4f)
    OVERRIDE_DEC(glProgramUniform1i)
    OVERRIDE_DEC(glProgramUniform2i)
    OVERRIDE_DEC(glProgramUniform3i)
    OVERRIDE_DEC(glProgramUniform4i)
    OVERRIDE_DEC(glProgramUniform1ui)
    OVERRIDE_DEC(glProgramUniform2ui)
    OVERRIDE_DEC(glProgramUniform3ui)
    OVERRIDE_DEC(glProgramUniform4ui)
    OVERRIDE_DEC(glProgramUniform1fv)
    OVERRIDE_DEC(glProgramUniform2fv)
    OVERRIDE_DEC(glProgramUniform3fv)
    OVERRIDE_DEC(glProgramUniform4fv)
    OVERRIDE_DEC(glProgramUniform1iv)
    OVERRIDE_DEC(glProgramUniform2iv)
    OVERRIDE_DEC(glProgramUniform3iv)
    OVERRIDE_DEC(glProgramUniform4iv)
    OVERRIDE_DEC(glProgramUniform1uiv)
    OVERRIDE_DEC(glProgramUniform2uiv)
    OVERRIDE_DEC(glProgramUniform3uiv)
    OVERRIDE_DEC(glProgramUniform4uiv)
    OVERRIDE_DEC(glProgramUniformMatrix2fv)
    OVERRIDE_DEC(glProgramUniformMatrix3fv)
    OVERRIDE_DEC(glProgramUniformMatrix4fv)
    OVERRIDE_DEC(glProgramUniformMatrix2x3fv)
    OVERRIDE_DEC(glProgramUniformMatrix3x2fv)
    OVERRIDE_DEC(glProgramUniformMatrix2x4fv)
    OVERRIDE_DEC(glProgramUniformMatrix4x2fv)
    OVERRIDE_DEC(glProgramUniformMatrix3x4fv)
    OVERRIDE_DEC(glProgramUniformMatrix4x3fv)
    OVERRIDE_DEC(glGetProgramInterfaceiv)
    OVERRIDE_DEC(glGetProgramResourceiv)
    OVERRIDE_DEC(glGetProgramResourceIndex)
    OVERRIDE_DEC(glGetProgramResourceLocation)
    OVERRIDE_DEC(glGetProgramResourceName)

    return 0;

}

int GLESv2Decoder::s_glFinishRoundTrip()
{
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glFinish();
    return 0;
}

void GLESv2Decoder::s_glGetCompressedTextureFormats(int count, GLint *formats)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();

    int nFormats;
    ctx->glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &nFormats);
    if (nFormats > count) {
        fprintf(stderr, "%s: GetCompressedTextureFormats: The requested number of formats does not match the number that is reported by OpenGL\n", __FUNCTION__);
    } else {
        ctx->glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats);
    }
}

void GLESv2Decoder::s_glVertexAttribPointerData(GLuint indx, GLint size, GLenum type,
                                             GLboolean normalized, GLsizei stride,  void * data, GLuint datalen)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    if (ctx->m_contextData != NULL) {
        ctx->m_contextData->storePointerData(indx, data, datalen);
        // note - the stride of the data is always zero when it comes out of the codec.
        // See gl2.attrib for the packing function call.
        if ((void*)ctx->glVertexAttribPointerWithDataSize != NULL) {
            ctx->glVertexAttribPointerWithDataSize(indx, size, type, normalized,
                    0, ctx->m_contextData->pointerData(indx), datalen);
        } else {
            // ALOGD("%s:%s:%d:GLuint indx %p, GLint size %p, GLenum type %p, GLboolean normalized %p, GLsizei stride %p, const GLvoid* ptr %p\n", 
            //     __FILE__, __FUNCTION__, __LINE__, indx,size,type,normalized,stride,data);
            ctx->glVertexAttribPointer(indx, size, type, normalized, 0,
                    ctx->m_contextData->pointerData(indx));
        }
    }
}

void GLESv2Decoder::s_glVertexAttribPointerOffset(GLuint indx, GLint size, GLenum type,
                                               GLboolean normalized, GLsizei stride,  GLuint data)
{
    // ALOGD("%s:%s:%d:GLuint indx %p, GLint size %p, GLenum type %p, GLboolean normalized %p, GLsizei stride %p, const GLvoid* ptr %p\n", 
    //     __FILE__, __FUNCTION__, __LINE__, indx,size,type,normalized,stride,data);
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribPointer(indx, size, type, normalized, stride, SafePointerFromUInt(data));
}


void GLESv2Decoder::s_glDrawElementsData(GLenum mode, GLsizei count, GLenum type, void * data, GLuint datalen)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElements(mode, count, type, data);
}


void GLESv2Decoder::s_glDrawElementsOffset(GLenum mode, GLsizei count, GLenum type, GLuint offset)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElements(mode, count, type, SafePointerFromUInt(offset));
}

void GLESv2Decoder::s_glMapBufferRangeAEMU(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, void* mapped)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    if ((access & GL_MAP_READ_BIT) ||
        ((access & GL_MAP_WRITE_BIT) &&
         (!(access & GL_MAP_INVALIDATE_RANGE_BIT) &&
          !(access & GL_MAP_INVALIDATE_BUFFER_BIT)))) {
        void* gpu_ptr = ctx->glMapBufferRange(target, offset, length, access);
        memcpy(mapped, gpu_ptr, length);
        ctx->glUnmapBuffer(target);
    } else {
        // if writing while not wanting to preserve previous contents,
        // let |mapped| stay as garbage.
    }
}

void GLESv2Decoder::s_glUnmapBufferAEMU(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, void* guest_buffer, GLboolean* out_res)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    *out_res = GL_TRUE;

    if (access & GL_MAP_WRITE_BIT) {
        if (!guest_buffer) fprintf(stderr, "%s: error: wanted to write to a mapped buffer with NULL!\n", __FUNCTION__);
        void* gpu_ptr = ctx->glMapBufferRange(target, offset, length, access);
        if (!gpu_ptr) fprintf(stderr, "%s: could not get host gpu pointer!\n", __FUNCTION__);
        memcpy(gpu_ptr, guest_buffer, length);
        *out_res = ctx->glUnmapBuffer(target);
    }
}

void GLESv2Decoder::s_glFlushMappedBufferRangeAEMU(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, void* guest_buffer) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    if (!guest_buffer) fprintf(stderr, "%s: error: wanted to write to a mapped buffer with NULL!\n", __FUNCTION__);
    void* gpu_ptr = ctx->glMapBufferRange(target, offset, length, access);
    memcpy(gpu_ptr, guest_buffer, length);
    if (!gpu_ptr) fprintf(stderr, "%s: could not get host gpu pointer!\n", __FUNCTION__);
    // |offset| was the absolute offset into the mapping, so just flush offset 0.
    ctx->glFlushMappedBufferRange(target, 0, length);
    ctx->glUnmapBuffer(target);
}

void GLESv2Decoder::s_glCompressedTexImage2DOffsetAEMU(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, SafePointerFromUInt(offset));
}
void GLESv2Decoder::s_glCompressedTexSubImage2DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, SafePointerFromUInt(offset));
}
void GLESv2Decoder::s_glTexImage2DOffsetAEMU(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glTexImage2D(target, level, internalformat, width, height, border, format, type, SafePointerFromUInt(offset));
}
void GLESv2Decoder::s_glTexSubImage2DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, SafePointerFromUInt(offset));
}

static const char* const kNameDelimiter = ";";

static std::vector<std::string> sUnpackVarNames(GLsizei count, const char* packedNames) {
    std::vector<std::string> unpacked;
    GLsizei current = 0;

    while (current < count) {
        const char* delimPos = strstr(packedNames, kNameDelimiter);
        size_t nameLen = delimPos - packedNames;
        std::string next;
        next.resize(nameLen);
        memcpy(&next[0], packedNames, nameLen);
        unpacked.push_back(next);
        packedNames = delimPos + 1;
        current++;
    }

    return unpacked;
}

void GLESv2Decoder::s_glGetUniformIndicesAEMU(GLuint program, GLsizei uniformCount, const GLchar* packedNames, GLsizei packedLen, GLuint* uniformIndices) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();

    std::vector<std::string> unpacked = sUnpackVarNames(uniformCount, packedNames);

    GLchar** unpackedArray = new GLchar*[unpacked.size()];
    GLsizei i = 0;
    std::vector<std::string>::iterator elt;
    for (elt = unpacked.begin();elt!=unpacked.end();elt++) {
        unpackedArray[i] = (GLchar*)&elt[0];
        i++;
    }

    ctx->glGetUniformIndices(program, uniformCount, (const GLchar**)unpackedArray, uniformIndices);

    delete [] unpackedArray;
}

void GLESv2Decoder::s_glVertexAttribIPointerDataAEMU(GLuint indx, GLint size, GLenum type, GLsizei stride, void * data, GLuint datalen)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    if (ctx->m_contextData != NULL) {
        ctx->m_contextData->storePointerData(indx, data, datalen);
        // note - the stride of the data is always zero when it comes out of the codec.
        // See gl2.attrib for the packing function call.
        ctx->glVertexAttribIPointer(indx, size, type, 0, ctx->m_contextData->pointerData(indx));
    }
}

void GLESv2Decoder::s_glVertexAttribIPointerOffsetAEMU(GLuint indx, GLint size, GLenum type, GLsizei stride, GLuint data)
{
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glVertexAttribIPointer(indx, size, type, stride, SafePointerFromUInt(data));
}

void GLESv2Decoder::s_glTransformFeedbackVaryingsAEMU(GLuint program, GLsizei count, const char* packedVaryings, GLuint packedVaryingsLen, GLenum bufferMode) {

    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();

    std::vector<std::string> unpacked = sUnpackVarNames(count, packedVaryings);

    char** unpackedArray = new char*[unpacked.size()];
    GLsizei i = 0;
    std::vector<std::string>::iterator elt;
    for (elt = unpacked.begin();elt!=unpacked.end();elt++) {
        unpackedArray[i] = (GLchar*)&elt[0];
        i++;
    }

    ctx->glTransformFeedbackVaryings(program, count, (const char**)unpackedArray, bufferMode);

    delete [] unpackedArray;
}

void GLESv2Decoder::s_glTexImage3DOffsetAEMU(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, SafePointerFromUInt(offset));
}
void GLESv2Decoder::s_glTexSubImage3DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, SafePointerFromUInt(offset));
}
void GLESv2Decoder::s_glCompressedTexImage3DOffsetAEMU(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, SafePointerFromUInt(offset));
}
void GLESv2Decoder::s_glCompressedTexSubImage3DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *) getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
	ctx->glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, SafePointerFromUInt(offset));
}

void GLESv2Decoder::s_glDrawElementsInstancedOffsetAEMU(GLenum mode, GLsizei count, GLenum type, GLuint offset, GLsizei primcount) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElementsInstanced(mode, count, type, SafePointerFromUInt(offset), primcount);
}

void GLESv2Decoder::s_glDrawElementsInstancedDataAEMU(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLsizei datalen) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElementsInstanced(mode, count, type, indices, primcount);
}

void GLESv2Decoder::s_glReadPixelsOffsetAEMU(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glReadPixels(x, y, width, height, format, type, SafePointerFromUInt(offset));
}

GLuint GLESv2Decoder::s_glCreateShaderProgramvAEMU(GLenum type, GLsizei count, const char* packedStrings, GLuint packedLen) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glCreateShaderProgramv(type, 1, &packedStrings);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDrawArraysIndirectDataAEMU(GLenum mode, const void* indirect, GLuint datalen) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawArraysIndirect(mode, indirect);
}

void GLESv2Decoder::s_glDrawArraysIndirectOffsetAEMU(GLenum mode, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawArraysIndirect(mode, SafePointerFromUInt(offset));
}

void GLESv2Decoder::s_glDrawElementsIndirectDataAEMU(GLenum mode, GLenum type, const void* indirect, GLuint datalen) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElementsIndirect(mode, type, indirect);
}

void GLESv2Decoder::s_glDrawElementsIndirectOffsetAEMU(GLenum mode, GLenum type, GLuint offset) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDrawElementsIndirect(mode, type, SafePointerFromUInt(offset));
}

uint64_t GLESv2Decoder::s_glFenceSyncAEMU(GLenum condition, GLbitfield flags) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return (uint64_t)(uintptr_t)ctx->glFenceSync(condition, flags);
}

GLenum GLESv2Decoder::s_glClientWaitSyncAEMU(uint64_t wait_on, GLbitfield flags, GLuint64 timeout) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glClientWaitSync((GLsync)(uintptr_t)wait_on, flags, timeout);
}

void GLESv2Decoder::s_glWaitSyncAEMU(uint64_t wait_on, GLbitfield flags, GLuint64 timeout) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glWaitSync((GLsync)(uintptr_t)wait_on, flags, timeout);
}

void GLESv2Decoder::s_glDeleteSyncAEMU(uint64_t to_delete) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteSync((GLsync)(uintptr_t)to_delete);
}

GLboolean GLESv2Decoder::s_glIsSyncAEMU(uint64_t sync) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glIsSync((GLsync)(uintptr_t)sync);
}

void GLESv2Decoder::s_glGetSyncivAEMU(uint64_t sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGetSynciv((GLsync)(uintptr_t)sync, pname, bufSize, length, values);
}

GLuint GLESv2Decoder::s_glCreateShader(GLenum shaderType) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    GLuint shader = ctx->glCreateShader(shaderType);
    
    if (ctx->m_snapshot) {
        GLuint emuName = ctx->m_snapshot->createShader(shader, shaderType);
        return emuName;
    }

    return shader;
}

GLuint GLESv2Decoder::s_glCreateProgram() {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    return ctx->glCreateProgram();
}

void GLESv2Decoder::s_glGenBuffers(GLsizei n, GLuint* buffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenBuffers(n, buffers);

    if (ctx->m_snapshot) {
        ctx->m_snapshot->genBuffers(n, buffers);
    }
}

void GLESv2Decoder::s_glGenFramebuffers(GLsizei n, GLuint* framebuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenFramebuffers(n, framebuffers);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenRenderbuffers(n, renderbuffers);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glGenTextures(GLsizei n, GLuint* textures) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenTextures(n, textures);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glGenVertexArraysOES(GLsizei n, GLuint* arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenVertexArraysOES(n, arrays);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glGenVertexArrays(GLsizei n, GLuint* arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenVertexArrays(n, arrays);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glGenTransformFeedbacks(GLsizei n, GLuint* transformFeedbacks) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenTransformFeedbacks(n, transformFeedbacks);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glGenSamplers(GLsizei n, GLuint* samplers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenSamplers(n, samplers);
    // TODO: Snapshot names

}

void GLESv2Decoder::s_glGenQueries(GLsizei n, GLuint* queries) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenQueries(n, queries);
    // TODO: Snapshot names

}

void GLESv2Decoder::s_glGenProgramPipelines(GLsizei n, GLuint* pipelines) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glGenProgramPipelines(n, pipelines);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteShader(GLuint shader) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteShader(shader);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteProgram(GLuint program) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteProgram(program);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteBuffers(GLsizei n, const GLuint *buffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteBuffers(n, buffers);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteFramebuffers(n, framebuffers);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteRenderbuffers(n, renderbuffers);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteTextures(GLsizei n, const GLuint *textures) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteTextures(n, textures);
    // TODO: Snapshot names
}


void GLESv2Decoder::s_glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteVertexArraysOES(n, arrays);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteVertexArrays(GLsizei n, const GLuint *arrays) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteVertexArrays(n, arrays);
    // TODO: Snapshot names
}


void GLESv2Decoder::s_glDeleteTransformFeedbacks(GLsizei n, const GLuint *transformFeedbacks) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteTransformFeedbacks(n, transformFeedbacks);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteSamplers(GLsizei n, const GLuint *samplers) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteSamplers(n, samplers);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteQueries(GLsizei n, const GLuint *queries) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteQueries(n, queries);
    // TODO: Snapshot names
}

void GLESv2Decoder::s_glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines) {
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr();
    ctx->glDeleteProgramPipelines(n, pipelines);
    // TODO: Snapshot names
}

#define SNAPSHOT_PROGRAM_NAME(x) \
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr(); \
    if (ctx->m_snapshot) { x = ctx->m_snapshot->getProgramName(x); } \

#define SNAPSHOT_PROGRAM_NAME2(x,y) \
    GLESv2Decoder *ctx = (GLESv2Decoder *)getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr(); \
    if (ctx->m_snapshot) { \
        x = ctx->m_snapshot->getProgramName(x); \
        y = ctx->m_snapshot->getProgramName(y); \
    } \

#define SNAPSHOT_SHADER_CALL(funcname,argtypes,args) \
void GLESv2Decoder::s_##funcname argtypes { \
    SNAPSHOT_PROGRAM_NAME(shader) \
    ctx-> funcname args ; \
} \

#define SNAPSHOT_PROGRAM_CALL(funcname,argtypes,args) \
void GLESv2Decoder::s_##funcname argtypes  { \
    SNAPSHOT_PROGRAM_NAME(program) \
    ctx-> funcname args ; \
} \

#define SNAPSHOT_PROGRAM_CALL_RET(rettype, funcname, argtypes, args) \
rettype GLESv2Decoder::s_##funcname argtypes  { \
    SNAPSHOT_PROGRAM_NAME(program) \
    return ctx-> funcname args; \
} \


void GLESv2Decoder::s_glShaderString(GLuint shader, const GLchar* string, GLsizei len)
{
    SNAPSHOT_PROGRAM_NAME(shader);

    ctx->glShaderSource(shader, 1, &string, NULL);

    if (ctx->m_snapshot) {
        ctx->m_snapshot->shaderString(shader, string);
    }
}

void GLESv2Decoder::s_glAttachShader(GLuint program, GLuint shader) {
    SNAPSHOT_PROGRAM_NAME2(program, shader)
    ctx->glAttachShader(program, shader);
}

void GLESv2Decoder::s_glDetachShader(GLuint program, GLuint shader) {
    SNAPSHOT_PROGRAM_NAME2(program, shader)
    ctx->glDetachShader(program, shader);
}

GLboolean GLESv2Decoder::s_glIsShader(GLuint shader) {
    SNAPSHOT_PROGRAM_NAME(shader);
    return ctx->glIsShader(shader);
}

GLboolean GLESv2Decoder::s_glIsProgram(GLuint program) {
    SNAPSHOT_PROGRAM_NAME(program);
    return ctx->glIsProgram(program);
}

SNAPSHOT_SHADER_CALL(glCompileShader, ( GLuint shader), (shader))
SNAPSHOT_SHADER_CALL(glGetShaderiv, ( GLuint shader, GLenum pname, GLint* params), (shader, pname, params))
SNAPSHOT_SHADER_CALL(glGetShaderInfoLog, ( GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog), (shader, bufsize, length, infolog))
SNAPSHOT_SHADER_CALL(glGetShaderSource, ( GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source), (shader, bufsize, length, source))
SNAPSHOT_PROGRAM_CALL(glLinkProgram, ( GLuint program), (program))
SNAPSHOT_PROGRAM_CALL(glUseProgram, ( GLuint program), (program))
SNAPSHOT_PROGRAM_CALL(glValidateProgram, ( GLuint program), (program))
SNAPSHOT_PROGRAM_CALL(glGetProgramiv, ( GLuint program, GLenum pname, GLint* params), (program, pname, params))
SNAPSHOT_PROGRAM_CALL(glGetProgramInfoLog, ( GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog), (program, bufsize, length, infolog))
SNAPSHOT_PROGRAM_CALL(glBindAttribLocation, ( GLuint program, GLuint index, const GLchar* name), (program, index, name))
SNAPSHOT_PROGRAM_CALL(glGetActiveAttrib, ( GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name), (program, index, bufsize, length, size, type, name))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniform, ( GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name), (program, index, bufsize, length, size, type, name))
SNAPSHOT_PROGRAM_CALL(glGetAttachedShaders, ( GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders), (program, maxcount, count, shaders))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetAttribLocation, ( GLuint program, const GLchar* name), (program, name))
SNAPSHOT_PROGRAM_CALL(glGetUniformfv, ( GLuint program, GLint location, GLfloat* params), (program, location, params))
SNAPSHOT_PROGRAM_CALL(glGetUniformiv, ( GLuint program, GLint location, GLint* params), (program, location, params))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetUniformLocation, ( GLuint program, const GLchar* name), (program, name))
SNAPSHOT_PROGRAM_CALL(glGetProgramBinaryOES, ( GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary), (program, bufSize, length, binaryFormat, binary))
SNAPSHOT_PROGRAM_CALL(glProgramBinaryOES, ( GLuint program, GLenum binaryFormat, const GLvoid* binary, GLint length), (program, binaryFormat, binary, length))
SNAPSHOT_PROGRAM_CALL(glUniformBlockBinding, ( GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding), (program, uniformBlockIndex, uniformBlockBinding))
SNAPSHOT_PROGRAM_CALL_RET(GLuint, glGetUniformBlockIndex, ( GLuint program, const GLchar* uniformBlockName), (program, uniformBlockName))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniformBlockiv, ( GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params), (program, uniformBlockIndex, pname, params))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniformBlockName, ( GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName), (program, uniformBlockIndex, bufSize, length, uniformBlockName))
SNAPSHOT_PROGRAM_CALL(glGetUniformuiv, ( GLuint program, GLint location, GLuint* params), (program, location, params))
SNAPSHOT_PROGRAM_CALL(glGetActiveUniformsiv, ( GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params), (program, uniformCount, uniformIndices, pname, params))
SNAPSHOT_PROGRAM_CALL(glTransformFeedbackVaryings, ( GLuint program, GLsizei count, const char** varyings, GLenum bufferMode), (program, count, varyings, bufferMode))
SNAPSHOT_PROGRAM_CALL(glGetTransformFeedbackVarying, ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, char* name), (program, index, bufSize, length, size, type, name))
SNAPSHOT_PROGRAM_CALL(glProgramParameteri, ( GLuint program, GLenum pname, GLint value), (program, pname, value))
SNAPSHOT_PROGRAM_CALL(glProgramBinary, ( GLuint program, GLenum binaryFormat, const void* binary, GLsizei length), (program, binaryFormat, binary, length))
SNAPSHOT_PROGRAM_CALL(glGetProgramBinary, ( GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary), (program, bufSize, length, binaryFormat, binary))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetFragDataLocation, ( GLuint program, const char* name), (program, name))
SNAPSHOT_PROGRAM_CALL(glUseProgramStages, ( GLuint pipeline, GLbitfield stages, GLuint program), (pipeline, stages, program))
SNAPSHOT_PROGRAM_CALL(glActiveShaderProgram, ( GLuint pipeline, GLuint program), (pipeline, program))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1f, ( GLuint program, GLint location, GLfloat v0), (program, location, v0))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2f, ( GLuint program, GLint location, GLfloat v0, GLfloat v1), (program, location, v0, v1))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3f, ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2), (program, location, v0, v1, v2))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4f, ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3), (program, location, v0, v1, v2, v3))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1i, ( GLuint program, GLint location, GLint v0), (program, location, v0))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2i, ( GLuint program, GLint location, GLint v0, GLint v1), (program, location, v0, v1))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3i, ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2), (program, location, v0, v1, v2))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4i, ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3), (program, location, v0, v1, v2, v3))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1ui, ( GLuint program, GLint location, GLuint v0), (program, location, v0))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2ui, ( GLuint program, GLint location, GLint v0, GLuint v1), (program, location, v0, v1))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3ui, ( GLuint program, GLint location, GLint v0, GLint v1, GLuint v2), (program, location, v0, v1, v2))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4ui, ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLuint v3), (program, location, v0, v1, v2, v3))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1fv, ( GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2fv, ( GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3fv, ( GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4fv, ( GLuint program, GLint location, GLsizei count, const GLfloat* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1iv, ( GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2iv, ( GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3iv, ( GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4iv, ( GLuint program, GLint location, GLsizei count, const GLint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform1uiv, ( GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform2uiv, ( GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform3uiv, ( GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniform4uiv, ( GLuint program, GLint location, GLsizei count, const GLuint* value), (program, location, count, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix2fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix3fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix4fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix2x3fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix3x2fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix2x4fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix4x2fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix3x4fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glProgramUniformMatrix4x3fv, ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value), (program, location, count, transpose, value))
SNAPSHOT_PROGRAM_CALL(glGetProgramInterfaceiv, ( GLuint program, GLenum programInterface, GLenum pname, GLint* params), (program, programInterface, pname, params))
SNAPSHOT_PROGRAM_CALL(glGetProgramResourceiv, ( GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params), (program, programInterface, index, propCount, props, bufSize, length, params))
SNAPSHOT_PROGRAM_CALL_RET(GLuint, glGetProgramResourceIndex, (GLuint program, GLenum programInterface, const char * name), (program, programInterface, name))
SNAPSHOT_PROGRAM_CALL_RET(GLint, glGetProgramResourceLocation, (GLuint program, GLenum programInterface, const char * name), (program, programInterface, name))
SNAPSHOT_PROGRAM_CALL(glGetProgramResourceName, ( GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, char* name), (program, programInterface, index, bufSize, length, name))
