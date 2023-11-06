set(SOURCE_FILES
	RegionChangeDlg.h
	resource.h
	resources.h
	stdafx.h
	UtilitiesFOXLib.h
	UtilitiesFOXLibDlg.h
	RegionChangeDlg.cpp
	resources.cpp
	stdafx.cpp
	UtilitiesFOXLib.cpp
	UtilitiesFOXLibDlg.cpp
	UtilitiesFOXLib.rc
	UtilitiesFOXLib.rc2
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.cpp
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
	set(BUILD_FILES
		${BUILD_FILES}
		UtilitiesFOXLib_2019.vcxproj
	)
endif(WIN32)

# Declare source groups for Visual Studio project.
source_group("Resource Files" "[_A-Za-z0-9-]+\\.(rc|rc2)")

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)

	add_executable(IsoSDKUtilitiesSample WIN32 MACOSX_BUNDLE
		${SOURCE_FILES}
		${COMMON_SOURCE_FILES}
		${OSX_ICON_FILES}
	)

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKUtilitiesSample PROPERTIES OUTPUT_NAME IsoSDKUtilitiesSampleUc)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKUtilitiesSample PROPERTIES OUTPUT_NAME IsoSDKUtilitiesSamplec)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKUtilitiesSample PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKUtilitiesSample
		FOXToolkit
		IsoSDK
		${X11_LIBRARIES}
	)

	set_target_properties(IsoSDKUtilitiesSample PROPERTIES
		MACOSX_BUNDLE_ICON_FILE isosdk.icns
	)
	set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
	
	install(TARGETS IsoSDKUtilitiesSample
		DESTINATION bin
		BUNDLE DESTINATION "/Applications/IsoSDK"
	)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/UtilitiesFOXLib COMPONENT IsoSDK_FOXToolkit)
install(FILES ${BUILD_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/UtilitiesFOXLib COMPONENT IsoSDK_FOXToolkit)
