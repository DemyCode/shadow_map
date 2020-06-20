//
// Created by mehdi on 20/06/2020.
//

#ifndef SHADOW_MAP_PROGRAM_HH
#define SHADOW_MAP_PROGRAM_HH

#include <vector>

#include "shader.hh"
#include <error/marcherror.hh>

class Program {
public:
    Program(Shader vertex, Shader fragment);
    ~Program();
    void use();

    GLint id_;
};


#endif //SHADOW_MAP_PROGRAM_HH
