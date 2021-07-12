#pragma once 


#include <string>
#include <memory>

namespace Matrix
{
	class Process
	{
	public:		
		Process(std::string fileName, std::string arguments = "");
		
		~Process();

		Process& start();

		bool wait(int milliseconds = -1);

		void terminate();

		std::string fileName();

		std::string arguments();

		int getId();

		int getExitCode();

		bool isRunning();

	private:
		std::string mFileName;
		std::string mArguments;

		//std::shared_ptr<OsAbstraction::OsProcess> mInnerProcess;
	};

}