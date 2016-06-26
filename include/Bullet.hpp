#ifndef BULLET_H
#define BULLET_H

#include "Vector.hpp"
#include "Soldier.hpp"
#include <vector>
namespace Game
{
	class Bullet
	{
		public:
			static constexpr float Speed = 400.0f;//600.0f;
			static constexpr float Damage = 5.0f;

			Bullet(Navigation::Vector &start, Soldier &target);
			Bullet(const Bullet &other);
			~Bullet();
			Bullet &operator=(const Bullet &other);
			void Work(double time);
			virtual void Explode(std::vector<Soldier> &soldierList);
		// private:
			Soldier *target;
			Navigation::Vector destination;
			Navigation::Vector direction;
			Navigation::Vector position;
			bool detonated;
	};
};

#endif /* BULLET_H */
