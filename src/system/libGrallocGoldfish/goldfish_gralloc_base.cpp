#include "goldfish_gralloc_base.h"


#if __LP64__
static const char * HAL_LIBRARY_PATH1 = "/system/lib64/hw";
static const char * HAL_LIBRARY_PATH2 = "/vendor/lib64/hw";
#else
static const char * HAL_LIBRARY_PATH1 = "/system/lib/hw";
static const char * HAL_LIBRARY_PATH2 = "/vendor/lib/hw";
#endif

namespace GoldfishGralloc{

GoldfishGrallocBase::GoldfishGrallocBase(){
    gralloc_path_.resize(0);
    char path[PATH_MAX] = {0};
    if(!HWGetGrallocModule(path,PATH_MAX)){
        gralloc_path_ = path;
    }
}
GoldfishGrallocBase::~GoldfishGrallocBase(){
    gralloc_path_.resize(0);
}
const char* GoldfishGrallocBase::GrallocModulePath(){
    if (gralloc_path_.length()>0){
        return gralloc_path_.c_str();
    }
    return NULL;
}
bool GoldfishGrallocBase::IsQemuEmulatorGLES(){
    char  prop[PROPERTY_VALUE_MAX];
    property_get("ro.kernel.qemu.gles", prop, "0");
    return (atoi(prop) > 0);
}
bool GoldfishGrallocBase::HWGetGrallocModule(char* out,size_t out_len){
    return (HWGetModule("gralloc",out,out_len)<=0);
}
int GoldfishGrallocBase::HWGetModule(const char *id,char* out,size_t out_len)
{
    static const char *variant_keys[] = {  
        "ro.hardware",  /* This goes first so that it can pick up a different file on the emulator. */  
        "ro.product.board",  
        "ro.board.platform",  
        "ro.arch"  
    };

    const int HAL_VARIANT_KEYS_COUNT =  (sizeof(variant_keys)/sizeof(variant_keys[0]));
    char path[PATH_MAX] = {0};
    for (int i=0 ; i<HAL_VARIANT_KEYS_COUNT+1 ; i++) {
        char prop[PATH_MAX] = {0};
        if (i < HAL_VARIANT_KEYS_COUNT) {  
            if (property_get(variant_keys[i], prop, NULL) == 0) {  
                continue;  
            }  
            snprintf(path, sizeof(path), "%s/%s.%s.so",  HAL_LIBRARY_PATH1, id, prop);  
            if (access(path, R_OK) == 0) 
                break;  
            snprintf(path, sizeof(path), "%s/%s.%s.so",  HAL_LIBRARY_PATH2, id, prop);  
            if (access(path, R_OK) == 0) 
                break;  
        } 
        else {  
            snprintf(path, sizeof(path), "%s/%s.default.so",  HAL_LIBRARY_PATH1, id);  
            if (access(path, R_OK) == 0) 
                break;  
        }  
    }
    size_t path_len = strlen(path);
    if (path_len>=out_len){
        return -path_len;
    }
    memset(out,0,out_len);
    memmove(out,path,path_len);
    return path_len;  
}
}