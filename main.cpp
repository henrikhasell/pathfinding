#ifdef _WIN32
#   include <Windows.h>
#endif

#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <cstring>

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "World.hpp"
#include "Text.hpp"
#include "Textures.hpp"

#define PROJECT_NAME "Pathfinding Demo"
#define SCREEN_W 32 * 20
#define SCREEN_H 32 * 20

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
       1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
};

Game::World world(20, 20, TILEMAP_DATA);

std::vector<Navigation::Vector> path;
Navigation::Vector start(16.5f * 32.0f, 0.5f * 32.0f), finish(16.5f * 32.0f, 19.5 * 32.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		double xpos;
		double ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		switch(key)
		{
			case GLFW_KEY_S:
				world.soldierList.emplace_back(start, path);
				break;
			case GLFW_KEY_T:
				if(world.money >= 20)
				{
					Tile *tile =
						world.nodeMap.GetTile(Navigation::Vector(xpos, ypos));

					if(tile->GetType() == Tile::WALL)
					{
						tile->SetType(Tile::TURRET);

						world.turretList.emplace_back(
							tile->GetX() * Navigation::NodeMap::TileW + 16.0f,
							tile->GetY() * Navigation::NodeMap::TileH + 16.0f
						);

						world.money -= 20;
					}
				}
				break;
			case GLFW_KEY_P:
				static int counter = 0;
				world.particleList.emplace_back(
					Navigation::Vector(xpos, ypos),
					Navigation::Vector(0.0f, -20.0f),
					1.0f, 1.0f, 1.0f,
					0.1f,
					8.0f,
					"Hello, world! %d", counter++);
				break;
		}
	}
}


// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
// {
// 	if(action == GLFW_PRESS)
// 	{
// 		double xpos;
// 		double ypos;
//
// 		glfwGetCursorPos(window, &xpos, &ypos);
//
// 		switch(button)
// 		{
// 			case GLFW_MOUSE_BUTTON_LEFT:
// 				start.x = xpos;
// 				start.y = ypos;
// 				break;
// 			case GLFW_MOUSE_BUTTON_RIGHT:
// 				finish.x = xpos;
// 				finish.y = ypos;
// 				break;
// 		}
// 	}
// }
//
// void cursor_pos_callback(GLFWwindow *window, double x, double y)
// {
// 	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == true)
// 	{
// 		mouse_button_callback(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
// 	}
//
// 	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == true)
// 	{
// 		mouse_button_callback(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0);
// 	}
// }

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
			// glfwSetMouseButtonCallback(window, mouse_button_callback);
			// glfwSetCursorPosCallback(window, cursor_pos_callback);

			// Create OpenGL context:
			glfwMakeContextCurrent(window);
			glfwSwapInterval(1);

			// Initialise OpenGL:
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPointSize(5.0f);

			// Load character textures:
			LoadCharacterTextures();
			LoadTextures();

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
								glTranslatef(x, y, 0.0f);

								Tile::Type type = tile->GetType();

								switch(type)
								{
								case Tile::Type::ROAD:
									glBindTexture(GL_TEXTURE_2D, tileTextures[0]);
									break;
								default:
									glBindTexture(GL_TEXTURE_2D, tileTextures[2]);
									break;
								}
								glColor3f(1.0f, 1.0f, 1.0f);
								glBegin(GL_TRIANGLE_STRIP);
									glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
									glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
									glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
									glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
								glEnd();


								glBindTexture(GL_TEXTURE_2D, 0);
/*
								switch(type)
								{
								case Tile::Type::ROAD:
									glColor3f(0.5f, 0.5f, 0.5f);

									glBegin(GL_TRIANGLE_STRIP);
										glVertex2f(0.0f, 0.0f);
										glVertex2f(1.0f, 0.0f);
										glVertex2f(0.0f, 1.0f);
										glVertex2f(1.0f, 1.0f);
									glEnd();

									glColor3f(0.4f, 0.4f, 0.4f);

									glBegin(GL_TRIANGLE_STRIP);
										glVertex2f(0.5f, 0.0f);
										glVertex2f(1.0f, 0.5f);
										glVertex2f(0.0f, 0.5f);
										glVertex2f(0.5f, 1.0f);
									glEnd();
									break;

								case Tile::Type::WALL:
									glColor3f(0.05f, 0.05f, 0.05f);
									glBegin(GL_TRIANGLE_STRIP);
										glVertex2f(0.0f, 0.0f);
										glVertex2f(1.0f, 0.0f);
										glVertex2f(0.0f, 1.0f);
										glVertex2f(1.0f, 1.0f);
									glEnd();
									break;
								}
*/
								// glColor3f(0.0f, 0.0f, 0.0f);
								// glBegin(GL_LINE_LOOP);
								// 	glVertex2f(0.0f, 0.0f);
								// 	glVertex2f(1.0f, 0.0f);
								// 	glVertex2f(1.0f, 1.0f);
								// 	glVertex2f(0.0f, 1.0f);
								// glEnd();
							glPopMatrix();
						}
					}
				glPopMatrix();

				path.clear();
				// Calculate a path between the
				// start and finish vectors if
				// possible:
				world.nodeMap.CalculatePath(start, finish, path);

				for(Game::Soldier &soldier : world.soldierList)
				{
					glPushMatrix();
						glTranslatef(soldier.position.x, soldier.position.y, 0.0f);
						glPushMatrix();
							glScalef(Game::Soldier::Radius, Game::Soldier::Radius, 1.0f);
							glRotatef(soldier.rotation * 57.2958f, 0.0f, 0.0f, 1.0f);
							glColor3f(0.0f, 1.0f, 1.0f);
							glBegin(GL_TRIANGLE_FAN);
								for(GLfloat i = 0.0f; i < M_PI * 2; i += 0.3f)
									glVertex2f( sinf(i), cosf(i) );
							glEnd();
							// Draw the soldier (outline).
							glColor3f(0.0f, 0.0f, 0.0f);
							// glBegin(GL_LINE_LOOP);
							// 	for(GLfloat i = 0.0f; i < M_PI * 2; i += 0.3f)
							// 		glVertex2f( sinf(i), cosf(i) );
							// glEnd();
							// Draw the soldier (direction).
							glBegin(GL_LINES);
								glVertex2f(0.0f, 0.0f);
								glVertex2f(0.0f, 1.0f);
							glEnd();
						glPopMatrix();
						if(soldier.hitpoints < Game::Soldier::MaximumHitpoints)
						{
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
						}
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
						//glBegin(GL_LINE_LOOP);
						//	glVertex2f(-0.5f,-0.5f);
						//	glVertex2f(+0.5f,-0.5f);
						//	glVertex2f(+0.5f,+0.5f);
						//	glVertex2f(-0.5f,+0.5f);
						//glEnd();
						glScalef(0.5f, 0.5f, 1.0f);
						glColor3f(1.0f, 0.0f, 0.0f);
						glRotatef(turret.rotation * 57.2958f,
							0.0f, 0.0f, 1.0f);
						glBegin(GL_LINES);
							glVertex2f(0.0f, 0.0f);
							glVertex2f(0.0f,-1.0f);
						glEnd();
					glPopMatrix();
					// if(turret.target)
					// {
					// 	glColor3f(1.0f, 0.0f, 0.0f);
					// 	glBegin(GL_POINTS);
					// 		glVertex2f(
					// 			turret.target->position.x,
					// 			turret.target->position.y);
					// 	glEnd();
					// }
				}

				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POINTS);
				for(Game::Bullet &bullet : world.bulletList)
				{
					glVertex2f(
						bullet.position.x, bullet.position.y);
				}
				glEnd();

				for(Particle &particle : world.particleList)
				{
					glColor4f(particle.r, particle.g, particle.b, particle.a);
					glPushMatrix();
						glTranslatef(particle.position.x, particle.position.y, 0.0f);

						size_t stringLength = strlen(particle.text);

						if(stringLength == 0)
						{
							glScalef(particle.scale, particle.scale, 1.0f);
							glBegin(GL_TRIANGLE_STRIP);
								glVertex2f(-0.5f,-0.5f);
								glVertex2f(+0.5f,-0.5f);
								glVertex2f(-0.5f,+0.5f);
								glVertex2f(+0.5f,+0.5f);
							glEnd();
						}
						else
						{
							glScalef(particle.scale, particle.scale, 1.0f);
							glTranslatef(-(GLfloat)stringLength/2.0f, -0.5f, 0.0f);
							RenderString(particle.text);
						}
					glPopMatrix();
				}

				glPushMatrix();
					glScalef(8.0f, 8.0f, 1.0f);
					glTranslatef(0.5f, 0.5f, 0.0f);
					glColor3f(1.0f, 1.0f, 1.0f);
					RenderString("Hello, world!");
					glTranslatef(0.0f, 1.5f, 0.0f);
					RenderString("Press \"T\" to spawn turrets.");
					glTranslatef(0.0f, 1.5f, 0.0f);
					RenderString("Press \"S\" to spawn soldiers.");
					glTranslatef(0.0f, 1.5f, 0.0f);
					RenderFormattedString("Current funds: $%d", world.money);
					glTranslatef(0.0f, 1.5f, 0.0f);
					if(world.lives <= 0)
					{
						glScalef(3.0f, 3.0f, 1.0f);
						RenderString("GAME OVER");
					}
					else
					{
						RenderFormattedString("Lives remaining: %d", world.lives);
					}
				glPopMatrix();

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
							if(world.lives) // != 0
								world.lives--;
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
						i->Work(elapsedTime, world);

						if(i->detonated == true)
						{
							i = world.bulletList.erase(i);
						}
						else
						{
							i++;
						}
					}
				}

				{
					std::vector<Particle>::iterator i =
						world.particleList.begin();

					while(world.particleList.end() != i)
					{
						i->position += i->velocity * elapsedTime;
						i->a -= i->fadeSpeed * elapsedTime;

						if(i->a <= 0.0f)
						{
							i = world.particleList.erase(i);
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
