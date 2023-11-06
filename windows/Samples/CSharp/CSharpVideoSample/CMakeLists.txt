set(SOURCE_FILES
	app.config
	isosdkbig.ico
	Program.cs
	VideoSampleDlg.cs
	VideoSampleDlg.Designer.cs
	VideoSampleDlg.resx
)

set(BUILD_FILES
	CSharpVideoSample_2017.csproj
)

add_subdirectory(Properties)
add_subdirectory(Resources)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/CSharpVideoSample" COMPONENT IsoSDK_DotNet)
