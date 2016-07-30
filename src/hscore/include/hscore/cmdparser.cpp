#include "cmdparser.h"

#include <hscore/log.h>
#if defined(WIN32)
#include <malloc.h>

#pragma warning(push, 0)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#pragma warning(pop)
#include <shellapi.h>
#endif

hscore::CmdParser::CmdParser()
{}

hscore::CmdParser::~CmdParser()
{

}

void hscore::CmdParser::parse(int32_t argc, char* argv[])
{
#ifdef WIN32
	LPWSTR *commandLineArgs = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (NULL == commandLineArgs)
	{
		argc = 0;
	}
	if (argc > 0)
	{
		argv = (char **) malloc(sizeof(char *) * argc);
		if (argv == NULL)
		{
			argc = 0;
		}
		else
		{
			for (int iii = 0; iii < argc; iii++)
			{
				size_t wideCharLen = wcslen(commandLineArgs[iii]);
				size_t numConverted = 0;

				argv[iii] = (char *) malloc(sizeof(char) * (wideCharLen + 1));
				if (argv[iii] != NULL)
				{
					wcstombs_s(&numConverted, argv[iii], wideCharLen + 1,
						commandLineArgs[iii], wideCharLen + 1);
				}
			}
		}
	}
	else
	{
		argv = NULL;
	}
#endif
	std::vector<inArgPair> inArgs;

	for (int32_t i = 0; i < argc; ++i)
	{
		HS_ASSERT(argv[i] != NULL);
		if (strncmp(argv[i], "--", 2) == 0)
		{
			inArgPair inArg;
			std::string strArg = std::string(argv[i]);
			inArg.longKey = strArg.substr(2, strArg.size());
			inArgs.push_back(inArg);
		}
		else if (strncmp(argv[i], "-", 1) == 0)
		{
			inArgPair inArg;
			inArg.smallKey[0] = argv[i][1];
			inArgs.push_back(inArg);
		}
		else
		{
			if (inArgs.size() > 0)
			{
				inArgs.back().value = argv[i];
			}
		}
	}
	for (const CmdParser::inArgPair& a : inArgs)
	{
		bool found = false;
		for (const CmdParser::arg_dI* v : m_arglist)
		{
			if (a.longKey == v->m_lkey
				|| a.smallKey[0] == v->m_key)
			{
				Settings::instance().updateValue(getSettingKey(v->m_lkey), a.value);
				found = true;
				break;
			}
		}
		if (!found)
		{
			std::string argString = a.toString();
			LOG_WARNING("Argument %s not found. It was ignored.", argString);
		}
	}
}

void hscore::CmdParser::logPossibleArguments() const
{
	for (const CmdParser::arg_dI* v : m_arglist)
	{
		LOG_INFO("-", v->m_key, "--", v->m_lkey, "\t", v->m_description);
	}
}

std::string hscore::CmdParser::getSettingKey(const std::string& lkey)
{
	std::string nk = lkey;
	nk.append("_CMD_ARG");
	return nk;
}
