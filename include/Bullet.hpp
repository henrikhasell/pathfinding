#ifndef BULLET_H
#define BULLET_H

#include "Vector.hpp"
#include "Soldier.hpp"
#include "World.hpp"

#include <vector>

namespace Game
{
	class Bullet
	{
		public:
			static constexpr float Speed = 400.0f;//600.0f;
			static constexpr float Damage = 5.0f;

			// Constructor:
			Bullet(Navigation::Vector &start, Soldier &target);
			// Copy constructor:
			Bullet(const Bullet &other);
			// Deestructor:
			~Bullet();
			// Assignment operator:
			Bullet &operator=(const Bullet &other);

			void Work(double time, World &world);
			virtual bool Collide(World &world);
		// private:
			Soldier *target;
			Navigation::Vector destination;
			Navigation::Vector direction;
			Navigation::Vector position;
			bool detonated;
	};
};

#endif /* BULLET_H */
