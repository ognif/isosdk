#include "stdafx.h"
#include "Sector2Text.h"

#ifndef WIN32
#include <string>
#include <sstream>
#include <iomanip>
#endif

namespace Sector2Text
{

KString int16To4Symbols(int16 n)
{
	return KStringFormat("%.04X", int(n));
}

KString byteToString(uint8 nByte)
{
	return KStringFormat(L"%.02X", (int)nByte);
}

KString IsPrintableTranslator::Translate(const std::vector<uint8> &vBytes)
{
	static const int alphaLower		= int('A');
	static const int alphaUpper		= int('z');
	static const int numberLower	= int('0');
	static const int numberUpper	= int('9');

	KString res(vBytes.size(), L'.');
	for( int i = 0 ; i < (int)vBytes.size(); ++i)
	{	

		if(alphaLower <= vBytes[i] && vBytes[i] <= alphaUpper)
		{
			res.SetAt(i, (char)vBytes[i]);
		}
		else if(numberLower <= vBytes[i] && vBytes[i] <= numberUpper)
		{
			res.SetAt(i, (char)vBytes[i]);
		}
	}
	return res;
}
}
