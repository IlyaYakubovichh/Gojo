#pragma once

#include "Core/Macros.h"
#include "Core/Utility.h"
#include <string>
#include <functional> 

struct GLFWwindow;

namespace GojoEngine
{
	// ====================================================================================================
	// Window Data Structures
	// ====================================================================================================

	struct GOJO_API WindowSettings
	{
		uint16_t XPos{ 50 };
		uint16_t YPos{ 50 };
		uint16_t Width{ 800 };
		uint16_t Height{ 600 };
		std::string Title{ "GojoWindow" };
	};

	/**
	 * @brief Strongly typed ID for windows to avoid confusion with regular integers.
	 */
	struct GOJO_API WindowId
	{
		constexpr explicit WindowId(uint32_t id) : mId(id) {}

		WindowId operator++(int)
		{
			WindowId temp = *this;
			++mId;
			return temp;
		}

		constexpr auto operator<=>(const WindowId&) const = default; // Space-ship operator that will be exposed to 6 operators.

		uint32_t mId{ 0 };
	};

	// ====================================================================================================
	// Window Class
	// ====================================================================================================

	class GOJO_API Window final : public NonCopyable
	{
	public:
		explicit Window(WindowId id, const WindowSettings& settings);
		~Window() override;

		[[nodiscard]] bool ShouldClose() const;
		[[nodiscard]] bool IsValid() const { return mWindow != nullptr; }

		[[nodiscard]] GLFWwindow* GetRaw() const { return mWindow; }
		[[nodiscard]] const std::string& GetTitle() const { return mSettings.Title; }
		[[nodiscard]] std::pair<uint16_t, uint16_t> GetResolution() const { return std::make_pair(mSettings.Width, mSettings.Height); }
		[[nodiscard]] WindowId GetId() const { return mId; }

	private:
		void InitializeCallbacks();

	private:
		GLFWwindow* mWindow{ nullptr };
		WindowSettings mSettings;
		WindowId mId;
	};
}

// ====================================================================================================
// Standard Library Specializations
// ====================================================================================================

namespace std
{
	template<>
	struct hash<GojoEngine::WindowId>
	{
		size_t operator()(const GojoEngine::WindowId& windowId)	const noexcept
		{
			return std::hash<uint32_t>{}(windowId.mId);
		}
	};
}