#include "stdafx.h"
#include "UIQuestRow.h"
#include "MouseMgr.h"
#include "BmpMgr.h"
#include "QuestMgr.h"

CUIQuestRow::CUIQuestRow(POINT _pt, QUEST_ID _eID)
{
	m_eQID = _eID;
	m_iXPos = _pt.x;
	m_iYPos = _pt.y;
	m_iXSize = 304;
	m_iYSize = 18;
	m_hActivatedRowDC = BMP_INST->Find_Img(L"UI_Quest_Row_Active");

	m_AbandonButotn = new CButton(L"UI_Quest_Row_Button",283,2,17,15);
	m_AbandonButotn->Set_Parent(this);
}

CUIQuestRow::~CUIQuestRow()
{
	Release();
}

void CUIQuestRow::Initialize()
{
}

void CUIQuestRow::Update()
{
	Update_Rect();
	m_AbandonButotn->Update();
}

void CUIQuestRow::Late_Update()
{
	m_AbandonButotn->Late_Update();
}

void CUIQuestRow::Render(HDC hdc)
{
	Render(hdc, m_eQID);
}

void CUIQuestRow::Render(HDC hdc, QUEST_ID _eQuest)
{
	if (m_bActivated)
		GdiTransparentBlt(hdc,
			m_tRect.left, m_tRect.top, m_iXSize, m_iYSize,
			m_hActivatedRowDC,
			0, 0, m_iXSize, m_iYSize,
			MAGENTA);
	if (_eQuest == QUEST_ID::END)
		return;
	m_AbandonButotn->Render(hdc);
	QUEST_DATA* pQData = QUEST_INST->Get_Quest_Data(_eQuest);
	TextOut(hdc, m_tRect.left + 3, m_tRect.top + 3, pQData->m_strName.c_str(), pQData->m_strName.size());
}

void CUIQuestRow::Release()
{
	Safe_Delete(m_AbandonButotn);
}

CUI* CUIQuestRow::On_Click(POINT _pt)
{
	m_bActivated = true;
	if (PtInRect(&m_AbandonButotn->Get_Rect(), _pt))
	{
		QUEST_INST->AbandonQuest(m_eQID);
		m_eQID = QUEST_ID::END;
	}
	return nullptr;
}

CUI* CUIQuestRow::On_Mouse_Down(POINT _pt)
{
	return nullptr;
}

CUI* CUIQuestRow::On_Mouse_Up(POINT _pt)
{
	return nullptr;
}

CUI* CUIQuestRow::On_Mouse_Press(POINT _pt)
{
	return nullptr;
}
