set(RES_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/AudioMFC.rc2
)

set(RES_SOURCE_FILES ${RES_SOURCE_FILES} PARENT_SCOPE)

install(FILES ${RES_SOURCE_FILES} DESTINATION Samples/C++/AudioMFC/res COMPONENT IsoSDK)
