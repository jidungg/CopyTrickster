#include "stdafx.h"
#include "UIMinimap.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "TileMgr.h"

CUIMinimap::CUIMinimap(int _iXSize, int _iYSize)
    :CUI(_iXSize, _iYSize)
{
    m_pPlayer = OBJ_INST->Get_Player();
    m_tPrevPlayerPos = m_pPlayer->Get_Point();
    m_tPrevPlayerPos.x /= 10;
    m_tPrevPlayerPos.y /= 10;

    m_iXPos = WINCX - _iXSize;
    m_iYPos = 0;
    m_hFrameDC = BMP_INST->Find_Img(L"UI_Minimap_Frame");
    m_hPortalDC = BMP_INST->Find_Img(L"UI_Minimap_Portal");
    m_hPlayerDC = BMP_INST->Find_Img(L"UI_Minimap_Player");
    m_MapDC.insert({ SCENE_ID::TOWN, BMP_INST->Find_Img(L"UI_Minimap_Town") });
    m_MapDC.insert({ SCENE_ID::ROAD, BMP_INST->Find_Img(L"UI_Minimap_Road") });
    m_MapDC.insert({ SCENE_ID::MAGMA, BMP_INST->Find_Img(L"UI_Minimap_Magma") });

    Update_Rect();
    m_tInnerRect = {
        m_tRect.left + m_iInnerXPos,
        m_tRect.top + m_iInnerYPos,
        m_tRect.left + m_iInnerXPos + m_iInnerXSize,
        m_tRect.top + m_iInnerYPos + m_iInnerYSize
    };

    m_MapSize.insert({ SCENE_ID::TOWN, {128,128} });
    m_MapSize.insert({ SCENE_ID::ROAD, {200,100} });
    m_MapSize.insert({ SCENE_ID::MAGMA, {160,160} });

    m_tPortalFrame.iFrameEnd = 3;
    m_tPortalFrame.iFrameStart = 0;
    m_tPortalFrame.dwSpeed = 200;
    m_tPortalFrame.dwTime = 0;
    m_tPortalFrame.bRepeat= true;

}

CUIMinimap::~CUIMinimap()
{
    Release();
}

void CUIMinimap::Initialize()
{
}

void CUIMinimap::Update()
{
    m_eScene = SCENE_INST->Get_Scene_ID();
    m_tCurPlayerPos = m_pPlayer->Get_Point();
    m_tCurPlayerPos.x /= 10;
    m_tCurPlayerPos.y /= 10;
}


void CUIMinimap::Late_Update()
{
    m_tPrintingRect = m_tInnerRect;
    m_iPrintingXPos = m_iInnerXPos;
    m_iPrintingYPos = m_iInnerYPos;
    m_iPrintingXSize = m_iInnerXSize;
    m_iPrintingYSize = m_iInnerYSize;
    //프레임 크기보다 맵이 더 작으면
    //프레임 크기를 내부로 재정비
    int iSizeDiffX = m_iInnerXSize - m_MapSize[m_eScene].first;
    int iSizeDiffY = m_iInnerYSize - m_MapSize[m_eScene].second;
    if (iSizeDiffX > 0)
    {
        m_tPrintingRect.left = m_tInnerRect.left +  iSizeDiffX / 2;
        m_tPrintingRect.right = m_tInnerRect.right -  iSizeDiffX / 2;
        m_iPrintingXPos = m_tPrintingRect.left;
        m_iPrintingXSize = m_MapSize[m_eScene].first;
    }
    if (iSizeDiffY > 0)
    {
        m_tPrintingRect.top = m_tInnerRect.top + iSizeDiffY / 2;
        m_tPrintingRect.bottom = m_tInnerRect.bottom - iSizeDiffY / 2;
        m_iPrintingYPos = m_tPrintingRect.top;
        m_iPrintingYSize = m_MapSize[m_eScene].second;
    }
    //스크롤
    int	iOffSetminX = m_iPrintingXSize / 2 - 10;
    int	iOffSetmaxX = m_iPrintingYSize / 2 + 10;

    int	iOffSetminY = m_iPrintingXSize / 2 - 10;
    int	iOffSetmaxY = m_iPrintingYSize / 2 + 10;

    int	iScrollX = m_iXScroll;
    int	iScrollY = m_iYScroll;
    int iXSpeed = m_tCurPlayerPos.x - m_tPrevPlayerPos.x;
    int iYSpeed = m_tCurPlayerPos.y - m_tPrevPlayerPos.y;
    //왼쪽으로 넘어감
    if (iOffSetminX > m_tCurPlayerPos.x + iScrollX)
        m_iXScroll += (abs(iXSpeed));
    //오른쪽으로 넘어감
    if (iOffSetmaxX < m_tCurPlayerPos.x + iScrollX)
        m_iXScroll+= (-abs(iXSpeed));
    //위쪽으로 넘어감
    if (iOffSetminY > m_tCurPlayerPos.y + iScrollY)
        m_iYScroll += (abs(iYSpeed));
    //아래쪽으로 넘어감
    if (iOffSetmaxY < m_tCurPlayerPos.y+ iScrollY)
        m_iYScroll += (-abs(iYSpeed));
    m_tPrevPlayerPos = m_tCurPlayerPos;

    //스크롤 락
    int MAPCX = m_MapSize[SCENE_INST->Get_Scene_ID()].first;
    int MAPCY = m_MapSize[SCENE_INST->Get_Scene_ID()].second;
    if (0 < m_iXScroll)
        m_iXScroll= 0;

    if (0 < m_iYScroll)
        m_iYScroll = 0;

    if (m_iPrintingXSize - MAPCX > m_iXScroll)
        m_iXScroll = m_iPrintingXSize - MAPCX;

    if (m_iPrintingYSize - MAPCY > m_iYScroll)
        m_iYScroll = m_iPrintingYSize - MAPCY;

    if (m_tPortalFrame.dwTime + m_tPortalFrame.dwSpeed < g_dwTime)
    {
        ++m_tPortalFrame.iFrameStart;
        if (m_tPortalFrame.iFrameStart > m_tPortalFrame.iFrameEnd)
        {
            if (m_tPortalFrame.bRepeat)
            {
                m_tPortalFrame.iFrameStart = 0;
            }
        }

        m_tPortalFrame.dwTime = g_dwTime;
    }
}

void CUIMinimap::Render(HDC hdc)
{
    //프레임 출력
    GdiTransparentBlt(hdc,
        m_iXPos, m_iYPos,
        m_iXSize, m_iYSize,
        m_hFrameDC,
        0,0,m_iXSize,m_iYSize, MAGENTA);
    //맵 출력
    SCENE_ID eSceneID = SCENE_INST->Get_Scene_ID();
    BitBlt(hdc,
        m_tPrintingRect.left, m_tPrintingRect.top,
        m_iPrintingXSize, m_iPrintingYSize,
        m_MapDC[eSceneID],
        -m_iXScroll, -m_iYScroll,
        SRCCOPY);
    //플레이어 출력
    GdiTransparentBlt(hdc,
        m_tPrintingRect.left + m_tCurPlayerPos.x + m_iXScroll - m_iPlayerSizeX/2,
        m_tPrintingRect.top + m_tCurPlayerPos.y + m_iYScroll - m_iPlayerSizeY / 2,
        m_iPlayerSizeX, m_iPlayerSizeY,
        m_hPlayerDC,
        0, 0, m_iPlayerSizeX, m_iPlayerSizeY,
        MAGENTA);
    //포탈 출력
    auto vecPortalTile = TILE_INST->Get_Tiles(TILE_TYPE::PORTAL);
    for (auto& i : *vecPortalTile)
    {
        POINT tPortalPoint = i->Get_Pos();
        tPortalPoint.x /= 10;
        tPortalPoint.y /= 10;
        if (tPortalPoint.x + m_iXScroll < 0 || tPortalPoint.x + m_iXScroll > m_iInnerXSize)
            continue;
        if (tPortalPoint.y + m_iYScroll < 0 || tPortalPoint.y + m_iYScroll > m_iInnerYSize)
            continue;
        GdiTransparentBlt(hdc,
            m_tPrintingRect.left + tPortalPoint.x + m_iXScroll - m_iPortalSizeX / 2,
            m_tPrintingRect.top + tPortalPoint.y + m_iYScroll - m_iPortalSizeY / 2,
            m_iPortalSizeX, m_iPortalSizeY,
            m_hPortalDC,
            m_iPortalSizeX* m_tPortalFrame.iFrameStart, 0,
            m_iPortalSizeX, m_iPortalSizeY,
            MAGENTA);
    }
    Safe_Delete(vecPortalTile);
}

void CUIMinimap::Release()
{
}

CUI* CUIMinimap::On_Click(POINT _pt)
{
    return nullptr;
}

CUI* CUIMinimap::On_Mouse_Down(POINT _pt)
{
    return nullptr;
}

CUI* CUIMinimap::On_Mouse_Up(POINT _pt)
{
    return nullptr;
}

CUI* CUIMinimap::On_Mouse_Press(POINT _pt)
{
    return nullptr;
}
