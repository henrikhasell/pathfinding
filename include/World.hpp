#ifndef WORLD_HPP
#define WORLD_HPP

#include "TileMap.hpp"
#include <cmath>

namespace Navigation
{
    struct Vector
    {
        Vector(float x, float y) : x(x), y(y) {}
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

    class World : public TileMap
    {
        public:
            // Static constants:
            static constexpr float TileW = 20.0f;
            static constexpr float TileH = 20.0f;
            // Constructors:
            World(int width, int height);
            World(int width, int height, const char data[]);
            // Getters:
            Tile *GetTile(Vector &position);
            // Pathfinding:
            bool CalculatePath(Vector &start, Vector &finish);
            bool CalculatePath(Vector &start, Vector &finish, std::vector<Vector> &path);
            bool Visible(Vector &start, Vector &finish);
    };
};
#endif // WORLD_HPP
