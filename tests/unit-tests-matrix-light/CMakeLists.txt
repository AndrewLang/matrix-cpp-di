

project(unittests-matrix-light)


include_directories(
	${CMAKE_SOURCE_DIR}/src/matrix-light/Include
	${CMAKE_SOURCE_DIR}/tests/unit-tests-matrix-light
	${CMAKE_SOURCE_DIR}/tests/unit-tests-matrix-light/include
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
	include/MockServiceProvider.h
	include/MockServiceContainer.h
	include/platformCheckMacros.h
	include/Rectangle.h
	include/Shape.h
	include/TestFiles.h
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
	src/MockServiceProvider.cpp
	src/MockServiceContainer.cpp
	src/Rectangle.cpp
	src/Shape.cpp
	src/TestFiles.cpp
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
	tests/logging/VsOutputLogger.cpp
	tests/logging/VsOutputLoggerProviderTests.cpp

	
	tests/pipeline/PipelineBlockTests.cpp
	tests/pipeline/PipelineBuilderTests.cpp
	tests/pipeline/PipelineContextTests.cpp
	tests/pipeline/PipelineTests.cpp
	
	tests/services/DataContextTests.cpp
	
	tests/task/DoTests.cpp
	tests/task/DoWithResultTests.cpp
	tests/task/TaskTests.cpp
	tests/task/TaskWithResultTests.cpp
	
	#[[]]
)





add_executable (${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})

# Include sub-projects.

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main matrix-light)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
