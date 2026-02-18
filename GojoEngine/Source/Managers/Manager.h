#pragma once

#include "Core/Macros.h"
#include "Core/Utility.h"

#include <utility>

namespace GojoEngine
{
	template<typename T>
	class Manager : public NonCopyable
	{
	public:
		template<typename... Args>
		static void StartUp(Args&&... args)
		{
			GOJO_RUNTIME_ASSERT(!sInstance, "Only one instance of LogManager should be!");
			if (!sInstance)
			{
				sInstance = new T(std::forward<Args>(args)...);
			}
		}

		static void ShutDown()
		{
			GOJO_RUNTIME_ASSERT(sInstance, "You already destroyed LogManager!");
			if (sInstance)
			{
				delete sInstance;
				sInstance = nullptr;
			}
		}

		static T& GetInstance()
		{
			GOJO_RUNTIME_ASSERT(sInstance, "Manager instance accessed before StartUp() or after ShutDown()!");
			return *sInstance;
		}

		static T* GetPtr() { return sInstance; }
		static bool IsInitialized() { return sInstance != nullptr; }

	protected:
		Manager() = default;
		~Manager() = default;

	protected:
		static T* sInstance;
	};

	template<typename T>
	T* Manager<T>::sInstance = nullptr;
}