#ifndef DEBUG_REDFINGER_DEBUG_H_
#define DEBUG_REDFINGER_DEBUG_H_

#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ErrorLog.h"

namespace RedFinger{
namespace Debug{
  static bool IsDebugPrint(){
    return false;
  }
  static bool IsDdgEGL(){
    return true;
  }
  static bool IsOverrideEGLWithRedFingerImpl(){
    return false;
  }
  static bool IsOverrideGLESv2FuncWithNativeFuncCall(){
    return false;
  }
  static bool IsCancelOverrideEGLContextType(){
    return false;
  }
  static const std::string& GetApplicationName(){
    std::ifstream comm("/proc/self/comm");
    std::string name;
    getline(comm, name);
    return name;
  }
  static bool IsZygoteProcess(){
      return (GetApplicationName()=="zygote");
  }
}
}

#define BEGIN_DEBUG_FUNC  if(0) ALOGD("BEGIN_DEBUG_FUNC:%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__)
#define END_DEBUG_FUNC  if(0) ALOGD("END_DEBUG_FUNC:%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__)
#define FUNC_RETURN_ADDR_TRACE  \
  Dl_info info; \
  dladdr(__builtin_return_address(0), &info); \
  ALOGD("FUNC_RETURN_ADDR_TRACE:%s:%s:%d:dli_fname %s:dli_fbase %p:dli_sname %s:dli_saddr %p\n",__FILE__, __FUNCTION__, __LINE__,info.dli_fname,info.dli_fbase,info.dli_sname,info.dli_saddr);

#endif