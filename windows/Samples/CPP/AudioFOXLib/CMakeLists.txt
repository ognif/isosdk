set(SOURCE_FILES
	AudioFOXLib.h
	AudioFOXLibDlg.h
	CDTextDlg.h
	CDTimeRule.h
	resource.h
	resources.h
	stdafx.h
	TrackList.h
	AudioFOXLib.cpp
	AudioFOXLibDlg.cpp
	CDTextDlg.cpp
	CDTimeRule.cpp
	resources.cpp
	stdafx.cpp
	TrackList.cpp
	AudioFOXLib.rc
	AudioFOXLib.rc2
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FileTreeFoxLib.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlg.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FileTreeFoxLib.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.cpp
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
		AudioFOXLib_2019.vcxproj
	)
endif(WIN32)

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)

	add_executable(IsoSDKAudioSample WIN32 MACOSX_BUNDLE
		${SOURCE_FILES}
		${COMMON_SOURCE_FILES}
		${OSX_ICON_FILES}
	)
	target_link_libraries(IsoSDKAudioSample
		FOXToolkit
		IsoSDK
		${X11_LIBRARIES}
	)

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKAudioSample PROPERTIES OUTPUT_NAME IsoSDKAudioSampleUc)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKAudioSample PROPERTIES OUTPUT_NAME IsoSDKAudioSamplec)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKAudioSample PROPERTIES DEBUG_POSTFIX _dbg)

	set_target_properties(IsoSDKAudioSample PROPERTIES
		MACOSX_BUNDLE_ICON_FILE isosdk.icns
	)
	set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

	install(TARGETS IsoSDKAudioSample
		DESTINATION bin
		BUNDLE DESTINATION "/Applications/IsoSDK"
	)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/AudioFOXLib COMPONENT IsoSDK_FOXToolkit)
install(FILES ${BUILD_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/AudioFOXLib COMPONENT IsoSDK_FOXToolkit)
