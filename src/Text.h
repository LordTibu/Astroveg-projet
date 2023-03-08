#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include <string>
#include <sstream>
#include <iostream>

/**
 * @class Text
 * @param texto texte a afficher
 * @param font la police du texte
 * @param textRect la taille du texte
 * @brief La classe qui gére le texte
 */
class Text
{
public:
	Text(const std::string& fontPath, int size, const std::string& message, const SDL_Color& color, SDL_Renderer* renderer);

	void display(int x, int y, SDL_Renderer* renderer);
	void updateTexto(const std::string newMessage, const SDL_Color& color, SDL_Renderer* renderer);

	SDL_Texture* update(const std::string newMessage, const SDL_Color& color, SDL_Renderer* renderer);
	SDL_Texture* loadFont(const std::string& fontPath, int size, const std::string& message, const SDL_Color& color, SDL_Renderer* renderer);

	TTF_Font* getFont();
private:
	SDL_Texture* texto;
	TTF_Font* font;
	SDL_Rect textRect;
};