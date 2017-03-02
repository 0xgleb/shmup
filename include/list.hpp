#ifndef LIST_H
#define LIST_H

#include "body.hpp"
#include <SDL2/SDL.h>

struct node {
	Body* val;
	struct node *next;
	struct node *prev;
};

class List {
	public:
		List();
		List(Body *body);
		~List();
		struct node* addNode(Body *body);
		void call(int (*f)(SDL_Renderer*, SDL_Texture*, 
					const SDL_Rect*, const SDL_Rect*), SDL_Renderer *renderer);
	private:
		struct node *_first;
};

#endif
