#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "World.hpp"

namespace Navigation
{
	class Soldier
	{
		public:
		    // Constant expressions:
		    static constexpr float MovementSpeed = 80.0f;
		    static constexpr float RotationSpeed = 0.1f;
		    // Constructor:
		    Soldier(float x, float y);
		    // Methods:
		    void SetPath(std::vector<Vector> &path);
		    void Move(double time);
			// Position:
			Vector position;
			// Rotation:
			float rotation;
		private:
			// Path:
			std::vector<Vector> path;
	};
};

#endif // SOLDIER_HPP
