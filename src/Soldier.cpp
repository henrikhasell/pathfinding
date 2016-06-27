#include "Soldier.hpp"
#include "Turret.hpp"
#include <iostream>

using namespace Game;

Soldier::Soldier(float x, float y) : position(x, y), hitpoints(MaximumHitpoints), rotation(0.0f)
{

}

Soldier::Soldier(float x, float y, std::vector<Navigation::Vector> &path) : Soldier(x, y)
{
	//std::cout << "[ Constructor] Creating object " << this << std::endl;
    SetPath(path);
}

Soldier::Soldier(const Soldier &soldier) :
	targetedBy(soldier.targetedBy),
	hitpoints(soldier.hitpoints),
	position(soldier.position),
	rotation(soldier.rotation),
	path(soldier.path)
{
	//std::cout << "[Copy Constructor] Copying " << &soldier << " to " << this << std::endl;

	for(Game::Turret *turret : targetedBy)
		turret->target = this;

	for(Game::Bullet *bullet : bulletList)
		bullet->target = this;
}

Soldier &Soldier::operator=(const Soldier &soldier)
{
	//std::cout << "[Assignment Operator] Copying " << &soldier << " to " << this << std::endl;

	for(Game::Turret *turret : targetedBy)
		if(turret->target == this)
			turret->target = nullptr;

	for(Game::Bullet *bullet : bulletList)
		if(bullet->target == this)
			bullet->target = nullptr;

	targetedBy = soldier.targetedBy;
	bulletList = soldier.bulletList;

	for(Game::Turret *turret : targetedBy)
		if(turret->target == &soldier)
			turret->target = this;

	for(Game::Bullet *bullet : bulletList)
		if(bullet->target == &soldier)
			bullet->target = this;

	hitpoints = soldier.hitpoints;
	position = soldier.position;
	rotation = soldier.rotation;

	path = soldier.path;

	return *this;
}

bool Soldier::operator==(const Soldier &soldier)
{
	return this == &soldier;
}

Soldier::~Soldier()
{
	for(Game::Turret *turret : targetedBy)
		if(turret->target == this)
			turret->target = nullptr;

	for(Game::Bullet *bullet : bulletList)
		if(bullet->target == this)
			bullet->target = nullptr;
}

void Soldier::SetPath(std::vector<Navigation::Vector> &path)
{
    this->path = path;
}

void Soldier::Move(double time)
{
    if(path.empty() == true)
    {
        return;
    }
    // Distance remaining is the total distance
    // the soldier is able to travel this frame.
    float distance_remaining = MovementSpeed * time;

    while(distance_remaining > 0.0f)
    {
        if(path.empty() == true)
        {
            break;
        }

        const Navigation::Vector &target = path.front();
        // Calculate vector representing
        // the direction towards the target.
        Navigation::Vector direction = target - position;
        // The magnitude of the vector is equal
        // to the distance form the target.
        float distance_to_target = direction.Magnitude();
        // Move the soldier towards the node
        // and adjust the remaining distance.
        if(distance_to_target > 0.0f)
        {
            // Update the rotation to face the target.
            rotation = atan2f(
                -direction.x, direction.y);

            if(distance_to_target < distance_remaining)
            {
                position = target;
            }
            else
            {
                direction /= distance_to_target;
                direction *= distance_remaining;
                position += direction;
            }

            distance_remaining -= distance_to_target;
        }
        else
        {
            path.erase( path.begin() );
        }
    }
}
