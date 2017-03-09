#include "Vector.hpp"
#include <cmath>

using namespace Navigation;

Vector::Vector(float x, float y) : x(x), y(y)
{

}

Vector Vector::operator+(const Vector &other) const
{
    return Vector(this->x + other.x, this->y  + other.y);
}

Vector Vector::operator-(const Vector &other) const
{
    return Vector(this->x - other.x, this->y  - other.y);
}

Vector Vector::operator*(const Vector &other) const
{
    return Vector(this->x * other.x, this->y  * other.y);
}

Vector Vector::operator/(const Vector &other) const
{
    return Vector(this->x / other.x, this->y  / other.y);
}

Vector Vector::operator+(const float other) const
{
    return Vector(this->x + other, this->y  + other);
}

Vector Vector::operator-(const float other) const
{
    return Vector(this->x - other, this->y  - other);
}

Vector Vector::operator*(const float other) const
{
    return Vector(this->x * other, this->y  * other);
}

Vector Vector::operator/(const float other) const
{
    return Vector(this->x / other, this->y  / other);
}

void Vector::operator+=(const Vector &other)
{
    this->x += other.x; this->y += other.y;
}

void Vector::operator-=(const Vector &other)
{
    this->x -= other.x; this->y -= other.y;
}

void Vector::operator*=(const Vector &other)
{
    this->x *= other.x; this->y *= other.y;
}

void Vector::operator/=(const Vector &other)
{
    this->x /= other.x; this->y /= other.y;
}

Vector &Vector::operator+=(const float other)
{
    this->x += other; this->y += other; return *this;
}

Vector &Vector::operator-=(const float other)
{
    this->x -= other; this->y -= other; return *this;
}

Vector &Vector::operator*=(const float other)
{
    this->x *= other; this->y *= other; return *this;
}

Vector &Vector::operator/=(const float other)
{
    this->x /= other; this->y /= other; return *this;
}

float Vector::Magnitude()
{
    return sqrtf(this->x * this->x + this->y * this->y);
}

Vector Vector::Normalise()
{
    return *this / Magnitude();
}
