set(SOURCE_FILES
	app.config
	isosdkbig.ico
	ImageEditSampleForm.cs
	ImageEditSampleForm.Designer.cs
	ImageEditSampleForm.resx
	KMD5Dialog.cs
	KMD5Dialog.Designer.cs
	KMD5Dialog.resx
	KPropertiesDialog.cs
	KPropertiesDialog.Designer.cs
	KPropertiesDialog.resx
	KScanSectorsDialog.cs
	KScanSectorsDialog.Designer.cs
	KScanSectorsDialog.resx
	KSector2Text.cs
	KSectorViewDialog.cs
	KSectorViewDialog.Designer.cs
	KSectorViewDialog.resx
	Program.cs
	TreeNodes.cs
)

set(BUILD_FILES
	CSharpImageEditSample_2017.csproj
)

add_subdirectory(JobDialogs)
add_subdirectory(Properties)
add_subdirectory(Resources)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/CSharpImageEditSample" COMPONENT IsoSDK_DotNet)
