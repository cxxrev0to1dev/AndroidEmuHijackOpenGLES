# This build script corresponds to a library containing many definitions
# common to both the guest and the host. They relate to
#
LOCAL_PATH := $(call my-dir)

commonSources := \
        GLClientState.cpp \
        GLSharedGroup.cpp \
        glUtils.cpp \
        SocketStream.cpp \
        TcpStream.cpp \
        TimeUtils.cpp	\
        IndexRangeCache.cpp	\
        GLESTextureUtils.cpp

### CodecCommon  guest ##############################################
$(call emugl-begin-static-library,libOpenglCodecCommon)

LOCAL_SRC_FILES := $(commonSources)

LOCAL_LDLIBS += -ldl
LOCAL_LDLIBS += -lstdc++
LOCAL_SHARED_LIBRARIES += libdl
LOCAL_CFLAGS += -DLOG_TAG=\"eglCodecCommon\"

LOCAL_CPPFLAGS += -std=c++11 -nostdinc++ -fexceptions
LOCAL_CFLAGS += $(EMUGL_COMMON_CFLAGS) $(EMUGL_USER_CFLAGS)
LOCAL_LDFLAGS += -ldl -D_STLP_USE_NEWALLOC -D_STLP_USE_NO_IOSTREAMS -D_STLP_USE_MALLOC
LOCAL_CFLAGS +=  -D_STLP_USE_MALLOC -D_STLP_USE_SIMPLE_NODE_ALLOC
LOCAL_CPPFLAGS += -D_STLP_USE_MALLOC -D_STLP_USE_SIMPLE_NODE_ALLOC
LOCAL_LDLIBS += -lstdc++
LOCAL_STL := c++_static stlport_static
APP_STL := c++_static stlport_static
LOCAL_LDLIBS += $(host_commonLdLibs) $(host_common_LDLIBS) $(ANDROID_EMU_LDLIBS) -lstdc++ -std=c++11 -lc++ -ldl

$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog libstlport)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
# $(call emugl-export,C_INCLUDES,external/stlport/stlport bionic)
$(call emugl-export,C_INCLUDES,external/libcxx/include)

$(call emugl-end-module)
