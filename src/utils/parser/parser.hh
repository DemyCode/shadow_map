//
// Created by mehdi on 28/02/2020.
//

#ifndef RAYTRACER_PARSER_HH
#define RAYTRACER_PARSER_HH

#include <fstream>
#include <iostream>
#include <regex>
#include <utils/vector3.hh>

class Parser {
public:
    Parser(std::string file);

    std::vector<float> vertices_;
    std::vector<int> indices_;
private:
    std::vector<Vector3> normals_;
};


#endif //RAYTRACER_PARSER_HH
