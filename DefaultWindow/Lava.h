#pragma once
#include "Obj.h"
class CLava :
    public CObj
{
public:
    CLava();
    // CObj을(를) 통해 상속됨
    void Set_Common_Motion(COMMON_STATE _eState) override;
    void Initialize() override;
    void Render(HDC hdc) override;
    int Update() override;
    void Late_Update() override;
    void Release() override;
    void Change_Motion() override;
    void On_Motion_End() override;
    void Motion_Func() override;
    void Interaction(CObj* _pObj) override;
    void On_Collision(CObj* _pObj) override;

private:
    HDC m_hBMPDC;
    int m_iAttack = 100;
};

