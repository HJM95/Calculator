#pragma once
#include <afxwin.h>

namespace Style
{
	extern CFont g_DisplayTopFont;    // 은은한 회색, 오른쪽 정렬용 폰트 (보통 굵기)
	extern CFont g_DisplayBottomFont; // 굵고 큰 검은색, 오른쪽 정렬용 폰트
	extern CFont g_ButtonFont;        // 0~9 버튼용 볼드 폰트

	void InitStyles(CWnd* pParent);
	void CleanupStyles();
}