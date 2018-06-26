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
#include "redfinger_egl_stream.h"
#include <cutils/sockets.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef _WIN32
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/un.h>
#else
#include <ws2tcpip.h>
#endif

#include "renderControl_dec.h"
#include "redfinger_egl_info.h"
#include "ErrorLog.h"

static RedFingerEGLStream s_writeback;
static pthread_mutex_t s_count_mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  s_condition_var   = PTHREAD_COND_INITIALIZER;

RedFingerEGLStream::RedFingerEGLStream(size_t bufSize) :
    IOStream(bufSize),
    m_sock(-1),
    m_bufsize(bufSize),
    m_buf(NULL),
    writeback_class_(NULL){
}

RedFingerEGLStream::RedFingerEGLStream(int sock, size_t bufSize) :
    IOStream(bufSize),
    m_sock(sock),
    m_bufsize(bufSize),
    m_buf(NULL),
    writeback_class_(NULL)
{
}

RedFingerEGLStream::~RedFingerEGLStream()
{
    if (m_sock >= 0) {
#ifdef _WIN32
        closesocket(m_sock);
#else
        ::close(m_sock);
#endif
    }
    if (m_buf != NULL) {
        free(m_buf);
        m_buf = NULL;
    }
}


void *RedFingerEGLStream::allocBuffer(size_t minSize)
{
    size_t allocSize = (m_bufsize < minSize ? minSize : m_bufsize);
    if (!m_buf) {
        m_buf = (unsigned char *)malloc(allocSize);
    }
    else if (m_bufsize < allocSize) {
        unsigned char *p = (unsigned char *)realloc(m_buf, allocSize);
        if (p != NULL) {
            m_buf = p;
            m_bufsize = allocSize;
        } else {
            ERR("%s: realloc (%zu) failed\n", __FUNCTION__, allocSize);
            free(m_buf);
            m_buf = NULL;
            m_bufsize = 0;
        }
    }

    return m_buf;
};

int RedFingerEGLStream::commitBuffer(size_t size)
{
//  RedFinger:20170926{
    return TestFully(m_buf,size);
//  }RedFinger:20170926
    return writeFully(m_buf, size);
}

int RedFingerEGLStream::writebackBuffer(size_t size){
    pthread_mutex_lock( &s_count_mutex );
    writeback_length_ = size;
    bufptr_ = m_buf;
    //ALOGD("xxxxxxxxxxxxxxxxxxxxxrun functionxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_1:%s,%d\n",__func__,__LINE__);
    pthread_mutex_unlock( &s_count_mutex );
    return 0;
}

int RedFingerEGLStream::writeFully(const void* buffer, size_t size)
{
    if (!valid()) return -1;

    size_t res = size;
    int retval = 0;

    while (res > 0) {
        ssize_t stat = ::send(m_sock, (const char *)buffer + (size - res), res, 0);
        if (stat < 0) {
            if (errno != EINTR) {
                retval =  stat;
                ERR("%s: failed: %s\n", __FUNCTION__, strerror(errno));
                break;
            }
        } else {
            res -= stat;
        }
    }
    return retval;
}
//  RedFinger:20170926{
int RedFingerEGLStream::TestFully(const void *buf, size_t len){
    //ALOGD("xxxxxxxxxxxxxxxxxxxxxrun functionxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_2:%s,%d\n",__func__,__LINE__);
    renderControl_decoder_context_t* gles_decode = (renderControl_decoder_context_t*)(decode_this_);
    void* bbb = malloc(len+20);
    memset(bbb,0,len+20);
    memcpy(bbb,buf,len);
    int rvalue = 0;
    if (!writeback_class_){
        writeback_class_ = new RedFingerEGLStream;
    }
    rvalue = gles_decode->decode(bbb,len,writeback_class_);
    free(bbb);
    return rvalue;
    //ALOGD("xxxxxxxxxxxxxxxxxxxxxrun functionxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_3:%s,%d\n",__func__,__LINE__);
}
void RedFingerEGLStream::InitDecode(void* decode_this){
    decode_this_ = decode_this;
}
//  }RedFinger:20170926
const unsigned char *RedFingerEGLStream::readFully(void *buf, size_t len)
{
    pthread_mutex_lock( &s_count_mutex );
    //ALOGD("xxxxxxxxxxxxxxxxxxxxxrun functionxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_1:%s,%d\n",__func__,__LINE__);

    //memmove(buf,writeback_class_->m_buf,writeback_class_->WriteBackLength());
    //writeback_class_->writeback_length_ = 0;
    memmove(buf,writeback_class_->bufptr_,len);
    writeback_class_->bufptr_ += len;
    writeback_class_->writeback_length_ = 0;

    pthread_mutex_unlock( &s_count_mutex );
    return (const unsigned char *)buf;

    const unsigned char* ret = NULL;
    if (!valid()) return NULL;
    if (!buf) {
      return NULL;  // do not allow NULL buf in that implementation
    }
    size_t res = len;
    while (res > 0) {
        ssize_t stat = ::recv(m_sock, (char *)(buf) + len - res, res, 0);
        if (stat > 0) {
            res -= stat;
            continue;
        }
        if (stat == 0 || errno != EINTR) { // client shutdown or error
            return NULL;
        }
    }
    return (const unsigned char *)buf;
}

const unsigned char *RedFingerEGLStream::read( void *buf, size_t *inout_len)
{
    if (!valid()) return NULL;
    if (!buf) {
      return NULL;  // do not allow NULL buf in that implementation
    }

    int n;
    do {
        n = recv(buf, *inout_len);
    } while( n < 0 && errno == EINTR );

    if (n > 0) {
        *inout_len = n;
        return (const unsigned char *)buf;
    }

    return NULL;
}

int RedFingerEGLStream::recv(void *buf, size_t len)
{
    if (!valid()) return int(ERR_INVALID_SOCKET);
    int res = 0;
    while(true) {
        res = ::recv(m_sock, (char *)buf, len, 0);
        if (res < 0) {
            if (errno == EINTR) {
                continue;
            }
        }
        break;
    }
    return res;
}
