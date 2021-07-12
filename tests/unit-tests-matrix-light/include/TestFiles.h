#pragma once
#include <string>

using std::string;

class TestFiles
{
public:
	string getConfiguration();
	string get9030A();
	string getSimulate();
	string getTempFolder();
	string getCurrentPath();
	string notExistsFile();
	string folder();
	string notExistsFolder();
	string rootFolder();
	string getPxisaFolder();
	string getLockFile();

	string getFilePath(string name);

	string getPxieGenericDriver();
	string getPxieSimulatePeripheralModuleDriver();
	string getPxieChassisDriver();
	string getPxieChassisDesFileFolder();
	string getChassis9020ADescFile();
	string getSystemModuleDriver();
};

