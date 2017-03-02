#include <iostream>

#include "../include/sdl.hpp"
#include "../include/body.hpp"
#include "../include/list.hpp"
#include "../include/constant.hpp"

using namespace std;

Sdl::Sdl(const char *title, const char *path, const int width, const int height) {
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) {
		cout << "An error occured while initializing SDL2: " 
				<< SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	this -> _win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(!this -> _win) {
		cout << "An error occured while creating window: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	this -> _renderer = SDL_CreateRenderer(this -> _win, -1, 
				SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(!this -> _renderer) {
		cout << "An error occured while creating renderer" << SDL_GetError() << endl;
		SDL_DestroyWindow(this -> _win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_Surface *surface = IMG_Load(path);
	if(!surface) {
		cout << "An error occured while creating surface" << SDL_GetError() << endl;
		SDL_DestroyRenderer(this -> _renderer);
		SDL_DestroyWindow(this -> _win);
		SDL_Quit();
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}

	SDL_RenderCopy(this->_renderer,this->_bcg,this->_bcg_size,this->_bcg_size);
	SDL_RenderPresent(this -> _renderer);
	SDL_SetRenderDrawColor(this -> _renderer, 255, 255, 255, 255);
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

SDL_Texture* Sdl::createTexture(const char *path) {
	SDL_Surface *surface = IMG_Load(path);
	if(!surface) {
		cout << "An error occured while creating a texture: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	SDL_Texture *result = SDL_CreateTextureFromSurface(this -> _renderer, surface);
	SDL_FreeSurface(surface);
	if(!this -> _bcg) {
		cout << "An error occured while creating texture for background: " 
				<< SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	return result;
}

void Sdl::render(Body& body, List& bullets) {
	SDL_RenderClear(this -> _renderer);
	SDL_RenderCopy(this->_renderer, this->_bcg, this->_bcg_size, this->_bcg_size);
	bullets.call(SDL_RenderCopy, this -> _renderer);
	SDL_RenderCopy(this -> _renderer, body.texture(), 
			body.selection(), body.destination());
	
	// SDL_RenderDrawRect(this -> _renderer, body.destination());
	SDL_RenderPresent(this -> _renderer);
}
