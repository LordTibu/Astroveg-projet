#pragma once

#include "Astronaut.h"

/**
 * @class Planet
 * @param radius rayon du planete
 * @param gravRad rayon d'attraction
 * @param G force de gravite
 * @param mass masse de la planete
 * @param Enttexture texture de l'entité
 * @param rotCenter centre de rotation
 * @param srcRect source rectangle
 * @param destRect destinqtion rectangle
 * @param rotAngle angle de rotation
 * @brief La classe qui gére l'entité
 */
class Planet : public Entity
{
public:
	/**
	 * @brief Constructeur de la classe: initialise planet avec les parametres
	 * @param tex texture de l'entité
	 * @param ren le renderer
	 * @param x position x
	 * @param y position y
	 * @return Une Planet initialiser avec les paramètres
	 */
	Planet(const char* tex, SDL_Renderer* ren, int x, int y);

	Planet();

	void initP(const char* tex, SDL_Renderer* ren, int x, int y,
		int nG, int nMass, int nRadius, int nGravRad);

	/**
	 * @brief Constructeur de la classe: initialise astronaut avec les parametres
	 * @param tex texture de l'entité
	 * @param ren le renderer
	 * @param x position x
	 * @param y position y
	 * @param nG force de gravite
	 * @param nMass masse de la planete
	 * @param nradius rayon de la planete
	 * @ngravrad rayon de l'attraction
	 * @return Une Planet initialiser avec les paramètres
	 */
	Planet(const char* tex, SDL_Renderer* ren, int x, int y, int nG, int nMass, int nradius, int ngravrad);

	/**
	 * @brief Destructeur de la classe
	 */
	~Planet();

	/**
	 * @brief Accesseur : récupère la force G du planete
	 * @return La force G
	 */
	int getG() const;

	/**
	 * @brief Accesseur : récupère la masse du planete
	 * @return La masse mass
	 */
	int getMass() const;

	/**
	 * @brief Accesseur : récupère le rayon du planete
	 * @return Le rayon radius
	 */
	float getRadius() const;

	/**
	 * @brief Accesseur : récupère le rayon d'attraction du planete
	 * @return Le rayon GravRad
	 */
	float getGravRad() const;

	/**
	 * @brief Attraction de l'astronaut 
	 * @param mover Astronaut qui va être attiré par la planete 
	 */
	void attract(Astronaut* mover);

private:
	float radius, gravRad;
	int G, mass;
};