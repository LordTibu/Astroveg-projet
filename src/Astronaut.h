#pragma once
#include"Entity.h"


/**
 * @class Astronaut
 * @param dx direction x
 * @param dy direction y
 * @param planetx 
 * @param planety
 * @param radians 
 * @param onSurface detection de la surface
 * @param justLanded detection de l'atterrissage 
 * @param clockwise direction du mouvement du personnage (dans le sens des aiguilles d'une montre)
 * @param propCharges charges du propulseur
 * @param mass masse de l'astronaut
 * @param runspeed vitesse de l'astronaut quand il cours
 * @param jumpSFX son du saut
 * @param astroRainbow emeteur de particule
 * @brief La sub-classe qui gére l'astronaut
 */
class Astronaut : public Entity {
public:

	/**
	 * @brief Constructeur de la classe: initialise astronaut avec les parametres
	 * @param tex texture de l'entité
	 * @param ren le renderer
	 * @param x position x
	 * @param y position y
	 * @return Un Astronaut initialiser avec les paramètres
	 */
	Astronaut(const char* tex, SDL_Renderer* ren, int x, int y);

	/**
	 * @brief Destructeur de la classe
	 */
	~Astronaut();

	ParticleEmitter* astroRainbow;

	/**
	 * @brief Mutateur : modifie la direction x de l'entité
	 * @param ndx direction x
	 */
	void setdx(float ndx);

	/**
	 * @brief Mutateur : modifie la direction y de l'entité
	 * @param ndy direction y
	 */
	void setdy(float ndy);

	/**
	 * @brief Mutateur : modifie bool onSurface de l'entité
	 * @param b booelan 
	 */
	void setOnSurf(bool b);

	/**
	 * @brief Mutateur : modifie la quantité de propulseur de l'entité
	 * @param prop quantité de propulseur 
	 */
	void setProp(int prop);

	/**
	 * @brief Mutateur : modifie bool clockwise de l'entité
	 * @param b boolean
	 */
	void setClock(bool b);

	/**
	 * @brief Mutateur : modifie bool justLanded l'entité
	 * @param b boolean
	 */
	void setJustLand(bool b);

	/**
	 * @brief Additioneur : ajoute une vitesse a dx de l'entité
	 * @param ndx vitesse ndx
	 */
	void add_dx(float ndx); 

	/**
	 * @brief Additioneur : ajoute une vitesse a dy de l'entité
	 * @param ndy vitesse ndy
	 */
	void add_dy(float ndy);

	/**
	 * @brief Accesseur : récupère la direction x de l'entité
	 * @return La direction x
	 */
	float getdx() const;

	/**
	 * @brief Accesseur : récupère la direction y de l'entité
	 * @return La direction y
	 */
	float getdy() const;

	/**
	 * @brief Accesseur : récupère la quantité de=u propulseur de l'entité
	 * @return La quantité du propulseur
	 */
	int getProp() const;

	/**
	 * @brief Accesseur : récupère bool onSurface de l'entité
	 * @return Le boolean onSurface
	 */
	bool getOnSurf() const;

	/**
	 * @brief Accesseur : récupère la masse de l'entité
	 * @return La masse mass
	 */
	int getMass() const;
	
	/**
	 * @brief Accesseur : récupère la planete x
	 * @return Planetx
	 */
	float getPlanetx();

	/**
	 * @brief Accesseur : récupère la planete y
	 * @return Planety
	 */
	float getPlanety();
	
	/**
	 * @brief Update
	 * @param wallx taille x du level
	 * @param wally taille y du level
	 * @param planet une planete
	 * @param radius rayon 
	 */
	void updateAstro(int wallx, int wally, Entity* planet, float radius);

	/**
	 * @brief Dessine la ligne de direction de l'astronaute
	 * @param ren render
	 * @param camx position x de la camera
	 * @param camy position y de la camera
	 * @param Screenw largeur de l'ecran
	 * @param screenh hauteur de l'ecran
	 */
	void drawlineAstro(SDL_Renderer* ren,int camx,int camy, int screenw, int screenh);

	/**
	 * @brief Distance entre l'astronaut et une entité
	 * @param obj Entity
	 * @return la distance entre l'astronaut et l'objet
	 */
	float getDistTo(Entity* obj);

	/**
	 * @brief Mutateur : modifie la direction selon la position xx, yy et la position de l'astronaut
	 * @param xx position xx
	 * @param yy position yy
	 */
	void direction(int xx, int yy);

	/**
	 * @brief L'astronaut cours autour d'une planete dont on connait le rayon
	 * @param planet Planete où l'astronaut se trouve
	 * @param radius Rayon de la planete
	 */
	void run(Entity* planet, float radius); 
	
	/**
	 * @brief L'astronaut saut
	 * @param mousex position x de la souris
	 * @param mousey position y de la souris
	 * @param camx position x de la camera
	 * @param camy position y de la camera
	 */
	void jump(float mousex, float mousey, int camx, int camy);

	/**
	 * @brief L'astronaut utilise le propulseur
	 * @param mousex position x de la souris
	 * @param mousey position y de la souris
	 * @param camx position x de la camera
	 * @param camy position y de la camera
	 */
	void prop(float mousex, float mousey, int camx, int camy);

	/**
	 * @brief Collision entre l'astronaut et les planetes
	 * @param wallx taille x du level
	 * @param wally taille y du level
	 * @param planete La planete pour les collisions
	 * @param radius rayon de la planete
	 */
	void collision(int wallx, int wally, Entity* planete, float radius);

private:
	float dx, dy;
	float planetx = 0;
	float planety = 0;
	double radians;
	bool onSurface, justLanded;
	bool clockwise = true;
	int propCharges;
	int mass = 1;
	double runSpeed = 0.05;
	Mix_Chunk* jumpSFX = Mix_LoadWAV("data/Assets/jump.mp3");

};
