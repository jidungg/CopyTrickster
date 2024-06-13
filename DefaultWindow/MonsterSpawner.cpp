#include "stdafx.h"
#include "MonsterSpawner.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Dragon.h"
#include "CharacterDataBase.h"
#include "UnarmoredDragon.h"


CMonsterSpawner::CMonsterSpawner(DWORD _delay, POINT _pos, MONSTER_ID _eID)
	: m_dwSpawnDelay(_delay), m_tPosition(_pos), m_eMonID(_eID)
{
	m_tMonData= CHARDB_INST->Get_Monster_Data(_eID);
}

CMonsterSpawner::~CMonsterSpawner()
{
	Release();
}

void CMonsterSpawner::Initialize()
{
	
}


void CMonsterSpawner::Update()
{
	if (m_bSpawn && (m_dwDeadTime + m_dwSpawnDelay )< g_dwTime)
	{
		SpawnMonster();
		m_bSpawn = false;
	}
}

void CMonsterSpawner::Release()
{
	//Safe_Delete(m_pMonster);
	//Safe_Delete(m_tMonData);
}

void CMonsterSpawner::SpawnMonster()
{
	switch (m_eMonID)
	{
	case MONSTER_ID::ARMORED_DRAGON:
		m_pMonster = new CDragon;
		break;
	case MONSTER_ID::UNARMORED_DRAGON:
		m_pMonster = new CUnarmoredDragon;
		break;
	default:
		m_pMonster = new CMonster();
		break;
	}
	m_pMonster->Set_Data(m_tMonData);
	m_pMonster->Initialize();
	m_pMonster->Set_Pos(m_tPosition.x,m_tPosition.y);
	m_pMonster->Set_Spawner(this);
	m_pMonster->Make_Stop();
	OBJ_INST->Add_Object(OBJ_MONSTER, m_pMonster);
}

void CMonsterSpawner::ResetTime()
{
	m_dwDeadTime = g_dwTime;  
	m_bSpawn = true;
}
