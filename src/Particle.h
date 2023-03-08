#pragma once
#include "Texture.h"

/**
 * @class Particule
 * @param angle
 * @param decal
 * @param alive
 * @param lifeTime
 * @param partRect
 * @param x
 * @param y
 * @param dx
 * @param dy
 * @param next
 * @brief La classe qui gére les particules
 */
class Particle {
public:

	/**
	 * @brief Initialise la particule avec les parametres
	 * @param posx
	 * @param posy
	 * @param velx
	 * @param vely
	 * @param rotation
	 */
	void init(float posx, float posy, float velx, float vely, float rotation);

	/**
	 * @brief Update
	 */
	void update();

	/**
	 * @brief Dessine la particule
	 * @param renderer Le render
	 * @param originalTexture
	 */
	void draw(SDL_Renderer* renderer, SDL_Texture* originalTexture);

	/**
	 * @brief Accesseur : récupère la particule suivante
	 * @return La particule next
	 */
	Particle* getNext();

	/**
	 * @brief Mutateur : modifie la particule suivante
	 * @param part Particule suivante
	 */
	void setNext(Particle* part);

	/**
	 * @brief Returne l'etat de la particule
	 * @return boolean alive
	 */
	bool isAlive();

private:
	float angle;
	float decal = 255;
	bool alive = true;
	int lifeTime = 300;
	SDL_Rect partRect;
	float x, y, dx, dy;
	Particle* next;
};