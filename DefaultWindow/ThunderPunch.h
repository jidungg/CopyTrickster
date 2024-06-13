#pragma once
#include "Skill.h"
class CThunderPunch :
    public CSkill
{
public:
    CThunderPunch();
    ~CThunderPunch();
    // CSkill을(를) 통해 상속됨
    void Update()override;
    virtual void Late_Update();
    virtual void Render(HDC hdc);
    void Func(CCharacter* _pObj, CCharacter* _pSbj) override;
    void Motion_Func() override;
    void Motion_End() override;
private:
    bool bThrust = false;
    float m_fSpeed = 30;
    float m_fXSpeed;
    float m_fYSpeed;
    POINT m_tNext;
    HDC m_hEffectDC;
    bool bAttacked = false;
};

