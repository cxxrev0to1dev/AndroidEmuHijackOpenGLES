ifneq (false,$(BUILD_EMULATOR_OPENGL_DRIVER))

LOCAL_PATH := $(call my-dir)

$(call emugl-begin-shared-library,gralloc.goldfish)
$(call emugl-import,libEGL_RedFinger_static)
$(call emugl-import,libEGL_RedFinger)
$(call emugl-set-shared-library-subpath,hw)

LOCAL_CFLAGS += -DLOG_TAG=\"gralloc_goldfish\"
LOCAL_CFLAGS += -Wno-missing-field-initializers
LOCAL_CFLAGS += -Wno-missing-field-initializers -std=c++11

LOCAL_SHARED_LIBRARIES += libEGL_RedFinger

LOCAL_SRC_FILES := gralloc.cpp

# Need to access the special OPENGL TLS Slot
LOCAL_C_INCLUDES += bionic/libc/private
LOCAL_SHARED_LIBRARIES += libdl
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libEGL_RedFinger)

$(call emugl-end-module)

endif # BUILD_EMULATOR_OPENGL_DRIVER != false
