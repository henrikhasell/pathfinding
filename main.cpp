#ifdef _WIN32
#   include <Windows.h>
#endif

#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "TileMap.hpp"
#include "World.hpp"
#include "Soldier.hpp"

#define PROJECT_NAME "Pathfinding Demo"
#define SCREEN_W 600
#define SCREEN_H 600

enum MouseMode{
    NORMAL, PLACE_WALL, PLACE_FLOOR
}mouse_mode = PLACE_WALL;

const char TILEMAP_DATA[30 * 30] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

std::vector<Navigation::Vector> path;

std::vector<Navigation::Soldier> army;

// Structure which represents navigable environment.
Navigation::World world(30, 30, TILEMAP_DATA);

// Start and finish points of our desired path.
Navigation::Vector start(0.0f, 0.0f), finish(0.0f, 0.0f);

bool smooth_path = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_SPACE:
                smooth_path = !smooth_path;
                break;
            case GLFW_KEY_S:
                army.emplace_back(start.x, start.y, path);
                break;
        }
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        double xpos;
        double ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        switch(button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                start.x = xpos;
                start.y = ypos;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                finish.x = xpos;
                finish.y = ypos;
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                {
                    Navigation::Vector location(xpos, ypos);

                    Tile *tile = world.GetTile(location);

                    if(tile)
                    {
                        if(world.GetTile(location)->GetNavigable() == true)
                        {
                            mouse_mode = PLACE_WALL;
                        }
                        else
                        {
                            mouse_mode = PLACE_FLOOR;
                        }
                    }
                }
                break;
        }
    }
}

void cursor_pos_callback(GLFWwindow *window, double x, double y)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == true)
    {
        mouse_button_callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == true)
    {
        mouse_button_callback(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0);
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == true)
    {
        Navigation::Vector location(x, y);
        // Find the tile under the mouse cursor.
        Tile *tile = world.GetTile(location);

        if(tile)
        {
            switch(mouse_mode)
            {
                case NORMAL:
                    // Do nothing!
                    break;
                case PLACE_FLOOR:
                    tile->SetNavigable(true);
                    break;
                case PLACE_WALL:
                    tile->SetNavigable(false);
                    break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    GLFWwindow* window = NULL;

    if(glfwInit() == GL_TRUE)
    {
        window = glfwCreateWindow(SCREEN_W, SCREEN_H, PROJECT_NAME, NULL, NULL);

        if(window != NULL)
        {
            // Initialise GLFW:
            glfwSetKeyCallback(window, key_callback);
            glfwSetMouseButtonCallback(window, mouse_button_callback);
            glfwSetCursorPosCallback(window, cursor_pos_callback);

            // Create OpenGL context:
            glfwMakeContextCurrent(window);

            // Start main loop:
            while(glfwWindowShouldClose(window) != GL_TRUE)
            {
                // Get the time at the
                // start of the frame.
                static double frame_start = glfwGetTime();

                glfwPollEvents();

                // Get the time at the
                // end of the frame.
                double frame_end = glfwGetTime();

                // Calculate the elapsed time.
                double frame_time = frame_end - frame_start;

                // Move every soldier the
                // appropriate distance.
                for(Navigation::Soldier &soldier : army)
                {
                    soldier.Move(frame_time);
                }

                std::vector<Navigation::Soldier>::iterator i = army.begin();

                // Iterate over the army array
                // and remove any soldiers who
                // have nowhere to walk.
                while(army.end() != i)
                {
                    if(i->path.empty() == true)
                    {
                        i = army.erase(i);
                    }
                    else
                    {
                        i++;
                    }
                }
                glfwSwapBuffers(window);
                // Slightly hacky way of ensuring
                // time steps are accurate. It makes
                // sense if you think about it.
                frame_start = frame_end;
            }
        }
        else
        {
            std::cerr << "Failed to create GLFW window." << std::endl;
        }

        glfwTerminate();
    }
    else
    {
        std::cerr << "Failed to initialise GLFW." << std::endl;
    }

    return window ? 0 : -1;
}
