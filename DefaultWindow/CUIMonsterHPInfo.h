#pragma once
#include "UI.h"
#include "Monster.h"
#include "CharacterHPBar.h"

class CUIMonsterHPInfo :
    public CUI
{
public:
    CUIMonsterHPInfo(int _iXPos, int _iYPos, int _iXSize, int _iYSize, int _iXMargin, int _iYMargin);
    ~CUIMonsterHPInfo();

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

    void Set_Monster(CObj* _pMonster);
private:

    CCharacterHPBar* m_pBar;
    CMonster* m_pMonster = nullptr;
    RECT m_tNameRect;
};

