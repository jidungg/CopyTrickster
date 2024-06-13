#pragma once
#include "Obj.h"
#include "Define.h"

class CEnvObj :
    public CObj
{
public:
    CEnvObj(ENV_DATA& _eEnvData, POINT _pt);
    ~CEnvObj();
    // CObj을(를) 통해 상속됨
    void Set_Common_Motion(COMMON_STATE _eState) override;
    void Render(HDC hdc);
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Release() override;
    void Change_Motion() override;
    void On_Motion_End() override;
    void Motion_Func() override;
    void Interaction(CObj* _pObj) override;

private:
    HDC m_hDC;
};

