#pragma once
#include <afxstr.h>  // CString ����

namespace CalcUtils
{
	CString FormatNumberWithComma(const CString& strNumber);
	bool IsParenthesesBalanced(const CString& expr);
}
