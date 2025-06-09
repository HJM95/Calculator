#include "stdafx.h"
#include "Utils.h"

//�޸� ����ֱ�
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

//��ȣ ��ȿ�� �˻�
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
			if (balance < 0) return false; // �ݴ� ��ȣ�� ���� ����
		}
	}

	return balance == 0; // ���� ��ȣ�� �ݴ� ��ȣ ���� ���ƾ� ��
}