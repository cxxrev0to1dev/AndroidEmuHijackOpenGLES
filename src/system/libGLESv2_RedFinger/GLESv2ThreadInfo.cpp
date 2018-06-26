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
#include "GLESv2ThreadInfo.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <bionic_tls.h>
#include <cutils/threads.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include "gles_wrapper_context.h"
#include "gles_client_context.h"
#include "gles_enc.h"
#include "gles_dec.h"
#include "GLESTestStream.h"
#include "GLClientState.h"
#include "GLSharedGroup.h"
#include "ErrorLog.h"
#include "eglContext.h"

static void* impl_so = NULL;

static thread_store_t s_tls = THREAD_STORE_INITIALIZER;

static void tlsDestruct(void *ptr)
{
    if (ptr) {
        GLESv2ThreadInfo *ti = (GLESv2ThreadInfo *)ptr;
        delete ti->gles_dispatch;
        // delete ti->encoder_dispatch;
        delete ti->encoder_dispatch_hook;
        // delete ti->decoder_dispatch;
        delete ti->encode_stream;
        delete ti->gl_client_state;
        delete ti->gl_shared_group;
        delete ti;
        ((void **)__get_tls())[TLS_SLOT_OPENGL] = NULL;
    }
}


static GLESv2ThreadInfo *slow_getEGLThreadInfo()
{
    GLESv2ThreadInfo *ti = (GLESv2ThreadInfo *)thread_store_get(&s_tls);
    if (ti) return ti;

    ti = new GLESv2ThreadInfo();
    thread_store_set(&s_tls, ti, tlsDestruct);

    return ti;
}
// #ifdef HAVE_ANDROID_OS
//     // We have a dedicated TLS slot in bionic
// GLESv2ThreadInfo* getGLESThreadInfo() {
//     GLESv2ThreadInfo *tInfo =
//         (GLESv2ThreadInfo *)(((uintptr_t *)__get_tls())[TLS_SLOT_OPENGL]);
//     if (!tInfo) {
//         tInfo = slow_getEGLThreadInfo();
//         ((uintptr_t *)__get_tls())[TLS_SLOT_OPENGL] = (uintptr_t)tInfo;
//     }
//     return tInfo;
// }
// #else
// GLESv2ThreadInfo* getGLESThreadInfo(){
//     return slow_getEGLThreadInfo();
// }
// #endif

static GLESv2ThreadInfo* (*GetGLESv2ThreadInfoFromGlobalTLS)() = NULL;

GLESv2ThreadInfo* getGLESThreadInfo(){
    return GetGLESv2ThreadInfoFromGlobalTLS();
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

GLESv2ThreadInfo::GLESv2ThreadInfo():
    gles_dispatch(NULL),
    // encoder_dispatch(NULL),
    encoder_dispatch_hook(NULL),
    // decoder_dispatch(NULL),
    encode_stream(NULL),
    gl_client_state(NULL),
    gl_shared_group(NULL){
       if (encode_stream==NULL){
            encode_stream = new TestStream;
        }
        if (gles_dispatch == NULL){
            gles_dispatch = new gles_wrapper_context_t;
        }
        if (encoder_dispatch_hook == NULL)
        {
            encoder_dispatch_hook = new GLESv2DispatchInternal(encode_stream);
        }
        if (gl_client_state == NULL){
            gl_client_state = new GLClientState;
        }
        if (gl_shared_group == NULL){
            gl_shared_group = new GLSharedGroup;
        }
        ApiInitializer *initializer = new ApiInitializer(impl_so);
        encoder_dispatch_hook->GetDecoder()->initDispatchByName(ApiInitializer::s_getProc, initializer);
        encode_stream->InitDecode((void*)encoder_dispatch_hook->GetDecoder());
        encode_stream->InitEGLDecode((void*)encoder_dispatch_hook->GetEGLDispatch()->GetRedFingerEGLDecoder());
        encode_stream->InitGLDecodeInterception((void*)encoder_dispatch_hook->GetGLInterception());
        gles_dispatch->initDispatchByName(ApiInitializer::s_getProc, initializer);
        delete initializer;
}
void GLESv2ThreadInfo::Free(){
    if (encode_stream!=NULL){
        delete encode_stream;
        encode_stream = NULL;
    }
    if (gles_dispatch != NULL){
        delete gles_dispatch;
        gles_dispatch = NULL;
    }
    if (encoder_dispatch_hook != NULL){
        delete encoder_dispatch_hook;
        encoder_dispatch_hook = NULL;
    }
    if (gl_client_state != NULL){
        delete gl_client_state;
        gl_client_state = NULL;
    }
    if (gl_shared_group != NULL){
        delete gl_shared_group;
        gl_shared_group = NULL;
    }
}

static gles_wrapper_context_t* getGLESContext(){
    GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    return result_derived->gles_dispatch;
}
static gles_client_context_t* getGLESClientContext(){
    GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    gles_encoder_context_t* encoder = result_derived->encoder_dispatch_hook->GetEncoder();
    gles_client_context_t* client = dynamic_cast<gles_client_context_t*>(encoder);
    return client;
}
static RedFingerEGLDispatch* RedFingerEGLDispatchAccessorType(void){
    GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    RedFingerEGLDispatch* encoder = result_derived->encoder_dispatch_hook->GetEGLDispatch();
    return encoder;
}
static RedFingerGLInterception* RedFingerGLInterceptionAccessorType(void){
    GLESv2ThreadInfo* result_derived = getGLESThreadInfo();
    RedFingerGLInterception* encoder = result_derived->encoder_dispatch_hook->GetGLInterception();
    return encoder;
}
extern "C"{
    void InitState(int major, int minor,int deviceMajor, int deviceMinor,GLClientState* state){
        GLESv2Encoder* gles3_encoder = getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr();
        if (state->needsInitFromCaps()){
            gles3_encoder->setVersion(major,minor,deviceMajor,deviceMinor);
            int max_transform_feedback_separate_attribs = 0;
            int max_uniform_buffer_bindings = 0;
            int max_atomic_counter_buffer_bindings = 0;
            int max_shader_storage_buffer_bindings = 0;
            int max_vertex_attrib_bindings = 0;
            int max_color_attachments = 1;
            int max_draw_buffers = 1;
           if (major > 2) {
                gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, &max_transform_feedback_separate_attribs);
                gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_UNIFORM_BUFFER_BINDINGS, &max_uniform_buffer_bindings);
                if (minor > 0) {
                    gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS, &max_atomic_counter_buffer_bindings);
                    gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &max_shader_storage_buffer_bindings);
                    gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_vertex_attrib_bindings);
                }
                gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);
                gles3_encoder->glGetIntegerv(gles3_encoder,GL_MAX_DRAW_BUFFERS, &max_draw_buffers);
            }
            //InitState:device/generic/goldfish/opengl.new/system/wrapperDir/GLESWrapper.cpp:InitState:160:colorAttachmentIndex 0x4:0x24:0x0:0x0:0x0:0x4:0x4
            //test mobile phone default data
            // please fix me (glGetIntegerv(GL_xxx,&xxx)==0)
            // if (!max_transform_feedback_separate_attribs){
            //     max_transform_feedback_separate_attribs = 0x4;
            // }
            // if (!max_uniform_buffer_bindings){
            //     max_uniform_buffer_bindings = 0x24;
            // }
            // if (max_color_attachments<=1){
            //     max_color_attachments = 0x4;
            // }
            // if (max_draw_buffers<=1){
            //     max_draw_buffers = 4;
            // }
            state->initFromCaps(max_transform_feedback_separate_attribs,
                    max_uniform_buffer_bindings,
                    max_atomic_counter_buffer_bindings,
                    max_shader_storage_buffer_bindings,
                    max_vertex_attrib_bindings,
                    max_color_attachments,
                    max_draw_buffers);
            //InitState:device/generic/goldfish/opengl.new/system/wrapperDir/GLESWrapper.cpp:InitState:153:colorAttachmentIndex 0x0:0x0:0x0:0x0:0x0:0x0:0x0
            //fix me glGetIntegerv max_transform_feedback_separate_attribs .... 0?
            //fix me GLClientState::attachTextureObject
            ALOGE("InitState:%s:%s:%d:colorAttachmentIndex %p:%p:%p:%p:%p:%p:%p\n", __FILE__, __FUNCTION__, __LINE__,
                    max_transform_feedback_separate_attribs,
                    max_uniform_buffer_bindings,
                    max_atomic_counter_buffer_bindings,
                    max_shader_storage_buffer_bindings,
                    max_vertex_attrib_bindings,
                    max_color_attachments,
                    max_draw_buffers);
        }
        // if (major > 1) {
        //     gles3_encoder->setClientStateMakeCurrent(state,major,minor,deviceMajor,deviceMinor);
        // }
    }
    void SetServerContext(EGLContext_t* context){
        getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2DecPtr()->setContextData(&context->decoderContextData());
    }
    void SetGL2ClientContext(EGLContext_t* context){
        if (context){
            getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr()->setClientState(context->getClientState());
            getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr()->setSharedGroup((GLSharedGroup*)context->getSharedGroupPtr());
        }
        else{
            getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr()->setClientState(NULL);
            getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr()->setSharedGroup(NULL);
        }
    }
    void SetGL2ClientStateMakeCurrent(EGLContext_t* context,GLClientState* state,int majorVersion,int minorVersion,int deviceMajorVersion,int deviceMinorVersion){
        if (context){
            getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr()->setClientStateMakeCurrent(state,context->majorVersion,context->minorVersion,
                context->deviceMajorVersion,context->deviceMinorVersion);
            getGLESThreadInfo()->encoder_dispatch_hook->GetGLESv2EncPtr()->setSharedGroup((GLSharedGroup*)context->getSharedGroupPtr());
        }
    }
    GLESv2ThreadInfo* createFromLib(void *solib,GLESv2ThreadInfo* (accessor)()){
        impl_so = solib;
        GetGLESv2ThreadInfoFromGlobalTLS = accessor;
        RedFingerEGLDispatch::setContextAccessor(RedFingerEGLDispatchAccessorType);
        RedFingerGLInterception::setContextAccessor(RedFingerGLInterceptionAccessorType);
        gles_wrapper_context_t::setContextAccessor(getGLESContext);
        gles_client_context_t::setContextAccessor(getGLESClientContext);
        return new GLESv2ThreadInfo();
    }
}
