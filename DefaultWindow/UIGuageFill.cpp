#include "stdafx.h"
#include "UIGuageFill.h"

CUIGuageFill::CUIGuageFill(int _iXSize, int _iYSize, HDC _fillDC)
	:m_hFillDC(_fillDC), m_iSrcX(_iXSize), m_iSrcY(_iYSize)
{

}

CUIGuageFill::~CUIGuageFill()
{
}

void CUIGuageFill::Initialize()
{
}

void CUIGuageFill::Update()
{
}

void CUIGuageFill::Late_Update()
{
}

void CUIGuageFill::Render(HDC hdc)
{
	float fRatio = m_iVal / (float)m_iMax;
	int xOff = 0, yOff = 0;
	if (m_pParent)
	{
		RECT tParent = m_pParent->Get_Rect();
		xOff = tParent.left;
		yOff = tParent.top;
	}
	GdiTransparentBlt(hdc, xOff + m_iXPos, yOff + m_iYPos, m_iXSize*fRatio, m_iSrcY,
		m_hFillDC, 0, 0, m_iSrcX, m_iSrcY,
		MAGENTA);
}

void CUIGuageFill::Release()
{
}

CUI* CUIGuageFill::On_Click(POINT _pt)
{
	return nullptr;
}

CUI* CUIGuageFill::On_Mouse_Down(POINT _pt)
{
	return nullptr;
}

CUI* CUIGuageFill::On_Mouse_Up(POINT _pt)
{
	return nullptr;
}

CUI* CUIGuageFill::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}
