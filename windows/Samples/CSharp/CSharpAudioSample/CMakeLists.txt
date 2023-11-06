set(SOURCE_FILES
	app.config
	AudioSampleForm.cs
	AudioSampleForm.Designer.cs
	AudioSampleForm.resx
	CDTextDlg.cs
	CDTextDlg.Designer.cs
	CDTextDlg.resx
	FileListView.cs
	isosdkbig.ico
	minidoc.gif
	minifolder.gif
	Program.cs
	TrackListView.cs
)
set(BUILD_FILES CMakeLists.txt)
set(BUILD_FILES
	${BUILD_FILES}
	CSharpAudioSample_2017.csproj
)

add_subdirectory(Properties)
add_subdirectory(Resources)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/CSharpAudioSample" COMPONENT IsoSDK_DotNet)
