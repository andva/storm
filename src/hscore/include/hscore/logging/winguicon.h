#ifndef HSCORE_WINGUICON_H
#define HSCORE_WINGUICON_H
#ifdef WIN32

#include <windows.h>
#include <stdio.h>

#pragma once

static const WORD MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole();

#endif


#endif
