set(SOURCE_FILES
	BootImageDlg.h
	DataFOXLib.h
	DataFOXLibDlg.h
	DateTime.h
	HeaderDlg.h
	PropertiesDlg.h
	resource.h
	resources.h
	SessionDlg.h
	stdafx.h
	BootImageDlg.cpp
	DataFOXLib.cpp
	DataFOXLibDlg.cpp
	HeaderDlg.cpp
	PropertiesDlg.cpp
	resources.cpp
	SessionDlg.cpp
	stdafx.cpp
	DataFOXLib.rc
	DataFOXLib.rc2
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FileTreeFoxLib.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/Rule.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlg.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FileTreeFoxLib.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/Rule.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlg.cpp
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
		DataFOXLib_2019.vcxproj
)
endif(WIN32)

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)

	add_executable(IsoSDKDataSample WIN32 MACOSX_BUNDLE
		${SOURCE_FILES}
		${COMMON_SOURCE_FILES}
		${OSX_ICON_FILES}
	)

	target_link_libraries(IsoSDKDataSample
		FOXToolkit
		IsoSDK
		${X11_LIBRARIES}
	)

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKDataSample PROPERTIES OUTPUT_NAME IsoSDKDataSampleUc)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKDataSample PROPERTIES OUTPUT_NAME IsoSDKDataSamplec)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKDataSample PROPERTIES DEBUG_POSTFIX _dbg)

	set_target_properties(IsoSDKDataSample PROPERTIES
		MACOSX_BUNDLE_ICON_FILE isosdk.icns
	)
	set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

	install(TARGETS IsoSDKDataSample
		DESTINATION bin
		BUNDLE DESTINATION "/Applications/IsoSDK"
	)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/DataFOXLib COMPONENT IsoSDK_FOXToolkit)
install(FILES ${BUILD_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/DataFOXLib COMPONENT IsoSDK_FOXToolkit)
