#include "TileMap.hpp"
#include <queue>

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

struct OpenSetComparator
{
    bool operator()(const Tile* left, const Tile* right) const
    {
        return left->GetHeuristic(finish) > right->GetHeuristic(finish);
    }

    static Tile *finish;
};

/* Not thread safe. */
Tile *OpenSetComparator::finish;

bool TileMap::CalculatePath(Tile *start, Tile *finish)
{
    std::priority_queue<Tile*, std::vector<Tile*>, OpenSetComparator> open_set;
	OpenSetComparator::finish = finish;
    Reset();

    open_set.push(start);

    start->SetCost(0);

    while(open_set.empty() != true)
    {
        Tile *head = open_set.top();
		open_set.pop();

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
                    open_set.push(selected);
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
                    open_set.push(selected);
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
