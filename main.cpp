#include <iostream>
#include "include/sdl.hpp"
#include "include/constant.hpp"

using namespace std;

int main() {
	Sdl sdl(constant::title, constant::bcg::path, 
			constant::window::width, constant::window::height);

	clock_t begin;
	bool close_requested = 0;
	SDL_Event *event = new SDL_Event;
	while(true) {
		begin = clock();
    while(SDL_PollEvent(event)) {
      switch(event -> type) {
        case SDL_QUIT:
          close_requested = 1;
          break;
      }
    }

		if(close_requested)
			break;
    SDL_Delay(1000 / constant::fps + 
				static_cast<int>((begin - clock()) / CLOCKS_PER_SEC) * 1000);
	}
	return 0;
}
