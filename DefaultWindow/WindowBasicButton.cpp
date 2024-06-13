#include "stdafx.h"
#include "WindowBasicButton.h"
#include "Window.h"
#include "SoundMgr.h"

CWindowBasicButton::CWindowBasicButton(WIN_BUTTON_TYPE _eType,CWindow* _pWnd , int _iXPos, int _iYPos, int _iXSize, int _iYSize)
	:  m_eWinButtonType(_eType), m_pWindow(_pWnd)
{
	m_hIconDC = BMP_INST->Find_Img( L"UI_Icon_WinButton");
	m_iXSize = _iXSize;
	m_iYSize = (_iYSize);
	m_iXPos = _iXPos;
	m_iYPos = _iYPos;
}

CWindowBasicButton::~CWindowBasicButton()
{
	Release();
}

void CWindowBasicButton::Render(HDC hdc)
{
	int idx = (int)m_eWinButtonType;
	switch (m_eWinButtonType)
	{
	case WIN_BUTTON_TYPE::UNMINIMALIZE:
		idx = 0;
		break;
	case WIN_BUTTON_TYPE::MINIMALIZE:
		idx = 1;
		break;
	case WIN_BUTTON_TYPE::OPEN:
		idx = 2;
		break;
	case WIN_BUTTON_TYPE::CLOSE:
		idx = 2;
		break;
	case WIN_BUTTON_TYPE::END:
		break;
	default:
		break;
	}
	switch (m_eCurState)
	{
	case BUTTON_STATE::NORMAL:
		idx = idx + 0;
		break;
	case BUTTON_STATE::HOVER:
		idx += 3;
		break;
	case BUTTON_STATE::PRESSED:
		idx += 6; 
		break;
	case BUTTON_STATE::END:
		break;
	default:
		break;
	}
	int xOff = 0, yOff = 0;
	if (m_pParent)
	{
		RECT tParent = m_pParent->Get_Rect();
		xOff = tParent.left;
		yOff = tParent.top;
	}
	GdiTransparentBlt(hdc, xOff + m_iXPos + 2, yOff + m_iYPos + 2, 64, 64,
		m_hIconDC, 64 * idx, 0, 64, 64,
		MAGENTA);
}

CUI* CWindowBasicButton::On_Click(POINT _pt)
{
	switch (m_eWinButtonType)
	{
	case WIN_BUTTON_TYPE::CLOSE:
		m_pWindow->Set_Close();
		m_eWinButtonType = WIN_BUTTON_TYPE::OPEN;
		break;
	case WIN_BUTTON_TYPE::OPEN:
		m_pWindow->Set_Open();
		m_eWinButtonType = WIN_BUTTON_TYPE::CLOSE;
		break;
	case WIN_BUTTON_TYPE::MINIMALIZE:
		m_pWindow->Set_Minimize();
		m_eWinButtonType = WIN_BUTTON_TYPE::UNMINIMALIZE;
		break;
	case WIN_BUTTON_TYPE::UNMINIMALIZE:
		m_pWindow->Set_UnMinimize();
		m_eWinButtonType = WIN_BUTTON_TYPE::MINIMALIZE;
		break;
	case WIN_BUTTON_TYPE::END:
		break;
	default:
		break;
	}
	return this;
}

CUI* CWindowBasicButton::On_Mouse_Down(POINT _pt)
{
	return this;
}

CUI* CWindowBasicButton::On_Mouse_Press(POINT _pt)
{
	return this;
}

CUI* CWindowBasicButton::On_Mouse_Up(POINT _pt)
{
	return this;
}
