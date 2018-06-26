#ifndef GLES_V1_THREAD_INFO_H_
#define GLES_V1_THREAD_INFO_H_

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
#include "GLESv1DispatchInternal.h"
#include "GLESTestStream.h"
#include "GLClientState.h"
#include "GLSharedGroup.h"
#include "ErrorLog.h"



struct GLESv1ThreadInfo
{
    GLESv1ThreadInfo();
    void Free();
    GLESv1DispatchInternal* dispatch_hook;
    TestStream* encode_stream;
};

GLESv1ThreadInfo* GetGLESv1ThreadInfo();


#endif