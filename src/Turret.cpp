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

void Turret::Work(double time, std::vector<Soldier> &selection, std::vector<Bullet> &bullets)
{
	if(TargetInRange() == false)
	{
		if(target)
		{
			std::vector<Game::Turret*> &targetedBy = target->targetedBy;
			std::vector<Game::Turret*>::iterator location = std::find(targetedBy.begin(), targetedBy.end(), this);

			if(location != targetedBy.end())
			{
				target->targetedBy.erase(location);
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
			nearestSoldier->targetedBy.push_back(this);
			target = nearestSoldier;
		}			
		else
		{
			target = nullptr;
		}
	}

	if(target)
	{
		Navigation::Vector direction = position - target->position;
		direction /= direction.Magnitude();

		rotation = atan2f(-direction.x, direction.y);

		cooldown -= time;

		if(cooldown <= 0.0)
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
	return 200.0f;
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
