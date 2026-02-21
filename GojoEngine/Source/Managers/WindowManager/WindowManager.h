#pragma once

#include "Managers/WindowManager/Window/Window.h"
#include "Managers/Manager.h"	
#include <unordered_map>
#include <memory>
#include <expected>

namespace GojoEngine
{

	// ====================================================================================================
	// Error types during setup
	// ====================================================================================================

	enum class WindowError
	{
		ManagerIsNotInitialized,
		CreationFailed
	};

	// ====================================================================================================
	// Window manager
	// ====================================================================================================

	class GOJO_API WindowManager final : public Manager<WindowManager>
	{
		friend class Manager<WindowManager>;

	public:
		[[nodiscard]] std::expected<WindowId, WindowError> CreateWindow(const WindowSettings& settings);
		[[nodiscard]] std::shared_ptr<Window> GetWindowById(WindowId id) const;
		[[nodiscard]] bool AreAllWindowsClosed() const;

		void OnUpdate();
		void CloseAllWindows();
		void CleanupClosedWindows();

	private:
		WindowManager();
		~WindowManager();

	private:
		std::unordered_map<WindowId, std::shared_ptr<Window>> mWindows;
		bool mInitialized{ false };
		uint16_t mWindowCounter{ 0 };
	};

}