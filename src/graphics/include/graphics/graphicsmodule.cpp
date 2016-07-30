#include "graphicsmodule.h"

#include <SDL.h>

#include <graphics/log.h>

GraphicsModule::GraphicsModule() { }

void GraphicsModule::addCmdArguments() { }

void GraphicsModule::addSettings() { }

void GraphicsModule::bindUpdatePasses() {
	m_updatePasses[0] = [&]() { 
		mWindowManager.update();
	};
}

void GraphicsModule::init() {
	mWindowManager.init();
}

void GraphicsModule::provideLocators() { }

void GraphicsModule::registerFolders() { }

void GraphicsModule::registerKeys() { }