#ifndef __renderControl_wrapper_types_h
#define __renderControl_wrapper_types_h

#ifndef GLsync
typedef struct __GLsync *GLsync;
#endif

#include <stdint.h>

typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef void *GLvoidptr;

#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>


#include <stdint.h>
#include <EGL/egl.h>
#include "glUtils.h"

// values for 'param' argument of rcGetFBParam
#define FB_WIDTH    1
#define FB_HEIGHT   2
#define FB_XDPI     3
#define FB_YDPI     4
#define FB_FPS      5
#define FB_MIN_SWAP_INTERVAL 6
#define FB_MAX_SWAP_INTERVAL 7


#include "gl_base_types.h"

#endif

