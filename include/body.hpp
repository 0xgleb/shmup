#ifndef BODY_H
#define BODY_H

#include <SDL2/SDL.h>

#include "vector.hpp"

class Body {
	public:
		Body(int x, int y, int selX, int selY, int selW, int selH);
		~Body();
		SDL_Texture* texture();
		SDL_Texture* texture(SDL_Texture *newTexture);
		SDL_Rect* selection();
		SDL_Rect* destination();
		Vector& coord();
		Vector& coord(Vector newVector);
		Vector& velocity();
		Vector& velocity(Vector newVector);
		Body* shoot(int selX, int selY, int selW, int selH);
	private:
		Vector _coord;
		Vector _velocity;
		SDL_Rect *_selection;
		SDL_Rect *_destination;
		SDL_Texture *_texture;
};

#endif
