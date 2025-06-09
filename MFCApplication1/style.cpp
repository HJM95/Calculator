#include "stdafx.h"
#include "style.h"

namespace Style
{
	CFont g_DisplayTopFont;
	CFont g_DisplayBottomFont;
	CFont g_ButtonFont;

	void InitStyles(CWnd* pParent)
	{
		LOGFONT lf = { 0 };

		// 1) IDC_DISPLAY_TOP ��Ʈ
		lf.lfHeight = 24;          // ������ ũ��, �ʿ信 ���� ����
		lf.lfWeight = FW_NORMAL;   // ���� ����
		_tcscpy_s(lf.lfFaceName, _T("����"));
		g_DisplayTopFont.CreateFontIndirect(&lf);

		// 2) IDC_DISPLAY_BOTTOM ��Ʈ
		lf.lfHeight = 36;          // DISPLAY_TOP���� ũ��
		lf.lfWeight = FW_BOLD;     // ���� �۾�
		g_DisplayBottomFont.CreateFontIndirect(&lf);

		// 3) 0~9 ��ư�� ��Ʈ
		lf.lfHeight = 20;          // ������ ũ��
		lf.lfWeight = FW_BOLD;     // ���� ó��
		g_ButtonFont.CreateFontIndirect(&lf);

		// ���⼭�� ���� ������ SetFont���� �ȵǰ� ��Ʈ�� �Ӽ� �Ǵ� �޽��� ó�� �ʿ�
	}

	void CleanupStyles()
	{
		if (g_DisplayTopFont.m_hObject) g_DisplayTopFont.DeleteObject();
		if (g_DisplayBottomFont.m_hObject) g_DisplayBottomFont.DeleteObject();
		if (g_ButtonFont.m_hObject) g_ButtonFont.DeleteObject();
	}
}
