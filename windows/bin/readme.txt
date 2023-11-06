C++
The FoxBurner SDK is compiled with the newest C Standards and C Compilers. 
The current build is dedicated to latest VisualStudio compilers.

WindowsXP
You can find a binary compatible 32 bit version inside the folder XP2008. This version will run on old
Windows XP systems. We do not recommend to run this on Windows8 and higher.

dotNet
You can find version of dotNet component compiled with SDK and Framework of 
VisualStudio2019. The VisualStudio2017 version is compiled according newest dotNet Framework.

You can find a strong signed Assembly for each dotNet build.

If you need a special build for dotNet Framework please contact our support.

Delphi
To install the Delphi component, please check the readme.txt inside the Delphi folder.
Note, Delphi is deprecated. This means, we will not change the wrapper or samples anymore.

JNI
In this folder you can find the JNIWrapper we used for Linux and Windows development.
It is complied with common CPU. If you need a Wrapepr for ARM or other CPU you need to recompile it.
This is only possible if you have the source code licene.

Linux
If you open a sample with FoxSDK, and you do not see an icon inside your Deskptop, then it is a 
matter of Ubuntu, not FoxSDK. Each sample need an Entry to its file in applications folder. 
As sample FoxDataSample.desktop
A sample .desktop file is:

[Desktop Entry]
Version=1.0
Type=Application
Name=FoxDataSample
Comment=Data sample for FoxSDK
Exec=<path to sample>/FoxDataSample  example: /home/developer/Downloads/build1a/Samples/CPP/DataFOXLib/FoxDataSample
Icon=<path to image>/FoxSample.png   example: /home/developer/Downloads/build1a/Samples/CPP/DataFOXLib/FoxDataSample
Terminal=false
Type=Application
Categories=FoxBurner;
StartupNotify=true
StartupWMClass=DataFOXLib 

StartupWMClass is important!

Common, after install the file should be:
[Desktop Entry]
Version=1.0
Type=Application
Name=FoxDataSample
Comment=Data sample for FoxSDK
Exec=FoxDataSample
Icon=FoxSample.png
Terminal=false
Type=Application
Categories=FoxBurner;
StartupNotify=true
StartupWMClass=DataFOXLib
