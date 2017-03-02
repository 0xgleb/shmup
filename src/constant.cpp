#include "../include/constant.hpp"

namespace constant {
	const char *title = const_cast<char *>("Shmup");
	const int fps = 60;
	namespace window {
		const int width = 1280;
		const int height = 720;
	}
	namespace bcg {
		const char *path = const_cast<char *>("images/bcg.jpg");
	}
	namespace player {
		const char* path = const_cast<char *>("images/shmup.png");
		const int width = 41;
		const int height = 32;
		const int selX = 9;
		const int selY = 15;
		const int speed = 10;
	}
	namespace bullet {
		const char *path = const_cast<char *>("images/sprites.png");
		const int selX = 150;
		const int selY = 200;
		const int selW = 10;
		const int selH = 30;
	}
}
