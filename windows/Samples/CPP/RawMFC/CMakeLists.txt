add_subdirectory(res)

set(SOURCE_FILES
	RawMFC.h
	RawMFCDlg.h
	RawMFCDlg.cpp
	resource.h
	stdafx.h
	RawMFC.cpp
	RawMFCDlg.cpp
	stdafx.cpp
	RawMFC.rc
	${RES_SOURCE_FILES}
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlgMFC.cpp
)

set(BUILD_FILES
	RawMFC_2019.vcxproj
)

# Declare source groups for Visual Studio project.
source_group("Resource Files" "[_A-Za-z0-9-]+\\.(rc|rc2)")

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)
	set(CMAKE_MFC_FLAG 1) # Use MFC in a static library

	add_executable(IsoSDKRawSampleMFC WIN32 ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKRawSampleMFC PROPERTIES OUTPUT_NAME IsoSDKRawSampleUw)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKRawSampleMFC PROPERTIES OUTPUT_NAME IsoSDKRawSamplew)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKRawSampleMFC PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKRawSampleMFC IsoSDKMFC)

	install(TARGETS IsoSDKRawSampleMFC DESTINATION ${RUNTIME_DESTINATION} COMPONENT IsoSDK)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION Samples/CPP/RawMFC COMPONENT IsoSDK)
install(FILES ${BUILD_FILES} DESTINATION Samples/CPP/RawMFC COMPONENT IsoSDK)
