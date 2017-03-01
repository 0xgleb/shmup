#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace constant {
	const char *title = const_cast<char *>("Shmup");
	namespace window {
		const int width = 1280;
		const int height = 720;
	}
	namespace bcg {
		const char* path = const_cast<char *>("images/bcg.png");
	}
}

using namespace std;

int main() {
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) {
		cout << "An error occured while initializing SDL2: " << SDL_GetError() << endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow(constant::title, 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			constant::window::width, constant::window::height, 0);
	if(!win) {
		cout << "An error occured while creating window: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(!renderer) {
		cout << "An error occured while creating renderer" << SDL_GetError() << endl;
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	// SDL_Surface *surface = IMG_Load(constant::bcg::path);

	return 0;
}
