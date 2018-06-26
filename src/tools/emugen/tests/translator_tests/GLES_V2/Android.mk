LOCAL_PATH:= $(call my-dir)

$(call emugl-begin-host-executable,triangleV2)
$(call emugl-import,libEGL_translator libGLES_V2_translator)

LOCAL_SRC_FILES:= \
        triangleV2.cpp

LOCAL_CFLAGS += $(EMUGL_SDL_CFLAGS) -g -O0
LOCAL_LDLIBS += $(EMUGL_SDL_LDLIBS) -lstdc++

LOCAL_STATIC_LIBRARIES += $(EMUGL_SDL_STATIC_LIBRARIES)



$(call emugl-end-module)
