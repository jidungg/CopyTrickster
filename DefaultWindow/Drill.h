#pragma once
#include "Skill.h"
class CDrill :
    public CSkill
{
    // CSkill��(��) ���� ��ӵ�
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;
    void Motion_Func() override;
    void Motion_End() override;
};

