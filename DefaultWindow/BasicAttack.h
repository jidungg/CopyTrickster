#pragma once
#include "Skill.h"

class CBasicAttack : public CSkill
{
public:
	CBasicAttack(DWORD dwCoolTime, float fRange);
	// CSkill��(��) ���� ��ӵ�
	void Func(CCharacter* _pObj, CCharacter* _pSbj) override;

	// CSkill��(��) ���� ��ӵ�
	void Motion_Func() override;
	void Motion_End() override;
};

