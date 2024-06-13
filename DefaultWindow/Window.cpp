#include "stdafx.h"
#include "Window.h"
#include "MouseMgr.h"


int CWindow::m_iStaticOrder = 0;
CWindow::CWindow(WINDOW_ID _eID, int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive)
	: CUI(_iXPos, _iYPos, _iXSize, _iYSize), m_eWindowType(_eID)
{
	m_eUIType = UI_TYPE::WINDOW;
	m_iOrder = m_iStaticOrder++;
	m_hActiveBMP = hActive;
	m_hDeactiveBMP = hDeactive;
	m_hMinimalActiveBMP = hMinActive;
	m_hMinimalDectiveBMP= hMinDeactive;
	m_bClosed = true;
}


CWindow::~CWindow()
{
	Release();
}

void CWindow::Initialize()
{
	m_pMimimalizeButton = new CWindowBasicButton(WIN_BUTTON_TYPE::MINIMALIZE,this, m_iXSize- 42, 2,16,16);
	m_pMimimalizeButton->Set_Parent(this);
	m_pCloseButton = new CWindowBasicButton(WIN_BUTTON_TYPE::CLOSE, this,  m_iXSize - 22,  2, 16, 16);
	m_pCloseButton->Set_Parent(this);
}

void CWindow::Update()
{
	if (m_bClosed == true)
		return;

	Update_Rect();
	m_pMimimalizeButton->Update();
	m_pCloseButton->Update();
	if (m_bMinimal == false )
	{
		for (auto& i : m_vecComponents)
		{
			i->Update();
		}
	}
}

void CWindow::Update_Rect()
{
	__super::Update_Rect();
	if (m_bMinimal) {
		m_tRect.left = m_iXPos;
		m_tRect.top = m_iYPos;
		m_tRect.right = m_iXPos + m_iXSize;
		m_tRect.bottom = m_iYPos + TITLE_HEIGHT;
		return;
	}
	else
	{
		m_tRect.left = m_iXPos;
		m_tRect.top = m_iYPos;
		m_tRect.right = m_iXPos + m_iXSize;
		m_tRect.bottom = m_iYPos + m_iYSize;

		m_tTitleRect.left = m_iXPos;
		m_tTitleRect.top = m_iYPos;
		m_tTitleRect.right = m_iXPos + m_iXSize;
		m_tTitleRect.bottom = m_iYPos + TITLE_HEIGHT;
	}



}

void CWindow::Late_Update()
{
	if (m_bClosed == true)
		return;

	m_pMimimalizeButton->Late_Update();
	m_pCloseButton->Late_Update();
}

void CWindow::Render(HDC hdc)
{
	if (m_bClosed == true)
		return;

	if (m_bMinimal == false)
	{
		HDC hMemDC = m_hActiveBMP;
		if (m_bActivate == false)
			hMemDC = m_hDeactiveBMP;
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_iXSize, m_iYSize,
			hMemDC, 0, 0, m_iXSize, m_iYSize,
			MAGENTA);
		for (auto& i : m_vecComponents)
		{	
			if(i != nullptr)
				i->Render(hdc);
		}
		Render_Tab_Content(hdc);
		Render_Content(hdc);
	}
	else
	{
		HDC hMemDC = m_hMinimalActiveBMP;
		if (m_bActivate == false)
			hMemDC = m_hMinimalDectiveBMP;
		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_iXSize, TITLE_HEIGHT,
			hMemDC, 0, 0, 272, TITLE_HEIGHT,
			MAGENTA);
	}
	m_pMimimalizeButton->Render(hdc);
	m_pCloseButton->Render(hdc);

}

void CWindow::Release()
{
	Safe_Delete(m_pMimimalizeButton);
	Safe_Delete(m_pCloseButton);
}

POINT CWindow::Get_Offset(POINT _pt)
{
	_pt.x -= m_tRect.left;
	_pt.y -= m_tRect.top;
	return _pt;
}

void CWindow::Render_Tab_Content(HDC hdc)
{
}

void CWindow::Render_Content(HDC hdc)
{
}

CUI* CWindow::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}

CUI* CWindow::On_Drag(POINT _pt)
{
	Move_X(_pt.x);
	Move_Y(_pt.y);
	return nullptr;
}

CUI* CWindow::On_Drop(CUI* _pt)
{
	return nullptr;
}


CUI* CWindow::On_Mouse_Down(POINT _pt)
{
	m_bActivate = true;

	for (auto& pUI : m_vecComponents)
	{
		RECT rc = pUI->Get_Rect();
		if (PtInRect(&rc, _pt))
		{
				
			return pUI->On_Mouse_Down(_pt);;
		}
	}
	return nullptr;
}


CUI* CWindow::On_Mouse_Up(POINT _pt)
{
	for (auto& pUI : m_vecComponents)
	{
		RECT rc = pUI->Get_Rect();
		if (PtInRect(&rc, _pt))
		{
			return pUI->On_Click(_pt);
		}
	}

	if (PtInRect(&m_pMimimalizeButton->Get_Rect(), _pt))
	{
		m_pMimimalizeButton->On_Click(_pt);
		return m_pMimimalizeButton;
	}
	if (PtInRect(&m_pCloseButton->Get_Rect(), _pt))
	{
		m_pCloseButton->On_Click(_pt);
		return m_pCloseButton;
	}
	return nullptr;
}

CUI* CWindow::On_Click(POINT _pt)
{
	return nullptr;
}



