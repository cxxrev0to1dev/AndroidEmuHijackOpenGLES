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
#include "GLESv1ThreadInfo.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <bionic_tls.h>
#include <cutils/threads.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include "eglContext.h"

static void* impl_so = NULL;

static thread_store_t s_tls = THREAD_STORE_INITIALIZER;

static void tlsDestruct(void *ptr)
{
    if (ptr) {
        GLESv1ThreadInfo *ti = (GLESv1ThreadInfo *)ptr;
        // delete ti->encoder_dispatch;
        delete ti->dispatch_hook;
        // delete ti->decoder_dispatch;
        delete ti->encode_stream;
        delete ti;
        ((void **)__get_tls())[TLS_SLOT_OPENGL] = NULL;
    }
}

// static GLESv1ThreadInfo *slow_getEGLThreadInfo()
// {
//     GLESv1ThreadInfo *ti = (GLESv1ThreadInfo *)thread_store_get(&s_tls);
//     if (ti) return ti;

//     ti = new GLESv1ThreadInfo();
//     thread_store_set(&s_tls, ti, tlsDestruct);

//     return ti;
// }

// #ifdef HAVE_ANDROID_OS
//     // We have a dedicated TLS slot in bionic
// GLESv1ThreadInfo* GetGLESv1ThreadInfo() {
//     GLESv1ThreadInfo *tInfo =
//         (GLESv1ThreadInfo *)(((uintptr_t *)__get_tls())[TLS_SLOT_OPENGL]);
//     if (!tInfo) {
//         tInfo = slow_getEGLThreadInfo();
//         ((uintptr_t *)__get_tls())[TLS_SLOT_OPENGL] = (uintptr_t)tInfo;
//     }
//     return tInfo;
// }
// #else
// GLESv1ThreadInfo* GetGLESv1ThreadInfo(){
//     return slow_getEGLThreadInfo();
// }
// #endif

static GLESv1ThreadInfo* (*GetGLESv1ThreadInfoFromGlobalTLS)() = NULL;
GLESv1ThreadInfo* GetGLESv1ThreadInfo(){
    return GetGLESv1ThreadInfoFromGlobalTLS();
}

class ApiInitializer {
public:
    ApiInitializer(void *dso) :
        m_dso(dso) {
    }
    static void *s_getProc(const char *name, void *userData) {
        ApiInitializer *self = (ApiInitializer *)userData;
        return self->getProc(name);
    }
private:
    void *m_dso;
    void *getProc(const char *name) {
        void *symbol = NULL;
        if (m_dso) {
            symbol = dlsym(m_dso, name);
        }
        //ALOGD("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxfunction:%s,%p\n",name,symbol);
        return symbol;
    }
};

GLESv1ThreadInfo::GLESv1ThreadInfo():dispatch_hook(NULL),encode_stream(NULL){
    if (encode_stream==NULL){
        encode_stream = new TestStream;
    }
    if (dispatch_hook == NULL){
        dispatch_hook = new GLESv1DispatchInternal(encode_stream,impl_so);
    }
    ApiInitializer *initializer = new ApiInitializer(impl_so);
    dispatch_hook->GetGLESv1Decoder()->initDispatchByName(ApiInitializer::s_getProc, initializer);
    encode_stream->InitDecode((void*)dispatch_hook->GetGLESv1Decoder());
    encode_stream->InitGLDecodeInterception((void*)dispatch_hook->GetGLESv1Interception());
    dispatch_hook->GetGLESv1WrapperContext()->initDispatchByName(ApiInitializer::s_getProc, initializer);
    delete initializer;
}
void GLESv1ThreadInfo::Free(){
    if (encode_stream!=NULL){
        delete encode_stream;
        encode_stream = NULL;
    }
    if (dispatch_hook!=NULL){
        delete dispatch_hook;
        dispatch_hook = NULL;
    }
}
static RedFingerGLESv1Interception* RedFingerGLESv1InterceptionAccessorType(void){
    RedFingerGLESv1Interception* encoder = GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Interception();
    return encoder;
}
static gles1_wrapper_context_t* getGLESContext(){
    return GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1WrapperContext();
}
static gles1_client_context_t* getGLESClientContext(){
    gles1_encoder_context_t* encoder = GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Encoder();
    gles1_client_context_t* client = dynamic_cast<gles1_client_context_t*>(encoder);
    return client;
}
extern "C"{
    void SetGLESv1DecodeContext(EGLContext_t* context){
        GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Decoder()->setContextData(&context->decoderContextData());
    }
    void SetGLESv1EncodeContext(EGLContext_t* context){
        if (context){
            GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Encoder()->setClientState(context->getClientState());
            GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Encoder()->setSharedGroup((GLSharedGroup*)context->getSharedGroupPtr());
        }
        else{
            GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Encoder()->setClientState(NULL);
            GetGLESv1ThreadInfo()->dispatch_hook->GetGLESv1Encoder()->setSharedGroup(NULL);
        }
    }
    GLESv1ThreadInfo* createFromLib(void *solib,GLESv1ThreadInfo* (accessor)()){
        impl_so = solib;
        GetGLESv1ThreadInfoFromGlobalTLS = accessor;
        RedFingerGLESv1Interception::setContextAccessor(RedFingerGLESv1InterceptionAccessorType);
        gles1_wrapper_context_t::setContextAccessor(getGLESContext);
        gles1_client_context_t::setContextAccessor(getGLESClientContext);
        return new GLESv1ThreadInfo();
    }
}
