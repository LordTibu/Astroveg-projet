#include "ParticlePool.h"

ParticlePool::ParticlePool(int size)
{
	poolSize = size;
	pool = new Particle[poolSize];
	firstAvailable = &pool[0];
	for (int i = 0; i < poolSize - 1; i++)
	{
		pool[i].setNext(&pool[i + 1]);
	}
	pool[poolSize - 1].setNext(nullptr);
}

ParticlePool::~ParticlePool()
{
	delete[] pool;
	pool = nullptr;
}

bool ParticlePool::update(SDL_Renderer* renderer, SDL_Texture* texture)
{
	bool result = false;

	for(int i = 0; i < poolSize; i++)
	{
		if(pool[i].isAlive())
		{
			pool[i].update();
			pool[i].draw(renderer, texture);
			result = true;
		}
		else
		{
			pool[i].setNext(firstAvailable);
			firstAvailable = &pool[i];
		}
	}
	return result;
}

void ParticlePool::generate(int posX, int posY, float speedx, float speedy, float rot)
{
	assert(firstAvailable != nullptr);

	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->getNext();

	newParticle->init(posX, posY, speedx, speedy, rot);
}
