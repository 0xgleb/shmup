#include <iostream>
#include <cassert>

#include "include/constant.hpp"
#include "include/sdl.hpp"
#include "include/list.hpp"
#include "include/body.hpp"
#include "include/ship.hpp"

using namespace std;

int main() {
	Sdl sdl(constant::title, constant::bcg::path, 
			constant::window::width, constant::window::height);

	Ship player((constant::window::width - constant::player::selW) / 2,
			constant::window::height - constant::player::selH, 
			constant::player::selX, constant::player::selY,
			constant::player::selW, constant::player::selH);
	player.texture(sdl.createTexture(constant::player::path));
	player.bullets()->texture(sdl.createTexture(constant::sprites));
	player.bullets()->selection(constant::bullet::selX, constant::bullet::selY, 
			constant::bullet::selW, constant::bullet::selH);

	Ship enemy((constant::window::width - constant::enemy::selW) / 2,
			constant::enemy::selH, constant::enemy::selX, 
			constant::enemy::selY, constant::enemy::selW, constant::enemy::selH);
	enemy.texture(sdl.createTexture(constant::sprites));
	
	List<Ship> enemies;
	enemies.addNode(&enemy);
	enemies.texture(sdl.createTexture(constant::sprites));
	enemies.selection(constant::enemy::selX, constant::enemy::selY,
			constant::enemy::selW, constant::enemy::selH);

	clock_t begin;
	bool close_requested = false,
			 right, left, up, down;
	right = left = up = down = false;
	SDL_Event *event = new SDL_Event;
	while(true) {
		begin = clock();
		while(SDL_PollEvent(event)) {
      switch(event->type) {
        case SDL_QUIT:
          close_requested = true;
          break;
        case SDL_KEYDOWN:
          switch(event->key.keysym.scancode) {
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
							right = true;
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
							left = true;
              break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
							up = true;
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
							down = true;
              break;
            case SDL_SCANCODE_SPACE:
							player.shoot(); 
              break;
            default:
              break;
          }
          break;
        case SDL_KEYUP:
          switch(event->key.keysym.scancode) {
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
							right = false;
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
							left = false;
              break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
							up = false;
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
							down = false;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }

		if(close_requested)
			break;

		if(right ^ left)
			player.velocity().x() = right? constant::player::speed 
				: - constant::player::speed;
		else
			player.velocity().x() = 0;

		if(up ^ down)
			player.velocity().y() = down ? constant::player::speed 
				: - constant::player::speed;
		else
			player.velocity().y() = 0;

		player.coord() += player.velocity();
		if(player.coord().x() < 0 || 
				constant::window::width - constant::player::selW < player.coord().x())
			player.coord().x() = 
				(player.coord().x() < 0) ? 0 : 
				constant::window::width - constant::player::selW;
		if(player.coord().y() < (2 * constant::window::height / 3) || 
				constant::window::height-constant::player::selH < player.coord().y())
			player.coord().y() = 
				(player.coord().y() < 2 * constant::window::height / 3) 
				? 2 * constant::window::height / 3 
				: constant::window::height - constant::player::selH;

		player.bullets()->update();

		getDamage(enemies, *player.bullets());

		sdl.render(player, enemies);
    SDL_Delay(1000 / constant::fps 
				+ static_cast<int>((begin - clock()) / CLOCKS_PER_SEC) * 1000);
	}

	return 0;
}
