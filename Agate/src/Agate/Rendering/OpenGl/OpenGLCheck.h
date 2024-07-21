
#ifndef AGATE_OPENGLCHECK_H
#define AGATE_OPENGLCHECK_H

#include <glad/glad.h>
#include "Core/Logger.h"

#ifdef DEBUG
#define GLCall(call) call; CheckGLError(#call)
#else
#define GLCall(call) call
#endif

static const char *GetGLErrorString(GLenum err) {
    switch (err) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:
            return "UNKNOWN_ERROR";
    }
}

static void CheckGLError(const char *call) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        PRINTERROR("Open GL error in call {}, with error code: {} and string of {}", call, err, GetGLErrorString(err));
    }
}


#endif //AGATE_OPENGLCHECK_H
