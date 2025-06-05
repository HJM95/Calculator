#pragma once

#include "afxwin.h" // CStatic, CButton �� ��Ʈ�� ��� �� �ʿ�
#include "resource.h"

// CalculatorDlg ��ȭ �����Դϴ�.

class CalculatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalculatorDlg)

public:
	CalculatorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CalculatorDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALCULATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog(); // ���̾�α� �ʱ�ȭ

	void OnNumberButtonClicked();
	void OnOperatorButtonClicked();
	void OnEqualButtonClicked();
	void OnClearButtonClicked();
	void OnDeleteButtonClicked();

	DECLARE_MESSAGE_MAP()

	void UpdateDisplayWithComma(const CString& strNumber);

	static const int MAX_DIGITS = 12;
	CStatic m_displayTop;			// ���� ǥ�� ��Ʈ�� ���� (IDC_DISPLAY_TOP)
	CStatic m_displayBottom;		// ���� ǥ�� ��Ʈ�� ���� (IDC_DISPLAY_BOTTOM)
	CString m_csExpression;			// ���� �Էµ� ���� (�ؽ�Ʈ ����)
	CString m_csResult;				// ��� ���
	CString m_csCurrent;			 // ���� �Է� ���� ����

	bool m_bCalculated;				// = �������� ����
	bool m_bLastInputWasOperator;  // ������ ���� �Է� ����
	bool m_bDecimalUsed;		   // �Ҽ��� �ߺ� ����

};
