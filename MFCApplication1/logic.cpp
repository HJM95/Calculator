#include "stdafx.h"
#include "logic.h"
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>
#include <cmath>


//maxDigits 값 초과시 
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

//DELETE 버튼 지우기 연산
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

//이전 입력값이 연산자인 경우 = 삭제, 아닌 경우 = 추가
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

//연산자 우선순위, 피연산자 판단
int GetPrecedence(TCHAR op) {
	if (op == _T('+') || op == _T('-')) return 1;
	if (op == _T('*') || op == _T('/')) return 2;
	return 0;
}

bool IsOperator(TCHAR ch) {
	return ch == _T('+') || ch == _T('-') || ch == _T('*') || ch == _T('/');
}

// 중위 -> 후위 
std::vector<CString> InfixToPostfix(const CString& expr)
{
	std::vector<CString> output; //리턴할 최종 후위값
	std::stack<TCHAR> opStack; //연산자&괄호 처리를 위한 스택
	CString token; //숫자 누적 임시 변수	

	for (int i = 0; i < expr.GetLength(); ++i)
	{
		TCHAR ch = expr[i];

		//숫자가 아닌 문자를 만날때까지 token값 추가
		if (_istdigit(ch) || ch == _T('.')) {
			token += ch;
		} else {
			if (!token.IsEmpty()) {
				output.push_back(token);
				token.Empty();
			}

			//'(' 괄호는 무조건 스택에 push
			if (ch == _T('(')) {
				opStack.push(ch);
			} /* 스택에서 '('가 나올때까지 pop, output에 연산자 추가, '('를 만나면 pop만하고 추가 x */else if (ch == _T(')')) {
				while (!opStack.empty() && opStack.top() != _T('(')) {
					output.push_back(CString(opStack.top()));
					opStack.pop();
				}
				if (!opStack.empty() && opStack.top() == _T('(')) {
					opStack.pop(); // '(' 제거
				}
			} else if (IsOperator(ch)) {
				while (!opStack.empty() &&
					GetPrecedence(opStack.top()) >= GetPrecedence(ch)) {
						output.push_back(CString(opStack.top()));
						opStack.pop();
				}
				opStack.push(ch);
			}
		}
	}

	//수식 끝에 도달했을때 남아 있는 숫자 token이 있으면 결과에 추가
	if (!token.IsEmpty()) {
		output.push_back(token);
	}

	//스택에 남은 연산자들 모두 output에 추가
	//이 시점에서 괄호 연산 없어야 함
	while (!opStack.empty()) {
		output.push_back(CString(opStack.top()));
		opStack.pop();
	}

	//최종 후위표기식(벡터) 반환
	return output;
}

// 후위 계산
CString EvaluatePostfix(const std::vector<CString>& tokens, bool& bError)
{
	std::stack<double> stack;

	for (const CString& tok : tokens)
	{
		if (IsOperator(tok[0]) && tok.GetLength() == 1) {
			if (stack.size() < 2) {
				bError = true;
				return _T("");
			}

			double b = stack.top(); stack.pop();
			double a = stack.top(); stack.pop();	
			double result = 0;

			switch (tok[0]) {
			case _T('+'): result = a + b; break;
			case _T('-'): result = a - b; break;
			case _T('*'): result = a * b; break;
			case _T('/'):
				if (b == 0) {
					bError = true;
					return _T("");
				}
				result = a / b; break;
			}
			stack.push(result);
		}
		else {
			double val = _tstof(tok);
			stack.push(val);
		}
	}

	if (stack.size() != 1) {
		bError = true;
		return _T("");
	}

	CString resultStr;
	resultStr.Format(_T("%.12g"), stack.top());
	return resultStr;
}

//실 계산
CString CalcLogic::Calculate(const CString& expr, bool& bError) {
	bError = false;
	std::vector<CString> postfix = InfixToPostfix(expr);
	return EvaluatePostfix(postfix, bError);
}