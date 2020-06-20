//
// Created by mehdi on 20/06/2020.
//

#ifndef SHADOW_MAP_SHADER_HH
#define SHADOW_MAP_SHADER_HH


#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <error/marcherror.hh>

class Shader {
public:
    Shader(std::string path, int SHADER_TYPE);
    ~Shader();
    GLuint id_;
private:
    static std::string load(const std::string &filename);

    std::string path_;
};


#endif //SHADOW_MAP_SHADER_HH
