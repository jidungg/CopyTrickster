#pragma once
#include "Skill.h"
#include "Obj.h"

class CTrippleAttack :
    public CSkill
{
public:
    CTrippleAttack();
   
    // CSkill��(��) ���� ��ӵ�
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;
    void Motion_Func() override;
    void Motion_End() override;
};

