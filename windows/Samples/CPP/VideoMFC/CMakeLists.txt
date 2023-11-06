add_subdirectory(res)

set(SOURCE_FILES
	resource.h
	ScanDlg.h
	StdAfx.h
	VideoMFC.h
	VideoMFCDlg.h
	ScanDlg.cpp
	StdAfx.cpp
	VideoMFC.cpp
	VideoMFCDlg.cpp
	VideoMFC.rc
	${RES_SOURCE_FILES}
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SizeRange.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlgMFC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SizeRange.cpp
)

set(BUILD_FILES
	VideoMFC_2019.vcxproj
)

# Declare source groups for Visual Studio project.
source_group("Resource Files" "[_A-Za-z0-9-]+\\.(rc|rc2)")

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)
	set(CMAKE_MFC_FLAG 1) # Use MFC in a static library

	add_executable(IsoSDKVideoSampleMFC WIN32 ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKVideoSampleMFC PROPERTIES OUTPUT_NAME IsoSDKVideoSampleUw)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKVideoSampleMFC PROPERTIES OUTPUT_NAME IsoSDKVideoSamplew)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKVideoSampleMFC PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKVideoSampleMFC IsoSDKMFC)

	install(TARGETS IsoSDKVideoSampleMFC DESTINATION ${RUNTIME_DESTINATION} COMPONENT IsoSDK)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION Samples/CPP/VideoMFC COMPONENT IsoSDK)
install(FILES ${BUILD_FILES} DESTINATION Samples/CPP/VideoMFC COMPONENT IsoSDK)
