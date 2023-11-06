add_subdirectory(res)

set(SOURCE_FILES
	ChangeRegionDlg.h
	DeviceInfoDlg.h
	DeviceInfoEx.h
	DiscCopyDlg.h
	GetCapa.h
	ImageCreationDlg.h
	MediumInfo.h
	resource.h
	StdAfx.h
	UtilitiesMFC.h
	UtilitiesMFCDlg.h
	ChangeRegionDlg.cpp
	DeviceInfoDlg.cpp
	DeviceInfoEx.cpp
	DiscCopyDlg.cpp
	GetCapa.cpp
	ImageCreationDlg.cpp
	MediumInfo.cpp
	StdAfx.cpp
	UtilitiesMFC.cpp
	UtilitiesMFCDlg.cpp
	UtilitiesMFC.rc
	${RES_SOURCE_FILES}
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlgMFC.h
)

set(BUILD_FILES
	UtilitiesMFC_2019.vcxproj
)

# Declare source groups for Visual Studio project.
source_group("Resource Files" "[_A-Za-z0-9-]+\\.(rc|rc2)")

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)
	set(CMAKE_MFC_FLAG 1) # Use MFC in a static library

	add_executable(IsoSDKUtilitiesSampleMFC WIN32 ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKUtilitiesSampleMFC PROPERTIES OUTPUT_NAME IsoSDKUtilitiesSampleUw)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKUtilitiesSampleMFC PROPERTIES OUTPUT_NAME IsoSDKUtilitiesSamplew)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKUtilitiesSampleMFC PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKUtilitiesSampleMFC IsoSDKMFC)

	install(TARGETS IsoSDKUtilitiesSampleMFC DESTINATION ${RUNTIME_DESTINATION} COMPONENT IsoSDK)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION Samples/CPP/UtilitiesMFC COMPONENT IsoSDK)
install(FILES ${BUILD_FILES} DESTINATION Samples/CPP/UtilitiesMFC COMPONENT IsoSDK)
