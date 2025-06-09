#pragma once
#include <afxstr.h>  // CString

namespace CalcLogic {
	// 외부에서 호출하는 함수들 (공용 API)
	CString AppendDigit(const CString& current, const CString& digit, int maxDigits, bool& bOverflowed);
	CString Backspace(const CString& current, bool& bDecimalUsed, bool& bLastInputWasOperator);
	CString AppendOperator(const CString& currentExpression, const CString& oper, bool& bLastInputWasOperator);

	// 중위표현식 계산 함수 (괄호 지원 포함)
	CString Calculate(const CString& expression, bool& bError);
}
	