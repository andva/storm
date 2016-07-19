#include <SDL.h>
#include <hscore/log.h>
#include <hscore/coremodule.h>
#include <graphics/graphicsmodule.h>
#include <hscore/modulemanager.h>

int main() {
	hscore::CoreModule cm;
	GraphicsModule gm;

	hscore::ModuleManager::instance().init();
	hscore::ModuleManager::instance().update();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_WARNING("main", "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		LOG_INFO("main", "SDL initialized!");
	}
	SDL_Window* window = SDL_CreateWindow(
			"storm",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			512,
			512,
			SDL_WINDOW_OPENGL);

	//Get window surface
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface( window );

	//Wait two seconds
	SDL_Delay( 2000 );

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}