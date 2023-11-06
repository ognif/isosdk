set(SOURCE_FILES
	AboutDlg.cs
	AboutDlg.Designer.cs
	AboutDlg.resx
	BurnDlgDevel.cs
	BurnDlgDevel.Designer.cs
	BurnDlgDevel.resx
	Common.cs
	CreateFolderDlg.cs
	CreateFolderDlg.Designer.cs
	CreateFolderDlg.resx
	EraseDlg.cs
	EraseDlg.Designer.cs
	EraseDlg.resx
	MultiDeviceDlg.cs
	MultiDeviceDlg.Designer.cs
	RenameDlg.cs
	RenameDlg.Designer.cs
	RenameDlg.resx
	WebSiteLinkForm.cs
	WebSiteLinkForm.Designer.cs
	WebSiteLinkForm.resx
)

set(BUILD_FILES
	Common_2017.csproj
)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/Common" COMPONENT IsoSDK_DotNet)

add_subdirectory(Properties)
add_subdirectory(Resources)
