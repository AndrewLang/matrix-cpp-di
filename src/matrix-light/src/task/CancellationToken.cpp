#include "task/CancellationToken.h"

namespace Matrix
{
	CancellationToken::CancellationToken()
	{
	}


	CancellationToken::~CancellationToken()
	{
	}
	bool CancellationToken::isCancellationRequested()
	{
		return false;
	}
	void CancellationToken::cancel()
	{
	}
}
