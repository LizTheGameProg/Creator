#pragma once
namespace GAME_ENGINE
{
	template<class T>
	class Handler
	{
	public:
		constexpr Handler() {}

		bool Initialize();
		void DeInitialize();

		virtual bool OnInitialize() = 0;
		virtual void OnDeInitialize() = 0;

		static T const & Get();
		static T & Access();

	private:
		//inline static T * instance = nullptr;
		bool isInitialized = false;
	};
}

#include "handler.hpp"