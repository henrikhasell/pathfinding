#include "Turret.hpp"
#include "Soldier.hpp"
#include <cfloat>
#include <iostream>

using namespace Game;

Turret::Turret(Navigation::Vector &position) : Turret(position.x, position.y)
{

}

Turret::Turret(float x, float y) : position(x, y), target(nullptr), cooldown(0.0)
{

}
#include <algorithm>
void Turret::Work(double time, std::vector<Navigation::Soldier> &selection, std::vector<Game::Bullet> &bullets)
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
		Navigation::Soldier *nearestSoldier = nullptr;
		for(Navigation::Soldier &soldier : selection)
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

void Turret::FireBullet(Navigation::Soldier &target, std::vector<Game::Bullet> &bullets)
{
	Navigation::Vector nozzleVector = target.position - position;
	nozzleVector.Normalise();
	nozzleVector *= Turret::NozzleLength;
	nozzleVector += position;
	bullets.emplace_back(nozzleVector, target);
}

void Turret::TargetSoldier(Navigation::Soldier &soldier)
{
	target = &soldier;
}
