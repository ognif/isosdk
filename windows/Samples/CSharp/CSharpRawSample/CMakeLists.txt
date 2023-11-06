set(SOURCE_FILES
	app.config
	isosdkbig.ico
	Program.cs
	RawSampleForm.cs
	RawSampleForm.Designer.cs
	RawSampleForm.resx
)

set(BUILD_FILES
	CSharpRawSample_2017.csproj
)

add_subdirectory(Properties)
add_subdirectory(Resources)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/CSharpRawSample" COMPONENT IsoSDK_DotNet)
