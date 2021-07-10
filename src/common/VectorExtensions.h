#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

namespace Matrix
{
	template<typename T>
	using Predicate = std::function<bool(T)>;

	template<typename T>
	using ActionT = std::function<void(T)>;

	class VectorExtensions
	{
	public:
		template<typename T>
		static T firstOrDefault(std::vector<T> items, Predicate<T> predicate)
		{
			T result;
			for (auto & item : items)
			{
				if (predicate(item))
				{
					result = item;
					break;
				}
			}
			return result;
		}

		template<typename T>
		static bool any(std::vector<T> items, Predicate<T> predicate)
		{
			bool result = false;
			for (auto & item : items)
			{
				if (predicate(item))
				{
					result = true;
					break;
				}
			}
			return result;
		}

		template<typename T>
		static void foreach(std::vector<T> items, ActionT<T> action)
		{
			for (auto & item : items)
			{
				action(item);
			}
		}

		template<typename T>
		static std::vector<T> where(std::vector<T> items, Predicate<T> predicate)
		{
			std::vector<T> result;

			for (auto & item : items)
			{
				if (predicate(item))
				{
					result.push_back(item);
				}
			}
			return result;
		}

		template<typename T>
		static std::vector<T> merge(std::vector<T>& source, std::vector<T> dest)
		{
			for (auto& item : dest)
			{
				source.push_back(item);
			}
			return source;
		}

		template<typename T>
		static bool isEmpty(std::vector<T> items)
		{
			return items.size() == 0;
		}

		template<typename T>
		static bool notEmpty(std::vector<T> items)
		{
			return items.size() > 0;
		}

		template<typename T>
		static std::string join(std::vector<T> items, std::string separator = "")
		{
			std::stringstream stream;
			auto size = items.size();

			for (size_t i = 0; i < size; i++)
			{
				stream << items[i];
				if (i < size - 1 && separator != "")
					stream << separator;
			}

			return stream.str();
		}

		template<typename TSource, typename TTarget>
		static std::vector<TTarget> selectAll(std::vector<TSource> items, std::function<std::vector<TTarget>(TSource)> selector)
		{
			std::vector<TTarget> result;

			for (auto& item : items)
			{
				auto values = selector(item);
				merge(result, values);
			}

			return result;
		}

		template<typename T>
		static std::vector<T> range(std::vector<T> items, const int start, const int length)
		{
			std::vector<T> result;
			auto size = items.size();

			if (start < size)
			{
				int end = start + length;
				for (int index = start; index < (end < size ? end : size); index++)
				{
					result.push_back(items[index]);
				}
			}

			return result;
		}

		template<typename T>
		static void fill(std::vector<T>& items, T item, const int count)
		{
			for (int i = 0; i < count; i++)
			{
				items.push_back(item);
			}
		}
	};

	using Vectors = VectorExtensions;
}