/*
* Copyright (C) 2016 The Android Open Source Project
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

#ifndef GLES_VALIDATION_H
#define GLES_VALIDATION_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>

#include "GLESv2Encoder.h"

#include <string>

namespace GLESv2Validation {

extern GLbitfield allBufferMapAccessFlags;
bool bufferTarget(GLESv2Encoder* ctx, GLenum target);
bool bufferParam(GLESv2Encoder* ctx, GLenum param);

bool pixelStoreParam(GLESv2Encoder* ctx, GLenum param);
bool pixelStoreValue(GLenum param, GLint value);

bool rboFormat(GLESv2Encoder* ctx, GLenum internalformat);

bool framebufferTarget(GLESv2Encoder* ctx, GLenum target);
bool framebufferAttachment(GLESv2Encoder* ctx, GLenum attachment);

bool readPixelsFormat(GLenum format);
bool readPixelsType(GLenum type);

bool vertexAttribType(GLESv2Encoder* ctx, GLenum type);

bool readPixelsFboFormatMatch(GLenum format, GLenum type, GLenum fboTexType);
bool blitFramebufferFormat(GLenum readFormat, GLenum drawFormat);

bool textureTarget(GLESv2Encoder* ctx, GLenum target);

GLsizei compressedTexImageSize(GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);

bool isCompressedFormat(GLenum internalformat);
bool supportedCompressedFormat(GLESv2Encoder* ctx, GLenum internalformat);

bool unsizedFormat(GLenum format);

bool filterableTexFormat(GLESv2Encoder* ctx, GLenum internalformat);
bool colorRenderableFormat(GLESv2Encoder* ctx, GLenum internalformat);
bool depthRenderableFormat(GLESv2Encoder* ctx, GLenum internalformat);
bool stencilRenderableFormat(GLESv2Encoder* ctx, GLenum internalformat);

bool isCubeMapTarget(GLenum target);

bool pixelType(GLESv2Encoder* ctx, GLenum type);
bool pixelFormat(GLESv2Encoder* ctx, GLenum format);

bool pixelInternalFormat(GLenum internalformat);

bool shaderType(GLESv2Encoder* ctx, GLenum type);

bool internalFormatTarget(GLESv2Encoder* ctx, GLenum target);

std::string vertexAttribIndexRangeErrorMsg(GLESv2Encoder* ctx, GLuint index);

} // namespace GLESv2Validation

#endif
