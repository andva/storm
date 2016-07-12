#pragma once

#ifndef ATO_H__
#define ATO_H__

#include <math.h>
#include <stdint.h>
#include <string>
#include <sstream>

namespace hscore
{

	template <typename T>
	inline T ato(const std::string& s);

	template <typename T>
	inline std::string toa(const T& v);

	template <>
	inline float_t ato(const std::string& s)
	{
		return static_cast<float_t>(atof(s.c_str()));
	};

	template <>
	inline int32_t ato(const std::string& s)
	{
		return static_cast<int32_t>(atof(s.c_str()));
	};

	template <>
	inline bool ato(const std::string& s)
	{
		return static_cast<int32_t>(atof(s.c_str())) == 1;
	};
 
	template <>
	inline std::string ato(const std::string& s)
	{
		return s;
	};

	template <>
	inline std::string toa(const std::string& s)
	{
		return s;
	}

	template <>
	inline std::string toa(char const * const & s)
	{
		return s;
	}

	template <>
	inline std::string toa(const int32_t& v)
	{
		std::stringstream ss;
		ss << v;
		return ss.str();
	};
	
	template <>
	inline std::string toa(const float_t& v)
	{
		std::stringstream ss;
		ss << v;
		return ss.str();
	};

	template <>
	inline std::string toa(const bool& v)
	{
		std::stringstream ss;
		ss << v;
		return ss.str();
	};
}
#endif // ATO_H__

