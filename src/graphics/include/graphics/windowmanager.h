#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL.h>

class WindowManager {
	public:
		WindowManager();
		~WindowManager();
		bool init();
		void resize();
		void close();
		void update();
	private:
		SDL_Window* mWindow;
		SDL_Surface* mSurface;
};

#endif