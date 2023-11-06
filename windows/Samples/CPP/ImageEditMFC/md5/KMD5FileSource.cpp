#include "stdafx.h"
#include "KMD5FileSource.h"
#include <sys/stat.h>

const size_t PACKET_SIZE = 1024 * 100; // 100 KB

KMD5FileSource::KMD5FileSource(const KString& strFileName) :	
	m_bEOF(false)
{
	m_pFile = _tfopen(strFileName, _T("rb"));

	____stat64 devStat;
	if (0 == _stat64(strFileName, &devStat))
	{
		m_nFileLength = devStat.st_size;				
	}
	else
	{
		m_nFileLength = 0;
	}
		
	
	m_cPacket.data = new char[PACKET_SIZE];
}

KMD5FileSource::~KMD5FileSource()
{
	delete m_cPacket.data;
}

bool KMD5FileSource::EndOfData()
{
	return m_bEOF;
}

KMD5DataSource::DataPacket KMD5FileSource::GetNextDataPacket()
{	
	m_cPacket.length = (unsigned int) fread(m_cPacket.data, sizeof(char), PACKET_SIZE, m_pFile);
	m_bEOF = m_cPacket.length < PACKET_SIZE;
	return m_cPacket;
}

int KMD5FileSource::GetProgress()
{	
	return (int)(100 * (double)ftell(m_pFile) / m_nFileLength);	
}