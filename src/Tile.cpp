#include "Tile.hpp"
#include <cfloat>

int Tile::GetHeuristic(Tile *destination)
{
    int relative_x = this->x - destination->x;
    int relative_y = this->y - destination->y;

    return (relative_x * relative_x) + (relative_y * relative_y);
}

void Tile::SetCost(float cost)
{
    this->cost = cost;
}

float Tile::GetCost()
{
    return cost;
}

void Tile::SetNavigable(bool navigable)
{
    this->navigable = navigable;
}

bool Tile::GetNavigable()
{
    return navigable;
}

void Tile::Initialise(int x, int y, bool navigable)
{
    // Set tile position:
    this->x = x;
    this->y = y;
    // Set navigable boolean:
    this->navigable = navigable;
    // Set parent and cost:
    Reset();
}

void Tile::Reset()
{
    // The tile does not have a parent.
    parent = nullptr;
    // Infinite cost until tile has been navigated.
    cost = FLT_MAX;
}

bool Tile::SetParent(Tile *parent, float cost)
{
    if(navigable)
    {
        float total_cost = parent->cost + cost;

        if(total_cost < this->cost)
        {
            this->cost = total_cost;
            this->parent = parent;

            return true;
        }
    }

    return false;
}

Tile *Tile::GetParent()
{
    return parent;
}

int Tile::GetX()
{
    return x;
}

int Tile::GetY()
{
    return y;
}
