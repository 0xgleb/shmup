#include "../include/body.hpp"
#include <SDL2/SDL.h>
#include <cassert>

Body::Body(int x, int y, int selX, int selY, int selW, int selH):_coord(x,y) {
	this -> _destination = new SDL_Rect;
	this -> _selection = new SDL_Rect;

	this -> _selection -> x = selX;
	this -> _selection -> y = selY;
	this -> _selection -> w = this -> _destination -> w = selW;
	this -> _selection -> h = this -> _destination -> h = selH;

	this -> _destination -> x = x;
	this -> _destination -> y = y;
}

Body::~Body() {
	delete this -> _destination;
	delete this -> _selection;
	SDL_DestroyTexture(this -> _texture);
}

SDL_Texture* Body::texture() {
	return this -> _texture;
}
SDL_Texture* Body::texture(SDL_Texture *newTexture) {
	return this -> _texture = newTexture;
}

SDL_Rect* Body::selection() {
	return this -> _selection;
}

SDL_Rect* Body::destination() {
	this -> _destination -> x = this -> _coord.x();
	this -> _destination -> y = this -> _coord.y();
	return this -> _destination;
}

Vector& Body::coord() {
	return this -> _coord;
}
Vector& Body::coord(Vector newVector) {
	this -> _coord = newVector;
	return this -> _coord;
}

Vector& Body::velocity() {
	return this -> _velocity;
}
Vector& Body::velocity(Vector newVector) {
	this -> _velocity = newVector;
	return this -> _velocity;
}

Body* Body::shoot(int selX, int selY, int selW, int selH) {
	Body *bullet = new Body(this -> _coord.x() + this -> _destination -> w / 2, 
			this -> _coord.y(), selX, selY, selW, selH);
	bullet -> velocity().x(this -> velocity().x());
	bullet -> velocity().y(this -> velocity().y() - 20);
	return bullet;
}
