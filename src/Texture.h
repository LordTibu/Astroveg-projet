#pragma once

#include "Text.h"

/**
 * @class Texture
 * @brief La classe qui gére les texture 
 */
class Texture {

public:
	/**
	 * @brief Charge une texture a partir d'une image
	 * @param file nom du fichier image
	 * @param ren le renderer
	 * @return Une texture
	 */
	static SDL_Texture* LoadTexture(const char* file, SDL_Renderer* ren);

};