#ifndef WORLD_HPP
#define WORLD_HPP

#include "TileMap.hpp"

namespace Navigation
{
    struct Vector
    {
        Vector(float x, float y) : x(x), y(y) {}
        float x;
        float y;
    };

    class World : public TileMap
    {
        public:
            // Static constants:
            static constexpr float TILE_W = 20.0f;
            static constexpr float TILE_H = 20.0f;
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
