#include "stdafx.h"
#include "UIGuageFrame.h"

CUIGuageFrame::CUIGuageFrame(int _iLeftX, int _iLeftY, int _iMidX, int _iMidY, HDC _leftDC, HDC _midDC, HDC _rightDC)
	: m_hFrameLeftDC(_leftDC), m_hFrameMidDC(_midDC), m_hFrameRightDC(_rightDC), m_iLeftX(_iLeftX), m_iLeftY(_iLeftY), m_iMidX(_iMidX), m_iMidY(_iMidY)
{

}

CUIGuageFrame::~CUIGuageFrame()
{
}

void CUIGuageFrame::Initialize()
{
}

void CUIGuageFrame::Update()
{
}

void CUIGuageFrame::Late_Update()
{
}

void CUIGuageFrame::Render(HDC hdc)
{
	int xOff = 0, yOff = 0;
	if (m_pParent)
	{
		RECT tParent = m_pParent->Get_Rect();
		xOff = tParent.left;
		yOff = tParent.top;
	}
	GdiTransparentBlt(hdc, xOff + m_iXPos, yOff + m_iYPos, m_iLeftX, m_iLeftY,
		m_hFrameLeftDC, 0, 0, m_iLeftX, m_iLeftY,
		MAGENTA);
	GdiTransparentBlt(hdc, xOff + m_iXPos + m_iLeftX, yOff + m_iYPos, m_iXSize - m_iLeftX*2, m_iLeftY,
		m_hFrameMidDC, 0, 0, m_iMidX, m_iMidY,
		MAGENTA);
	GdiTransparentBlt(hdc, xOff + m_iXPos +m_iXSize- m_iLeftX, yOff + m_iYPos,  m_iLeftX , m_iLeftY,
		m_hFrameRightDC, 0, 0, m_iLeftX, m_iLeftY,
		MAGENTA);
}

void CUIGuageFrame::Release()
{
}

CUI* CUIGuageFrame::On_Click(POINT _pt)
{
	return nullptr;
}

CUI* CUIGuageFrame::On_Mouse_Down(POINT _pt)
{
	return nullptr;
}

CUI* CUIGuageFrame::On_Mouse_Up(POINT _pt)
{
	return nullptr;
}

CUI* CUIGuageFrame::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}
