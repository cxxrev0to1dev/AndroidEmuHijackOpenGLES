# This build script corresponds to a library containing many definitions
# common to both the guest and the host. They relate to
#
LOCAL_PATH := $(call my-dir)

### emugl_common host library ###########################################

commonSources := \
        id_to_object_map.cpp \
        lazy_instance.cpp \
        pod_vector.cpp \
        smart_ptr.cpp \
        sockets.cpp \
        thread_store.cpp \

host_commonSources := $(commonSources)

$(call emugl-begin-host-static-library,libemugl_common)
LOCAL_SRC_FILES := $(host_commonSources)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/shared)
$(call emugl-export,LDLIBS,-lstdc++)
$(call emugl-end-module)

ifdef EMUGL_BUILD_64BITS
    $(call emugl-begin-host64-static-library,lib64emugl_common)
    LOCAL_SRC_FILES := $(host_commonSources)
    $(call emugl-export,CFLAGS,-m64 -fPIC)
    $(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/shared)
    $(call emugl-export,LDLIBS,-lstdc++)
    $(call emugl-end-module)
endif

