#pragma once

#include "tchar.h"

typedef unsigned int TelUint32;
typedef unsigned char TelByte;
typedef bool TelBool;
typedef TelUint32 TelError;


#	ifdef __cplusplus
extern "C" {
#	endif


#ifdef _MSC_VER
#	define TEL_CALL		__stdcall
#elif /* defined MAC || */ defined LINUX
#	define TEL_CALL		__attribute__((visibility("default")))
#else
#	define TEL_CALL
#endif

const wchar_t * TEL_CALL TelGetVidGenreName(int i);
const wchar_t * TEL_CALL TelGetGenreName(int i);
const TelUint32 TEL_CALL TelGetGenreCount();
const TelUint32 TEL_CALL TelGetVidGenreCount();

/************************************************************************/
/* General part: type and macro definitions                             */
/************************************************************************/

#define TEL_INVALID_HANDLE (-1)

#define		TEL_ERR_OK							0	//No errors
#define		TEL_ERR_HANDLE						1	//TelBuffer or TelEncoder Handle is incorrect
#define		TEL_ERR_PARAM						2
#define		TEL_ERR_MOREMEMMORY					3
#define		TEL_ERR_INTERNAL					4
#define		TEL_ERR_CANT_OPEN_FILE				5
#define		TEL_ERR_UNKNOWN_FORMAT				6
#define		TEL_ERR_UNIMPLEMENTED				7
#define		TEL_ERR_UNKNOWN_PLAYLIST_FORMAT		8
#define		TEL_ERR_BAD_PLAYLIST				9
#define		TEL_ERR_BAD_STAGS_STRUCTURE			10
#define		TEL_ERR_BAD_PROJECT_DIR				11
#define		TEL_ERR_CANT_WRITE_FILE				12
#define		TEL_ERR_TOO_BIG_PLAYLIST			13
#define		TEL_ERR_TOO_BIG_PROJECT				14
#define		TEL_ERR_FILE_ALLREADY_EXISTS		15
#define		TEL_ERR_WRITE_ARTWORK				16
#define		TEL_ERR_ENCODING					17	//Error during encoding. See log file for more information


#define LIBRARY_PREFIX Tel // Tagging and Encoding Library

/************************************************************************/
/*  Encoding part                                                       */
/************************************************************************/
enum TelEncoderType
{
	ET_MP3,
	ET_WMA,
	ET_AAC,
	ET_OGG,
	ET_MP4,
	ET_FLAC,
	ET_OPUS,
};

/*
BASSenc_MP3
BASSenc_FLAC
BASSenc_OGG
BASSenc_OPUS
BASSenc_AAC
*/

enum TelBitrateType
{
	BT_VARIABLE,
	BT_CONSTANT,
	BT_AVERAGE,
};

struct TelEncodingSettings
{
    TelUint32 bitrate;
	TelUint32 minBitrate;
	TelUint32 maxBitrate;
	TelUint32 quality;
	TelBitrateType bitrateType;
};


/************************************************************************/
/* Buffer part                                                          */
/************************************************************************/

typedef int TelBufferHandle;

// Create object
TelBufferHandle TEL_CALL TelBufferAllocate(TelUint32 size);
// Delete the object
TelError TEL_CALL TelBufferFree(TelBufferHandle hBuffer);
// Put data into buffer
TelError TEL_CALL TelBufferPut(TelBufferHandle hBuffer, const TelByte* buffer, TelUint32 size);
// Put values into buffer
TelError TEL_CALL TelBufferPutValue(TelBufferHandle hBuffer, TelByte nValue, TelUint32 nAmount);
// Get values from buffer
TelError TEL_CALL TelBufferGet(TelBufferHandle hBuffer, TelByte* buffer, TelUint32 size, bool bWaitFullSize = true);
// Begin reset
TelError TEL_CALL TelBufferBeginReset(TelBufferHandle hBuffer);
// End Reset
TelError TEL_CALL TelBufferEndReset(TelBufferHandle hBuffer);
// Get free space
TelError TEL_CALL TelBufferGetFreeSpace(TelBufferHandle hBuffer, TelUint32 *pFreeSpace);
// Get used size
TelError TEL_CALL TelBufferGetUsedSpace(TelBufferHandle hBuffer, TelUint32 *pUsedSpace);
// Finilize
TelError TEL_CALL TelBufferFinilize(TelBufferHandle hBuffer);
// 
TelError TEL_CALL TelBufferGetTransferedData(TelBufferHandle hBuffer, TelUint32 *pTransferedData);


/************************************************************************/
/* Encoder part                                                         */
/************************************************************************/


// Handle of encoder.
typedef int TelEncoderHandle;

// create encoder
TelEncoderHandle TEL_CALL TelEncoderCreate(TelEncoderType type, TelEncodingSettings settings);
// free encoder
TelError TEL_CALL TelEncoderFree(TelEncoderHandle hEncoder);
// main encoder function
TelError TEL_CALL TelEncoderSave(TelEncoderHandle hEncoder, const TCHAR* path, 
						TelBufferHandle hBuffer);

TelError TEL_CALL TelEncoderBitrateType(TelEncoderHandle hEncoder, TelBitrateType *BitrateType);
TelError TEL_CALL TelEncoderBitrate(TelEncoderHandle hEncoder, TelUint32 *pValue);
TelError TEL_CALL TelEncoderMinBitrate(TelEncoderHandle hEncoder, TelUint32 *pValue);
TelError TEL_CALL TelEncoderMaxBitrate(TelEncoderHandle hEncoder, TelUint32 *pValue);



/************************************************************************/
/* Tagging part                                                        */
/************************************************************************/


enum TelFileInfo
{
	FINFO_BITRATE = 0,
	FINFO_DURATION,
	FINFO_FILE_SIZE,
	FINFO_PROTECTED,
	FINFO_VBR,
	FINFO_ENCODED_BY,
	FINFO_CODEC,
	FINFO_STRIDABLE,
	FINFO_SEEKABLE,
	FINFO_FRAMES,
	FINFO_CHANNELS,
	FINFO_COPYRIGHTED,
	FINFO_CRC,
	FINFO_FRAME_SIZE,
	FINFO_SAMPLE_RATE,
	FINFO_MPEG_LAYER,
	FINFO_ORIGINAL,
	FINFO_PRIVATE_BIT,
	FINFO_AVG_VBR,
	FINFO_MPEG_VERSION,
	FINFO_BITS_PER_SAMPLE,
	FINFO_LAST
};

enum TelMp4TagField
{
	TAG_MP4_ADDITIONAL_TEXT = 1,
	TAG_MP4_COLLECTION = 2,
	TAG_MP4_TOOL = 3
};

enum TelTagField
{
	TAG_INVALID = 0,

	TAG_START = 1,

	TAG_ID3V1_START = 1,
	TAG_TITLE = 1,
	TAG_ARTIST = 2,
	TAG_ALBUM = 3,
	TAG_GENRE = 4,
	TAG_COMMENT = 5,
	TAG_TRACK = 6,
	TAG_YEAR = 7,
	TAG_ID3V1_FIN = 8,

	TAG_ID3V2_START	= 9,
	TAG_TITLE_2	= 9,
	TAG_ARTIST_2 = 10,
	TAG_ALBUM_2	= 11,
	TAG_GENRE_2	= 12,
	TAG_COMMENT_2 = 13,
	TAG_TRACK_2	= 14,
	TAG_YEAR_2	= 15,

	TAG_ID3V2_ADDITIONAL_TAGS_START = 16,
	TAG_PUBLISHER = 16,
	TAG_ORIGARTIST = 17,
	TAG_COPYRIGHT = 18,
	TAG_DISC = 19,
	TAG_URL	= 20,
	TAG_COMPOSER = 21,
	TAG_BPM	= 22,
	TAG_ENCODED_BY = 23,
	TAG_ALBUM_ARTIST = 24,
	TAG_RATING = 25,
	TAG_ID3V2_FIN = 26,

	TAG_FIN	= 26
};


enum TelPictureFormat
{
	PICT_FORMAT_BMP,
	PICT_FORMAT_JPG,
	PICT_FORMAT_GIF,
	PICT_FORMAT_PNG,
	PICT_FORMAT_UNKNOWN
};

		


// Handle of encoder.
typedef int TelTagsHandle;

TelTagsHandle TEL_CALL TelTagsCreateContainer(void);
TelError TEL_CALL TelTagsReadFromFile(TelTagsHandle hContainer, const TCHAR *path);
TelError TEL_CALL TelTagsModifyToFile(TelTagsHandle hContainer, const TCHAR *path);
TelError TEL_CALL TelTagsWriteToFile(TelTagsHandle hContainer, const TCHAR *path);
TelError TEL_CALL TelTagsDeleteContainer(TelTagsHandle hContainer);

TelError TEL_CALL TelTagsHasID3V1(TelTagsHandle hContainer, TelBool *pValue);
TelError TEL_CALL TelTagsHasID3V2(TelTagsHandle hContainer, TelBool *pValue);

TelError TEL_CALL TelTagsSetHasID3V1(TelTagsHandle hContainer, TelBool bHas);
TelError TEL_CALL TelTagsSetHasID3V2(TelTagsHandle hContainer, TelBool bHas);

TelError TEL_CALL TelTagsSetID3VXFlags(TelTagsHandle hContainer);
TelError TEL_CALL TelTagsCopyID3v1ToID3v2(TelTagsHandle hContainer);
TelError TEL_CALL TelTagsCopyID3v2ToID3v1(TelTagsHandle hContainer);

TelError TEL_CALL TelTagsGetTag(TelTagsHandle hContainer, TelTagField eField, TCHAR *pText, TelUint32 *pLength);
TelError TEL_CALL TelMp4TagsGetTag(TelTagsHandle hContainer, TelMp4TagField eField, TCHAR *pText, TelUint32 *pLength);
TelError TEL_CALL TelTagsSetTag(TelTagsHandle hContainer, TelTagField eField, const TCHAR *pText);
TelError TEL_CALL TelMp4TagsSetTag(TelTagsHandle hContainer, TelMp4TagField eField, const TCHAR *pText);
TelError TEL_CALL TelTagsClearContent(TelTagsHandle hContainer);

TelError TEL_CALL TelTagsGetFileName(TelTagsHandle hContainer, TCHAR *pText, TelUint32 *pLength);
TelError TEL_CALL TelTagsGetFileAttribute(TelTagsHandle hContainer, TelFileInfo eKey, TCHAR *pText, TelUint32 *pLength);

TelError TEL_CALL TelTagsGetPicturesCount(TelTagsHandle hContainer, TelUint32 *pCount);
TelError TEL_CALL TelTagsGetPicture(TelTagsHandle hContainer, TelUint32 nPictureIndex, TelByte* pData, TelUint32 *pDataSize);
TelError TEL_CALL TelTagsAddPictureFromFile(TelTagsHandle hContainer, const TCHAR *path);
TelError TEL_CALL TelTagsAddPictureFromData(TelTagsHandle hContainer, const char *pData, unsigned long nDataLength);
TelError TEL_CALL TelTagsDeletePicture(TelTagsHandle hContainer, TelUint32 nPictureIndex);
TelError TEL_CALL TelTagsSavePictureToFile(TelTagsHandle hContainer, TelUint32 nPictureIndex, const TCHAR *path);
TelError TEL_CALL TelTagsSaveMemPicture(const char *pData, unsigned long nDataSize, const TCHAR *path);
TelError TEL_CALL TelTagsGetPictureFormat(TelTagsHandle hContainer, TelUint32 nPictureIndex, TelPictureFormat *pFormat);

TelTagsHandle TEL_CALL TelTagsMakeTagsContentUnion(TelTagsHandle hContainerV1,
										  TelTagsHandle hContainerV2,
										  TelTagsHandle hContainerAW);

#	ifdef __cplusplus
}
#	endif
