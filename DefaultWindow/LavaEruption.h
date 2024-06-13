#pragma once
#include "Skill.h"
class CLavaEruption :
    public CSkill
{
public:
    CLavaEruption();
    // CSkill을(를) 통해 상속됨
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;
    void Motion_Func() override;
    void Motion_End() override;
};

