#include "io/Process.h"
#include "common/Guard.h"


namespace Matrix
{
	using namespace std;

	Process::Process(string fileName, string arguments)
		: mFileName(fileName)
        , mArguments(arguments)
	{
		//mInnerProcess = std::make_shared<OsProcess>(mFileName, mArguments);
	}

	Process::~Process()
	{
		terminate();
	}
	
	Process& Process::start()
	{

		return *this;
	}

	bool Process::wait(int milliseconds)
	{
		/*if (mInnerProcess)
		{
			auto result = mInnerProcess->wait(milliseconds);

			return result == SynchronizationResult::Success;
		}*/

		return false;
	}

	void Process::terminate()
	{
		/*if (mInnerProcess && isRunning())
			mInnerProcess->terminate();*/
	}

	string Process::fileName()
	{
		return mFileName;
	}

	string Process::arguments()
	{
		return mArguments;
	}

	int Process::getId()
	{
		/*if (mInnerProcess)
			return mInnerProcess->getId();*/

		return -1;
	}

	int Process::getExitCode()
	{
		/*if (mInnerProcess)
			return mInnerProcess->getExitCode();*/

		return -1;
	}

	bool Process::isRunning()
	{
		/*if (mInnerProcess)
			return mInnerProcess->isRunning();*/

		return false;
	}
}