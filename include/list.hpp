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
		struct node* delNode(struct node *target);
		void texture(SDL_Texture *arg);
		void selection(int selX,int selY, int selW, int selH);
		SDL_Rect* selection();
		int count();
		void render(SDL_Renderer *renderer);
		void update();
	private:
		SDL_Texture *_texture;
		SDL_Rect *_selection;
		struct node *_first;
};

#endif
