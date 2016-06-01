#include "Soldier.hpp"

using namespace Navigation;

Soldier::Soldier(float x, float y) : position(x, y), rotation(0.0f)
{

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

    float distance_remaining = MovementSpeed * time;

    while(distance_remaining > 0.0f)
    {
        if(path.empty() == true)
        {
            break;
        }

        const Vector &target = path.front();

        Vector direction = target - position;

        float distance_to_target = direction.Magnitude();

        if(distance_to_target > 0.0f)
        {
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
