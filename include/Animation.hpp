#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <GL/gl.h>
#include "Textures.hpp"

constexpr GLuint *ANIMATION_BUNNY_U = animalTextures + 4 * 3;
constexpr GLuint *ANIMATION_BUNNY_D = animalTextures + 4 * 2;
constexpr GLuint *ANIMATION_BUNNY_L = animalTextures + 4 * 0;
constexpr GLuint *ANIMATION_BUNNY_R = animalTextures + 4 * 1;

struct Animation
{
	Animation() :
		animation(ANIMATION_BUNNY_D),
		index(0),
		frameProgress(0.0),
		frameLength(0.1)
	{

	}
	GLuint *animation;
	size_t index;
	double frameProgress;
	double frameLength;

	void Work(double time, size_t length)
	{
		frameProgress += time;

		while(frameProgress >= frameLength)
		{
			if(++index >= length)
			{
				index = 0;
			}

			frameProgress -= frameLength;
		}
	}
};

#endif /* ANIMATION_HPP */
