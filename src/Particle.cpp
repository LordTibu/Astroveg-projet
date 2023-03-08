#include "Particle.h"

void Particle::init(float posx, float posy, float velx, float vely, float rotation)
{
	partRect.x = posx;
	partRect.y = posy;
	partRect.h = 16;
	partRect.w = 16;
	x = posx;
	y = posy;
	if (velx != 0) { float rangex = (rand() % 201 / (float)100) - 1; dx = velx + rangex; }
	else { dx = 0; }
	if (vely != 0) { float rangey = (rand() % 201 / (float)100) - 1; dy = vely + rangey; }
	else { dy = 0; }
	angle = rotation;

	lifeTime = 90;
	decal = 255 / lifeTime;
	alive = true;
}

Particle* Particle::getNext()
{
	return next;
}

void Particle::setNext(Particle* part)
{
	next = part;
}

void Particle::update()
{
	x += dx;
	y += dy;
	partRect.x = x;
	partRect.y = y;
	//std::cout << dy << std::endl;

	lifeTime--;
	
	if (lifeTime <= 0) { alive = false; }
}
bool Particle::isAlive()
{
	return alive;
}

void Particle::draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, decal*lifeTime);
	SDL_RenderFillRect(renderer, &partRect);*/
	SDL_SetTextureAlphaMod(texture, decal * lifeTime);
	SDL_RenderCopyEx(renderer, texture, NULL, &partRect, angle + 90, NULL, SDL_FLIP_NONE);
}