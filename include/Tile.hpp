#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
public:
	enum Type
	{
		ROAD, WALL, TURRET
	};

	void Initialise(int x, int y, Type type);
	void Reset();

	void SetCost(float cost);
	float GetCost();

	void SetType(Type type);
	Type GetType();

	bool SetParent(Tile *parent, float cost);
	Tile *GetParent();

	int GetHeuristic(Tile *destination);

	int GetX();
	int GetY();

private:
	Tile *parent;
	float cost;
	int x;
	int y;
	Type type;
};

#endif // TILE_HPP
