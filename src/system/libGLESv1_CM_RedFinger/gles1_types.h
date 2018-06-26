#ifndef __gles1_wrapper_types_h
#define __gles1_wrapper_types_h

#ifndef GLsync
typedef struct __GLsync *GLsync;
#endif

#include <stdint.h>

typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef void *GLvoidptr;

#include "gl_base_types.h"

#endif

