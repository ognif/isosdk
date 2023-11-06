
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
project(IsoSDKJNI)

if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DWIN32)
	set( CMAKE_CXX_FLAGS "-std=c++11" )
endif(WIN32)

if(UNIX AND NOT APPLE)
	add_definitions(-DLINUX)
	#set( CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++" )
	set( CMAKE_CXX_FLAGS "-std=c++11" )
endif(UNIX AND NOT APPLE)


message("PATH_TO_ISOSDK: "${PATH_TO_ISOSDK})

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_OSX_ARCHITECTURES x86_64)
add_definitions(-D_FILE_OFFSET_BITS=64)


include_directories(${PATH_TO_ISOSDK}/isosdk/include)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(${JNI_INCLUDE_DIRS})

set(OUTPUT_NAME IsoSDKCore)

if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/win64)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/win64)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/win64)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/win64)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/win64)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/win64)
		link_directories(${PATH_TO_ISOSDK}/isosdk/lib/win64)
		set(OUTPUT_NAME ${OUTPUT_NAME}64)
	else(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/win32)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/win32)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/win32)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/win32)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/win32)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/win32)
		link_directories(${PATH_TO_ISOSDK}/isosdk/lib/win32)
		set(OUTPUT_NAME ${OUTPUT_NAME}32)		
	endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
endif(WIN32)

if(UNIX AND NOT APPLE)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/linux64)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/linux64)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/linux64)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/linux64)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/linux64)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/linux64)	
		link_directories(${PATH_TO_ISOSDK}/isosdk/lib/linux64)
		set(OUTPUT_NAME ${OUTPUT_NAME}64.2.31)	
	else(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/linux32)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/linux32)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/linux32)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/linux32)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PATH_TO_ISOSDK}/bin/linux32)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PATH_TO_ISOSDK}/bin/linux32)	
		link_directories(${PATH_TO_ISOSDK}/isosdk/lib/linux32)
		set(OUTPUT_NAME ${OUTPUT_NAME}32.2.31)	
	endif(CMAKE_SIZEOF_VOID_P EQUAL 8)	
endif(UNIX AND NOT APPLE)



add_library( # Sets the name of the library.
        IsoSDKJNI
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        IsoSDKJNI.cpp
        )
        
target_link_libraries( # Specifies the target library.
        IsoSDKJNI
        ${OUTPUT_NAME})
