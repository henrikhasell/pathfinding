#include "Turret.hpp"
#include "Soldier.hpp"
#include <cfloat>
#include <iostream>
#include <algorithm>

using namespace Game;

Turret::Turret(Navigation::Vector &position) :
	Turret(position.x, position.y)
{

}

Turret::Turret(float x, float y) :
	position(x, y),
	target(nullptr),
	rotation(0.0f),
	cooldown(0.0)
{

}

Turret::Turret(const Turret &other) :
	position(other.position),
	rotation(other.rotation),
	cooldown(other.cooldown),
	target(other.target)
{
	if(target)
		target->turretList.push_back(this);
}

Turret::~Turret()
{
	if(target)
	{
		std::vector<Game::Turret*>::iterator location =
			std::find(target->turretList.begin(), target->turretList.end(), this);

		if(location != target->turretList.end())
			target->turretList.erase(location);
	}
}

Turret &Turret::operator=(const Turret &other)
{
	position = other.position;
	rotation = other.rotation;
	cooldown = other.cooldown;

	if(target)
	{
		std::vector<Game::Turret*>::iterator location =
			std::find(target->turretList.begin(), target->turretList.end(), this);

		if(location != target->turretList.end())
			target->turretList.erase(location);
	}

	target = other.target;

	if(target)
		target->turretList.push_back(this);
}

void Turret::Work(double time, std::vector<Soldier> &selection, std::vector<Bullet> &bullets)
{
	if(TargetInRange() == false)
	{
		if(target)
		{
			std::vector<Game::Turret*> &turretList = target->turretList;
			std::vector<Game::Turret*>::iterator location = std::find(turretList.begin(), turretList.end(), this);

			if(location != turretList.end())
			{
				target->turretList.erase(location);
			}
		}

		float shortestDistance = FLT_MAX;
		Soldier *nearestSoldier = nullptr;
		for(Soldier &soldier : selection)
		{
			Navigation::Vector relativePosition = position - soldier.position;

			float distance = relativePosition.Magnitude();

			if(distance < shortestDistance)
			{
				shortestDistance = distance;
				nearestSoldier = &soldier;
			}
		}

		if(shortestDistance <= GetRange())
		{
			nearestSoldier->turretList.push_back(this);
			target = nearestSoldier;
		}
		else
		{
			target = nullptr;
		}
	}

	if(target)
	{
		cooldown -= time;
		bool facingTarget = false;
		Navigation::Vector direction = position - target->position;
		direction /= direction.Magnitude();

		float desiredRotation = atan2f(-direction.x, direction.y);

		float delta = rotation - desiredRotation;

		float deltaAngle = atan2(sin(delta), cos(delta));

		if(fabs(deltaAngle) < RotationSpeed)
		{
			rotation = desiredRotation;
			facingTarget = true;
		}
		else
		{
			if(deltaAngle < 0)
			{
				rotation += RotationSpeed;
			}
			else
			{
				rotation -= RotationSpeed;
			}
		}

		if(facingTarget && cooldown <= 0.0)
		{
			cooldown = 0.25;
			FireBullet(*target, bullets);
		}
	}
}

bool Turret::TargetInRange()
{
	if(!target)
	{
		return false;
	}

	Navigation::Vector relativePosition = position - target->position;
	float distance = relativePosition.Magnitude();
	return distance <= GetRange();
}

float Turret::GetRange()
{
	return 100.0f;
}

void Turret::FireBullet(Soldier &target, std::vector<Bullet> &bullets)
{
	Navigation::Vector nozzleVector = target.position - position;
	nozzleVector.Normalise();
	nozzleVector *= Turret::NozzleLength;
	nozzleVector += position;
	bullets.emplace_back(nozzleVector, target);
}

void Turret::TargetSoldier(Soldier &soldier)
{
	target = &soldier;
}
