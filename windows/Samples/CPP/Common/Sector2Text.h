#ifndef _SECTOR_TO_TEXT_H_
#define _SECTOR_TO_TEXT_H_

#include "IsoSDKDefinitions.h"

#include <vector>

namespace Sector2Text
{
	//Writes out something like 31 -> 001F
	KString int16To4Symbols(int16 n);
	//Writes out something like 15 -> 0F
	KString byteToString(uint8 nByte);

	class IsPrintableTranslator
	{
	public:
		static KString Translate(const std::vector<uint8>& vBytes);
	};
	
	template<class ByteTranslatorClass>
	class SixteenByteLine
	{
	private:		
		std::vector<uint8> m_vBytes;
	public:
		///Reads 16 bytes from pointer. You should now, that pointer s not corrupted;
		SixteenByteLine():m_vBytes(16,0) {}
		SixteenByteLine(const uint8* pData)
			:m_vBytes(16)
		{
			setData(pData);
		}

		void setData(const uint8* pData)
		{
			std::copy(pData, pData + 16, m_vBytes.begin());
		}

		KString getByteString()
		{
			KString res = "";			
			for(int i = 0 ; i < 16; ++i)
			{
				res += byteToString(m_vBytes[i]);
				if(i<15)
				{		
					if(i == 7)
					{
						res += "   " ;
					}
					else
					{
						res += ' ' ;
					}
				}
			}

			return res;
		}
		KString				getHumanReadableString()
		{
			return ByteTranslatorClass::Translate(m_vBytes);
		}

	};//class SixteenByteLine



	template<class ByteTranslatorClass>
	class SectorLines
	{
	private:
		std::vector< SixteenByteLine<ByteTranslatorClass> > m_vLines;
	public:
		SectorLines()
		{
			m_vLines.clear();
		}
		SectorLines(const uint8* pData, const unsigned nSizeOfDataInBytes)
		{
			setData(pData, nSizeOfDataInBytes);			
		}
		~SectorLines()
		{}
		void setData(const uint8* pData, const unsigned nSizeOfDataInBytes)
		{
			const int n = nSizeOfDataInBytes / 16;
			m_vLines.resize(n);
			for(int i = 0 ; i < n; ++i)
			{
				m_vLines[i].setData(pData+16*i);
			}
			if(nSizeOfDataInBytes % 16)
			{
				SixteenByteLine<ByteTranslatorClass> cAdditionalLine;
				uint8* pNewData = new uint8[16];
				memset(pNewData,0,16);
				memcpy(pNewData, pData+16*n,nSizeOfDataInBytes%16);
				cAdditionalLine.setData(pNewData);
				delete[] pNewData;
				m_vLines.push_back(cAdditionalLine);
			}
		}
		std::vector<KString> getLines()
		{
			std::vector<KString> vRes;
			vRes.resize(m_vLines.size());
			for(int i = int(m_vLines.size()-1); i>=0; --i)
			{
									//LBA
				vRes[i] = int16To4Symbols(i*16) + KString("  :  ") 
					+ m_vLines[i].getByteString()+ KString("   ")
					+ m_vLines[i].getHumanReadableString();
			}
			return vRes;
		}
	};
}//namespace Sector2Text





#endif //_SECTOR_TO_TEXT_H_
