include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Common
	${CMAKE_CURRENT_BINARY_DIR}/Common
)
if(NOT WIN32)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common/winhdrs)
endif(NOT WIN32)

if(WIN32)
	add_subdirectory(AudioMFC)
	add_subdirectory(DataMFC)
	add_subdirectory(ConsoleBurner)
	add_subdirectory(ImageEditMFC)
	add_subdirectory(RawMFC)
	add_subdirectory(UtilitiesMFC)
	add_subdirectory(VideoMFC)
endif(WIN32)

if(NOT CMAKE_PROJECT_NAME STREQUAL IsoSDK)
	find_package(IsoSDK REQUIRED NO_MODULE)
	include_directories(${IsoSDK_INCLUDE_DIRS})
	if(UNIX AND NOT APPLE)
		add_definitions(-DLINUX)
	endif(UNIX AND NOT APPLE)
	if(APPLE)
		add_definitions(-DMAC)
	endif(APPLE)
	
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif(NOT CMAKE_PROJECT_NAME STREQUAL IsoSDK)

if(APPLE)
	set(OSX_ICON_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../res/isosdk.icns)
endif(APPLE)

add_subdirectory(Common)
add_subdirectory(AudioFOXLib)
add_subdirectory(DataFOXLib)
add_subdirectory(ImageEditFOXLib)
add_subdirectory(RawFOXLib)
add_subdirectory(UtilitiesFOXLib)
add_subdirectory(VideoFOXLib)

install(FILES CMakeLists.txt DESTINATION ${BASE_SAMPLES_DIR}/CPP COMPONENT IsoSDK)
