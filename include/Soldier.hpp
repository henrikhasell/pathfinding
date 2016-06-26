#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Vector.hpp"
#include "World.hpp"
#include <vector>

namespace Game
{
	class Turret;

	class Soldier
	{
		public:
		    // Constant expressions:
		    static constexpr float MovementSpeed = 40.0f;
		    static constexpr float RotationSpeed = 0.1f;
		    // Constructor:
		    Soldier(float x, float y);
		    Soldier(float x, float y, std::vector<Navigation::Vector> &path);
            Soldier(const Soldier &soldier);
            Soldier &operator=(const Soldier &soldier);
			bool operator==(const Soldier &soldier);
            ~Soldier();
		    // Methods:
		    void SetPath(std::vector<Navigation::Vector> &path);
		    void Move(double time);
		//private:
			std::vector<Turret*> targetedBy;
			std::vector<Bullet*> bulletList;
			std::vector<Navigation::Vector> path;
			Navigation::Vector position;
			float hitpoints;
			float rotation;
	};
};

#endif // SOLDIER_HPP
