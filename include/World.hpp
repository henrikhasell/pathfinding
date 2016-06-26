#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

namespace Game
{
	class Soldier;
	class Bullet;
	class Turret;
};

#include "Soldier.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"
#include "NodeMap.hpp"

namespace Game
{
	struct World
	{
		World(int w, int h, const char data[]) :
			nodeMap(w, h, data) {}

		Navigation::NodeMap nodeMap;

		std::vector<Soldier> soldierList;
		std::vector<Turret> turretList;
		std::vector<Bullet> bulletList;
	};
};

#endif /* WORLD_HPP */
