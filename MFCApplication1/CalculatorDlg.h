#pragma once

#include "afxwin.h" // CStatic, CButton 등 컨트롤 사용 시 필요
#include "resource.h"

// CalculatorDlg 대화 상자입니다.

class CalculatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalculatorDlg)

public:
	CalculatorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CalculatorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALCULATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog(); // 다이얼로그 초기화

	void OnNumberButtonClicked();
	void OnOperatorButtonClicked();
	void OnEqualButtonClicked();
	void OnClearButtonClicked();
	void OnDeleteButtonClicked();

	DECLARE_MESSAGE_MAP()

	void UpdateDisplayWithComma(const CString& strNumber);

	static const int MAX_DIGITS = 12;
	CStatic m_displayTop;			// 숫자 표시 컨트롤 변수 (IDC_DISPLAY_TOP)
	CStatic m_displayBottom;		// 숫자 표시 컨트롤 변수 (IDC_DISPLAY_BOTTOM)
	CString m_csExpression;			// 현재 입력된 수식 (텍스트 누적)
	CString m_csResult;				// 계산 결과
	CString m_csCurrent;			 // 현재 입력 중인 숫자

	bool m_bCalculated;				// = 눌렀는지 여부
	bool m_bLastInputWasOperator;  // 연산자 연속 입력 방지
	bool m_bDecimalUsed;		   // 소수점 중복 방지

};
