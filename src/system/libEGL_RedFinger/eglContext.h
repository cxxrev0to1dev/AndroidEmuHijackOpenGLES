#ifndef __LIBEGL_REDFINGER_EGLCONTEXT_T_H_
#define __LIBEGL_REDFINGER_EGLCONTEXT_T_H_

#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <pthread.h>
#include <bionic_tls.h>
#include <cutils/threads.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "GLDecoderContextData.h"
#include "goldfish_sync.h"

struct EGLContext_t {

    enum {
        IS_CURRENT      =   0x00010000,
        NEVER_CURRENT   =   0x00020000
    };

    EGLContext_t(EGLDisplay dpy, EGLContext context, EGLConfig config, EGLContext_t* shareCtx, EGLint maj, EGLint min);
    virtual ~EGLContext_t();
    uint32_t            flags;
    EGLDisplay          dpy;
    EGLConfig           config;
    EGLSurface          read;
    EGLSurface          draw;
    EGLContext          context;
    EGLContext_t    *   shareCtx;
    EGLint              version;
    EGLint              majorVersion;
    EGLint              minorVersion;
    EGLint              deviceMajorVersion;
    EGLint              deviceMinorVersion;
    char*         versionString;
    char*         vendorString;
    char*         rendererString;
    char*         extensionString;
    EGLint              deletePending;
    void AddVersionString(const char* str);
    void AddVendorString(const char* str);
    void AddExtensionString(const char* str);
    GLClientState* getClientState(){ return clientState; }
    void* getSharedGroupPtr(){ 
        return sharedGroup.Ptr(); 
    }
    GLDecoderContextData& decoderContextData() { return decoder_context_data; }
    int getGoldfishSyncFd(){
        if (goldfishSyncFd < 0) {
            goldfishSyncFd = goldfish_sync_open();
        }
        return goldfishSyncFd;
    }
private:
    GLSharedGroupPtr getSharedGroup(){ 
        return sharedGroup; 
    }
    GLClientState* clientState;
    GLSharedGroupPtr sharedGroup;
    GLDecoderContextData decoder_context_data;
    int goldfishSyncFd;
};

#endif