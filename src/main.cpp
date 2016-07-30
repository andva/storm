#include <SDL.h>

#include <hscore/log.h>
#include <hscore/coremodule.h>
#include <graphics/graphicsmodule.h>
#include <hscore/modulemanager.h>
#include <graphics/log.h>

bool pollKeyboard() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch( event.type ){
			/* Look for a keypress */
			case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch(event.key.keysym.sym){
				case SDLK_q:
					SDL_Quit();
					return true;
				case SDLK_t:
					LOG_INFO("main", "T");
				default:
					break;
			}
		}
	}
	return false;
}



int main() {
	hscore::CoreModule cm;
	GraphicsModule gm;

	hscore::ModuleManager::instance().init();

	//Wait two seconds

	while (!pollKeyboard()) {
		hscore::ModuleManager::instance().update();
	}
	SDL_Quit();

	return 0;
}