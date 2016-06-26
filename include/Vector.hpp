#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

namespace Navigation
{
    struct Vector
    {
        Vector(float x, float y) : x(x), y(y) {}
	Vector(const Vector &other) : x(other.x), y(other.y) {}
        // Arithmetic operators with vectors:
        Vector operator+(const Vector &other) const {
            return Vector(this->x + other.x, this->y  + other.y); }
        Vector operator-(const Vector &other) const {
            return Vector(this->x - other.x, this->y  - other.y); }
        Vector operator*(const Vector &other) const {
            return Vector(this->x * other.x, this->y  * other.y); }
        Vector operator/(const Vector &other) const {
            return Vector(this->x / other.x, this->y  / other.y); }
        // Assignment operators with scalars:
        Vector operator+(const float other) const {
            return Vector(this->x + other, this->y  + other); }
        Vector operator-(const float other) const {
            return Vector(this->x - other, this->y  - other); }
        Vector operator*(const float other) const {
            return Vector(this->x * other, this->y  * other); }
        Vector operator/(const float other) const {
            return Vector(this->x / other, this->y  / other); }
        // Arithmetic operators with vectos:
        void operator+=(const Vector &other) {
            this->x += other.x; this->y += other.y; }
        void operator-=(const Vector &other) {
            this->x -= other.x; this->y -= other.y; }
        void operator*=(const Vector &other) {
            this->x *= other.x; this->y *= other.y; }
        void operator/=(const Vector &other) {
            this->x /= other.x; this->y /= other.y; }
        // Arithmetic operators with scalars:
        Vector &operator+=(const float other) {
            this->x += other; this->y += other; return *this; }
        Vector &operator-=(const float other) {
            this->x -= other; this->y -= other; return *this; }
        Vector &operator*=(const float other) {
            this->x *= other; this->y *= other; return *this; }
        Vector &operator/=(const float other) {
            this->x /= other; this->y /= other; return *this; }
        // Mathematical operations for vectors:
        float Magnitude() {
            return sqrtf(this->x * this->x + this->y * this->y); }        // Mathematical operations for vectors:
        void Normalise() { *this /= Magnitude(); }
        float x;
        float y;
    };
};

#endif /* VECTOR_HPP */
