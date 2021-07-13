#pragma once

#include <functional>

namespace Matrix
{
	template<typename T>
	using Predicate = std::function<bool(T)>;

	template<typename T>
	using ActionT = std::function<void(T)>;

	using Action = std::function<void()>;

	template<class... TArgs>
	using ActionArgs = std::function<void(TArgs&&... args)>;


}