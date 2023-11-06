/*
 *  IsoSDK - a powerful CD/DVD/BD recording SDK for Linux, macOS, Windows and Android.
 *  Copyright (c) 2002-2021 Ingo Foerster (pixbytesl@gmail.com).
 *  http://www.isosdk.com
 */

#ifndef __ISOSDK_EXPORT_H__
#	define __ISOSDK_EXPORT_H__

#	include "IsoSDKDefinitions.h"

#	ifdef __cplusplus
extern "C" {
#	endif

#ifdef _MSC_VER
#	define 						BS_CALL		__stdcall
#elif defined MAC || defined LINUX
#	define 						BS_CALL		__attribute__((visibility("default")))
#else
#	define 						BS_CALL
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Initialization / Deinitialization. Things do do first when working with the IsoSDK //
////////////////////////////////////////////////////////////////////////////////////////
int32 							BS_CALL	CheckLicenseKey								(const TCHAR chLicenseKey[35]);	
#	ifdef __cplusplus
int32 							BS_CALL	Initialize									(const TCHAR chLicenseKey[35], int32 nAspiInterface = BS_ASPI_INTERNAL, BS_BOOL bEnableImageDevice = BS_FALSE);
#	else
int32 							BS_CALL	Initialize									(const TCHAR chLicenseKey[35], int32 nAspiInterface, BS_BOOL bEnableImageDevice);
#	endif												
int32 							BS_CALL	DeInitialize								(void);
#	ifdef __cplusplus
int32 							BS_CALL SetASPI										(int32 nAspiInterface = BS_ASPI_INTERNAL);
#	else
int32 							BS_CALL SetASPI										(int32 nAspiInterface);
#	endif
int32 							BS_CALL GetASPI										(int32* pAspiInterface);
int32 							BS_CALL EnableImageDevice							(BS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////////////
// End Initialization / Deinitialization.											  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Callbacks / Events to get info from the IsoSDK 									  //
////////////////////////////////////////////////////////////////////////////////////////
int32							BS_CALL	SetGetTextEventCallback						(GetTextEvent GetTextEventCallback, void *pUserData);
int32							BS_CALL	SetInfoTextEventCallback					(InfoTextEvent InfoTextCallback, int32 nLevel, void *pUserData);
InfoTextEvent					BS_CALL GetInfoTextEventCallback					(void **pUserData);
int32							BS_CALL	SetProcessEventCallback						(ProcessEvent ProcessCallback, void *pUserData);
ProcessEvent					BS_CALL	GetProcessEventCallback						(void **pUserData);
int32							BS_CALL SetBurnFileEventCallback					(BurnFileEvent BurnFileCallback, void *pUserData);
BurnFileEvent					BS_CALL GetBurnFileEventCallback					(void **pUserData);
int32							BS_CALL	SetEraseDoneEventCallback					(EraseDoneEvent EraseDoneEventCallback, void *pUserData);
EraseDoneEvent					BS_CALL	GetEraseDoneEventCallback					(void **pUserData);
int32							BS_CALL	SetFinalizeEventCallback					(FinalizeEvent FinalizeEventCallback, void *pUserData);
FinalizeEvent					BS_CALL GetFinalizeEventCallback					(void **pUserData);
int32							BS_CALL	SetBurnDoneEventCallback					(BurnDoneEvent WriteDoneEventCallback, void *pUserData);
BurnDoneEvent					BS_CALL GetBurnDoneEventCallback					(void **pUserData);
int32							BS_CALL SetJobDoneEventCallback						(JobDoneEvent JobDoneEventCallback, void *pUserData);
JobDoneEvent					BS_CALL GetJobDoneEventCallback						(void **pUserData);
int32							BS_CALL	SetAddFileEventCallback						(AddFileEvent AddFileEventCallback, void *pUserData);
int32							BS_CALL SetCreateDirEventCallback					(CreateDirEvent CreateDirEventCallback, void *pUserData);
int32							BS_CALL	SetRemoveFileEventCallback					(RemoveFileEvent RemoveFileEventCallback, void *pUserData);
int32							BS_CALL	SetAudioDecoderEventCallback				(AudioDecoderEvent AudioDecoderEventCallback, void *pUserData);
int32							BS_CALL	SetAudioDecodeDoneEventCallback				(AudioDecodeDoneEvent AudioDecodeDoneCallback, void *pUserData);
int32							BS_CALL	SetVideoScannerEventCallback				(VideoScannerEvent VideoScannerCallback, void *pUserData);
int32							BS_CALL	SetVideoScanDoneEventCallback				(VideoScanDoneEvent VideoScanDoneCallback, void *pUserData);
StartVerifyEvent				BS_CALL GetStartVerifyEventCallback					(void **pUserData);
int32							BS_CALL SetStartVerifyEventCallback					(StartVerifyEvent StartVerifyEventCallback, void *pUserData);
VerifyFileEvent					BS_CALL GetVerifyFileEventCallback					(void **pUserData);
int32							BS_CALL SetVerifyFileEventCallback					(VerifyFileEvent VerifyFileEventCallback, void *pUserData);
VerifySectorEvent				BS_CALL GetVerifySectorEventCallback				(void **pUserData);
int32							BS_CALL SetVerifySectorEventCallback				(VerifySectorEvent VerifySectorEventCallback, void *pUserData);
VerifyErrorEvent				BS_CALL GetVerifyErrorEventCallback					(void **pUserData);
int32							BS_CALL SetVerifyErrorEventCallback					(VerifyErrorEvent VerifyErrorEventCallback, void *pUserData);
VerifyDoneEvent					BS_CALL GetVerifyDoneEventCallback					(void **pUserData);
int32							BS_CALL SetVerifyDoneEventCallback					(VerifyDoneEvent VerifyDoneEventCallback, void *pUserData);
int32							BS_CALL SetRAWDataEventCallback						(RAWDataEvent RAWDataEventCallback, void* pUserData);
RAWDataEvent					BS_CALL GetRAWDataEventCallback						(void** pUserData);
int32							BS_CALL SetCompareFilesForArrangementEventCallback	(CompareFilesForArrangementEvent callback, void* pUserData);
CompareFilesForArrangementEvent	BS_CALL GetCompareFilesForArrangementEventCallback	(void** pUserData);
int32							BS_CALL	ResetCallbacks								(void);
////////////////////////////////////////////////////////////////////////////////////////
// End Callbacks / Events															  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// General IsoSDK settings						 									  //
////////////////////////////////////////////////////////////////////////////////////////
int32 							BS_CALL	SetTmpPath									(const TCHAR *pchPath);
int32 							BS_CALL	GetTmpPath									(TCHAR chPath[_MAX_PATH]);
#	ifdef __cplusplus
int32 							BS_CALL	SetLanguage									(const TCHAR *pchLanguage, const TCHAR *pchLanguageFile = BS_DEFAULT_LANGUAGE_FILE);
#	else
int32 							BS_CALL	SetLanguage									(const TCHAR *pchLanguage, const TCHAR *pchLanguageFile);
#	endif
int32 							BS_CALL	GetLanguage									(TCHAR chLanguage[100], TCHAR chLanguageFile[_MAX_PATH]);
int32 							BS_CALL	GetText										(int32 nTextID, TCHAR *pchText, int32 *pnLength);
////////////////////////////////////////////////////////////////////////////////////////
// End general IsoSDK settings						 								  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Functions to deal with the device or medium						 				  //
////////////////////////////////////////////////////////////////////////////////////////
#	ifdef __cplusplus
int32 							BS_CALL	GetDevices									(TCHAR chListDevices[26][50], int32 *pnUsed, BS_BOOL bBurningDevicesOnly = BS_FALSE);
#	else
int32 							BS_CALL	GetDevices									(TCHAR chListDevices[26][50], int32 *pnUsed, BS_BOOL bBurningDevicesOnly);
#	endif																		
int32 							BS_CALL	SetBurnDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	AddBurnDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	RemoveBurnDevice							(const TCHAR* lpszDevice);
int32 							BS_CALL SetReadDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	GetErrorDeviceName							(TCHAR* pDeviceName, int32 nLength);
int32 							BS_CALL	RescanDevices								(void);
int32 							BS_CALL	GetBurnDevice								(TCHAR* lpszDevice, int32* pnLength);					
int32 							BS_CALL GetBurnDevices								(TCHAR chListDevices[26][50], int32 *pnUsed);
int32 							BS_CALL	GetReadDevice								(TCHAR* lpszDevice, int32* pnLength);
int32 							BS_CALL	DAGetDeviceInformation						(const TCHAR* lpszDevice, TCHAR chVendorID[9], TCHAR chProductID[17], TCHAR chProductRevision[5]);
int32 							BS_CALL	GetDeviceInformation						(int32 index, TCHAR chVendorID[9], TCHAR chProductID[17], TCHAR chProductRevision[5]);
int32 							BS_CALL	DAGetDeviceInformationEx					(const TCHAR* lpszDevice, SExtendedDeviceInformation* pExtendedInformation);
int32 							BS_CALL	GetDeviceInformationEx						(int32 index, SExtendedDeviceInformation* pExtendedInformation);
int32 							BS_CALL	GetActiveDevicesCount						(int32 *pnCount);
int32 							BS_CALL	DAGetDeviceCapabilities						(const TCHAR* lpszDevice, int64* pnDeviceCapabilities);
int32 							BS_CALL	GetDeviceCapabilities						(int32 index, int64 *pnDeviceCapabilities);	
int32							BS_CALL DAGetDeviceCapabilitiesHandle				(const TCHAR* lpszDevice, int32* pnNewCapabilitiesHandle);
int32 							BS_CALL	GetDeviceCapabilitiesHandle					(int32 index, int32 * pnNewCapabilitiesHandle);
int32 							BS_CALL	ReleaseDeviceCapabilities					(int32 CapabilitiesHandle);
int32 							BS_CALL	AnalyseDeviceCapability						(int32 CapabilitiesHandle, int64 nCapabilityName, BS_BOOL * pbResult);
int32							BS_CALL	DAGetMaxReadSpeed							(const TCHAR* lpszDevice, int32* pnSpeed);
int32 							BS_CALL	GetMaxReadSpeed								(int32 index, int32 *pnSpeed);									
#	ifdef __cplusplus
int32 							BS_CALL	DASetReadSpeed								(const TCHAR* lpszDevice, int32 nSpeed = BS_MAX_SPEED);
int32 							BS_CALL	SetReadSpeed								(int32 index, int32 nSpeed = BS_MAX_SPEED);
#	else
int32 							BS_CALL	DASetReadSpeed								(const TCHAR* lpszDevice, int32 nSpeed);
int32 							BS_CALL	SetReadSpeed								(int32 index, int32 nSpeed);
#	endif
int32 							BS_CALL	DAGetReadSpeed								(const TCHAR* lpszDevice, int32* pnSpeed);
int32 							BS_CALL	GetReadSpeed								(int32 index, int32 *pnSpeed);		
int32 							BS_CALL	DAGetMaxBurnSpeed							(const TCHAR* lpszDevice, int32* pnSpeed);
int32 							BS_CALL	GetMaxBurnSpeed								(int32 index, int32 *pnSpeed);	
int32 							BS_CALL	DAConvertSpeedFromKBPerSec					(const TCHAR* lpszDevice, int32 nSpeedInKBPerSec, float* pfConvertedSpeed);
int32 							BS_CALL	ConvertSpeedFromKBPerSec    				(int32 nSpeedInKBPerSec, float *pfConvertedSpeed);   
#	ifdef __cplusplus
int32 							BS_CALL	DASetBurnSpeed								(const TCHAR* lpszDevice, int32 nSpeed = BS_MAX_SPEED);
int32 							BS_CALL	SetBurnSpeed								(int32 index, int32 nSpeed = BS_MAX_SPEED);
#	else
int32 							BS_CALL	DASetBurnSpeed								(const TCHAR* lpszDevice, int32 nSpeed);
int32 							BS_CALL	SetBurnSpeed								(int32 index, int32 nSpeed);
#	endif
int32 							BS_CALL	DAGetPossibleBurnSpeeds						(const TCHAR* lpszDevice, struct SSpeed* pSpeeds, int32* pnSize);
int32 							BS_CALL	GetPossibleBurnSpeeds       				(int32 index, struct SSpeed *pSpeeds, int32 *pnSize);
int32 							BS_CALL	DAGetPossibleReadSpeeds						(const TCHAR* lpszDevice, struct SSpeed* pSpeeds, int32* pnSize);
int32 							BS_CALL	GetPossibleReadSpeeds       				(int32 index, struct SSpeed *pSpeeds, int32 *pnSize);
int32 							BS_CALL	DAGetBurnSpeed								(const TCHAR* lpszDevice, int32* pnSpeed);
int32 							BS_CALL	GetBurnSpeed								(int32 index, int32 *pnSpeed);
#	ifdef __cplusplus
int32 							BS_CALL	DAEjectDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	EjectDevice									(int32 index = BS_CURRENT_DEVICE);
#else
int32 							BS_CALL	DAEjectDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	EjectDevice									(int32 index);
#endif
#	ifdef __cplusplus
int32							BS_CALL	DALockMedium								(const TCHAR* lpszDevice, BS_BOOL bLock = true);
int32							BS_CALL	LockMedium									(int32 index = BS_CURRENT_DEVICE, BS_BOOL bLock = true);
#else
int32 							BS_CALL	DALockMedium								(const TCHAR* lpszDevice, BS_BOOL bLock);
int32 							BS_CALL	LockMedium									(int32 index, BS_BOOL bLock);
#endif
#	ifdef __cplusplus
int32 							BS_CALL	DACloseDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	CloseDevice									(int32 index = BS_CURRENT_DEVICE);
#else
int32 							BS_CALL	DACloseDevice								(const TCHAR* lpszDevice);
int32 							BS_CALL	CloseDevice									(int32 index);
#endif
int32 							BS_CALL	DAIsDeviceReady							(const TCHAR* lpszDevice, BS_LP_BOOL pbReady);
int32 							BS_CALL	IsDeviceReady								(int32 index, BS_LP_BOOL pbReady);
#	ifdef __cplusplus
int32 							BS_CALL	DAErase									(const TCHAR* lpszDevice, BS_BOOL bFast /*= BS_TRUE*/, BS_BOOL bEjectAfterErase /*= BS_TRUE*/);
int32 							BS_CALL	Erase										(BS_BOOL bFast /*= BS_TRUE*/, BS_BOOL bEjectAfterErase /*= BS_TRUE*/);
#	else
int32 							BS_CALL	DAErase									(const TCHAR* lpszDevice, BS_BOOL bFast, BS_BOOL bEjectAfterErase);
int32 							BS_CALL	Erase										(BS_BOOL bFast, BS_BOOL bEjectAfterErase);
#	endif
int32 							BS_CALL	DACopyDisk									(const TCHAR* lpszDevice, SDiskCopyOptions cDiskCopyOptions);
int32 							BS_CALL	CopyDisk									(SDiskCopyOptions cDiskCopyOptions);
int32 							BS_CALL	DACreateImage								(const TCHAR* lpszDevice, SCreateImageParams cCreateImageParams, int8 nTaskType);
int32 							BS_CALL	CreateImage									(SCreateImageParams cCreateImageParams, int8 nTaskType);
int32 							BS_CALL	DAGrabAudioTrack							(const TCHAR* lpszDevice, SAudioGrabbingParams cAudioGrabbingParams, int16 nTrackNumber, const TCHAR* strSavePath);
int32 							BS_CALL	GrabAudioTrack								(SAudioGrabbingParams cAudioGrabbingParams, int16 nTrackNumber, const TCHAR *strSavePath);
int32 							BS_CALL	DAReadSectors								(const TCHAR* lpszDevice, int32 nLBA, int32 nCount, int8 nFormat, void* pBuff, int32 nBuffLength);
int32 							BS_CALL	ReadSectors									(int32 index, int32 nLBA, int32 nCount, int8 nFormat, void* pBuff, int32 nBuffLength);
int32 							BS_CALL	DASaveTrackToFile							(const TCHAR* lpszDevice, int16 nTrackNumber, const TCHAR* pchFileName, int32 nFileFormat);
int32 							BS_CALL	SaveTrackToFile								(int32 index, int16 nTrackNumber, const TCHAR* pchFileName, int32 nFileFormat);
int32 							BS_CALL	DAGetPossibleImageFormats					(const TCHAR* lpszDevice, int16* pImageFormats);
int32 							BS_CALL	GetPossibleImageFormats						(int16 *pImageFormats);
int32							BS_CALL DACheckSignature							(const TCHAR* lpszDevice);
int32							BS_CALL CheckSignature								();
int32 							BS_CALL	DAImportFile								(const TCHAR* lpszDevice, HSESSION  hSession, const TCHAR* lpszSourcePath, const TCHAR* lpszDestFolderPath);
int32 							BS_CALL	ImportFile									(HSESSION  hSession, const TCHAR* lpszSourcePath, const TCHAR* lpszDestFolderPath);
int32 							BS_CALL	DAImportFileEx								(const TCHAR* lpszDevice, HSESSION  hSession, const TCHAR* lpszSourcePath, const TCHAR* lpszDestFolderPath, const TCHAR* pchPassword);
int32 							BS_CALL	ImportFileEx								(HSESSION  hSession, const TCHAR* lpszSourcePath, const TCHAR *lpszDestFolderPath, const TCHAR* pchPassword);
int32 							BS_CALL	DAVerifyFile								(const TCHAR* lpszDevice, HSESSION  hSession, const TCHAR* lpszSourcePath);
int32 							BS_CALL	VerifyFile									(HSESSION  hSession, const TCHAR* lpszSourcePath);
int32 							BS_CALL	DAGetMediumInformation						(const TCHAR* lpszDevice, struct SMediumInfo* pMediumInfo);
int32 							BS_CALL	GetMediumInformation						(int32 index, struct SMediumInfo *pMediumInfo);
int32 							BS_CALL	DAGetMediumFreedbId							(const TCHAR* lpszDevice, TCHAR id[9]);
int32 							BS_CALL	GetMediumFreedbId							(int32 index, TCHAR id[9]);
int32 							BS_CALL	DAGetSessionInformation						(const TCHAR* lpszDevice, int32 nSession, struct SSessionInfo* pSessionInfo);
int32 							BS_CALL	GetSessionInformation						(int32 index, int32 nSession, struct SSessionInfo *pSessionInfo); 
int32 							BS_CALL	DAGetTrackIndexes							(const TCHAR* lpszDevice, int32 nTrack, int32* pArrIndexes, int32* pnLength);
int32 							BS_CALL	GetTrackIndexes								(int32 index, int32 nTrack, int32 * pArrIndexes, int32 * pnLength);
int32 							BS_CALL	DAGetTrackISRC								(const TCHAR* lpszDevice, int32 nTrack, TCHAR pStrISRC[12]);
int32 							BS_CALL	GetTrackISRC								(int32 index, int32 nTrack, TCHAR pStrISRC[12]);
int32 							BS_CALL DAGetTrackInformation						(const TCHAR* lpszDevice, int32 nTrack, struct STrackInfo* pTrackInfo);
int32 							BS_CALL GetTrackInformation         				(int32 index, int32 nTrack, struct STrackInfo *pTrackInfo);
int32 							BS_CALL DAGetTrackFormatEx							(const TCHAR* lpszDevice, int32 nTrack, int8* pFormat);
int32 							BS_CALL GetTrackFormatEx							(int32 index, int32 nTrack, int8 *pFormat);
int32							BS_CALL DASetRegionalCode							(const TCHAR* lpszDevice, int32 nRPC);
int32 							BS_CALL SetRegionalCode								(int32 index, int32 nRPC);
int32 							BS_CALL	SetWriteCDTextInUnicode						(BS_BOOL bWriteInUnicode = BS_FALSE);
int32 							BS_CALL	GetWriteCDTextInUnicode						(BS_BOOL* pbWriteInUnicode);
int32 							BS_CALL DAReadCDText								(const TCHAR* lpszDevice, int32* pHandle);
int32 							BS_CALL ReadCDText									(int32 index, int32 *pHandle);
int32 							BS_CALL GetCDTextDiskTagString						(int32 hOpenedHandle, int32 nCDTCI, TCHAR* pchText, int32 *pnLength);
int32 							BS_CALL GetCDTextTrackTagString						(int32 hOpenedHandle, int32 nTrackNumber, int32 nCDTCI, TCHAR* pchText, int32 *pnLength);
int32 							BS_CALL CloseCDTextHandle							(int32 hOpenedHandle);
int32 							BS_CALL GetNetworkDiskTagString						(int32 hOpenedHandle, int32 nTagsContentId, TCHAR* pchText, int32 *pnLength);
int32 							BS_CALL GetNetworkDiskTagInt						(int32 hOpenedHandle, int32 nTagsContentId, int32* pNum);
int32 							BS_CALL GetNetworkTrackTagString					(int32 hOpenedHandle, int32 nTrackNumber, int32 nTagsContentId, TCHAR* pchText, int32 *pnLength);
int32 							BS_CALL GetNetworkTrackTagInt						(int32 hOpenedHandle, int32 nTrackNumber, int32 nTagsContentId, int32* pNum);
int32 							BS_CALL CloseNetworkTagsHandle						(int32 hOpenedHandle);
#	ifdef __cplusplus
int32 							BS_CALL	DACloseSession								(const TCHAR* lpszDevice);
int32 							BS_CALL	CloseSession								(int32 index = BS_CURRENT_DEVICE);
#	else
int32 							BS_CALL	DACloseSession								(const TCHAR* lpszDevice);
int32 							BS_CALL	CloseSession								(int32 index);
#	endif

#	ifdef __cplusplus
int32 							BS_CALL EnableMCNDisabling							(BS_BOOL bEnable = BS_TRUE);
#	else	
int32 							BS_CALL EnableMCNDisabling							(BS_BOOL bEnable);
#	endif
int32 							BS_CALL SetImageFilePath							(const TCHAR* pchPath);
int32 							BS_CALL GetImageFilePath							(TCHAR* pchPath, int32* pnLength);
////////////////////////////////////////////////////////////////////////////////////////
// End functions to deal with the device or medium						 				  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Functions to deal with the available project types				 				  //
////////////////////////////////////////////////////////////////////////////////////////
#	ifdef __cplusplus
int32 							BS_CALL	CreateProject								(int32 nType, int32 nSessionToContinue = BS_CONTINUE_LAST_SESSION);
#	else
int32 							BS_CALL	CreateProject								(int32 nType, int32 nSessionToContinue);
#	endif
int32 							BS_CALL	DeleteProject								(void);
int32 							BS_CALL	GetProjectType								(int32 *pnType);					// valid pointer
////////////////////////////////////////////////////////////////////////////////////////
// End functions to deal with the available project types				 			  //
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// Functions to deal with files and folders								 			  //
// Each of the following functions is only available for the current project. 		  //
////////////////////////////////////////////////////////////////////////////////////////
int32 							BS_CALL DirExists									(const TCHAR *strDirectoryName);
int32 							BS_CALL	CreateDir									(struct SDirToCreate DirToCreate);
int32 							BS_CALL	AddDir										(struct SDirToAdd DirToAdd);
int32 							BS_CALL	RemoveDir									(struct SDirToRemove DirToRemove);
int32 							BS_CALL	AddFile										(struct SFileToAdd FileToAdd);
int32 							BS_CALL	AddFileEx									(struct SFileToAddEx FileToAdd);
int32 							BS_CALL	SetAudioFileProperty						(struct SFileAudioProperty FileToAdd);
int32 							BS_CALL	RemoveFile									(struct SFileToRemove FileToRemove);
int32 							BS_CALL	RenameFile									(struct SFileToRename FileToRename);
int32 							BS_CALL	RenameDir									(struct SDirToRename DirToRename);
int32 							BS_CALL	SetFileAttr									(const TCHAR *lpszFilePath, int32 nFileAttributes);
int32 							BS_CALL	SetFileTimes								(const TCHAR *lpszFilePath, const SFileDateTime *pCreationTime, const SFileDateTime *pModificationTime, const SFileDateTime *pAccessTime);
int32 							BS_CALL	SetFileUserParam							(const TCHAR *lpszFilePath, void *pUserData);
int32 							BS_CALL	GetFileEntry								(const TCHAR *lpszFilePath, struct SFileEntry* pFileEntry);
int32 							BS_CALL	SetRAWStructure								(struct SRAWTrackToAdd* pTracks, int32 nLength);
int32 							BS_CALL	ClearAll									(void);
int32 							BS_CALL	GetPrecisePlayTime							(const TCHAR *strFileName, double *time);
int32 							BS_CALL	GetPlayTime									(const TCHAR *strFileName, int32 *time);
int32 							BS_CALL	PlayAudioFile								(const TCHAR *strFileName);
int32 							BS_CALL	DAPlayAudioTrack							(const TCHAR* lpszDevice, int16 nTrackNumber);
int32 							BS_CALL	PlayAudioTrack								(int16 nTrackNumber);
int32 							BS_CALL	GetAudioTags								(const TCHAR* strFileName, const char* tags);
int32 							BS_CALL	AudioFileStop								(void);
int32 							BS_CALL LoadBassPlugin          					(const TCHAR *strFileName);
int32 							BS_CALL	GetAudioFileSize							(const TCHAR *strFileName, double *fSize);
int32 							BS_CALL	StopMpegAction								(void);
int32 							BS_CALL	EraseMpegByIndex							(int32 index);
int32 							BS_CALL	GetMpegCount								(void);
int32 							BS_CALL SetVCDKeyHandler							(int32 nItemNumber, int32 nKey, int32 nNextItemNumber);
int32 							BS_CALL SetVCDTimeOutHandler						(int32 nItemNumber, int32 nTimeOut, int32 nNextItemNumber);
#	ifdef __cplusplus
int32 							BS_CALL	DAOpenDiskSession							(const TCHAR* lpszDevice, int32 nTrackNumber, HSESSION* phSession, int32 nFileSystem = BS_FS_UNKNOWN);
int32 							BS_CALL	OpenDiskSession								(int32 index, int32 nTrackNumber, HSESSION *phSession, int32 nFileSystem = BS_FS_UNKNOWN);
#	else
int32 							BS_CALL	DAOpenDiskSession							(const TCHAR* lpszDevice, int32 nTrackNumber, HSESSION* phSession, int32 nFileSystem);
int32 							BS_CALL	OpenDiskSession								(int32 index, int32 nTrackNumber, HSESSION *phSession, int32 nFileSystem);
#	endif
int32 							BS_CALL	CloseDiskSession							(HSESSION hSession);
int32 							BS_CALL GetUDFVolumeInformation						(HSESSION hSession, struct SUDFVolumeInfo* pUDFVolumeInfo);
int32 							BS_CALL GetISOVolumeInformation						(HSESSION hSession, struct SISOVolumeInfo* pISOVolumeInfo);
int32 							BS_CALL GetBootVolumeInformation					(HSESSION hSession, struct SBootVolumeInfo* pBootVolumeInfo);
int32 							BS_CALL	OpenDirectory								(HSESSION hSession, const TCHAR *lpszDirName, HDIR *phDir);
int32 							BS_CALL	CloseDirectory								(HDIR hDirectory);
int32 							BS_CALL	GetNumberOfFiles							(HDIR hDirectory, int32* pNumber);
int32 							BS_CALL	ReadDirectory								(HDIR hDirectory, int32 nIndex, struct SFileEntry* pFileEntry);
int32 							BS_CALL DAReadFileContents							(const TCHAR* lpszDevice, HSESSION hSession, const TCHAR* lpszFilePath, int64 nOffset, void* pBuffer, int32 nBufferSize, int32* pRead);
int32 							BS_CALL ReadFileContents							(HSESSION hSession, const TCHAR* lpszFilePath, int64 nOffset, void* pBuffer, int32 nBufferSize, int32* pRead);
int32 							BS_CALL	GetFileAllocationTable						(HSESSION hSession, const TCHAR* lpszFilePath, struct SFileAllocationTable *pAllocTable, int32 *pnTableSize);
BS_BOOL 						BS_CALL	IsValidVideoTsFolder						(const TCHAR *strPath);
////////////////////////////////////////////////////////////////////////////////////////
// End functions to deal with the available project types				 			  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Functions to deal with the bruning options			 			 				  //
////////////////////////////////////////////////////////////////////////////////////////
int32 							BS_CALL	SetOptions									(struct SOptions Options);
int32 							BS_CALL	GetOptions									(struct SOptions *pOptions);
int32							BS_CALL SetFileTimeEx								(struct SFileTimeEx FileTimeEx);
int32							BS_CALL GetFileTimeEx								(struct SFileTimeEx* FileTimeEx);
int32 							BS_CALL	SetISOInfoEx								(struct SISOInfoEx IsoInfoEx);
int32 							BS_CALL	GetISOInfoEx								(struct SISOInfoEx *pIsoInfoEx);
int32 							BS_CALL	SetUDFOptions								(struct SUDFOptions UdfOptions);
int32 							BS_CALL	GetUDFOptions								(struct SUDFOptions *pUdfOptions);
int32 							BS_CALL	SetUDFOptionsEx								(struct SUDFOptionsEx *pUdfOptions);
int32 							BS_CALL	GetUDFOptionsEx								(struct SUDFOptionsEx *pUdfOptions);
int32 							BS_CALL	SetBootInfoEx								(struct SBootInfoEx BootInfoEx);
int32 							BS_CALL	GetBootInfoEx								(struct SBootInfoEx *pBootInfoEx);
int32 							BS_CALL	SetCompressEncrypt							(struct SCompressEncryptInfo CEInfo);
int32 							BS_CALL	GetCompressEncrypt							(struct SCompressEncryptInfo* pCEInfo);
int32 							BS_CALL SetDVDVideoOptions							(struct SDVDVideoOptions DVDVideoOptions);
int32 							BS_CALL GetDVDVideoOptions							(struct SDVDVideoOptions* pDVDVideoOptions);
int32 							BS_CALL	SaveOptionsToFile							(const TCHAR *pchPath);
int32 							BS_CALL	SetOptionsFromFile							(const TCHAR *pchPath);
////////////////////////////////////////////////////////////////////////////////////////
// End functions to deal with the bruning options			 			 			  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Functions to work with burning			 			 				 			  //
////////////////////////////////////////////////////////////////////////////////////////
int32							BS_CALL	SetIgnoreFileExist							(BS_BOOL bIgnore);
int32 							BS_CALL	DAPrepare									(const TCHAR* lpszDevice);
int32 							BS_CALL	Prepare										(void);
int32 							BS_CALL	GetImageSize								(double *pdImageSize);
int32							BS_CALL DABurnISOImage								(const TCHAR* lpszDevice, const TCHAR* pchFilePath, struct SOptions options);
int32 							BS_CALL	BurnISO										(const TCHAR *pchFilePath, struct SOptions options);
int32 							BS_CALL	DABurn										(const TCHAR* lpszDevice);
int32 							BS_CALL	Burn										(void);
int32 							BS_CALL	Abort										(void);
int32 							BS_CALL	SetVerify									(BS_BOOL bVerify);
int32 							BS_CALL	GetVerify									(BS_BOOL *bVerify);
int32 							BS_CALL	SaveLogToFile								(const TCHAR* pchFilePath);
////////////////////////////////////////////////////////////////////////////////////////
// End functions to work with burning			 			 				 		  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Undocumented functions		 			 				 			  			  //
////////////////////////////////////////////////////////////////////////////////////////
int32 							BS_CALL ForceDeInitialize							(BS_BOOL bForce);
////////////////////////////////////////////////////////////////////////////////////////
// End Undocumented functions				 			 				 			  //
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Functions to use the prebuild dialogs inside the IsoSDK		 		  			  //
// On Linux and Max X11 is needed								 		  			  //
// BS_GUI is not available in FoxCore Library					 		  			  //
////////////////////////////////////////////////////////////////////////////////////////
#	ifdef BS_GUI
void 							BS_CALL	DeInitALL									();
int32 							BS_CALL	SetFXApp									(void* pApp);
#		ifdef __cplusplus
int32 							BS_CALL	EraseDialog									(const TCHAR *pchTitle = NULL);		// null-terminated
int32 							BS_CALL	BurnDialog									(BS_BOOL bAutoRun = BS_FALSE, BS_BOOL bOpenSettings = BS_FALSE, BS_BOOL bViewSettings = BS_TRUE, const TCHAR *pchTitle = NULL, const TCHAR *pchIsoFilePath = NULL);
#		else
int32 							BS_CALL	EraseDialog									(const TCHAR *pchTitle);				// null-terminated
int32 							BS_CALL	BurnDialog									(BS_BOOL bAutoRun, BS_BOOL bOpenSettings, BS_BOOL bViewSettings, const TCHAR *pchTitle, const TCHAR *pchIsoFilePath);
#		endif
int32 							BS_CALL	MultiDeviceDialog							();
int32 							BS_CALL	TagsFromNetworkDialog						(int32 nDeviceIndex, int32 *pHandle);
#	endif
////////////////////////////////////////////////////////////////////////////////////////
// End functions to use the prebuild dialogs inside the IsoSDK			 			  //
////////////////////////////////////////////////////////////////////////////////////////

#	ifdef __cplusplus
}
#	endif

#endif	// __ISOSDK_EXPORT_H__
