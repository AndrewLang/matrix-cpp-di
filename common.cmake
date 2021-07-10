

# header files
SET(HeaderFiles 
	pch.h	
	
	include/common/ArgumentNullException.h
	include/common/BaseException.h
	include/common/FileLoadException.h
	include/common/FileNotExistsException.h
	include/common/Guard.h
	include/common/MapValueDescriptor.h
	include/common/MapExtensions.h
	include/common/ObjectMap.h
	include/common/Platform.h
	include/common/Stopwatch.h
	include/common/StringExtensions.h	
	include/common/TextFormatter.h
	include/common/VectorExtensions.h

	include/configuration/ConfigurationBuilder.h
	include/configuration/ConfigurationProvider.h
	include/configuration/ConfigurationRoot.h
	include/configuration/FileConfigurationProvider.h
	include/configuration/IConfiguration.h
	include/configuration/IConfigurationBuilder.h
	include/configuration/IConfigurationProvider.h
	include/configuration/IConfigurationRoot.h
	include/configuration/IConfigurationSaver.h
	include/configuration/IniConfigurationProvider.h
	include/configuration/MemoryConfigurationProvider.h

	include/di/ApplicationBase.h
	include/di/ApplicationBuilder.h
	include/di/ApplicationStartBlock.h
	include/di/ApplicationStartBlockContext.h
	include/di/ComponentBase.h
	include/di/IApplication.h
	include/di/IApplicationBuilder.h
	include/di/IApplicationStartBlock.h
	include/di/IComponent.h
	include/di/InstanceCreatorContext.h
	include/di/InstanceDescriptor.h
	include/di/IServiceContainer.h
	include/di/IServiceProvider.h
	include/di/ServiceContainer.h
	include/di/ServiceDescriptor.h
	include/di/ServiceLifetime.h
	include/di/TypeInfo.h
	include/di/TypeMap.h

	include/io/Directory.h
	include/io/DirectoryInfo.h
	include/io/File.h
	include/io/FileInfo.h
	include/io/FileStream.h
	include/io/FileSystemInfo.h
	include/io/FileWatcher.h
	include/io/Process.h


	include/logging/ConsoleLogger.h
	include/logging/ConsoleLoggerProvider.h
	include/logging/ILogger.h
	include/logging/ILoggerFactory.h
	include/logging/ILoggerProvider.h
	include/logging/InternalLogger.h
	include/logging/LoggerBase.h
	include/logging/LoggerFactory.h
	include/logging/LogLevelConverter.h
	include/logging/LogMessageName.h
	include/logging/OsAbstractionLogger.h
	include/logging/OsAbstractionLoggerProvider.h
	include/logging/VsOutput.h
	include/logging/VsOutputLogger.h
	include/logging/VsOutputLoggerProvider.h

	include/pipeline/IPipeline.h
	include/pipeline/IPipelineBlock.h
	include/pipeline/IPipelineBuilder.h
	include/pipeline/Pipeline.h
	include/pipeline/PipelineBlock.h
	include/pipeline/PipelineBuilder.h
	include/pipeline/PipelineContext.h

	include/services/AppStartBlockProvider.h
	include/services/ChassisInfoUpdater.h
	include/services/DataContext.h
	include/services/DataProcessor.h
	include/services/DriverFileLoader.h
	include/services/EnumServerApplicationBuilder.h
	include/services/IAppStartBlockProvider.h
	include/services/IDataEnumerator.h
	include/services/IDataProcessor.h
	include/services/IDataWriter.h
	include/services/IDriverLoader.h
	include/services/IEnvironmentInfo.h
	include/services/IEnvironmentProfile.h
	include/services/IFileLocker.h
	include/services/IPathResolver.h
	include/services/IPciEnumerator.h
	include/services/IPxiInfoTreeLoader.h
	include/services/ResourceManagerApplicationBuilder.h

	include/task/CancellationToken.h
	include/task/Do.h
	include/task/DoWithResult.h
	include/task/Task.h
	include/task/TaskWithResult.h	
)


# source files
SET(SourceFiles 
	pch.cpp
	
	src/common/ArgumentNullException.cpp
	src/common/BaseException.cpp
	src/common/FileLoadException.cpp
	src/common/FileNotExistsException.cpp
	src/common/Guard.cpp
	src/common/Platform.cpp
	src/common/Stopwatch.cpp
	src/common/StringExtensions.cpp
	src/common/TextFormatter.cpp

	src/configuration/ConfigurationBuilder.cpp
	src/configuration/ConfigurationProvider.cpp
	src/configuration/ConfigurationRoot.cpp
	src/configuration/IniConfigurationProvider.cpp
	src/configuration/MemoryConfigurationProvider.cpp

	src/di/ApplicationBase.cpp
	src/di/ApplicationBuilder.cpp
	src/di/ApplicationStartBlock.cpp
	src/di/ApplicationStartBlockContext.cpp
	src/di/ComponentBase.cpp
	src/di/InstanceCreatorContext.cpp
	src/di/InstanceDescriptor.cpp
	src/di/ServiceContainer.cpp
	src/di/ServiceDescriptor.cpp
	src/di/TypeInfo.cpp
	src/di/TypeMap.cpp

	src/io/Directory.cpp
	src/io/DirectoryInfo.cpp
	src/io/File.cpp
	src/io/FileInfo.cpp
	src/io/FileStream.cpp
	src/io/FileSystemInfo.cpp
	src/io/FileWatcher.cpp
	src/io/Process.cpp

	src/logging/ConsoleLogger.cpp
	src/logging/ConsoleLoggerProvider.cpp
	src/logging/InternalLogger.cpp
	src/logging/LoggerBase.cpp
	src/logging/LoggerFactory.cpp
	src/logging/LogLevelConverter.cpp
	src/logging/OsAbstractionLogger.cpp
	src/logging/OsAbstractionLoggerProvider.cpp
	src/logging/VsOutput.cpp
	src/logging/VsOutputLogger.cpp
	src/logging/VsOutputLoggerProvider.cpp


	src/pipeline/Pipeline.cpp
	src/pipeline/PipelineBlock.cpp
	src/pipeline/PipelineBuilder.cpp
	src/pipeline/PipelineContext.cpp
	
	src/services/AppStartBlockProvider.cpp

	src/task/CancellationToken.cpp
	src/task/Task.cpp
	src/task/TaskWithResult.cpp
)

if(WIN32)
	list(APPEND SourceFiles 
		
	)

	list(APPEND HeaderFiles
		
	)
else ()
	list(APPEND SourceFiles		
		
	)

	list(APPEND HeaderFiles
		
	)
endif()