/*****************************************************
* Project: IsoSDK
* Version: 1.0
* File Name: KString.cpp
* Programmer Name: Roman Kudinov
* Date of create: 22\07\2003
* Description: 
* Language VC 7.1			Target: Win32
* Require:
* --------------------------------- HISTORY ------------------------------
History: 
22\07\2003  - Created
******************************************************/

#include "KString.h"
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cstdarg>
#include <cstring>
#include <wchar.h>
# include <wctype.h>

#if _MSC_VER >= 1400
	#ifdef _SECURE_SCL
		#undef _SECURE_SCL
	#endif
	#define _SECURE_SCL 0
#endif

#include <algorithm>

typedef KString::index_t index_t;

const size_t FORMAT_BUFFER_SIZE = 32000;

KString::KString() :
	m_szTempString(NULL),
	m_wszString(NULL),
	m_dwLen(1)
{	
}

KString::KString(const char *szString) :
	m_szTempString(NULL),
	m_wszString(NULL),
	m_dwLen(1)
{
	set(szString);
}

KString::KString(const wchar_t *wszString) :
	m_szTempString(NULL),
	m_wszString(NULL),
	m_dwLen(1)
{
	set(wszString);
}

KString::KString(const KString &String) :
	m_szTempString(NULL),
	m_wszString(NULL),
	m_dwLen(1)
{
	set(String);
}

KString::KString(char Char) :
	m_szTempString(NULL),
	m_wszString(NULL),
	m_dwLen(1)
{
	set(Char);
}

KString::KString(wchar_t wChar) :
	m_szTempString(NULL),
	m_wszString(NULL),
	m_dwLen(1)
{
	set(wChar);
}

KString::KString(size_t nLength, wchar_t wChar)
	:m_szTempString(NULL)
	,m_wszString(new wchar_t[nLength + 1])
	,m_dwLen(nLength + 1)
{
	std::fill(m_wszString, m_wszString + nLength, wChar);
	m_wszString[nLength] = L'\0';
}

KString::KString(const char* pChar, size_t nLength)
	:m_szTempString(new char[nLength+1])
	,m_wszString(NULL)
	,m_dwLen(1)
{
	memcpy(m_szTempString, pChar, nLength);
	m_szTempString[nLength] = '\0';

	set(m_szTempString);
}

void KString::set(const KString &String)
{
	if (m_wszString == String.m_wszString)
		return;

	delete [] m_wszString;
	m_wszString = 0;

	if (String.m_wszString == NULL)
	{
		m_wszString = NULL;
		m_dwLen = 1;
		return;
	}

	m_dwLen = String.m_dwLen;
	m_wszString = new wchar_t[m_dwLen];
	wcscpy(m_wszString, String.m_wszString);
}

void KString::set(const char *szString)
{
	delete [] m_wszString;
	m_wszString = 0;

	if(!szString)
	{
		m_wszString = NULL;
		m_dwLen = 1;

		return;
	}
	
	m_dwLen = mbstowcs(NULL, szString, 0) + 1;		
	if (0 != m_dwLen)
	{		
		m_wszString = new wchar_t[m_dwLen];		
		mbstowcs(m_wszString, szString, m_dwLen);
	}
	else
	{
		m_wszString = NULL;		
		m_dwLen = 1;		
	}
}

void KString::set(const wchar_t *wszString)
{
	if(m_wszString)
	{
		delete [] m_wszString;
		m_wszString = 0;
	}

	if(!wszString)
	{
		m_wszString = NULL;
		m_dwLen = 1;

		return;
	}

	m_dwLen = wcslen(wszString) + 1;
	m_wszString = new wchar_t[m_dwLen];
	wcscpy(m_wszString, wszString);
}

void KString::set(char Char)
{
	if(m_wszString)
	{
		delete [] m_wszString;
		m_wszString = 0;
	}

	wchar_t wc;
	
	if (-1 != mbtowc(&wc, &Char, 1))
	{
		m_dwLen = 2;
		m_wszString = new wchar_t[m_dwLen];
		m_wszString[0] = wc;
		m_wszString[1] = 0;
	}
	else
	{
		m_wszString = NULL;
		m_dwLen = 1;
	}
}

void KString::set(wchar_t wChar)
{
	if(m_wszString)
	{
		delete [] m_wszString;
		m_wszString = 0;
	}
	m_dwLen = 2;
	m_wszString = new wchar_t[m_dwLen];
	m_wszString[0] = wChar;
	m_wszString[1] = 0;
}

KString::~KString()
{
	delete [] m_wszString;
	m_wszString = 0;

	delete [] m_szTempString;
	m_szTempString = 0;
}

void KString::Empty()
{
	delete [] m_wszString;
	m_wszString = NULL;

	delete [] m_szTempString;
	m_szTempString = 0;

	m_dwLen = 1;
}

const KString &KString::operator =(const KString &String)
{
	set(String);
	return *this;
}

const KString &KString::operator =(const char *szString)
{
	set(szString);
	return *this;
}

const KString &KString::operator =(const wchar_t *wszString)
{
	set(wszString);
	return *this;
}

const KString &KString::operator =(char Char)
{
	set(Char);
	return *this;
}

const KString &KString::operator =(wchar_t wChar)
{
	set(wChar);
	return *this;
}

const KString &KString::operator +=(const KString &String)
{
	if(!String.m_wszString)
	{
		return *this;
	}

	m_dwLen += String.m_dwLen - 1;

	wchar_t *wszTempString = new wchar_t[m_dwLen];
	
	if(m_wszString)
		wcscpy(wszTempString, m_wszString);			
	else
		wcscpy(wszTempString, L"");					

	wcscat(wszTempString, String.m_wszString);		

	if(m_wszString)
	{
		delete [] m_wszString;
	}

	m_wszString = wszTempString;

	return *this;
}

const KString &KString::operator +=(const char *szString)
{
	if(!szString)
	{
		return *this;
	}
	
	size_t dwLen = mbstowcs(NULL, szString, 0);
	
	if (-1 == dwLen || 0 == dwLen)
	{
		return *this;
	}

	size_t dwNewLen = m_dwLen + dwLen;

	wchar_t *wszTempString = new wchar_t[dwNewLen];

	if(m_wszString)
	{
		wcscpy(wszTempString, m_wszString);			//Copy old string
	}
	else
	{
		wcscpy(wszTempString, L"");					//Copy old string
	}
	
	mbstowcs(wszTempString + m_dwLen - 1, szString, dwLen + 1);

	if(m_wszString)
	{
		delete [] m_wszString;
	}

	m_wszString = wszTempString;
	m_dwLen = dwNewLen;

	return *this;
}

const KString &KString::operator +=(const wchar_t *wszString)
{
	if(!wszString)
	{
		return *this;
	}

	size_t dwNewLen = m_dwLen + wcslen(wszString);	

	wchar_t *wszTempString = new wchar_t[dwNewLen];
	
	if(m_wszString)
	{
		wcscpy(wszTempString, m_wszString);			
	}
	else
	{
		wcscpy(wszTempString, L"");					
	}

	wcscat(wszTempString, wszString);

	if(m_wszString)
	{
		delete [] m_wszString;
	}

	m_wszString = wszTempString;
	m_dwLen = dwNewLen;

	return *this;
}

const KString &KString::operator +=(const char Char)
{
	if (-1 == mbtowc(NULL, &Char, 1))
		return *this;

	size_t dwNewLen = m_dwLen + 1;

	wchar_t *wszTempString = new wchar_t[dwNewLen];

	if(m_wszString)
	{
		wcscpy(wszTempString, m_wszString);			
	}
	else
	{
		wcscpy(wszTempString, L"");					
	}

	mbtowc(wszTempString + m_dwLen - 1, &Char, 1);
	wszTempString[m_dwLen] = 0;

	if(m_wszString)
	{
		delete [] m_wszString;
	}
	
	m_wszString = wszTempString;
	m_dwLen = dwNewLen;

	return *this;
}

const KString &KString::operator +=(const wchar_t wChar)
{
	size_t dwNewLen = m_dwLen + 1;
	
	wchar_t *wszTempString = new wchar_t[dwNewLen];
	
	if(m_wszString)
	{
		wcscpy(wszTempString, m_wszString);			
	}
	else
	{
		wcscpy(wszTempString, L"");					
	}
	
	wszTempString[m_dwLen - 1] = wChar;
	wszTempString[m_dwLen] = 0;

	if(m_wszString)
	{
		delete [] m_wszString;
	}

	m_wszString = wszTempString;
	m_dwLen = dwNewLen;

	return *this;
}

bool KString::operator <(const KString &String) const
{
	if(!String.m_wszString)
		return false;

	if(!m_wszString)
	{
		if (0 == wcslen(String.m_wszString))
			return false;

		return true;
	}

	return (0 > wcscmp(m_wszString, String.m_wszString));
}

bool KString::operator <(const char *szString) const
{
	if(!szString)
		return false;
	
	size_t mblen = mbstowcs(NULL, szString, 0);

	if(!m_wszString)
	{
		
		if (-1 == mblen || 0 == mblen)
			return false;

		return true;
	}
	
	wchar_t *wszTempString = new wchar_t[mblen + 1];
	
	mbstowcs(wszTempString, szString, mblen + 1);

	int res = wcscmp(m_wszString, wszTempString);
	
	delete [] wszTempString;

	return (res < 0);
}

bool KString::operator <(const wchar_t *wszString) const
{
	if(!wszString)
		return false;

	if(!m_wszString)
	{
		if (0 == wcslen(wszString))
			return false;

		return true;
	}

	return (0 > wcscmp(m_wszString, wszString));
}

bool KString::operator >(const KString &String) const
{
	if(!m_wszString)
		return false;

	if(!String.m_wszString)
	{
		if (0 == wcslen(m_wszString))
			return false;

		return true;
	}

	return (0 < wcscmp(m_wszString, String.m_wszString));
}

bool KString::operator >(const char *szString) const
{
	if(!m_wszString)
		return false;
    
	if(!szString)
	{
		if (0 == wcslen(m_wszString))
			return false;

		return true;
	}

	size_t mblen = mbstowcs(NULL, szString, 0);

	if (-1 == mblen)
		return false;
	
	wchar_t *wszTempString = new wchar_t[mblen+1];
	mbstowcs(wszTempString, szString, mblen+1);
	
	int res = wcscmp(m_wszString, wszTempString);	
	
	delete [] wszTempString;

	return (res > 0);
}

bool KString::operator >(const wchar_t *wszString) const
{
	if(!m_wszString)
		return false;

	if(!wszString)
	{
		if (0 == wcslen(m_wszString))	
			return false;

		return true;
	}

	return (0 < wcscmp(m_wszString, wszString));
}

bool KString::operator ==(const KString &String) const
{
	if(!m_wszString)
	{
		if(!String.m_wszString)
			return true;
		
		if (0 == wcslen(String.m_wszString))
			return true;

		return false;
	}

	if(!String.m_wszString)
	{
		if (0 == wcslen(m_wszString))
			return true;

		return false;
	}

	return  (0 == wcscmp(m_wszString, String.m_wszString));
}

bool KString::operator ==(const char *szString) const
{
	if(!szString)
	{
		if(!m_wszString)
			return true;

		if (0 == wcslen(m_wszString))
			return true;

		return false;
	}

	size_t mblen = mbstowcs(NULL, szString, 0);

	if(!m_wszString)
	{		
		if (-1 == mblen)
			return false;

		if (0 == mblen)
			return true;

		return false;
	}
	
	if (mblen == -1)
		return false;
	
	wchar_t *wszTempString = new wchar_t[mblen + 1];
	mbstowcs(wszTempString, szString, mblen + 1);

	int res = wcscmp(m_wszString, wszTempString);
	
	delete [] wszTempString;

	return (res == 0);
}

bool KString::operator ==(char Char) const
{
	if (!m_wszString)
		return false;

	wchar_t buf[2] = {0,};
	
	if (-1 == mbtowc(buf, &Char, 1))
		return false;

	return (0 == wcscmp(buf, m_wszString));
}

bool KString::operator!=(char Char) const
{
	return !(*this == Char);
}

bool KString::operator ==(const wchar_t *wszString) const
{
	if(!m_wszString)
	{
		if(!wszString)
			return true;

		if (wcslen(wszString) == 0)
			return true;

		return false;
	}

	if(!wszString)
	{
		if (wcslen(m_wszString) == 0)
			return true;

		return false;
	}

	int res = wcscmp(m_wszString, wszString);
	
	return (res == 0);
}

bool KString::operator ==(wchar_t wChar) const
{
	if (!m_wszString)
		return false;
	
	wchar_t	buf[2] = {0, };
	buf[0] = wChar;

	int res = wcscmp(m_wszString, buf);
	
	return (res == 0);
}

bool KString::operator !=(wchar_t wChar) const
{
	return !(*this == wChar);
}

bool KString::operator !=(const KString &String) const
{
	return !(*this == String);
}

bool KString::operator !=(const char *szString) const
{
	return !(*this == szString);
}

bool KString::operator !=(const wchar_t *wszString) const
{
	return !(*this == wszString);
}

KString operator+( const KString& str1, const KString& str2 )
{
	KString strResult( str1 );

	strResult += str2;

	return( strResult );
}

KString operator+( const KString& str1, wchar_t *psz2 )
{
	KString strResult( str1 );

	strResult += psz2;

	return( strResult );
}

KString operator+( wchar_t *psz1, const KString& str2 )
{
	KString strResult( psz1 );

	strResult += str2;

	return( strResult );
}

KString operator+( const KString& str1, wchar_t ch2 )
{
	KString strResult( str1 );

	strResult += ch2;

	return( strResult );
}

KString operator+( const KString& str1, char ch2 )
{
	KString strResult( str1 );

	strResult += ch2;

	return( strResult );
}

KString operator+( wchar_t ch1, const KString& str2 )
{
	KString strResult( ch1 );

	strResult += str2;

	return( strResult );
}

KString operator+( char ch1, const KString& str2 )
{
	KString strResult( ch1 );

	strResult += str2;

	return( strResult );
}


KString::operator const char*() const
{
	delete [] m_szTempString;

	size_t mblen = 0;
	
	if (m_wszString)
		mblen = wcstombs(NULL, m_wszString, 0);

	if (-1 != mblen && 0 != mblen)
	{
		m_szTempString = new char[mblen + 1];		
		wcstombs(m_szTempString, m_wszString, mblen + 1);
	}
	else
	{
		m_szTempString = new char[1];
		m_szTempString[0] = 0;
	}

	return m_szTempString;
}

KString::operator const wchar_t*() const
{
	if (!m_wszString)
	{
		delete [] m_szTempString;
		m_szTempString = (char*)(new wchar_t[1]);
		((wchar_t*)m_szTempString)[0] = 0;
		return (wchar_t*)m_szTempString;
	}
	else
	{
		return m_wszString;
	}
}

TCHAR KString::operator [](index_t nIndex) const
{
	return GetAt(nIndex);
}

TCHAR KString::GetAt( index_t iChar ) const
{
	if(!m_wszString)
	{
		return (TCHAR)0;
	}

	if( (size_t)iChar > m_dwLen - 2)
	{
		iChar = index_t(m_dwLen - 2);
	}
	
#if !defined(_UNICODE) && !defined(UNICODE)
	char buf [6] = {0,};
    wctomb(buf, m_wszString[iChar]);
	return buf[0];
#else
	return m_wszString[iChar];	
#endif	
}

TCHAR KString::GetAtReverse(index_t iChar ) const
{
	if(iChar > index_t(m_dwLen - 2)) {
		return TCHAR(0);
	}

    return GetAt(index_t(m_dwLen - 2 - iChar));
}

void KString::SetAt( index_t iChar, TCHAR tSym )
{
	assert(tSym != _T('\0'));

	if( !m_wszString)
		return;

	if( (size_t)iChar > (m_dwLen - 2) )
	{
		iChar = index_t(m_dwLen - 2);
	}
#if !defined(_UNICODE) && !defined(UNICODE)
	mbtowc(m_wszString + iChar, &tSym, 1);		
#else
	m_wszString[iChar] = tSym;
#endif
}

int uppercompare(const wchar_t * dst,
				 const wchar_t * src)
{
	wchar_t	f,l;

	do
	{
		f = towupper( *dst++ );
		l = towupper( *src++ );
	} while ( (f) && (f == l) );
	return int(f-l);
}

int KString::CompareNoCase(const KString &String) const
{
	if(!m_wszString)
	{
		if(!String.m_wszString)
			return 0;

		if (0 == wcslen(String.m_wszString))
			return 0;
		
		return -1;
	}

	if(!String.m_wszString)
	{
		return 1;		//The cur string is bigger
	}
	return uppercompare(m_wszString, String.m_wszString);
}

int KString::CompareNoCase(const char *szString) const
{
	KString	strArg(szString);
	return	CompareNoCase(strArg);
}

int KString::CompareNoCase(const wchar_t *wszString) const
{
	KString	strArg(wszString);
	return CompareNoCase(strArg);
}

size_t KString::GetLength() const
{
	return m_dwLen - 1;
}

void KString::SetLength( size_t nLength )
{
	assert( nLength <= m_dwLen - 1 );

	if( nLength > m_dwLen - 1)
		return;
		
	m_dwLen = nLength + 1;
	m_wszString[nLength] = 0;
}


TCHAR *KString::GetBuffer( size_t nMinBufferLength )
{
	if (nMinBufferLength + 1 > m_dwLen)
	{
		m_dwLen = nMinBufferLength + 1;
		wchar_t *wszTemp = new wchar_t[m_dwLen];
		
		if(m_wszString)
		{
			wcscpy(wszTemp, m_wszString);
			delete [] m_wszString;			
		}
		else
		{
			wszTemp[0] = 0;
		}

		m_wszString = wszTemp;
	}

	if(m_szTempString)
	{
		delete [] m_szTempString;
	}

	m_szTempString = (char*)(new TCHAR[m_dwLen]);
	memset(m_szTempString, 0, m_dwLen * sizeof(TCHAR));

#if !defined(UNICODE) && !defined(_UNICODE)
	wcstombs(m_szTempString, m_wszString, m_dwLen);
#else
	wcsncpy((wchar_t*)m_szTempString, m_wszString, m_dwLen);
#endif

	return (TCHAR*)m_szTempString;
}

void KString::ReleaseBuffer()
{
	if(m_wszString)
	{
		delete [] m_wszString;		
	}

#if !defined(UNICODE) && !defined(_UNICODE)
	size_t mblen = mbstowcs(0, m_szTempString, 0);
	if (-1 != mblen) {
		m_dwLen = mblen + 1;
		m_wszString = new wchar_t[m_dwLen];
		mbstowcs(m_wszString, m_szTempString, m_dwLen);
	}
	else {
		m_dwLen = 1;
		m_wszString = NULL;
	}	
#else
	m_dwLen = wcslen((TCHAR*)m_szTempString) + 1;
	m_wszString = new wchar_t[m_dwLen];
	wcsncpy(m_wszString, (wchar_t*)m_szTempString, m_dwLen);
#endif
}

bool KString::IsEmpty() const throw()
{
	return( GetLength() == 0 );
}

void KString::Truncate( size_t nNewLength )
{
	assert( nNewLength <= GetLength() );
	SetLength( nNewLength );
}

// Delete 'nCount' characters, starting at index 'iIndex'
size_t KString::Delete( index_t iIndex, size_t nCount )
{
	if( iIndex < 0 )
		iIndex = 0;
	
    size_t nLength = GetLength();

	if (iIndex >= index_t(nLength))
		return nLength;

	if( (iIndex+nCount) > nLength )
	{
		nCount = nLength-iIndex;
	}
	if( nCount > 0 )
	{
		size_t nNewLength = nLength-nCount;
		size_t nXCHARsToCopy = nLength-(iIndex+nCount)+1;
		wchar_t *pszBuffer = m_wszString;
		memmove( pszBuffer+iIndex, pszBuffer+iIndex+nCount, nXCHARsToCopy*sizeof( wchar_t ) );
		SetLength( nNewLength );
	}

	return( GetLength() );
}

// Remove all trailing whitespace
KString& KString::TrimRight()
{
	// find beginning of trailing spaces by starting
	// at beginning (DBCS aware)

	wchar_t * psz = m_wszString;
	wchar_t * pszLast = NULL;

	while( *psz != 0 )
	{
		if( iswspace( *psz ) )
		{
			if( pszLast == NULL )
				pszLast = psz;
		}
		else
		{
			pszLast = NULL;
		}
		psz = psz+1;
	}

	if( pszLast != NULL )
	{
		// truncate at trailing space start
		size_t iLast = pszLast-m_wszString;

		Truncate( iLast );
	}

	return( *this );
}

// Remove all leading whitespace
KString& KString::TrimLeft()
{
	// find first non-space character

	wchar_t * psz = m_wszString;

	while( iswspace( *psz ) )
	{
		psz = psz + 1;
	}

	if( psz != m_wszString )
	{
		// fix up data and length
		size_t iFirst = psz - m_wszString;
		wchar_t *pszBuffer = m_wszString;
		psz = pszBuffer+iFirst;
		size_t nDataLength = GetLength() - iFirst;
		memmove( pszBuffer, psz, (nDataLength+1)*sizeof( wchar_t ) );
		SetLength( nDataLength );
	}

	return( *this );
}

// Remove all leading and trailing whitespace
KString& KString::Trim()
{
	return( TrimRight().TrimLeft() );
}

// Remove all leading and trailing occurrences of character 'chTarget'
KString& KString::Trim( wchar_t chTarget )
{
	return( TrimRight( chTarget ).TrimLeft( chTarget ) );
}

// Remove all trailing occurrences of character 'chTarget'
KString& KString::TrimRight( wchar_t chTarget )
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)

	wchar_t * psz = m_wszString;
	wchar_t * pszLast = NULL;

	while( *psz != 0 )
	{
		if( *psz == chTarget )
		{
			if( pszLast == NULL )
			{
				pszLast = psz;
			}
		}
		else
		{
			pszLast = NULL;
		}
		psz = psz + 1;
	}

	if( pszLast != NULL )
	{
		// truncate at left-most matching character  
		size_t iLast = pszLast-m_wszString;
		Truncate( iLast );
	}

	return( *this );
}

// Remove all leading occurrences of character 'chTarget'
KString& KString::TrimLeft( wchar_t chTarget )
{
	// find first non-matching character
	wchar_t * psz = m_wszString;

	while( chTarget == *psz )
	{
		psz = psz + 1;
	}

	if( psz != m_wszString )
	{
		// fix up data and length
		size_t iFirst = psz-m_wszString;
		wchar_t *pszBuffer = m_wszString;
		psz = pszBuffer+iFirst;
		size_t nDataLength = GetLength()-iFirst;
		memmove( pszBuffer, psz, (nDataLength+1)*sizeof( wchar_t ) );
		SetLength( nDataLength );
	}

	return( *this );
}

KString KString::Left(size_t nAmount) const
{
	if(!m_wszString)
	{
		return( *this );
	}

	if(nAmount >= m_dwLen - 1)
	{
		return( *this );
	}

	KString strResult(*this);

	strResult.m_wszString[nAmount] = 0;
	strResult.m_dwLen = nAmount + 1;

	return( strResult );
}

KString KString::Right(size_t nAmount) const
{
	if(!m_wszString)
	{
		return( *this );
	}

	if((size_t)nAmount >= m_dwLen - 1)
	{
		return( *this );
	}
	
	wchar_t *rightPart = m_wszString + m_dwLen - 1 - nAmount;   
	return KString(rightPart);
}


void KString::KeepLeft(int nAmount)
{
	if(!m_wszString)
	{
		return;
	}

	if((size_t)nAmount >= m_dwLen - 1)
	{
		return;
	}
	m_wszString[nAmount] = 0;
	m_dwLen = nAmount + 1;
}

void KString::KeepRight(int nAmount)
{
	if(!m_wszString)
	{
		return;
	}

	if((size_t)nAmount >= m_dwLen - 1)
	{
		return;
	}

	memmove(m_wszString, m_wszString + m_dwLen - nAmount - 1, (nAmount + 1) * sizeof(wchar_t));
	m_dwLen = nAmount + 1;
}

// Return the substring starting at index 'iFirst'
KString KString::Mid( index_t iFirst ) const
{
	return( Mid( iFirst, GetLength()-iFirst ) );
}

// Return the substring starting at index 'iFirst', with length 'nCount'
KString KString::Mid( index_t iFirst, size_t nCount ) const
{
	// nCount is in wchar_ts

	// out-of-bounds requests return sensible things
	if (iFirst < 0)
		iFirst = 0;
	if (nCount < 0)
		nCount = 0;

	if( (iFirst+nCount) > GetLength() )
	{
		nCount = GetLength()-iFirst;
	}
	if( iFirst > index_t(GetLength()) )
	{
		nCount = 0;
	}

	assert( (nCount == 0) || ((iFirst+nCount) <= GetLength()) );

	// optimize case of returning entire string
	if( (iFirst == 0) && ((iFirst+nCount) == GetLength()) )
	{
		return( *this );
	}

	KString strResult(m_wszString+iFirst);
	strResult.SetLength(nCount);

	return strResult;
}

KString &KString::MakeUpper()
{
	if(!m_wszString)
	{
		return *this;
	}

	std::transform(m_wszString, m_wszString + m_dwLen-1, m_wszString, towupper);

	return( *this );
}

KString &KString::MakeLower()
{
	if(!m_wszString)
	{
		return *this;
	}

	std::transform(m_wszString, m_wszString + m_dwLen-1, m_wszString, towlower);

	return( *this );
}

KString KString::MakeUpperCopy() const
{
	KString res = *this;
	res.MakeUpper();
	return res;
}

index_t KString::Find( const char *szSub ) const
{
	return Find(szSub, 0);
}

index_t KString::Find( const wchar_t *wszSub ) const
{
	return Find(wszSub, 0);
}

index_t KString::Find( char ch, index_t nStart) const
{
	wchar_t wch;
	mbstowcs(&wch, &ch, 1);
	
	return Find(wch, nStart);
}

index_t KString::Find( wchar_t wch, index_t nStart ) const
{
	if(!m_wszString)
	{
		return -1;
	}

	if(nStart >= index_t(m_dwLen - 1))
	{
		return -1;
	}

	wchar_t *wszPos = wcschr(m_wszString + nStart, wch);
	if(!wszPos)
	{
		return -1;
	}
	return (index_t)(wszPos - m_wszString);
}

index_t KString::Find( const char *szSub, index_t nStart ) const
{
	size_t nLen = strlen(szSub) + 1;
	wchar_t *wszSub = new wchar_t[nLen];
	mbstowcs( wszSub, szSub, nLen );

	index_t nRes = Find(wszSub, nStart);

	delete [] wszSub;

	return nRes;
}

index_t KString::Find( const wchar_t *wszSub, index_t nStart ) const
{
	if(!m_wszString)
	{
		return -1;
	}

	if(nStart >= index_t(m_dwLen - 1))
	{
		return -1;
	}

	wchar_t *wszPos = wcsstr(m_wszString + nStart, wszSub);
	if(!wszPos)
	{
		return -1;
	}
	return index_t(wszPos - m_wszString);
}

index_t KString::ReverseFind( char ch ) const
{
	wchar_t wch;
	mbstowcs( &wch, &ch, 1 );

	return ReverseFind(wch);
}

int KString::ReverseFind( wchar_t wch ) const
{
	if(!m_wszString)
	{
		return -1;
	}

	wchar_t *wszPos = wcsrchr(m_wszString, wch);
	if(!wszPos)
	{
		return -1;
	}
	return index_t(wszPos - m_wszString);
}

KString& KString::Format(KString strFormat, ... )
{
	va_list	argList;
	va_start( argList, strFormat );
	FormatV((const wchar_t*)strFormat, argList);
	va_end( argList );
	return *this;
}

// Format data using format string 'pszFormat'
KString& KString::Format( const wchar_t *pszFormat, ... )
{
	va_list argList;
	va_start( argList, pszFormat );
	FormatV(pszFormat, argList);
	va_end( argList );
	return *this;
}

// Format data using format string 'pszFormat'
KString& KString::Format( const char *pszFormat, ... )
{
	va_list argList;
	va_start( argList, pszFormat );
	FormatV(pszFormat, argList );
	va_end( argList );
	return *this;
}

KString& KString::FormatV(const char* pszFormat, va_list args)
{
	char	szString[FORMAT_BUFFER_SIZE];
	vsprintf(szString, pszFormat, args );
	set(szString);
	return *this;
}

KString& KString::FormatV(const wchar_t* pszFormat, va_list args)
{
	wchar_t szString[FORMAT_BUFFER_SIZE];
	vswprintf(szString, FORMAT_BUFFER_SIZE, pszFormat, args );
	set(szString);
	return *this;
}

KString KStringFormat(const char* pszFormat, ...)
{
	KString strResult;
	va_list argList;
	va_start( argList, pszFormat );
	strResult.FormatV(pszFormat, argList );
	va_end( argList );
	return strResult;
}

KString KStringFormat(const wchar_t* pwszFormat, ...)
{
	KString strResult;
	va_list argList;
	va_start( argList, pwszFormat );
	strResult.FormatV(pwszFormat, argList );
	va_end( argList );
	return strResult;
}

KString KStringFormat(KString strFormat, ...)
{
	KString strResult;
	va_list argList;
	va_start( argList, strFormat );
	strResult.FormatV((const wchar_t*)strFormat, argList );
	va_end( argList );
	return strResult;
}


// Copy wide character substring of length n to dst
int wc2utfs(char* dst, const wchar_t *src, int n)
{
  register int len = 0;
  register int p = 0;
  register wchar_t w;

  while (p < n)
  {
    w = src[p++];

    if (w < 0x80)
	{
      dst[len++] = (char)w;
      continue;
	}

    if (w < 0x800)
	{
      dst[len++] = (char)((w >> 6) | 0xC0);
      dst[len++] = (char)((w & 0x3F) | 0x80);
      continue;
	}

    if (w < 0x10000)
	{
      dst[len++] = (char)((w >> 12) | 0xE0);
      dst[len++] = (char)(((w >> 6) & 0x3F) | 0x80);
      dst[len++] = (char)((w & 0x3F) | 0x80);
      continue;
	}
#ifndef WIN32
    if (w < 0x200000)
	{
      dst[len++] = (char)((w >> 18) | 0xF0);
      dst[len++] = (char)(((w >> 12) & 0x3F) | 0x80);
      dst[len++] = (char)(((w >> 6) & 0x3F) | 0x80);
      dst[len++] = (char)((w & 0x3F) | 0x80);
      continue;
	}

    if (w < 0x4000000)
	{
      dst[len++] = (char)((w >> 24) | 0xF8);
      dst[len++] = (char)(((w >> 18) & 0x3F) | 0x80);
      dst[len++] = (char)(((w >> 12) & 0x3F) | 0x80);
      dst[len++] = (char)(((w >> 6) & 0x3F) | 0x80);
      dst[len++] = (char)((w & 0x3F) | 0x80);
      continue;
	}

    dst[len++] = (char)((w >> 30) | 0xFC);
    dst[len++] = (char)(((w >> 24) & 0X3F) | 0x80);
    dst[len++] = (char)(((w >> 18) & 0X3F) | 0x80);
    dst[len++] = (char)(((w >> 12) & 0X3F) | 0x80);
    dst[len++] = (char)(((w >> 6) & 0X3F) | 0x80);
    dst[len++] = (char)((w & 0X3F) | 0x80);
#endif
  }

  return len;
}


// Length of utf8 representation of wide characters string str of length n
int utfslen(const wchar_t *str, int n)
{
  register int len = 0;
  register int p = 0;
  register wchar_t w;

  while (p < n)
  {
    w = str[p++];

	len++;
    
	if (0x80 <= w){ len++;
    if (0x800 <= w){ len++;
    if (0x10000 <= w){ len++;
    if (0x200000 <= w){ len++;
    if (0x4000000 <= w){ len++; }}}}}

  }

  return len;
}

const char* KString::GetAsUtf8() const
{
	size_t nWideLen = wcslen(m_wszString);
	int cbSize = utfslen(m_wszString, (int)nWideLen) + 1;				

	delete[] m_szTempString;

	m_szTempString = new char[cbSize];

	wc2utfs(m_szTempString, m_wszString, (int)nWideLen + 1);

	return m_szTempString;	
}


/*

#ifdef WIN32
#include <windows.h>

const char* KString::GetAsUtf8Old() const
{
	int cbSize = WideCharToMultiByte(CP_UTF8,
						0,
						m_wszString,
						-1,
						NULL,
						0,
						NULL,
						NULL);

	delete[] m_szTempString;

	m_szTempString = new char[cbSize];

	WideCharToMultiByte(CP_UTF8,
						0,
						m_wszString,
						-1,
						m_szTempString,
						cbSize,
						NULL,
						NULL);
	return m_szTempString;	
}
*/
/*KString ConvertUtf8ToKStringOld(const char* szString)
{
	size_t nSrcLength = strlen(szString);
	wchar_t* wszBuffer = new wchar_t[nSrcLength+1];

	MultiByteToWideChar(CP_UTF8, 
						0, 
						szString,
						-1,
						wszBuffer,
						int(nSrcLength+1));

	KString result(wszBuffer);
	delete[] wszBuffer;
	return result;
}*/


// Copy utf8 string of length n to wide character string dst
int utf2wcs(wchar_t *dst, const char *src, int n)
{
  register int len=0;
  register int p=0;
  register wchar_t w;

  while (p < n)
  {
    w = (unsigned char)src[p++];

    if (0xC0 <= w){ w = (wchar_t)((w << 6) ^ (unsigned char)src[p++] ^ 0x3080);
    if (0x800 <= w){ w = (wchar_t)((w << 6) ^ (unsigned char)src[p++] ^ 0x20080);
    if (0x10000 <= w){ w = (wchar_t)((w << 6) ^ (unsigned char)src[p++] ^ 0x400080);
    if (0x200000 <= w){ w = (wchar_t)((w << 6) ^ (unsigned char)src[p++] ^ 0x8000080);
    if (0x4000000 <= w){ w = (wchar_t)((w << 6) ^ (unsigned char)src[p++] ^ 0x80); }}}}}

    dst[len++] = w;
  }

  return len;
}

KString ConvertUtf8ToKString(const char* szString)
{
	size_t nSrcLength = strlen(szString);
	wchar_t* wszBuffer = new wchar_t[nSrcLength + 1];

	utf2wcs(wszBuffer, szString, int(nSrcLength + 1));

	KString result(wszBuffer);
	delete[] wszBuffer;
	return result;
}

#define IMPLEMENT_EQUAL_COMPARISON		\
{										\
	return KString(pStr) == String;		\
}

#define IMPLEMENT_UNEQUAL_COMPARISON	\
{										\
	return KString(pStr) != String;		\
}

bool operator ==(const char *pStr, const KString &String)
IMPLEMENT_EQUAL_COMPARISON
bool operator ==(const wchar_t *pStr, const KString &String)
IMPLEMENT_EQUAL_COMPARISON
bool operator !=(const char *pStr, const KString &String)
IMPLEMENT_UNEQUAL_COMPARISON
bool operator !=(const wchar_t *pStr, const KString &String)
IMPLEMENT_UNEQUAL_COMPARISON


/*#endif*/

