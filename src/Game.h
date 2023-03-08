#pragma once


#include "Planet.h" // Astronaut deja inclus dedans

/**
 * @class Game
 * @param start
 * @param whitSound
 * @param isRunning
 * @param LEVEL_HEIGHT
 * @param LEVEL_WIDTH
 * @param SCREEN_HEIGHT
 * @param SCREEN_WIDTH
 * @param number[9]
 * @param paused
 * @param gameOver
 * @param levelStart
 * @param levelMax
 * @param ActualTime
 * @param pausedTime
 * @param timer
 * @param DeathByOxygen
 * @param translucentBlack
 * @param BACKGROUND
 * @param menu
 * @param oxygenTank
 * @param scrBack
 * @param destBack
 * @param timeRect
 * @param window
 * @param renderer
 * @param camera
 * @param oxygenTankRect
 * @param victory
 * @brief La classe qui gére le jeu
 */
class Game
{
public:
	SDL_Texture* number[10];
	bool paused = false;
	bool gameOver = false;
	Uint32 levelStart;
	int levelMax;
	int ActualTime = 10;
	int pausedTime = 0;
	std::stringstream ss;
	Text* timer;
	SDL_Texture* Border;
	SDL_Texture* DeathByLost;
	SDL_Texture* DeathByOxygen;
	SDL_Texture* translucentBlack;
	SDL_Texture* BACKGROUND;
	SDL_Texture* Menu;
	SDL_Texture* oxygenTank;
	SDL_Rect scrBack, destBack, timeRect;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect camera, oxygenTankRect;
	Entity* victory;
	/**
	 * @brief Constructeur de la classe: initialise Game avec les parametres
	 * @param title
	 * @param fullscreen
	 * @return Un Game initialiser avec les paramètres
	 */
	Game(const char* title, bool fullscreen);

	/**
	 * @brief Destructeur de la classe
	 */
	~Game();

	/**
	 * @brief Initialise la classe
	 */
	void init();

	/**
	 * @brief Cherche l'etat du jeu
	 */
	void findGameState();

	/**
	 * @brief Victory 
	 */
	void gameVictory();

	/**
	 * @brief Defeat
	 * @param reason raison de la defaite
	 */
	void gameDefeat(int reason);

	/**
	 * @brief Reinitialiser le jeu
	 */
	void reset();

	/**
	 * @brief Charger le timer
	 */
	void loadTimer();

	/**
	 * @brief Render le border du niveau
	 */
	void drawBorder(int camx, int camy);

	/**
	 * @brief Affichage du timer
	 */
	void showTimer();

	/**
	 * @brief Piscine de particule rainbow
	 */
	void makeRainbow();

	/**
	 * @brief Gestion d'évenements
	 */
	void handleEvents();

	/**
	 * @brief Update
	 */
	void update();

	/**
	 * @brief Returne true si le jeu fonctionne
	 * @return boolean
	 */
	bool running();

	/**
	 * @brief Render
	 */
	void render();

	/**
	 * @brief Fais le ménage
	 */
	void clean();

private:
	Astronaut* astronaute;
	Planet* planet = nullptr;
	bool start, immortal;
	bool dead = false;
	bool withSound = false;
	bool isRunning = false;
	int LEVEL_HEIGHT = 860;
	int LEVEL_WIDTH = 1530;

	int SCREEN_HEIGHT = 860;
	int SCREEN_WIDTH = 1530;

};