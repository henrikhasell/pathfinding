#include "Bullet.hpp"
#include <iostream>
#include <algorithm>

using namespace Game;

Bullet::Bullet(Navigation::Vector &position, Soldier &soldier) :
	destination(soldier.position),
	direction(soldier.position - position),
	position(position),
	target(&soldier),
	detonated(false)
{
	direction.Normalise();
	soldier.bulletList.push_back(this);
}

Bullet::Bullet(const Bullet &other) :
	destination(other.destination),
	direction(other.direction),
	position(other.position),
	target(other.target),
	detonated(other.detonated)
{
	if(target)
	{
		target->bulletList.push_back(this);
	}
}

Bullet::~Bullet()
{
	if(target)
	{
			std::vector<Bullet*>::iterator location =
				std::find(target->bulletList.begin(), target->bulletList.end(), this);

			if(location != target->bulletList.end())
				target->bulletList.erase(location);
	}
}

Bullet &Bullet::operator=(const Bullet &other)
{
	destination = other.destination;
	direction = other.direction;
	position = other.position;
	detonated = other.detonated;

	if(target)
	{
		std::vector<Bullet*>::iterator location =
			std::find(target->bulletList.begin(), target->bulletList.end(), this);

		if(location != target->bulletList.end())
			target->bulletList.erase(location);
	}

	target = other.target;

	if(target)
	{
		target->bulletList.push_back(this);
	}

	return *this;
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

void Bullet::Explode(std::vector<Soldier> &soldierList)
{

	if(target)
	{
		float distance = (position - target->position).Magnitude();

		if(distance < 20.0f)
		{

			target->hitpoints -= 10.0f;

			if(target->hitpoints <= 0.0f)
			{
				std::vector<Soldier>::iterator location =
					 std::find(soldierList.begin(), soldierList.end(), *target);

				if(soldierList.end() != location)
					soldierList.erase(location);

				target = nullptr;
			}
		}
	}
}
