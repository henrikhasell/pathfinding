#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>

//namespace Navigataion
//{
    class Tile
    {
        public:
            void Initialise(int x, int y, bool navigable);
            void Reset();
    
            void SetCost(float cost);
            float GetCost() const;
    
            void SetNavigable(bool navigable);
            bool GetNavigable() const;
    
            bool SetParent(Tile *parent, float cost);
            Tile *GetParent() const;
    
            int GetHeuristic(const Tile *destination) const;
    
    		int GetX() const;
    		int GetY() const;
    
        private:
            float cost;
            bool navigable;
            Tile *parent;
            int x;
            int y;
    };
//}

#endif // TILE_HPP
