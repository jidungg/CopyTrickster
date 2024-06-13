#pragma once
#include "Quest.h"
#include <set>
class CQuestMgr
{
#pragma region Singleton
private:
	CQuestMgr();
	~CQuestMgr();

public:
	static CQuestMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CQuestMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CQuestMgr* m_pInstance;
#pragma endregion

public:
	void Initialize();
	void Release();
	void On_Monster_Killed(MONSTER_ID _eMonsterID);
	void AcceptQuest(QUEST_ID _eQID);
	void AbandonQuest(QUEST_ID _eQID);
	QUEST_DATA* Get_Quest_Data(QUEST_ID _eId) { return m_QuestDB[_eId]; }
	map<QUEST_ID, CQuest*>* Get_Accepted_Quests() { return &m_AcceptedQuests; }
	bool Is_Cleared(QUEST_ID _eQID) { return m_setClearedQuests.find(_eQID) != m_setClearedQuests.end(); }
	bool Is_Accepted(QUEST_ID _eQID);
	//퀘스트가 클리어됐는지 아닌지 반환. 
	bool Complete_Quest(QUEST_ID _eQID);
	REWARD Get_Reward(QUEST_ID _eQID);
	bool Gain_Reward(QUEST_ID _eQID);
private:
	map<QUEST_ID, CQuest*> m_AcceptedQuests;
	set<QUEST_ID> m_setClearedQuests;
	set<QUEST_ID> m_setAvailableQuests;
	map<QUEST_ID, QUEST_DATA*> m_QuestDB;
};

#define QUEST_INST CQuestMgr::Get_Instance()