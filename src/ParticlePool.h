#pragma once
#include <assert.h>
#include "Particle.h"

/**
 * @class ParticulePool
 * @param pool 
 * @param firstAvailable premier particule disponible
 * @param poolSize taille de la piscine
 * @brief La classe qui gére la piscine des particules
 */
class ParticlePool
{
public:

	/**
	 * @brief Constructeur de la classe: initialise la piscine avec les parametres
	 * @param size taille de la piscine
	 * @return La piscine des particules initialiser avec les paramètres
	 */
	ParticlePool(int size);

	~ParticlePool();

	/**
	 * @brief Update
	 * @param renderer
	 * @param originalTexture
	 * @return boolean
	 */
	bool update(SDL_Renderer* renderer, SDL_Texture* originalTexture);

	/**
	 * @brief Generateur de la piscine
	 * @param posX
	 * @param posY
	 * @param speedx
	 * @param speedy
	 * @param rot
	 */
	void generate(int posX, int posY, float speedx, float speedy, float rot);

private:
	Particle* pool = nullptr;
	Particle* firstAvailable = nullptr;
	int poolSize = 0;
};

