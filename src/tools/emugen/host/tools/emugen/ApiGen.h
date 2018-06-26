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
#ifndef __API_GEN_H_
#define __API_GEN_H_

#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "EntryPoint.h"


class ApiGen : public std::vector<EntryPoint> {

public:
    typedef std::vector<std::string> StringVec;
    typedef enum { CLIENT_SIDE, SERVER_SIDE, WRAPPER_SIDE } SideType;

    ApiGen(const std::string & basename) :
        m_basename(basename),
        m_maxEntryPointsParams(0),
        m_baseOpcode(0){
        api_define_.resize(0);
        aemu_funcs_.resize(0);
    }
    virtual ~ApiGen() {}
    //  RedFinger:20170925{
    void RedefineUnknownStruct(FILE* fp);
    bool IsAEMUFuncName(const EntryPoint* ref);
    void AddAEMUFunc(const EntryPoint* ref);
    bool FuncInAEMUFuncs(const EntryPoint* ref);
    bool IsDebugTestAPI(const EntryPoint* ref);
    bool IsUnsupported(const EntryPoint& ref);
    bool IsRedefineAPI(const EntryPoint& ref);
    bool IsRedefineArrayAPI(const EntryPoint& ref);
    bool IsGLTexSubImage2D(const EntryPoint* ref);
    bool IsSmallParameterFunctionPointer(EntryPoint* ref);
    bool IsInOutParameterFunctionPointer(EntryPoint* ref);
    bool IsLargeDataArgFunctionPointer(EntryPoint* ref);
    //  }RedFinger:20170925
    int readSpec(const std::string & filename,SideType side);
    int readAttributes(const std::string & attribFilename);
    size_t maxEntryPointsParams() {  return m_maxEntryPointsParams; }
    void updateMaxEntryPointsParams(size_t val) {
        if (m_maxEntryPointsParams == 0 || val > m_maxEntryPointsParams) m_maxEntryPointsParams = val;
    }
    int baseOpcode() { return m_baseOpcode; }
    void setBaseOpcode(int base) { m_baseOpcode = base; }

    const char *sideString(SideType side) {
        const char *retval;
        switch(side) {
        case CLIENT_SIDE:
            retval = "client";
            break;
        case SERVER_SIDE:
            retval = "server";
            break;
        case WRAPPER_SIDE:
            retval = "wrapper";
            break;
        default:
            retval = "unknown";
        }
        return retval;
    }

    StringVec & clientContextHeaders() { return m_clientContextHeaders; }
    StringVec & encoderHeaders() { return m_encoderHeaders; }
    StringVec & serverContextHeaders() { return m_serverContextHeaders; }
    StringVec & decoderHeaders() { return m_decoderHeaders; }

    EntryPoint * findEntryByName(const std::string & name);
    int genOpcodes(const std::string &filename);
    int genAttributesTemplate(const std::string &filename);
    int genProcTypes(const std::string &filename, SideType side);
    int genFuncTable(const std::string &filename, SideType side);

    int genContext(const std::string &filename, SideType side);
    int genContextImpl(const std::string &filename, SideType side);
//  RedFinger:20170925{
    int genTypeFile(const std::string &filename, SideType side);
//  }RedFinger:20170925
    int genEntryPoints(const std::string &filename, SideType side);

    int genEncoderHeader(const std::string &filename);
    int genEncoderImpl(const std::string &filename);

    int genDecoderHeader(const std::string &filename);
    int genDecoderImpl(const std::string &filename);

protected:
    virtual void printHeader(FILE *fp) const;

    std::vector<EntryPoint> api_define_;
    std::vector<std::string> aemu_funcs_;
    std::string m_basename;
    StringVec m_clientContextHeaders;
    StringVec m_encoderHeaders;
    StringVec m_serverContextHeaders;
    StringVec m_decoderHeaders;
    size_t m_maxEntryPointsParams; // record the maximum number of parameters in the entry points;
    int m_baseOpcode;
    int setGlobalAttribute(const std::string & line, size_t lc);
};

#endif
