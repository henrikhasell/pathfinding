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

#include "World.hpp"

#define PROJECT_NAME "Pathfinding Demo"
#define SCREEN_W 600
#define SCREEN_H 600

// const char TILEMAP_DATA[30 * 30] = {
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
// 	1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
// };
// 
// Game::World world(30, 30, TILEMAP_DATA);

const char TILEMAP_DATA[20 * 20] = {
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
};
 
Game::World world(20, 20, TILEMAP_DATA);

bool smooth_path = true;
std::vector<Navigation::Vector> path;
Navigation::Vector start(0.0f, 0.0f), finish(0.0f, 0.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		switch(key)
		{
			case GLFW_KEY_SPACE:
				smooth_path = !smooth_path;
				break;
			case GLFW_KEY_S:
				world.soldierList.emplace_back(start.x, start.y, path);
				break;
			case GLFW_KEY_T:
				world.turretList.emplace_back(xpos, ypos);
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

			// Emplace turret.
			// turrets.emplace_back(50, 50);

			double frame_start = glfwGetTime();
			// Start main loop:
			while(glfwWindowShouldClose(window) != GL_TRUE)
			{
				glfwPollEvents();

				glClear(GL_COLOR_BUFFER_BIT);

				glPushMatrix();
					glScalef(
						Navigation::NodeMap::TileW,
						Navigation::NodeMap::TileH, 1.0f
					);
					for(int x = 0; x < world.nodeMap.width; x++)
					{
						for(int y = 0; y < world.nodeMap.height; y++)
						{
							Tile *tile = world.nodeMap.TileMap::GetTile(x, y);

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
				if(world.nodeMap.CalculatePath(start, finish, path) == true)
				{
					if(smooth_path)
					{

						std::vector<Navigation::Vector> minimal_path;

						Navigation::Vector previousViewpoint = path[0], currentViewpoint = path[0];

						minimal_path.push_back(start);

						for(Navigation::Vector selectedNode : path)
						{
							if(world.nodeMap.Visible(currentViewpoint, selectedNode) == false)
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

				for(Game::Soldier &soldier : world.soldierList)
				{
					glPushMatrix();
						glTranslatef(soldier.position.x, soldier.position.y, 0.0f);
						glPushMatrix();
							glScalef(9.0f, 9.0f, 1.0f);
							glRotatef(soldier.rotation * 57.2958f, 0.0f, 0.0f, 1.0f);
							glColor3f(0.0f, 1.0f, 1.0f);
							glBegin(GL_TRIANGLE_FAN);
								for(GLfloat i = 0.0f; i < M_PI * 2; i += 0.3f)
									glVertex2f( sinf(i), cosf(i) );
							glEnd();
							// Draw the soldier (outline).
							glColor3f(0.0f, 0.0f, 0.0f);
							glBegin(GL_LINE_LOOP);
								for(GLfloat i = 0.0f; i < M_PI * 2; i += 0.3f)
									glVertex2f( sinf(i), cosf(i) );
							glEnd();
							// Draw the soldier (direction).
							glBegin(GL_LINES);
								glVertex2f(0.0f, 0.0f);
								glVertex2f(0.0f, 1.0f);
							glEnd();
						glPopMatrix();
						glTranslatef(-10.0f, -15.0f, 0.0f);
						glColor3f(0.0f, 0.0f, 0.0f);
						glScalef(20.0f, 5.0f, 1.0f);
						glBegin(GL_TRIANGLE_STRIP);
							glVertex2f(0.0f, 0.0f);
							glVertex2f(1.0f, 0.0f);
							glVertex2f(0.0f, 1.0f);
							glVertex2f(1.0f, 1.0f);
						glEnd();
						glColor3f(1.0f, 0.0f, 0.0f);
						glScalef(soldier.hitpoints / Game::Soldier::MaximumHitpoints, 1.0f, 1.0f);
						glBegin(GL_TRIANGLE_STRIP);
							glVertex2f(0.0f, 0.0f);
							glVertex2f(1.0f, 0.0f);
							glVertex2f(0.0f, 1.0f);
							glVertex2f(1.0f, 1.0f);
						glEnd();
					glPopMatrix();
				}

				for(Game::Turret &turret : world.turretList)
				{
					glPushMatrix();
						glTranslatef(
							turret.position.x,
							turret.position.y, 0.0f);
						glScalef(
							Navigation::NodeMap::TileW,
							Navigation::NodeMap::TileW, 0.0f);
			glColor3f(0.2f, 0.2f, 0.2f);
						glBegin(GL_TRIANGLE_STRIP);
							glVertex2f(-0.5f,-0.5f);
							glVertex2f(+0.5f,-0.5f);
							glVertex2f(-0.5f,+0.5f);
							glVertex2f(+0.5f,+0.5f);
						glEnd();
						glColor3f(0.0f, 0.0f, 0.0f);
						glBegin(GL_LINE_LOOP);
							glVertex2f(-0.5f,-0.5f);
							glVertex2f(+0.5f,-0.5f);
							glVertex2f(+0.5f,+0.5f);
							glVertex2f(-0.5f,+0.5f);
						glEnd();
			glColor3f(1.0f, 0.0f, 0.0f);
						glRotatef(turret.rotation * 57.2958f,
							0.0f, 0.0f, 1.0f);
						glBegin(GL_LINES);
							glVertex2f(0.0f, 0.0f);
							glVertex2f(0.0f,-1.0f);
						glEnd();
					glPopMatrix();
					if(turret.target)
					{
						glColor3f(1.0f, 0.0f, 0.0f);
						glBegin(GL_POINTS);
							glVertex2f(
								turret.target->position.x,
								turret.target->position.y);
						glEnd();
					}
				}

				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POINTS);
				for(Game::Bullet &bullet : world.bulletList)
				{
					glVertex2f(
						bullet.position.x, bullet.position.y);
				}
				glEnd();

				glfwSwapBuffers(window);

				double frame_end = glfwGetTime();

				double elapsedTime = frame_end - frame_start;

				{
					std::vector<Game::Soldier>::iterator i =
						world.soldierList.begin();

					while(world.soldierList.end() != i)
					{
						i->Move(elapsedTime);

						if(i->path.empty() == true)
						{
							i = world.soldierList.erase(i);
						}
						else
						{
							i++;
						}
					}
				}

				for(Game::Turret &turret : world.turretList)
				{
					turret.Work(elapsedTime,
						world.soldierList, world.bulletList);
				}

				{
					std::vector<Game::Bullet>::iterator i =
						world.bulletList.begin();

					while(world.bulletList.end() != i)
					{
						i->Work(elapsedTime);

						if(i->detonated == true)
						{
							i->Explode(world.soldierList);
							i = world.bulletList.erase(i);
						}
						else
						{
							i++;
						}
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
