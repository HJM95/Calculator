#include "stdafx.h"
#include "CalculatorDlg.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "resource.h"
#include "utils.h"
#include "logic.h"
#include "style.h"

IMPLEMENT_DYNAMIC(CalculatorDlg, CDialogEx)

CalculatorDlg::CalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CalculatorDlg::IDD, pParent)
{
	m_csCurrent = _T("");
	m_csExpression = _T("");
	m_csResult = _T("");
}

CalculatorDlg::~CalculatorDlg()
{
}

void CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISPLAY_TOP, m_displayTop);
	DDX_Control(pDX, IDC_DISPLAY_BOTTOM, m_displayBottom);
}

BEGIN_MESSAGE_MAP(CalculatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_0, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_1, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_2, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_3, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_4, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_5, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_6, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_7, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_8, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_9, &CalculatorDlg::OnNumberButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CalculatorDlg::OnOperatorButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CalculatorDlg::OnOperatorButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CalculatorDlg::OnOperatorButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CalculatorDlg::OnOperatorButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CalculatorDlg::OnEqualButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CalculatorDlg::OnClearButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CalculatorDlg::OnDeleteButtonClicked)
END_MESSAGE_MAP()

BOOL CalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Style::InitStyles(this);

	CStatic* pDisplayTop = (CStatic*)GetDlgItem(IDC_DISPLAY_TOP);
	if (pDisplayTop) {
		pDisplayTop->SetFont(&Style::g_DisplayTopFont);
	}

	CStatic* pDisplayBottom = (CStatic*)GetDlgItem(IDC_DISPLAY_BOTTOM);
	if (pDisplayBottom) {
		pDisplayBottom->SetFont(&Style::g_DisplayBottomFont);
	}

	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_9; ++i) {
		CWnd* pBtn = GetDlgItem(i);
		if (pBtn) pBtn->SetFont(&Style::g_ButtonFont);
	}

	return TRUE;
}

void CalculatorDlg::OnClearButtonClicked()
{
	m_csExpression.Empty();
	m_csCurrent.Empty();
	m_csResult.Empty();
	m_bDecimalUsed = false;
	m_bLastInputWasOperator = false;
	m_bCalculated = false;

	UpdateDisplayWithComma(_T("0"));
	m_displayBottom.SetWindowText(_T("0"));
}

void CalculatorDlg::OnNumberButtonClicked()
{
	UINT nID = (UINT)GetCurrentMessage()->wParam;
	CString digit;

	switch (nID) {
	case IDC_BUTTON_0: digit = _T("0"); break;
	case IDC_BUTTON_1: digit = _T("1"); break;
	case IDC_BUTTON_2: digit = _T("2"); break;
	case IDC_BUTTON_3: digit = _T("3"); break;
	case IDC_BUTTON_4: digit = _T("4"); break;
	case IDC_BUTTON_5: digit = _T("5"); break;
	case IDC_BUTTON_6: digit = _T("6"); break;
	case IDC_BUTTON_7: digit = _T("7"); break;
	case IDC_BUTTON_8: digit = _T("8"); break;
	case IDC_BUTTON_9: digit = _T("9"); break;
	default: return;
	}

	// 만약 바로 전에 계산 완료 후 숫자 입력하면 초기화
	if (m_bCalculated) {
		m_csExpression.Empty();
		m_csCurrent.Empty();
		m_bCalculated = false;
	}

	// 숫자 붙이기
	m_csCurrent += digit;
	UpdateDisplayWithComma(m_csCurrent);

	m_bLastInputWasOperator = false;
}


void CalculatorDlg::OnOperatorButtonClicked()
{
	UINT nID = (UINT)GetCurrentMessage()->wParam;
	CString oper;

	switch (nID) {
	case IDC_BUTTON_ADD: oper = _T("+"); break;
	case IDC_BUTTON_MIN: oper = _T("-"); break;
	case IDC_BUTTON_MUL: oper = _T("*"); break;
	case IDC_BUTTON_DIV: oper = _T("/"); break;
	default: return;
	}

	// 계산 이후면 현재 결과를 기반으로 다시 시작
	if (m_bCalculated) {
		m_csExpression = m_csCurrent;
		m_csCurrent.Empty();
		m_bCalculated = false;
	}

	// 현재 숫자가 있으면 수식에 붙임
	if (!m_csCurrent.IsEmpty()) {
		m_csExpression += m_csCurrent;
		m_csCurrent.Empty();
	}

	// 마지막에 연산자가 있다면 교체
	if (!m_csExpression.IsEmpty()) {
		TCHAR lastChar = m_csExpression[m_csExpression.GetLength() - 1];
		if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/')
			m_csExpression.Delete(m_csExpression.GetLength() - 1, 1);
	}

	m_csExpression += oper;

	m_displayTop.SetWindowText(m_csExpression);
	m_displayBottom.SetWindowText(_T("0"));

	m_bLastInputWasOperator = true;
	m_bDecimalUsed = false;
}



void CalculatorDlg::OnEqualButtonClicked()
{
	if (!m_csCurrent.IsEmpty()) {
		m_csExpression += m_csCurrent;
	}

	// 끝에 연산자 제거
	if (!m_csExpression.IsEmpty()) {
		TCHAR lastChar = m_csExpression[m_csExpression.GetLength() - 1];
		if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/')
			m_csExpression.Delete(m_csExpression.GetLength() - 1, 1);
	}

	bool bError = false;
	m_csResult = CalcLogic::Calculate(m_csExpression, bError);

	if (bError || m_csResult.IsEmpty()) {
		m_displayBottom.SetWindowText(_T("ERROR"));
	}
	else {
		m_displayBottom.SetWindowText(m_csResult);
		m_displayTop.SetWindowText(m_csExpression);
	}

	// 결과 저장 → 다음 입력 시 초기화
	m_csCurrent = m_csResult;
	m_csExpression.Empty();
	m_bCalculated = true;
	m_bLastInputWasOperator = false;
	m_bDecimalUsed = false;
}



void CalculatorDlg::OnDeleteButtonClicked()
{
	m_csCurrent = CalcLogic::Backspace(m_csCurrent, m_bDecimalUsed, m_bLastInputWasOperator);
	UpdateDisplayWithComma(m_csCurrent.IsEmpty() ? _T("0") : m_csCurrent);
}

void CalculatorDlg::UpdateDisplayWithComma(const CString& strNumber)
{
	CString formatted = CalcUtils::FormatNumberWithComma(strNumber);
	m_displayTop.SetWindowText(formatted);
}