#pragma once

namespace Matrix
{
	class CancellationToken
	{
	public:
		CancellationToken();

		~CancellationToken();

		bool isCancellationRequested();

		void cancel();
	};
	
}