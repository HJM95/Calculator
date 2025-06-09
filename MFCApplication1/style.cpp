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

		// 1) IDC_DISPLAY_TOP 폰트
		lf.lfHeight = 24;          // 적당한 크기, 필요에 따라 조정
		lf.lfWeight = FW_NORMAL;   // 보통 굵기
		_tcscpy_s(lf.lfFaceName, _T("굴림"));
		g_DisplayTopFont.CreateFontIndirect(&lf);

		// 2) IDC_DISPLAY_BOTTOM 폰트
		lf.lfHeight = 36;          // DISPLAY_TOP보다 크다
		lf.lfWeight = FW_BOLD;     // 굵은 글씨
		g_DisplayBottomFont.CreateFontIndirect(&lf);

		// 3) 0~9 버튼용 폰트
		lf.lfHeight = 20;          // 적당한 크기
		lf.lfWeight = FW_BOLD;     // 볼드 처리
		g_ButtonFont.CreateFontIndirect(&lf);

		// 여기서는 색과 정렬은 SetFont에서 안되고 컨트롤 속성 또는 메시지 처리 필요
	}

	void CleanupStyles()
	{
		if (g_DisplayTopFont.m_hObject) g_DisplayTopFont.DeleteObject();
		if (g_DisplayBottomFont.m_hObject) g_DisplayBottomFont.DeleteObject();
		if (g_ButtonFont.m_hObject) g_ButtonFont.DeleteObject();
	}
}
