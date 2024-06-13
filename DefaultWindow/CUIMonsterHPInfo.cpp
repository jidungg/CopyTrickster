#include "stdafx.h"
#include "CUIMonsterHPInfo.h"
#include "BmpMgr.h"

CUIMonsterHPInfo::CUIMonsterHPInfo(int _iXPos, int _iYPos, int _iXSize, int _iYSize, int _iXMargin, int _iYMargin)
	:CUI(_iXPos,_iYPos, _iXSize,_iYSize)
{
	//32,9
	CCharacterHPBar* pUI = new CCharacterHPBar(0, 0, 225, 9, _iXMargin,_iYMargin);
	CUIGuageFrame* pFrame = new CUIGuageFrame(3, 52, 32, 52,
		BMP_INST->Find_Img(L"UI_MonsterHP_frame_Left"),
		BMP_INST->Find_Img(L"UI_MonsterHP_frame_Mid"),
		BMP_INST->Find_Img(L"UI_MonsterHP_frame_Right"));
	pUI->Set_Frame(pFrame);
	CUIGuageFill* pFIll = new CUIGuageFill(32, 7,
		BMP_INST->Find_Img(L"UI_MonsterHP_Fill_01"));
	pUI->Set_Fill(pFIll);
	m_pBar = pUI;
	pUI->Set_Parent(this);
	pUI->Set_Close();
	Update_Rect();
	m_pBar->Update_Rect();

	m_tNameRect = { m_tRect.left,m_tRect.top, m_tRect.right, m_tRect.top + _iYMargin };

}

CUIMonsterHPInfo::~CUIMonsterHPInfo()
{
}

void CUIMonsterHPInfo::Initialize()
{

}

void CUIMonsterHPInfo::Update()
{
	if (m_pMonster == nullptr || m_pMonster->Get_Dead())
	{
		m_pMonster = nullptr;
		return;
	}
	m_pBar->Update();

}

void CUIMonsterHPInfo::Late_Update()
{
}

void CUIMonsterHPInfo::Render(HDC hdc)
{
	if (m_pMonster == nullptr || m_pMonster->Get_Dead())
	{
		m_pMonster = nullptr;
		return;
	}
	m_pBar->Render(hdc);
	//Rectangle(hdc, m_tNameRect.left, m_tNameRect.top, m_tNameRect.right, m_tNameRect.bottom);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc,m_pMonster->Get_Name(), -1, &m_tNameRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void CUIMonsterHPInfo::Release()
{
}

CUI* CUIMonsterHPInfo::On_Click(POINT _pt)
{
	return nullptr;
}

CUI* CUIMonsterHPInfo::On_Mouse_Down(POINT _pt)
{
	return nullptr;
}

CUI* CUIMonsterHPInfo::On_Mouse_Up(POINT _pt)
{
	return nullptr;
}

CUI* CUIMonsterHPInfo::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}

void CUIMonsterHPInfo::Set_Monster(CObj* _pMonster)
{
	if (_pMonster->Get_ID() == OBJ_PORTAL)
	{
		m_pMonster = nullptr;
	}
	m_pBar->Set_Character((CCharacter*) _pMonster);
	m_pMonster = (CMonster*)_pMonster;
}
