#ifndef CONSTANT_H
#define CONSTANT_H

namespace constant {
	extern const char *title;
	extern const int fps;
	extern const char *sprites;
	namespace window {
		extern const int width;
		extern const int height;
	}
	namespace bcg {
		extern const char* path;
	}
	namespace player {
		extern const char* path;
		extern const int selX;
		extern const int selY;
		extern const int selW;
		extern const int selH;
		extern const int speed;
	}
	namespace enemy {
		extern const char *path;
		extern const int selX;
		extern const int selY;
		extern const int selW;
		extern const int selH;
		extern const int speed;
	}
	namespace bullet {
		extern const int selX;
		extern const int selY;
		extern const int selW;
		extern const int selH;
	}
}

#endif
