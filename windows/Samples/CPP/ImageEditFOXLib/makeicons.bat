set resources=..\..\..\Samples\res\isosdksmall.ico ..\..\..\Samples\res\isosdkbig.ico ..\..\..\Samples\res\burn_iso.ico ..\..\..\Samples\res\audio.ico ..\..\..\Samples\res\open_folder.ico ..\..\..\Samples\res\closed_folder.ico ..\..\..\Samples\res\minidoc.gif ..\..\..\Samples\res\iso.ico  ..\..\..\Samples\res\play.ico ..\..\..\Samples\res\stop.ico
reswrap.exe --header -o resources.h %resources% --source --include stdafx.h -o resources.cpp %resources%