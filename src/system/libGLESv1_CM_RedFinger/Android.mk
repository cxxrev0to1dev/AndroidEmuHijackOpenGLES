LOCAL_PATH := $(call my-dir)

### GLESv2_enc Encoder ###########################################
$(call emugl-begin-shared-library,libGLESv1_CM_RedFinger)

LOCAL_CFLAGS += -DLOG_TAG=\"libGLESv1_CM_RedFinger\" -DGLES1

LOCAL_SRC_FILES := \
    gles1_client_context.cpp \
    gles1_dec.cpp	\
    gles1_enc.cpp	\
    gles1_server_context.cpp	\
    gles1_wrapper_context.cpp	\
    gles1_wrapper_entry.cpp	\
    GLESEncoderUtils.cpp	\
    GLESv1Encoder.cpp	\
    GLESv1Decoder.cpp	\
    GLESTestStream.cpp	\
    GLESv1ThreadInfo.cpp	\
    GLESv1DispatchInternal.cpp \

    
LOCAL_LDLIBS += -ldl
LOCAL_SHARED_LIBRARIES += libdl
LOCAL_LDLIBS += -lstdc++

LOCAL_CPPFLAGS += -std=c++11 -nostdinc++ -fexceptions
LOCAL_CFLAGS += $(EMUGL_COMMON_CFLAGS) $(EMUGL_USER_CFLAGS)
LOCAL_LDFLAGS += -ldl -D_STLP_USE_NEWALLOC -D_STLP_USE_NO_IOSTREAMS -D_STLP_USE_MALLOC
LOCAL_CFLAGS +=  -D_STLP_USE_MALLOC -D_STLP_USE_SIMPLE_NODE_ALLOC
LOCAL_CPPFLAGS += -D_STLP_USE_MALLOC -D_STLP_USE_SIMPLE_NODE_ALLOC
LOCAL_LDLIBS += -lstdc++
LOCAL_STL := c++_static stlport_static
APP_STL := c++_static stlport_static
LOCAL_LDLIBS += $(host_commonLdLibs) $(host_common_LDLIBS) $(ANDROID_EMU_LDLIBS) -lstdc++ -std=c++11 -lc++ -ldl

#LOCAL_CFLAGS += -Werror
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/include)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libEGL_RedFinger)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
# $(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-export,C_INCLUDES,external/libcxx/include)
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libGLESv2_RedFinger)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog libstlport)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)

# LOCAL_MODULE_PATH := /media/dengtao/win_software/win_software/firefly-rk3288/out/target/product/rk3288/system/lib/
$(call emugl-set-shared-library-subpath,egl)
$(call emugl-end-module)


$(call emugl-begin-static-library,libGLESv1_CM_RedFinger_static)

LOCAL_CFLAGS += -DLOG_TAG=\"libGLESv1_CM_RedFinger\" -DGLES1
# LOCAL_CFLAGS := -fvisibility=internal

LOCAL_SRC_FILES := \
    gles1_client_context.cpp \
    gles1_dec.cpp	\
    gles1_enc.cpp	\
    gles1_server_context.cpp	\
    gles1_wrapper_context.cpp	\
    gles1_wrapper_entry.cpp	\
    GLESEncoderUtils.cpp	\
    GLESv1Encoder.cpp	\
    GLESv1Decoder.cpp	\
    GLESTestStream.cpp	\
    GLESv1ThreadInfo.cpp	\
    GLESv1DispatchInternal.cpp \

    
LOCAL_LDLIBS += -ldl
LOCAL_SHARED_LIBRARIES += libdl
LOCAL_LDLIBS += -lstdc++

#LOCAL_CFLAGS += -Werror
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/include)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libEGL_RedFinger)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
$(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libGLESv2_RedFinger)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog libstlport)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)
$(call emugl-end-module)