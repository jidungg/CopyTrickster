#pragma once
#include "Button.h"

class CWindow;
enum class WIN_BUTTON_TYPE
{
    UNMINIMALIZE,
    MINIMALIZE,
    CLOSE,
    OPEN,
    END
};

class CWindowBasicButton :
    public CButton
{
public:
    CWindowBasicButton() = default;
    CWindowBasicButton(WIN_BUTTON_TYPE _eType, CWindow* _pWnd, int _iXPos, int _iYPos, int _iXSize, int _iYSize);
    ~CWindowBasicButton();

    void Render(HDC hdc) override;
    CUI* On_Click(POINT _pt) override;
    CUI* On_Mouse_Up(POINT _pt) override;
    CUI* On_Mouse_Down(POINT _pt) override;
    CUI* On_Mouse_Press(POINT _pt) override;
  

    void Set_Window(CWindow* _pWnd) { m_pWindow = _pWnd; }
    void Set_Type(WIN_BUTTON_TYPE _eType) { m_eWinButtonType = _eType; }
private:
    WIN_BUTTON_TYPE m_eWinButtonType;
    CWindow* m_pWindow;


    // CButton을(를) 통해 상속됨

};

