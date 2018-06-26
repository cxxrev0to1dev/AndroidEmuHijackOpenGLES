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

#ifndef __GLES_V2_DECODER_H_
#define __GLES_V2_DECODER_H_

#include "gles_dec.h"
#include "GLDecoderContextData.h"
#include "GLESv2Snapshot.h"

typedef void (gles_APIENTRY *glVertexAttribPointerWithDataSize_server_proc_t) (GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*, GLsizei);
class GLSnapshotState;

class GLESv2Decoder : public gles_decoder_context_t
{
public:
    GLESv2Decoder();
    ~GLESv2Decoder();
    int initGL();
    void setContextData(GLDecoderContextData *contextData) { m_contextData = contextData; }
    glVertexAttribPointerWithDataSize_server_proc_t glVertexAttribPointerWithDataSize;
    gles_decoder_context_t* GetDecoder(){
        return (dynamic_cast<gles_decoder_context_t*>(this));
    }
protected:
    GLSnapshotState *m_snapshot;
private:
    GLDecoderContextData *m_contextData;
    static void gles_APIENTRY s_glGetCompressedTextureFormats(int count, GLint *formats);
    static void gles_APIENTRY s_glVertexAttribPointerData(GLuint indx, GLint size, GLenum type,
                                      GLboolean normalized, GLsizei stride,  void * data, GLuint datalen);
    static void gles_APIENTRY s_glVertexAttribPointerOffset(GLuint indx, GLint size, GLenum type,
                                        GLboolean normalized, GLsizei stride,  GLuint offset);

    static void gles_APIENTRY s_glDrawElementsOffset(GLenum mode, GLsizei count, GLenum type, GLuint offset);
    static void gles_APIENTRY s_glDrawElementsData(GLenum mode, GLsizei count, GLenum type, void * data, GLuint datalen);
    static int  gles_APIENTRY s_glFinishRoundTrip();

    static void gles_APIENTRY s_glMapBufferRangeAEMU(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, void* mapped);
    static void gles_APIENTRY s_glUnmapBufferAEMU(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, void* guest_buffer, GLboolean* out_res);
    static void gles_APIENTRY s_glFlushMappedBufferRangeAEMU(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access, void* guest_buffer);

    static void gles_APIENTRY s_glCompressedTexImage2DOffsetAEMU(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLuint offset);
    static void gles_APIENTRY s_glCompressedTexSubImage2DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLuint offset);
    static void gles_APIENTRY s_glTexImage2DOffsetAEMU(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLuint offset);
    static void gles_APIENTRY s_glTexSubImage2DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint offset);

    static void gles_APIENTRY s_glVertexAttribIPointerDataAEMU(GLuint indx, GLint size, GLenum type, GLsizei stride, void * data, GLuint datalen);
    static void gles_APIENTRY s_glVertexAttribIPointerOffsetAEMU(GLuint indx, GLint size, GLenum type, GLsizei stride,  GLuint offset);

    static void gles_APIENTRY s_glTexImage3DOffsetAEMU(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLuint offset);
    static void gles_APIENTRY s_glTexSubImage3DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint offset);
    static void gles_APIENTRY s_glCompressedTexImage3DOffsetAEMU(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLuint offset);
    static void gles_APIENTRY s_glCompressedTexSubImage3DOffsetAEMU(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLuint offset);
    static void gles_APIENTRY s_glDrawElementsInstancedOffsetAEMU(GLenum mode, GLsizei count, GLenum type, GLuint offset, GLsizei primcount);
    static void gles_APIENTRY s_glDrawElementsInstancedDataAEMU(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount, GLsizei datalen);

    static void gles_APIENTRY s_glReadPixelsOffsetAEMU(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint offset);

    static GLuint gles_APIENTRY s_glCreateShaderProgramvAEMU(GLenum type, GLsizei count, const char* packedStrings, GLuint packedLen);

    static void gles_APIENTRY s_glDrawArraysIndirectDataAEMU(GLenum mode, const void* indirect, GLuint datalen);
    static void gles_APIENTRY s_glDrawArraysIndirectOffsetAEMU(GLenum mode, GLuint offset);

    static void gles_APIENTRY s_glDrawElementsIndirectDataAEMU(GLenum mode, GLenum type, const void* indirect, GLuint datalen);
    static void gles_APIENTRY s_glDrawElementsIndirectOffsetAEMU(GLenum mode, GLenum type, GLuint offset);

    static uint64_t gles_APIENTRY s_glFenceSyncAEMU(GLenum condition, GLbitfield flags);
    static GLenum gles_APIENTRY s_glClientWaitSyncAEMU(uint64_t wait_on, GLbitfield flags, GLuint64 timeout);
    static void gles_APIENTRY s_glWaitSyncAEMU(uint64_t wait_on, GLbitfield flags, GLuint64 timeout);
    static void gles_APIENTRY s_glDeleteSyncAEMU(uint64_t to_delete);
    static GLboolean gles_APIENTRY s_glIsSyncAEMU(uint64_t sync);
    static void gles_APIENTRY s_glGetSyncivAEMU(uint64_t sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

    //============================================================
    // Snapshot state
    //============================================================

    // All generations============================================
    
    static GLuint gles_APIENTRY s_glCreateShader(GLenum shaderType);
    static GLuint gles_APIENTRY s_glCreateProgram();

    static void gles_APIENTRY s_glGenBuffers(GLsizei n, GLuint* buffers);

    static void gles_APIENTRY s_glGenFramebuffers(GLsizei n, GLuint* framebuffers);
    static void gles_APIENTRY s_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
    static void gles_APIENTRY s_glGenTextures(GLsizei n, GLuint* textures);

    static void gles_APIENTRY s_glGenVertexArraysOES(GLsizei n, GLuint* arrays);
    static void gles_APIENTRY s_glGenVertexArrays(GLsizei n, GLuint* arrays);

    static void gles_APIENTRY s_glGenTransformFeedbacks(GLsizei n, GLuint* transformFeedbacks);

    static void gles_APIENTRY s_glGenSamplers(GLsizei n, GLuint* samplers);

    static void gles_APIENTRY s_glGenQueries(GLsizei n, GLuint* queries);

    static GLuint gles_APIENTRY s_glCreateShaderProgramv(GLenum type, GLsizei count, const char** strings);

    static void gles_APIENTRY s_glGenProgramPipelines(GLsizei n, GLuint* pipelines);

    // All deletes================================================
    static void gles_APIENTRY s_glDeleteShader(GLuint shader);
    static void gles_APIENTRY s_glDeleteProgram(GLuint program);

    static void gles_APIENTRY s_glDeleteBuffers(GLsizei n, const GLuint *buffers);
    static void gles_APIENTRY s_glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
    static void gles_APIENTRY s_glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);
    static void gles_APIENTRY s_glDeleteTextures(GLsizei n, const GLuint *textures);

    static void gles_APIENTRY s_glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays);
    static void gles_APIENTRY s_glDeleteVertexArrays(GLsizei n, const GLuint *arrays);

    static void gles_APIENTRY s_glDeleteTransformFeedbacks(GLsizei n, const GLuint *transformfeedbacks);
    static void gles_APIENTRY s_glDeleteSamplers(GLsizei n, const GLuint *samplers);
    static void gles_APIENTRY s_glDeleteQueries(GLsizei n, const GLuint *queries);
    static void gles_APIENTRY s_glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines);

    // Shaders and programs=======================================
    static void gles_APIENTRY s_glShaderString(GLuint shader, const GLchar* string, GLsizei len);
    static void gles_APIENTRY s_glCompileShader(GLuint shader);
    static void gles_APIENTRY s_glAttachShader(GLuint program, GLuint shader);
    static void gles_APIENTRY s_glDetachShader(GLuint program, GLuint shader);
    static void gles_APIENTRY s_glLinkProgram(GLuint program);
    static void gles_APIENTRY s_glUseProgram(GLuint program);
    static void gles_APIENTRY s_glValidateProgram(GLuint program);

    static GLboolean gles_APIENTRY s_glIsShader(GLuint shader);
    static GLboolean gles_APIENTRY s_glIsProgram(GLuint program);

    static void gles_APIENTRY s_glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
    static void gles_APIENTRY s_glGetProgramiv(GLuint program, GLenum pname, GLint* params);
    static void gles_APIENTRY s_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    static void gles_APIENTRY s_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    static void gles_APIENTRY s_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);

    static void gles_APIENTRY s_glBindAttribLocation(GLuint program, GLuint index, const GLchar* name);
    static void gles_APIENTRY s_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    static void gles_APIENTRY s_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    static void gles_APIENTRY s_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
    static GLint gles_APIENTRY s_glGetAttribLocation(GLuint program, const GLchar* name);

    static void gles_APIENTRY s_glGetUniformfv(GLuint program, GLint location, GLfloat* params);
    static void gles_APIENTRY s_glGetUniformiv(GLuint program, GLint location, GLint* params);
    static GLint gles_APIENTRY s_glGetUniformLocation(GLuint program,  const GLchar* name);

    static void gles_APIENTRY s_glGetProgramBinaryOES(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary);
    static void gles_APIENTRY s_glProgramBinaryOES(GLuint program, GLenum binaryFormat, const GLvoid* binary, GLint length);

    static void gles_APIENTRY s_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
    static GLuint gles_APIENTRY s_glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName);
    static void gles_APIENTRY s_glGetUniformIndicesAEMU(GLuint program, GLsizei uniformCount, const GLchar* packedNames, GLsizei packedLen, GLuint* uniformIndices);

    static void gles_APIENTRY s_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
    static void gles_APIENTRY s_glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);

    static void gles_APIENTRY s_glGetUniformuiv(GLuint program, GLint location, GLuint *params);
    static void gles_APIENTRY s_glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);

    static void gles_APIENTRY s_glTransformFeedbackVaryings(GLuint program, GLsizei count, const char ** varyings, GLenum bufferMode);
    static void gles_APIENTRY s_glTransformFeedbackVaryingsAEMU(GLuint program, GLsizei count, const char* packedVaryings, GLuint packedVaryingsLen, GLenum bufferMode);
    static void gles_APIENTRY s_glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, char * name);

    static void gles_APIENTRY s_glProgramParameteri(GLuint program, GLenum pname, GLint value);
    static void gles_APIENTRY s_glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
    static void gles_APIENTRY s_glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);

    static GLint gles_APIENTRY s_glGetFragDataLocation(GLuint program, const char * name);

    static void gles_APIENTRY s_glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
    static void gles_APIENTRY s_glActiveShaderProgram(GLuint pipeline, GLuint program);

    static void gles_APIENTRY s_glProgramUniform1f(GLuint program, GLint location, GLfloat v0);
    static void gles_APIENTRY s_glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1);
    static void gles_APIENTRY s_glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static void gles_APIENTRY s_glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    static void gles_APIENTRY s_glProgramUniform1i(GLuint program, GLint location, GLint v0);
    static void gles_APIENTRY s_glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1);
    static void gles_APIENTRY s_glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
    static void gles_APIENTRY s_glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    static void gles_APIENTRY s_glProgramUniform1ui(GLuint program, GLint location, GLuint v0);
    static void gles_APIENTRY s_glProgramUniform2ui(GLuint program, GLint location, GLint v0, GLuint v1);
    static void gles_APIENTRY s_glProgramUniform3ui(GLuint program, GLint location, GLint v0, GLint v1, GLuint v2);
    static void gles_APIENTRY s_glProgramUniform4ui(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLuint v3);
    static void gles_APIENTRY s_glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value);
    static void gles_APIENTRY s_glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value);
    static void gles_APIENTRY s_glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value);
    static void gles_APIENTRY s_glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value);
    static void gles_APIENTRY s_glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void gles_APIENTRY s_glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void gles_APIENTRY s_glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void gles_APIENTRY s_glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
    static void gles_APIENTRY s_glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    static void gles_APIENTRY s_glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

    static void gles_APIENTRY s_glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
    static void gles_APIENTRY s_glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params);
    static GLuint gles_APIENTRY s_glGetProgramResourceIndex(GLuint program, GLenum programInterface, const char * name);
    static GLint gles_APIENTRY s_glGetProgramResourceLocation(GLuint program, GLenum programInterface, const char * name);
    static void gles_APIENTRY s_glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, char * name);

};
#endif
