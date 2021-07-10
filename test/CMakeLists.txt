

project(unittests-rm-common)


include_directories(
	${CMAKE_SOURCE_DIR}/src/pxi-resource-manager-common/Include
	${CMAKE_SOURCE_DIR}/tests/unit-tests-pxirm-common
	${CMAKE_SOURCE_DIR}/tests/unit-tests-pxirm-common/include
	${CMAKE_SOURCE_DIR}/../../../../os_abstraction/OsAbstraction	
	${CMAKE_SOURCE_DIR}/../../../../os_abstraction/OsAbstraction/Logging
)

set (HeaderFiles 
	pch.h
	main.h

	include/ApiHandleComponent.h
	include/ApiHandler.h
	

	include/IApiHandler.h
	include/InitializeComponent.h
	include/LoggerCreator.h
	include/MockApplication.h
	include/MockPathResolver.h
	include/MockPeripheralModuleRegistryLoader.h
	include/MockPxiChassisRegistryLoader.h
	include/MockServiceContainer.h
	include/MockServiceProvider.h
	include/MockSystemModuleRegistryLoader.h
	include/platformCheckMacros.h
	include/Rectangle.h
	include/Shape.h
	include/TestFiles.h
	include/TestRuntimeProfile.h
	include/TestServices.h
	
)

set (SourceFiles 
	pch.cpp
	main.cpp
			
	src/ApiHandleComponent.cpp
	src/ApiHandler.cpp
	src/IApiHandler.cpp
	src/Circle.cpp	
	src/InitializeComponent.cpp
	src/LoggerCreator.cpp
	src/MockApplication.cpp
	src/MockPathResolver.cpp
	src/MockPeripheralModuleRegistryLoader.cpp
	src/MockPxiChassisRegistryLoader.cpp
	src/MockServiceContainer.cpp
	src/MockServiceProvider.cpp
	src/MockSystemModuleRegistryLoader.cpp
	src/Rectangle.cpp
	src/Shape.cpp
	src/TestFiles.cpp
	src/TestRuntimeProfile.cpp
	src/TestServices.cpp
	
	

	tests/common/ArgumentNullExceptionTests.cpp
	tests/common/GuardTests.cpp
	tests/common/ObjectMapTests.cpp
	tests/common/MapExtensionsTests.cpp
	tests/common/StopwatchTests.cpp
	tests/common/StringExtensionsTests.cpp
	tests/common/TextFormatterTests.cpp
	tests/common/VectorExtensionsTests.cpp

	tests/configuration/ConfigurationBuilderTests.cpp
	tests/configuration/ConfigurationRootTests.cpp
	tests/configuration/IniConfigurationProviderTests.cpp
	tests/configuration/MemoryConfigurationProviderTests.cpp

	tests/di/ApplicationBuilderTests.cpp
	tests/di/ApplicationStartBlockTests.cpp
	tests/di/ApplicationTests.cpp
	tests/di/InstanceCreatorContextTests.cpp
	tests/di/ServiceContainerTests.cpp
	tests/di/ServiceDescriptorTests.cpp
	tests/di/ServiceLifetimeTests.cpp
	tests/di/TypeInfoTests.cpp
	tests/di/TypeMapTests.cpp

	tests/io/DirectoryInfoTests.cpp
	tests/io/DirectoryTests.cpp
	tests/io/FileInfoTests.cpp	
	tests/io/FileStreamTests.cpp
	tests/io/FileTests.cpp
	tests/io/FileWatcherTests.cpp
	tests/io/ProcessTests.cpp

	tests/logging/ConsoleLoggerProviderTests.cpp
	tests/logging/ConsoleLoggerTests.cpp
	tests/logging/InternalLoggerTests.cpp
	tests/logging/LoggerFactoryTests.cpp
	tests/logging/LogLevelConverterTests.cpp
	tests/logging/OsAbstractionLoggerProviderTests.cpp
	tests/logging/OsAbstractionLoggerTests.cpp
	tests/logging/VsOutputLogger.cpp
	tests/logging/VsOutputLoggerProviderTests.cpp

	tests/models/ChassisEepromTests.cpp
	tests/models/DeviceInfoTests.cpp
	tests/models/ModelExtensionsTests.cpp
	tests/models/PxiAddressTests.cpp
	tests/models/PxiChassisTests.cpp
	tests/models/PxiPeripheralModuleDriverTests.cpp
	tests/models/PxiPeripheralModuleTests.cpp
	tests/models/PxiSystemModuleTests.cpp

	tests/pipeline/PipelineBlockTests.cpp
	tests/pipeline/PipelineBuilderTests.cpp
	tests/pipeline/PipelineContextTests.cpp
	tests/pipeline/PipelineTests.cpp

	tests/services/ChassisInfoUpdaterTests.cpp
	tests/services/DataContextTests.cpp
	tests/services/EnumServerApplicationBuilderTests.cpp
	tests/services/ResourceManagerApplicationBuilderTests.cpp
	
	tests/task/DoTests.cpp
	tests/task/DoWithResultTests.cpp
	tests/task/TaskTests.cpp
	tests/task/TaskWithResultTests.cpp
	
	#[[]]
)


if(WIN32)
	# append windows tests
	list(APPEND  SourceFiles  
		tests/windows/PeripheralModuleRegistryLoaderTests.cpp
		tests/windows/PxiChassisRegistryLoaderTests.cpp
		tests/windows/RegistryKeyTests.cpp
		tests/windows/SystemModuleRegistryLoaderTests.cpp
		tests/windows/WinAxieChassisEnumeratorTests.cpp
		tests/windows/WinDataEnumerateComponentTests.cpp
		tests/windows/WinConfigurationLoaderTests.cpp
		tests/windows/WinDataProcessComponentTests.cpp
		tests/windows/WinDataWriterComponentTests.cpp
		tests/windows/WinEnumServerAppTests.cpp
		tests/windows/WinEnumServerBlockProviderTests.cpp
		tests/windows/WinEnvironmentInfoTests.cpp
		tests/windows/WinPathResolverTests.cpp
		tests/windows/WinPciEnumeratorTests.cpp
		tests/windows/WinPeripheralModuleDriverLoaderTests.cpp
		tests/windows/WinPxieChassisDriverLoaderTests.cpp
		tests/windows/WinPxieChassisEnumeratorTests.cpp
		tests/windows/WinPxiePeripheralModuleEnumeratorTests.cpp
		tests/windows/WinPxiePeripheralModuleEnumeratorWithServerTests.cpp
		tests/windows/WinResourceManagerAppTests.cpp
		tests/windows/WinRuntimeProfileTests.cpp
		tests/windows/WinStartBlockProviderTests.cpp
		tests/windows/WinSystemModuleDriverLoaderTests.cpp
		tests/windows/WinSystemModuleEnumeratorTests.cpp

		tests/io/FileLockerTests.cpp

		tests/services/ChassisInfoUpdaterTestsWin.cpp

		src/WinPciEnumeratorTester.cpp
		src/MockWinPxiePeripheralModuleEnumerator.cpp
	)

	list(APPEND HeaderFiles 
		include/WinPciEnumeratorTester.h
		include/MockWinPxiePeripheralModuleEnumerator.h
	)

else()
	list(APPEND  SourceFiles  		
		tests/linux/LinuxEnvironmentInfoTests.cpp
		tests/linux/LinuxResourceManagerTests.cpp
	)
endif()

add_executable (${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})

# Include sub-projects.

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main pxi-resource-manager-common)


if(WIN32)
	# set(CMAKE_CXX_FLAGS "-m32")

	# link to OsAbstraction 
		
	IF(BINARY_BITS EQUAL 64)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../../../os_abstraction/OsAbstraction/x64/${CMAKE_BUILD_TYPE}/OsAbstraction.lib)
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../../../os_abstraction/OsAbstraction/Win32/${CMAKE_BUILD_TYPE}/OsAbstraction.lib)
	endif()
	#[[]]
	

	# Link to Setupapi
	find_library(SETUP_API setupapi)
	
	target_link_libraries(${PROJECT_NAME} PUBLIC ${SETUP_API})
else ()
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../../../os_abstraction/cmake_build/x64/debug/bin/libOsAbstraction.so )	
endif()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
