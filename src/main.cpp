#include <SDL.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <hscore/log.h>
#include <hscore/coremodule.h>
#include <hscore/modulemanager.h>

int main() {
	hscore::CoreModule cm;

	hscore::ModuleManager::instance().init();
	hscore::ModuleManager::instance().update();

	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_WARNING("main", "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		LOG_INFO("main", "SDL initialized!");
	}
	return 0;
}