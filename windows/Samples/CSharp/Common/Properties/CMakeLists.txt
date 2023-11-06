configure_file(
	AssemblyInfo.cs.in
	AssemblyInfo.cs
)

set(SOURCE_FILES
	${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
	Resources.Designer.cs
	Resources.resx
)

install(FILES ${SOURCE_FILES} DESTINATION "Samples/C#/Common/Properties" COMPONENT IsoSDK_DotNet)
