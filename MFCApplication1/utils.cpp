#include "stdafx.h"
#include "Utils.h"

////////////////////////////////////////////////////
//ÄÞ¸¶ Âï¾îÁÖ´Â ÇÔ¼ö
////////////////////////////////////////////////////

CString CalcUtils::FormatNumberWithComma(const CString& strNumber)
{
	CString strFormatted;

	int len = strNumber.GetLength();
	int commaCount = (len - 1) / 3;

	int index = 0;
	int firstGroupLen = len - commaCount * 3;

	strFormatted = strNumber.Mid(index, firstGroupLen);
	index += firstGroupLen;

	while (index < len)
	{
		strFormatted += _T(",");
		strFormatted += strNumber.Mid(index, 3);
		index += 3;
	}

	return strFormatted;
}

