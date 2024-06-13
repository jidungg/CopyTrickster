#include "stdafx.h"
#include "CharacterHPBar.h"
#include "Character.h"

CCharacterHPBar::CCharacterHPBar(int _iXPos, int _iYPos, int _iXSize, int _iYSize, int _iBorderX, int _iBorderY)
	:CUI(_iXPos, _iYPos, _iXSize, _iYSize), m_iBorderX (_iBorderX), m_iBorderY(_iBorderY)
{
	
}

CCharacterHPBar::~CCharacterHPBar()
{
	Release();
}

void CCharacterHPBar::Initialize()
{
}

void CCharacterHPBar::Update()
{
	if (m_bClosed)
		return;

	if (m_pCharacter && m_pCharacter->Get_Dead() == false)
	{
		m_pFill->Set_Max(m_pCharacter->Get_Stat()._iMaxHP);
		m_pFill->Set_Val(m_pCharacter->Get_Stat()._iHP);
	}
	else
	{
		m_pCharacter = nullptr;
		Set_Close();
	}
	Update_Rect();
}

void CCharacterHPBar::Late_Update()
{

}

void CCharacterHPBar::Render(HDC hdc)
{
	if (m_bClosed)
		return;

	if(m_pFrame)
		m_pFrame->Render(hdc);
	if(m_pFill)
		m_pFill->Render(hdc);
}

void CCharacterHPBar::Release()
{
	Safe_Delete(m_pFrame);
	Safe_Delete(m_pFill);
}

CUI* CCharacterHPBar::On_Click(POINT _pt)
{
	return nullptr;
}

CUI* CCharacterHPBar::On_Mouse_Down(POINT _pt)
{
	return nullptr;
}

CUI* CCharacterHPBar::On_Mouse_Up(POINT _pt)
{
	return nullptr;
}

CUI* CCharacterHPBar::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}

void CCharacterHPBar::Set_Frame(CUIGuageFrame* _pFrame)
{
	m_pFrame = _pFrame;
	m_pFrame->Set_Parent(this);
	m_pFrame->Set_Position({0,0});
	m_pFrame->Set_XSize(m_iXSize);
}

void CCharacterHPBar::Set_Fill(CUIGuageFill* _pFill)
{
	m_pFill = _pFill;
	m_pFill->Set_Parent(this);
	m_pFill->Set_Position({m_iBorderX,m_iBorderY});
	m_pFill->Set_XSize(m_iXSize - m_iBorderX*2);
	m_pFill->Set_YSize(m_iYSize);
}
