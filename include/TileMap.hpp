#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "Tile.hpp"
#include <vector>

namespace Navigation
{
    class TileMap
    {
        private:
            Tile *tile;
        public:
            const int width;
            const int height;
            // Constructors:
            TileMap(int width, int height);
            TileMap(int width, int height, const char data[]);
            // Destructor:
            ~TileMap();
            // Getters:
            Tile *GetTile(int x, int y);
            // Pathfinding:
            bool CalculatePath(Tile *start, Tile *finish);
            bool CalculatePath(Tile *start, Tile *finish, std::vector<Tile*> &path);
            void Reset();
    };
};

#endif // TILEMAP_HPP

