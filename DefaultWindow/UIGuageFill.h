#pragma once
#include "UI.h"
class CUIGuageFill :
    public CUI
{
public:
    CUIGuageFill( int _iSrcX, int _iSrcY, HDC _fillDC);
    ~CUIGuageFill();
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    CUI* On_Click(POINT _pt) override;
    CUI* On_Mouse_Down(POINT _pt) override;
    CUI* On_Mouse_Up(POINT _pt) override;
    CUI* On_Mouse_Press(POINT _pt) override;

    void Set_Val(int _i) { m_iVal = _i; }
    void Set_Max(int _i) { m_iMax= _i; }
private:
    HDC m_hFillDC;
    int m_iMax;
    int m_iVal;
    int m_iSrcX;
    int m_iSrcY;
};

