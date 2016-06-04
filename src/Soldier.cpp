#include "Soldier.hpp"

using namespace Navigation;

Soldier::Soldier(float x, float y) : position(x, y), rotation(0.0f)
{

}

Soldier::Soldier(float x, float y, std::vector<Vector> &path) : Soldier(x, y)
{
    SetPath(path);
}

void Soldier::SetPath(std::vector<Vector> &path)
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

        const Vector &target = path.front();
        // Calculate vector representing
        // the direction towards the target.
        Vector direction = target - position;
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
