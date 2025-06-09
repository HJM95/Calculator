#pragma once
#include <afxstr.h>  // CString

namespace CalcLogic {
	// �ܺο��� ȣ���ϴ� �Լ��� (���� API)
	CString AppendDigit(const CString& current, const CString& digit, int maxDigits, bool& bOverflowed);
	CString Backspace(const CString& current, bool& bDecimalUsed, bool& bLastInputWasOperator);
	CString AppendOperator(const CString& currentExpression, const CString& oper, bool& bLastInputWasOperator);

	// ����ǥ���� ��� �Լ� (��ȣ ���� ����)
	CString Calculate(const CString& expression, bool& bError);
}
	