#include "Planet.h"

Planet::Planet()
{
}

Planet::Planet(const char* tex, SDL_Renderer* ren, int x, int y)
	: Entity(tex, ren, x, y), G(0), mass(0), radius(0), gravRad(0) {};

Planet::Planet(const char* tex, SDL_Renderer* ren, int x, int y,
			   int nG, int nMass, int nRadius, int nGravRad)
	: Entity(tex, ren, x, y), G(nG), mass(nMass),
	  radius(nRadius), gravRad(nGravRad) {};

void Planet::initP(const char* tex, SDL_Renderer* ren, int x, int y,
	int nG, int nMass, int nRadius, int nGravRad)
{
	this->init(tex, ren, x, y);
	G = nG;
	mass = nMass;
	radius = nRadius;
	gravRad = nGravRad;
}

Planet::~Planet()
{
}

int Planet::getG() const { return G; }
int Planet::getMass() const { return mass; }
float Planet::getRadius() const { return radius; }
float Planet::getGravRad() const { return gravRad; }

void Planet::attract(Astronaut* mover)
{
	if (!mover->getOnSurf()) {
		float d = mover->getDistTo(this);
		float nx = (this->getx() - mover->getx()) / d;
		float ny = (this->gety() - mover->gety()) / d;
		if (d < 2) { d = 2; }
		if (d > 75) { d = 75; }
		float strenght = (G * mass * mover->getMass()) / (d * d);
		mover->add_dx(nx * strenght);
		mover->add_dy(ny * strenght);
		}
}