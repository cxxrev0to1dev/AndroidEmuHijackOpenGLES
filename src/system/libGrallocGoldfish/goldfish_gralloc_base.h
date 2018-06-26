#ifndef GOLDFISH_GRALLOC_BASE_H_
#define GOLDFISH_GRALLOC_BASE_H_

#include <sys/mman.h>
#include <cutils/ashmem.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include <cutils/native_handle.h>
#include <linux/fb.h>
#include <hardware/gralloc.h>
#include <string>

namespace GoldfishGralloc{

template <typename T, typename S>
struct UnpackerT {
    static T unpack(const void* ptr) {
        static_assert(sizeof(T) == sizeof(S),"Bad input arguments, have to be of the same size");
        return *(const T*)ptr;
    }
};

template <typename T, typename S>
struct UnpackerT<T*, S> {
    static T* unpack(const void* ptr) {
        return (T*)(uintptr_t)(*(const S*)ptr);
    }
};

template <>
struct UnpackerT<ssize_t, uint32_t> {
    static ssize_t unpack(const void* ptr) {
        return (ssize_t)*(const int32_t*)ptr;
    }
};

template <typename T, typename S>
inline T Unpack(const void* ptr) {
    return UnpackerT<T, S>::unpack(ptr);
}

template <typename T>
struct PackToSizeT{
	static ssize_t ToSizeT(T arg){
        static_assert(sizeof(ssize_t) == sizeof(T),"Bad input arguments, have to be of the same size");
        return reinterpret_cast<ssize_t>(arg);
	}
	static ssize_t PtrToSizeT(T* arg){
		static_assert(sizeof(ssize_t) == sizeof(T*),"Bad input arguments, have to be of the same size");
        return reinterpret_cast<ssize_t>(arg);
	}
	static ssize_t ConstPtrToSizeT(const T* arg){
		static_assert(sizeof(ssize_t) == sizeof(const T*),"Bad input arguments, have to be of the same size");
        return reinterpret_cast<ssize_t>(arg);
	}
};

enum class GoldfishGrallocNativeFuncTable{
	kGrallocRegisterBuffer = 0x7656,
	kGrallocUnregisterBuffer,
	kGrallocLock,
	kGrallocUnlock,
	kGrallocDeviceOpen
};

class GoldfishGrallocBase
{
public:
    GoldfishGrallocBase();
    virtual ~GoldfishGrallocBase();
    bool IsQemuEmulatorGLES();
    const char* GrallocModulePath();
private:
    bool HWGetGrallocModule(char* out,size_t out_len);
    int HWGetModule(const char *id,char* out,size_t out_len);

    std::string gralloc_path_;
};
}

#endif