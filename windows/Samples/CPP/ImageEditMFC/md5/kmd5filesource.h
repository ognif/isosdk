#ifndef _K_MD5_FILE_SOURCE_H_
#define _K_MD5_FILE_SOURCE_H_

#include "KMD5DataSource.h"


class KMD5FileSource : public KMD5DataSource
{
	private:
		FILE *m_pFile;
		bool m_bEOF;
		int64 m_nFileLength;
		KMD5DataSource::DataPacket m_cPacket;
	public:
		KMD5FileSource(const KString& strFileName);		
		~KMD5FileSource();		
		virtual bool EndOfData();
		virtual DataPacket GetNextDataPacket();
		virtual int GetProgress();
};

#endif //#ifndef _K_MD5_FILE_SOURCE_H_

