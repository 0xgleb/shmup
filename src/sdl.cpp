#include "../include/sdl.hpp"
#include "../include/constant.hpp"
#include <iostream>

using namespace std;

Sdl::Sdl(const char *title, const char *path, const int width, const int height) {
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) {
		cout << "An error occured while initializing SDL2: " 
				<< SDL_GetError() << endl;
		abort();
	}

	this -> _win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(!this -> _win) {
		cout << "An error occured while creating window: " << SDL_GetError() << endl;
		SDL_Quit();
		abort();
	}

	this -> _renderer = SDL_CreateRenderer(this -> _win, -1, 
				SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(!this -> _renderer) {
		cout << "An error occured while creating renderer" << SDL_GetError() << endl;
		SDL_DestroyWindow(this -> _win);
		SDL_Quit();
		abort();
	}

	SDL_Surface *surface = IMG_Load(path);
	if(!surface) {
		cout << "An error occured while creating surface" << SDL_GetError() << endl;
		SDL_DestroyRenderer(this -> _renderer);
		SDL_DestroyWindow(this -> _win);
		SDL_Quit();
		abort();
	}

	this -> _bcg_size = new SDL_Rect;
	this -> _bcg_size -> x = this -> _bcg_size -> y = 0;
	this -> _bcg_size -> w = width;
	this -> _bcg_size -> h = height;
	this -> _bcg = SDL_CreateTextureFromSurface(this -> _renderer, surface);
	SDL_FreeSurface(surface);
	if(!this -> _bcg) {
		cout << "An error occured while creating texture for background: " 
				<< SDL_GetError() << endl;
		SDL_DestroyRenderer(this -> _renderer);
		SDL_DestroyWindow(this -> _win);
		SDL_Quit();
		abort();
	}
}

Sdl::~Sdl() {
	SDL_DestroyTexture(this -> _bcg);
	SDL_DestroyRenderer(this -> _renderer);
	SDL_DestroyWindow(this -> _win);
	SDL_Quit();
}

void inline Sdl::delay(int duration) {
	SDL_Delay(duration);
}
