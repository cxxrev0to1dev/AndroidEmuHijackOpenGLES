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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GLClientState.h"
#include "GLSharedGroup.h"
#include "SmartPtr.h"
#include "GLESv2ThreadInfo.h"
#include <GLES3/gl31.h>

namespace glesv2_enc {
size_t pixelDataSize(void *self, GLsizei width, GLsizei height, GLenum format, GLenum type, int pack)
{
    // GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    // return result_derived->gl_client_state->pixelDataSize(width, height, format, type, pack);
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    return ctx->state()->pixelDataSize(width, height, 1, format, type, pack);
}

size_t pixelDataSize3D(void *self, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, int pack)
{
    // size_t layerSize = pixelDataSize(self, width, height, depth, format, type, pack);
    // return layerSize * depth;
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    assert (ctx->state() != NULL);
    return ctx->state()->pixelDataSize(width, height, depth, format, type, pack);
}

GLenum uniformType(void * self, GLuint program, GLint location)
{
    // GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    // return result_derived->gl_shared_group->getProgramUniformType(program, location);
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    return ctx->shared_static()->getProgramUniformType(program, location);
}
size_t clearBufferNumElts(void* self, GLenum buffer) {
    // GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    // return result_derived->gl_client_state->clearBufferNumElts(buffer);
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    return ctx->state_static()->clearBufferNumElts(buffer);
}

size_t numActiveUniformsInUniformBlock(void* self, GLuint program, GLuint blockIndex) {
    // GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    // return result_derived->gl_client_state->numActiveUniformsInUniformBlock(program, blockIndex);
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    return ctx->state_static()->numActiveUniformsInUniformBlock(program, blockIndex);
}

size_t glActiveUniformBlockivParamSize(void* self, GLuint program, GLuint blockIndex, GLenum pname) {
    GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    if (pname == GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES) {
        // return result_derived->gl_client_state->numActiveUniformsInUniformBlock(program, blockIndex);
        GLESv2Encoder *ctx = (GLESv2Encoder *)self;
        return ctx->state_static()->numActiveUniformsInUniformBlock(program, blockIndex);
    } else {
        return glUtilsParamSize(pname);
    }
}
}  // namespace glesv2_enc

namespace glesv1_enc {
size_t pixelDataSize(void *self, GLsizei width, GLsizei height, GLenum format, GLenum type, int pack)
{
    // GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    // return result_derived->gl_client_state->pixelDataSize(width, height, format, type, pack);
    GLESv2Encoder *ctx = (GLESv2Encoder *)self;
    return ctx->state_static()->pixelDataSize(width, height, format, type, pack);
}
} // namespace glesv2_enc