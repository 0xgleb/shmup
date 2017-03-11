#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ship.hpp"
#include "list.hpp"

class Sdl {
	public:
		Sdl(const char *title, const char *path, 
				const int width, const int height);
		~Sdl();
		void delay(int duration);
		SDL_Texture* createTexture(const char *path);
		void render(Ship &player, List<Ship>& enemies);
	private:
		SDL_Window *_win;
		SDL_Renderer *_renderer;
		SDL_Texture *_bcg;
		SDL_Rect *_bcg_size;
};

#endif
