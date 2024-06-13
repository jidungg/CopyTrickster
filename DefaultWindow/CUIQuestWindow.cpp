#include "stdafx.h"
#include "CUIQuestWindow.h"
#include "QuestMgr.h"
#include "CharacterDataBase.h"
#include "UIMgr.h"
#include "CItemMgr.h"

CUIQuestWindow::CUIQuestWindow(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive, HDC hQuestSide)
	:CWindow(WINDOW_ID::QUEST, _iXPos, _iYPos, _iXSize, _iYSize, hActive, hDeactive, hMinActive, hMinDeactive), m_hQuestSideDC(hQuestSide)
{
	POINT pt = m_tFirstRowPt;
	m_pAcceptedQuests = QUEST_INST->Get_Accepted_Quests();
	for (int i = 0; i < m_iRowCount; i++)
	{
		auto pRow = new CUIQuestRow(pt, QUEST_ID::END);
		m_vecQuestRow.push_back(pRow);
		pt.y += m_iRowGap;
		m_vecComponents.push_back(pRow);
		pRow->Set_Parent(this);
	}
	Reset_Quest();
}

void CUIQuestWindow::Update()
{
	CWindow::Update();

	int iIdx = 0;
	for (auto& i : *m_pAcceptedQuests)
	{
		m_vecQuestRow[iIdx++]->Set_Quest(i.first);

	}
	for (; iIdx < m_vecQuestRow.size(); iIdx++)
	{
		m_vecQuestRow[iIdx]->Set_Quest(QUEST_ID::END);
	}
}

void CUIQuestWindow::Update_Rect()
{
	CWindow::Update_Rect();
	m_tSideRect = { m_tRect.right + 1, m_tRect.top,
	m_tRect.right + 1 + m_iSideCX , m_tRect.top + m_iSideCY };
}

void CUIQuestWindow::Release()
{
	CWindow::Release();
	for (auto& i : m_vecQuestRow)
	{
		Safe_Delete(i);
	}
	m_vecQuestRow.clear();
}

void CUIQuestWindow::Render_Content(HDC hdc)
{
	if (m_bClosed)
		return;


	//사이드 윈도우
	GdiTransparentBlt(hdc,
		m_tSideRect.left, m_tSideRect.top,
		m_iSideCX, m_iSideCY,
		m_hQuestSideDC,
		0, 0, m_iSideCX, m_iSideCY,
		MAGENTA);
	QUEST_ID eID = m_vecQuestRow[m_iCurSelected]->Get_Quest();
	if (eID == QUEST_ID::END)
		return;
	QUEST_DATA& tQuest = (*m_pAcceptedQuests)[eID]->Get_Data();
	wstring str;
	RECT rt;
	//이름
	TextOut(hdc, m_tRect.left+ m_tSideTitle.x,m_tRect.top+ m_tSideTitle.y,
		tQuest.m_strName.c_str(), tQuest.m_strName.size());
	//의뢰자
	TextOut(hdc, m_tRect.left + m_tClientIndex.x, m_tRect.top + m_tClientIndex.y,
		L"의뢰자", 3);
	TextOut(hdc, m_tRect.left+ m_tClient.x,m_tRect.top+ m_tClient.y,
		CHARDB_INST->Get_NPC_Data(tQuest.m_eClient)->pName, _tcslen(CHARDB_INST->Get_NPC_Data(tQuest.m_eClient)->pName));
	//내용
	rt = { m_tContentIndex.left + m_tRect.left, m_tContentIndex.top + m_tRect.top,
			m_tRect.left + m_tContentIndex.right, m_tRect.top + m_tContentIndex.bottom };
	DrawText(hdc, L"내용", 2, &rt, DT_VCENTER|DT_SINGLELINE | DT_CENTER);
	int iGoal= 0, iCount= 0;
	if (tQuest.m_iMonsterGoal > 0)
	{
		iGoal = tQuest.m_iMonsterGoal;
		iCount = (*m_pAcceptedQuests)[eID]->Get_Count();
	}
	else if (tQuest.m_iItemGoal > 0) 
	{
		iGoal = tQuest.m_iItemGoal;
		iCount = ITEM_INST->Get_Item_Count(tQuest.m_eTargetItem);
	}
	str = tQuest.m_strContent +L'\n' + to_wstring(iCount) + L'/' + to_wstring(iGoal);
	rt = { m_tContent.left + m_tRect.left, m_tContent.top + m_tRect.top,
			m_tRect.left + m_tContent.right, m_tRect.top + m_tContent.bottom };
	DrawText(hdc, str.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);

	//보상
	rt = { m_tRewardIndex.left + m_tRect.left, m_tRewardIndex.top + m_tRect.top,
		m_tRect.left + m_tRewardIndex.right, m_tRect.top + m_tRewardIndex.bottom };
	DrawText(hdc, L"보상", 2, &rt, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	str = L"EXP: ";
	str += to_wstring(tQuest.m_tReward.m_iExp);
	str += L"/ 겔더: " + to_wstring(tQuest.m_tReward.m_iGelder);
	TextOut(hdc, m_tRect.left + m_tRewardEXP.x, m_tRect.top + m_tRewardEXP.y,
		str.c_str(), str.length());
	int idx = 0;
	for (auto& i : tQuest.m_tReward.m_eItemList)
	{
		POINT pt = m_tRewardItem;
		pt.x = idx * SLOT_CX + m_tRewardItem.x + m_tRect.left;
		pt.y =m_tRewardItem.y + m_tRect.top;
		UI_INST->PrintItemIcon(hdc, pt,i.first );
		str = to_wstring(i.second);
		TextOut(hdc, pt.x + 20, pt.y + 15, str.c_str(), str.length());
		idx++;
	}
	rt = { m_tConversation.left + m_tRect.left, m_tConversation.top + m_tRect.top,
	m_tRect.left + m_tConversation.right, m_tRect.top + m_tConversation.bottom};
	DrawText(hdc, tQuest.m_strConversation.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
}

CUI* CUIQuestWindow::On_Mouse_Up(POINT _pt)
{

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
	int idx = 0;
	for (auto& i : m_vecQuestRow)
	{
		if (PtInRect(&i->Get_Rect(), _pt))
		{
			for (auto& j : m_vecQuestRow)
			{
				j->Set_Activate(false);
			}
			i->On_Click(_pt);
			m_iCurSelected = idx;
			return nullptr;
		}
		idx++;
	}
	return nullptr;
}

void CUIQuestWindow::Reset_Quest()
{
	int iIdx = 0;
	for (auto& i : *m_pAcceptedQuests)
	{
		m_vecQuestRow[iIdx++]->Set_Quest(i.first);

	}
}

