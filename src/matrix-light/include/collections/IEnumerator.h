#pragma once

namespace Matrix
{
	template<class T>
	class IEnumerator
	{
	public:
		virtual ~IEnumerator(){}
		virtual int getCurrent() const = 0;
		virtual bool moveNext() = 0;
		virtual void reset() = 0;
	protected:
		IEnumerator();
	};
}