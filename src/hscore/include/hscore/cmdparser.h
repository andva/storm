#ifndef HSCORE_CMDPARSER_H
#define HSCORE_CMDPARSER_H

#include <vector>
#include <map>

#include <hscore/assert.h>
#include <hscore/cm.h>
#include <hscore/pattern/singleton.h>
#include <hscore/settings.h>
#include <hscore/settings/settingsdescription.h>

#pragma once

namespace hscore
{
	class CmdParser : public hscore::Singleton<CmdParser>
	{
	public:
		~CmdParser();

		void parse(int32_t argc, char* argv[]);

		void logPossibleArguments() const;

		void logCmdState() const;

		void parse();

		template<typename T>
		void add(char key, std::string lkey, std::string description, T defVal);

		template<typename T>
		T getValue(char key) const;

	private:
		static std::string getSettingKey(const std::string& lkey);

		struct arg_dI
		{
			arg_dI(char key, std::string lkey, std::string description)
				: m_key(key), m_lkey(lkey), m_description(description)
			{}
			char m_key;
			std::string m_lkey;
			std::string m_description;
		};
		template<typename T>
		struct arg_d : public arg_dI
		{
			arg_d(char key, std::string lkey, std::string description, T defaultVal)
				: arg_dI(key, lkey, description)
				, settingdescr(CmdParser::getSettingKey(lkey), defaultVal)
			{

			}
			SettingDescription<T> settingdescr;
		};

		struct inArgPair
		{
		public:
			char ssk = ' ';
			char smallKey[2];
			std::string longKey;
			std::string value;
			inArgPair() { smallKey[0] = ssk, longKey = "noLongIn", value = ""; };
			std::string toString() const
			{
				std::string s;
				if (smallKey[0] != ssk)
				{
					s.append("-");
					s.append(std::string(smallKey));
					s = s.substr(0, 2);
				}
				if (longKey != "noLongIn")
				{
					s.append("--");
					s.append(longKey);
				}
				return s;
			}
		};

		template<typename T>
		arg_d<T>* getArg(char key) const;

		CmdParser();
		SETUP_SINGLETON(CmdParser);


		std::vector<arg_dI*> m_arglist;
	};

	template<typename T>
	hscore::CmdParser::arg_d<T>* hscore::CmdParser::getArg(char key) const
	{
		for (auto& a : m_arglist)
		{
			if (a->m_key == key)
			{
				return static_cast<arg_d<T>*>(a);
			}
		}
		return nullptr;
	}

	template<typename T>
	T hscore::CmdParser::getValue(char key) const
	{
		arg_d<T>* v = getArg<T>(key);
		HS_ASSERT(v != nullptr && "Argument not defined");
		return Settings::get<T>(getSettingKey(v->m_lkey));
	}

	template<typename T>
	void hscore::CmdParser::add(char key, std::string lkey, std::string description, T defVal)
	{
		arg_d<T>* d = new arg_d<T>(key, lkey, description, defVal);
		m_arglist.push_back(d);
		Settings::instance().registerSetting<T>(d->settingdescr);
	}

}

#endif
