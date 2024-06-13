#pragma once
#include "Window.h"
#include "Obj.h"
class CUIMinimap :
    public CUI
{
public :
    CUIMinimap(int _iXSize, int _iYSize);
    ~CUIMinimap();

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
private:
    SCENE_ID m_eScene;
    CObj* m_pPlayer;

    HDC m_hFrameDC;
    HDC m_hPortalDC;
    HDC m_hPlayerDC;
    map<SCENE_ID,HDC> m_MapDC;

    int m_iInnerXPos = 1;
    int m_iInnerYPos = 12;
    int m_iInnerXSize = 140;
    int m_iInnerYSize = 140;
    RECT m_tInnerRect;
    int     m_iPrintingXPos;
    int     m_iPrintingYPos;
    int     m_iPrintingXSize;
    int     m_iPrintingYSize;
    RECT     m_tPrintingRect; 

    int m_iPlayerSizeX = 21;
    int m_iPlayerSizeY = 19;
    map<SCENE_ID, pair<int,int>> m_MapSize;

    POINT m_tPrevPlayerPos;
    POINT m_tCurPlayerPos;
    int m_iXScroll = 0;
    int m_iYScroll = 0;

    int m_iPortalSizeX = 11;
    int m_iPortalSizeY = 12;
    FRAME m_tPortalFrame;
};

