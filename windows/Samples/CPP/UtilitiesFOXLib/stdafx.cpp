#include "stdafx.h"

FXString SDK2FoxString(const char* pcText)
{
	return (const wchar_t*)KString(pcText);
}

FXString SDK2FoxString(const wchar_t* pcText)
{
	return pcText;
}

KString Fox2SDKString(const FXString &fxStr)
{
	FXtchar *buffer = new FXtchar[fxStr.length() + 1];
	utf2tcs(buffer, fxStr.text(), fxStr.length() + 1, fxStr.length() + 1);
	KString sdkStr = (wchar_t*) buffer;
	delete[] buffer;
	return sdkStr;
}
