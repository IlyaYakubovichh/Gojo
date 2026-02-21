#pragma once

namespace GojoEngine
{
	/**
	 * @brief Inherit from this class to prevent copying and moving of the derived class.
	 */
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;

		// Disable Copy
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

		// Disable Move
		NonCopyable(NonCopyable&&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
	};
}