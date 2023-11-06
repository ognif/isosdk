if(WIN32)
	
	set(BASE_SAMPLES_DIR Samples)
elseif(APPLE)
	set(BASE_SAMPLES_DIR /Users/Shared/IsoSDK/Samples)
else(WIN32)
	set(BASE_SAMPLES_DIR share/IsoSDK/Samples)
endif(WIN32)

if(NOT BUILD_TYPE STREQUAL "DotNet")
	add_subdirectory(CPP)
	if(CMAKE_PROJECT_NAME STREQUAL IsoSDK)
		add_subdirectory(res)
	endif(CMAKE_PROJECT_NAME STREQUAL IsoSDK)
else(NOT BUILD_TYPE STREQUAL "DotNet")
	add_subdirectory(CSharp)
endif(NOT BUILD_TYPE STREQUAL "DotNet")

install(FILES CMakeLists.txt DESTINATION ${BASE_SAMPLES_DIR} COMPONENT IsoSDK)
