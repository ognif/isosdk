add_subdirectory(res)

set(SOURCE_FILES
	AudioMFC.h
	AudioMFCDlg.h
	CDTextDlg.h
	resource.h
	StdAfx.h
	TrackList.h
	AudioMFC.cpp
	AudioMFCDlg.cpp
	CDTextDlg.cpp
	StdAfx.cpp
	TrackList.cpp
	AudioMFC.rc
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
	AudioMFC_2019.vcxproj
)

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)
	set(CMAKE_MFC_FLAG 1) # Use MFC in a static library

	add_executable(IsoSDKAudioSampleMFC WIN32 ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKAudioSampleMFC PROPERTIES OUTPUT_NAME IsoSDKAudioSampleUw)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKAudioSampleMFC PROPERTIES OUTPUT_NAME IsoSDKAudioSamplew)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKAudioSampleMFC PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKAudioSampleMFC IsoSDKMFC)

	install(TARGETS IsoSDKAudioSampleMFC DESTINATION ${RUNTIME_DESTINATION} COMPONENT IsoSDK)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION Samples/CPP/AudioMFC COMPONENT IsoSDK)
install(FILES ${BUILD_FILES} DESTINATION Samples/CPP/AudioMFC COMPONENT IsoSDK)
