#pragma once
#include "Character.h"

class CMonsterSpawner;
class CMonster : public CCharacter
{
	
public:
	CMonster();
	virtual ~CMonster();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;

	void Release() override;

	void Interaction(CObj* _pObj) override;
	void On_Move() override;
	void On_Noting() override;
	void On_Move_End() override;
	void On_Hit(CCharacter* _pObj, int _iDamage) override;
	void On_Kill(CCharacter* _pObj) override;
	void On_Dead(CCharacter* _pObj) override;
	void On_Motion_End() override;
	void On_Range() override;
	void Set_Common_Motion(COMMON_STATE _eState) override;
	void Set_Data(CHARACTER_DATA* _tData);

	void Motion_Func() override;

	void Set_Spawner(CMonsterSpawner* _pSpawn) { m_pSpawner = _pSpawn; }
	MONSTER_ID Get_Monster_ID() { return m_eMonID; }
	void Set_Random_Dest();
protected:
	CMonsterSpawner* m_pSpawner = nullptr;

	MONSTER_ID m_eMonID;

	DWORD m_dwRandomDestTime = 0;
	DWORD m_dwRandomDestDelay = 4000;

};


