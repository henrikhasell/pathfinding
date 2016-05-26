#ifndef SOLDIER_H
#define SOLDIER_H

#include "World.h"

namespace Navigation
{
	class Soldier
	{
		public:
		    // Constant expressions:
		    static constexpr float MovementSpeed = 2.0f;
		    static constexpr float RotationSpeed = 0.1f;
		    // Constructor:
		    Soldier(float x, float y);
		    // Methods:
		    void SetPath(std::vector<Vector> path);
			// Position:
			Vector position;
			// Rotation:
			float rotation;
		private:
			// Path:
			std::vector<Vector> path;
	};
};

#endif // SOLDIER_H
