add_subdirectory(md5)
add_subdirectory(res)

set(SOURCE_FILES
	AudioGrabbingDialog.h
	AudioTrackPlayingDialog.h
	CDTextReadDlg.h
	ErrorListLogCreator.h
	FilePropertiesDlg.h
	ImageEditMFC.h
	ImageEditMFCDlg.h
	KLock.h
	Logging.h
	Md5Dialog.h
	PropertiesDlg.h
	resource.h
	SaveContentDialog.h
	SaveDiscDialog.h
	SaveTrackDialog.h
	PasswordDlg.h
	ScanSectorsDialog.h
	SectorViewDialog.h
	stdafx.h
	TreeNodes.h
	AudioGrabbingDialog.cpp
	AudioTrackPlayingDialog.cpp
	CDTextReadDlg.cpp
	ErrorListLogCreator.cpp
	FilePropertiesDlg.cpp
	ImageEditMFC.cpp
	ImageEditMFCDlg.cpp
	Md5Dialog.cpp
	PropertiesDlg.cpp
	SaveContentDialog.cpp
	SaveDiscDialog.cpp
	SaveTrackDialog.cpp
	ScanSectorsDialog.cpp
	SectorViewDialog.cpp
	PasswordDlg.cpp
	stdafx.cpp
	TreeNodes.cpp
	ImageEditMFC.rc
	${MD5_SOURCE_FILES}
	${RES_SOURCE_FILES}
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/AboutDlgMFC.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/Sector2Text.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/KString.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common/Sector2Text.cpp
)

set(BUILD_FILES
	ImageEditMFC_2019.vcxproj
)

# Declare source groups for Visual Studio project.
source_group("Resource Files" "[_A-Za-z0-9-]+\\.(rc|rc2)")
source_group("MD5" "md5/[_A-Za-z0-9-]+\\.(h|cpp|c|idl)")

if(NOT BUILD_TYPE STREQUAL "WindowsInstaller")
	add_definitions(-DBS_GUI)
	set(CMAKE_MFC_FLAG 1) # Use MFC in a static library

	add_executable(IsoSDKImageEditSampleMFC WIN32 ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

	if(BUILD_TYPE STREQUAL "NativeUnicode")
		set_target_properties(IsoSDKImageEditSampleMFC PROPERTIES OUTPUT_NAME IsoSDKImageEditSampleUw)
	elseif(BUILD_TYPE STREQUAL "NativeMultibyte")
		set_target_properties(IsoSDKImageEditSampleMFC PROPERTIES OUTPUT_NAME IsoSDKImageEditSamplew)
	endif(BUILD_TYPE STREQUAL "NativeUnicode")

	set_target_properties(IsoSDKImageEditSampleMFC PROPERTIES DEBUG_POSTFIX _dbg)

	target_link_libraries(IsoSDKImageEditSampleMFC IsoSDKMFC)

	install(TARGETS IsoSDKImageEditSampleMFC DESTINATION ${RUNTIME_DESTINATION} COMPONENT IsoSDK)
endif(NOT BUILD_TYPE STREQUAL "WindowsInstaller")

install(FILES ${SOURCE_FILES} DESTINATION Samples/CPP/ImageEditMFC COMPONENT IsoSDK)
install(FILES ${BUILD_FILES} DESTINATION Samples/CPP/ImageEditMFC COMPONENT IsoSDK)
