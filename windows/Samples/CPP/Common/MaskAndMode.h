#ifndef _MASK_AND_MODE_H_
#define _MASK_AND_MODE_H_

#include "IsoSDKDefinitions.h"

namespace {
const TCHAR IDS_MODE_AUDIO[] =		   _T("Audio");
const TCHAR IDS_MODE_1[] =              _T("Mode1");
const TCHAR IDS_MODE_2_FORMLESS[] =     _T("Mode2 Formless");
const TCHAR IDS_MODE_2_FORM_1[] =       _T("Mode2 Form1");
const TCHAR IDS_MODE_2_FORM_2[] =       _T("Mode2 Form2");
const TCHAR IDS_MODE_UNKNOWN[] =        _T("Unknown");

const TCHAR IDS_BS_RDT_SYNC_HEADER[] =  _T("BS_RDT_SYNC_HEADER");
const TCHAR IDS_BS_RDT_SUBHEADERS[] =   _T("BS_RDT_SUBHEADERS");
const TCHAR IDS_BS_RDT_DATA[] =         _T("BS_RDT_DATA");
const TCHAR IDS_BS_RDT_EDC_ECC[] =      _T("BS_RDT_EDC_ECC");
const TCHAR IDS_BS_RDT_SUBCH_PQ[] =     _T("BS_RDT_SUBCH_PQ");
const TCHAR IDS_BS_RDT_SUBCH_PW[] =     _T("BS_RDT_SUBCH_PW");
const TCHAR IDS_BS_RDT_SUBCH_RW[] =     _T("BS_RDT_SUBCH_RW");
};

// Namespace to prevent conflicts with simple names like add();
namespace MaskAndMode {

	// Constructs string like "word1 | word2 | word3"
	template <class StringType1, class StringType2>
	void add(StringType1 &to, const StringType2 &what)
	{
		if(to != "") to += " | ";
		to += what;
	}


	//Returns string with mask names separated by " | "
	template <class StringType>
	StringType getMask(int32 mask)
	{
		StringType result;// = "";
		if (mask & BS_RDT_SYNC_HEADER)
			add(result, IDS_BS_RDT_SYNC_HEADER);
		if (mask & BS_RDT_SUBHEADERS)
			add(result,IDS_BS_RDT_SUBHEADERS);	
		if (mask & BS_RDT_DATA)
			add(result, IDS_BS_RDT_DATA);	
		if (mask & BS_RDT_EDC_ECC)
			add(result, IDS_BS_RDT_EDC_ECC);	    
		if (mask & BS_RDT_SUBCH_PQ)
			add(result, IDS_BS_RDT_SUBCH_PQ);	
		if (mask & BS_RDT_SUBCH_PW)
			add(result, IDS_BS_RDT_SUBCH_PW);	
		if (mask & BS_RDT_SUBCH_RW)
			add(result, IDS_BS_RDT_SUBCH_RW);
		return result;
	}
    
	
//Returns constant equivalent to it's string representation.
//Returns 0 on error.
template <class StringType>
int32 str2mask(const StringType& str)
{	
	if (str == IDS_BS_RDT_SUBHEADERS)
		return BS_RDT_SUBHEADERS;
	
	if (str == IDS_BS_RDT_SYNC_HEADER)
		return BS_RDT_SYNC_HEADER;

	if (str == IDS_BS_RDT_DATA)
		return BS_RDT_DATA;
	
	if (str == IDS_BS_RDT_EDC_ECC)
		return BS_RDT_EDC_ECC;
	
	if (str == IDS_BS_RDT_SUBCH_PQ)
		return BS_RDT_SUBCH_PQ;
	
	if (str == IDS_BS_RDT_SUBCH_PW)
		return BS_RDT_SUBCH_PW;
	
	if (str == IDS_BS_RDT_SUBCH_RW)
		return BS_RDT_SUBCH_RW;

	return 0;//Bad string, mask not read.
}


//Returns string with STrack track's mode name.
template <class StringType>
StringType getMode(const int8 nFormat)
{
	switch (nFormat)
	{
		case BS_RTF_AUDIO:
			return IDS_MODE_AUDIO;			
		break;		
		
		case BS_RTF_MODE1:
			return IDS_MODE_1;			
		break;
		
		case BS_RTF_MODE2_FORMLESS:
			return IDS_MODE_2_FORMLESS;				
		
		case BS_RTF_MODE2_FORM1:
			return IDS_MODE_2_FORM_1;				
		
		case BS_RTF_MODE2_FORM2:
			return IDS_MODE_2_FORM_2;
		break;
		
		default:
			return IDS_MODE_UNKNOWN;
		break;
	}
}


//Returns string with SRawTrackToAdd track's format (mode) name.
template <class StringType>
StringType getFormat(const SRAWTrackToAdd &track)
{
	switch (track.nFormat)
	{
		case BS_RTF_AUDIO:
			return IDS_MODE_AUDIO;			
		break;		
		case BS_RTF_MODE1:
			return IDS_MODE_1;			
		break;
		case BS_RTF_MODE2_FORM1:
			return IDS_MODE_2_FORM_1;				
		break;
		case BS_RTF_MODE2_FORM2:
			return IDS_MODE_2_FORM_2;
		break;
		case BS_RTF_MODE2_FORMLESS:
            return IDS_MODE_2_FORMLESS;				
		break;
		default:
			return IDS_MODE_UNKNOWN;
		break;
	}
}


//Reads string and tries to give it's int constant equivalent.
template <class StringType>
int str2format(const StringType &str)
{
	if (str == IDS_MODE_AUDIO)
		return BS_RTF_AUDIO;
	if (str == IDS_MODE_1)
		return BS_RTF_MODE1;
	if (str == IDS_MODE_2_FORMLESS)
		return BS_RTF_MODE2_FORMLESS;
	if (str == IDS_MODE_2_FORM_1)
		return BS_RTF_MODE2_FORM1;
	if (str == IDS_MODE_2_FORM_2)
		return BS_RTF_MODE2_FORM2;    
	return 0; // Error! Illegal Mode name.
}


}; // namespace MaskAndMode 

#endif// _MASK_AND_MODE_H_
