#include "Astronaut.h"
#include <iostream>

#define PI 3.14159265

Astronaut::Astronaut(const char* tex, SDL_Renderer* ren, int x, int y)
	: Entity(tex, ren, x, y), dx(0.0), dy(0.0), radians(0.0f), propCharges(0),
	  onSurface(false), justLanded(true), astroRainbow(new ParticleEmitter(x, y, 600, 1, ren)) {};


Astronaut::~Astronaut()
{
	delete astroRainbow;
	astroRainbow = nullptr;
}

void Astronaut::setdx(float ndx) { dx = ndx; };
void Astronaut::setdy(float ndy) { dy = ndy; };
void Astronaut::add_dx(float ndx) { dx += ndx; };
void Astronaut::add_dy(float ndy) { dy += ndy; };

float Astronaut::getdx() const { return dx; };
float Astronaut::getdy() const { return dy; };
void Astronaut::setProp(int prop) { propCharges = prop; };
int Astronaut::getProp() const { return propCharges; };
int Astronaut::getMass() const { return mass; }

void Astronaut::setOnSurf(bool b) { onSurface = b; };
bool Astronaut::getOnSurf() const { return onSurface; };

void Astronaut::setClock(bool b) { clockwise = b; }
float Astronaut::getPlanetx() { return planetx; }
float Astronaut::getPlanety() { return planety; }
void Astronaut::setJustLand(bool b) { justLanded = b; }


float Astronaut::getDistTo(Entity* obj)
{
	float nx, ny;
	nx = (this->getx() - obj->getx());
	ny = (this->gety() - obj->gety());
	return sqrt(nx * nx + ny * ny);
}

void Astronaut::direction(int xx, int yy) {
	dx = xx - this->getx();
	dy = yy - this->gety();
}

void Astronaut::collision(int wallx, int wally, Entity* planet, float radius) {
	if (this->gety() < 0) { this->sety(0); }
	if (this->gety() > wally - 10) { this->sety(wally - 10); }
	if (this->getx() < 0) { this->setx(0); }
	if (this->getx() > wallx - 10) { this->setx(wallx - 10); }

	float dist = this->getDistTo(planet);
	float idealDist = radius / 2 + this->getdestRect().h / 2;

	if (dist <= idealDist)
	{
		onSurface = true;
		planetx = planet->getx();
		planety = planet->gety();
		dx = 0;
		dy = 0;
		if (dist < idealDist)
		{
			float nx = (this->getx() - planet->getx()) / dist;
			float ny = (this->gety() - planet->gety()) / dist;
			this->addx(nx * idealDist - (this->getx() - planet->getx()));
			this->addy(ny * idealDist - (this->gety() - planet->gety()));
		}
	}
}

void Astronaut::run(Entity* planet, float radius) {
	if (onSurface)
	{
		if (justLanded)		// initialisation de l'angle de rentree sur la planete
		{
			float distx = this->getx() - planetx;
			float disty = this->gety() - planety;
			if (distx == 0)
			{
				if (disty > 0) { radians = PI / 2; }
				else { radians = -PI / 2; }
				justLanded = false;
			}
			if (disty == 0)
			{
				if (distx > 0) { radians = 0; }
				else { radians = PI; }
				justLanded = false;
			}
			else
			{
				radians = atan2(this->gety() - planet->gety(), distx);
				justLanded = false;
			}

		}
		if (clockwise)
		{
			this->rotAngle = radians * 180 / PI + 90;
			setx(planetx + cos(radians) * ((radius / 2) +
				((float)this->getdestRect().h / 2)));
			sety(planety + sin(radians) * ((radius / 2) +
				((float)this->getdestRect().h / 2)));
			radians += runSpeed;
		}
		else
		{
			this->rotAngle = radians * 180 / PI + 90;
			setx(planetx + cos(radians) * ((radius / 2) + 
				((float)this->getdestRect().h / 2)));
			sety(planety + sin(radians) * ((radius / 2) + 
				((float)this->getdestRect().h / 2)));
			radians -= runSpeed;
		}
	}
}

void Astronaut::jump(float mousex, float mousey, int camx, int camy)
{
	float x, y;
	x = mousex - this->getx() + camx;
	std::cout << x << std::endl;
	y = mousey - this->gety() + camy;;
	if (x > 12) { x = 12; }
	if (x < -12) { x = -12; }
	if (y > 12) { y = 12; }
	if (y < -12) { y = -12; }
	dx += x / 45;
	dy += y / 45;
	Mix_PlayChannel(0, jumpSFX, 0);
	onSurface = false;
	justLanded = true;
}

void Astronaut::prop(float mousex, float mousey, int camx, int camy)
{
	float x, y;
	x = mousex - (this->getx() - camx);
	y = mousey - (this->gety() - camy);
	if (x > 12) { x = 12; }
	if (x < -12) { x = -12; }
	if (y > 12) { y = 12; }
	if (y < -12) { y = -12; }
	dx -= x / 36;
	dy -= y / 36;
	std::cout << mousex << mousey << std::endl;
}

void Astronaut::updateAstro(int wallx, int wally, Entity* planet, float radius)
{

	this->addx(dx);
	this->addy(dy);
	astroRainbow->x = this->getx() - 16;
	astroRainbow->y = this->gety() - 16;
	astroRainbow->dx = dx;
	astroRainbow->dy = dy;
	this->collision(wallx, wally, planet, radius);
}

void Astronaut::drawlineAstro(SDL_Renderer* ren, int camx, int camy,
							  int screenw, int screenh){
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	if (onSurface) {
		SDL_RenderDrawLine(ren, this->getx() - camx, this->gety() - camy,
						   this->getmx(), this->getmy());
	}
	else {
		SDL_RenderDrawLine(ren, this->getx() - camx, this->gety() - camy,
							2 * (this->getx() - camx) - this->getmx(),
							2 * (this->gety() - camy) - this->getmy());
		
	}
}

