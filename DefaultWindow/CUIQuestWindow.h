#pragma once
#include "Window.h"
#include "UIQuestRow.h"
#include "Quest.h"

class CUIQuestWindow :
    public CWindow
{
public:
    CUIQuestWindow(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive, HDC hQuestSide);
    ~CUIQuestWindow() { Release(); }
    void Update() override;
    void Update_Rect() override;
    void Release() override;
    void Render_Content(HDC hdc)override;
    CUI* On_Mouse_Up(POINT _pt) override;
    void Reset_Quest();
private:
    HDC m_hQuestSideDC;
    //ªÁ¿ÃµÂ : 298, 323
    RECT m_tSideRect;
    
    POINT m_tFirstRowPt = { 8,45 };
    int m_iSideCX = 298;
    int m_iSideCY = 323;
    int m_iRowGap = 22;
    int m_iRowCount = 12;
    vector<CUIQuestRow*> m_vecQuestRow;
    map<QUEST_ID, CQuest*>* m_pAcceptedQuests;
    int m_iCurSelected = 0;

    POINT m_tSideTitle = { 332,9 };
    POINT m_tClientIndex = { 332,26 };
    POINT m_tClient = { 380,26 };
    RECT m_tContentIndex = { 332,61,375,115 };
    RECT m_tContent = { 380,61, 608,115};
    RECT m_tRewardIndex = { 332,120,375,165};
    POINT m_tRewardEXP = { 380,120};
    POINT m_tRewardItem = { 383,137};
    RECT m_tConversation = { 332,193, 608,312};
};

