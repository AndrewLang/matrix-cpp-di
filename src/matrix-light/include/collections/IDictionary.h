#pragma once

namespace Matrix
{
	template<class TKey, class TValue>
	class IDictionary
	{
	public:
		virtual ~IDictionary() {}

		virtual int count() const = 0;

	protected:
		IDictionary();
	};
}