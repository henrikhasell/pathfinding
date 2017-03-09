#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace Navigation
{
    struct Vector
    {
        Vector(float x, float y);
        // Arithmetic operators with vectors:
        Vector operator+(const Vector &other) const;
        Vector operator-(const Vector &other) const;
        Vector operator*(const Vector &other) const;
        Vector operator/(const Vector &other) const;
        // Assignment operators with scalars:
        Vector operator+(const float other) const;
        Vector operator-(const float other) const;
        Vector operator*(const float other) const;
        Vector operator/(const float other) const;
        // Arithmetic operators with vectos:
        void operator+=(const Vector &other);
        void operator-=(const Vector &other);
        void operator*=(const Vector &other);
        void operator/=(const Vector &other);
        // Arithmetic operators with scalars:
        Vector &operator+=(const float other);
        Vector &operator-=(const float other);
        Vector &operator*=(const float other);
        Vector &operator/=(const float other);
        // Mathematical operations for vectors:
        float Magnitude();
        Vector Normalise();
	// Variables:
        float x;
        float y;
    };
}

#endif // VECTOR_HPP
