LOCAL_PATH := $(call my-dir)

$(call emugl-begin-shared-library,gralloc.rk30board.test)
$(call emugl-import,libGLESv1_enc lib_renderControl_enc libOpenglSystemCommon)
LOCAL_MODULE_PATH := /media/dengtao/win_software/win_software/firefly-rk3288/out/target/product/rk3288/system/lib/
$(call emugl-set-shared-library-subpath,hw)

LOCAL_CFLAGS += -DLOG_TAG=\"libGrallocGoldfish\"
LOCAL_CFLAGS += -Wno-missing-field-initializers -std=c++11

LOCAL_SRC_FILES := goldfish_gralloc_receive.cpp	\
					goldfish_gralloc_base.cpp	\
					goldfish_gralloc_frame.cpp	\

# Need to access the special OPENGL TLS Slot
LOCAL_C_INCLUDES += bionic/libc/private
LOCAL_SHARED_LIBRARIES += libdl

LOCAL_LDLIBS += -lstdc++
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
$(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog libstlport)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)

$(call emugl-end-module)
