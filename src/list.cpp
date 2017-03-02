#include "../include/list.hpp"
#include "../include/body.hpp"

#include <SDL2/SDL.h>

List::List() {
	this -> _first = NULL;
}

List::List(Body *body) {
	this -> _first = new struct node;
	this -> _first -> prev = NULL;
	this -> _first -> next = NULL;
	this -> _first -> val = body;
}

List::~List() {
	if(!this -> _first)
		return;
	struct node *current = this -> _first;
	while(current -> next) {
		current = current -> next;
		delete current -> prev;
	}
	delete current;
}

struct node* List::addNode(Body *body) {
	struct node *newNode = new struct node;
	newNode -> prev = NULL;
	newNode -> next = this -> _first;
	newNode -> val = body;
	if(this -> _first)
		this -> _first -> prev = newNode;
	return this -> _first = newNode;
}

void List::call(
		int (*f)(SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*), 
		SDL_Renderer* renderer) {
	struct node *current = this -> _first;
	while(current) {
		f(renderer, current -> val -> texture(), 
				current -> val -> selection(),  current -> val -> destination());
		current = current -> next;
	}
}
