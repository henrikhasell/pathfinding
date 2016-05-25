#ifndef TILE_HPP
#define TILE_HPP

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

        int GetHeuristic(Tile *destination);

		int GetX();
		int GetY();

    private:
        bool navigable;
        float cost;
        int x;
        int y;
        Tile *parent;
};

#endif // TILE_HPP
