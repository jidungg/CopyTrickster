#pragma once
#include "Skill.h"
class CSkillCrossBomb :
    public CSkill
{
public:
    CSkillCrossBomb();
protected:
    // CSkill��(��) ���� ��ӵ�
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;
    void Motion_Func() override;
    void Motion_End() override;
};

