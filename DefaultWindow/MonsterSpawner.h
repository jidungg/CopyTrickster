#pragma once
#include "Monster.h"

class CMonsterSpawner
{
public:
	CMonsterSpawner(DWORD _delay, POINT _pos, MONSTER_ID _eID);
	~CMonsterSpawner();

	void Initialize();
	void Update();
	void Release();

	void SpawnMonster();
	void ResetTime();
private:
	DWORD m_dwSpawnDelay;
	DWORD m_dwDeadTime=0;
	CMonster* m_pMonster = nullptr;
	POINT m_tPosition;
	CHARACTER_DATA* m_tMonData;
	bool m_bSpawn = true;
	MONSTER_ID m_eMonID;
};

