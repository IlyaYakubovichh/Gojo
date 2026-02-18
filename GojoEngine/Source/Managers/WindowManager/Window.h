#pragma once

#include "Core/Macros.h"
#include "Core/Utility.h"
#include <string>

struct GLFWwindow;

namespace GojoEngine
{
	struct GOJO_API WindowSettings
	{
		u16 XPos{ 50 };
		u16 YPos{ 50 };
		u16	Width{ 800 };
		u16 Height{ 600 };
		std::string Title{ "GojoWindow" };
	};

	struct GOJO_API WindowId
	{
		constexpr explicit WindowId(u32 id) // Literal, no virtual, isn't try block HENCE can be constexpr
			: mId(id)
		{
		}

		WindowId operator++(int)
		{
			WindowId windowId = *this;
			++mId;
			return windowId;
		}

		constexpr auto operator<=>(const WindowId&) const = default;

		u32 mId{ 0 };
	};

	class GOJO_API Window final : public NonCopyable
	{
	public:
		explicit Window(const WindowSettings& settings);
		~Window();

		[[nodiscard]] b8 ShouldClose() const;
		[[nodiscard]] b8 IsValid() const { return mWindow != nullptr; }

		[[nodiscard]] GLFWwindow* GetRaw() const { return mWindow; }
		[[nodiscard]] const std::string& GetTitle() const { return mSettings.Title; }

	private:
		GLFWwindow* mWindow{ nullptr };
		WindowSettings mSettings;
	};
}

namespace std {
	template<>
	struct hash<GojoEngine::WindowId>
	{
		size_t operator()(const GojoEngine::WindowId& windowId)	const noexcept
		{
			return std::hash<u32>{}(windowId.mId);
		}
	};
}