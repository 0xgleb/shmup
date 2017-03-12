#ifndef BODY_H
#define BODY_H

#include <SDL2/SDL.h>

#include "vector.hpp"

class Body {
	public:
		Body(int x, int y, int w, int h);
		~Body();
		SDL_Rect* destination();
		Vector& coord();
		Vector& coord(Vector& newVector);
		Vector& velocity();
		Vector& velocity(Vector& newVector);
	protected:
		Vector _coord;
		Vector _velocity;
		SDL_Rect *_destination;
};

#endif
