#include "stdafx.h"
#include "logic.h"
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>
#include <cmath>

CString CalcLogic::AppendDigit(const CString& current, const CString& digit, int maxDigits, bool& bOverflowed)
{
	CString raw = current;
	raw.Remove(',');

	if (raw.GetLength() >= maxDigits) {
		bOverflowed = true;
		return _T("999999999999");
	}

	bOverflowed = false;
	return current + digit;
}

CString CalcLogic::Backspace(const CString& current, bool& bDecimalUsed, bool& bLastInputWasOperator)
{
	if (current.IsEmpty())
		return current;

	TCHAR lastChar = current.GetAt(current.GetLength() - 1);
	CString newStr = current.Left(current.GetLength() - 1);

	if (lastChar == '.')
		bDecimalUsed = false;
	else if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/')
		bLastInputWasOperator = false;

	return newStr;
}

CString CalcLogic::AppendOperator(const CString& currentExpression, const CString& oper, bool& bLastInputWasOperator)
{
	if (currentExpression.IsEmpty())
		return currentExpression;

	if (bLastInputWasOperator) {
		CString newExpr = currentExpression.Left(currentExpression.GetLength() - 1);
		newExpr += oper;
		return newExpr;
	}
	else {
		bLastInputWasOperator = true;
		return currentExpression + oper;
	}
}

// ----- Expression Parsing Utilities -----

int GetPrecedence(TCHAR op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

double ApplyOp(double a, double b, TCHAR op, bool& bError)
{
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		if (b == 0) {
			bError = true;
			return 0;
		}
		return a / b;
	default:
		bError = true;
		return 0;
	}
}

CString CalcLogic::Calculate(const CString& expression, bool& bError)
{
	bError = false;

	std::stack<double> values;
	std::stack<TCHAR> ops;
	CString token;
	double num;

	for (int i = 0; i < expression.GetLength(); ++i)
	{
		TCHAR ch = expression[i];

		if (isdigit(ch) || ch == '.')
		{
			token += ch;
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			if (!token.IsEmpty())
			{
				num = _tstof(token);
				values.push(num);
				token.Empty();
			}

			while (!ops.empty() && GetPrecedence(ops.top()) >= GetPrecedence(ch))
			{
				double b = values.top(); values.pop();
				double a = values.top(); values.pop();
				TCHAR op = ops.top(); ops.pop();
				values.push(ApplyOp(a, b, op, bError));
				if (bError) return _T("ERROR");
			}

			ops.push(ch);
		}
		else {
			bError = true;
			return _T("ERROR");
		}
	}

	if (!token.IsEmpty()) {
		values.push(_tstof(token));
	}

	while (!ops.empty())
	{
		if (values.size() < 2) { bError = true; return _T("ERROR"); }

		double b = values.top(); values.pop();
		double a = values.top(); values.pop();
		TCHAR op = ops.top(); ops.pop();
		values.push(ApplyOp(a, b, op, bError));
		if (bError) return _T("ERROR");
	}

	if (values.size() != 1) {
		bError = true;
		return _T("ERROR");
	}

	CString strResult;
	strResult.Format(_T("%.10g"), values.top());
	return strResult;
}
