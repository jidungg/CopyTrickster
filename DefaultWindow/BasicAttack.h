#pragma once
#include "Skill.h"

class CBasicAttack : public CSkill
{
public:
	CBasicAttack(DWORD dwCoolTime, float fRange);
	// CSkill을(를) 통해 상속됨
	void Func(CCharacter* _pObj, CCharacter* _pSbj) override;

	// CSkill을(를) 통해 상속됨
	void Motion_Func() override;
	void Motion_End() override;
};

