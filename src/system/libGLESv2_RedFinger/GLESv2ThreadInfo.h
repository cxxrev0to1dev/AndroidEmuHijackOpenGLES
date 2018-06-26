#ifndef GLESV2THREADINFO_H_
#define GLESV2THREADINFO_H_

#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <pthread.h>
#include <bionic_tls.h>
#include <cutils/threads.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "gles_wrapper_context.h"
#include "gles_client_context.h"
#include "GLESv2DispatchInternal.h"
#include "gles_enc.h"
#include "gles_dec.h"
#include "GLESTestStream.h"
#include "GLClientState.h"
#include "GLSharedGroup.h"
#include "ErrorLog.h"



struct GLESv2ThreadInfo
{
    GLESv2ThreadInfo();
    void Free();
    gles_wrapper_context_t* gles_dispatch;
    GLESv2DispatchInternal* encoder_dispatch_hook;
    TestStream* encode_stream;
    GLClientState* gl_client_state;
    GLSharedGroup* gl_shared_group;

};
GLESv2ThreadInfo* getGLESThreadInfo();

#endif