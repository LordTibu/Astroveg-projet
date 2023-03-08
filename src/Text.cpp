#include "Text.h"

Text::Text(const std::string &fontPath, int size, const std::string& message, const SDL_Color& color, SDL_Renderer* renderer)
{
	//textRect.w = textRect.h = size;
	texto = loadFont(fontPath, size, message, color, renderer);
	SDL_QueryTexture(texto, NULL, NULL, &textRect.w, &textRect.h);
}

void Text::display(int x, int y, SDL_Renderer* renderer)
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, texto, NULL, &textRect);
}

void Text::updateTexto(const std::string newMessage, const SDL_Color& color, SDL_Renderer* renderer)
{
	SDL_DestroyTexture(texto);
	texto = update(newMessage, color, renderer);
	if (!texto) { std::cerr << "failure to load texto" << std::endl; }
}

SDL_Texture* Text::update(const std::string newMessage, const SDL_Color& color, SDL_Renderer* renderer)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, newMessage.c_str(), color);
	if (!textSurface) { std::cerr << "failure to load surface" << std::endl; }

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!tex) { std::cerr << "failure to load texture" << std::endl; }
	SDL_FreeSurface(textSurface);
	return tex;
}

SDL_Texture* Text::loadFont(const std::string &fontPath, int size, const std::string &message, const SDL_Color& color, SDL_Renderer* renderer)
{
	font = TTF_OpenFont(fontPath.c_str(), size);
	if (!font) { std::cerr << "failure to load font" << std::endl; }

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!textSurface) { std::cerr << "failure to load surface" << std::endl; }

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!tex) { std::cerr << "failure to load texture" << std::endl; }
	SDL_FreeSurface(textSurface);
	return tex;
}

TTF_Font* Text::getFont()
{
	return font;
}