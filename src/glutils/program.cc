//
// Created by mehdi on 20/06/2020.
//

#include "program.hh"

Program::Program(Shader vertex, Shader fragment) {
    GLint link_status = GL_TRUE;
    this->id_ = glCreateProgram(); MarchError::test_opengl_error_line();
    if (this->id_ == 0)
    {
        std::cerr << "Program ID is 0 !" << std::endl;
        return;
    }
    glAttachShader(this->id_, vertex.id_); MarchError::test_opengl_error_line();
    glAttachShader(this->id_, fragment.id_); MarchError::test_opengl_error_line();
    glLinkProgram(this->id_); MarchError::test_opengl_error_line();
    glGetProgramiv(this->id_, GL_LINK_STATUS, &link_status);
    if (link_status!=GL_TRUE) {
        GLint log_size;
        char *program_log;
        glGetProgramiv(this->id_, GL_INFO_LOG_LENGTH, &log_size);
        program_log = (char*)std::malloc(log_size+1); /* +1 pour le caractere de fin de chaine '\0' */
        if(program_log != 0) {
            glGetProgramInfoLog(this->id_, log_size, &log_size, program_log);
            std::cerr << "Program " << program_log << std::endl;
            std::free(program_log);
        }
        glDeleteProgram(this->id_); MarchError::test_opengl_error_line();
        this->id_ = 0;
        std::cerr << "Linking program failed !" << std::endl;
        return;
    }
}

void Program::use() {
    glUseProgram(this->id_);
}

Program::~Program() {
    glDeleteProgram(this->id_);
}

