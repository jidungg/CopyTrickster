#pragma once
#include "UI.h"
class CUIGuageFrame :
    public CUI
{
public:
    CUIGuageFrame( int _iLeftX, int _iLeftY, int _iMidX, int _MidY,HDC _leftDC, HDC _midDC, HDC _rightDC);
    ~CUIGuageFrame();
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    CUI* On_Click(POINT _pt) override;
    CUI* On_Mouse_Down(POINT _pt) override;
    CUI* On_Mouse_Up(POINT _pt) override;
    CUI* On_Mouse_Press(POINT _pt) override;
private:
    int m_iLeftX;
    int m_iLeftY;
    int m_iMidX;
    int m_iMidY;
    HDC m_hFrameLeftDC;
    HDC m_hFrameRightDC;
    HDC m_hFrameMidDC;
};

