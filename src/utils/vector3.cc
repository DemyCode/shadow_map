//
// Created by mehdi on 11/02/2020.
//

#include "vector3.hh"

Vector3::Vector3(float x, float y, float z)
{
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
}

Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(this->x_ + v.x_, this->y_ + v.y_, this->z_ + v.z_);
}

Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(this->x_ - v.x_, this->y_ - v.y_, this->z_ - v.z_);
}

Vector3 Vector3::operator*(const Vector3& v) const {
    return Vector3(this->x_ * v.x_, this->y_ * v.y_, this->z_ * v.z_);
}

Vector3 Vector3::operator/(const Vector3& v) const {
    return Vector3(this->x_ / v.x_, this->y_ / v.y_, this->z_ / v.z_);
}

std::ostream &operator<<(std::ostream &out, const Vector3 &vect) {
    return out << "(" << vect.x_ << "," << vect.y_ << "," << vect.z_ << ")";
}

float Vector3::dot(const Vector3 &v) const {
    return this->x_ * v.x_ + this->y_ * v.y_ + this->z_ * v.z_;
}

Vector3 Vector3::cross(const Vector3 &v) const {
    return Vector3(
            this->y_ * v.z_ - this->z_ * v.y_,
            this->z_ * v.x_ - this->x_ * v.z_,
            this->x_ * v.y_ - this->y_ * v.x_);
}

float Vector3::norm() const {
    return std::sqrt(
            this->x_ * this->x_ +
            this->y_ * this->y_ +
            this->z_ * this->z_);
}

Vector3 Vector3::operator/(float val) const {
    return Vector3(this->x_ / val, this->y_ / val, this->z_ / val);
}

Vector3 Vector3::normalize() const
{
    return (*this) / this->norm();
}

Vector3 Vector3::operator*(float val) const {
    return Vector3(this->x_ * val, this->y_ * val, this->z_ * val);
}

float Vector3::dist(const Vector3 &v) const {
    return std::sqrt(
            (v.x_ - this->x_) * (v.x_ - this->x_) +
            (v.y_ - this->y_) * (v.y_ - this->y_) +
            (v.z_ - this->z_) * (v.z_ - this->z_));
}