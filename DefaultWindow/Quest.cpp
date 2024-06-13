#include "stdafx.h"
#include "Quest.h"
#include "CItemMgr.h"
#include "QuestMgr.h"

CQuest::CQuest(QUEST_ID _eId)
{
	m_tQuestData =  *QUEST_INST->Get_Quest_Data(_eId);
}

CQuest::~CQuest()
{
}

void CQuest::On_Monster_Killed(MONSTER_ID _eMonsterID)
{
	if (m_tQuestData.m_eTargetMonster == _eMonsterID)
		m_iMonsterCount++;
}

bool CQuest::Check_Complete()
{
	if (m_tQuestData.m_eTargetMonster != MONSTER_ID::END)
	{
		if (m_tQuestData.m_iMonsterGoal <= m_iMonsterCount)
			return true;
	}
	else if (m_tQuestData.m_eTargetItem != ITEM_ID::END)
	{
		if (m_tQuestData.m_iItemGoal <= ITEM_INST->Get_Item_Count(m_tQuestData.m_eTargetItem))
			return true;
	}
	return false;
}

