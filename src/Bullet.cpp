#include "Bullet.hpp"
#include <iostream>

using namespace Game;

Bullet::Bullet(Navigation::Vector &position, Navigation::Soldier &target) :
	destination(target.position),
	direction(target.position - position),
	position(position),
	detonated(false)
{
	direction.Normalise();
}

void Bullet::Work(double time)
{
	double distanceAvailable = time * Bullet::Speed;

	double distanceToDestination = (destination - position).Magnitude();

	if(distanceToDestination <= distanceAvailable)
	{
		position = destination;
		detonated = true;
	}
	else
	{
		position += direction * distanceAvailable;
	}
}
