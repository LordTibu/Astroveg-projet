#include "Texture.h"

SDL_Texture* Texture::LoadTexture(const char* file, SDL_Renderer* ren) {

	SDL_Surface* tempSurface = IMG_Load(file);
	if (tempSurface == NULL) { printf("Unable to load suface"); }
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	if (tex == NULL) { printf("Unable to load texture"); }
	SDL_FreeSurface(tempSurface);
	//SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	return tex;
}