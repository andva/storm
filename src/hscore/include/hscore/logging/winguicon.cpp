#include "winguicon.h"
#ifdef WIN32

void RedirectIOToConsole()
{
  CONSOLE_SCREEN_BUFFER_INFO coninfo;

  FILE *fp;

  // allocate a console for this app

  AllocConsole();

  // set the screen buffer to be big enough to let us scroll text

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

  coninfo.dwSize.Y = MAX_CONSOLE_LINES;

  SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

  fp = freopen("conin$", "r", stdin);
  fp = freopen("conout$", "w", stdout);
  fp = freopen("conout$", "w", stderr);
}
#endif
