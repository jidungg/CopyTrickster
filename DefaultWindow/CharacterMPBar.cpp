#include "stdafx.h"
#include "CharacterMPBar.h"
#include "Character.h"

CCharacterMPBar::CCharacterMPBar(int _iXPos, int _iYPos, int _iXSize, int _iYSize, int _iBorderX, int _iBorderY)
	:CCharacterHPBar(_iXPos, _iYPos, _iXSize,_iYSize, _iBorderX, _iBorderY)
{
}

CCharacterMPBar::~CCharacterMPBar()
{
	Release();
}

void CCharacterMPBar::Update()
{
	if (m_bClosed)
		return;

	if (m_pCharacter && m_pCharacter->Get_Dead() == false)
	{
		m_pFill->Set_Max(m_pCharacter->Get_Stat()._iMaxMP);
		m_pFill->Set_Val(m_pCharacter->Get_Stat()._iMP);
	}
	else
	{
		m_pCharacter = nullptr;
		Set_Close();
	}
	Update_Rect();
}
