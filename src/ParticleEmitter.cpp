#include "ParticleEmitter.h"

#define PI 3.14159265

ParticleEmitter::ParticleEmitter(float posx, float posy, int size, int emission, SDL_Renderer* renderer)
{
	x = posx;
	y = posy;
	lastEmission = 0;
	mousex = 0;
	mousey = 0;
	dx = dy = 0;
	emitterSize = size;
	emissionRate = emission;
	rotation = 90;
	modelTexture = Texture::LoadTexture("data/Assets/RainbowTrail.png", renderer);
	emitterPool = new ParticlePool(emitterSize);
}

ParticleEmitter::~ParticleEmitter()
{
	delete emitterPool;
	emitterPool = nullptr;
}

void ParticleEmitter::generatePerSecond(int quantity)
{
	float milliseconds = 1000 / quantity;
	if (SDL_GetTicks() - lastEmission >= milliseconds)
	{
		/*for (int i = 0; i < quantity; i++)
		{
			emitterPool->generate(x, y, 2, 2);
		}*/
		emitterPool->generate(x, y, 2, 2, rotation);
		lastEmission = SDL_GetTicks();
	}
}

void ParticleEmitter::emitTowardsPerFrame(int posx, int posy)
{
	float distx = posx - x;
	float disty = posy - y;
	float radians;
	if (distx == 0)
	{
		if (disty > 0) { radians = PI / 2; }
		else { radians = -PI / 2; }
	}
	if (disty == 0)
	{
		if (distx > 0) { radians = 0; }
		else { radians = PI; }
	}
	else
	{
		radians = atan2(disty, distx);
	}
	emitterPool->generate(x, y, cos(radians)*2, sin(radians)*2, rotation);
}

void ParticleEmitter::emitStatic()
{
	emitterPool->generate(x, y, 0, 0, rotation);
}

void ParticleEmitter::updateAndDrawEmitter(SDL_Renderer* renderer)
{
	x += dx;
	y += dy;
	if (dx == 0)
	{
		if (dy > 0) { rotation = -90; }
		else { rotation = 90; }
	}
	if (dy == 0)
	{
		if (dx > 0) { rotation = 0; }
		else { rotation = 180; }
	}
	else
	{
		rotation = atan2(dy, dx) * 180 / PI;
	}
	dx = dx * 0.4;
	dy = dy * 0.4;
	emitterPool->update(renderer, modelTexture);
}