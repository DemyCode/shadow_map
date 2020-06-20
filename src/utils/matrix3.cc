//
// Created by mehdi on 13/04/2020.
//

#include "matrix3.hh"

Matrix3::Matrix3(Vector3 a, Vector3 b, Vector3 c) {
    this->a_ = a.x_;
    this->b_ = a.y_;
    this->c_ = a.z_;
    this->d_ = b.x_;
    this->e_ = b.y_;
    this->f_ = b.z_;
    this->g_ = c.x_;
    this->h_ = c.y_;
    this->i_ = c.z_;
}

Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    this->a_ = a;
    this->b_ = b;
    this->c_ = c;
    this->d_ = d;
    this->e_ = e;
    this->f_ = f;
    this->g_ = g;
    this->h_ = h;
    this->i_ = i;
}

Vector3 Matrix3::operator*(const Vector3 &v) const {
    Vector3(this->a_ * v.x_ + this->b_ * v.y_ + this->c_ * v.z_,
            this->d_ * v.x_ + this->e_ * v.y_ + this->f_ * v.z_,
            this->g_ * v.x_ + this->h_ * v.y_ + this->i_ * v.z_);
}