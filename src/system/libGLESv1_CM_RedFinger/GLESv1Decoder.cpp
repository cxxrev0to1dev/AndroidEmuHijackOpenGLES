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
#include "GLESv1Decoder.h"

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GLESv1ThreadInfo.h"

static inline void* SafePointerFromUInt(GLuint value) {
  return (void*)(uintptr_t)value;
}

GLESv1Decoder::GLESv1Decoder()
{
    m_contextData = NULL;
}

GLESv1Decoder::~GLESv1Decoder()
{
}


int GLESv1Decoder::initGL()
{
    glGetCompressedTextureFormats = s_glGetCompressedTextureFormats;
    glVertexPointerOffset = s_glVertexPointerOffset;
    glColorPointerOffset = s_glColorPointerOffset;
    glNormalPointerOffset = s_glNormalPointerOffset;
    glTexCoordPointerOffset = s_glTexCoordPointerOffset;
    glPointSizePointerOffset = s_glPointSizePointerOffset;
    glWeightPointerOffset = s_glWeightPointerOffset;
    glMatrixIndexPointerOffset = s_glMatrixIndexPointerOffset;

    glVertexPointerData = s_glVertexPointerData;
    glColorPointerData = s_glColorPointerData;
    glNormalPointerData = s_glNormalPointerData;
    glTexCoordPointerData = s_glTexCoordPointerData;
    glPointSizePointerData = s_glPointSizePointerData;
    glWeightPointerData = s_glWeightPointerData;
    glMatrixIndexPointerData = s_glMatrixIndexPointerData;

    glDrawElementsOffset = s_glDrawElementsOffset;
    glDrawElementsData = s_glDrawElementsData;
    glFinishRoundTrip = s_glFinishRoundTrip;

    glGenBuffers = s_glGenBuffers;
    glGenTextures = s_glGenTextures;

    glGenFramebuffersOES = s_glGenFramebuffersOES;
    glGenRenderbuffersOES = s_glGenRenderbuffersOES;

    glGenVertexArraysOES = s_glGenVertexArraysOES;

    glDeleteBuffers = s_glDeleteBuffers;
    glDeleteTextures = s_glDeleteTextures;
    glDeleteRenderbuffersOES = s_glDeleteRenderbuffersOES;
    glDeleteFramebuffersOES = s_glDeleteFramebuffersOES;
    glDeleteVertexArraysOES = s_glDeleteVertexArraysOES;

    return 0;
}

int GLESv1Decoder::s_glFinishRoundTrip()
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glFinish();
    return 0;
}

void GLESv1Decoder::s_glVertexPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glVertexPointer(size, type, stride, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glColorPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glColorPointer(size, type, stride, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glTexCoordPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glTexCoordPointer(size, type, stride, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glNormalPointerOffset(GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glNormalPointer(type, stride, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glPointSizePointerOffset(GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glPointSizePointerOES(type, stride, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glWeightPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glWeightPointerOES(size, type, stride, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glMatrixIndexPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glMatrixIndexPointerOES(size, type, stride, SafePointerFromUInt(offset));
}



#define STORE_POINTER_DATA_OR_ABORT(location)    \
    if (ctx->m_contextData != NULL) {   \
        ctx->m_contextData->storePointerData((location), data, datalen); \
    } else { \
        return; \
    }

void GLESv1Decoder::s_glVertexPointerData(GLint size, GLenum type, GLsizei stride, void *data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();

    STORE_POINTER_DATA_OR_ABORT(GLDecoderContextData::VERTEX_LOCATION);

    ctx->glVertexPointer(size, type, 0, ctx->m_contextData->pointerData(GLDecoderContextData::VERTEX_LOCATION));
}

void GLESv1Decoder::s_glColorPointerData(GLint size, GLenum type, GLsizei stride, void *data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();

    STORE_POINTER_DATA_OR_ABORT(GLDecoderContextData::COLOR_LOCATION);

    ctx->glColorPointer(size, type, 0, ctx->m_contextData->pointerData(GLDecoderContextData::COLOR_LOCATION));
}

void GLESv1Decoder::s_glTexCoordPointerData(GLint unit, GLint size, GLenum type, GLsizei stride, void *data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    STORE_POINTER_DATA_OR_ABORT((GLDecoderContextData::PointerDataLocation)
                                (GLDecoderContextData::TEXCOORD0_LOCATION + unit));

    ctx->glTexCoordPointer(size, type, 0,
                           ctx->m_contextData->pointerData((GLDecoderContextData::PointerDataLocation)
                                                           (GLDecoderContextData::TEXCOORD0_LOCATION + unit)));
}

void GLESv1Decoder::s_glNormalPointerData(GLenum type, GLsizei stride, void *data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();

    STORE_POINTER_DATA_OR_ABORT(GLDecoderContextData::NORMAL_LOCATION);

    ctx->glNormalPointer(type, 0, ctx->m_contextData->pointerData(GLDecoderContextData::NORMAL_LOCATION));
}

void GLESv1Decoder::s_glPointSizePointerData(GLenum type, GLsizei stride, void *data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();

    STORE_POINTER_DATA_OR_ABORT(GLDecoderContextData::POINTSIZE_LOCATION);

    ctx->glPointSizePointerOES(type, 0, ctx->m_contextData->pointerData(GLDecoderContextData::POINTSIZE_LOCATION));
}

void GLESv1Decoder::s_glWeightPointerData(GLint size, GLenum type, GLsizei stride, void * data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();

    STORE_POINTER_DATA_OR_ABORT(GLDecoderContextData::WEIGHT_LOCATION);

    ctx->glWeightPointerOES(size, type, 0, ctx->m_contextData->pointerData(GLDecoderContextData::WEIGHT_LOCATION));
}

void GLESv1Decoder::s_glMatrixIndexPointerData(GLint size, GLenum type, GLsizei stride, void * data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();

    STORE_POINTER_DATA_OR_ABORT(GLDecoderContextData::MATRIXINDEX_LOCATION);

    ctx->glMatrixIndexPointerOES(size, type, 0, ctx->m_contextData->pointerData(GLDecoderContextData::MATRIXINDEX_LOCATION));
}

void GLESv1Decoder::s_glDrawElementsOffset(GLenum mode, GLsizei count, GLenum type, GLuint offset)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDrawElements(mode, count, type, SafePointerFromUInt(offset));
}

void GLESv1Decoder::s_glDrawElementsData(GLenum mode, GLsizei count, GLenum type, void * data, GLuint datalen)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDrawElements(mode, count, type, data);
}

void GLESv1Decoder::s_glGetCompressedTextureFormats(GLint count, GLint *data)
{
    GLESv1Decoder *ctx = (GLESv1Decoder *) GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, data);
}

void GLESv1Decoder::s_glGenBuffers(GLsizei n, GLuint* buffers) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glGenBuffers(n, buffers);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glGenTextures(GLsizei n, GLuint* textures) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glGenTextures(n, textures);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glGenRenderbuffersOES(GLsizei n, GLuint* renderbuffers) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glGenRenderbuffersOES(n, renderbuffers);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glGenFramebuffersOES(GLsizei n, GLuint* framebuffers) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glGenFramebuffersOES(n, framebuffers);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glGenVertexArraysOES(GLsizei n, GLuint* arrays) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glGenVertexArraysOES(n, arrays);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glDeleteBuffers(GLsizei n, const GLuint *buffers) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDeleteBuffers(n, buffers);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glDeleteTextures(GLsizei n, const GLuint *textures) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDeleteTextures(n, textures);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glDeleteRenderbuffersOES(GLsizei n, const GLuint* renderbuffers) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDeleteRenderbuffersOES(n, renderbuffers);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glDeleteFramebuffersOES(GLsizei n, const GLuint* framebuffers) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDeleteFramebuffersOES(n, framebuffers);
    // TODO: Snapshot names
}

void GLESv1Decoder::s_glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays) {
    GLESv1Decoder *ctx = (GLESv1Decoder *)GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder();
    ctx->glDeleteVertexArraysOES(n, arrays);
    // TODO: Snapshot names
}