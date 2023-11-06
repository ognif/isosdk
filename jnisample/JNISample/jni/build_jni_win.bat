SET MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\MSBuild.exe"
SET NATIVECONFIGDIR="E:\Ingo\eclipse\workspace\JNISample\jni\buildkit\win64"
SET NATIVESOURCEDIR="E:\Ingo\eclipse\workspace\JNISample\jni"
SET NATIVEBINDIR="E:\Ingo\eclipse\workspace\JNISample\jni\bin\win64"
SET ISOSDKCOREDIR="E:\Ingo\eclipse\workspace\JNISample\jni\isosdk\lib\win64"
SET JARLIBDIR="E:\Ingo\eclipse\workspace\JNISample\jar\jni\win64\"

REM -- CMake configure
cmake -B %NATIVECONFIGDIR% -S %NATIVESOURCEDIR% -D PATH_TO_ISOSDK="%NATIVESOURCEDIR%"

REM -- Build all
%MSBUILD% "%NATIVECONFIGDIR%\IsoSDKJNI.sln" /t:Clean;Rebuild /property:Configuration=Release
IF NOT %ERRORLEVEL%==0 GOTO ERROR

REM -- Copy 64bit Files
xcopy /s /Y "%ISOSDKCOREDIR%\IsoSDKCore64.dll" "%JARLIBDIR%"
xcopy /s /Y "%NATIVEBINDIR%\IsoSDKJNI.dll" "%JARLIBDIR%"


ECHO --------------------------------------------------
ECHO SUCCESS FINISHED
ECHO --------------------------------------------------
pause

:ERROR
ECHO --------------------------------------------------
ECHO ERROR HAS OCCURED
ECHO --------------------------------------------------
pause