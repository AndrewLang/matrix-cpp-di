#include "gtest/gtest.h"
#include "linux/LinuxEnvironmentInfo.h"
#include "common/StringExtensions.h"
#include "logging/ConsoleLogger.h"
#include "logging/ILogger.h"

#include <memory>

namespace Matrix
{
    TEST(LinuxEnvironmentInfoTests, Constructor) {
		LinuxEnvironmentInfo info;
	}

    TEST(LinuxEnvironmentInfoTests, GetInfo) {
		LinuxEnvironmentInfo info;


        std::shared_ptr<ILogger> logger = std::make_shared<ConsoleLogger>("LinuxEnvironmentInfoTests");

        logger->debug(N("System name"), info.sysName)
                .debug(N("Node name"), info.nodeName)
                .debug(N("Release"), info.release)
                .debug(N("Version"), info.version)
                .debug(N("Machine"), info.machine)
                .debug(N("Report"), info.report);


        ASSERT_FALSE(Strings::isNullOrEmpty(info.sysName));
        ASSERT_FALSE(Strings::isNullOrEmpty(info.nodeName));
        ASSERT_FALSE(Strings::isNullOrEmpty(info.release));
        ASSERT_FALSE(Strings::isNullOrEmpty(info.version));
        ASSERT_FALSE(Strings::isNullOrEmpty(info.machine));
        ASSERT_FALSE(Strings::isNullOrEmpty(info.report));
	}
}