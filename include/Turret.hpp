#ifndef TURRET_HPP
#define TURRET_HPP

#include "Vector.hpp"
#include "World.hpp"
#include <vector>

namespace Game
{
	class Turret
	{
		public:
			static float constexpr NozzleLength = 20.0f;

			Turret(Navigation::Vector &position);
			Turret(float x, float y);
			void Work(
				double time,
				std::vector<Soldier> &selection,
				std::vector<Bullet> &bullets);
			bool TargetInRange();
			virtual float GetRange();
		protected:
			virtual void FireBullet(
				Soldier &target,
				std::vector<Bullet> &bullets);
			void TargetSoldier(
				Soldier &soldier);
		public: // private: Temporary~!
			Navigation::Vector position;
			float rotation;
			double cooldown;
			Soldier *target;
	};
};

#endif /* TURRET_HPP */
