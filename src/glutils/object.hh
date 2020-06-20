//
// Created by mehdi on 20/06/2020.
//

#ifndef SHADOW_MAP_OBJECT_HH
#define SHADOW_MAP_OBJECT_HH

#include <GL/glew.h>
#include <GL/gl.h>

class Object {
public:
    Object(float vertices[], unsigned int indices[], int length_vertices, int length_indices);
    Object(float vertices[], int length_vertices);
    ~Object();
    void render();
private:
    bool indices_;
    GLuint VBO_;
    GLuint VAO_;
    GLuint EBO_;
    int length_vertices_;
    int length_indices_;
    float vertices_colors_[];
};


#endif //SHADOW_MAP_OBJECT_HH
