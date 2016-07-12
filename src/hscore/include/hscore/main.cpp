#if defined(WIN32)
#pragma comment(linker, "/subsystem:windows")
#pragma warning(push, 0)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#pragma warning(pop)
#endif

#include <hscore/cm.h>
#include <hscore/log.h>

#include <hscore/cmdparser.h>
#include <hscore/modulemanager.h>
#include <hscore/coremodule.h>
#include <hscore/settings.h>
#include <hscore/files/filesys.h>

#ifdef _WIN32
// Include header required for parsing the command line options.`

#pragma warning(disable: 28251)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
  int argc = 0;
  char *argv[1] = {""};

  hscore::CoreModule cm;

  hscore::ModuleManager::instance().init();
  hscore::ModuleManager::instance().update();
  
  return 1;
}
#else
int main(int argc, char **argv) {

}
#endif
