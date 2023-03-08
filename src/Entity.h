#pragma once

#include "ParticleEmitter.h"
#include <math.h>

/**
 * @class Entity
 * @param posx position x
 * @param posy position y
 * @param mx position de la souris x
 * @param my position de la souris y
 * @param Enttexture texture de l'entit�
 * @param rotCenter centre de rotation
 * @param srcRect source rectangle
 * @param destRect destinqtion rectangle
 * @param rotAngle angle de rotation
 * @brief La classe qui g�re l'entit�
 */
class Entity
{
private:
	float posx, posy;
	int mx, my;

	SDL_Texture* Enttexture;
	SDL_Point* rotCenter;
	SDL_Rect srcRect, destRect;


public:
	float rotAngle;
	/**
	 * @brief Constructeur par d�faut de la classe: initialise l'entit� a 0
	 * @return Entity 
	 */
	Entity();

	/**
	 * @brief Constructeur de la classe: initialise posx, posy, Enttexture, destRect, srcRect avec les parametres
	 * @param tex texture de l'entit�
	 * @param ren le renderer 
	 * @param x position x
	 * @param y position y
	 * @return Une Entity initialiser avec les param�tres
	 */
	Entity(const char* tex, SDL_Renderer* ren, int x, int y);

	void init(const char* tex, SDL_Renderer* ren, int x, int y);

	/**
	 * @brief Destructeur de la classe
	 */
	~Entity();

	/**
	 * @brief Accesseur : r�cup�re la position x de l'entit�
	 * @return La position x 
	 */
	float getx() const;

	/**
	 * @brief Accesseur : r�cup�re la position y de l'entit�
	 * @return La position y
	 */
	float gety() const;

	/**
	 * @brief Accesseur : r�cup�re la position x de la souris
	 * @return La position mx
	 */
	int getmx()const;

	/**
	 * @brief Accesseur : r�cup�re la position y de la souris
	 * @return La position my
	 */
	int getmy()const;

	/**
	 * @brief Mutateur : modifie la position x de l'entit�
	 * @param nx position x
	 */
	void setx(float nx);
	
	/**
	 * @brief Mutateur : modifie la position y de l'entit�
	 * @param ny position y
	 */
	void sety(float ny);

	/**
	 * @brief Mutateur : modifie la position x de la souris
	 * @param x position x
	 */
	void setmx(int x);

	/**
	 * @brief Mutateur : modifie la position y de la souris
	 * @param y position y
	 */
	void setmy(int y);

	/**
	 * @brief Additioneur : ajoute nx a la position x de l'entit�
	 * @param nx position nx
	 */
	void addx(float nx);

	/**
	 * @brief Additioneur : ajoute ny a la position y de l'entit�
	 * @param ny position ny
	 */
	void addy(float ny);

	/**
	 * @brief Accesseur : r�cup�re le rectangle de destination de l'entit� 
	 * @return Le rectangle de destination
	 */
	SDL_Rect getdestRect() const;

	/**
	 * @brief Update
	 * @param camX position x de la camera
	 * @param camY position y de la camera
	 * @param ScreenW Longueur de l'�cran
	 * @param ScreenH Hauteur de l'�cran
	 * @param rectW Longueur de l'entit�
	 * @param rectH Hauteur de l'entit�
	 */
	void update(int camX, int camY, int ScreenW, int ScreenH, float rectW, float rectH);

	/**
	 * @brief Render
	 * @param renderer 
	 */
	void render(SDL_Renderer* renderer);
};