#ifndef TEXT_HPP
#define TEXT_HPP

#include <GL/gl.h>

extern GLuint characterTexture[16 *16];

void LoadCharacterTextures();

void RenderString(const char string[]);
void RenderFormattedString(const char format[], ...);

#endif /* TEXT_HPP */
