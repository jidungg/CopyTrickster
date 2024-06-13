#pragma once
#include "Monster.h"
class CUnarmoredDragon :
    public CMonster
{
public:
    void Initialize() override;
    void Set_Common_Motion(COMMON_STATE _eState) override;

	void Interaction(CObj* _pObj) override;
	void On_Move() override;
	void On_Noting() override;
	void On_Move_End() override;
	void On_Hit(CCharacter* _pObj, int _iDamage) override;
	void On_Kill(CCharacter* _pObj) override;
	void On_Dead(CCharacter* _pObj) override;
	void On_Range() override;
    void On_Motion_End() override;

	void Select_Skill();

private:
    bool m_bFlying = false;
};

