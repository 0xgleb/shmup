#include "../include/ship.hpp"
#include "../include/list.hpp"
#include <iostream>

Ship::Ship(int x, int y, int selX, int selY, int selW, int selH):Body(x,y,selW,selH) {
	this->_bullets = new List<Body>;
	
	this->_health = 100;

	this->_selection = new SDL_Rect;

	this->_selection->x = selX;
	this->_selection->y = selY;
	this->_selection->w = this->_destination->w = selW;
	this->_selection->h = this->_destination->h = selH;
}

Ship::~Ship() {
	SDL_DestroyTexture(this->_texture);
}

int Ship::health() {
	return this->_health;
}
int Ship::health(int arg) {
	return this->_health = arg;
}

void Ship::shoot() {
	Body *bullet = new Body(this->_coord.x() + this->_destination->w /2, this->_coord.y(),
			this->_bullets->selection()->w, this->_bullets->selection()->h);
	bullet->velocity().x(this->velocity().x());
	bullet->velocity().y(this->velocity().y() - 20);
	this->_bullets->addNode(bullet);
}

List<Body>* Ship::bullets() {
	return this->_bullets;
}

SDL_Texture* Ship::texture() {
	return this->_texture;
}
SDL_Texture* Ship::texture(SDL_Texture *newTexture) {
	return this->_texture = newTexture;
}

SDL_Rect* Ship::selection() {
	return this->_selection;
}

int Ship::getDamage(int lostHp) {
	return this->_health -= lostHp;
}
