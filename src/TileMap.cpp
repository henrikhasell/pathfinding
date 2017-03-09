#include "TileMap.hpp"
#include <list>

using namespace Navigation;

TileMap::TileMap(int width, int height) : width(width), height(height)
{
    tile = new Tile[width * height];

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            GetTile(x, y)->Initialise(x, y, true);
        }
    }
}

TileMap::TileMap(int width, int height, const char data[]) : TileMap(width, height)
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            const char &navigable = data[x + width * y];
            // Set the tile navigability based on the data.
            GetTile(x, y)->SetNavigable(navigable == 0);
        }
    }
}

TileMap::~TileMap()
{
    delete[] tile;
}

Tile *TileMap::GetTile(int x, int y)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return nullptr;
    return tile + x + width * y;
}

static void priority_insert(std::list<Tile*> &list, Tile *tile, Tile *destination) {
    std::list<Tile*>::iterator iterator = list.begin();
    while(iterator != list.end() && (*iterator)->GetHeuristic(destination) < tile->GetHeuristic(destination))
    {
        iterator++;
    }
    list.insert(iterator, tile);
}

bool TileMap::CalculatePath(Tile *start, Tile *finish)
{
    std::list<Tile*> open_set;

    Reset();

    open_set.push_back(start);

    start->SetCost(0);

    while(open_set.empty() != true)
    {
        Tile *head = open_set.front();
        open_set.pop_front();

        int x = head->GetX();
        int y = head->GetY();

        Tile *adjacent[4] = {
            GetTile(x + 1, y + 0),
            GetTile(x - 1, y + 0),
            GetTile(x + 0, y + 1),
            GetTile(x + 0, y - 1)
        };

        Tile *diagonal[4] = {
            GetTile(x + 1, y + 1),
            GetTile(x - 1, y - 1),
            GetTile(x + 1, y - 1),
            GetTile(x - 1, y + 1)
        };

        for(Tile *selected : adjacent)
        {
            if(selected && selected->SetParent(head, 1.0f) == true)
            {
                if(selected == finish)
                {
                    return true;
                }
                else
                {
                    priority_insert(open_set, selected, finish);
                }
            }
        }

        for(Tile *selected : diagonal)
        {
            if(selected && selected->SetParent(head, 1.4f) == true)
            {
                if(selected == finish)
                {
                    return true;
                }
                else
                {
                    priority_insert(open_set, selected, finish);
                }
            }
        }
    }

    return false;
}

bool TileMap::CalculatePath(Tile *start, Tile *finish, std::vector<Tile*> &path)
{
    bool result = CalculatePath(start, finish);

    if(result)
    {
        for(Tile *tile = finish; tile; tile = tile->GetParent())
        {
            path.push_back(tile);
        }
    }
    
    return result;
}

void TileMap::Reset()
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            GetTile(x, y)->Reset();
        }
    }
}
