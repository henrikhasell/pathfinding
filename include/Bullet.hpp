#ifndef BULLET_H
#define BULLET_H

#include "Vector.hpp"
#include "Soldier.hpp"

namespace Game
{
	class Bullet
	{
		public:
			static constexpr float Speed = 200.0f;//600.0f;
			static constexpr float Damage = 5.0f;

			Bullet(Navigation::Vector &start, Soldier &target);
			void Work(double time);
		// private:
			Navigation::Vector destination;
			Navigation::Vector direction;
			Navigation::Vector position;
			bool detonated;
	};
};

#endif /* BULLET_H */
