#pragma once
#include "Obj.h"
class CObjItem :
    public CObj
{
public:
    CObjItem(ITEM_ID _eID, POINT _pt);
    ~CObjItem();
    // CObj을(를) 통해 상속됨
    void Set_Common_Motion(COMMON_STATE _eState) override;
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void	Move_Frame() override;
    void Change_Motion() override;
    void On_Motion_End() override;
    void Motion_Func() override;
    void Interaction(CObj* _pObj) override;

private:
    ITEM_ID m_eItemID = ITEM_ID::END;
    HDC m_hIconDC;
    float m_fShootRad;
    float m_fShootSpeed = 1.f;
    DWORD m_dwStartTime;
};

