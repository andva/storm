//
// Created by Andreas Valter on 14/07/16.
//

#ifndef STORM_GRAPHICSMODULE_H
#define STORM_GRAPHICSMODULE_H

#include <hscore/hailstormmodule.h>

#pragma once

class GraphicsModule : hscore::HailStormModule {
public:
	GraphicsModule();
	virtual void registerFolders() override;
	virtual void addCmdArguments() override;
	virtual void addSettings() override;
	virtual void bindUpdatePasses() override;
	virtual void provideLocators() override;
	virtual void registerKeys() override;
	virtual void init() override;
private:
};


#endif //STORM_GRAPHICSMODULE_H
