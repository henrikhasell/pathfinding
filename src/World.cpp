#include "World.hpp"
#include <cmath>

using namespace Navigation;

World::World(int width, int height) : TileMap(width, height)
{

}

World::World(int width, int height, const char data[]) : TileMap(width, height, data)
{

}

Tile *World::GetTile(Vector &position)
{
    return TileMap::GetTile(
        (int)(position.x / TILE_W),
        (int)(position.y / TILE_H)
    );
}

bool World::CalculatePath(Vector &start, Vector &finish)
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

bool World::CalculatePath(Vector &start, Vector &finish, std::vector<Vector> &path)
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

    bool result = TileMap::CalculatePath(start_tile, finish_tile);

    if(result)
    {
        for(Tile *tile = GetTile(finish); tile; tile = tile->GetParent())
        {
            path.emplace(path.end(),
                (TILE_W * tile->GetX()) + (TILE_W / 2),
                (TILE_H * tile->GetY()) + (TILE_H / 2)
            );
        }

    }

    return result;
}


bool World::Visible(Vector &start, Vector &finish)
{
    Vector ray_direction = {
        finish.x - start.x,
        finish.y - start.y
    };

    float ray_magnitude = sqrtf(
        ray_direction.x * ray_direction.x +
        ray_direction.y * ray_direction.y
    );

    ray_direction.x /= ray_magnitude;
    ray_direction.y /= ray_magnitude;

    int stepX = ray_direction.x >= 0 ? 1 : -1;
    int stepY = ray_direction.y >= 0 ? 1 : -1;

    float distanceFromEdgeX = stepX < 0
        ? -fmod(start.x, TILE_W) : TILE_W - fmod(start.x, TILE_W);

    float distanceFromEdgeY = stepY < 0
        ? -fmod(start.y, TILE_H) : TILE_H - fmod(start.y, TILE_H);

    float magnitudeToEdgeX = distanceFromEdgeX / ray_direction.x;
    float magnitudeToEdgeY = distanceFromEdgeY / ray_direction.y;

    float magnitudeForOneUnitX = TILE_W / fabs(ray_direction.x);
    float magnitudeForOneUnitY = TILE_H / fabs(ray_direction.y);

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
