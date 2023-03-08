#include "Game.h"


Game::Game(const char* title, bool fullscreen)
{
	int flags = 0;
	window = nullptr;
	renderer = nullptr;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
				 SDL_WINDOWPOS_CENTERED,
				 SCREEN_WIDTH, SCREEN_HEIGHT, flags);
		if (window) {
			renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				isRunning = true;
			}
			else {
				std::cout << "failed to init renderer" << SDL_GetError() << std::endl;
			}
		}
		else { std::cout << "failed to init window" << SDL_GetError() << std::endl; }

	}
	else { std::cout << "Error in SDL init; Error: " << SDL_GetError() << std::endl; }

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error:"
			<< Mix_GetError() << std::endl;
		std::cout << "No sound !!!" << std::endl;
		//SDL_Quit();exit(1);
		withSound = false;
	}
	else withSound = true;

	if (TTF_Init() == -1)
	{
		std::cout << "failure to load SDL_TTF" << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	start = false;
}

Game::~Game()
{}

void Game::init()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	Menu = Texture::LoadTexture("data/Assets/Menu.png", renderer);
	if (start)
	{
		immortal = false;
		paused = false;
		Border = Texture::LoadTexture("data/Assets/border.png", renderer);
		DeathByLost = Texture::LoadTexture("data/Assets/DeathByLost.png", renderer);
		DeathByOxygen = Texture::LoadTexture("data/Assets/DeathByOxygen.png", renderer);
		translucentBlack = Texture::LoadTexture("data/Assets/translucentBlack.png", renderer);
		BACKGROUND = Texture::LoadTexture("data/Assets/background.png", renderer);
		scrBack = { 0, 0, 768, 768 };
		destBack = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		timeRect = { 0, 0, 20, 20 };
		levelMax = 25000;
		oxygenTankRect = { SCREEN_WIDTH - 72, 0, 32, 128 };
		planet = new Planet[5];
		victory = new Entity("data/Assets/victory.png", renderer, 1000, 200);
		oxygenTank = Texture::LoadTexture("data/Assets/oxygen.png", renderer);
		if (withSound)
		{
			Mix_Music* Music = Mix_LoadMUS("data/Assets/chill.mp3");
			Mix_PlayMusic(Music, -1);
		}
		astronaute = new Astronaut("data/Assets/astronaute.png", renderer, 200, 300);
		planet[0] = Planet("data/Assets/planet_test.png", renderer, 400, 300, 1, 6, 50, 0);
		planet[1] = Planet("data/Assets/planet_test1.png", renderer, 1000, 700, 1, 6, 100, 0);
		planet[2] = Planet("data/Assets/planet_test.png", renderer, 1000, 100, 1, 6, 100, 0);
		planet[3] = Planet("data/Assets/planet_test1.png", renderer, 220, 800, 1, 6, 200, 0);
		planet[4] = Planet("data/Assets/planet_test1.png", renderer, 200, 100, 1, 6, 100, 0);
		ActualTime = levelMax;
		loadTimer();
		levelStart = SDL_GetTicks();
	}
}

void Game::findGameState()
{
	if (astronaute->getDistTo(victory) < victory->getdestRect().w / 2 + astronaute->getdestRect().w / 3)
	{
		gameVictory();
	}
	if (!immortal && ActualTime <= 0)
	{
		gameDefeat(1);
	}
	if (astronaute->getx() == LEVEL_WIDTH || astronaute->getx() == 0 ||
		astronaute->gety() == LEVEL_HEIGHT || astronaute->gety() == 0)
	{
		gameDefeat(2);
	}
}

void Game::gameVictory()
{
	std::cout << "Victory!, Pog" << std::endl;
}

void Game::gameDefeat(int reason)
{
	int dim = 256;
	SDL_Rect temp = { (SCREEN_WIDTH - dim) / 2, (SCREEN_HEIGHT - dim) / 2, dim, dim };
	switch (reason)
	{
	case 1:
		std::cout << "Oxygen ran out, bummer" << std::endl;
		paused = true;
		dead = true;
		Mix_PauseMusic();
		SDL_RenderCopy(renderer, translucentBlack, NULL, &destBack);
		SDL_RenderCopy(renderer, DeathByOxygen, NULL, &temp);
		SDL_RenderPresent(renderer);
		break;
	case 2:
		std::cout << "Lost in space, F" << std::endl;
		dead = true;
		paused = true;
		Mix_PauseMusic();
		SDL_RenderCopy(renderer, translucentBlack, NULL, &destBack);
		SDL_RenderCopy(renderer, DeathByLost, NULL, &temp);
		SDL_RenderPresent(renderer);
	default:
		break;
	}
}

void Game::reset()
{
	astronaute->setx(200);
	astronaute->sety(200);
	astronaute->setdx(0);
	astronaute->setdy(0);
	astronaute->setOnSurf(false);
	astronaute->setJustLand(true);
	levelStart = SDL_GetTicks();
	ActualTime = levelMax;
}

void Game::loadTimer()
{
	TTF_Font* font = TTF_OpenFont("data/Assets/ocra.ttf", 20);
	if (!font) { std::cerr << "failure to load font" << std::endl; }

	SDL_Surface* textSurface;
	std::string temp;

	for (int i = 0; i < 10; i++)
	{
		ss.str(std::string());
		ss << i;
		temp = ss.str();
		//std::cout << temp << std::endl;
		textSurface = TTF_RenderText_Solid(font, temp.c_str(), {255, 0, 0, 255});
		if (!textSurface) { std::cerr << "failure to load surface" << std::endl; }

		number[i] = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (!number[i]) { std::cerr << "failure to load texture" << std::endl; }
		SDL_FreeSurface(textSurface);
	}
	TTF_CloseFont(font);
}

void Game::showTimer()
{
	int unit, dec;
	unit = (ActualTime / 1000) % 10;
	dec = (int)ActualTime / 10000;
	timeRect.x = 0;
	timeRect.y = 20;
	SDL_RenderCopy(renderer, number[dec], NULL, &timeRect);
	timeRect.x = 15;
	SDL_RenderCopy(renderer, number[unit], NULL, &timeRect);
	//number[dec]->display(0, 0, renderer);
	//number[unit]->display(8, 0, renderer);
}

void Game::makeRainbow()
{
	SDL_Rect temp;
	temp.x = LEVEL_WIDTH - 64;
	temp.y = 26;
	temp.w = 18;
	temp.h = 1;
	float step = 255 / 84;
	float time = - ((ActualTime - levelMax) / 1000) * 84 / (levelMax / 1000);
	for (float i = time; i < 84; i++)
	{
		temp.y = i + 26;
		SDL_SetRenderDrawColor(renderer,step * i, 255 - step * i, 0, 255);
		SDL_RenderFillRect(renderer, &temp);
	}
}

void Game::drawBorder(int camx, int camy)
{
	bool alternate = true;
	int stepx, stepy;
	SDL_Rect Vertical, Horizontal, index;
	Horizontal = { 0 - camx, 0 - camy, 48, 16 };
	Vertical = { 0 - camx, 0 - camy, 16, 48 };
	index = { 16 - camx, 0 - camy, 48, 16 };
	stepx = LEVEL_WIDTH / 48;
	stepy = LEVEL_HEIGHT / 16;

	for (int i = 0; i < stepx; i++)
	{
		Horizontal.x = i * 48 - camx;
		if (alternate)
		{
			SDL_RenderCopy(renderer, Border, &index, &Horizontal);
			index.x = 64;
			alternate = false;
		}
		else
		{
			SDL_RenderCopy(renderer, Border, &index, &Horizontal);
			index.x = 16;
			alternate = true;
		}
	}

	index = { 0, 111, 16, 48 };

	for (int i = 0; i < stepy; i++)
	{
		Vertical.y = 48 * i - camy;
		if (alternate)
		{
			SDL_RenderCopy(renderer, Border, &index, &Vertical);
			index.y = 64;
			alternate = false;
		}
		else
		{
			SDL_RenderCopy(renderer, Border, &index, &Vertical);
			index.y = 16;
			alternate = true;
		}
	}

	index = { 16, 112, 48, 16 };
	Horizontal.y = LEVEL_HEIGHT - 16 - camy;

	for (int i = 0; i < stepx; i++)
	{
		Horizontal.x = 48 * i - camx;
		if (alternate)
		{
			SDL_RenderCopy(renderer, Border, &index, &Horizontal);
			index.x = 64;
			alternate = false;
		}
		else
		{
			SDL_RenderCopy(renderer, Border, &index, &Horizontal);
			index.x = 16;
			alternate = true;
		}
	}

	index = { 112, 16, 16, 48 };
	Vertical.x = LEVEL_WIDTH - 16 - camx;

	for (int i = 0; i < stepy; i++)
	{
		Vertical.y = 48 * i - camy;
		if (alternate)
		{
			SDL_RenderCopy(renderer, Border, &index, &Vertical);
			index.y = 64;
			alternate = false;
		}
		else
		{
			SDL_RenderCopy(renderer, Border, &index, &Vertical);
			index.y = 16;
			alternate = true;
		}
	}
}


bool Game::running() { return isRunning; };

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				std::cout << "escape" << std::endl;
				isRunning = false;
				break;
			case SDLK_p:
				if (!start)
				{
					start = true;
					this->init();
				}
				break;
			case SDLK_SPACE:
				if (!paused)
				{
					paused = true;
					Mix_PauseMusic();
					pausedTime = SDL_GetTicks();
					SDL_RenderCopy(renderer, translucentBlack, NULL, &destBack);
					SDL_RenderPresent(renderer);
				}
				else
				{
					if (!dead)
					{
						paused = false;
						Mix_ResumeMusic();
						pausedTime = SDL_GetTicks() - pausedTime;
						levelStart += pausedTime;
					}
				}
				break;
			case SDLK_d:
				if (start) { astronaute->setClock(true); }
				break;
			case SDLK_q:
				if (start) { astronaute->setClock(false); }
				break;
			case SDLK_i:
				immortal = true;
				break;
			case SDLK_r:
				paused = false;
				Mix_ResumeMusic();
				reset();
				break;
			
			}

		case SDL_MOUSEMOTION:
			if (start)
			{
				astronaute->setmx(event.motion.x);
				astronaute->setmy(event.motion.y);
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (start)
			{
				if (astronaute->getOnSurf())
				{
					astronaute->jump(event.motion.x, event.motion.y, camera.x, camera.y);
					std::cout << "jump" << std::endl;
				}
				else
				{
					astronaute->prop(event.motion.x, event.motion.y, camera.x, camera.y);
					std::cout << "Al Infinito! Y mas Alla!" << std::endl;
				}
			}
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	if (start) {
		if (!paused)
		{
			camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			camera.x = (astronaute->getx() + astronaute->getdestRect().w / 2)
				- SCREEN_WIDTH / 2;
			camera.y = (astronaute->gety() + astronaute->getdestRect().h / 2)
				- SCREEN_HEIGHT / 2;
			if (camera.x < 0)
			{
				camera.x = 0;
			}
			if (camera.y < 0)
			{
				camera.y = 0;
			}
			if (camera.x > LEVEL_WIDTH - camera.w)
			{
				camera.x = LEVEL_WIDTH - camera.w;
			}
			if (camera.y > LEVEL_HEIGHT - camera.h)
			{
				camera.y = LEVEL_HEIGHT - camera.h;
			}
			for (int i = 0; i < 5; i++) {

				planet[i].attract(astronaute);
				astronaute->updateAstro(LEVEL_WIDTH,
					LEVEL_HEIGHT,
					&planet[i],
					planet[i].getRadius());
				planet[i].update(camera.x, camera.y,
					LEVEL_WIDTH, LEVEL_HEIGHT,
					planet[i].getRadius(), planet[i].getRadius());

				if (planet[i].getx() == astronaute->getPlanetx()
					&& planet[i].gety() == astronaute->getPlanety())
				{
					astronaute->run(&planet[i], planet[i].getRadius());
				}
			}
			astronaute->update(camera.x, camera.y, LEVEL_WIDTH, LEVEL_HEIGHT, 30, 30);
			victory->update(camera.x, camera.y, LEVEL_WIDTH, LEVEL_HEIGHT, 32, 32);
			astronaute->astroRainbow->x -= camera.x;
			astronaute->astroRainbow->y -= camera.y;
			astronaute->astroRainbow->emitStatic();
			ActualTime = levelMax - SDL_GetTicks() + levelStart;
			//std::cout << ActualTime % 10 << " ref" << std::endl;
			if (ActualTime <= 0) { ActualTime = 0; }
			ss.str(std::string());
			ss << ActualTime;
			findGameState();
		}
	}
}

void Game::render()
{
	if (start) {
		if (!paused)
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, BACKGROUND, &scrBack, &destBack);
			drawBorder(camera.x, camera.y);
			victory->render(renderer);
			astronaute->astroRainbow->updateAndDrawEmitter(renderer);
			astronaute->render(renderer);
			astronaute->drawlineAstro(renderer, camera.x, camera.y, camera.w, camera.h);
			for (int i = 0; i < 5; i++) {
				planet[i].render(renderer);
			}
			showTimer();
			makeRainbow();
			SDL_RenderCopy(renderer, oxygenTank, NULL, &oxygenTankRect);
			SDL_RenderPresent(renderer);
		}
	}
	else { 
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Menu, NULL, NULL);
	    SDL_RenderPresent(renderer);
	}
}

void Game::clean()
{
	delete astronaute;
	astronaute = nullptr;
	delete[] planet;
	planet = nullptr;
	while (Mix_Init(0)) { Mix_Quit(); }
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}