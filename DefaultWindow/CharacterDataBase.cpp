#include "stdafx.h"
#include "CharacterDataBase.h"
#include "BmpMgr.h"

CCharacterDataBase* CCharacterDataBase::m_pInstance = nullptr;
CCharacterDataBase::CCharacterDataBase()
{
}
CCharacterDataBase::~CCharacterDataBase()
{
	Release();
}

void CCharacterDataBase::Initialize()
{
	CHARACTER_DATA* tData;

#pragma region PLAYER
	{
		tData = new CHARACTER_DATA;
		tData->tStat._dwAttackDelay = 2000;
		tData->tStat._iAttak = 123;
		tData->tStat._iMagicAttack = 123;
		tData->tStat._iHP = 1050;
		tData->tStat._iMP = 225;
		tData->tStat._iMaxHP = 1200;
		tData->tStat._iMaxMP = 300;
		tData->tStat._fAttackRange = 0;
		tData->tStat._iDodgeChance = 200;
		tData->tStat._iCritChance = 200;
		tData->tStat._fCritMultiplier = 2.f;
		tData->tStat._fSpeed = 3.5f;

		tData->tInfo.fCX = TILECX;
		tData->tInfo.fCY = TILECY;
		tData->tInfo.fRX = 100;
		tData->tInfo.fRY = 100;


		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		vector<int>* pVec;
		pVec = new vector<int>; pVec->push_back(0);
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{L"Player_Body_Idle", 0,0,0,200,0,true,true,pVec} });
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{L"Player_Body_Walk", 0,5,0,100,0,true,true,nullptr} });
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{L"Player_Body_Run", 0,7,0,100,0,true,true,nullptr} });
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Body_Battle", 0,7,0,150,0,true,true,nullptr} });
		pVec = new vector<int>; pVec->push_back(5);
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Body_CritAttack", 0,14,0,50,0,false,false, pVec} });
		pVec = new vector<int>; pVec->push_back(4);
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Body_NormalAttack", 0,7,0,50,0,false,false,pVec} });
		pVec = new vector<int>; pVec->push_back(4);
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Body_SnapAttack", 0,6,0,50,0,false,false, pVec} });
		pVec = new vector<int>; pVec->push_back(10); pVec->push_back(12); pVec->push_back(14); pVec->push_back(16); pVec->push_back(18); pVec->push_back(20);
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Charge_Attack", 0,20,0,100,0,false,false,pVec} });
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{L"Player_Body_Drill", 0,5,0,100,0,true,true, nullptr} });
		//Hit
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Body_Hit", 0,2,0,100,0,false,true, nullptr} });
		//DODGE
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Player_Body_Hit", 0,3,5,100,0,false,true, nullptr} });
		//DEAD
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{L"Player_Body_Hit", 0,1,4,100,0,true,true, nullptr} });
		//Grooming
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{L"Player_Body_Grooming", 0,1,7,100,0,false,true, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = -30;

		m_pPlayerData = tData;
	}
#pragma endregion
#pragma region MUMMY
	
	{
		tData = new CHARACTER_DATA;
		tData->tStat._dwAttackDelay = 3000;
		tData->tStat._iAttak = 30;
		tData->tStat._iMagicAttack = 0;
		tData->tStat._iHP = 600;
		tData->tStat._iMP = 600;
		tData->tStat._iMaxHP= 600;
		tData->tStat._iMaxHP= 600;
		tData->tStat._fAttackRange = TILECX * 1.5f;
		tData->tStat._iDodgeChance = 0.f;
		tData->tStat._iCritChance = 0.f;
		tData->tStat._fCritMultiplier = 2.f;
		tData->tStat._fSpeed = 2.f;

		tData->tInfo.fCX = TILECX;
		tData->tInfo.fCY = TILECY;
		tData->tInfo.fRX = 128;
		tData->tInfo.fRY = 128;

		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		vector<int>* pQueue;
		//IDLE
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{ L"Monster_Mummy",0,7,0,200,0,true,true,nullptr} });
		//WALK
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{ L"Monster_Mummy",0,5,4,200,0,true,true, nullptr} });
		pQueue = new vector<int>; pQueue->push_back(3);
		//ATTACK
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{ L"Monster_Mummy",0,6,12,100,0,false,false,pQueue } });
		//HIT
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{ L"Monster_Mummy",0,2,16,100,0,false,true, nullptr} });
		//DEAD
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{ L"Monster_Mummy",0,7,20,100,0,false,false, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = -30;
		tData->pName = L"미라";
		tData->m_eID = (int)MONSTER_ID::MUMMY;
		m_MonsterData.insert({ MONSTER_ID::MUMMY,tData });
	}
#pragma endregion
	
#pragma region DRAGON
	{
		tData = new CHARACTER_DATA;
		tData->tStat._dwAttackDelay = 3000;
		tData->tStat._iAttak = 100;
		tData->tStat._iMagicAttack = 0;
		tData->tStat._iHP = 3000;
		tData->tStat._iMP = 0;
		tData->tStat._iMaxHP = 3000;
		tData->tStat._iMaxHP = 3000;
		tData->tStat._fAttackRange = TILECX * 4.f;
		tData->tStat._iDodgeChance = 0.f;
		tData->tStat._iCritChance = 0.f;
		tData->tStat._fCritMultiplier = 2.f;
		tData->tStat._fSpeed = 2.f;

		tData->tInfo.fCX = TILECX * 3;
		tData->tInfo.fCY = TILECY * 3;
		tData->tInfo.fRX = 550;
		tData->tInfo.fRY = 400;

		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		vector<int>* pQueue;
		//IDLE
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Monster_Dragon_Armored", 0,7,0,300,0,true,true,nullptr} });
		//WALK
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{L"Monster_Dragon_Armored", 0,7,4,200,0,true,true, nullptr} });
		//ATTACK
		pQueue = new vector<int>; pQueue->push_back(5);
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Monster_Dragon_Armored", 0,14,12,100,0,false,false,pQueue} });
		//FLY(DEAD)
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{L"Monster_Dragon_Armored", 0,11,16,400,0,false,false, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = -100;
		tData->pName = L"스파이시 드래곤";
		tData->m_eID = (int)MONSTER_ID::ARMORED_DRAGON;
		m_MonsterData.insert({ MONSTER_ID::ARMORED_DRAGON,tData });
	}
#pragma endregion
#pragma region UNARMORED DRAGOn
	{
		tData = new CHARACTER_DATA;
		tData->tStat._dwAttackDelay = 3000;
		tData->tStat._iAttak = 100;
		tData->tStat._iMagicAttack = 0;
		tData->tStat._iHP = 3000;
		tData->tStat._iMP = 3000;
		tData->tStat._iMaxHP = 3000;
		tData->tStat._iMaxHP = 3000;
		tData->tStat._fAttackRange = TILECX * 4.f;
		tData->tStat._iDodgeChance = 0.f;
		tData->tStat._iCritChance = 500;
		tData->tStat._fCritMultiplier = 2.f;
		tData->tStat._fSpeed = 2.f;

		tData->tInfo.fCX = TILECX * 3;
		tData->tInfo.fCY = TILECY * 3;
		tData->tInfo.fRX = 550;
		tData->tInfo.fRY = 450;

		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		vector<int>* pQueue;
		//IDLE
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Monster_Dragon_Unarmored1", 0,7,0,200,0,true,true,nullptr} });
		//WALK
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{L"Monster_Dragon_Unarmored1", 0,7,4,200,0,true,true, nullptr} });
		//ATTACK
		pQueue = new vector<int>; pQueue->push_back(2);
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"Monster_Dragon_Attack", 0,10,0,100,0,false,false,pQueue} });
		//DEAD
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{L"Monster_Dragon_Dead", 0,25,0,200,0,false,false, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = -150;
		tData->pName = L"스파이시 드래곤";
		tData->m_eID = (int)MONSTER_ID::UNARMORED_DRAGON;
		m_MonsterData.insert({ MONSTER_ID::UNARMORED_DRAGON,tData });
	}
#pragma endregion
#pragma region OCTOPUS

	{
		tData = new CHARACTER_DATA;
		tData->tStat._dwAttackDelay = 3000;
		tData->tStat._iAttak = 15;
		tData->tStat._iMagicAttack = 0;
		tData->tStat._iHP = 300;
		tData->tStat._iMP = 300;
		tData->tStat._iMaxHP = 300;
		tData->tStat._iMaxHP = 300;
		tData->tStat._fAttackRange = TILECX * 1.5f;
		tData->tStat._iDodgeChance = 0.f;
		tData->tStat._iCritChance = 0.f;
		tData->tStat._fCritMultiplier = 2.f;
		tData->tStat._fSpeed = 2.f;

		tData->tInfo.fCX = TILECX;
		tData->tInfo.fCY = TILECY;
		tData->tInfo.fRX = 200;
		tData->tInfo.fRY = 200;

		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		vector<int>* pQueue;
		//IDLE
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{ L"Monster_Octopus",0,0,0,200,0,true,true,nullptr} });
		//WALK
		tData->vecAnimData->push_back({ ANIM_TYPE::EIGHT_DIR,	{ L"Monster_Octopus",0,2,8,200,0,true,true, nullptr} });
		pQueue = new vector<int>; pQueue->push_back(3);
		//ATTACK
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{ L"Monster_Octopus",0,3,16,100,0,false,false,pQueue } });
		//HIT
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{ L"Monster_Octopus",0,1,20,250,0,false,true, nullptr} });
		//DEAD
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{ L"Monster_Octopus",0,3,24,200,0,false,false, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = 0;
		tData->pName = L"훌라문어";
		tData->m_eID = (int)MONSTER_ID::OCTOPUS;
		m_MonsterData.insert({ MONSTER_ID::OCTOPUS,tData });
	}
#pragma endregion

#pragma region MAID
	{
		tData = new NPC_DATA;
		tData->tInfo.fCX = TILECX;
		tData->tInfo.fCY = TILECY;
		tData->tInfo.fRX = 100;
		tData->tInfo.fRY = 100;
		tData->tStat._iHP = 300;
		tData->tStat._iMP = 300;
		tData->tStat._iMaxHP = 300;
		tData->tStat._iMaxHP = 300;
		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		queue<int>* pQueue;
		//IDLE
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"NPC_Maid"	, 0,0,0,200,0,true,true, nullptr} });
		//WALK
		tData->vecAnimData->push_back({ ANIM_TYPE::FOUR_DIR,	{L"NPC_Maid"	, 0,3,0,100,0,true,true,nullptr} });
		//HELLO
		tData->vecAnimData->push_back({ ANIM_TYPE::TWO_DIR,	{L"NPC_Maid"	, 0,3,0,100,0,false,false, nullptr} });
		//NOD
		tData->vecAnimData->push_back({ ANIM_TYPE::TWO_DIR,	{L"NPC_Maid"	, 0,1,0,200,0,false,false, nullptr} });
		//BLINKING
		tData->vecAnimData->push_back({ ANIM_TYPE::TWO_DIR,	{L"NPC_Maid"	, 0,7,0,200,0,false,false, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = -30;
		tData->pName = L"바니 메이드";
		NPC_DATA* pNpcData = (NPC_DATA*)tData;
		pNpcData->strConversation = L"안녕하세요? 저는 바니 메이드입니다.";
		pNpcData->QuestList.push_back(QUEST_ID::MAID_01);
		pNpcData->QuestList.push_back(QUEST_ID::MAID_02);
		pNpcData->hNPCLiustDC = BMP_INST->Find_Img(L"NPC_Maid_Ilust");
		m_NPCData.insert({ NPC_ID::MAID, pNpcData });
	}
#pragma endregion

#pragma region HUNTERGIRL
	{
		tData = new NPC_DATA;
		tData->tInfo.fCX = TILECX;
		tData->tInfo.fCY = TILECY;
		tData->tInfo.fRX = 48;
		tData->tInfo.fRY = 82;
		tData->tStat._iHP = 300;
		tData->tStat._iMP = 300;
		tData->tStat._iMaxHP = 300;
		tData->tStat._iMaxHP = 300;
		tData->vecAnimData = new vector<pair<ANIM_TYPE, FRAME>>;
		queue<int>* pQueue;
		//IDLE
		tData->vecAnimData->push_back({ ANIM_TYPE::ONE_DIR,	{L"NPC_Hunter"	, 0,5,0,400,0,true,true, nullptr} });

		tData->iRenderOffsetX = 0;
		tData->iRenderOffsetY = -30;
		tData->pName = L"몬스터 걸 유리";
		NPC_DATA* pNpcData = (NPC_DATA*)tData;
		pNpcData->strConversation = L"안녕하세요? 저는 몬스터 헌터 유리입니다. 몬스터 사냥 같이 하실래요??";
		pNpcData->QuestList.push_back(QUEST_ID::MONSTER_01);
		pNpcData->QuestList.push_back(QUEST_ID::MONSTER_02);
		pNpcData->hNPCLiustDC = BMP_INST->Find_Img(L"NPC_Hunter_Ilust");
		m_NPCData.insert({ NPC_ID::MONSTER_GIRL, pNpcData });
	}
#pragma endregion
}

void CCharacterDataBase::Release()
{
	for (auto& i : m_MonsterData)
	{
		Safe_Delete(i.second);
	}
}
