#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Vector.hpp"
#include <cstdarg>
#include <cstdio>

struct Particle
{
	char text[32];
	Navigation::Vector position;
	Navigation::Vector velocity;
	float r;
	float g;
	float b;
	float a;
	float fadeSpeed;
	float scale;

	Particle(
		const Navigation::Vector &position,
		const Navigation::Vector &velocity,
		float r, float g, float b,
		float fadeSpeed,
		float scale = 8.0f,
		const char format[] = "", ...) :
		position(position),
		velocity(0.0f, -30.0f),
		r(r),
		g(g),
		b(b),
		a(1.0f),
		fadeSpeed(fadeSpeed),
		scale(scale)
	{
		va_list argumentList;
		va_start(argumentList, format);
		vsnprintf(text, sizeof(text), format, argumentList);
		va_end(argumentList);
	}
};
/*
struct Particle
{
	enum Type
	{
		TEXT, SMOKE
	};

	struct Text
	{
		char text[32];
		Navigation::Vector position;
		float visibility;
	};

	struct Smoke
	{
		Navigation::Vector position;
		Navigation::Vector direction;
		float visibility;
	};

	union
	{
		Text text;
		Smoke smoke;
	};


	static Particle CreateSmokeParticle(Navigation::Vector &position);
};
*/
/*
class Particle
{
public:
	Particle(Navigation::Vector &position);
	virtual bool Move(double time) = 0;
	virtual void Draw() = 0;
private:
	Navigation::Vector position;
};

class SmokeParticle : public Particle
{
public:
	SmokeParticle(Navigation::Vector &position);
	virtual bool Move(double time);
	virtual void Draw();
private:
	float visibility;
	float scale;
};
*/
#endif /* PARTICLE_HPP */
