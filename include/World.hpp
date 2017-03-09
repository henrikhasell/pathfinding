#ifndef WORLD_HPP
#define WORLD_HPP

#include "TileMap.hpp"
#include "Vector.hpp"

namespace Navigation
{
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
            Tile *GetTile(const Vector &position);
            // Pathfinding:
            bool CalculatePath(const Vector &start, const Vector &finish);
            bool CalculatePath(const Vector &start, const Vector &finish, std::vector<Vector> &path);
            bool Visible(const Vector &start, const Vector &finish);
    };
}
#endif // WORLD_HPP
