#include "Tile.hpp"
#include <cfloat>
#include <cmath>

float Tile::GetHeuristic(const Tile *start, const Tile *destination) const
{
    float relative_x = (float)(this->x - destination->x);
    float relative_y = (float)(this->y - destination->y);
#ifdef DIAGONAL
    return cost + sqrtf(relative_x * relative_x + relative_y * relative_y);
#else
    float relative_start_x = start->x - destination->x;
    float relative_start_y = start->y - destination->y;
    float manhattan = fabs(relative_x) + fabs(relative_y);
    float cross = fabs(relative_start_x * relative_y - relative_start_y * relative_x);

    return cost + manhattan + cross * 0.001f;
#endif
}

void Tile::SetCost(float cost)
{
    this->cost = cost;
}

float Tile::GetCost() const
{
    return cost;
}

void Tile::SetNavigable(bool navigable)
{
    this->navigable = navigable;
}

bool Tile::GetNavigable() const
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

Tile *Tile::GetParent() const
{
    return parent;
}

int Tile::GetX() const
{
    return x;
}

int Tile::GetY() const
{
    return y;
}
