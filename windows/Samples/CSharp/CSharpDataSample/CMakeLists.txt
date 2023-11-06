set(SOURCE_FILES
	addfile.ico
	app.config
	BootImageDlg.cs
	BootImageDlg.Designer.cs
	BootImageDlg.resx
	burn.ico
	cancel.ico
	cd_erase.ico
	DataSampleForm.cs
	DataSampleForm.Designer.cs
	DataSampleForm.resx
	delete.ico
	FileListView.cs
	isosdkbig.ico
	HeaderDlg.cs
	HeaderDlg.Designer.cs
	HeaderDlg.resx
	ImportSessionDlg.cs
	ImportSessionDlg.Designer.cs
	ImportSessionDlg.resx
	minidoc.gif
	minifolder.gif
	Program.cs
	PropertiesDlg.cs
	PropertiesDlg.Designer.cs
	PropertiesDlg.resx
	reset.ico
)

set(BUILD_FILES
	CSharpDataSample_2017.csproj
)

add_subdirectory(Properties)
add_subdirectory(Resources)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/CSharpDataSample" COMPONENT IsoSDK_DotNet)
