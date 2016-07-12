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

void Bullet::Work(double time, World &world)
{
	if(!detonated)
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

		if(Collide(world) == true)
		{
			if(target)
			{
				world.particleList.emplace_back(
					position,
					Navigation::Vector(0.0f, -100.0f),
					1.0f, 0.0f, 0.0f,
					1.5f,
					8.0f, "-10");
			}
			else
			{
				world.particleList.emplace_back(
					position,
					Navigation::Vector(0.0f, -100.0f),
					0.0f, 1.0f, 0.0f,
					0.2f,
					8.0f, "+$5");
			}
		}
		else if(detonated && target)
		{
			world.particleList.emplace_back(
				position,
				Navigation::Vector(0.0f, -100.0f),
				1.0f, 1.0f, 1.0f,
				0.2f,
				8.0f, "miss");
		}
	}
}

bool Bullet::Collide(World &world)
{
	if(target)
	{
		float distance = (position - target->position).Magnitude();

		if(distance < Soldier::Radius)
		{
			position = target->position;
			target->hitpoints -= 10.0f;

			if(target->hitpoints <= 0.0f)
			{
				std::vector<Soldier>::iterator location =
					 std::find(world.soldierList.begin(), world.soldierList.end(), *target);

				if(world.soldierList.end() != location)
				{
					world.soldierList.erase(location);
				}

				world.money += 5;

				target = nullptr;
			}

			detonated = true;

			return true;
		}
	}

	return false;
}
