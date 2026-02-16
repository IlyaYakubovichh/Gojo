#pragma once

namespace GojoEngine
{
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		~NonCopyable() = default;

		NonCopyable(NonCopyable&) = delete;
		NonCopyable& operator=(NonCopyable&) = delete;

		NonCopyable(NonCopyable&&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
	};
}