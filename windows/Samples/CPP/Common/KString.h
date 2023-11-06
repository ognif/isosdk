#ifndef __KSTRING_H__
#define __KSTRING_H__

#include <cstdio>
#include <tchar.h>
#include <clocale>

class LocaleSetter
{
public:
	LocaleSetter()
	{
#ifdef WIN32
		setlocale(LC_ALL, ".ACP");		
#else
		setlocale(LC_ALL, "en_US.UTF-8");
#endif
	}
};

/// Helper class intended to convert strings to upper and lower case (???? make a correct description)
class KString: private LocaleSetter
{
public:	
	typedef int index_t;

	/// Construct empty string
	KString();
	/// Copy from another string
	KString(const KString &String);
	/// Copy from multibyte string
	KString(const char *szString);
	/// Copy from Unicode string
	KString(const wchar_t *wszString);
	/// Construct single-symbol string
	explicit KString(char Char);
	/// Construct single-symbol string from Unicode symbol
	explicit KString(wchar_t wChar);
	/// Construct string of length 'nLength' filled with 'wChar'
	KString(size_t nLength, wchar_t wChar);
	/// Construct string of length 'nLenght' using non-zero-terminated multibyte string 'pChar'
	KString(const char* pChar, size_t nLength);

	/// UTF8 representation
	const char* GetAsUtf8() const;

	~KString();

	/// Clear string
	void Empty();

	//Operators
	const KString &operator =(const KString &String);
	const KString &operator =(const char *szString);
	const KString &operator =(const wchar_t *wszString);
	const KString &operator =(char Char);
	const KString &operator =(wchar_t wChar);

	const KString &operator +=(const KString &String);
	const KString &operator +=(const char *szString);
	const KString &operator +=(const wchar_t *wszString);
	const KString &operator +=(const char Char);
	const KString &operator +=(const wchar_t wChar);

	bool operator <(const KString &String) const;
	bool operator <(const char *szString) const;
	bool operator <(const wchar_t *wszString) const;
	bool operator >(const KString &String) const;
	bool operator >(const char *szString) const;
	bool operator >(const wchar_t *wszString) const;

	bool operator ==(const KString &String) const;
	bool operator ==(const char *szString) const;
	bool operator ==(const wchar_t *wszString) const;
	bool operator ==(char Char) const;
	bool operator ==(wchar_t wChar) const;

	bool operator !=(const KString &String) const;
	bool operator !=(const char *szString) const;
	bool operator !=(const wchar_t *wszString) const;
	bool operator !=(char Char) const;
	bool operator !=(wchar_t wChar) const;

	friend KString operator+( const KString& str1, const KString& str2 );
	friend KString operator+( const KString& str1, wchar_t *psz2 );
	friend KString operator+( wchar_t *psz1, const KString& str2 );
	friend KString operator+( const KString& str1, wchar_t ch2 );
	friend KString operator+( const KString& str1, char ch2 );
	friend KString operator+( wchar_t ch1, const KString& str2 );
	friend KString operator+( char ch1, const KString& str2 );

	operator const char*() const;
	operator const wchar_t*() const;

	TCHAR operator [](index_t nIndex) const;

	///////////////////////

	/// Returns amount of characters in the string
	size_t GetLength() const;			

	/// Sets new string length. Can only truncate string.
	void SetLength( size_t nLength );

	/// Returns pointer to modificable buffer at least nMinBufferLength
	TCHAR *GetBuffer( size_t nMinBufferLength );
	void ReleaseBuffer();

	/// Returns 'true' if string's length is 0
	bool IsEmpty() const throw();

	/// Truncate string to the given length. Equal to SetLength.
	void Truncate( size_t nNewLength );
	/// Deletes 'nCount' characters from position 'iIndex'
	size_t Delete( index_t iIndex, size_t nCount = 1 );

	/// Returns character from given position
	TCHAR GetAt( index_t iChar ) const;

	/// Returns character from giver position reverse
	TCHAR GetAtReverse(index_t iChar) const;

	/// Sets symbol at position 'iChar'
	void SetAt( index_t iChar, TCHAR tSym );

	/// Returns 'nAmount' of symbols from the beginning
	KString Left(size_t nAmount) const;
	/// Returns 'nAmount' of symbols from the end of a string
	KString Right(size_t nAmount) const;
	/// Return the substring starting at index 'iFirst'

	/// Cuts all symbols beginning from the nAmount - 1
	void KeepLeft(int nAmount);		
	/// Cuts all symbols except nAmount rightmost symbols (NULL - terminated character is not included)
	void KeepRight(int nAmount);	

	KString Mid( index_t iFirst ) const;
	/// Return the substring starting at index 'iFirst', with length 'nCount'
	KString Mid( index_t iFirst, size_t nCount ) const;	

	/// Remove all trailing whitespace
	KString& TrimRight();
	/// Remove all leading whitespace
	KString& TrimLeft();
	/// Remove all leading and trailing whitespace
	KString& Trim();
	/// Remove all leading and trailing occurrences of character 'chTarget'
	KString& Trim( wchar_t chTarget );
	// Remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
	//KString& Trim( wchar_t *pszTargets );
	// Remove all trailing occurrences of character 'chTarget'
	KString& TrimRight( wchar_t chTarget );
	// Remove all trailing occurrences of any of the characters in string 'pszTargets'
	KString& TrimRight( wchar_t *pszTargets );
	// Remove all leading occurrences of character 'chTarget'
	KString& TrimLeft( wchar_t chTarget );
	// Remove all leading occurrences of any of the characters in string 'pszTargets'
	KString& TrimLeft( wchar_t *pszTargets );

	KString& MakeUpper();	
	KString& MakeLower();
	KString  MakeUpperCopy() const;

	//return
	//\arg -1	If the current string is less than the passed one
	//\arg	0	If the current string is equal to the passed one
	//\arg	1	If the current string iw bigger than the passed one
	int CompareNoCase(const KString &String) const;
	int CompareNoCase(const char *szString) const;
	int CompareNoCase(const wchar_t *wszString) const;


	/* \brief Find
	*
	*	\return 
	*	\arg The zero-based index of the first character in this
	*	KString object that matches the requested substring or characters;
	*	\arg -1 if the substring or character is not found
	*/
	index_t Find( const char *szSub ) const;
	index_t Find( const wchar_t *wszSub ) const;
	index_t Find( char ch, index_t nStart = 0 ) const;
	index_t Find( wchar_t wch, index_t nStart = 0 ) const;
	index_t Find( const char *szSub, index_t nStart ) const;
	index_t Find( const wchar_t *wszSub, index_t nStart ) const;

	index_t ReverseFind( char ch ) const;
	index_t ReverseFind( wchar_t wch ) const;

	// Format data using format string
	KString& Format( KString strFormat, ... );
	KString& Format( const wchar_t *pszFormat, ... );
	KString& Format( const char *pszFormat, ... );

	KString& FormatV( const wchar_t* pwszFormat, va_list args);
	KString& FormatV( const char* pszFormat, va_list args);

protected:
	void set(const KString &String);
	void set(const char *szString);
	void set(const wchar_t *wszString);
	void set(char Char);
	void set(wchar_t wChar);

private:
	wchar_t			*m_wszString;
	mutable char	*m_szTempString;
	size_t			m_dwLen;
};

// a-la printf formatting functions
KString KStringFormat(KString strFormat, ... );
KString KStringFormat(const wchar_t* pwszFormat, ... );
KString KStringFormat(const char* pszFormat, ... );

KString ConvertUtf8ToKString(const char* szString);

bool operator ==(const char *szString, const KString &String);
bool operator ==(const wchar_t *wszString, const KString &String);
bool operator !=(const char *szString, const KString &String);
bool operator !=(const wchar_t *wszString, const KString &String);


#endif	//__KSTRING_H__
