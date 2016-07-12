
#ifndef SINGLETON_H__
#define SINGLETON_H__

#pragma once
#include <hscore/cm.h>

namespace hscore
{

	template <typename T>
	class Singleton
	{
	public:
		static inline T& instance()
		{
			static T instance;
			return instance;
		};
	protected:
		Singleton()
		{};
		~Singleton()
		{};
	private:
		HS_DISSALLOW_COPY_ASSIGN(Singleton)
	};

}

#define SETUP_SINGLETON(__class_name__) \
  friend class hscore::Singleton<__class_name__>; \
  HS_DISSALLOW_COPY_ASSIGN(__class_name__)

#endif // SINGLETON_H__

