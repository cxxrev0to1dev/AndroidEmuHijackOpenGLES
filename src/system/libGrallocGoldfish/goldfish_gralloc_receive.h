#ifndef GOLDFISH_GRALLOC_RECEIVE_H_
#define GOLDFISH_GRALLOC_RECEIVE_H_

#include "goldfish_gralloc_android_v7.h"
#include "IOStream.h"

namespace GoldfishGralloc{

class GoldfishGrallocReceive{
public:
	class GoldfishGrallocHardwareNativeFunc
	{
	public:
		static void FallbackInit(void);
		GoldfishGrallocHardwareNativeFunc(){}
		virtual ~GoldfishGrallocHardwareNativeFunc(){}
		private_module_t* sFallbackPtr();
		gralloc_module_t* GrallocNativeFuncPtr();
		int gralloc_register_buffer(gralloc_module_t const* module,buffer_handle_t handle);
		int gralloc_unregister_buffer(gralloc_module_t const* module,buffer_handle_t handle);
		int gralloc_lock(gralloc_module_t const* module,buffer_handle_t handle, int usage,int l, int t, int w, int h,void** vaddr);
		int gralloc_unlock(gralloc_module_t const* module,buffer_handle_t handle);
		int gralloc_device_open(const hw_module_t* module,const char* name,hw_device_t** device);
	private:
		bool InitOnce();
		static private_module_t* sFallback;
	};
	GoldfishGrallocReceive();
	virtual ~GoldfishGrallocReceive();
	size_t decode(void *buf, size_t len, IOStream *stream);
};

}

#endif