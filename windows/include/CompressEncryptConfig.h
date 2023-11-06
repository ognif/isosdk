#ifndef COMPRESSENCRYPTCONFIG_H
#define COMPRESSENCRYPTCONFIG_H


#define SFIOCTL_TYPE 74001
#define SF_FSCTL_SET_DECRYPT_KEY	CTL_CODE(SFIOCTL_TYPE, 0x900, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FOXFILTER_DOSDEVICE_NAME L"\\DosDevices\\FoxRdr"
#define DriverName				_T("FoxFilter")
#define DriverDosName			_T("\\\\.\\FoxRdr")


#define BS_COMPRESSED_SIGNATURE_FOR_DRIVER 'CxoF'

/// Signature, which appends to the end of compressed file
#define BS_COMPRESSED_SIGNATURE	"FoxC"

#define	COMPRESS_BLOCKSIZE	8192
#define ENCRYPT_BLOCKSIZE	2048


typedef struct _FoxEntries
{
	uint64	lnOffset;			//< Offset of a block in a compressed file, in bytes
	uint64	lnSize;				//< Size of a block in a compressed file, in bytes
} FoxEntries, *PFoxEntries;

typedef struct _FoxIndecies
{
	uint64		lnFileSize;		//< Length of a decompressed file in bytes
	uint32		nSize;			//< Size of a table, in bytes, including this structure
	uint32		nSignature;		//< Compressed table signature. "FoxC" is here.
} FoxIndecies, *PFoxIndecies;

#endif
