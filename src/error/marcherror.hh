//
// Created by mehdi on 09/04/2020.
//

#ifndef POGLTEMPLATE_ERROR_HH
#define POGLTEMPLATE_ERROR_HH

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

class MarchError {
public:
    static void test_opengl_error_enum();
    static void test_opengl_error_line();
};


#endif //POGLTEMPLATE_ERROR_HH
