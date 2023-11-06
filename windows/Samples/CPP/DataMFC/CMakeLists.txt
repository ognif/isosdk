add_subdirectory(res)

set(SOURCE_FILES
	BootOptions.h
	DataMFC.h
	DataMFCDlg.h
	ExtInfos.h
	MultiSession.h
	PropertiesDlg.h
	resource.h
	StdAfx.h
	BootOptions.cpp
	DataMFC.cpp
	DataMFCDlg.cpp
	ExtInfos.cpp
	MultiSession.cpp
	PropertiesDlg.cpp
	StdAfx.cpp
	DataMFC.rc
	${RES_SOURCE_FILES}
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FolderPickerDialog.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FileTree.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KCreateFolderDlg.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/LegacyFolderPickerDialog.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SizeRange.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FolderPickerDialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/FileTree.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KCreateFolderDlg.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/LegacyFolderPickerDialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SampleBurnDlgMFC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/SizeRange.cpp
)

if(MSVC_VERSION GREATER 1500)
	set(COMMON_SOURCE_FILES
		${COMMON_SOURCE_FILES}
		${CMAKE_CURRENT_SOURCE_DIR}/../Common/VistaFolderPickerDialog.h
		${CMAKE_CURRENT_SOURCE_DIR}/../Common/VistaFolderPickerDialog.cpp
	)
endif(MSVC_VERSION GREATER 1500)

set(BUILD_FILES
	DataMFC_2019.vcxproj
)

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)
	set(CMAKE_MFC_FLAG 1) # Use MFC in a static library

	add_executable(IsoSDKDataSampleMFC WIN32 ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKDataSampleMFC PROPERTIES OUTPUT_NAME IsoSDKDataSampleUw)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKDataSampleMFC PROPERTIES OUTPUT_NAME IsoSDKDataSamplew)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKDataSampleMFC PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKDataSampleMFC IsoSDKMFC)

	install(TARGETS IsoSDKDataSampleMFC DESTINATION ${RUNTIME_DESTINATION} COMPONENT IsoSDK)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION Samples/CPP/DataMFC COMPONENT IsoSDK)
install(FILES ${BUILD_FILES} DESTINATION Samples/CPP/DataMFC COMPONENT IsoSDK)
