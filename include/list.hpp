#ifndef LIST_H
#define LIST_H

#include "body.hpp"
#include "ship.hpp"
#include "constant.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class Ship;

template<class T> struct node {
	T* val;
	struct node *next;
	struct node *prev;
};

template<class T> class List {
	public:
		List();
		~List();
		struct node<T>* addNode(T *element);
		struct node<T>* delNode(struct node<T> *target);
		void texture(SDL_Texture *arg);
		void selection(int selX,int selY, int selW, int selH);
		SDL_Rect* selection();
		int count();
		void render(SDL_Renderer *renderer);
		void update(int height);
		int countIntersections(Vector& coord, int width, int height);
		friend void doDamage(List<Ship>& enemies, List<Body>& bullets);
		friend void changeVelocity(List<Ship>& enemies, Ship &player);
		friend Ship* findIntersections(List<Ship>& objects, struct node<Ship> *target);
	private:
		SDL_Texture *_texture;
		SDL_Rect *_selection;
		struct node<T> *_first;
};


template<class T> List<T>::List() {
	this->_first = NULL;
}

template<class T> List<T>::~List() {
	if(!this->_first)
		return;

	struct node<T> *current = this->_first;

	while(current->next) {
		current = current->next;
		delete current->prev;
	}

	delete current;

	if(this->_texture)
		SDL_DestroyTexture(this->_texture);
}

template<class T> struct node<T>* List<T>::addNode(T *element) {
	struct node<T> *newNode = new struct node<T>;

	newNode->prev = NULL;
	newNode->next = this->_first;
	newNode->val = element;

	if(this->_first)
		this->_first->prev = newNode;

	return this->_first = newNode;
}

template<class T> struct node<T>* List<T>::delNode(struct node<T> *target) {
	if(!target->prev) {
		this->_first = target->next;
		delete target;

		if(this->_first) {
			this->_first->prev = NULL;
			return this->_first->next;
		}

		return NULL;
	}

	struct node<T> *prev = target->prev;
	prev->next = target->next;

	if(target->next)
		target->next->prev = prev;

	delete target;

	return prev->next;
}

template<class T> void List<T>::texture(SDL_Texture* arg) {
	this->_texture = arg;
}

template<class T> void List<T>::selection(int selX, int selY, int selW, int selH) {
	this->_selection = new SDL_Rect;
	this->_selection->x = selX;
	this->_selection->y = selY;
	this->_selection->w = selW;
	this->_selection->h = selH;
}
template<class T> SDL_Rect* List<T>::selection() {
	return this->_selection;
}

template<class T> int List<T>::count() {
	int count;
	struct node<T> *current = this->_first;
	for(count = 0; current; count++)
		current = current->next;
	return count;
}

template<class T> void List<T>::update(int height) {
	struct node<T> *current = this->_first;
	while(current) {
		if(current->val->coord().y() + height > 0) {
			current->val->coord() += current->val->velocity();
			current = current->next;
		}
		else
			current = this->delNode(current);
	}
}
template<class T> void List<T>::render(SDL_Renderer* renderer) {
	struct node<T> *current = this->_first;
	while(current) {
		SDL_RenderCopy(renderer, this->_texture, this->_selection, current->val->destination());
		current = current->next;
	}
}

template<class T> int List<T>::countIntersections(Vector& coord, int width, int height) {
	int count;
	Vector tmp;
	struct node<T> *current = this->_first;
	for(count = 0; current; current = (current) ? current->next : NULL) {
		tmp = (current->val->coord() - coord);
		if(abs(tmp.x()) <= width && abs(tmp.y()) <= height) {
			current = this->delNode(current);
			count++;
		}
	}

	return count;
}

#endif
