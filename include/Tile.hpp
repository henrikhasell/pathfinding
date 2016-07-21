#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>

class Tile
{
    public:
        void Initialise(int x, int y, bool navigable);
        void Reset();

        void SetCost(float cost);
        float GetCost();

        void SetNavigable(bool navigable);
        bool GetNavigable();

        bool SetParent(Tile *parent, float cost);
        Tile *GetParent();

        int GetHeuristic(Tile *destination) const;

		int GetX() const;
		int GetY() const;

    private:
        float cost;
        bool navigable;
        Tile *parent;
        int x;
        int y;
};

#endif // TILE_HPP
