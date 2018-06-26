LOCAL_PATH := $(call my-dir)

##### libEGL_RedFinger_static.a ###########
$(call emugl-begin-static-library,libEGL_RedFinger_static)
$(call emugl-import,libGLESv1_CM_RedFinger libGLESv2_RedFinger libOpenglCodecCommon)
LOCAL_CFLAGS += -DLOG_TAG=\"libEGL_RedFinger_static\" -DEGL_EGLEXT_PROTOTYPES
LOCAL_CFLAGS += -Wno-missing-field-initializers -std=c++11

LOCAL_SRC_FILES := \
	renderControl_client_context.cpp	\
	renderControl_dec.cpp	\
	renderControl_enc.cpp	\
	renderControl_entry.cpp	\
	renderControl_server_context.cpp	\
	renderControl_wrapper_context.cpp	\
	renderControl_wrapper_entry.cpp	\
	redfinger_egl_info.cpp	\
	redfinger_egl_stream.cpp	\
	FbConfig.cpp	\
	eglDisplay.cpp \
    
LOCAL_LDLIBS += -ldl
LOCAL_LDLIBS += -lstdc++
LOCAL_SHARED_LIBRARIES += libdl
LOCAL_SHARED_LIBRARIES += libOpenglRender
LOCAL_STATIC_LIBRARIES += libstlport_static

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/include)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/host/include/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/host/libs/libOpenglRender/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/shared/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/shared/emugl/common/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/OpenglSystemCommon)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libGLESv1_CM_RedFinger)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libGLESv2_RedFinger)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
# $(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-export,C_INCLUDES,external/libcxx/include)
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)
$(call emugl-end-module)


##### libEGL_RedFinger.so ###########
$(call emugl-begin-shared-library,libEGL_RedFinger)
$(call emugl-import,libGLESv1_CM_RedFinger libGLESv2_RedFinger)
$(call emugl-set-shared-library-subpath,egl)

LOCAL_CFLAGS += -DLOG_TAG=\"libEGL_RedFinger\" -DEGL_EGLEXT_PROTOTYPES
LOCAL_CFLAGS += -Wno-missing-field-initializers -std=c++11

LOCAL_LDLIBS += -ldl
LOCAL_SHARED_LIBRARIES += libdl
LOCAL_STATIC_LIBRARIES += libEGL_RedFinger_static
LOCAL_STATIC_LIBRARIES += breakpad_client
LOCAL_STATIC_LIBRARIES += libOpenglCodecCommon



LOCAL_SHARED_LIBRARIES += libOpenglRender

LOCAL_CPPFLAGS += -std=c++11 -nostdinc++ -fexceptions
LOCAL_CFLAGS += $(EMUGL_COMMON_CFLAGS) $(EMUGL_USER_CFLAGS)
LOCAL_LDFLAGS += -ldl -D_STLP_USE_NEWALLOC -D_STLP_USE_NO_IOSTREAMS -D_STLP_USE_MALLOC
LOCAL_CFLAGS +=  -D_STLP_USE_MALLOC -D_STLP_USE_SIMPLE_NODE_ALLOC
LOCAL_CPPFLAGS += -D_STLP_USE_MALLOC -D_STLP_USE_SIMPLE_NODE_ALLOC
LOCAL_LDLIBS += -lstdc++
LOCAL_STL := c++_static stlport_static
APP_STL := c++_static stlport_static
LOCAL_LDLIBS += $(host_commonLdLibs) $(host_common_LDLIBS) $(ANDROID_EMU_LDLIBS) -lstdc++ -std=c++11 -lc++ -ldl

LOCAL_SRC_FILES :=  \
        egl.cpp \
        egl_dispatch.cpp \
        ThreadInfo.cpp	\
        FbConfig.cpp	\

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/include)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/host/include/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/host/libs/libOpenglRender/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/shared/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/shared/emugl/common/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/android-emugl/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/google-breakpad/src/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/third_party/google-breakpad/src/common/android/include/)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/egl)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/OpenglSystemCommon)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libGLESv1_CM_RedFinger)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/system/libGLESv2_RedFinger)
$(call emugl-export,C_INCLUDES,$(EMUGL_PATH)/tests/ut_rendercontrol_enc)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)
# $(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-export,C_INCLUDES,external/libcxx/include)
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)
$(call emugl-end-module)