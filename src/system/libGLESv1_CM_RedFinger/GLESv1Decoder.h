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
#ifndef _GL_DECODER_H_
#define _GL_DECODER_H_

#include "gles1_dec.h"

#include "GLDecoderContextData.h"

class GLESv1Decoder : public gles1_decoder_context_t
{
public:
    GLESv1Decoder();
    ~GLESv1Decoder();
    int initGL();
    void setContextData(GLDecoderContextData *contextData) { m_contextData = contextData; }
    gles1_decoder_context_t* GetContext(){
        return (dynamic_cast<gles1_decoder_context_t*>(this));
    }
private:
    static void gles1_APIENTRY s_glGetCompressedTextureFormats(GLint cont, GLint *data);
    static void gles1_APIENTRY s_glVertexPointerData(GLint size, GLenum type, GLsizei stride, void *data, GLuint datalen);
    static void gles1_APIENTRY s_glVertexPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset);

    static void gles1_APIENTRY s_glColorPointerData(GLint size, GLenum type, GLsizei stride, void *data, GLuint datalen);
    static void gles1_APIENTRY s_glColorPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset);

    static void gles1_APIENTRY s_glTexCoordPointerData(GLint unit, GLint size, GLenum type, GLsizei stride, void *data, GLuint datalen);
    static void gles1_APIENTRY s_glTexCoordPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset);

    static void gles1_APIENTRY s_glNormalPointerData(GLenum type, GLsizei stride, void *data, GLuint datalen);
    static void gles1_APIENTRY s_glNormalPointerOffset(GLenum type, GLsizei stride, GLuint offset);

    static void gles1_APIENTRY s_glPointSizePointerData(GLenum type, GLsizei stride, void *data, GLuint datalen);
    static void gles1_APIENTRY s_glPointSizePointerOffset(GLenum type, GLsizei stride, GLuint offset);

    static void gles1_APIENTRY s_glDrawElementsOffset(GLenum mode, GLsizei count, GLenum type, GLuint offset);
    static void gles1_APIENTRY s_glDrawElementsData(GLenum mode, GLsizei count, GLenum type, void * data, GLuint datalen);

    static void gles1_APIENTRY s_glWeightPointerData(GLint size, GLenum type, GLsizei stride, void * data, GLuint datalen);
    static void gles1_APIENTRY s_glWeightPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset);

    static void gles1_APIENTRY s_glMatrixIndexPointerData(GLint size, GLenum type, GLsizei stride, void * data, GLuint datalen);
    static void gles1_APIENTRY s_glMatrixIndexPointerOffset(GLint size, GLenum type, GLsizei stride, GLuint offset);

    static int gles1_APIENTRY s_glFinishRoundTrip();

    static void gles1_APIENTRY s_glGenBuffers(GLsizei n, GLuint* buffers);
    static void gles1_APIENTRY s_glGenTextures(GLsizei n, GLuint* textures);
    static void gles1_APIENTRY s_glGenRenderbuffersOES(GLsizei n, GLuint* renderbuffers);
    static void gles1_APIENTRY s_glGenFramebuffersOES(GLsizei n, GLuint* framebuffers);
    static void gles1_APIENTRY s_glGenVertexArraysOES(GLsizei n, GLuint* arrays);

    static void gles1_APIENTRY s_glDeleteBuffers(GLsizei n, const GLuint *buffers);
    static void gles1_APIENTRY s_glDeleteTextures(GLsizei n, const GLuint *textures);

    static void gles1_APIENTRY s_glDeleteRenderbuffersOES(GLsizei n, const GLuint* renderbuffers);
    static void gles1_APIENTRY s_glDeleteFramebuffersOES(GLsizei n, const GLuint* framebuffers);

    static void gles1_APIENTRY s_glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays);
    GLDecoderContextData *m_contextData;
};

#endif
