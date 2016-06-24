#ifndef BULLET_H
#define BULLET_H

#include "World.hpp"
#include "Soldier.hpp"

namespace Game
{
	class Bullet
	{
		public:
			static constexpr float Speed = 500.0f;//600.0f;

			Bullet(Navigation::Vector &start, Navigation::Soldier &target);
			void Work(double time);
		// private:
			Navigation::Vector destination;
			Navigation::Vector direction;
			Navigation::Vector position;
			bool detonated;
	};
};

#endif /* BULLET_H */
