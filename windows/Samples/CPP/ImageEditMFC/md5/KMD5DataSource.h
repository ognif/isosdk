#ifndef _K_MD5_DATA_SOURCE_H_
#define _K_MD5_DATA_SOURCE_H_


class KMD5DataSource
{
public:	
	struct DataPacket
	{
		void* data;
		unsigned int length;

		DataPacket()
		{
			length = 0;
			data = 0;
		}		
	};	
	virtual bool EndOfData() = 0;
	virtual DataPacket GetNextDataPacket() = 0;
	virtual int GetProgress() = 0;
};



#endif //#ifndef _K_MD5_DATA_SOURCE_H_

