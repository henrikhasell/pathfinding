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

            // Initialise OpenGL:
            glPointSize(5.0f);

            // Initialise projection:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluOrtho2D(0.0, SCREEN_W, SCREEN_H, 0.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();


            double frame_start = glfwGetTime();
            // Start main loop:
            while(glfwWindowShouldClose(window) != GL_TRUE)
            {
                glfwPollEvents();

				glClear(GL_COLOR_BUFFER_BIT);

                glPushMatrix();
                    glScalef(
                        Navigation::World::TileW,
                        Navigation::World::TileH, 1.0f
                    );
                    for(int x = 0; x < world.width; x++)
                    {
                        for(int y = 0; y < world.height; y++)
                        {
                            Tile *tile = world.TileMap::GetTile(x, y);

                            glPushMatrix();
                                if(tile->GetNavigable() == true)
                                    glColor3f(0.5f, 0.5f, 0.5f);
                                else
                                    glColor3f(0.1f, 0.1f, 0.1f);
                                glTranslatef(x, y, 0.0f);
                                glBegin(GL_TRIANGLE_STRIP);
                                    glVertex2f(0.0f, 0.0f);
                                    glVertex2f(1.0f, 0.0f);
                                    glVertex2f(0.0f, 1.0f);
                                    glVertex2f(1.0f, 1.0f);
                                glEnd();
                                glColor3f(0.0f, 0.0f, 0.0f);
                                glBegin(GL_LINE_LOOP);
                                    glVertex2f(0.0f, 0.0f);
                                    glVertex2f(1.0f, 0.0f);
                                    glVertex2f(1.0f, 1.0f);
                                    glVertex2f(0.0f, 1.0f);
                                glEnd();
                            glPopMatrix();
                        }
                    }
                glPopMatrix();

                path.clear();
                // Calculate a path between the
                // start and finish vectors if
                // possible:
                if(world.CalculatePath(start, finish, path) == true)
                {
                    if(smooth_path)
                    {

                        std::vector<Navigation::Vector> minimal_path;

                        Navigation::Vector previousViewpoint = path[0], currentViewpoint = path[0];

                        minimal_path.push_back(start);

                        for(Navigation::Vector selectedNode : path)
                        {
                            if(world.Visible(currentViewpoint, selectedNode) == false)
                            {
                                minimal_path.push_back(previousViewpoint);
                                currentViewpoint = previousViewpoint;
                            }

                            previousViewpoint = selectedNode;
                        }

                        minimal_path.push_back(finish);

                        path = minimal_path;
                    }

                    glColor3f(1.0f, 0.0f, 0.0f);
                    // Draw the path (line):
                    glBegin(GL_LINE_STRIP);
                    for(Navigation::Vector &i : path)
                    {
                        glVertex2f(i.x, i.y);
                    }
                    glEnd();

                    glColor3f(0.0f, 0.0f, 1.0f);
                    // Draw the path (vertices):
                    glBegin(GL_POINTS);
                    for(Navigation::Vector &i : path)
                    {
                        glVertex2f(i.x, i.y);
                    }
                    glEnd();
                }
                // Draw the start and finish positions of the path.
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_POINTS);
                    if(start.x || start.y)
                        glVertex2f(start.x, start.y);
                    if(finish.x || finish.y)
                        glVertex2f(finish.x, finish.y);
                glEnd();

                for(Navigation::Soldier &soldier : army)
                {
                    glPushMatrix();
                        glTranslatef(
                            soldier.position.x,
                            soldier.position.y, 0.0f);
                        glScalef(
                            9.0f, 9.0f, 1.0f);
                        glRotatef(soldier.rotation * 57.2958f,
                            0.0f, 0.0f, 1.0f);
                        // Draw the soldier (fill).
                        glColor3f(0.0f, 1.0f, 1.0f);
                        glBegin(GL_TRIANGLE_FAN);
                            for(GLfloat i = 0.0f; i < M_PI * 2; i += 0.3f)
                            {
                                glVertex2f( sinf(i), cosf(i) );
                            }
                        glEnd();
                        // Draw the soldier (outline).
                        glColor3f(0.0f, 0.0f, 0.0f);
                        glBegin(GL_LINE_LOOP);
                            for(GLfloat i = 0.0f; i < M_PI * 2; i += 0.3f)
                            {
                                glVertex2f( sinf(i), cosf(i) );
                            }
                        glEnd();
                        // Draw the soldier (direction).
                        glBegin(GL_LINES);
                            glVertex2f(0.0f, 0.0f);
                            glVertex2f(0.0f, 1.0f);
                        glEnd();
                    glPopMatrix();
                }
                glfwSwapBuffers(window);
                double frame_end = glfwGetTime();

                for(Navigation::Soldier &soldier : army)
                {
                    soldier.Move(frame_end - frame_start);
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
