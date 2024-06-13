#include "stdafx.h"
#include "UI.h"
#include "SoundMgr.h"

CUI::CUI()
{
}

CUI::CUI(int _iXSize, int _iYSize)
	:m_iXSize(_iXSize), m_iYSize(_iYSize)
{
}

CUI::CUI(int _iXPos, int _iYPos, int _iXSize, int _iYSize)
	:m_iXSize(_iXSize), m_iYSize(_iYSize), m_iXPos(_iXPos), m_iYPos(_iYPos)
{

}

CUI::~CUI()
{
}

void CUI::Update_Rect()
{
	int iXOffset=0, iYOffset = 0;
	if (m_pParent != nullptr)
	{
		iXOffset = m_pParent->Get_Rect().left;
		iYOffset = m_pParent->Get_Rect().top;
	}
	m_tRect.left =	iXOffset + m_iXPos ;
	m_tRect.top = iYOffset +  m_iYPos;
	m_tRect.right =  iXOffset + (m_iXPos + m_iXSize);
	m_tRect.bottom = iYOffset + (m_iYPos + m_iYSize);
}

CUI* CUI::On_Drag(POINT _pt)
{
	return nullptr;
}

CUI* CUI::On_Drop(CUI* _pt)
{
	return nullptr;
}

void CUI::On_Laid(CUI* _pSlot, POINT _pt)
{
}

void CUI::Set_Close()
{
	m_bClosed = true;
	SOUND_INST->StopSound(SOUND_UI);
	SOUND_INST->PlaySoundW(L"ui_user_close.wav", SOUND_UI, 1);
}

void CUI::Set_Open()
{
	m_bClosed = false;
	SOUND_INST->StopSound(SOUND_UI);
	SOUND_INST->PlaySoundW(L"ui_user_open.wav", SOUND_UI,1);
}
