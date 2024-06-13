#pragma once
#include "UI.h"

class CButton :
    public CUI
{

public:
    CButton() = default;
    CButton(TCHAR* _pFrameKey, int _iXPos, int _iYPos, int _iXSize, int _iYSize);
    CButton(HDC _hdc, int _iXPos, int _iYPos, int _iXSize, int _iYSize);
    ~CButton();

    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;

    // CUI을(를) 통해 상속됨
    CUI* On_Mouse_Down(POINT _pt) override;

    CUI* On_Mouse_Up(POINT _pt) override;

    CUI* On_Mouse_Press(POINT _pt) override;
    CUI* On_Click(POINT _pt) override;

    void Set_BMP(TCHAR* _pFrameKey);
    void Set_BMP(HDC _hDC) { m_hIconDC = _hDC; }
protected:
    HDC m_hIconDC;

    BUTTON_STATE m_ePrevState = BUTTON_STATE::END;
    BUTTON_STATE m_eCurState = BUTTON_STATE::NORMAL;
public:



};

