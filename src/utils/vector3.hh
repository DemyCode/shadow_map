//
// Created by mehdi on 11/02/2020.
//

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#include <iostream>
#include <cmath>

class Vector3
{
public:
    Vector3(float x, float y, float z);
    Vector3() = default;
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(const Vector3& v) const;
    Vector3 operator/(const Vector3& v) const;
    float dist(const Vector3& v) const;
    Vector3 operator*(float val) const;
    Vector3 operator/(float val) const;
    float dot(const Vector3& v) const;
    Vector3 cross(const Vector3& v) const;
    float norm() const;
    Vector3 normalize() const;
    friend std::ostream& operator<<(std::ostream &out, const Vector3 &vect);

    float x_;
    float y_;
    float z_;
};

#endif //RAYTRACER_VECTOR3_H
