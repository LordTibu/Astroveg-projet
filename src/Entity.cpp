#include "Entity.h"


Entity::Entity() {
	Enttexture = NULL;
	rotAngle = 0;
	//rotCenter->x = 400;
	//rotCenter->y = 300;
	posx = 0;
	posy = 0;

	destRect = { 0, 0, 0, 0 };
	srcRect = { 0,0,0,0 };
}

Entity::Entity(const char* tex, SDL_Renderer* renderer, int x, int y) {
	rotAngle = 0;
	Enttexture = Texture::LoadTexture(tex, renderer);
	posx = x;
	posy = y;
	destRect = { 0, 0, 0, 0 };
	srcRect = { 0,0,0,0 };
}

void Entity::init(const char* tex, SDL_Renderer* ren, int x, int y)
{
	Enttexture = Texture::LoadTexture(tex, ren);
	posx = x;
	posy = y;
	destRect = { 0, 0, 0, 0 };
	srcRect = { 0,0,0,0 };
}

float Entity::getx() const {
	return posx;
}

float Entity::gety() const {
	return posy;
}

int Entity::getmx() const {
	return mx;
}

int Entity::getmy() const {
	return my;
}

void Entity::setx(float nx) { posx = nx; }
void Entity::sety(float ny) { posy = ny; }
void Entity::setmx(int x) { mx = x; }
void Entity::setmy(int y) { my = y; }
void Entity::addx(float nx) { posx += nx; }
void Entity::addy(float ny) { posy += ny; }


SDL_Rect Entity::getdestRect() const { return destRect; }

void Entity::update(int camX, int camY,int ScreenW, int ScreenH, float rectW, float rectH) {
	//srcRect = { 0,0,1000,1000 };
	destRect.x = posx - rectW / 2 - camX;
	destRect.y = posy - rectH / 2 - camY;
	destRect.w = rectW;
	destRect.h = rectH;
}

void Entity::render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, Enttexture, NULL, &destRect, rotAngle, NULL, SDL_FLIP_NONE);
}

Entity::~Entity() { }

