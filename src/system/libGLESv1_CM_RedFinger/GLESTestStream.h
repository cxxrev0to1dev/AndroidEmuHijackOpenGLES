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
#ifndef __SOCKET_STREAM_H
#define __SOCKET_STREAM_H

#include <stdlib.h>
#include "IOStream.h"


class TestStream : public IOStream {
public:
    typedef enum { ERR_INVALID_SOCKET = -1000 } TestError;

    explicit TestStream(size_t bufsize = 1024*1024*20/*10000*/);
    virtual ~TestStream();

    virtual void *allocBuffer(size_t minSize);
    virtual int commitBuffer(size_t size);
    virtual int writebackBuffer(size_t size);
    virtual const unsigned char *readFully(void *buf, size_t len);
    virtual const unsigned char *read(void *buf, size_t *inout_len);

    bool valid() { return m_sock >= 0; }
    virtual int recv(void *buf, size_t len);
    virtual int writeFully(const void *buf, size_t len);
    
    virtual int TestFully(const void *buf, size_t len);

    virtual void InitDecode(void* decode_this);
    virtual void InitGLDecodeInterception(void* decode_this){
        gl_decodeInterception_this_ = decode_this;
    }
private:
    size_t WriteBackLength() const{
        return writeback_length_;
    }
private:
    unsigned char *bufptr_;
    size_t  writeback_length_;
    TestStream* writeback_class_;
protected:
    int            m_sock;
    size_t         m_bufsize;       
    unsigned char *m_buf;
    void* decode_this_;
    void* gl_decodeInterception_this_;

    TestStream(int sock, size_t bufSize);
};

class WritebackStream : public IOStream {
public:
    explicit WritebackStream(size_t bufsize = 10000);
    virtual ~WritebackStream();
    
};


#endif /* __SOCKET_STREAM_H */
