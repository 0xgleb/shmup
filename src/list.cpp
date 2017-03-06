#include "../include/list.hpp"
#include "../include/body.hpp"
#include "../include/constant.hpp"

#include <SDL2/SDL.h>
#include <iostream>

List::List() {
	this->_first = NULL;
}

List::List(Body *body) {
	this->_first = new struct node;
	this->_first->prev = NULL;
	this->_first->next = NULL;
	this->_first->val = body;
}

List::~List() {
	if(!this->_first)
		return;
	struct node *current = this->_first;
	while(current->next) {
		current = current->next;
		delete current->prev;
	}
	delete current;
	if(this->_texture)
		SDL_DestroyTexture(this->_texture);
}

struct node* List::addNode(Body *body) {
	struct node *newNode = new struct node;
	newNode->prev = NULL;
	newNode->next = this->_first;
	newNode->val = body;
	if(this->_first)
		this->_first->prev = newNode;
	return this->_first = newNode;
}

struct node* List::delNode(struct node *target) {
	if(!target->prev) {
		this->_first = target->next;
		delete target;
		if(this->_first) {
			this->_first->prev = NULL;
			return this->_first->next;
		}
		else
			return NULL;
	}

	struct node *prev = target->prev;
	prev->next = target->next;
	if(target->next)
		target->next->prev = prev;
	delete target;
	return prev->next;
}

void List::texture(SDL_Texture* arg) {
	this->_texture = arg;
}

void List::selection(int selX, int selY, int selW, int selH) {
	this->_selection = new SDL_Rect;
	this->_selection->x = selX;
	this->_selection->y = selY;
	this->_selection->w = selW;
	this->_selection->h = selH;
}
SDL_Rect* List::selection() {
	return this->_selection;
}

int List::count() {
	int count;
	struct node *current = this->_first;
	for(count = 0; current; count++)
		current = current->next;
	return count;
}

void List::update() {
	struct node *current = this->_first;
	while(current) {
		if(current->val->coord().y() + constant::bullet::selH > 0) {
			current->val->coord() += current->val->velocity();
			current = current->next;
		}
		else
			current = this->delNode(current);
	}
}
void List::render(SDL_Renderer* renderer) {
	struct node *current = this->_first;
	while(current) {
		SDL_RenderCopy(renderer, this->_texture, this->_selection, 
				current->val->destination());
		current = current->next;
	}
}
