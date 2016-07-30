#include "windowmanager.h"

#include <graphics/log.h>
#include <OpenGL/gl3.h>

void checkSDLError(int line = -1) {
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		if (line != -1)
			LOG_ERROR("SDL Error: ", error, " line: ", line);
		else
			LOG_ERROR("SDL Error: ", error);
		SDL_ClearError();
	}
#endif
}

WindowManager::WindowManager() {

}

WindowManager::~WindowManager() {
	close();
}

bool WindowManager::init() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_WARNING(
			"SDL could not initialize! SDL_Error: ", SDL_GetError());
			return false;
	}
	else {
		LOG_INFO("SDL initialized!");
	}
	mWindow = SDL_CreateWindow(
			"storm",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			512,
			512,
			SDL_WINDOW_OPENGL);
	resize();
	const unsigned char* gl_version = glGetString(GL_VERSION);
	std::string v = reinterpret_cast<const char*>(gl_version);
	LOG_INFO("GL Version is: ", v);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

void WindowManager::close() {
	if (mWindow) {
		SDL_DestroyWindow(mWindow);
	}
}

void WindowManager::update() {
	SDL_GL_SwapWindow(mWindow);
	glClear(GL_COLOR_BUFFER_BIT);
}

void WindowManager::resize() {
	//Get window surface
	mSurface = SDL_GetWindowSurface(mWindow);

	//Update the surface
	SDL_UpdateWindowSurface(mWindow);
}