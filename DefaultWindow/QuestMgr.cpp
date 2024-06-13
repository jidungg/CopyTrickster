#include "stdafx.h"
#include "QuestMgr.h"
#include "CItemMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"

CQuestMgr* CQuestMgr::m_pInstance = nullptr;

CQuestMgr::CQuestMgr()
{
}

CQuestMgr::~CQuestMgr()
{
	Release();
}

void CQuestMgr::Initialize()
{
	QUEST_DATA* pQuestData;
	{
		pQuestData = new QUEST_DATA;
		pQuestData->m_eQuestID = QUEST_ID::MAID_01;
		pQuestData->m_eClient = NPC_ID::MAID;
		pQuestData->m_eTargetItem = ITEM_ID::VINIL;
		pQuestData->m_iItemGoal = 2;
		pQuestData->m_strName = L"�ؾȰ� û��";
		pQuestData->m_strContent = L"��� ���� 2���� ����.";
		pQuestData->m_strConversation = L"�Ǽ������� �ؾȰ��� �����⸦ ���� ������ �����̿���. \nȯ���� ��ȣ�ϱ� ���� �����⸦ ġ���ֽø� ����ϰڽ��ϴ�.";
		pQuestData->m_tReward.m_eItemList.push_back({ ITEM_ID::BUNNY_EAR ,1});
		pQuestData->m_tReward.m_eItemList.push_back({ ITEM_ID::PINK_POTION, 5});
		pQuestData->m_tReward.m_eItemList.push_back({ ITEM_ID::BLUE_POTION, 5});
		pQuestData->m_tReward.m_iExp = 1000;
		pQuestData->m_tReward.m_iGelder = 500;
		m_QuestDB.insert({ pQuestData->m_eQuestID, pQuestData });
	}
	{
		pQuestData = new QUEST_DATA;
		pQuestData->m_eQuestID = QUEST_ID::MAID_02;
		pQuestData->m_eClient = NPC_ID::MAID;
		pQuestData->m_eTargetMonster = MONSTER_ID::OCTOPUS;
		pQuestData->m_iMonsterGoal = 5;
		pQuestData->m_strName = L"�Ƕ� ���� ��ġ";
		pQuestData->m_strContent = L"�Ƕ� ���� 5������ ������.";
		pQuestData->m_strConversation = L"�� �Ƕ� ��� �ʹ� �Ⱦ��. ���ߴ� �� �Ⱬ�ؿ�. 5������ �׿��ּ���.";
		pQuestData->m_tReward.m_eItemList.push_back({ ITEM_ID::DRILL, 1});
		pQuestData->m_tReward.m_iExp = 1000;
		pQuestData->m_tReward.m_iGelder = 500;
		m_QuestDB.insert({ pQuestData->m_eQuestID, pQuestData });
	}

	{
		pQuestData = new QUEST_DATA;
		pQuestData->m_eQuestID = QUEST_ID::MONSTER_01;
		pQuestData->m_eClient = NPC_ID::MONSTER_GIRL;
		pQuestData->m_eTargetMonster = MONSTER_ID::MUMMY;
		pQuestData->m_iMonsterGoal = 5;
		pQuestData->m_strName = L"�̶� ��ġ";
		pQuestData->m_strContent = L"�̶� 5������ ������.";
		pQuestData->m_strConversation = L"���� �ڰ� ���� ����� ���ϰ� �־��. �� �׿��ּ���. 5������.";
		pQuestData->m_tReward.m_eItemList.push_back({ ITEM_ID::HELMET, 1 });
		pQuestData->m_tReward.m_iExp = 1000;
		pQuestData->m_tReward.m_iGelder = 500;
		m_QuestDB.insert({ pQuestData->m_eQuestID, pQuestData });
	}
	{
		pQuestData = new QUEST_DATA;
		pQuestData->m_eQuestID = QUEST_ID::MONSTER_02;
		pQuestData->m_eClient = NPC_ID::MONSTER_GIRL;
		pQuestData->m_eTargetItem = ITEM_ID::SPOON;
		pQuestData->m_iItemGoal = 2;
		pQuestData->m_strName = L"�������� ����";
		pQuestData->m_strContent = L"�������� 2�� ���ؿ���.";
		pQuestData->m_strConversation = L"�� �Ծ�� �ϴµ� �������� �Ҿ���Ⱦ�. �� ���� ������.";
		pQuestData->m_tReward.m_eItemList.push_back({ ITEM_ID::TURTLE_BACK, 1 });
		pQuestData->m_tReward.m_iExp = 1000;
		pQuestData->m_tReward.m_iGelder = 500;
		m_QuestDB.insert({ pQuestData->m_eQuestID, pQuestData });
	}
	for (auto& i : m_QuestDB)
	{
		m_setAvailableQuests.insert(i.first);
	}
}

void CQuestMgr::Release()
{
	for (auto& i : m_QuestDB)
	{
		Safe_Delete(i.second);
	}
	for (auto& i : m_AcceptedQuests)
	{
		Safe_Delete(i.second);
	}
}

void CQuestMgr::On_Monster_Killed(MONSTER_ID _eMonsterID)
{
	for (auto& i : m_AcceptedQuests)
	{
		i.second->On_Monster_Killed(_eMonsterID);
	}
}

void CQuestMgr::AcceptQuest(QUEST_ID _eQID)
{
	m_AcceptedQuests.insert({ _eQID, new CQuest(_eQID) });
	SOUND_INST->PlaySoundW(L"etc_quest.wav",SOUND_UI,1);
}

void CQuestMgr::AbandonQuest(QUEST_ID _eQID)
{
	m_AcceptedQuests.erase(_eQID);
	m_setAvailableQuests.insert(_eQID);
}

bool CQuestMgr::Is_Accepted(QUEST_ID _eQID)
{
	return m_AcceptedQuests.find(_eQID) != m_AcceptedQuests.end();
}

bool CQuestMgr::Complete_Quest(QUEST_ID _eQID)
{
	if (Is_Accepted(_eQID) == false)
		return false;
	if (m_AcceptedQuests[_eQID]->Check_Complete())
	{


		bool bResult = Gain_Reward(_eQID);
		if (bResult)
		{
			auto& data = m_AcceptedQuests[_eQID]->Get_Data();
			if (data.m_eTargetItem != ITEM_ID::END )
			{
				ITEM_INST->Remove_From_Inventory(data.m_eTargetItem, data.m_iItemGoal);
			}
			m_setClearedQuests.insert(_eQID);
			Safe_Delete(m_AcceptedQuests[_eQID]);
			m_AcceptedQuests.erase(_eQID);

			SOUND_INST->PlaySoundW(L"etc_q_ok.wav", SOUND_UI, 1);
		}
		return bResult;
	}
	
	return false;
}

REWARD CQuestMgr::Get_Reward(QUEST_ID _eQID)
{
	
	return m_QuestDB[_eQID]->m_tReward;;
}

bool CQuestMgr::Gain_Reward(QUEST_ID _eQID)
{
	REWARD tReward = Get_Reward(_eQID);
	if (false == ITEM_INST->Check_Enough_Inventory(tReward.m_eItemList))
		return false;

	ITEM_INST->Gain_Gold(tReward.m_iGelder);
	(static_cast<CPlayer*>( OBJ_INST->Get_Player()))->Gain_Exp(tReward.m_iExp);
	for (auto& i : tReward.m_eItemList)
	{
		for (int j = 0; j < i.second; j++)
		{
			ITEM_INST->Add_To_Inventory(i.first);

		}
	}

	return true;
}
