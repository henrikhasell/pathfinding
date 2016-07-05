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
			static float constexpr NozzleLength = 10.0f;
			static float constexpr RotationSpeed = 0.1f;
			Turret(Navigation::Vector &position);
			Turret(float x, float y);
			Turret(const Turret &other);
			~Turret();
			Turret &operator=(const Turret &other);
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
