#include "IsoSDKJNI.h"

#include <IsoSDKBurningLib.h>
#include <IsoSDKExport.h>
#include <tchar.h>

#include <time.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>


static JavaVM *g_jVM = NULL;
static jclass g_jClazz = NULL;
static jmethodID g_jMID = NULL;
static std::string g_dlgClass = "";
static bool nDebug = true;
static int32 nCapsHandle = 0;
static int32 hCdText = 0;



extern "C" char* strptime(const char* s,
                          const char* f,
                          struct tm* tm) {
  // Isn't the C++ standard lib nice? std::get_time is defined such that its
  // format parameters are the exact same as strptime. Of course, we have to
  // create a string stream first, and imbue it with the current C locale, and
  // we also have to make sure we return the right things if it fails, or
  // if it succeeds, but this is still far simpler an implementation than any
  // of the versions in any of the C standard libraries.
  std::istringstream input(s);
  input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
  input >> std::get_time(tm, f);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(s + input.tellg());
}

/*
 * Also, laut Internet unterliegt der JNI dem ZEichensatz des zugrunde liegenden Systems.
 * Ähnlich wie bei QT
 * TCHAR ist wenn nicht unicode dann char.
 */

IsoSDK::IsoSDK (const TCHAR * licensekey){

	lastError = 0;
	int32 res = ::Initialize(licensekey, BS_ASPI_INTERNAL, BS_TRUE);
	lastError = res;

	if (nDebug == true) {
		std::cout << "Key" << licensekey << std::endl;
		std::cout << "Initialize: " << res << std::endl;
	}


}

//SetTheProcess Callback
//Defne a pocess Function
//FireBack to JNI

std::string IsoSDK::driveList() {

    int32 res =  ::RescanDevices();

   	std::string mydrives;

    	TCHAR chListDevices[26][50];
    	int32 nUsed = 0;
    	res = ::GetDevices(chListDevices, &nUsed, false);

    	if (BS_SDK_ERROR_NO == res) {
        	for (int i = 0; i < nUsed; i++) {
            	mydrives.append(chListDevices[i]);
            	mydrives.append(" | ");
        	}
    	}

	return mydrives;
}

IsoSDK::~IsoSDK() {

}

void OnProcess(float fPercent, float fDeviceBuffer, float fCache,
			   double dBytesWritten, double dImageSize, void *pUserData)
{
	if(nDebug==true) {
		std::cout << "\n !!! Process !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);
	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printProcess", "(F)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, fPercent);
	g_jVM->DetachCurrentThread();

}

void OnJobDone(void*)
{
	std::cout << "JobDone" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Process !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);
	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";
	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printJobDone", "()V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid);
	g_jVM->DetachCurrentThread();
}

void OnBurnDone(const TCHAR* pcError, void* pUserData)
{
	std::cout << "BurnDone" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Process !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);


	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jstring buffer = jEnv->NewStringUTF(pcError ? pcError : _T("no errors."));

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printBurnDone", "(Ljava/lang/String;)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, buffer);
	g_jVM->DetachCurrentThread();
}

void OnFinalize(void*)
{
	std::cout << "Finalize" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Process !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);
	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printFinalize", "()V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid);
	g_jVM->DetachCurrentThread();
}

void OnEraseDone(const TCHAR *pcError, void* pUserData)
{
	std::cout << "Erase Done" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Erase Done !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);


	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jstring buffer = jEnv->NewStringUTF(pcError ? pcError : _T("no errors."));

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printEraseDone", "(Ljava/lang/String;)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, buffer);
	g_jVM->DetachCurrentThread();
}

void OnStartVerify(void*)
{
	std::cout << "StartVerify" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Start Verify !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);


	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printVerifyStart", "()V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid);
	g_jVM->DetachCurrentThread();
}

void OnVerifyFile(const TCHAR* pcFileName, void* pUserData)
{
	std::cout << "Verify File" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Verify File !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);


	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jstring buffer = jEnv->NewStringUTF(pcFileName);

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printVerifyFile", "(Ljava/lang/String;)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, buffer);
	g_jVM->DetachCurrentThread();
}

void OnVerifyError(const TCHAR* pcFileName, const TCHAR* pcError, void* pUserData)
{
	std::cout << "Verify Error" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Verify Error !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);


	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jstring fileName = jEnv->NewStringUTF(pcFileName);
	jstring buffer = jEnv->NewStringUTF(pcError);

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printVerifyError", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, pcFileName, buffer);
	g_jVM->DetachCurrentThread();

}

void OnVerifyDone(int nNumErrors, void* pUserData)
{
	std::cout << "Verify Done" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Verify Done !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);
	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printVerifyDone", "(I)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, nNumErrors);
	g_jVM->DetachCurrentThread();
}

void OnBurnFile(const TCHAR* pcFileName, void* pUserData){

	std::cout << "Burn File" << std::endl;

	if(nDebug==true) {
		std::cout << "\n !!! Burn File !!! \n";

	}

	JNIEnv *jEnv = NULL;
	g_jVM->AttachCurrentThread((void **)(&jEnv), NULL);


	if (jEnv == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n !!! Failed to attach current thread with JVM !!! \n";
			}
			return;
		}

	jstring buffer = jEnv->NewStringUTF(pcFileName);

	jclass jClz = jEnv->FindClass(g_dlgClass.c_str());
	if (jClz == NULL)
		{
			if(nDebug==true) {
				std::cout << "\n %%%\t !!! FindClass returns NULL !!! \n";

			}
			return;
		}

	jmethodID jMid = jEnv->GetStaticMethodID(jClz, "printBurnFile", "(Ljava/lang/String;)V");
	if (jMid == NULL){

		if(nDebug==true) {
			std::cout << "\n %%%\t GetStaticMethodID returns NULL !!!\n";

		}
		return;
	}

	jEnv->CallStaticVoidMethod(jClz, jMid, buffer);
	g_jVM->DetachCurrentThread();

}

static IsoSDK *example = NULL;

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_initializeIsoSDK
  ( JNIEnv *env, jobject jobj, jstring lKey )
{

	const TCHAR *licenceKey = env->GetStringUTFChars ( lKey, JNI_FALSE );
	example = new IsoSDK ( licenceKey );
	env->ReleaseStringUTFChars ( lKey, licenceKey );

	std::string hello = "IsoSDK says Hello";

    return env->NewStringUTF ( hello.c_str() );
}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_drivelist
  ( JNIEnv *env, jobject jObj )
{

 	std::string drives= example->driveList();

	return env->NewStringUTF ( drives.c_str() );
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_openDevice
  ( JNIEnv *env, jobject jObj, jint lDeviceIndex )
{

	int32 res = ::LockMedium ((int)lDeviceIndex, BS_FALSE );
	res =  ::EjectDevice( (int)lDeviceIndex );
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_closeDevice
  ( JNIEnv *env, jobject jObj, jint lDeviceIndex )
{

	int32 res = ::LockMedium ((int)lDeviceIndex, BS_FALSE );
	res =  ::CloseDevice ( (int)lDeviceIndex );
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setBurnDevice
  ( JNIEnv *env, jobject jObj, jstring lDevice )
{

	const TCHAR *drive = env->GetStringUTFChars ( lDevice, JNI_FALSE );

	int32 res = ::SetBurnDevice ( drive);

	env->ReleaseStringUTFChars ( lDevice, drive );

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setReadDevice
  ( JNIEnv *env, jobject jObj, jstring lDevice )
{
	const TCHAR *drive = env->GetStringUTFChars ( lDevice, JNI_FALSE );

	int32 res = ::SetReadDevice(drive);

	env->ReleaseStringUTFChars ( lDevice, drive );

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_addBurnDevice
  ( JNIEnv *env, jobject jObj, jstring lDevice )
{
	const TCHAR *drive = env->GetStringUTFChars ( lDevice, JNI_FALSE );

	int32 res = ::AddBurnDevice(drive);

	env->ReleaseStringUTFChars ( lDevice, drive );

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_removeBurnDevice
  ( JNIEnv *env, jobject jObj, jstring lDevice )
{
	const TCHAR *drive = env->GetStringUTFChars ( lDevice, JNI_FALSE );

	int32 res = ::RemoveBurnDevice(drive);

	env->ReleaseStringUTFChars ( lDevice, drive );

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setProject
  ( JNIEnv *env, jobject jObj, jint lProjectType )
{

	/*
	#	define BS_BURNER_AUDIO						0
	#	define BS_BURNER_CUE						1
	#	define BS_BURNER_DATA						2
	#	define BS_BURNER_VCD						3
	#	define BS_BURNER_SVCD						4
	#	define BS_BURNER_VIDEODVD					5
	#	define BS_BURNER_UDFDVD						6
	#	define BS_BURNER_ISOUDF						7
	#	define BS_BURNER_BLURAY						8
	#	define BS_BURNER_MIXEDMODE					9
	#	define BS_BURNER_RAW						10
	*/
	int32 res = ::CreateProject( (int)lProjectType,BS_CONTINUE_NO_SESSION );

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_addFile
  (JNIEnv *env, jobject jObj, jstring lFilePath, jstring lDiscPath)
{
	const TCHAR *filePath = env->GetStringUTFChars(lFilePath, JNI_FALSE);
	const TCHAR *discPath = env->GetStringUTFChars(lDiscPath, JNI_FALSE);

	std::cout << "discPath: " << discPath << std::endl;
	std::cout << "discPathlength: " << env->GetStringUTFLength(lDiscPath) << std::endl;

    SFileToAdd file;

    file.lpszFileName = nullptr;
    file.lpszSourceFilePath = filePath;
    file.lpszDestinationPath = discPath;
    file.bVideoFile = BS_FALSE;
    file.nSavePath = BS_DONT_SAVE_PATH;
    

    int32 res = ::AddFile(file);
    if(nDebug==true) std::cout << "AddFile: " << res << std::endl;

	env->ReleaseStringUTFChars(lFilePath, filePath);
	env->ReleaseStringUTFChars(lDiscPath, discPath);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_addFolder
  (JNIEnv *env, jobject jObj, jstring lFolderPath, jstring lDiscPath)
{
	const TCHAR *folderPath = env->GetStringUTFChars(lFolderPath, JNI_FALSE);
	const TCHAR *discPath = env->GetStringUTFChars(lDiscPath, JNI_FALSE);

	SDirToAdd dir;

	dir.lpszSourceDirPath = folderPath;
	dir.lpszDestinationPath = discPath;
	dir.lpszFileSpecification = _T("*");
	dir.nFileAttributes = BS_FA_ALL;
	dir.nSavePath = BS_PARENTDIR_ONLY;
	dir.bRecursive = BS_TRUE;

	int32 res = ::AddDir(dir);
	if(nDebug==true) std::cout << "AddFolder: " << res << std::endl;

	env->ReleaseStringUTFChars(lFolderPath, folderPath);
	env->ReleaseStringUTFChars(lDiscPath, discPath);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_createFolder
  (JNIEnv *env, jobject jObj, jstring lFolderName, jstring lDiscPath)
{
	const TCHAR *folderName = env->GetStringUTFChars(lFolderName, JNI_FALSE);
	const TCHAR *discPath = env->GetStringUTFChars(lDiscPath, JNI_FALSE);

	SDirToCreate dir;
	dir.lpszDestinationPath = discPath;
	dir.lpszDir = folderName;

	int32 res = ::CreateDir(dir);
	if(nDebug==true) std::cout << "Create Folder: " << res << std::endl;

	env->ReleaseStringUTFChars(lFolderName, folderName);
	env->ReleaseStringUTFChars(lDiscPath, discPath);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_renameFile
  (JNIEnv *env, jobject jObj, jstring lFilePath, jstring lNewFileName)
{
	const TCHAR *filePath = env->GetStringUTFChars(lFilePath, JNI_FALSE);
	const TCHAR *newFileName = env->GetStringUTFChars(lNewFileName, JNI_FALSE);

	SFileToRename file;

	file.lpszSourcePath = filePath;
	file.lpszDestinationPath = newFileName;

	int32 res = ::RenameFile(file);
	if(nDebug==true) std::cout << "Rename File: " << res << std::endl;

	env->ReleaseStringUTFChars(lFilePath, filePath);
	env->ReleaseStringUTFChars(lNewFileName, newFileName);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_removeFile
  (JNIEnv *env, jobject jObj, jstring lFilePath, jstring lFileName)
{
	const TCHAR *filePath = env->GetStringUTFChars(lFilePath, JNI_FALSE);
	const TCHAR *fileName = env->GetStringUTFChars(lFileName, JNI_FALSE);

	SFileToRemove file;

	file.lpszFile = fileName;
	file.lpszDestinationPath = filePath;

	int32 res = ::RemoveFile(file);
	if(nDebug==true) std::cout << "Remove File: " << res << std::endl;

	env->ReleaseStringUTFChars(lFilePath, filePath);
	env->ReleaseStringUTFChars(lFileName, fileName);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_renameFolder
  (JNIEnv *env, jobject jObj, jstring lFolderPath, jstring lNewFolderName)
{
	const TCHAR *folderPath = env->GetStringUTFChars(lFolderPath, JNI_FALSE);
	const TCHAR *newFolderName = env->GetStringUTFChars(lNewFolderName, JNI_FALSE);

	SDirToRename dir;
	dir.lpszSourcePath = folderPath;
	dir.lpszDestinationPath = newFolderName;

	int32 res = ::RenameDir(dir);
	if(nDebug==true) std::cout << "RenameFolder: " << res << std::endl;

	env->ReleaseStringUTFChars(lFolderPath, folderPath);
	env->ReleaseStringUTFChars(lNewFolderName, newFolderName);
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_removeFolder
  (JNIEnv *env, jobject jObj, jstring lDiscPath)
{

	const TCHAR *discPath = env->GetStringUTFChars(lDiscPath, JNI_FALSE);

	SDirToRemove dir;
	dir.lpszDestinationPath = discPath;

	int32 res = ::RemoveDir(dir);
	if(nDebug==true) std::cout << "Remove Folder: " << res << std::endl;

	env->ReleaseStringUTFChars(lDiscPath, discPath);
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_dirExists
  ( JNIEnv *env, jobject jObj, jstring lPath )
{

	//returns BS_SDK_ERROR_INVALID_DEST_PATH 9
	//return BS_SDK_ERROR_PATH_EXISTS 11
	const TCHAR *dirPath = env->GetStringUTFChars(lPath, JNI_FALSE);

	int32 res = ::DirExists(dirPath);

	if(nDebug==true) std::cout << "DirExists: " << res << std::endl;
	env->ReleaseStringUTFChars(lPath, dirPath);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_abort
  (JNIEnv *env, jobject jObj)
{
	int32 res = ::Abort();
	if(nDebug==true) std::cout << "Abort: " << res << std::endl;
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_deleteProject
  (JNIEnv *env, jobject jObj)
{
	int32 res = ::DeleteProject();
	if(nDebug==true) std::cout << "Delete Project: " << res << std::endl;
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_rescanDevices
  (JNIEnv *env, jobject jObj)
{
	int32 res = ::RescanDevices();
	if(nDebug==true) std::cout << "Rescan Devices: " << res << std::endl;
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getProjectType
  (JNIEnv *env, jobject jObj)
{
	int32 m_iProjectType = -1;
	example->lastError = ::GetProjectType(&m_iProjectType);
	if(nDebug==true) std::cout << "Get Project Type: " << m_iProjectType << std::endl;
	return (int)m_iProjectType;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getActiveDevices
  (JNIEnv *env, jobject jObj)
{
	int32 m_iDevices = -1;
	example->lastError = ::GetActiveDevicesCount(&m_iDevices);
	if(nDebug==true) std::cout << "Get ActiveDevices: " << m_iDevices << std::endl;
	return (int)m_iDevices;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getLastError
  (JNIEnv *env, jobject jObj)
{
	int res = example->lastError;
 	if(nDebug==true) std::cout << "Get Last Error: " << res << std::endl;
	return res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_doPrepare
  (JNIEnv *env, jobject jObj)
{
	int32 res = ::Prepare();
	if(nDebug==true) std::cout << "Prepare: " << res << std::endl;
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_doBurn
  (JNIEnv *env, jobject jObj)
{
	int32 res = ::Burn();
	if(nDebug==true) std::cout << "Burn: " << res << std::endl;
	return (int)res;
}


JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_isDeviceReady
  (JNIEnv *env, jobject jObj, jint lDeviceIndex)
{
	BS_BOOL m_bReady = BS_FALSE;
	example->lastError = ::IsDeviceReady((int)lDeviceIndex, &m_bReady);

	if(nDebug==true) std::cout << "Device Ready: " << example->lastError << std::endl;
	return (int)m_bReady;

}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getText
  (JNIEnv *env, jobject jobj, jint lValue)
{

	std::string textValue = "";

	TCHAR chError[2048];
	int32 nLength = 2048;

	int32 res = ::GetText((int)lValue, chError, &nLength);
	example->lastError = res;
	if(res==0){
		textValue.append(chError);
	}

	return env->NewStringUTF(textValue.c_str());
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setBurnSpeed
  (JNIEnv *env, jobject jobj, jint lDevice, jint lValue)
{

	int32 res = ::SetBurnSpeed((int)lDevice, (int)lValue);
	if(nDebug==true) std::cout << "Set Burn Speed Ready: " << res << std::endl;
	return (int)res;

}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setReadSpeed
  (JNIEnv *env, jobject jobj, jint lDevice, jint lValue)
{

	int32 res = ::SetReadSpeed((int)lDevice, (int)lValue);
	if(nDebug==true) std::cout << "Set Read Speed Ready: " << res << std::endl;
	return (int)res;

}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getBurnSpeed
  ( JNIEnv *env, jobject jobj, jint lDevice)
{
	int32 nSpeed = 0;
	int32 res = ::GetBurnSpeed((int)lDevice, &nSpeed);

	if (nSpeed == BS_MAX_SPEED)
		res = ::GetMaxBurnSpeed((int)lDevice, &nSpeed);

	if(nDebug==true) std::cout << "Get Burn Speed Ready: " << nSpeed << std::endl;

	example->lastError = res;
	return (int)nSpeed;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getReadSpeed
  (JNIEnv *env, jobject jobj, jint lDevice)
{
	int32 nSpeed = 0;
	int32 res = ::GetReadSpeed((int)lDevice, &nSpeed);

	if (nSpeed == BS_MAX_SPEED)
		res = ::GetMaxReadSpeed((int)lDevice, &nSpeed);

	if(nDebug==true) std::cout << "Get Read Speed Ready: " << nSpeed << std::endl;

	example->lastError = res;
	return (int)nSpeed;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getMaxBurnSpeed
  ( JNIEnv *env, jobject jobj, jint lDevice)
{
	int32 nSpeed = 0;
	int32 res = ::GetMaxBurnSpeed((int)lDevice, &nSpeed);

	if(nDebug==true) std::cout << "Get Max Burn Speed Ready: " << nSpeed << std::endl;

	example->lastError = res;
	return (int)nSpeed;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getMaxReadSpeed
  (JNIEnv *env, jobject jobj, jint lDevice)
{
	int32 nSpeed = 0;
	int32 res = ::GetMaxBurnSpeed((int)lDevice, &nSpeed);

	if(nDebug==true) std::cout << "Get Max Read Speed Ready: " << nSpeed << std::endl;

	example->lastError = res;
	return (int)nSpeed;
}

JNIEXPORT void JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_initializeCallbacks
	(JNIEnv *env, jclass clz, jstring dlgClassName)
{
		env->GetJavaVM(&g_jVM);

		const TCHAR *className = env->GetStringUTFChars(dlgClassName, JNI_FALSE);
		g_dlgClass.append(className);
		env->ReleaseStringUTFChars(dlgClassName, className);


		int32 res = ::SetFinalizeEventCallback(OnFinalize, 0);
		if(nDebug==true) std::cout << "SetCallback: " << res << std::endl;
		::SetBurnDoneEventCallback(OnBurnDone, 0);
		::SetProcessEventCallback(OnProcess, 0);
		::SetJobDoneEventCallback(OnJobDone, 0);
		::SetStartVerifyEventCallback(OnStartVerify, 0);
		::SetVerifyFileEventCallback(OnVerifyFile, 0);
		::SetVerifyErrorEventCallback(OnVerifyError, 0);
		::SetVerifyDoneEventCallback(OnVerifyDone, 0);
		::SetBurnFileEventCallback(OnBurnFile, 0);
		::SetEraseDoneEventCallback(OnEraseDone,0);

}

JNIEXPORT void JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_clearCallbacks
	(JNIEnv *env, jclass clz)
{

	::SetFinalizeEventCallback(NULL, NULL);
	::SetBurnDoneEventCallback(NULL, NULL);
	::SetProcessEventCallback(NULL, NULL);
	::SetJobDoneEventCallback(NULL, NULL);
	::SetStartVerifyEventCallback(NULL, NULL);
	::SetVerifyFileEventCallback(NULL, NULL);
	::SetVerifyErrorEventCallback(NULL, NULL);
	::SetVerifyDoneEventCallback(NULL, NULL);
	::SetBurnFileEventCallback(NULL, NULL);
	::SetEraseDoneEventCallback(NULL, NULL);

}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setImageFilePath
  (JNIEnv *env, jobject jObj, jstring lPath)
{

	const TCHAR *imagePath = env->GetStringUTFChars(lPath, JNI_FALSE);

	int32 res = ::SetImageFilePath(imagePath);
 	if(nDebug==true) std::cout << "SetImageFilePath: " << res << std::endl;
	env->ReleaseStringUTFChars(lPath, imagePath);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_isImageWriterSelected
  (JNIEnv *env, jobject jObj)
{
	TCHAR pchDevice[50];
	int32 nLength = sizeof(pchDevice)/sizeof(TCHAR);
	int32 res = ::GetBurnDevice(pchDevice, &nLength);
	example->lastError = res;

	if (0 == _tcsncmp(_T("#"), pchDevice, 1))  // Iso writer selected
		{
			return 1;
		}

	return 0;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_saveLogToFile
  (JNIEnv *env, jobject jObj, jstring lPath){

	const TCHAR *logPath = env->GetStringUTFChars(lPath, JNI_FALSE);

	int32 res = ::SaveLogToFile(logPath);

 	if(nDebug==true) std::cout << "SaveLogToFile: " << res << std::endl;
	env->ReleaseStringUTFChars(lPath, logPath);

	return (int)res;

}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_doErase
  (JNIEnv *env, jobject jObj, jboolean lFast, jboolean lEject){

	int32 res = ::Erase((bool)lFast, (bool)lEject);
	return (int)res;
}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getBurnDevice
  (JNIEnv *env, jobject jobj){

	std::string textValue = "";

	TCHAR	burnDevices[26][50];
	int32	nBurnDevices = 0;

	int32 res = ::GetBurnDevices(burnDevices, &nBurnDevices);
	example->lastError = res;
	if(nDebug==true) std::cout << "GetBurnDeviceEx Error: " << res << std::endl;
	if(res==0){
		textValue.append(burnDevices[0]);
	}

	return env->NewStringUTF(textValue.c_str());

}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getReadDevice
  (JNIEnv *env, jobject jobj){

	std::string textValue = "";

	TCHAR pchDevice[50];
	int32 nLength = sizeof(pchDevice) / sizeof(TCHAR);

	int32 res = ::GetReadDevice(pchDevice, &nLength);
	example->lastError = res;
	if(nDebug==true) std::cout << "GetReadDevice Error: " << res << std::endl;
	if(res==0){
		textValue.append(pchDevice);
	}

	return env->NewStringUTF(textValue.c_str());

}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getDriveInfo
  (JNIEnv *env, jobject jobj)
{

    TCHAR vendorId_[9];
    TCHAR productId_[17];
    TCHAR productRevision_[5];

	jclass clazz = env->FindClass ("IsoSDKJNIPkg/DriveInfo");
	if(clazz == 0){
		if(nDebug==true) std::cout << "FindClass DriveInfo failed " << std::endl;
		return NULL;
	}

	int32 res = ::GetDeviceInformation(BS_CURRENT_DEVICE, vendorId_, productId_, productRevision_);
	if (res != 0){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetDeviceInformation Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject (clazz);

	jstring jstr1 = env->NewStringUTF(vendorId_);
	jstring jstr2 = env->NewStringUTF(productId_);
	jstring jstr3 = env->NewStringUTF(productRevision_);

	jfieldID vendorId = env->GetFieldID (clazz,"vendorId","Ljava/lang/String;");
	if (vendorId == 0){
		return NULL;
	}
	jfieldID productId = env->GetFieldID (clazz,"productId","Ljava/lang/String;");
	if (productId == 0){
		return NULL;
	}
	jfieldID productRevision = env->GetFieldID (clazz,"productRevision","Ljava/lang/String;");
	if (productRevision == 0){
		return NULL;
	}

	env->SetObjectField(obj,vendorId,jstr1);
	env->SetObjectField(obj,productId,jstr2);
	env->SetObjectField(obj,productRevision,jstr3);

	return obj;

}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getOptions
  (JNIEnv *env, jobject jobj)
{
	jclass clazz = env->FindClass ("IsoSDKJNIPkg/BurnOptions");
	if(clazz == 0){
		if(nDebug==true) std::cout << "FindClass BurnOptions failed " << std::endl;
		return NULL;
	}

	SOptions opt;
	int32 res = ::GetOptions(&opt);
	if (res != 0){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetOptions Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject (clazz);

	jfieldID volumeLabel = env->GetFieldID (clazz,"volumeLabel","Ljava/lang/String;");
	if (volumeLabel != 0){
		jstring jstr1 = env->NewStringUTF(opt.chVolumeLabel);
		env->SetObjectField(obj,volumeLabel,jstr1);
	}
	jfieldID bootImage = env->GetFieldID (clazz,"bootImage","Ljava/lang/String;");
	if (bootImage != 0){
		jstring jstr2 = env->NewStringUTF(opt.chBootImage);
		env->SetObjectField(obj,bootImage,jstr2);
	}
	jfieldID writeMethod = env->GetFieldID (clazz,"writeMethod","I");
	if (writeMethod != 0){
		env->SetIntField(obj,writeMethod,opt.nWriteMethod);
	}
	jfieldID cacheSize = env->GetFieldID (clazz,"cacheSize","I");
	if (writeMethod != 0){
		env->SetIntField(obj,cacheSize,opt.nCacheSize);
	}
	jfieldID jolietFileSystem = env->GetFieldID (clazz,"jolietFileSystem","Z");
	if (jolietFileSystem != 0){
		env->SetBooleanField(obj,jolietFileSystem,(bool)opt.bJolietFileSystem);
	}
	jfieldID bootable = env->GetFieldID (clazz,"bootable","Z");
	if (bootable != 0){
		env->SetBooleanField(obj,bootable,(bool)opt.bBootable);
	}
	jfieldID finalize = env->GetFieldID (clazz,"finalize","Z");
	if (finalize != 0){
		env->SetBooleanField(obj,finalize,(bool)opt.bFinalize);
	}
	jfieldID testBurn = env->GetFieldID (clazz,"testBurn","Z");
	if (testBurn != 0){
		env->SetBooleanField(obj,testBurn,(bool)opt.bTestBurn);
	}
	jfieldID performOPC = env->GetFieldID (clazz,"performOPC","Z");
	if (performOPC != 0){
		env->SetBooleanField(obj,performOPC,(bool)opt.bPerformOPC);
	}
	jfieldID verifyAfterBurn = env->GetFieldID (clazz,"verifyAfterBurn","Z");
	if (verifyAfterBurn != 0){
		env->SetBooleanField(obj,verifyAfterBurn,(bool)opt.bVerifyAfterBurn);
	}
	jfieldID underrunProtection = env->GetFieldID (clazz,"underrunProtection","Z");
	if (underrunProtection != 0){
		env->SetBooleanField(obj,underrunProtection,(bool)opt.bUnderrunProtection);
	}
	jfieldID ejectAfterBurn = env->GetFieldID (clazz,"ejectAfterBurn","Z");
	if (ejectAfterBurn != 0){
		env->SetBooleanField(obj,ejectAfterBurn,(bool)opt.bEjectAfterBurn);
	}
	jfieldID autoErase = env->GetFieldID (clazz,"autoErase","Z");
	if (autoErase != 0){
		env->SetBooleanField(obj,autoErase,(bool)opt.bAutoErase);
	}
	jfieldID rockRidgeFileSystem = env->GetFieldID (clazz,"rockRidgeFileSystem","Z");
	if (rockRidgeFileSystem != 0){
		env->SetBooleanField(obj,rockRidgeFileSystem,(bool)opt.bRockRidgeFileSystem);
	}
	jfieldID padDataTracks = env->GetFieldID (clazz,"padDataTracks","Z");
	if (padDataTracks != 0){
		env->SetBooleanField(obj,padDataTracks,(bool)opt.bPadDataTracks);
	}

	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setOptions
  (JNIEnv *env, jobject jobj, jobject jstruct)
{
	jclass clazz = env->GetObjectClass(jstruct);
	if(clazz == 0){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	SOptions opt;
	int32 res = ::GetOptions(&opt);
	if (res != 0){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetOptions Error: " << res << std::endl;
		return 0;
	}

	jfieldID volumeLabel = env->GetFieldID(clazz,"volumeLabel","Ljava/lang/String;");
	if(volumeLabel != 0){
		jstring strVolumeLabel = (jstring) env->GetObjectField(jstruct, volumeLabel);
		if(strVolumeLabel != NULL){
			const TCHAR *tVolumeLabel = env->GetStringUTFChars(strVolumeLabel, JNI_FALSE);
			_tcscpy(opt.chVolumeLabel, tVolumeLabel);
			env->ReleaseStringUTFChars(strVolumeLabel, tVolumeLabel);
		}

	}
	///
	jfieldID bootImage = env->GetFieldID(clazz,"bootImage","Ljava/lang/String;");
	if(bootImage != 0){
		jstring strBootImage = (jstring) env->GetObjectField(jstruct, bootImage);
		if(strBootImage != NULL){
			const TCHAR *tBootImage = env->GetStringUTFChars(strBootImage, JNI_FALSE);
			_tcscpy(opt.chBootImage, tBootImage);
			env->ReleaseStringUTFChars(strBootImage, tBootImage);
		}
	}
	///
	jfieldID jolietFileSystem = env->GetFieldID(clazz,"jolietFileSystem","Z");
	if(jolietFileSystem != 0){
		bool bJolietFileSystem = env->GetBooleanField(jstruct, jolietFileSystem);
		opt.bJolietFileSystem = bJolietFileSystem==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID bootable = env->GetFieldID(clazz,"bootable","Z");
	if(bootable != 0){
		bool bBootable = env->GetBooleanField(jstruct, bootable);
		opt.bBootable = bBootable==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID finalize = env->GetFieldID(clazz,"finalize","Z");
	if(finalize != 0){
		bool bFinalize = env->GetBooleanField(jstruct, finalize);
		opt.bFinalize = bFinalize==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID testBurn = env->GetFieldID(clazz,"testBurn","Z");
	if(testBurn != 0){
		bool bTestBurn = env->GetBooleanField(jstruct, testBurn);
		opt.bTestBurn = bTestBurn==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID performOPC = env->GetFieldID(clazz,"performOPC","Z");
	if(performOPC != 0){
		bool bPerformOPC = env->GetBooleanField(jstruct, performOPC);
		opt.bPerformOPC = bPerformOPC==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID verifyAfterBurn = env->GetFieldID(clazz,"verifyAfterBurn","Z");
	if(verifyAfterBurn != 0){
		bool bVerifyAfterBurn = env->GetBooleanField(jstruct, verifyAfterBurn);
		opt.bVerifyAfterBurn = bVerifyAfterBurn==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID underrunProtection = env->GetFieldID(clazz,"underrunProtection","Z");
	if(underrunProtection != 0){
		bool bUnderrunProtection = env->GetBooleanField(jstruct, underrunProtection);
		opt.bUnderrunProtection = bUnderrunProtection==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID ejectAfterBurn = env->GetFieldID(clazz,"ejectAfterBurn","Z");
	if(ejectAfterBurn != 0){
		bool bEjectAfterBurn = env->GetBooleanField(jstruct, ejectAfterBurn);
		opt.bEjectAfterBurn = bEjectAfterBurn==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID autoErase = env->GetFieldID(clazz,"autoErase","Z");
	if(autoErase != 0){
		bool bAutoErase = env->GetBooleanField(jstruct, autoErase);
		opt.bAutoErase = bAutoErase==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID rockRidgeFileSystem = env->GetFieldID(clazz,"rockRidgeFileSystem","Z");
	if(rockRidgeFileSystem != 0){
		bool bRockRidgeFileSystem = env->GetBooleanField(jstruct, rockRidgeFileSystem);
		opt.bRockRidgeFileSystem = bRockRidgeFileSystem==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID padDataTracks = env->GetFieldID(clazz,"padDataTracks","Z");
	if(padDataTracks != 0){
		bool bPadDataTracks = env->GetBooleanField(jstruct, padDataTracks);
		opt.bPadDataTracks = bPadDataTracks==0 ? BS_FALSE : BS_TRUE;
	}
	///
	jfieldID writeMethod = env->GetFieldID(clazz,"writeMethod","I");
	if(writeMethod != 0){
		int nWriteMethod = env->GetIntField(jstruct, writeMethod);
		if(nWriteMethod != -1)
			opt.nWriteMethod = nWriteMethod;
	}
	///
	jfieldID cacheSize = env->GetFieldID(clazz,"cacheSize","I");
	if(cacheSize != 0){
		int nCacheSize = env->GetIntField(jstruct, cacheSize);
		if(nCacheSize != -1)
			opt.nCacheSize = nCacheSize;
	}

	res = ::SetOptions(opt);

	return (int)res;
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getBootInfo
  (JNIEnv *env, jobject jobj)
{
	jclass clazz = env->FindClass ("IsoSDKJNIPkg/BootInfo");
	if(clazz == 0){
		if(nDebug==true) std::cout << "FindClass BootInfo failed " << std::endl;
		return NULL;
	}

	SBootInfoEx info;
	int32 res = ::GetBootInfoEx(&info);
	if (res != 0){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetBootInfoEx Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject (clazz);

	jfieldID developerId = env->GetFieldID (clazz,"developerId","Ljava/lang/String;");
	if (developerId != 0){
		jstring strDeveloperId = env->NewStringUTF(info.DeveloperID);
		env->SetObjectField(obj,developerId,strDeveloperId);
	}
	jfieldID loadSegment = env->GetFieldID (clazz,"loadSegment","I");
	if (loadSegment != 0){
		env->SetIntField(obj,loadSegment,info.LoadSegment);
	}
	jfieldID platformId = env->GetFieldID (clazz,"platformId","I");
	if (platformId != 0){
		env->SetIntField(obj,platformId,info.PlatformID);
	}
	jfieldID emulation = env->GetFieldID (clazz,"emulation","I");
	if (emulation != 0){
		env->SetIntField(obj,emulation,info.Emulation);
	}
	jfieldID sectorCount = env->GetFieldID (clazz,"sectorCount","I");
	if (sectorCount != 0){
		env->SetIntField(obj,sectorCount,info.SectorCount);
	}
	jfieldID bootIndicator = env->GetFieldID (clazz,"bootIndicator","Z");
	if (bootIndicator != 0){
		env->SetBooleanField(obj,bootIndicator,(bool)info.BootIndicator);
	}

	return obj;

}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setBootInfo
  ( JNIEnv *env, jobject jobj, jobject jstruct )
{

	jclass clazz = env->GetObjectClass( jstruct );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	SBootInfoEx info;
	int32 res = ::GetBootInfoEx ( &info );
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetBootInfoEx Error: " << res << std::endl;
		return 0;
	}

	jfieldID developerId = env->GetFieldID ( clazz, "developerId", "Ljava/lang/String;" );
	if( developerId != 0 ){
		jstring strDeveloperId = (jstring) env->GetObjectField ( jstruct, developerId );
		if( strDeveloperId != NULL ){
			const TCHAR *tDeveloperId = env->GetStringUTFChars ( strDeveloperId, JNI_FALSE );
			_tcscpy( info.DeveloperID, tDeveloperId );
			env->ReleaseStringUTFChars ( strDeveloperId, tDeveloperId );
		}
	}
	jfieldID bootIndicator = env->GetFieldID ( clazz, "bootIndicator", "Z" );
	if( bootIndicator != 0 ){
		bool bBootIndicator = env->GetBooleanField ( jstruct, bootIndicator );
		info.BootIndicator = bBootIndicator == 0 ? BS_FALSE : BS_TRUE;
	}
	jfieldID loadSegment = env->GetFieldID ( clazz, "loadSegment", "I" );
	if( loadSegment != 0 ){
		int nLoadSegment = env->GetIntField ( jstruct, loadSegment );
		if( nLoadSegment != -1 )
			info.LoadSegment = nLoadSegment;
	}
	jfieldID platformId = env->GetFieldID ( clazz, "platformId", "I" );
	if( platformId != 0 ){
		int nPlatformId = env->GetIntField ( jstruct, platformId );
		if( nPlatformId != -1 )
			info.PlatformID = nPlatformId;
	}
	jfieldID emulation = env->GetFieldID ( clazz, "emulation", "I" );
	if( emulation != 0 ){
		int nEmulation = env->GetIntField ( jstruct,  emulation );
		if( nEmulation != -1 )
			info.Emulation = nEmulation;
	}
	jfieldID sectorCount = env->GetFieldID ( clazz, "sectorCount", "I" );
	if( sectorCount != 0 ){
		int nSectorCount = env->GetIntField ( jstruct, sectorCount );
		if( nSectorCount != -1 )
			info.SectorCount = nSectorCount;
	}

	res = ::SetBootInfoEx ( info );

	return (int)res;
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getUDFOptions
  ( JNIEnv *env, jobject jobj )
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/UDFOptions" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass UDFOptions failed " << std::endl;
		return NULL;
	}

	SUDFOptions udfOptions;
	int32 res = ::GetUDFOptions( &udfOptions );
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetUDFOptions Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID version = env->GetFieldID ( clazz, "version", "I" );
	if ( version != 0 ){
		env->SetIntField ( obj, version, udfOptions.Version );
	}
	////
	jfieldID partitionType = env->GetFieldID ( clazz, "partitionType", "I" );
	if ( partitionType != 0 ){
		env->SetIntField ( obj, partitionType, udfOptions.PartitionType );
	}
	////
	jfieldID writeFileStreams = env->GetFieldID ( clazz, "writeFileStreams", "Z" );
	if ( writeFileStreams != 0 ){
		env->SetBooleanField ( obj, writeFileStreams, (bool)udfOptions.WriteFileStreams );
	}
	////
	jfieldID avchdDisc = env->GetFieldID ( clazz, "avchdDisc", "Z" );
	if ( avchdDisc != 0 ){
		env->SetBooleanField ( obj, avchdDisc, (bool)udfOptions.AvchdDisc );
	}

	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setUDFOptions
  ( JNIEnv *env, jobject jobj, jobject jstruct )
{
	jclass clazz = env->GetObjectClass ( jstruct );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	SUDFOptions udfOptions;
	int32 res = ::GetUDFOptions( &udfOptions );
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetUDFOptions Error: " << res << std::endl;
		return 0;
	}

	////
	jfieldID version = env->GetFieldID ( clazz, "version", "I" );
	if( version != 0 ){
		int nVersion = env->GetIntField ( jstruct, version );
		if( nVersion != -1 )
			udfOptions.Version = nVersion;
	}
	////
	jfieldID partitionType = env->GetFieldID ( clazz, "partitionType", "I" );
	if( partitionType != 0 ){
		int nPartitionType = env->GetIntField ( jstruct, partitionType );
		if( nPartitionType != -1 )
			udfOptions.PartitionType = nPartitionType;
	}
	////
	jfieldID writeFileStreams = env->GetFieldID ( clazz, "writeFileStreams", "Z" );
	if( writeFileStreams != 0 ){
		bool bWriteFileStreams = env->GetBooleanField ( jstruct, writeFileStreams );
		udfOptions.WriteFileStreams = bWriteFileStreams == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID avchdDisc = env->GetFieldID ( clazz, "avchdDisc", "Z" );
	if( avchdDisc != 0 ){
		bool bAvchdDisc = env->GetBooleanField ( jstruct, avchdDisc );
		udfOptions.AvchdDisc = bAvchdDisc == 0 ? BS_FALSE : BS_TRUE;
	}

	res = ::SetUDFOptions ( udfOptions );

	return (int)res;
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getUDFOptionsEx
  ( JNIEnv *env, jobject jobj )
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/UDFOptionsEx" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass UDFOptionsEx failed " << std::endl;
		return NULL;
	}

	SUDFOptionsEx udfOptionsEx;
	int32 res = ::GetUDFOptionsEx ( &udfOptionsEx );
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetUDFOptionsEx: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID structSize = env->GetFieldID ( clazz, "structSize", "I" );
	if ( structSize != 0 ){
		env->SetIntField ( obj, structSize, udfOptionsEx.StructSize );
	}
	////
	jfieldID mask = env->GetFieldID ( clazz, "mask", "I" );
	if ( mask != 0 ){
		env->SetIntField ( obj, mask, udfOptionsEx.Mask );
	}
	////
	jfieldID version = env->GetFieldID ( clazz, "version", "I" );
	if ( version != 0 ){
		env->SetIntField ( obj, version, udfOptionsEx.Version );
	}
	////
	jfieldID partitionType = env->GetFieldID ( clazz, "partitionType", "I" );
	if ( partitionType != 0 ){
		env->SetIntField ( obj, partitionType, udfOptionsEx.PartitionType );
	}
	////
	jfieldID writeFileStreams = env->GetFieldID ( clazz, "writeFileStreams", "Z" );
	if ( writeFileStreams != 0 ){
		env->SetBooleanField ( obj, writeFileStreams, (bool)udfOptionsEx.WriteFileStreams );
	}
	////
	jfieldID avchdDisc = env->GetFieldID ( clazz, "avchdDisc", "Z" );
	if ( avchdDisc != 0 ){
		env->SetBooleanField ( obj, avchdDisc, (bool)udfOptionsEx.AvchdDisc );
	}
	////
	jfieldID implementationId = env->GetFieldID ( clazz, "implementationId", "Ljava/lang/String;" );
	if ( implementationId != 0 ){
		jstring strImplementationId = env->NewStringUTF ( udfOptionsEx.ImplementationID );
		env->SetObjectField ( obj, implementationId, strImplementationId );
	}

	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setUDFOptionsEx
  ( JNIEnv *env, jobject jobj, jobject jstruct )
{
	jclass clazz = env->GetObjectClass ( jstruct );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	SUDFOptionsEx udfOptionsEx;
	int32 res = ::GetUDFOptionsEx ( &udfOptionsEx );
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetUDFOptionsEx Error: " << res << std::endl;
		return 0;
	}

	////
	jfieldID structSize = env->GetFieldID ( clazz, "structSize", "I" );
	if( structSize != 0 ){
		int nStructSize = env->GetIntField ( jstruct, structSize );
		if( nStructSize != -1 )
			udfOptionsEx.StructSize = nStructSize;
	}
	////
	jfieldID mask = env->GetFieldID ( clazz, "mask", "I" );
	if( mask != 0 ){
		int nMask = env->GetIntField ( jstruct, mask );
		if( nMask != -1 )
			udfOptionsEx.Mask = nMask;
	}
	////
	jfieldID version = env->GetFieldID ( clazz, "version", "I" );
	if( version != 0 ){
		int nVersion = env->GetIntField ( jstruct, version );
		if( nVersion != -1 )
			udfOptionsEx.Mask = nVersion;
	}
	////
	jfieldID partitionType = env->GetFieldID ( clazz, "partitionType", "I" );
	if( partitionType != 0 ){
		int nPartitionType = env->GetIntField ( jstruct, partitionType );
		if( nPartitionType != -1 )
			udfOptionsEx.PartitionType = nPartitionType;
	}
	////
	jfieldID writeFileStreams = env->GetFieldID ( clazz, "writeFileStreams", "Z" );
	if( writeFileStreams != 0 ){
		bool bWriteFileStreams = env->GetBooleanField ( jstruct, writeFileStreams);
		udfOptionsEx.WriteFileStreams = bWriteFileStreams == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID avchdDisc = env->GetFieldID ( clazz, "avchdDisc", "Z" );
	if( avchdDisc != 0 ){
		bool bAvchdDisc = env->GetBooleanField ( jstruct, avchdDisc );
		udfOptionsEx.AvchdDisc = bAvchdDisc == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID implementationId = env->GetFieldID ( clazz, "implementationId", "Ljava/lang/String;" );
	if( implementationId != 0 ){
		jstring strImplementationId = (jstring) env->GetObjectField ( jstruct, implementationId );
		if( strImplementationId != NULL ){
			const TCHAR *tImplementationId = env->GetStringUTFChars ( strImplementationId, JNI_FALSE );
			_tcscpy( udfOptionsEx.ImplementationID, tImplementationId );
			env->ReleaseStringUTFChars ( strImplementationId, tImplementationId );
		}
	}

	res = ::SetUDFOptionsEx ( &udfOptionsEx );

	return (int)res;
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getMediumInformation
  ( JNIEnv *env, jobject jobj )
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/MediumInformation" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass MediumInformation failed " << std::endl;
		return NULL;
	}

	SMediumInfo infoMedium;
	int32 res = ::GetMediumInformation(BS_CURRENT_DEVICE, &infoMedium);
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetMediumInformation Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID mediumType = env->GetFieldID ( clazz, "mediumType", "Ljava/lang/String;" );
	if ( mediumType != 0 ){
		jstring strMediumType = env->NewStringUTF ( infoMedium.chMediumType );
		env->SetObjectField ( obj, mediumType, strMediumType );
	}
	////
	jfieldID uPCEANCode = env->GetFieldID ( clazz, "uPCEANCode", "Ljava/lang/String;" );
	if ( uPCEANCode != 0 ){
		jstring strUPCEANCode = env->NewStringUTF ( infoMedium.chUPCEANCode );
		env->SetObjectField ( obj, uPCEANCode, strUPCEANCode );
	}
	////
	jfieldID vendorId = env->GetFieldID ( clazz, "vendorId", "Ljava/lang/String;" );
	if ( vendorId != 0 ){
		jstring strVendorId = env->NewStringUTF ( infoMedium.chVendorID );
		env->SetObjectField ( obj, vendorId, strVendorId );
	}
	////
	jfieldID firstSession = env->GetFieldID ( clazz, "firstSession", "I" );
	if ( firstSession != 0 ){
		env->SetIntField ( obj, firstSession, infoMedium.nFirstSession );
	}
	////
	jfieldID lastSession = env->GetFieldID ( clazz, "lastSession", "I" );
	if ( lastSession != 0 ){
		env->SetIntField ( obj, lastSession, infoMedium.nLastSession );
	}
	////
	jfieldID firstTrack = env->GetFieldID ( clazz, "firstTrack", "I" );
	if ( firstTrack != 0 ){
		env->SetIntField ( obj, firstTrack, infoMedium.nFirstTrack );
	}
	////
	jfieldID lastTrack = env->GetFieldID ( clazz, "lastTrack", "I" );
	if ( lastTrack != 0 ){
		env->SetIntField ( obj, lastTrack, infoMedium.nLastTrack );
	}
	////
	jfieldID lastSessionStatus = env->GetFieldID ( clazz, "lastSessionStatus", "I" );
	if ( lastSessionStatus != 0 ){
		env->SetIntField ( obj, lastSessionStatus, infoMedium.nLastSessionStatus );
	}
	////
	jfieldID mediumSize = env->GetFieldID ( clazz, "mediumSize", "D" );
	if ( mediumSize != 0 ){
		env->SetDoubleField ( obj, mediumSize, infoMedium.dMediumSize );
	}
	////
	jfieldID mediumUsedSize = env->GetFieldID ( clazz, "mediumUsedSize", "D" );
	if ( mediumUsedSize != 0 ){
		env->SetDoubleField ( obj, mediumUsedSize, infoMedium.dMediumUsedSize );
	}
	////
	jfieldID mediumFreeSize = env->GetFieldID ( clazz, "mediumFreeSize", "D" );
	if ( mediumFreeSize != 0 ){
		env->SetDoubleField ( obj, mediumFreeSize, infoMedium.dMediumFreeSize );
	}
	////
	jfieldID maxWriteSpeed = env->GetFieldID ( clazz, "maxWriteSpeed", "F" );
	if ( maxWriteSpeed != 0 ){
		env->SetDoubleField ( obj, maxWriteSpeed, infoMedium.fMaxWriteSpeed );
	}
	////
	jfieldID mediumStatus = env->GetFieldID ( clazz, "mediumStatus", "I" );
	if ( mediumStatus != 0 ){
		env->SetIntField ( obj, mediumStatus, infoMedium.nMediumStatus );
	}
	////
	jfieldID mediumTypeCode = env->GetFieldID ( clazz, "mediumTypeCode", "S" );
	if ( mediumTypeCode != 0 ){
		env->SetShortField ( obj, mediumTypeCode, infoMedium.wMediumTypeCode );
	}
	////
	jfieldID extendedMediumType = env->GetFieldID ( clazz, "extendedMediumType", "S" );
	if ( extendedMediumType != 0 ){
		env->SetShortField ( obj, extendedMediumType, infoMedium.nExtendedMediumType );
	}


	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setISOInfoEx
  ( JNIEnv *env, jobject jobj, jobject jstruct )
{
	jclass clazz = env->GetObjectClass ( jstruct );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	SISOInfoEx isoInfo;
	int32 res = ::GetISOInfoEx(&isoInfo);
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetISOInfoEx Error: " << res << std::endl;
		return 0;
	}

	////
	jfieldID iSOAbstractFileIdentifier = env->GetFieldID ( clazz, "iSOAbstractFileIdentifier", "Ljava/lang/String;" );
	if( iSOAbstractFileIdentifier != 0 ){
		jstring strISOAbstractFileIdentifier = (jstring) env->GetObjectField ( jstruct, iSOAbstractFileIdentifier );
		if( strISOAbstractFileIdentifier != NULL ){
			const TCHAR *tISOAbstractFileIdentifier = env->GetStringUTFChars ( strISOAbstractFileIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOAbstractFileIdentifier, tISOAbstractFileIdentifier );
			env->ReleaseStringUTFChars ( strISOAbstractFileIdentifier, tISOAbstractFileIdentifier );
		}
	}
	////
	jfieldID iSOApplicationIdentifier = env->GetFieldID ( clazz, "iSOApplicationIdentifier", "Ljava/lang/String;" );
	if( iSOApplicationIdentifier != 0 ){
		jstring strISOApplicationIdentifier = (jstring) env->GetObjectField ( jstruct, iSOApplicationIdentifier );
		if( strISOApplicationIdentifier != NULL ){
			const TCHAR *tISOApplicationIdentifier = env->GetStringUTFChars ( strISOApplicationIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOApplicationIdentifier, tISOApplicationIdentifier );
			env->ReleaseStringUTFChars ( strISOApplicationIdentifier, tISOApplicationIdentifier );
		}
	}
	////
	jfieldID iSOBiblioIdentifier = env->GetFieldID ( clazz, "iSOBiblioIdentifier", "Ljava/lang/String;" );
	if( iSOBiblioIdentifier != 0 ){
		jstring strISOBiblioIdentifier = (jstring) env->GetObjectField ( jstruct, iSOBiblioIdentifier );
		if( strISOBiblioIdentifier != NULL ){
			const TCHAR *tISOBiblioIdentifier = env->GetStringUTFChars ( strISOBiblioIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOBiblioIdentifier, tISOBiblioIdentifier );
			env->ReleaseStringUTFChars ( strISOBiblioIdentifier, tISOBiblioIdentifier );
		}
	}
	////
	jfieldID iSOCopyrightFileIdentifier = env->GetFieldID ( clazz, "iSOCopyrightFileIdentifier", "Ljava/lang/String;" );
	if( iSOCopyrightFileIdentifier != 0 ){
		jstring strISOCopyrightFileIdentifier = (jstring) env->GetObjectField ( jstruct, iSOCopyrightFileIdentifier );
		if( strISOCopyrightFileIdentifier != NULL ){
			const TCHAR *tISOCopyrightFileIdentifier = env->GetStringUTFChars ( strISOCopyrightFileIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOCopyrightFileIdentifier, tISOCopyrightFileIdentifier );
			env->ReleaseStringUTFChars ( strISOCopyrightFileIdentifier, tISOCopyrightFileIdentifier );
		}
	}
	////
	jfieldID iSODataPreparerIdentifier = env->GetFieldID ( clazz, "iSODataPreparerIdentifier", "Ljava/lang/String;" );
	if( iSODataPreparerIdentifier != 0 ){
		jstring strISODataPreparerIdentifier = (jstring) env->GetObjectField ( jstruct, iSODataPreparerIdentifier );
		if( strISODataPreparerIdentifier != NULL ){
			const TCHAR *tISODataPreparerIdentifier = env->GetStringUTFChars ( strISODataPreparerIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISODataPreparerIdentifier, tISODataPreparerIdentifier );
			env->ReleaseStringUTFChars ( strISODataPreparerIdentifier, tISODataPreparerIdentifier );
		}
	}
	////
	jfieldID iSOPublisherIdentifier = env->GetFieldID ( clazz, "iSOPublisherIdentifier", "Ljava/lang/String;" );
	if( iSOPublisherIdentifier != 0 ){
		jstring strISOPublisherIdentifier = (jstring) env->GetObjectField ( jstruct, iSOPublisherIdentifier );
		if( strISOPublisherIdentifier != NULL ){
			const TCHAR *tISOPublisherIdentifier = env->GetStringUTFChars ( strISOPublisherIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOPublisherIdentifier, tISOPublisherIdentifier );
			env->ReleaseStringUTFChars ( strISOPublisherIdentifier, tISOPublisherIdentifier );
		}
	}
	////
	jfieldID iSOSetIdentifier = env->GetFieldID ( clazz, "iSOSetIdentifier", "Ljava/lang/String;" );
	if( iSOSetIdentifier != 0 ){
		jstring strISOSetIdentifier = (jstring) env->GetObjectField ( jstruct, iSOSetIdentifier );
		if( strISOSetIdentifier != NULL ){
			const TCHAR *tISOSetIdentifier = env->GetStringUTFChars ( strISOSetIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOSetIdentifier, tISOSetIdentifier );
			env->ReleaseStringUTFChars ( strISOSetIdentifier, tISOSetIdentifier );
		}
	}
	////
	jfieldID iSOSystemIdentifier = env->GetFieldID ( clazz, "iSOSystemIdentifier", "Ljava/lang/String;" );
	if( iSOSystemIdentifier != 0 ){
		jstring strISOSystemIdentifier = (jstring) env->GetObjectField ( jstruct, iSOSystemIdentifier );
		if( strISOSystemIdentifier != NULL ){
			const TCHAR *tISOSystemIdentifier = env->GetStringUTFChars ( strISOSystemIdentifier, JNI_FALSE );
			_tcscpy( isoInfo.ISOSystemIdentifier, tISOSystemIdentifier );
			env->ReleaseStringUTFChars ( strISOSystemIdentifier, tISOSystemIdentifier );
		}
	}
	////
	jfieldID iSOLevel = env->GetFieldID ( clazz, "iSOLevel", "I" );
	if( iSOLevel != 0 ){
		int nISOLevel = env->GetIntField ( jstruct, iSOLevel );
		if( nISOLevel != -1 )
			isoInfo.ISOLevel = nISOLevel;
	}
	////
	jfieldID iSOAllowManyDirectories = env->GetFieldID ( clazz, "iSOAllowManyDirectories", "Z" );
	if( iSOAllowManyDirectories != 0 ){
		bool bISOAllowManyDirectories = env->GetBooleanField ( jstruct, iSOAllowManyDirectories);
		isoInfo.ISOAllowManyDirectories = bISOAllowManyDirectories == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOAllowLowercaseNames = env->GetFieldID ( clazz, "iSOAllowLowercaseNames", "Z" );
	if( iSOAllowLowercaseNames != 0 ){
		bool bISOAllowLowercaseNames = env->GetBooleanField ( jstruct, iSOAllowLowercaseNames);
		isoInfo.ISOAllowLowercaseNames = bISOAllowLowercaseNames == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOAllowLongISO9660Names = env->GetFieldID ( clazz, "iSOAllowLongISO9660Names", "Z" );
	if( iSOAllowLongISO9660Names != 0 ){
		bool bISOAllowLongISO9660Names = env->GetBooleanField ( jstruct, iSOAllowLongISO9660Names);
		isoInfo.ISOAllowLongISO9660Names = bISOAllowLongISO9660Names == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOAllowLongJolietNames = env->GetFieldID ( clazz, "iSOAllowLongJolietNames", "Z" );
	if( iSOAllowLongJolietNames != 0 ){
		bool bISOAllowLongJolietNames = env->GetBooleanField ( jstruct, iSOAllowLongJolietNames);
		isoInfo.ISOAllowLongJolietNames = bISOAllowLongJolietNames == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOUseCreationDateTime = env->GetFieldID ( clazz, "iSOUseCreationDateTime", "Z" );
	if( iSOUseCreationDateTime != 0 ){
		bool bISOUseCreationDateTime = env->GetBooleanField ( jstruct, iSOUseCreationDateTime);
		isoInfo.ISOUseCreationDateTime = bISOUseCreationDateTime == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOUseModificationDateTime = env->GetFieldID ( clazz, "iSOUseModificationDateTime", "Z" );
	if( iSOUseModificationDateTime != 0 ){
		bool bISOUseModificationDateTime = env->GetBooleanField ( jstruct, iSOUseModificationDateTime);
		isoInfo.ISOUseModificationDateTime = bISOUseModificationDateTime  == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOUseExpirationDateTime = env->GetFieldID ( clazz, "iSOUseExpirationDateTime", "Z" );
	if( iSOUseExpirationDateTime != 0 ){
		bool bISOUseExpirationDateTime = env->GetBooleanField ( jstruct, iSOUseExpirationDateTime);
		isoInfo.ISOUseExpirationDateTime = bISOUseExpirationDateTime == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID iSOUseEffectiveDateTime = env->GetFieldID ( clazz, "iSOUseEffectiveDateTime", "Z" );
	if( iSOUseEffectiveDateTime != 0 ){
		bool bISOUseEffectiveDateTime = env->GetBooleanField ( jstruct, iSOUseEffectiveDateTime);
		isoInfo.ISOUseEffectiveDateTime = bISOUseEffectiveDateTime == 0 ? BS_FALSE : BS_TRUE;
	}

	//We will set the dat only if the user set the usage to true. Else we save the time
	if( isoInfo.ISOUseCreationDateTime == BS_TRUE) {
		jfieldID iSOCreationDateTime = env->GetFieldID ( clazz, "iSOCreationDateTime", "Ljava/lang/String;" );
		if( iSOCreationDateTime != 0 ){
			jstring strISOCreationDateTime = (jstring) env->GetObjectField ( jstruct, iSOCreationDateTime );
			if( strISOCreationDateTime != NULL ){
				const TCHAR *tISOCreationDateTime = env->GetStringUTFChars ( strISOCreationDateTime, JNI_FALSE );
				struct tm tmISOCreationDateTime;

				if (strptime(tISOCreationDateTime, "%Y/%m/%d %H:%M:%S", &tmISOCreationDateTime) == NULL){
					if(nDebug==true) std::cout << "strptime failed " << std::endl;
					return 0;
				}
				isoInfo.ISOCreationDateTime.nYear = tmISOCreationDateTime.tm_year;
				isoInfo.ISOCreationDateTime.nMonth = tmISOCreationDateTime.tm_mon;
				isoInfo.ISOCreationDateTime.nDay = tmISOCreationDateTime.tm_mday;
				isoInfo.ISOCreationDateTime.nHour = tmISOCreationDateTime.tm_hour;
				isoInfo.ISOCreationDateTime.nMinute = tmISOCreationDateTime.tm_min;
				isoInfo.ISOCreationDateTime.nSecond = tmISOCreationDateTime.tm_sec;
				env->ReleaseStringUTFChars ( strISOCreationDateTime, tISOCreationDateTime );
			}
		}
	}
	///
	if( isoInfo.ISOUseModificationDateTime == BS_TRUE ) {
		jfieldID iSOModificationDateTime = env->GetFieldID ( clazz, "iSOModificationDateTime", "Ljava/lang/String;" );
		if( iSOModificationDateTime != 0 ){
			jstring strISOModificationDateTime = (jstring) env->GetObjectField ( jstruct, iSOModificationDateTime );
			if( strISOModificationDateTime != NULL ){
				const TCHAR *tISOModificationDateTime = env->GetStringUTFChars ( strISOModificationDateTime, JNI_FALSE );
				struct tm tmISOModificationDateTime;

				if (strptime(tISOModificationDateTime, "%Y/%m/%d %H:%M:%S", &tmISOModificationDateTime) == NULL){
					if(nDebug==true) std::cout << "strptime failed " << std::endl;
					return 0;
				}
				isoInfo.ISOModificationDateTime.nYear = tmISOModificationDateTime.tm_year;
				isoInfo.ISOModificationDateTime.nMonth = tmISOModificationDateTime.tm_mon;
				isoInfo.ISOModificationDateTime.nDay = tmISOModificationDateTime.tm_mday;
				isoInfo.ISOModificationDateTime.nHour = tmISOModificationDateTime.tm_hour;
				isoInfo.ISOModificationDateTime.nMinute = tmISOModificationDateTime.tm_min;
				isoInfo.ISOModificationDateTime.nSecond = tmISOModificationDateTime.tm_sec;
				env->ReleaseStringUTFChars ( strISOModificationDateTime, tISOModificationDateTime );

			}
		}
	}
	///
	if( isoInfo.ISOUseExpirationDateTime == BS_TRUE ){
		jfieldID iSOExpirationDateTime = env->GetFieldID ( clazz, "iSOExpirationDateTime", "Ljava/lang/String;" );
		if( iSOExpirationDateTime != 0 ){
			jstring strISOExpirationDateTime = (jstring) env->GetObjectField ( jstruct, iSOExpirationDateTime );
			if( strISOExpirationDateTime != NULL ){
				const TCHAR *tISOExpirationDateTime = env->GetStringUTFChars (strISOExpirationDateTime, JNI_FALSE );
				struct tm tmISOExpirationDateTime;

				if (strptime(tISOExpirationDateTime, "%Y/%m/%d %H:%M:%S", &tmISOExpirationDateTime) == NULL){
					if(nDebug==true) std::cout << "strptime failed " << std::endl;
					return 0;
				}
				isoInfo.ISOExpirationDateTime.nYear = tmISOExpirationDateTime.tm_year;
				isoInfo.ISOExpirationDateTime.nMonth = tmISOExpirationDateTime.tm_mon;
				isoInfo.ISOExpirationDateTime.nDay = tmISOExpirationDateTime.tm_mday;
				isoInfo.ISOExpirationDateTime.nHour = tmISOExpirationDateTime.tm_hour;
				isoInfo.ISOExpirationDateTime.nMinute = tmISOExpirationDateTime.tm_min;
				isoInfo.ISOExpirationDateTime.nSecond = tmISOExpirationDateTime.tm_sec;
				env->ReleaseStringUTFChars ( strISOExpirationDateTime, tISOExpirationDateTime );

			}
		}
	}
	///
	if( isoInfo.ISOUseEffectiveDateTime == BS_TRUE ){
		jfieldID iSOEffectiveDateTime = env->GetFieldID ( clazz, "iSOEffectiveDateTime", "Ljava/lang/String;" );
		if( iSOEffectiveDateTime != 0 ){
			jstring strISOEffectiveDateTime = (jstring) env->GetObjectField ( jstruct, iSOEffectiveDateTime );
			if( strISOEffectiveDateTime != NULL ){
				const TCHAR *tISOEffectiveDateTime = env->GetStringUTFChars (strISOEffectiveDateTime, JNI_FALSE );
				struct tm tmISOEffectiveDateTime;

				if (strptime(tISOEffectiveDateTime, "%Y/%m/%d %H:%M:%S", &tmISOEffectiveDateTime) != NULL){
					isoInfo.ISOEffectiveDateTime.nYear = tmISOEffectiveDateTime.tm_year;
					isoInfo.ISOEffectiveDateTime.nMonth = tmISOEffectiveDateTime.tm_mon;
					isoInfo.ISOEffectiveDateTime.nDay = tmISOEffectiveDateTime.tm_mday;
					isoInfo.ISOEffectiveDateTime.nHour = tmISOEffectiveDateTime.tm_hour;
					isoInfo.ISOEffectiveDateTime.nMinute = tmISOEffectiveDateTime.tm_min;
					isoInfo.ISOEffectiveDateTime.nSecond = tmISOEffectiveDateTime.tm_sec;
				}

				env->ReleaseStringUTFChars ( strISOEffectiveDateTime, tISOEffectiveDateTime );

			}
		}
	}

	//jstring strLocalTime = new jstring("2021/01/01 00:00:00");
	//const TCHAR *localTime = env->GetStringUTFChars ( strLocalTime, JNI_FALSE );




	//Struct ist int. Also aufbauen.
	//Wohl seit 1900, denn das Ergebnis 121
	//std::cout << "Year" << tm.tm_year << std::endl;
	//std::cout << "Month" << tm.tm_mon  << std::endl;
	//std::cout << "Day" << tm.tm_mday << std::endl;


	//env->ReleaseStringUTFChars ( strLocalTime, localTime );

	res = ::SetISOInfoEx(isoInfo);

	return (int)res;
}

//Alle Funktionen mit CurrentDevice im Interface noch auf das Device erweitern.
//Muss ich den neuen UTF8 String auch releasen?
JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getISOInfoEx
  ( JNIEnv *env, jobject jobj )
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/ISOInfoEx" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass ISOInfoEx failed" << std::endl;
		return NULL;
	}

	SISOInfoEx isoInfo;
	int32 res = ::GetISOInfoEx(&isoInfo);
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetISOInfoEx Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID iSOAbstractFileIdentifier = env->GetFieldID ( clazz, "iSOAbstractFileIdentifier", "Ljava/lang/String;" );
	if ( iSOAbstractFileIdentifier != 0 ){
		jstring strISOAbstractFileIdentifier = env->NewStringUTF ( isoInfo.ISOAbstractFileIdentifier);
		env->SetObjectField ( obj, iSOAbstractFileIdentifier, strISOAbstractFileIdentifier );
	}
	////
	jfieldID iSOApplicationIdentifier = env->GetFieldID ( clazz, "iSOApplicationIdentifier", "Ljava/lang/String;" );
	if ( iSOApplicationIdentifier != 0 ){
		jstring strISOApplicationIdentifier = env->NewStringUTF ( isoInfo.ISOApplicationIdentifier);
		env->SetObjectField ( obj, iSOApplicationIdentifier, strISOApplicationIdentifier );
	}
	////
	jfieldID iSOBiblioIdentifier = env->GetFieldID ( clazz, "iSOBiblioIdentifier", "Ljava/lang/String;" );
	if ( iSOBiblioIdentifier != 0 ){
		jstring strISOBiblioIdentifier = env->NewStringUTF ( isoInfo.ISOBiblioIdentifier);
		env->SetObjectField ( obj, iSOBiblioIdentifier, strISOBiblioIdentifier );
	}
	////
	jfieldID iSOCopyrightFileIdentifier = env->GetFieldID ( clazz, "iSOCopyrightFileIdentifier", "Ljava/lang/String;" );
	if ( iSOCopyrightFileIdentifier != 0 ){
		jstring strISOCopyrightFileIdentifier = env->NewStringUTF ( isoInfo.ISOCopyrightFileIdentifier);
		env->SetObjectField ( obj, iSOCopyrightFileIdentifier, strISOCopyrightFileIdentifier );
	}
	////
	jfieldID iSODataPreparerIdentifier = env->GetFieldID ( clazz, "iSODataPreparerIdentifier", "Ljava/lang/String;" );
	if ( iSODataPreparerIdentifier != 0 ){
		jstring strISODataPreparerIdentifier = env->NewStringUTF ( isoInfo.ISODataPreparerIdentifier);
		env->SetObjectField ( obj, iSODataPreparerIdentifier, strISODataPreparerIdentifier );
	}
	////
	jfieldID iSOPublisherIdentifier = env->GetFieldID ( clazz, "iSOPublisherIdentifier", "Ljava/lang/String;" );
	if ( iSOPublisherIdentifier != 0 ){
		jstring strISOPublisherIdentifier = env->NewStringUTF ( isoInfo.ISOPublisherIdentifier);
		env->SetObjectField ( obj, iSOPublisherIdentifier, strISOPublisherIdentifier );
	}
	////
	jfieldID iSOSetIdentifier = env->GetFieldID ( clazz, "iSOSetIdentifier", "Ljava/lang/String;" );
	if ( iSOSetIdentifier != 0 ){
		jstring strISOSetIdentifier = env->NewStringUTF ( isoInfo.ISOSetIdentifier);
		env->SetObjectField ( obj, iSOSetIdentifier, strISOSetIdentifier );
	}
	////
	jfieldID iSOSystemIdentifier = env->GetFieldID ( clazz, "iSOSystemIdentifier", "Ljava/lang/String;" );
	if ( iSOSystemIdentifier != 0 ){
		jstring strISOSystemIdentifier = env->NewStringUTF ( isoInfo.ISOSystemIdentifier);
		env->SetObjectField ( obj, iSOSystemIdentifier, strISOSystemIdentifier );
	}
	////
	jfieldID iSOLevel = env->GetFieldID ( clazz, "iSOLevel", "I" );
	if ( iSOLevel != 0 ){
		env->SetIntField ( obj, iSOLevel, isoInfo.ISOLevel );
	}
	////
	jfieldID iSOAddSuffix = env->GetFieldID ( clazz, "iSOAddSuffix", "Z" );
	if ( iSOAddSuffix != 0 ){
		env->SetBooleanField ( obj, iSOAddSuffix, (bool)isoInfo.ISOAddSuffix );
	}
	////
	jfieldID iSOAllowManyDirectories = env->GetFieldID ( clazz, "iSOAllowManyDirectories", "Z" );
	if ( iSOAllowManyDirectories != 0 ){
		env->SetBooleanField ( obj, iSOAllowManyDirectories, (bool)isoInfo.ISOAllowManyDirectories );
	}
	////
	jfieldID iSOAllowLowercaseNames = env->GetFieldID ( clazz, "iSOAllowLowercaseNames", "Z" );
	if ( iSOAllowLowercaseNames != 0 ){
		env->SetBooleanField ( obj, iSOAllowLowercaseNames, (bool)isoInfo.ISOAllowLowercaseNames );
	}
	////
	jfieldID iSOAllowLongISO9660Names = env->GetFieldID ( clazz, "iSOAllowLongISO9660Names", "Z" );
	if ( iSOAllowLongISO9660Names != 0 ){
		env->SetBooleanField ( obj, iSOAllowLongISO9660Names, (bool)isoInfo.ISOAllowLongISO9660Names );
	}
	////
	jfieldID iSOAllowLongJolietNames = env->GetFieldID ( clazz, "iSOAllowLongJolietNames", "Z" );
	if ( iSOAllowLongJolietNames != 0 ){
		env->SetBooleanField ( obj, iSOAllowLongJolietNames, (bool)isoInfo.ISOAllowLongJolietNames );
	}
	////
	jfieldID iSOUseCreationDateTime = env->GetFieldID ( clazz, "iSOUseCreationDateTime", "Z" );
	if ( iSOUseCreationDateTime != 0 ){
		env->SetBooleanField ( obj, iSOUseCreationDateTime, (bool)isoInfo.ISOUseCreationDateTime );
	}
	////
	jfieldID iSOUseModificationDateTime = env->GetFieldID ( clazz, "iSOUseModificationDateTime", "Z" );
	if ( iSOUseModificationDateTime != 0 ){
		env->SetBooleanField ( obj, iSOUseModificationDateTime, (bool)isoInfo.ISOUseModificationDateTime );
	}
	////
	jfieldID iSOUseExpirationDateTime = env->GetFieldID ( clazz, "iSOUseExpirationDateTime", "Z" );
	if ( iSOUseExpirationDateTime != 0 ){
		env->SetBooleanField ( obj, iSOUseExpirationDateTime, (bool)isoInfo.ISOUseExpirationDateTime );
	}
	////
	jfieldID iSOUseEffectiveDateTime = env->GetFieldID ( clazz, "iSOUseEffectiveDateTime", "Z" );
	if ( iSOUseEffectiveDateTime != 0 ){
		env->SetBooleanField ( obj, iSOUseEffectiveDateTime, (bool)isoInfo.ISOUseEffectiveDateTime );
	}

	//%Y/%m/%d %H:%M:%S
	////
	jfieldID iSOCreationDateTime = env->GetFieldID ( clazz, "iSOCreationDateTime", "Ljava/lang/String;" );
	if ( iSOCreationDateTime != 0 ){


		TCHAR buffer[50];
		sprintf (buffer, "%d/%02d/%02d %02d:%02d:%02d", isoInfo.ISOCreationDateTime.nYear + 1900,
				isoInfo.ISOCreationDateTime.nMonth,
				isoInfo.ISOCreationDateTime.nDay,
				isoInfo.ISOCreationDateTime.nHour,
				isoInfo.ISOCreationDateTime.nMinute,
				isoInfo.ISOCreationDateTime.nSecond);
		std::string time1(buffer);
		jstring strISOCreationDateTime = env->NewStringUTF ( time1.c_str());
		env->SetObjectField ( obj, iSOCreationDateTime, strISOCreationDateTime );

	}
	////
	jfieldID iSOModificationDateTime = env->GetFieldID ( clazz, "iSOModificationDateTime", "Ljava/lang/String;" );
	if ( iSOModificationDateTime != 0 ){

		TCHAR buffer[50];
		sprintf (buffer, "%d/%02d/%02d %02d:%02d:%02d", isoInfo.ISOModificationDateTime.nYear + 1900,
				isoInfo.ISOModificationDateTime.nMonth,
				isoInfo.ISOModificationDateTime.nDay,
				isoInfo.ISOModificationDateTime.nHour,
				isoInfo.ISOModificationDateTime.nMinute,
				isoInfo.ISOModificationDateTime.nSecond);
		std::string time1(buffer);
		jstring strISOModificationDateTime = env->NewStringUTF ( time1.c_str());
		env->SetObjectField ( obj, iSOModificationDateTime, strISOModificationDateTime );
	}
	////
	jfieldID iSOExpirationDateTime = env->GetFieldID ( clazz, "iSOExpirationDateTime", "Ljava/lang/String;" );
	if ( iSOExpirationDateTime != 0 ){

		TCHAR buffer[50];
		sprintf (buffer, "%d/%02d/%02d %02d:%02d:%02d", isoInfo.ISOExpirationDateTime.nYear + 1900,
				isoInfo.ISOExpirationDateTime.nMonth,
				isoInfo.ISOExpirationDateTime.nDay,
				isoInfo.ISOExpirationDateTime.nHour,
				isoInfo.ISOExpirationDateTime.nMinute,
				isoInfo.ISOExpirationDateTime.nSecond);
		std::string time1(buffer);
		jstring strISOExpirationDateTime = env->NewStringUTF ( time1.c_str());
		env->SetObjectField ( obj, iSOExpirationDateTime, strISOExpirationDateTime );
	}
	////
	jfieldID iSOEffectiveDateTime = env->GetFieldID ( clazz, "iSOEffectiveDateTime", "Ljava/lang/String;" );
	if ( iSOEffectiveDateTime != 0 ){
		TCHAR buffer[50];
		sprintf (buffer, "%d/%02d/%02d %02d:%02d:%02d", isoInfo.ISOEffectiveDateTime.nYear + 1900,
				isoInfo.ISOEffectiveDateTime.nMonth,
				isoInfo.ISOEffectiveDateTime.nDay,
				isoInfo.ISOEffectiveDateTime.nHour,
				isoInfo.ISOEffectiveDateTime.nMinute,
				isoInfo.ISOEffectiveDateTime.nSecond);
		std::string time1(buffer);
		jstring strISOEffectiveDateTime = env->NewStringUTF ( time1.c_str());
		env->SetObjectField ( obj, iSOEffectiveDateTime, strISOEffectiveDateTime );
	}

	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_lockDevice
  ( JNIEnv *env, jobject jObj, jint lDeviceIndex, jboolean lLock)
{
 	int32 res = ::LockMedium((int)lDeviceIndex,(bool)lLock);
 	if(nDebug==true)  std::cout << "Lock Medium: " << res << std::endl;
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_burnISO
  ( JNIEnv *env, jobject jObj, jstring lFilePath)
{
	const TCHAR *isoFile = env->GetStringUTFChars(lFilePath, JNI_FALSE);
	SOptions opt;
	::GetOptions(&opt);

	int32 res = ::BurnISO(isoFile,opt);
 	if(nDebug==true) std::cout << "BurnIso: " << res << std::endl;
	env->ReleaseStringUTFChars(lFilePath, isoFile);

	return (int)res;
}

JNIEXPORT jdouble JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getImageSize
  ( JNIEnv *env, jobject jObj)
{
	//Must called Prepare before
	//MB is fSize = fSize / 1024 / 1024
	double fSize = 0.0;
	int32 res = ::GetImageSize(&fSize);
	example->lastError = res;

	return fSize;
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getSessionInformation
  ( JNIEnv *env, jobject jobj, jint nSession )
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/SessionInfo" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass SessionInfo failed" << std::endl;
		return NULL;
	}

	//First Session is 1 not 0
	SSessionInfo info;
	int32 res = GetSessionInformation(BS_CURRENT_DEVICE, (int)nSession, &info);
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetSessionInformation Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID sessionSize = env->GetFieldID ( clazz, "sessionSize", "J" );
	if ( sessionSize != 0 ){
		env->SetLongField ( obj, sessionSize, info.dSessionSize );
	}
	////
	jfieldID lastSession = env->GetFieldID ( clazz, "lastSession", "Z" );
	if ( lastSession != 0 ){
		env->SetBooleanField ( obj, lastSession, (bool)info.bLastSession );
	}
	////
	jfieldID startLBA = env->GetFieldID ( clazz, "startLBA", "J" );
	if ( startLBA != 0 ){
		env->SetLongField ( obj, startLBA, info.dStartLBA );
	}
	////
	jfieldID firstTrack = env->GetFieldID ( clazz, "firstTrack", "J" );
	if ( firstTrack != 0 ){
		env->SetLongField ( obj, firstTrack, info.nFirstTrack );
	}
	////
	jfieldID lastTrack = env->GetFieldID ( clazz, "lastTrack", "J" );
	if ( lastTrack != 0 ){
		env->SetLongField ( obj, lastTrack, info.nLastTrack );
	}

	return obj;
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getTrackInformation
  ( JNIEnv *env, jobject jobj, jint nTrack)
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/TrackInfo" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass TrackInfo failed" << std::endl;
		return NULL;
	}

	//nTrack is a number out of session nFirstTrack and nLastTrack
	STrackInfo ti;
	int32 res = ::GetTrackInformation(BS_CURRENT_DEVICE, nTrack, &ti);
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetTrackInformation Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID trackNumber = env->GetFieldID ( clazz, "trackNumber", "S" );
	if ( trackNumber != 0 ){
		env->SetShortField ( obj, trackNumber, ti.nTrackNumber );
	}
	////
	jfieldID sessionNumber = env->GetFieldID ( clazz, "sessionNumber", "S" );
	if ( sessionNumber != 0 ){
		env->SetShortField ( obj, sessionNumber, ti.nSessionNumber );
	}
	////
	jfieldID startLBA = env->GetFieldID ( clazz, "startLBA", "I" );
	if ( startLBA != 0 ){
		env->SetIntField ( obj, startLBA, (int)ti.nStartLBA );
	}
	////
	jfieldID trackSize = env->GetFieldID ( clazz, "trackSize", "I" );
	if ( trackSize != 0 ){
		env->SetIntField ( obj, trackSize, ti.nSize );
	}
	////
	jfieldID trackFormat = env->GetFieldID ( clazz, "trackFormat", "I" );
	if ( trackFormat != 0 ){
		env->SetIntField ( obj, trackFormat, (int)ti.nFormat );
	}
	////
	jfieldID trackFS = env->GetFieldID ( clazz, "trackFS", "C" );
	if ( trackFS != 0 ){
		env->SetCharField ( obj, trackFS, ti.nFileSystem );
	}

	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_closeSession
  ( JNIEnv *env, jobject jobj )
{
	int32 res = ::CloseSession(BS_CURRENT_DEVICE);
	return (int)res;
}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getErrorDevice
  ( JNIEnv *env, jobject jobj )
{
	std::string driveName = "";

	TCHAR chDrive[2048];
	int32 nLength = 2048;

	int32 res = ::GetErrorDeviceName( chDrive, nLength );
	example->lastError = res;
	if(res==0){
		driveName.append(chDrive);
	}

	return env->NewStringUTF(driveName.c_str());
}

JNIEXPORT jobject JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getDeviceInformationEx
  ( JNIEnv *env, jobject jobj )
{
	jclass clazz = env->FindClass ( "IsoSDKJNIPkg/ExtendedDeviceInformation" );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "FindClass ExtendedDeviceInformation failed" << std::endl;
		return NULL;
	}

	//nTrack is a number out of session nFirstTrack and nLastTrack
	SExtendedDeviceInformation driveInfo;
	int32 res = ::GetDeviceInformationEx(BS_CURRENT_DEVICE, &driveInfo);
	if ( res != 0 ){
		example->lastError = res;
		if(nDebug==true) std::cout << "GetDeviceInformationEx Error: " << res << std::endl;
		return NULL;
	}

	jobject obj = env->AllocObject ( clazz );

	////
	jfieldID strName = env->GetFieldID ( clazz, "strName", "Ljava/lang/String;" );
	if ( strName != 0 ){
		jstring strStrName = env->NewStringUTF ( driveInfo.lpszName);
		env->SetObjectField ( obj, strName, strStrName );
	}
	////
	jfieldID strRevision = env->GetFieldID ( clazz, "strRevision", "Ljava/lang/String;" );
	if ( strRevision != 0 ){
		jstring strStrRevision = env->NewStringUTF ( driveInfo.lpszRevision );
		env->SetObjectField ( obj, strRevision, strStrRevision );
	}
	////
	jfieldID loaderType = env->GetFieldID ( clazz, "loaderType", "Ljava/lang/String;" );
	if ( loaderType != 0 ){
		jstring strLoaderType = env->NewStringUTF ( driveInfo.lpszLoaderType );
		env->SetObjectField ( obj, loaderType, strLoaderType );
	}
	////
	jfieldID connectionInterface = env->GetFieldID ( clazz, "connectionInterface", "Ljava/lang/String;" );
	if ( connectionInterface != 0 ){
		jstring strConnectionInterface = env->NewStringUTF ( driveInfo.lpszConnectionInterface );
		env->SetObjectField ( obj, connectionInterface, strConnectionInterface );
	}
	////
	jfieldID physicalInterface = env->GetFieldID ( clazz, "physicalInterface", "Ljava/lang/String;" );
	if ( physicalInterface != 0 ){
		jstring strPhysicalInterface = env->NewStringUTF ( driveInfo.lpszPhysicalInterface );
		env->SetObjectField ( obj, physicalInterface, strPhysicalInterface );
	}
	////
	jfieldID serialNumber = env->GetFieldID ( clazz, "serialNumber", "Ljava/lang/String;" );
	if ( serialNumber != 0 ){
		jstring strSerialNumber = env->NewStringUTF ( driveInfo.lpszSerialNumber );
		env->SetObjectField ( obj, serialNumber, strSerialNumber );
	}
	////
	jfieldID regionCode = env->GetFieldID ( clazz, "regionCode", "I" );
	if ( regionCode != 0 ){
		env->SetIntField ( obj, regionCode, driveInfo.nRegionCode );
	}
	////
	jfieldID regionCodeChangesLeft = env->GetFieldID ( clazz, "regionCodeChangesLeft", "I" );
	if ( regionCodeChangesLeft != 0 ){
		env->SetIntField ( obj, regionCodeChangesLeft, driveInfo.nRegionCodeChangesLeft );
	}
	////
	jfieldID numberOfVolumeLevels = env->GetFieldID ( clazz, "numberOfVolumeLevels", "I" );
	if ( numberOfVolumeLevels != 0 ){
		env->SetIntField ( obj, numberOfVolumeLevels, driveInfo.nNumberOfVolumeLevels );
	}
	////
	jfieldID bufferSize = env->GetFieldID ( clazz, "bufferSize", "I" );
	if ( bufferSize != 0 ){
		env->SetIntField ( obj, bufferSize, driveInfo.nBufferSize );
	}
	////
	jfieldID readRetryCount = env->GetFieldID ( clazz, "readRetryCount", "I" );
	if ( readRetryCount != 0 ){
		env->SetIntField ( obj, readRetryCount, driveInfo.nReadRetryCount );
	}
	////
	jfieldID regionCodeVendorResetLeft = env->GetFieldID ( clazz, "regionCodeVendorResetLeft", "I" );
	if ( regionCodeVendorResetLeft != 0 ){
		env->SetIntField ( obj, regionCodeVendorResetLeft, driveInfo.nRegionCodeVendorResetsLeft );
	}
	////
	jfieldID iDETransfermode = env->GetFieldID ( clazz, "iDETransfermode", "I" );
	if ( iDETransfermode != 0 ){
		env->SetIntField ( obj, iDETransfermode, driveInfo.nIdeTransferMode );
	}


	return obj;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_writeTrackToFile
  ( JNIEnv *env, jobject jobj, jstring ltargetPath, jint nTrack, jint nFormat )
{

	const TCHAR *targetFile = env->GetStringUTFChars(ltargetPath, JNI_FALSE);

	int32 res = ::SaveTrackToFile(BS_READ_DEVICE, (int)nTrack, targetFile, (int)nFormat);

 	if(nDebug==true) std::cout << "SaveTrackToFile: " << res << std::endl;
	env->ReleaseStringUTFChars(ltargetPath, targetFile);



	return 1;
}

/*
 * FilePath is the path to the file on the disc not the original file path on HDD
 * This means, you can call this only after adding a file to the project.
 */
JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setFileAttributes
  ( JNIEnv *env, jobject jobj, jstring lfilePath, jobject jstruct )
{
	jclass clazz = env->GetObjectClass(jstruct);
	if(clazz == 0){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	const TCHAR *targetFile = env->GetStringUTFChars(lfilePath, JNI_FALSE);

	int fileAttributes;

	jfieldID faArchive = env->GetFieldID(clazz,"faArchive","Z");
	if(faArchive != 0){
		fileAttributes |= BS_FA_ARCHIVE;
	}
	jfieldID faHidden = env->GetFieldID(clazz,"faHidden","Z");
	if(faHidden != 0){
		fileAttributes |= BS_FA_HIDDEN;
	}
	jfieldID faAdvhidden = env->GetFieldID(clazz,"faAdvhidden","Z");
	if(faAdvhidden != 0){
		fileAttributes |= BS_FA_ADVANCED_HIDDEN;
	}
	jfieldID faReadonly = env->GetFieldID(clazz,"faReadonly","Z");
	if(faReadonly != 0){
		fileAttributes |= BS_FA_READONLY;
	}
	jfieldID faSystem = env->GetFieldID(clazz,"faSystem","Z");
	if(faSystem != 0){
		fileAttributes |= BS_FA_SYSTEM ;
	}
	jfieldID faDirectory = env->GetFieldID(clazz,"faDirectory","Z");
	if(faDirectory != 0){
		fileAttributes |= BS_FA_DIRECTORY ;
	}

	int32 res = ::SetFileAttr(targetFile, fileAttributes);

	env->ReleaseStringUTFChars(lfilePath, targetFile);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_clearAll
  ( JNIEnv *env, jobject jobj ){

	int32 res = ::ClearAll();
	return (int)res;
}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getTrackISRC
  ( JNIEnv *env, jobject jobj, jint nTrack )
{

	std::string iSRCNumber = "";

	TCHAR strISRC[13];
	int32 res = ::GetTrackISRC(BS_READ_DEVICE, (int)nTrack, strISRC);
	if(res==0){
		iSRCNumber.append(strISRC);
	}else{
		example->lastError = res;
	}

	return env->NewStringUTF(iSRCNumber.c_str());

}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getImageFilePath
  ( JNIEnv *env, jobject jobj )
{
	std::string imagePath = "";

	TCHAR chPath[2048];
	int32 nLength = 2048;

	int32 res = ::GetImageFilePath(chPath, &nLength);
	if(res==0){
		imagePath.append(chPath);
	}else{
		example->lastError = res;
	}

	return env->NewStringUTF(imagePath.c_str());
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setRegionCode
  ( JNIEnv *env, jobject jobj, jint nrgCode )
{
	int32 res = ::SetRegionalCode(BS_CURRENT_DEVICE, (int)nrgCode);
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_isValidVideoTsFolder
  ( JNIEnv *env, jobject jobj, jstring lDVDPath )
{
	const TCHAR *dvdFolder = env->GetStringUTFChars(lDVDPath, JNI_FALSE);

	int32 res = ::IsValidVideoTsFolder(dvdFolder);

	env->ReleaseStringUTFChars(lDVDPath, dvdFolder);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_createDeviceCapabilitiesHandle
  ( JNIEnv *env, jobject jobj)
{
	int32 res = ::GetDeviceCapabilitiesHandle(BS_CURRENT_DEVICE, &nCapsHandle);
	if(nDebug==true) std::cout << "Device :" << res << std::endl;
	if(nDebug==true) std::cout << "Handle :" << nCapsHandle << std::endl;
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_releaseDeviceCapabilitiesHandle
  ( JNIEnv *env, jobject jobj)
{
	int32 res = ::ReleaseDeviceCapabilities(nCapsHandle);
	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_analyzeDeviceCapabilitie
  ( JNIEnv *env, jobject jobj, jlong lCapability )
{
	BS_BOOL bRes = false;
	int32 res = AnalyseDeviceCapability(nCapsHandle, (long long int)lCapability, &bRes);
	example->lastError = res;

	return (int)bRes;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_createImage
  ( JNIEnv *env, jobject jobj, jobject jstruct, jint nType)
{

	jclass clazz = env->GetObjectClass ( jstruct );
	if( clazz == 0 ){
		if(nDebug==true) std::cout << "GetObjectClass failed " << std::endl;
		return 0;
	}

	SCreateImageParams cCreateImageParams;

	////
	jfieldID impagePath = env->GetFieldID ( clazz, "impagePath", "Ljava/lang/String;" );
	if( impagePath != 0 ){
		jstring strImpagePath = (jstring) env->GetObjectField ( jstruct, impagePath );
		if( strImpagePath != NULL ){
			const TCHAR *tImpagePath = env->GetStringUTFChars ( strImpagePath, JNI_FALSE );
			_tcscpy( cCreateImageParams.lpszImagePath, tImpagePath );
			env->ReleaseStringUTFChars ( strImpagePath, tImpagePath );
		}
	}
	////
	jfieldID badSectorsFilePath = env->GetFieldID ( clazz, "badSectorsFilePath", "Ljava/lang/String;" );
	if( badSectorsFilePath != 0 ){
		jstring strbBadSectorsFilePath = (jstring) env->GetObjectField ( jstruct, badSectorsFilePath );
		if( strbBadSectorsFilePath != NULL ){
			const TCHAR *tbBadSectorsFilePath = env->GetStringUTFChars ( strbBadSectorsFilePath, JNI_FALSE );
			_tcscpy( cCreateImageParams.lpszBadSectorsFilePath, tbBadSectorsFilePath );
			env->ReleaseStringUTFChars ( strbBadSectorsFilePath, tbBadSectorsFilePath );
		}
	}
	////
	jfieldID fullCapacity = env->GetFieldID ( clazz, "fullCapacity", "Z" );
	if( fullCapacity != 0 ){
		bool bFullCapacity = env->GetBooleanField ( jstruct, fullCapacity);
		cCreateImageParams.bFullCapacity = bFullCapacity == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID errorCorrection = env->GetFieldID ( clazz, "errorCorrection", "Z" );
	if( errorCorrection != 0 ){
		bool bErrorCorrection = env->GetBooleanField ( jstruct, errorCorrection);
		cCreateImageParams.cErrorParams.bErrorCorrection = bErrorCorrection == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID blankBadSectors = env->GetFieldID ( clazz, "blankBadSectors", "Z" );
	if( blankBadSectors != 0 ){
		bool bBlankBadSectors = env->GetBooleanField ( jstruct, blankBadSectors );
		cCreateImageParams.cErrorParams.bBlankBadSectors = bBlankBadSectors == 0 ? BS_FALSE : BS_TRUE;
	}
	////
	jfieldID verifyBufferSectors = env->GetFieldID ( clazz, "verifyBufferSectors", "I" );
	if( verifyBufferSectors != 0 ){
		int nVerifyBufferSectors = env->GetIntField ( jstruct, verifyBufferSectors );
		if( nVerifyBufferSectors != -1 )
			cCreateImageParams.nVerifyBufferSectors = nVerifyBufferSectors;
	}
	////
	jfieldID hardwareRetryCounts = env->GetFieldID ( clazz, "hardwareRetryCounts", "I" );
	if( hardwareRetryCounts != 0 ){
		int nHardwareRetryCounts = env->GetIntField ( jstruct, hardwareRetryCounts );
		if( nHardwareRetryCounts != -1 )
			cCreateImageParams.cErrorParams.nHardwareRetryCount = nHardwareRetryCounts;
	}
	////
	jfieldID softwareRetryCounts = env->GetFieldID ( clazz, "softwareRetryCounts", "I" );
	if( softwareRetryCounts != 0 ){
		int nSoftwareRetryCounts = env->GetIntField ( jstruct, softwareRetryCounts );
		if( nSoftwareRetryCounts != -1 )
			cCreateImageParams.cErrorParams.nSoftwareRetryCount = nSoftwareRetryCounts;
	}
	////
	jfieldID imageType = env->GetFieldID ( clazz, "imageType", "S" );
	if( imageType != 0 ){
		int nImageType = env->GetIntField ( jstruct, imageType );
		if( nImageType != -1 )
			cCreateImageParams.nImageType = nImageType == 2 ? BS_IMG_BIN : BS_IMG_ISO;
	}

	int8 dwOperation = 0;

	switch((int)nType){
		case 1:
			dwOperation = BS_IMGTASK_CREATE;
			break;
		case 2:
			dwOperation = BS_IMGTASK_VERIFY;
			break;
		case 3:
			dwOperation = BS_IMGTASK_CREATE | BS_IMGTASK_VERIFY;
			break;
	}

	int32 res = ::CreateImage(cCreateImageParams, dwOperation);

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_checkFormat
  ( JNIEnv *env, jobject jobj, jint nFormat ){

	int16 nImageFormats;
	int32 nRes = ::GetPossibleImageFormats(&nImageFormats);

	if((int)nFormat == 1){
		if (nImageFormats & BS_IMG_ISO)
			{
				return 1;
			}
	}
	if((int)nFormat == 2){
		if (nImageFormats & BS_IMG_BIN)
		{
			return 1;
		}
	}

	return 0;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_createCDTextReader
  ( JNIEnv *env, jobject jobj )
{
	int32 res = ::ReadCDText(BS_READ_DEVICE, &hCdText);
	if(nDebug==true) std::cout << "ReadCDText :" << res << std::endl;
	if(nDebug==true) std::cout << "Handle :" << hCdText << std::endl;

	return (int)res;
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_releaseCDTextReader
  ( JNIEnv *env, jobject jobj )
{
	int32 res = ::CloseCDTextHandle(hCdText);
	return (int)res;
}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getCDTextTrackString
  ( JNIEnv *env, jobject jobj, jint nTrack, jint nCDTid )
{
	std::string cdText = "";

	int32 nLen = 0;
	int32 res = ::GetCDTextTrackTagString(hCdText, (int)nTrack, (int)nCDTid, 0, &nLen);
	if(res != BS_SDK_ERROR_NO)
	{
		example->lastError = res;
		return env->NewStringUTF(cdText.c_str());
	}

	if(!nLen || nLen == 1)
	{
		example->lastError = 0;
		return env->NewStringUTF(cdText.c_str());
	}

	TCHAR *pBuf = new TCHAR[nLen];
	res = ::GetCDTextTrackTagString(hCdText, (int)nTrack, (int)nCDTid, pBuf, &nLen);
	if(res != BS_SDK_ERROR_NO)
	{
		delete pBuf;
		example->lastError = res;
		return env->NewStringUTF(cdText.c_str());
	}

	pBuf[nLen-1] = _T('\0');
	cdText.append(pBuf);
	delete pBuf;

	return env->NewStringUTF(cdText.c_str());

	/*
	TCHAR chText[2048];
	int32 nLength = 2048;

	int32 res = ::GetCDTextTrackTagString(hCdText, (int)nTrack, (int)nCDTid, chText, &nLength);
	if(res==0){
		cdText.append(chText);
	}else{
		example->lastError = res;
	}

	return env->NewStringUTF(cdText.c_str());
	*/
}

JNIEXPORT jstring JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_getCDTextDiscString
  ( JNIEnv *env, jobject jobj, jint nCDTid )
{
	std::string cdText = "";

	int32 nLen = 0;
	int32 res = ::GetCDTextDiskTagString(hCdText, (int)nCDTid, 0, &nLen);
	if(res != BS_SDK_ERROR_NO)
	{
		example->lastError = res;
		return env->NewStringUTF(cdText.c_str());
	}

	if(!nLen || nLen == 1)
	{
		example->lastError = 0;
		return env->NewStringUTF(cdText.c_str());
	}

	TCHAR *pBuf = new TCHAR[nLen];
	res = ::GetCDTextDiskTagString(hCdText, (int)nCDTid, pBuf, &nLen);
	if(res != BS_SDK_ERROR_NO)
	{
		delete pBuf;
		example->lastError = res;
		return env->NewStringUTF(cdText.c_str());
	}

	pBuf[nLen-1] = _T('\0');
	cdText.append(pBuf);
	delete pBuf;

	return env->NewStringUTF(cdText.c_str());

	/*

	std::string cdText = "";

	TCHAR chText[2048];
	int32 nLength = 2048;

	int32 res = ::GetCDTextDiskTagString(hCdText, (int)nCDTid, chText, &nLength);
	if(res==0){
		cdText.append(chText);
	}else{
		example->lastError = res;
	}

	return env->NewStringUTF(cdText.c_str());
	*/
}

JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_playAudioTrack
  ( JNIEnv *env, jobject jobj, jint nTrack )
{
	int32 res = ::PlayAudioTrack((int)nTrack);
	return (int)res;
}

/*
 * Set a custom time information to the file. You will need the
 * destination path on the disc and not the original file path.
 */
JNIEXPORT jint JNICALL Java_IsoSDKJNIPkg_IsoSDKJNI_setFileTimes
  ( JNIEnv *env, jobject jobj, jstring lFilePath, jstring tCreation, jstring tModification, jstring tAccess)
{

	const TCHAR *tFilePath = env->GetStringUTFChars (lFilePath, JNI_FALSE );

	const TCHAR *tCreationTime = env->GetStringUTFChars (tCreation, JNI_FALSE );
	struct tm tmCreationTime;
	SFileDateTime creationTime;

	if (strptime(tCreationTime, "%Y/%m/%d %H:%M:%S", &tmCreationTime) != NULL){
		creationTime.nYear = tmCreationTime.tm_year;
		creationTime.nMonth = tmCreationTime.tm_mon;
		creationTime.nDay = tmCreationTime.tm_mday;
		creationTime.nHour = tmCreationTime.tm_hour;
		creationTime.nMinute = tmCreationTime.tm_min;
		creationTime.nSecond = tmCreationTime.tm_sec;
	}

	env->ReleaseStringUTFChars ( tCreation, tCreationTime );

	const TCHAR *tModificationTime = env->GetStringUTFChars (tModification, JNI_FALSE );
	struct tm tmModificationTime;
	SFileDateTime modificationTime;

	if (strptime(tModificationTime, "%Y/%m/%d %H:%M:%S", &tmModificationTime) != NULL){
		modificationTime.nYear = tmModificationTime.tm_year;
		modificationTime.nMonth = tmModificationTime.tm_mon;
		modificationTime.nDay = tmModificationTime.tm_mday;
		modificationTime.nHour = tmModificationTime.tm_hour;
		modificationTime.nMinute = tmModificationTime.tm_min;
		modificationTime.nSecond = tmModificationTime.tm_sec;
	}

	env->ReleaseStringUTFChars ( tModification, tModificationTime );

	const TCHAR *tAccessTime = env->GetStringUTFChars (tAccess, JNI_FALSE );
	struct tm tmAccessTime;
	SFileDateTime accessTime;

	if (strptime(tAccessTime, "%Y/%m/%d %H:%M:%S", &tmAccessTime) != NULL){
		accessTime.nYear = tmAccessTime.tm_year;
		accessTime.nMonth = tmAccessTime.tm_mon;
		accessTime.nDay = tmAccessTime.tm_mday;
		accessTime.nHour = tmAccessTime.tm_hour;
		accessTime.nMinute = tmAccessTime.tm_min;
		accessTime.nSecond = tmAccessTime.tm_sec;
	}

	env->ReleaseStringUTFChars ( tAccess, tAccessTime );

	int32 res = ::SetFileTimes(tFilePath, &creationTime, &modificationTime, &accessTime);

	env->ReleaseStringUTFChars ( lFilePath, tFilePath );

	return (int)res;
}
