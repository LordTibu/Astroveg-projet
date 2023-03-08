#pragma once
#include "ParticlePool.h"

/**
 * @class ParticuleEmitter
 * @param dx
 * @param dy
 * @param x
 * @param y
 * @param mousex
 * @param mousey
 * @param modelTexture
 * @param rotation
 * @param emitterPool 
 * @param emitterSize taille de l'emetteur
 * @param emissionRate le nombre de particule par seconde
 * @param lastEmission derniere emission
 * @brief La classe qui gére les particules
 */
class ParticleEmitter {
public:
	float dx, dy, x, y;
	int mousex, mousey;
	/**
	 * @brief Constructeur de la classe: initialise l'emetteur avec les parametres
	 * @param posx
	 * @param posy
	 * @param size
	 * @param rate
	 * @param renderer
	 * @return L'émetteur de particule initialiser avec les paramètres
	 */
	ParticleEmitter(float posx, float posy, int size, int rate, SDL_Renderer* renderer);

	~ParticleEmitter();
	
	/**
	 * @brief Emitte des particule chaque seconde
	 * @param quantity quantité de particule
	 */
	void generatePerSecond(int quantity);

	/**
	 * @brief Emitte des paticules par frame
	 * @param posx
	 * @param posy
	 */
	void emitTowardsPerFrame(int posx, int posy);

	/**
	 * @brief Emitte des particules statiques
	 */
	void emitStatic();
	/**
	 * @brief Update et dessin 
	 * @param renderer 
	 */
	void updateAndDrawEmitter(SDL_Renderer* renderer);
private:
	SDL_Texture* modelTexture;
	float rotation;
	ParticlePool* emitterPool = nullptr;
	int emitterSize;
	int emissionRate; 
	Uint32 lastEmission;
};