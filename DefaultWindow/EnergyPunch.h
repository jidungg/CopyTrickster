#pragma once
#include "Skill.h"
class CEnergyPunch :
    public CSkill
{
public:
    CEnergyPunch();
    // CSkill을(를) 통해 상속됨
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;

    // CSkill을(를) 통해 상속됨
    void Motion_Func() override;
    void Motion_End() override;
};

