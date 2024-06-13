#include "stdafx.h"
#include "Button.h"
#include "BmpMgr.h"
#include "MouseMgr.h"
#include "KeyMgr.h"

CButton::CButton(TCHAR* _pFrameKey, int _iXPos, int _iYPos, int _iXSize, int _iYSize)
	: CUI(_iXPos, _iYPos, _iXSize, _iYSize)
{
	m_eUIType = UI_TYPE::BUTTON;
	m_hIconDC = BMP_INST->Find_Img(_pFrameKey);

}
CButton::CButton(HDC _hdc, int _iXPos, int _iYPos, int _iXSize, int _iYSize)
	: CUI(_iXPos, _iYPos, _iXSize, _iYSize)
{
	m_eUIType = UI_TYPE::BUTTON;
	m_hIconDC = _hdc;
}
CButton::~CButton()
{
	Release();
}

void CButton::Initialize()
{
}

void CButton::Update()
{
	POINT pt = MOUSE_INST->Get_Mouse_Point();
	if (PtInRect(&m_tRect,pt))
	{
		if (KEY_INST->Key_Pressing(VK_LBUTTON))
		{
			m_eCurState = BUTTON_STATE::PRESSED;
		}
		else if (KEY_INST->Key_Up(VK_LBUTTON))
		{
			m_eCurState = BUTTON_STATE::HOVER;
		}
		else
		{
			m_eCurState = BUTTON_STATE::HOVER;
		}
	}
	else
	{
			m_eCurState = BUTTON_STATE::NORMAL;
	}
	Update_Rect();
}

void CButton::Late_Update()
{
}

void CButton::Render(HDC hdc)
{

	GdiTransparentBlt(hdc,  m_tRect.left, m_tRect.top, m_iXSize, m_iYSize,
		m_hIconDC, m_iXSize * (int)m_eCurState, 0, m_iXSize, m_iYSize,
		MAGENTA);
}

void CButton::Release()
{
}

CUI* CButton::On_Click(POINT _pt)
{
	return nullptr;
}

void CButton::Set_BMP(TCHAR* _pFrameKey)
{ 
	m_hIconDC = BMP_INST->Find_Img(_pFrameKey); 
}

CUI* CButton::On_Mouse_Down(POINT _pt)
{
	return nullptr;
}

CUI* CButton::On_Mouse_Up(POINT _pt)
{
	return nullptr;
}

CUI* CButton::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}
