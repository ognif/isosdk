set(SOURCE_FILES
	consoleburner.cpp
	stdafx.cpp
	stdafx.h
	synclib.h
)

if(UNIX AND NOT APPLE)
if(${CMAKE_CXX_COMPILER_VERSION} GREATER 5)
    message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -no-pie")
endif(${CMAKE_CXX_COMPILER_VERSION} GREATER 5)
endif(UNIX AND NOT APPLE)


set(BUILD_FILES CMakeLists.txt)

if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
	set(BUILD_FILES
		${BUILD_FILES}
		ConsoleBurner_2019.vcxproj
	)
endif(WIN32)

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

	add_executable(IsoSDKConsole WIN32 MACOSX_BUNDLE
		${SOURCE_FILES}
		${OSX_ICON_FILES}
	)
	target_link_libraries(IsoSDKConsole
		FOXToolkit
		IsoSDK
		${X11_LIBRARIES}
	)

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKConsole PROPERTIES OUTPUT_NAME IsoSDKConsoleUc)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKConsole PROPERTIES OUTPUT_NAME IsoSDKConsolec)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKConsole PROPERTIES DEBUG_POSTFIX _dbg)

	set_target_properties(IsoSDKConsole PROPERTIES
		MACOSX_BUNDLE_ICON_FILE isosdk.icns
	)
	set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

	install(TARGETS IsoSDKConsole
		DESTINATION bin
		BUNDLE DESTINATION "/Applications/IsoSDK"
	)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/ConsoleBurner COMPONENT IsoSDK_FOXToolkit)
install(FILES ${BUILD_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/ConsoleBurner COMPONENT IsoSDK_FOXToolkit)
