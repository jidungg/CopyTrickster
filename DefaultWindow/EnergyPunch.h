#pragma once
#include "Skill.h"
class CEnergyPunch :
    public CSkill
{
public:
    CEnergyPunch();
    // CSkill��(��) ���� ��ӵ�
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;

    // CSkill��(��) ���� ��ӵ�
    void Motion_Func() override;
    void Motion_End() override;
};

