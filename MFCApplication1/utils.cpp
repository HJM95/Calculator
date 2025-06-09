#include "stdafx.h"
#include "Utils.h"

//ÄÞ¸¶ Âï¾îÁÖ±â
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

//°ýÈ£ À¯È¿¼º °Ë»ç
bool CalcUtils::IsParenthesesBalanced(const CString& expr)
{
	int balance = 0;

	for (int i = 0; i < expr.GetLength(); ++i)
	{
		TCHAR ch = expr[i];
		if (ch == '(') {
			balance++;
		} else if (ch == ')') {
			balance--;
			if (balance < 0) return false; // ´Ý´Â °ýÈ£°¡ ¸ÕÀú ³ª¿È
		}
	}

	return balance == 0; // ¿©´Â °ýÈ£¿Í ´Ý´Â °ýÈ£ ¼ö°¡ °°¾Æ¾ß ÇÔ
}