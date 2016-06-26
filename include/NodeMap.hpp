#ifndef NODEMAP_HPP
#define NODEMAP_HPP

#include "TileMap.hpp"
#include "Vector.hpp"
#include <cmath>

namespace Navigation
{
    class NodeMap : public TileMap
    {
        public:
            // Static constants:
            static constexpr float TileW = 20.0f;
            static constexpr float TileH = 20.0f;
            // Constructors:
            NodeMap(int width, int height);
            NodeMap(int width, int height, const char data[]);
            // Getters:
            Tile *GetTile(Vector &position);
            // Pathfinding:
            bool CalculatePath(Vector &start, Vector &finish);
            bool CalculatePath(Vector &start, Vector &finish, std::vector<Vector> &path);
            bool Visible(Vector &start, Vector &finish);
    };
};
#endif // NODEMAP_HPP
