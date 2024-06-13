#pragma once
#include "Define.h"

class CCharacterDataBase
{
#pragma region Singleton
private:
	CCharacterDataBase();
	~CCharacterDataBase();

public:
	static CCharacterDataBase* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CCharacterDataBase;

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
	static CCharacterDataBase* m_pInstance;
#pragma endregion

public:
	void Initialize();
	void Release();

	CHARACTER_DATA* Get_Monster_Data(MONSTER_ID _eID) { return m_MonsterData[_eID]; }
	NPC_DATA* Get_NPC_Data(NPC_ID _eID) { return m_NPCData[_eID]; }
	CHARACTER_DATA* Get_Player_Data() { return m_pPlayerData; }
private:
	map<MONSTER_ID, CHARACTER_DATA*> m_MonsterData;
	map< NPC_ID, NPC_DATA*> m_NPCData;
	CHARACTER_DATA* m_pPlayerData;
};
#define CHARDB_INST CCharacterDataBase::Get_Instance()
 