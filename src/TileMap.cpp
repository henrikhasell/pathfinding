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
            GetTile(x, y)->Initialise(x, y, Tile::WALL);
        }
    }
}

TileMap::TileMap(int width, int height, const char data[]) : TileMap(width, height)
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
			Tile *tile = GetTile(x, y);

            // Set the tile navigability based on the data.
            switch(data[x + width * y])
            {
				case 0:
					tile->SetType(Tile::ROAD); break;
				case 1:
					tile->SetType(Tile::WALL); break;
			}
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

bool TileMap::CalculatePath(Tile *start, Tile *finish)
{
    std::queue<Tile*> open_set;

    Reset();

    open_set.push(start);

    start->SetCost(0);

    while(open_set.empty() != true)
    {
        Tile *head = open_set.front();

        int x = head->GetX();
        int y = head->GetY();

        Tile *adjacent[4] = {
            GetTile(x + 1, y + 0),
            GetTile(x - 1, y + 0),
            GetTile(x + 0, y + 1),
            GetTile(x + 0, y - 1)
        };

//        Tile *diagonal[4] = {
//            GetTile(x + 1, y + 1),
//            GetTile(x - 1, y - 1),
//            GetTile(x + 1, y - 1),
//            GetTile(x - 1, y + 1)
//        };

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

//        for(Tile *selected : diagonal)
//        {
//            if(selected && selected->SetParent(head, 1.4f) == true)
//            {
//                if(selected == finish)
//                {
//                    return true;
//                }
//                else
//                {
//                    open_set.push(selected);
//                }
//            }
//        }

        open_set.pop();
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
