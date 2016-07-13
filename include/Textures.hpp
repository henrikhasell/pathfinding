#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <GL/gl.h>

extern GLuint tileTextures[5];
extern GLuint animalTextures[4 * 8];

void LoadTextures();
void FreeTextures();

#endif /* TEXTURES_HPP */
