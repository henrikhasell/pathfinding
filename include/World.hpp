#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

namespace Game
{
	class Soldier;
	class Bullet;
	class Turret;
};

#include "Vector.hpp"
#include "Particle.hpp"
#include "Soldier.hpp"
#include "Turret.hpp"
#include "Bullet.hpp"
#include "NodeMap.hpp"

namespace Game
{
	struct World
	{
		World(int w, int h, const char data[]) :
			nodeMap(w, h, data), money(100), lives(5) {}

		Navigation::NodeMap nodeMap;

		std::vector<Navigation::Vector> path;
		std::vector<Particle> particleList;
		std::vector<Soldier> soldierList;
		std::vector<Turret> turretList;
		std::vector<Bullet> bulletList;
		int money, lives;
	};
};

#endif /* WORLD_HPP */
