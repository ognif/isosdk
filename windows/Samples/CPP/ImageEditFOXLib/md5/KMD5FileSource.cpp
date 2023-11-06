#include "stdafx.h"
#include "kmd5filesource.h"
#include <sys/stat.h>

const size_t PACKET_SIZE = 1024 * 100; // 100 KB

KMD5FileSource::KMD5FileSource(const FXString& strFileName) :	
	m_bEOF(false)
{
	m_cFile.open(strFileName, FXFile::Reading);

	m_nFileLength = m_cFile.size();				

	m_cPacket.data = new char[PACKET_SIZE];
}

KMD5FileSource::~KMD5FileSource()
{
	delete (char *)m_cPacket.data;
}

bool KMD5FileSource::EndOfData()
{
	return m_bEOF;
}

KMD5DataSource::DataPacket KMD5FileSource::GetNextDataPacket()
{	
	m_cPacket.length = m_cFile.readBlock(m_cPacket.data, PACKET_SIZE);
	m_bEOF = m_cPacket.length < PACKET_SIZE;
	return m_cPacket;
}

int KMD5FileSource::GetProgress()
{	
	return (int)(100 * (double)m_cFile.position() / m_nFileLength);	
}
