#ifndef SHIP_H
#define SHIP_H

#include "body.hpp"
#include "list.hpp"
#include <SDL2/SDL.h>

template<class T> class List;

class Ship: public Body {
	public:
		Ship(int x, int y, int selX, int selY, int selW, int selH);
		~Ship();
		SDL_Rect* selection();
		void shoot();
		int health();
		int health(int arg);
		List<Body>* bullets();
		SDL_Texture* texture();
		SDL_Texture* texture(SDL_Texture *newTexture);
		int applyDamage(int lostHp);
	private:
		List<Body>* _bullets;
		int _health;
		SDL_Texture *_texture;
		SDL_Rect *_selection;
};

#endif
