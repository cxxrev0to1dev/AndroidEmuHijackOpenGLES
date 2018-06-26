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
#include "ThreadInfo.h"
#include "cutils/threads.h"

thread_store_t s_tls = THREAD_STORE_INITIALIZER;

static void tlsDestruct(void *ptr)
{
    if (ptr) {
        EGLThreadInfo* ti = (EGLThreadInfo*)ptr;
        if (ti->GLESv1) {
            delete ti->GLESv1; 
            ti->GLESv1 = NULL; 
        }
        if (ti->GLESv2) {
            delete ti->GLESv2; 
            ti->GLESv2 = NULL; 
        }
        if (ti->EGLInfo) { 
            delete ti->EGLInfo; 
            ti->EGLInfo = NULL; 
        }
        if (ti->EGLDisp) { 
            delete ti->EGLDisp; 
            ti->EGLDisp = NULL; 
        }
        delete ti;
    }
}

EGLThreadInfo *getEGLThreadInfo()
{
    EGLThreadInfo *ti = (EGLThreadInfo *)thread_store_get(&s_tls);
    if (ti) return ti;
    ti = new EGLThreadInfo();
    ti->GLESv1 = NULL;
    ti->GLESv2 = NULL;
    ti->EGLInfo = NULL;
    ti->EGLDisp = NULL;
    ti->current_context = NULL;
    thread_store_set(&s_tls, ti, tlsDestruct);

    return ti;
}
