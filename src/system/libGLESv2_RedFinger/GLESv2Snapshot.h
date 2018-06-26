#ifndef __GLES_V2_SNAPSHOT_H_
#define __GLES_V2_SNAPSHOT_H_

#include "GLESv2Decoder.h"

#include <map>
#include <string>
#include <vector>
#include <iterator>

#include <inttypes.h>

#include <GLES2/gl2.h>

class GLESv2Decoder;

struct GLValue {
    std::vector<GLenum> enums;
    std::vector<unsigned char> bytes;
    std::vector<uint16_t> shorts;
    std::vector<uint32_t> ints;
    std::vector<float> floats;
    std::vector<uint64_t> int64s;
};

typedef std::map<GLenum, GLValue> GlobalStateMap;
typedef std::map<GLenum, bool> GlobalEnables;

struct GLShaderState {
    GLenum type;
    std::string source;
    bool compileStatus;
};

struct GLProgramState {
    std::map<GLenum, GLuint> linkage;
    bool linkStatus;
};

class GLSnapshotState {
public:
    GLSnapshotState(GLESv2Decoder* gl);
    void save();
    void restore();

    // Shaders
    GLuint createShader(GLuint shader, GLenum shaderType);
    GLuint createProgram(GLuint program);
    void shaderString(GLuint shader, const GLchar* string);
    void genBuffers(GLsizei n, GLuint* buffers);
    GLuint getProgramName(GLuint name);

private:
    void getGlobalStateEnum(GLenum name, int size);
    void getGlobalStateByte(GLenum name, int size);
    void getGlobalStateInt(GLenum name, int size);
    void getGlobalStateFloat(GLenum name, int size);
    void getGlobalStateInt64(GLenum name, int size);

    void getGlobalStateEnable(GLenum name);

    GLESv2Decoder* mGL;
    GlobalStateMap mGlobals;
    GlobalEnables mEnables;

    GLuint mProgramCounter = 1;

    std::map<GLuint, GLuint> mProgramNames;
    std::map<GLuint, GLuint> mProgramNamesBack;
    std::map<GLuint, GLShaderState> mShaderState;
    std::map<GLuint, GLProgramState> mShaderProgramState;

};

#endif