// ConsoleBurner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
typedef unsigned int UINT;


const TCHAR chHelp[]						= _T("-help");
const TCHAR chFolder[]						= _T("-folder");
const TCHAR chDevice[]						= _T("-device");
const TCHAR chSpeed[]						= _T("-speed");
const TCHAR chLabel[]						= _T("-label");
const TCHAR chNoJoliet[]					= _T("-nojoliet");
const TCHAR chFinalize[]					= _T("-finalize");
const TCHAR chVerify[]						= _T("-verify");
const TCHAR chCache[]						= _T("-cache");
const TCHAR chEject[]						= _T("-eject");
const TCHAR chProject[]						= _T("-project");
const TCHAR chImage[]						= _T("-image");
const TCHAR chIso[]							= _T("-iso");
const TCHAR chUdfVersion[]					= _T("-udfver");
const TCHAR chPartition[]					= _T("-ptype");
const TCHAR chStreams[]						= _T("-streams");
const TCHAR chBoot[]						= _T("-boot");
const TCHAR chWriteMethod[]					= _T("-writemethod");
const TCHAR chASPI[]						= _T("-aspi");
const TCHAR chCompress[]					= _T("-compress");
const TCHAR chEncrypt[]						= _T("-encrypt");
const TCHAR chAudioFolder[]					= _T("-audiofolder");
const TCHAR chDataFile[]					= _T("-data");
const TCHAR chAudioFile[]					= _T("-audio");
const TCHAR chImportSession[]				= _T("-importsession");
const TCHAR chCopyDisc[]					= _T("-copydisc");

const TCHAR* chProjectMap[10]				= { _T("audio"), _T("") ,_T("iso"), _T(""), _T("") , _T("videodvd"),
												_T("udfdvd"), _T("isoudf"), _T("bluray"), _T("mixmode") };
const TCHAR* chPartitions[3]				= { _T("physical"), _T("virtual"), _T("sparable") };
const TCHAR* chUdfVersions[6]				= { _T("1.02"), _T("1.50"), _T("2.00"), _T("2.01"), _T("2.50"), _T("2.60") };
const int32 aVersionsMap[6]					= { BS_UDF_VERSION_102, BS_UDF_VERSION_150, BS_UDF_VERSION_200
												,BS_UDF_VERSION_201 ,BS_UDF_VERSION_250 ,BS_UDF_VERSION_260 };

const TCHAR* chASPIs[3]						= { _T("spti"), _T("wnaspi"), _T("frogaspi") };
const int32 aASPIsMap[3]					= { BS_ASPI_INTERNAL, BS_ASPI_WNASPI, BS_ASPI_FROGASPI };

const TCHAR* chCompressionLevels[10]		= { _T("0"), _T("1"), _T("2"), _T("3"), _T("4"), _T("5")
												, _T("6"), _T("7"), _T("8"), _T("9") };


const TCHAR* chWriteMethods[3]				= { _T("tao"), _T("dao"), _T("dao96") };

const TCHAR* chErrorCorrection[2]			= { _T("no"), _T("yes") };

// Burning options
TCHAR*				g_lpszFolderName		= 0;		// Folder to burn
TCHAR*				g_lpszAudioFolderName	= 0;		// Folder to burn
int32				g_nAspi					= BS_ASPI_INTERNAL;	// Use SPTI
TCHAR*				g_chDriveLetter			= 0;		// Burning device
int32				g_nBurningSpeed			= 0;		// Bunring speed
tstring				g_strVolumeLabel		= _T("New");	// Volume Label
bool				g_bJoliet				= true;			// Use Joliet file system
bool				g_bFinalize				= false;		// Finalize disk after burn
bool				g_bVerify				= false;			// Virify data after burn
int32				g_nCacheSize			= 1024 * 1024 * 4;	// Cache size, default - 4M
bool				g_bEject				= false;			// Eject medium after burn
int32				g_nProjectType			= BS_BURNER_DATA;	// Project type, default - ISO
TCHAR*				g_lpszImage				= 0;			// If specified, path to file to write image
TCHAR*				g_lpszIsoImage			= 0;			// If specified, path to image file to write from
TCHAR*				g_lpszBootImage			= 0;		// Boot image
int32				g_nUdfVersion			= BS_UDF_VERSION_102;
int32				g_nUdfPartition			= BS_UDF_PARTITION_PHYSICAL;
bool				g_bWriteStreams			= false;
int32				g_nWriteMethod			= BS_WM_TAO;
bool				g_bCompression			= false;
int32				g_nCompressionLevel		= 0;
bool				g_bEncryption			= false;
char*				g_lpszPassword			= 0;
int32				g_nSessionToContinue	= 0;
bool				g_bCopyDisc				= false;				// Set copy disc operation
TCHAR*				g_chSourceDriveLetter	= 0;		// Source device for copy disc operation
bool				g_bErrorCorection		= false;			// Set error corection flag for copy disc operation
int32				g_nReadMode				= BS_RM_RAW;

std::vector<TCHAR*>	g_vAudioFilesToAdd;
std::vector<TCHAR*>	g_vDataFilesToAdd;

bool				g_bDone					= false;
KCriticalSection	g_cOutputLock;
tstring				g_strBuffer;

void PrintHelp(TCHAR* lpszAppName)
{
	_tcout << endl
		<< _T("Console Burner Sample") << endl
		<< _T("Usage: ") << lpszAppName << _T(" <folder name> [<options>]") << endl << endl
		<< _T("Options are:") << endl
		<< _T("    -help        			# Show usage") << endl
		<< _T("    -folder        			# Set folder to burn") << endl
		<< _T("    -aspi <type>				# Use external ASPI realization instead internal") << endl
		<< _T("    -device <letter>			# Set burning device by drive letter associated with it. Min 2 chars like D: or 1:") << endl
		<< _T("    -speed <speed>			# Set burning speed") << endl
		<< _T("    -label <string>			# Set label for volume. Default lable is \"New\"") << endl
		<< _T("    -nojoliet				# Don't use joliet file system") << endl
		<< _T("    -finalize				# Finalize medium after burn") << endl
		<< _T("    -verify	    			# Verify data after burn") << endl
		<< _T("    -cache <size>			# Set size of cache. Default is 4MB") << endl
		<< _T("    -eject	    			# Eject medium after burn") << endl
		<< _T("    -boot					# Boot image path") << endl
		<< _T("    -project <type>			# Set project type. Default is iso.") << endl
		<< _T("                  			# Following types are supported: ") << endl
		<< _T("                 			# audio, iso, videodvd, udfdvd, isoudf") << endl
		<< _T("    -image <path>			# Set path to file to write image") << endl
		<< _T("    -iso <path>				# Burn image file from hard drive") << endl
		<< _T("    -udfver <ver>			# Set version of UDF in UDF projects") << endl
		<< _T("    -ptype <type>			# Set type of partition in UDF projects") << endl
		<< _T("    -streams					# Write file streams in UDF projects") << endl
		<< _T("    -writemethod <type>		# Set write method. Default is TAO") << endl
		<< _T("    -compress <level>		# Set compression level. Only for ISO projects") << endl
		<< _T("    -encrypt <password>		# Set encryption password. Only for ISO projects") << endl
		<< _T("    -audiofolder <path>		# Set additional audio folder path. Only for mix-mode projects") << endl
		<< _T("    -audio <path>			# Set additional audio file path. Only for mix-mode projects") << endl
		<< _T("    -data <path>				# Set additional data file path. Only for mix-mode projects") << endl
		<< _T("    -importsession <number>	# Set session number to continue. Default is 0 - last session. Only for multisession projects") << endl
		<< endl
		<< _T("    -erase					# Erase the disc. Default is 0 = fast. For complete use 1") << endl
		<< _T("    -copydisc <letter> <mode> <correction>	# Set copy disc to dics operation. <letter> : letter of source device; <mode> : 0 - user data, 1 - raw, 2 - raw+subchannel; <correction> : yes, no - error correction flag") << endl;


}

bool ParseCommandLine(UINT argc, _TCHAR* argv[])
{
	if (argc < 2)
	{
		_tcout << _T("Error: Parameters are not specified.") << endl;
		return false;
	}

	if (!_tcscmp(argv[1], chHelp))
	{
		return false;	// Caller will print help and exit
	}

	g_vAudioFilesToAdd.clear();
	g_vDataFilesToAdd.clear();

	UINT i = 1;

	while (i < argc)
	{
		if (!_tcscmp(argv[i], chHelp))
		{
			return false;	// Caller will print help and exit
		}

		if (!_tcscmp(argv[i], chFolder))
		{
			if (i + 1 < argc)
			{
				g_lpszFolderName = argv[i + 1];

				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: folder name expected") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chNoJoliet))
		{
			g_bJoliet = false;
			i++;
			continue;
		}

		if (!_tcscmp(argv[i], chStreams))
		{
			g_bWriteStreams = true;
			i++;
			continue;
		}
		if (!_tcscmp(argv[i], chFinalize))
		{
			g_bFinalize = true;
			i++;
			continue;
		}
		if (!_tcscmp(argv[i], chEject))
		{
			g_bEject = true;
			i++;
			continue;
		}
		if (!_tcscmp(argv[i], chVerify))
		{
			g_bVerify = true;
			i++;
			continue;
		}

		if (!_tcscmp(argv[i], chSpeed))
		{
			if (i + 1 < argc)
			{
				g_nBurningSpeed = _tstoi(argv[i + 1]);
				if (!g_nBurningSpeed)
				{
					_tcout << _T("Error: ") << argv[i + 1] << _T(" is not valid speed value.") << endl;
					return false;
				}
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: speed value expected") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chLabel))
		{
			if (i + 1 < argc)
			{
				g_strVolumeLabel = argv[i + 1];

				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: volume label expected.") << endl;
				return false;
			}
		}


		if (!_tcscmp(argv[i], chCache))
		{
			if (i + 1 < argc)
			{
				g_nCacheSize = _tstoi(argv[i + 1]);
				if (!g_nCacheSize)
				{
					_tcout << _T("Error: ") << argv[i + 1] << " is not valid cache size value." << endl;
					return false;
				}
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: cache size value expected.") << endl;
				return false;
			}

		}

		if (!_tcscmp(argv[i], chProject))
		{
			if (i + 1 < argc)
			{
				UINT j;
				for (j = 0; j < 10; j++)
				{
					if (!_tcscmp(argv[i + 1], chProjectMap[j]))
					{
						g_nProjectType = j;
						break;
					}
				}
				if (j == 10)
				{
					_tcout << _T("Error: unknown project type.") << endl;
					return false;
				}

				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: project type expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chImage))
		{
			if (i + 1 < argc)
			{
				g_lpszImage = argv[i + 1];
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: image file name expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chIso))
		{
			if (i + 1 < argc)
			{
				g_lpszIsoImage = argv[i + 1];
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: iso image file name expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chBoot))
		{
			if (i + 1 < argc)
			{
				g_lpszBootImage = argv[i + 1];
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: boot image file name expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chDevice))
		{
			if (i + 1 < argc)
			{
				if (_tcslen(argv[i + 1]) > 50)
				{
					_tcout << _T("Error: '") << argv[i + 1] << _T("' is invalid drive letter.") << endl;
					return false;
				}
				else
				{
					g_chDriveLetter = argv[i + 1];
					i += 2;
					continue;
				}
			}
			else
			{
				_tcout << _T("Error: drive letter expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chUdfVersion))
		{
			if (i + 1 < argc)
			{
				UINT j;
				for (j = 0; j < 6; j++)
				{
					if (!_tcscmp(argv[i + 1], chUdfVersions[j]))
					{
						g_nUdfVersion = j;
						break;
					}
				}
				if (j == 6)
				{
					_tcout << _T("Error: unknown UDF version.") << endl;
					return false;
				}
				g_nUdfVersion = aVersionsMap[g_nUdfVersion];
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: UDF version expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chPartition))
		{
			if (i + 1 < argc)
			{
				UINT j;
				for (j = 0; j < 3; j++)
				{
					if (!_tcscmp(argv[i + 1], chPartitions[j]))
					{
						g_nUdfPartition = j;
						break;
					}
				}
				if (j == 3)
				{
					_tcout << _T("Error: unknown partition type.") << endl;
					return false;
				}
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: UDF version expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chWriteMethod))
		{
			if (i + 1 < argc)
			{
				UINT j;
				for (j = 0; j < 3; j++)
				{
					if (!_tcscmp(argv[i + 1], chWriteMethods[j]))
					{
						g_nWriteMethod = j;
						break;
					}
				}
				if (j == 3)
				{
					_tcout << _T("Error: unknown write method.") << endl;
					return false;
				}
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Write method expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chASPI))
		{
			if (i + 1 < argc)
			{
				UINT j;
				for (j = 0; j < 3; j++)
				{
					if (!_tcscmp(argv[i + 1], chASPIs[j]))
					{
						g_nAspi = j;
						break;
					}
				}
				if (j == 3)
				{
					_tcout << _T("Error: unknown ASPI driver.") << endl;
					return false;
				}

				g_nAspi = aASPIsMap[g_nAspi];
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Name of ASPI driver expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chCompress))
		{
			if (i + 1 < argc)
			{
				UINT j;
				for (j = 0; j < 10; j++)
				{
					if (!_tcscmp(argv[i + 1], chCompressionLevels[j]))
					{
						g_nCompressionLevel = j;
						break;
					}
				}
				if (j == 10)
				{
					_tcout << _T("Error: Compression level should be between 0 and 9.") << endl;
					return false;
				}

				g_bCompression = true;
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Compression level expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chEncrypt))
		{
			if (i + 1 < argc)
			{
				USES_CONVERSION;
				g_lpszPassword = T2A(argv[i + 1]);

				g_bEncryption = true;
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Password expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chAudioFolder))
		{
			if (i + 1 < argc)
			{
				g_lpszAudioFolderName = argv[i + 1];

				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Audio folder path expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chAudioFile))
		{
			if (i + 1 < argc)
			{
				g_vAudioFilesToAdd.push_back(argv[i + 1]);

				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Audio file path expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chDataFile))
		{
			if (i + 1 < argc)
			{
				g_vDataFilesToAdd.push_back(argv[i + 1]);

				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Audio file path expected.") << endl;
				return false;
			}
		}

		if (!_tcscmp(argv[i], chImportSession))
		{
			if (i + 1 < argc)
			{
				g_nSessionToContinue = _tstoi(argv[i + 1]);
				if (g_nSessionToContinue < 0)
				{
					_tcout << _T("Error: ") << argv[i + 1] << _T(" is not valid session value value.") << endl;
					return false;
				}
				i += 2;
				continue;
			}
			else
			{
				_tcout << _T("Error: Session number to continue expected") << endl;
				return false;
			}
		}



		if (!_tcscmp(argv[i], chCopyDisc))
		{
			if (i + 1 < argc)
			{
				g_chSourceDriveLetter = argv[i + 1];
				g_bCopyDisc = true;
				i += 1;

				if (i + 1 < argc)
				{
					g_nReadMode = _tstoi(argv[i + 1]);
					if (g_nReadMode < 0 || g_nReadMode > 2)
					{
						_tcout << _T("Error: ") << argv[i + 1] << _T(" is not valid read mode value value.") << endl;
						return false;
					}

					i += 1;

					if (i + 1 < argc)
					{
						int32 j;
						for (j = 0; j < 2; j++)
						{
							if (!_tcscmp(argv[i + 1], chErrorCorrection[j]))
							{
								g_bErrorCorection = (bool)j;
								break;
							}
						}
						if (j == 2)
						{
							_tcout << _T("Error: ") << argv[i + 1] << _T(" is not valid error correction value.") << endl;
							return false;
						}

						i += 2;
					}
				}
				continue;
			}
			else
			{
				_tcout << _T("Error: Session number to continue expected") << endl;
				return false;
			}
		}



		_tcout << _T("Error: unknown argument '") << argv[i] << _T("'") << endl;
		return false;
	}
	return true;
}

void HandleError(int32 nError)
{
	if (nError != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		::GetText(nError, chError, &nLength);

		_tcout << "Error: " << chError;
		getchar();
		exit(-1);
	}
}

void OnBurnDone(const TCHAR* pcError, void* pUserData)
{
	g_cOutputLock.Lock();
	g_strBuffer += _T("Burn done: ") + tstring(pcError ? pcError : _T("no errors.")) + _T("\n");
	g_cOutputLock.UnLock();
}

void OnJobDone(void*)
{
	g_cOutputLock.Lock();
	g_bDone = true;
	g_cOutputLock.UnLock();
}

void OnFinalize(void*)
{
	g_cOutputLock.Lock();
	g_strBuffer += _T("\n");
	g_strBuffer += _T("Finalizing disc...\n");
	g_cOutputLock.UnLock();
}

void OnProcess(float fPercent, float fDeviceBuffer, float fCache,
	double dBytesWritten, double dImageSize, void* pUserData)
{
	static int nChars = 0;
	g_cOutputLock.Lock();

	while ((fPercent / 100.0) * 80 > nChars)
	{

		g_strBuffer += _T("*");
		nChars++;

	}
	g_cOutputLock.UnLock();
}

void OnVerifyDone(int32 nErrors, void* pUserData)
{
	g_cOutputLock.Lock();
	TCHAR buff[20];
	_itot(nErrors, buff, 10);
	g_strBuffer += _T("Verification complete. Total errors: ") + tstring(buff) + _T("\n");
	g_cOutputLock.UnLock();
}

void OnVerifyFile(const TCHAR* pcFileName, void* pUserData)
{
}

void OnStartVerify(void* pUserData)
{
	g_cOutputLock.Lock();
	g_strBuffer += _T("Verification started.\n");
	g_cOutputLock.UnLock();
}

void OnVerifyError(const TCHAR* pcFileName, const TCHAR* pcError, void* pUserData)
{
	g_cOutputLock.Lock();
	g_strBuffer += _T("Verification error: ") + tstring(pcFileName) + _T(" ")
		+ tstring(pcError) + tstring(_T("\n"));
	g_cOutputLock.UnLock();
}

void BurnToCD()
{
	int32 nRes = 0;

	::SetBurnDevice(g_chDriveLetter);
	::SetBurnSpeed(g_nBurningSpeed ? g_nBurningSpeed : BS_MAX_SPEED);

	_tcout << _T("Preparing image...") << endl;
	nRes = ::Prepare();
	HandleError(nRes);

	nRes = ::Burn();
	HandleError(nRes);
}

void BurnFromISO()
{
	int32 nRes = 0;

	::SetBurnDevice(g_chDriveLetter);
	::SetBurnSpeed(g_nBurningSpeed ? g_nBurningSpeed : BS_MAX_SPEED);

	SOptions options;
	::GetOptions(&options);

	nRes = ::BurnISO(g_lpszIsoImage, options);
	HandleError(nRes);
}

void CopyDisc()
{
	int32 nRes = 0;

	::SetBurnDevice(g_chDriveLetter);
	::SetBurnSpeed(g_nBurningSpeed ? g_nBurningSpeed : BS_MAX_SPEED);
	::SetReadDevice(g_chSourceDriveLetter);

	SDiskCopyOptions cDiscCopyOptions;
	cDiscCopyOptions.bVerifyAfterBurn = g_bVerify;
	cDiscCopyOptions.nReadMode = g_nReadMode;
	cDiscCopyOptions.nWriteMethod = g_nWriteMethod;

	SReadErrorCorrectionParams cCorrecionParams;
	cCorrecionParams.bErrorCorrection = g_bErrorCorection;

	cDiscCopyOptions.cErrorParams = cCorrecionParams;

	nRes = ::CopyDisk(cDiscCopyOptions);
	HandleError(nRes);
}

void BurnToImage()
{
	int32 nRes = 0;

	_tcout << _T("Preparing image...") << endl;

	nRes = ::SetBurnDevice(_T("#:"));
	HandleError(nRes);

	nRes = ::SetImageFilePath(g_lpszImage);
	HandleError(nRes);

	nRes = ::Prepare();
	HandleError(nRes);

	nRes = ::Burn();
	HandleError(nRes);

	g_bVerify = false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Parse command line
	if (!ParseCommandLine(argc, argv))
	{
		PrintHelp(argv[0]);
		exit(0);
	}

	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
	int32 nRes = BS_SDK_ERROR_NO;

	nRes = Initialize(chLicenseKey, g_nAspi, BS_TRUE);
	HandleError(nRes);

	SetFinalizeEventCallback(OnFinalize, 0);
	SetBurnDoneEventCallback(OnBurnDone, 0);
	SetProcessEventCallback(OnProcess, 0);
	SetJobDoneEventCallback(OnJobDone, 0);
	SetVerifyDoneEventCallback(OnVerifyDone, 0);
	SetVerifyFileEventCallback(OnVerifyFile, 0);
	SetStartVerifyEventCallback(OnStartVerify, 0);
	SetVerifyErrorEventCallback(OnVerifyError, 0);



	if (g_lpszIsoImage)
	{
		g_nProjectType = BS_BURNER_DATA;
	}

	if (g_nSessionToContinue)
	{
		// check if project supports multisession
		if (g_nProjectType == BS_BURNER_DATA ||
			g_nProjectType == BS_BURNER_UDFDVD ||
			g_nProjectType == BS_BURNER_ISOUDF ||
			g_nProjectType == BS_BURNER_BLURAY)
		{
			nRes = ::CreateProject(g_nProjectType, g_nSessionToContinue);
			HandleError(nRes);
		}
		else
		{
			_tcout << _T("Error: Current project doesn't support multisession.") << endl;
			return false;
		}
	}
	else
	{
		nRes = ::CreateProject(g_nProjectType);
		HandleError(nRes);
	}

	SOptions cOptions;
	::GetOptions(&cOptions);

	if (g_lpszBootImage)
	{
		cOptions.bBootable = BS_TRUE;
		_tcscpy(cOptions.chBootImage, g_lpszBootImage);
	}
	else
	{
		cOptions.bBootable = BS_FALSE;
	}

	cOptions.bEjectAfterBurn = g_bEject ? BS_TRUE : BS_FALSE;
	cOptions.bFinalize = g_bFinalize ? BS_TRUE : BS_FALSE;
	cOptions.bJolietFileSystem = g_bJoliet ? BS_TRUE : BS_FALSE;
	cOptions.bVerifyAfterBurn = g_bVerify && !g_lpszImage ? BS_TRUE : BS_FALSE;
	cOptions.nCacheSize = g_nCacheSize;
	cOptions.nWriteMethod = g_nWriteMethod;


	if (g_strVolumeLabel.size() < 128)
	{
		_tcscpy(cOptions.chVolumeLabel, g_strVolumeLabel.c_str());
	}
	else
	{
		memcpy(cOptions.chVolumeLabel, g_strVolumeLabel.c_str(), 127);
		cOptions.chVolumeLabel[127] = 0;
	}

	SetOptions(cOptions);
	GetOptions(&cOptions);

	if (g_nProjectType == BS_BURNER_ISOUDF
		|| g_nProjectType == BS_BURNER_UDFDVD || g_nProjectType == BS_BURNER_BLURAY)
	{
		SUDFOptions cUDFOptions;
		cUDFOptions.PartitionType = g_nUdfPartition;
		cUDFOptions.Version = g_nUdfVersion;
		cUDFOptions.WriteFileStreams = g_bWriteStreams ? 1 : 0;
		nRes = SetUDFOptions(cUDFOptions);
		HandleError(nRes);
	}

	if (g_bCompression || g_bEncryption)
	{
		if (g_nProjectType != BS_BURNER_DATA)
		{
			_tcout << _T("Error: Encryption and compression can be implemented only to ISO projects. So it will be not implemented.") << endl;
		}
		else
		{
			SCompressEncryptInfo cCompressEncryptInfo;
			cCompressEncryptInfo.bCompression = g_bCompression;
			cCompressEncryptInfo.bEncryption = g_bEncryption;
			cCompressEncryptInfo.lpszPassword = g_lpszPassword;
			cCompressEncryptInfo.nCompressionLevel = g_nCompressionLevel;

			nRes = ::SetCompressEncrypt(cCompressEncryptInfo);
			HandleError(nRes);
		}
	}

	if (!g_lpszImage)
	{
		if (!g_chDriveLetter)
		{
			TCHAR	chListDevices[26][50];
			int32 nUsed = 0;

			nRes = ::GetDevices(chListDevices, &nUsed, BS_TRUE);
			HandleError(nRes);

			if (!nUsed)
			{
				_tcout << _T("Error: no burning devices found.") << endl;
				exit(-1);
			}
			else
			{
				g_chDriveLetter = chListDevices[0];
			}
		}
	}

	/* _tcout << _T("Options:") << endl;
	_tcout << _T("Device		:	") << g_chDriveLetter << _T(":") << endl;
	_tcout << _T("Joliet		:	") << cOptions.bJolietFileSystem << endl;
	_tcout << _T("Finalize		:	") << cOptions.bFinalize << endl;
	_tcout << _T("Verify		:	") << cOptions.bVerifyAfterBurn << endl;
	_tcout << _T("Eject			:	") << cOptions.bEjectAfterBurn << endl; */

	SISOInfoEx sIsoInfoEx;
	GetISOInfoEx(&sIsoInfoEx);
	sIsoInfoEx.ISOAddSuffix = BS_FALSE;
	SetISOInfoEx(sIsoInfoEx);

	SBootInfoEx sBootInfo;
	GetBootInfoEx(&sBootInfo);
	sBootInfo.BootIndicator = 88;
	sBootInfo.Emulation = 0;
	sBootInfo.LoadSegment = 0x00;
	sBootInfo.PlatformID = 0;
	sBootInfo.SectorCount = 4;
	SetBootInfoEx(sBootInfo);



	if (g_nProjectType == BS_BURNER_MIXEDMODE)
	{
		if (g_lpszAudioFolderName)
		{
			SDirToAdd cDirToAdd;
			cDirToAdd.lpszSourceDirPath = g_lpszAudioFolderName;
			cDirToAdd.lpszDestinationPath = _T("\\audio");
			cDirToAdd.nSavePath = BS_DONT_SAVE_PATH;
			nRes = ::AddDir(cDirToAdd);
			HandleError(nRes);
		}

		int32 nAudioFilesSize = (int32)g_vAudioFilesToAdd.size();
		if (nAudioFilesSize > 0)
		{
			for (int32 i = 0; i < nAudioFilesSize; i++)
			{
				SFileToAdd cFileToAdd;
				cFileToAdd.lpszSourceFilePath = g_vAudioFilesToAdd[i];
				cFileToAdd.lpszDestinationPath = _T("\\data");
				cFileToAdd.nSavePath = BS_DONT_SAVE_PATH;
				nRes = ::AddFile(cFileToAdd);
				HandleError(nRes);
			}
		}

		int32 nDataFilesSize = (int32)g_vDataFilesToAdd.size();
		if (nDataFilesSize > 0)
		{
			for (int32 i = 0; i < nDataFilesSize; i++)
			{
				SFileToAdd cFileToAdd;
				cFileToAdd.lpszSourceFilePath = g_vDataFilesToAdd[i];
				cFileToAdd.lpszDestinationPath = _T("\\data");
				cFileToAdd.nSavePath = BS_DONT_SAVE_PATH;
				nRes = ::AddFile(cFileToAdd);
				HandleError(nRes);
			}
		}
	}
	else {

		if (g_lpszFolderName)
		{
			SDirToAdd cDirToAdd;
			cDirToAdd.lpszSourceDirPath = g_lpszFolderName;
			cDirToAdd.lpszDestinationPath = _T("\\");
			cDirToAdd.nSavePath = BS_DONT_SAVE_PATH;
			nRes = ::AddDir(cDirToAdd);
			HandleError(nRes);
		}
		int32 nDataFilesSize = (int32)g_vDataFilesToAdd.size();
		if (nDataFilesSize > 0)
		{
			for (int32 i = 0; i < nDataFilesSize; i++)
			{
				SFileToAdd cFileToAdd;
				cFileToAdd.lpszSourceFilePath = g_vDataFilesToAdd[i];
				cFileToAdd.lpszDestinationPath = _T("\\");
				cFileToAdd.nSavePath = BS_DONT_SAVE_PATH;
				nRes = ::AddFile(cFileToAdd);
				HandleError(nRes);
			}
		}
	}

	if (g_bCopyDisc)
	{
		CopyDisc();
	}
	else if (g_chDriveLetter)
	{
		if (g_lpszIsoImage)
		{
			BurnFromISO();
		}
		else
		{
			BurnToCD();
		}
	}
	else
	{
		BurnToImage();
	}

	_tcout << _T("Burning:") << endl;
	_tcout << _T("0%--------------------------------------------------------------------------100%") << endl;

	for (; !g_bDone;)
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				PostQuitMessage((int)msg.wParam);
				return 0;
			}

			DispatchMessage(&msg);
		}

#ifdef WIN32
		Sleep(5);
#else
		sleep(5);
#endif
		g_cOutputLock.Lock();
		if (!g_strBuffer.empty())
		{
			_tcout << g_strBuffer;
			g_strBuffer.clear();
		}

		g_cOutputLock.UnLock();
	}

	::SaveLogToFile(_T("isosdk.log"));

#ifdef WIN32
	Sleep(500);
#else
	sleep(500);
#endif

	return 0;
}
