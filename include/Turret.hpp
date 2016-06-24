#ifndef TURRET_HPP
#define TURRET_HPP

#include <vector>
#include "World.hpp"
#include "Bullet.hpp"

namespace Navigation
{
	class Soldier;
};

namespace Game
{
	class Turret
	{
		public:
			static float constexpr NozzleLength = Navigation::World::TileW;

			Turret(Navigation::Vector &position);
			Turret(float x, float y);
			void Work(
				double time,
				std::vector<Navigation::Soldier> &selection,
				std::vector<Game::Bullet> &bullets);
			bool TargetInRange();
			virtual float GetRange();
		protected:
			virtual void FireBullet(
				Navigation::Soldier &target,
				std::vector<Game::Bullet> &bullets);
			void TargetSoldier(
				Navigation::Soldier &soldier);
		public: // private: Temporary~!
			Navigation::Vector position;
			float rotation;
			double cooldown;
			Navigation::Soldier *target;
	};
};

#endif /* TURRET_HPP */
