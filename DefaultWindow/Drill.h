#pragma once
#include "Skill.h"
class CDrill :
    public CSkill
{
    // CSkill을(를) 통해 상속됨
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;
    void Motion_Func() override;
    void Motion_End() override;
};

