#pragma once

#include "Managers/WindowManager/Window.h"
#include "Managers/Manager.h"	
#include <unordered_map>
#include <memory>
#include <expected>

namespace GojoEngine
{
	enum class WindowError
	{
		ManagerIsNotInitialized,
		CreationFailed
	};

	class GOJO_API WindowManager final : public Manager<WindowManager>
	{
		friend class Manager<WindowManager>;

	public:
		std::expected<WindowId, WindowError> CreateWindow(const WindowSettings& settings);
		void OnUpdate();
		void CloseAllWindows();
		void CleanupClosedWindows();
		b8 AreAllWindowsClosed();

		std::shared_ptr<Window> GetWindowById(WindowId id) const;

	private:
		WindowManager();
		~WindowManager();

	private:
		std::unordered_map<WindowId, std::shared_ptr<Window>> mWindows;

		b8 mInitialized{ false };
		u16 mWindowCounter{ 0 };
	};
}