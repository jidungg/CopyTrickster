#pragma once
#include "Monster.h"

class CDragon : public CMonster
{

public:
	CDragon();
	~CDragon();

	void On_Move() override;
	void On_Noting() override;
	void On_Move_End() override;
	void On_Hit(CCharacter* _pObj, int _iDamage) override;
	void On_Kill(CCharacter* _pObj) override;
	void On_Dead(CCharacter* _pObj) override;
	void On_Motion_End() override;
	void Motion_Func() override;
	void Set_Common_Motion(COMMON_STATE _eState) override;
private:


	// CMonster을(를) 통해 상속됨
	void Interaction(CObj* _pObj) override;

};

