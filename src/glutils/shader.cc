//
// Created by mehdi on 20/06/2020.
//

#include "shader.hh"

Shader::Shader(std::string path, int SHADER_TYPE)
{
    this->path_ = path;
    std::string shader_src = load(this->path_);
    GLint compile_status = GL_TRUE;
    char *shd_src = (char*)std::malloc(shader_src.length()*sizeof(char));
    shader_src.copy(shd_src, shader_src.length());
    if (SHADER_TYPE == 0)
        this->id_ = glCreateShader(GL_VERTEX_SHADER);
    if (SHADER_TYPE == 1)
        this->id_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->id_, 1, (const GLchar**)&(shd_src), 0); MarchError::test_opengl_error_line();
    glCompileShader(this->id_); MarchError::test_opengl_error_line();
    glGetShaderiv(this->id_, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE) {
        GLint log_size;
        char *shader_log;
        glGetShaderiv(this->id_, GL_INFO_LOG_LENGTH, &log_size);
        shader_log = (char*)std::malloc(log_size+1); /* +1 pour le caractere de fin de chaine '\0' */
        if(shader_log != 0) {
            glGetShaderInfoLog(this->id_, log_size, &log_size, shader_log);
            std::cerr << "SHADER " << path << ": " << shader_log << std::endl;
            std::free(shader_log);
        }
        std::free(shd_src);
        glDeleteShader(this->id_);
    }
}

std::string Shader::load(const std::string &filename) {
    std::ifstream input_src_file(filename, std::ios::in);
    std::string ligne;
    std::string file_content;
    if (input_src_file.fail()) {
        std::cerr << "Failed to find " << filename << std::endl;
        exit(-1);
        return "";
    }
    while(getline(input_src_file, ligne)) {
        file_content = file_content + ligne + "\n";
    }
    file_content += '\0';
    input_src_file.close();
    return file_content;
}

Shader::~Shader() {
    glDeleteShader(this->id_);
}
