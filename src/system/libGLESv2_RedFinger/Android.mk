LOCAL_PATH := $(call my-dir)

### GLESv2_enc Encoder ###########################################
$(call emugl-begin-shared-library,libGLESv2_RedFinger)

LOCAL_CFLAGS += -DLOG_TAG=\"libGLESv2_RedFinger\" -DGLES2
#LOCAL_CFLAGS += -Werror

LOCAL_SRC_FILES := \
    gles_client_context.cpp \
    gles_dec.cpp	\
    gles_enc.cpp	\
    gles_server_context.cpp	\
    gles_wrapper_context.cpp	\
    gles_wrapper_entry.cpp	\
    GLESEncoderUtils.cpp	\
    GLESTestStream.cpp	\
    GLESv2ThreadInfo.cpp	\
    GLESv2DispatchInternal.cpp	\
    GLESv2Encoder.cpp	\
    GLESv2NativeFuncCall.cpp	\
    GLESv2Decoder.cpp	\
    GLESv2Snapshot.cpp	\
		GLESv2Validation.cpp	\
		GLESv2Unimplement.cpp \
    
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

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/include)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libEGL_RedFinger)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
# $(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-export,C_INCLUDES,external/libcxx/include)
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog libstlport)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)

# LOCAL_MODULE_PATH := /media/dengtao/win_software/win_software/firefly-rk3288/out/target/product/rk3288/system/lib/
$(call emugl-set-shared-library-subpath,egl)
$(call emugl-end-module)

$(call emugl-begin-static-library,libGLESv2_RedFinger_static)

LOCAL_CFLAGS += -DLOG_TAG=\"libGLESv2_RedFinger\" -DGLES2
# LOCAL_CFLAGS := -fvisibility=internal
#LOCAL_CFLAGS += -Werror

LOCAL_SRC_FILES := \
    gles_client_context.cpp \
    gles_dec.cpp	\
    gles_enc.cpp	\
    gles_server_context.cpp	\
    gles_wrapper_context.cpp	\
    gles_wrapper_entry.cpp	\
    GLESEncoderUtils.cpp	\
    GLESTestStream.cpp	\
    GLESv2ThreadInfo.cpp	\
    GLESv2DispatchInternal.cpp	\
    GLESv2NativeFuncCall.cpp	\
    GLESv2Encoder.cpp	\
    GLESv2Decoder.cpp	\
    GLESv2Snapshot.cpp	\
		GLESv2Validation.cpp	\
		GLESv2Unimplement.cpp \
    
LOCAL_LDLIBS += -ldl
LOCAL_SHARED_LIBRARIES += libdl
LOCAL_LDLIBS += -lstdc++

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/include)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libEGL_RedFinger)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
$(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog libstlport)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)

$(call emugl-end-module)