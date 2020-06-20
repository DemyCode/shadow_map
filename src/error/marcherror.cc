//
// Created by mehdi on 09/04/2020.
//

#include "marcherror.hh"

void MarchError::test_opengl_error_enum() {
    GLenum err = glGetError();
    switch (err) {
        case GL_NO_ERROR:
            return;
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM\n";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE\n";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION\n";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY\n";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW\n";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW\n";
            break;
        default:
            std::cerr << "UNKONWN ERROR\n";
            break;
    }
}

void MarchError::test_opengl_error_line() {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        std::cerr << "OpenGL ERROR!" << __LINE__ << std::endl;
}
