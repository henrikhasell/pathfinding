#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Vector.hpp"
#include "Animation.hpp"
#include <vector>

namespace Game
{
	class Turret;
	class Bullet;
	class World;

	class Soldier
	{
		public:
		    // Constant expressions:
		    static constexpr float MaximumHitpoints = 400.0f;
		    static constexpr float MovementSpeed = 40.0f;
		    static constexpr float Radius = 16.0f;

		    // Constructor:
		    Soldier(
				const Navigation::Vector &position,
				const std::vector<Navigation::Vector> &path
			);
			Soldier(const Soldier &soldier);
			Soldier &operator=(const Soldier &soldier);
			bool operator==(const Soldier &soldier);
			~Soldier();

			// Methods:
			void SetPath(std::vector<Navigation::Vector> &path);
			void Move(double time);
		//private:
			Animation animation;
			std::vector<Turret*> turretList;
			std::vector<Bullet*> bulletList;
			std::vector<Navigation::Vector> path;
			Navigation::Vector position;
			float hitpoints;
			float rotation;
	};
};

#endif // SOLDIER_HPP
