#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "World.hpp"

namespace Game
{
	class Turret;
};

namespace Navigation
{
	class Soldier
	{
		public:
		    // Constant expressions:
		    static constexpr float MovementSpeed = 60.0f;
		    static constexpr float RotationSpeed = 0.1f;
		    // Constructor:
		    Soldier(float x, float y);
		    Soldier(float x, float y, std::vector<Vector> &path);
                    Soldier(const Soldier &soldier);
                    Soldier &operator=(const Soldier &soldier);
                    ~Soldier();
		    // Methods:
		    void SetPath(std::vector<Vector> &path);
		    void Move(double time);
			// Position:
			Vector position;
			// Rotation:
			float rotation;
		//private:
			std::vector<Game::Turret*> targetedBy;
			// Path:
			std::vector<Vector> path;
	};
};

#endif // SOLDIER_HPP
