#pragma once
#include "Define.h"
#include "string"

typedef struct tagQuestReward
{
	int m_iExp = 0;
	int m_iGelder = 0;
	list<pair<ITEM_ID,int>> m_eItemList;
}REWARD;
typedef struct tagQuestData
{
	QUEST_ID m_eQuestID = QUEST_ID::END;
	MONSTER_ID m_eTargetMonster = MONSTER_ID::END;
	ITEM_ID m_eTargetItem = ITEM_ID::END;
	NPC_ID m_eClient = NPC_ID::END;
	REWARD m_tReward;
	int m_iMonsterGoal = 0;
	int m_iItemGoal = 0;
	wstring m_strName;
	wstring m_strContent;
	wstring m_strConversation;
}QUEST_DATA;
class CQuest
{
public:
	CQuest(QUEST_ID _eId);
	~CQuest();

	void Set_Client(NPC_ID _eNPC) { m_tQuestData.m_eClient = _eNPC; }
	void Set_Client(REWARD _tReward) { m_tQuestData.m_tReward = _tReward; }
	void On_Monster_Killed(MONSTER_ID _eMonsterID);
	bool Check_Complete();
	QUEST_ID Get_QID() { return m_tQuestData.m_eQuestID; }
	QUEST_DATA Get_Data() { return m_tQuestData; }
	int Get_Count() { return m_iMonsterCount; }
protected:
	QUEST_DATA m_tQuestData;
	int m_iMonsterCount = 0;
};
