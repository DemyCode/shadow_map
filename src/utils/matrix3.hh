//
// Created by mehdi on 13/04/2020.
//

#ifndef RAYMARCHERGL_MATRIX3_HH
#define RAYMARCHERGL_MATRIX3_HH


#include "vector3.hh"

class Matrix3 {
public:
    Matrix3(Vector3 a, Vector3 b, Vector3 c);
    Matrix3(float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i);
    Vector3 operator*(const Vector3& v) const;
    float a_;
    float b_;
    float c_;
    float d_;
    float e_;
    float f_;
    float g_;
    float h_;
    float i_;
};


#endif //RAYMARCHERGL_MATRIX3_HH
