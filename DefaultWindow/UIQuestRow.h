#pragma once
#include "UI.h"
#include "Button.h"


class CUIQuestRow :
    public CUI
{
public:
    CUIQuestRow(POINT _pt, QUEST_ID _eID);
    ~CUIQuestRow();
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Render(HDC hdc, QUEST_ID _eQuest );
    void Release() override;
    CUI* On_Click(POINT _pt) override;
    CUI* On_Mouse_Down(POINT _pt) override;
    CUI* On_Mouse_Up(POINT _pt) override;
    CUI* On_Mouse_Press(POINT _pt) override;
    void Set_Activate(bool _bActive) { m_bActivated = _bActive; }
    void Set_Quest(QUEST_ID _eQID) { m_eQID = _eQID; }
    QUEST_ID Get_Quest() { return m_eQID; }
private:
    bool m_bActivated = false;
    HDC m_hActivatedRowDC;
    CButton* m_AbandonButotn;
    POINT m_tAbandonButtonPoint = {283,2};
    QUEST_ID m_eQID;
};

