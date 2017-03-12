#include "../include/body.hpp"
#include <SDL2/SDL.h>
#include <cassert>

Body::Body(int x, int y, int w, int h):_coord(x,y) {
	this->_destination = new SDL_Rect;

	this->_destination->x = x;
	this->_destination->y = y;
	this->_destination->w = w;
	this->_destination->h = h;
}

Body::~Body() {
	delete this->_destination;
}

SDL_Rect* Body::destination() {
	this->_destination->x = this->_coord.x();
	this->_destination->y = this->_coord.y();
	return this->_destination;
}

Vector& Body::coord() {
	return this->_coord;
}
Vector& Body::coord(Vector& newVector) {
	this->_coord = newVector;
	return this->_coord;
}

Vector& Body::velocity() {
	return this->_velocity;
}
Vector& Body::velocity(Vector& newVector) {
	this->_velocity = newVector;
	return this->_velocity;
}
