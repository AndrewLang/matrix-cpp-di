#include "TestFiles.h"
#include "platformCheckMacros.h"
#include <filesystem>

namespace fs = std::filesystem;

#if defined(PLATFORM_OS_WINDOWS)
#define SLN_PATH "..\\"
#define Separator "\\"
#elif defined(PLATFORM_OS_LINUX)
#define SLN_PATH "../"
#define Separator "/"
#else
// #error not supported
#endif

string TestFiles::getConfiguration()
{
	return getFilePath("configuration.ini");
}

string TestFiles::get9030A()
{
	return getFilePath("IoMS9030A.ini");
}

string TestFiles::getSimulate()
{
	return getFilePath("PxiSimulate.ini");
}

string TestFiles::getTempFolder()
{
	return ((string)SLN_PATH).append("tests").append(Separator).append("temp").append(Separator);
}

string TestFiles::getCurrentPath()
{
	return fs::current_path().string();
}

string TestFiles::notExistsFile()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/not-exist.txt");
}

string TestFiles::folder()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files");
}

string TestFiles::notExistsFolder()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/not-exist");
}

string TestFiles::rootFolder()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light");
}

string TestFiles::getIniFileFolder()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/ini");
}

string TestFiles::getLockFile()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/lock.ini" );
}

string TestFiles::getFilePath(string name)
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/" + name);
}

string TestFiles::getPxieGenericDriver()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/Drivers/ioPXIePMD.dll");
}

string TestFiles::getPxieSimulatePeripheralModuleDriver()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/Drivers/IoPXIePMD_Sim.dll");
}

string TestFiles::getPxieChassisDriver()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/Drivers/IoPXIeCDu_Sim.dll");
}

string TestFiles::getPxieChassisDesFileFolder() {
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/Chassis");
}

string TestFiles::getChassis9020ADescFile() {
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/Chassis/IoMS9020A.ini");
}

string TestFiles::getSystemModuleDriver()
{
	return ((string)SLN_PATH).append("tests/unit-tests-matrix-light/files/Drivers/IoPXIeSMu_Sim.dll");
}
