add_subdirectory(md5)

set(SOURCE_FILES
	AudioGrabbingDialog.h
	AudioTrackPlayingDialog.h
	ImageEditFOXLib.h
	ImageEditFOXLibDlg.h
	Logging.h
	md5Dialog.h
	PropertiesDlg.h
	ReadCDTextDlg.h
	resource.h
	resources.h
	SaveContentDialog.h
	SaveDiscDialog.h
	SaveTrackDialog.h
	ScanSectorsDialog.h
	SectorViewDialog.h
	stdafx.h
	TreeNodes.h
	AudioGrabbingDialog.cpp
	AudioTrackPlayingDialog.cpp
	ImageEditFOXLib.cpp
	ImageEditFOXLibDlg.cpp
	md5Dialog.cpp
	PropertiesDlg.cpp
	ReadCDTextDlg.cpp
	resources.cpp
	SaveContentDialog.cpp
	SaveDiscDialog.cpp
	SaveTrackDialog.cpp
	ScanSectorsDialog.cpp
	SectorViewDialog.cpp
	stdafx.cpp
	TreeNodes.cpp
	ImageEditFOXLib.rc
	ImageEditFOXLib.rc2
	${MD5_SOURCE_FILES}
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/Sector2Text.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlg.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/Sector2Text.cpp
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
		ImageEditFOXLib_2019.vcxproj
	)
endif(WIN32)

# Declare source groups for Visual Studio project.
source_group("Resource Files" "[_A-Za-z0-9-]+\\.(rc|rc2)")
source_group("MD5" "md5/[_A-Za-z0-9-]+\\.(h|cpp|c|idl)")

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)

	add_executable(IsoSDKImageEditSample WIN32 MACOSX_BUNDLE
		${SOURCE_FILES}
		${COMMON_SOURCE_FILES}
		${OSX_ICON_FILES}
	)

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKImageEditSample PROPERTIES OUTPUT_NAME IsoSDKImageEditSampleUc)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKImageEditSample PROPERTIES OUTPUT_NAME IsoSDKImageEditSamplec)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKImageEditSample PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKImageEditSample
		FOXToolkit
		IsoSDK
		${X11_LIBRARIES}
	)

	if(APPLE)
		add_definitions(-DOPENSSL_NO_ASM)
	endif(APPLE)

	set_target_properties(IsoSDKDataSample PROPERTIES
		MACOSX_BUNDLE_ICON_FILE isosdk.icns
	)

	set_target_properties(IsoSDKImageEditSample PROPERTIES
		MACOSX_BUNDLE_ICON_FILE isosdk.icns
	)
	set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
	
	install(TARGETS IsoSDKImageEditSample
		DESTINATION bin
		BUNDLE DESTINATION "/Applications/IsoSDK"
	)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/ImageEditFOXLib COMPONENT IsoSDK_FOXToolkit)
install(FILES ${BUILD_FILES} DESTINATION ${BASE_SAMPLES_DIR}/CPP/ImageEditFOXLib COMPONENT IsoSDK_FOXToolkit)
