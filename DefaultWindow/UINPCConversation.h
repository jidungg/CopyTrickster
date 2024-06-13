#pragma once
#include "Window.h"
#include "NPC.h"
#include <string>

class CConvOptionText
{
public :
    CConvOptionText( RECT _tRect, OPTION* _pOption);
    ~CConvOptionText();
    void Render(HDC hdc);
    void Release();
    RECT Get_Rect() { return m_tRect; }
    void Set_Option(OPTION* _pOpt) { m_pOption = _pOpt; }
    OPTION* Get_Option() { return m_pOption; }

private:
    RECT m_tRect;
    OPTION* m_pOption;
};

class CUINPCConversation :
    public CWindow
{
public:
    CUINPCConversation();
    ~CUINPCConversation();
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

    void Set_Balloon_DC(HDC _hdc) { m_hConversationBaloonDC = _hdc; }
    void Set_Illust_DC(HDC _hdc) { m_hIllustDC = _hdc; }
    void Set_NPC(CNPC* _pNPC);
    void Set_Quest(QUEST_ID _eQuestID);
    void Select_Option(int _iIdx);
    void ResetData();
    void ClearOptions();
    void Add_Option(wstring _str, CONV_OPTION_TYPE _eType, QUEST_ID _eQID = QUEST_ID::END);
    RECT Get_Nth_OptionRect(int _iIdx);
private:
    int m_iConversationBoxOffX = 0;
    int m_iConversationBoxOffY = WINCY - ILLUST_Y - NPC_BALLOON_Y;
    int m_iOptionOffX = 12;
    int m_iOptionOffY = 132;
    int m_iOptionSizeX = 280;
    int m_iOptionRectGap = 18;

    HDC m_hConversationBaloonDC;
    HDC m_hIllustDC;
    wstring m_strName;
    RECT m_tNameRect;
    RECT m_tConversationRect;
    CNPC* m_pNPC;

    wstring m_strConversation;
    vector< CConvOptionText*> m_vecOptionText;
};

