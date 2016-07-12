#include "stacktrace.h"

#include "stacktrace.h"

#include <hscore/log.h>
#include <hscore/cm.h>

#ifdef _LINUX
#include <execinfo.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cxxabi.h>
#elif (_MSC_VER >= 1500 && _MSC_VER < 1900)
#pragma comment(lib, "Dbghelp.lib") 
#pragma warning(push, 0)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#pragma warning(pop)
#include <DbgHelp.h>
#endif

#if (_WIN32 && _MSC_VER < 1900 && _UNIX)
void hscore::printStack()
{
  unsigned int   i;
  void         * stack[100];
  unsigned short frames;
  SYMBOL_INFO  * symbol;
  HANDLE         process;

  process = GetCurrentProcess();

  SymSetOptions(SYMOPT_LOAD_LINES);

  SymInitialize(process, NULL, TRUE);

  frames = CaptureStackBackTrace(0, 200, stack, NULL);
  symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
  symbol->MaxNameLen = 255;
  symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

  for (i = 1; i < frames; i++)
  {
    SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
    DWORD  dwDisplacement;
    IMAGEHLP_LINE64 line;

    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    if (/*!strstr(symbol->Name, "VSDebugLib::") &&*/
      SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &dwDisplacement, &line))
    {
			LOG_INFO(LOG_CORE, symbol->Name, ":", line.LineNumber);
    }
    if (0 == strcmp(symbol->Name, "main"))
      break;
  }

  free(symbol);
}
#elif _LINUX
int hscore::getFileAndLine(unw_word_t addr, char *file, size_t flen, int *line)
{
  static char buf[256];

  // prepare command to be executed
  // our program need to be passed after the -e parameter
  sprintf(buf, "/usr/bin/addr2line -C -e ./%s -f -i %lx", __progname, addr);

  FILE* f = popen(buf, "r");

  if (f == NULL)
  {
    perror(buf);
    return 0;
  }

  // get function name
  fgets(buf, 256, f);

  // get file and line
  fgets(buf, 256, f);

  if (buf[0] != '?')
  {
    char *p = buf;

    // file name is until ':'
    while (*p != ':')
    {
      p++;
    }

    *p++ = 0;
    // after file name follows line number
    strcpy(file, buf);
    sscanf(p, "%d", line);
  }
  else
  {
    strcpy(file, "unknown");
    *line = -1;
  }

  pclose(f);
}

void hscore::printStack()
{

  unw_cursor_t cursor;
  unw_context_t uc;
  unw_word_t ip, sp, off;
  unw_proc_info_t pi;
  char file[256], name[256];
  int line;
  int status;

  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);
  while (unw_step(&cursor) > 0)
  {
    unw_get_reg(&cursor, UNW_REG_IP, &ip);
    unw_get_reg(&cursor, UNW_REG_SP, &sp);

    unw_get_proc_name(&cursor, name, sizeof(name), &off);
    getFileAndLine((long)ip, file, 256, &line);

    if (line >= 0)
    {
      char *realname;
      realname = abi::__cxa_demangle(name, 0, 0, &status);

      if (realname)
      {
        printf("%s: %s, %d\n", realname, file, line);
        free(realname);
      }
      else
      {
        printf("%s: %s, %d\n", name, file, line);
      }
    }
  }
}
#else
void hscore::printStack() {}
#endif


