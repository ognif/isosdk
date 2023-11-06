set(SOURCE_FILES
	KAudioGrabbingDialog.cs
	KAudioGrabbingDialog.Designer.cs
	KAudioGrabbingDialog.resx
	KSaveContentDialog.cs
	KSaveContentDialog.Designer.cs
	KSaveContentDialog.resx
	KSaveDiscDialog.cs
	KSaveDiscDialog.Designer.cs
	KSaveDiscDialog.resx
	KSaveTrackDialog.cs
	KSaveTrackDialog.Designer.cs
	KSaveTrackDialog.resx
	KTrackPlayDialog.cs
	KTrackPlayDialog.Designer.cs
	KTrackPlayDialog.resx
)

install(FILES ${SOURCE_FILES} DESTINATION "Samples/C#/CSharpImageEditSample/JobDialogs" COMPONENT IsoSDK_DotNet)
