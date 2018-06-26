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
#include "goldfish_gralloc_receive.h"
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#include "gralloc_cb.h"
#include "glUtils.h"
#include "goldfish_gralloc_base.h"

/* Set to 1 or 2 to enable debug traces */
#define DEBUG  0

#if DEBUG >= 1
#  define D(...)   ALOGD(__VA_ARGS__)
#else
#  define D(...)   ((void)0)
#endif

#if DEBUG >= 2
#  define DD(...)  ALOGD(__VA_ARGS__)
#else
#  define DD(...)  ((void)0)
#endif

#define DBG_FUNC DBG("%s\n", __FUNCTION__)

namespace GoldfishGralloc{

private_module_t* GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::sFallback = NULL;

void GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::FallbackInit(void){
    GoldfishGrallocBase base;
    if (base.IsQemuEmulatorGLES()||base.GrallocModulePath()==NULL){
        return;
    }
    ALOGD("Emulator without GPU emulation detected.");
    void* module = dlopen(base.GrallocModulePath(), RTLD_LAZY|RTLD_LOCAL);
    if (module != NULL) {
        sFallback = reinterpret_cast<private_module_t*>(dlsym(module, HAL_MODULE_INFO_SYM_AS_STR));
        if (sFallback == NULL) {
            dlclose(module);
        }
    }
    if (sFallback == NULL) {
        ALOGE("Could not find software fallback module!?");
    }
}
GoldfishGrallocReceive::GoldfishGrallocReceive(){
    decode(NULL,0,NULL);
}
GoldfishGrallocReceive::~GoldfishGrallocReceive(){

}
size_t GoldfishGrallocReceive::decode(void *buf, size_t len, IOStream *stream){
    size_t pos = 0;
    if (len < (sizeof(ssize_t) * 2)) 
        return pos;
    unsigned char *ptr = (unsigned char*)buf;
    bool unknownOpcode = false;
    while ((len - pos >= (sizeof(ssize_t) * 2)) && !unknownOpcode) {
        GoldfishGrallocNativeFuncTable opcode = Unpack<GoldfishGrallocNativeFuncTable,size_t>(ptr);
        size_t packetLen = Unpack<ssize_t,size_t>(ptr + sizeof(ssize_t));
        const ssize_t size_base = (sizeof(ssize_t) * 2);
        const ssize_t sb = size_base;
        if (len - pos < packetLen) 
            return pos;
        switch(opcode) {
            case GoldfishGrallocNativeFuncTable::kGrallocRegisterBuffer:{
                gralloc_module_t const* module = Unpack<gralloc_module_t const*,size_t>(ptr + sb);
                buffer_handle_t handle = Unpack<buffer_handle_t,size_t>(ptr + sb + sizeof(ssize_t));
                break;
            }
            case GoldfishGrallocNativeFuncTable::kGrallocUnregisterBuffer:{
                gralloc_module_t const* module = Unpack<gralloc_module_t const*,size_t>(ptr + sb);
                buffer_handle_t handle = Unpack<buffer_handle_t,size_t>(ptr + sb + sizeof(ssize_t));
                break;
            }
            case GoldfishGrallocNativeFuncTable::kGrallocLock:{
                gralloc_module_t const* module = Unpack<gralloc_module_t const*,size_t>(ptr + sb);
                buffer_handle_t handle = Unpack<buffer_handle_t,size_t>(ptr + sb + sizeof(ssize_t));
                int usage = Unpack<int,size_t>(ptr + sb + (sizeof(size_t) * 2));
                int l = Unpack<int,size_t>(ptr + sb + (sizeof(size_t) * 2) + (sizeof(int) * 1));
                int t = Unpack<int,size_t>(ptr + sb + (sizeof(size_t) * 2) + (sizeof(int) * 2));
                int w = Unpack<int,size_t>(ptr + sb + (sizeof(size_t) * 2) + (sizeof(int) * 3));
                int h = Unpack<int,size_t>(ptr + sb + (sizeof(size_t) * 2) + (sizeof(int) * 4));
                ssize_t size_vaddr = Unpack<ssize_t,size_t>(ptr + sb + (sizeof(size_t) * 2) + (sizeof(int) * 5));
                break;
            }
            case GoldfishGrallocNativeFuncTable::kGrallocUnlock:{
                gralloc_module_t const* module = Unpack<gralloc_module_t const*,size_t>(ptr + sb);
                buffer_handle_t handle = Unpack<buffer_handle_t,size_t>(ptr + sb + sizeof(ssize_t));
                break;
            }
            case GoldfishGrallocNativeFuncTable::kGrallocDeviceOpen:{
                break;
            }
            break;
            default:
            unknownOpcode = true;
            break;
        }
    }
    return pos;
}
private_module_t* GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::sFallbackPtr(){
    return sFallback;
}
gralloc_module_t* GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::GrallocNativeFuncPtr(){
    return &(sFallback->base);
}
bool GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::InitOnce(){
    static pthread_once_t sFallbackOnce = PTHREAD_ONCE_INIT;
    return (pthread_once(&sFallbackOnce, FallbackInit)==0);
}

int GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::gralloc_register_buffer(gralloc_module_t const* module,buffer_handle_t handle){
    if (InitOnce()&&GrallocNativeFuncPtr() != NULL) {
        return GrallocNativeFuncPtr()->registerBuffer(module, handle);
    }
    return -EINVAL;
}

int GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::gralloc_unregister_buffer(gralloc_module_t const* module,buffer_handle_t handle){
    if (GrallocNativeFuncPtr() != NULL) {
        return GrallocNativeFuncPtr()->unregisterBuffer(module, handle);
    }
    return -EINVAL;
}

int GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::gralloc_lock(gralloc_module_t const* module,buffer_handle_t handle, int usage,
                                                                int l, int t, int w, int h,void** vaddr){
    if (GrallocNativeFuncPtr() != NULL) {
        return GrallocNativeFuncPtr()->lock(module, handle, usage, l, t, w, h, vaddr);
    }
    return -EINVAL;
}

int GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::gralloc_unlock(gralloc_module_t const* module,buffer_handle_t handle){
    if (GrallocNativeFuncPtr() != NULL) {
        return GrallocNativeFuncPtr()->unlock(module, handle);
    }
    return -EINVAL;
}

int GoldfishGrallocReceive::GoldfishGrallocHardwareNativeFunc::gralloc_device_open(const hw_module_t* module,const char* name,hw_device_t** device){
    if (InitOnce()&&GrallocNativeFuncPtr()!=NULL){
        private_module_t* p = sFallbackPtr();
        return GrallocNativeFuncPtr()->common.methods->open(&p->base.common, name, device);
    }
    return -EINVAL;
}
}