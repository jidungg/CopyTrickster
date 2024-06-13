#pragma once
#include "UI.h"
#include "UIGuageFrame.h"
#include "UIGuageFill.h"

class CCharacter;
class CCharacterHPBar :
    public CUI
{
public:
    CCharacterHPBar(int _iXPos, int _iYPos, int _iXSize, int _iYSize, int _iXBorderSize, int _iYBorderSize);
    ~CCharacterHPBar();

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

    void Set_Character(CCharacter* _pChar) { m_pCharacter = _pChar; m_bClosed = false; }
    void Set_Frame(CUIGuageFrame* _pFrame);
    void Set_Fill(CUIGuageFill* _pFill)  ;
protected:
    CCharacter* m_pCharacter = nullptr;
    CUIGuageFrame* m_pFrame = nullptr;
    CUIGuageFill* m_pFill = nullptr;
    int m_iBorderX;
    int m_iBorderY;
};

