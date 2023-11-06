set(SOURCE_FILES
	app.config
	isosdkbig.ico
	Program.cs
	RegionSelect.cs
	RegionSelect.Designer.cs
	RegionSelect.resx
	UtilitiesSampleForm.cs
	UtilitiesSampleForm.Designer.cs
	UtilitiesSampleForm.resx
)

set(BUILD_FILES
	CSharpUtilitiesSample_2017.csproj
)

add_subdirectory(Properties)
add_subdirectory(Resources)

install(FILES ${SOURCE_FILES} ${BUILD_FILES} DESTINATION "Samples/CSharp/CSharpUtilitiesSample" COMPONENT IsoSDK_DotNet)
