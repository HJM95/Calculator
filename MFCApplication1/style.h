#pragma once
#include <afxwin.h>

namespace Style
{
	extern CFont g_DisplayTopFont;    // ������ ȸ��, ������ ���Ŀ� ��Ʈ (���� ����)
	extern CFont g_DisplayBottomFont; // ���� ū ������, ������ ���Ŀ� ��Ʈ
	extern CFont g_ButtonFont;        // 0~9 ��ư�� ���� ��Ʈ

	void InitStyles(CWnd* pParent);
	void CleanupStyles();
}