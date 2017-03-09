#include "World.hpp"
#include <cmath>

using namespace Navigation;

World::World(int width, int height) : TileMap(width, height)
{

}

World::World(int width, int height, const char data[]) : TileMap(width, height, data)
{

}

Tile *World::GetTile(const Vector &position)
{
    return TileMap::GetTile(
        (int)(position.x / TileW),
        (int)(position.y / TileH)
    );
}

bool World::CalculatePath(const Vector &start, const Vector &finish)
{
    Tile *start_tile = GetTile(start);

    if(!start_tile)
    {
        return false;
    }

    Tile *finish_tile = GetTile(finish);

    if(!finish_tile)
    {
        return false;
    }

    return TileMap::CalculatePath(start_tile, finish_tile);
}

bool World::CalculatePath(const Vector &start, const Vector &finish, std::vector<Vector> &path)
{
    bool result = CalculatePath(start, finish);

    if(result)
    {
        for(Tile *tile = GetTile(finish); tile; tile = tile->GetParent())
        {
            path.emplace(path.begin(),
                (TileW * tile->GetX()) + (TileW / 2),
                (TileH * tile->GetY()) + (TileH / 2)
            );
        }

    }

    return result;
}


bool World::Visible(const Vector &start, const Vector &finish)
{
    Vector ray_direction = finish - start;
    ray_direction.Normalise();

    int stepX = ray_direction.x >= 0 ? 1 : -1;
    int stepY = ray_direction.y >= 0 ? 1 : -1;

    float distanceFromEdgeX = stepX < 0
        ? -fmod(start.x, TileW) : TileW - fmod(start.x, TileW);

    float distanceFromEdgeY = stepY < 0
        ? -fmod(start.y, TileH) : TileH - fmod(start.y, TileH);

    float magnitudeToEdgeX = distanceFromEdgeX / ray_direction.x;
    float magnitudeToEdgeY = distanceFromEdgeY / ray_direction.y;

    float magnitudeForOneUnitX = TileW / fabs(ray_direction.x);
    float magnitudeForOneUnitY = TileH / fabs(ray_direction.y);

    Tile *current_tile = GetTile(start);
    Tile *target_tile = GetTile(finish);

    if(!current_tile || !target_tile)
    {
        return false;
    }

    while(current_tile)
    {
        int X = current_tile->GetX();
        int Y = current_tile->GetY();

        if(current_tile->GetNavigable() == false)
        {
            return false;
        }

        if(magnitudeToEdgeX < magnitudeToEdgeY)
        {
            magnitudeToEdgeX += magnitudeForOneUnitX;
            X += stepX;
        }
        else
        {
            magnitudeToEdgeY += magnitudeForOneUnitY;
            Y += stepY;
        }

        if(current_tile == target_tile)
        {
            break;
        }

        current_tile = TileMap::GetTile(X, Y);
    }

    return true;
}
