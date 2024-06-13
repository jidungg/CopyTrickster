#pragma once
#include "Obj.h"
class CPortal :
    public CObj
{
public:
    CPortal();
    ~CPortal();

    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Change_Motion() override;
    void On_Motion_End() override;
    void Motion_Func() override;
    void Interaction(CObj* _pObj) override;
    void Set_Scene(SCENE_ID _eSCene) { m_eScene = _eSCene; }
    void Set_Common_Motion(COMMON_STATE _eState) override;
    SCENE_ID Get_Scene() { return m_eScene; }
private:
    HDC m_hMemDC;
    SCENE_ID m_eScene;

};

