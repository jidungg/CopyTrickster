#include "stdafx.h"
#include "UINPCConversation.h"
#include "BmpMgr.h"
#include "QuestMgr.h"
#include "CharacterDataBase.h"

CUINPCConversation::CUINPCConversation()
{
}

CUINPCConversation::~CUINPCConversation()
{
    Release();
}

void CUINPCConversation::Initialize()
{
    m_iOrder = m_iStaticOrder++;
    m_hConversationBaloonDC = BMP_INST -> Find_Img(L"UI_NPC_Balloon");
    m_bClosed = true;
    m_tNameRect = { 8,WINCY - ILLUST_Y - NPC_BALLOON_Y + 5, 295,WINCY - ILLUST_Y - NPC_BALLOON_Y +20 };
    m_tConversationRect = { 8,WINCY - ILLUST_Y - NPC_BALLOON_Y +25,292,WINCY - ILLUST_Y - NPC_BALLOON_Y +232 };
    m_tRect.left = 0;
    m_tRect.top = WINCY - ILLUST_Y - NPC_BALLOON_Y;
    m_tRect.right = NPC_BALLOON_X;
    m_tRect.bottom = WINCY;
    m_pCloseButton = nullptr;
    m_pMimimalizeButton = nullptr;
}

void CUINPCConversation::Update()
{


}

void CUINPCConversation::Late_Update()
{
}

void CUINPCConversation::Render(HDC hdc)
{
    if (m_bClosed)
        return;
    //일러스트
    GdiTransparentBlt(hdc, 0, WINCY - ILLUST_Y, ILLUST_X, ILLUST_Y,
        m_hIllustDC, 0,0,ILLUST_X, ILLUST_Y, MAGENTA);
    //말풍선
    GdiTransparentBlt(hdc, 2, m_iConversationBoxOffY, NPC_BALLOON_X, NPC_BALLOON_Y,
        m_hConversationBaloonDC, 0, 0, NPC_BALLOON_X, NPC_BALLOON_Y, MAGENTA);
    //이름
    DrawText(hdc, m_strName.c_str(),m_strName.length(),&m_tNameRect,DT_SINGLELINE | DT_LEFT);
    //대화내용
    DrawText(hdc, m_strConversation.c_str(), m_strConversation.length(), &m_tConversationRect, DT_LEFT | DT_WORDBREAK);

    for (auto& i : m_vecOptionText)
    {
        i->Render(hdc);
    }
}

void CUINPCConversation::Release()
{
    for (auto i : m_vecOptionText)
    {
        Safe_Delete(i);
    }
    m_vecOptionText.clear();
}

CUI* CUINPCConversation::On_Click(POINT _pt)
{
    return nullptr;
}

CUI* CUINPCConversation::On_Mouse_Down(POINT _pt)
{
    Set_Top();
    return nullptr;
}

CUI* CUINPCConversation::On_Mouse_Up(POINT _pt)
{
    for (int i = 0; i < m_vecOptionText.size(); i++)
    {
        if (PtInRect(&m_vecOptionText[i]->Get_Rect(), _pt))
        {
            Select_Option(i);
            return nullptr;
        }
    }
    return nullptr;
}

CUI* CUINPCConversation::On_Mouse_Press(POINT _pt)
{
    return nullptr;
}

void CUINPCConversation::Set_NPC(CNPC* _pNPC)
{
    ResetData();
    m_pNPC = _pNPC;
    m_strName = m_pNPC->Get_Name();
    m_strConversation = m_pNPC->Get_Conversation_Str();
    m_hIllustDC = _pNPC->Get_Illust_DC();


    CConvOptionText* pOptionText;
    RECT tRect = { m_iConversationBoxOffX + m_iOptionOffX,
        m_iConversationBoxOffY + m_iOptionOffY,
        m_iConversationBoxOffX + m_iOptionOffX  + m_iOptionSizeX ,
         m_iConversationBoxOffY + m_iOptionOffY  + m_iOptionRectGap };
    auto pList = m_pNPC->Get_Quests();
    for (auto& i : *pList)
    {
        OPTION* pOption;
        pOption = new OPTION;
        pOption->eOptType = CONV_OPTION_TYPE::QUEST;
        pOption->strText = QUEST_INST->Get_Quest_Data(i)->m_strName;
        pOption->eQuestID = QUEST_INST->Get_Quest_Data(i)->m_eQuestID;

        pOptionText = new CConvOptionText(tRect,pOption);
        m_vecOptionText.push_back(pOptionText);
        tRect.top += m_iOptionRectGap;
        tRect.bottom += m_iOptionRectGap;
    }

    if (false == m_pNPC->Get_StoreList()->empty())
    {
        OPTION* pOption;
        pOption = new OPTION;
        pOption->eOptType = CONV_OPTION_TYPE::STORE;
        pOption->strText = L"상점";

        pOptionText = new CConvOptionText(tRect, pOption);
        m_vecOptionText.push_back(pOptionText);
        tRect.top += m_iOptionRectGap;
        tRect.bottom += m_iOptionRectGap;
    }

    {
        OPTION* pOption;
        pOption = new OPTION;
        pOption->eOptType = CONV_OPTION_TYPE::BYE;
        pOption->strText = L"안녕히 계세요.";
   
        pOptionText = new CConvOptionText(tRect, pOption);
        m_vecOptionText.push_back(pOptionText);
        tRect.top += m_iOptionRectGap;
        tRect.bottom += m_iOptionRectGap;
    }
}


void CUINPCConversation::Set_Quest(QUEST_ID _eQuestID)
{
    QUEST_DATA* pData =  QUEST_INST->Get_Quest_Data(_eQuestID);
    m_strConversation = pData->m_strConversation;
    ClearOptions();
    CConvOptionText* pOptionText;
    if (QUEST_INST->Is_Accepted(_eQuestID))
    {
        Add_Option(L"완료하기", CONV_OPTION_TYPE::COMPLETE, _eQuestID);
        Add_Option(L"다음에 올게요", CONV_OPTION_TYPE::BYE, _eQuestID);
    }
    else {

        Add_Option(L"수락하기", CONV_OPTION_TYPE::ACCEPT, _eQuestID);
        Add_Option(L"거절하기", CONV_OPTION_TYPE::BYE, _eQuestID);
    }

}

void CUINPCConversation::Select_Option(int _iIdx)
{
    OPTION* pOption = m_vecOptionText[_iIdx]->Get_Option();
    CONV_OPTION_TYPE eOptType = pOption->eOptType;

    switch (eOptType)
    {
        break;
    case CONV_OPTION_TYPE::STORE:
        //TODO : 상점 열기
    case CONV_OPTION_TYPE::QUEST:
        Set_Quest(pOption->eQuestID);
        break;
    case CONV_OPTION_TYPE::ACCEPT:
        QUEST_INST->AcceptQuest(pOption->eQuestID);
        m_bClosed = true;
        break;
    case CONV_OPTION_TYPE::COMPLETE:
        if (false == QUEST_INST->Complete_Quest(pOption->eQuestID))
        {
            m_strConversation = L"퀘스트 조건이 완료되지 않았거나, \n 인벤토리 가 가득 찼습니다.";
            ClearOptions();
            Add_Option(L"오케이", CONV_OPTION_TYPE::BYE);
        }
        else
        {

            m_pNPC->Clear_Quest(pOption->eQuestID);
            m_bClosed = true;
        }
        break;
    case CONV_OPTION_TYPE::BYE:
        m_bClosed = true;
        break;
    case CONV_OPTION_TYPE::END:
        break;
    default:
        break;
    }
}

void CUINPCConversation::ResetData()
{
    m_hIllustDC = NULL;
    m_strName = L"";
    m_strConversation = L"";
    m_pNPC = nullptr;
    Release();
}

void CUINPCConversation::ClearOptions()
{
    for (auto i : m_vecOptionText)
    {
        Safe_Delete(i);
    }
    m_vecOptionText.clear();
}

void CUINPCConversation::Add_Option(wstring _str, CONV_OPTION_TYPE _eType, QUEST_ID _eQID)
{
    OPTION* pOpt = new OPTION();
    pOpt->eOptType = _eType;
    pOpt->strText = _str;
    pOpt->eQuestID = _eQID;
    CConvOptionText* pOptionText = new CConvOptionText(Get_Nth_OptionRect(m_vecOptionText.size()), pOpt);
    m_vecOptionText.push_back(pOptionText);
}



RECT CUINPCConversation::Get_Nth_OptionRect(int _iIdx)
{
    RECT tRect = { m_iConversationBoxOffX + m_iOptionOffX  ,
    m_iConversationBoxOffY + m_iOptionOffY + _iIdx*m_iOptionRectGap,
    m_iConversationBoxOffX + m_iOptionOffX + m_iOptionSizeX ,
     m_iConversationBoxOffY + m_iOptionOffY + m_iOptionRectGap + _iIdx * m_iOptionRectGap };

    return tRect;
}

//===========================================================
CConvOptionText::CConvOptionText(RECT _tRect, OPTION* _pOption)
{
    m_tRect = _tRect;
    m_pOption = _pOption;
}

CConvOptionText::~CConvOptionText()
{
    Release();
}

void CConvOptionText::Render(HDC hdc)
{
    wstring str = L"- " +m_pOption->strText;
    DrawText(hdc, str.c_str(), str.length(), &m_tRect, DT_LEFT);

}

void CConvOptionText::Release()
{
   Safe_Delete(m_pOption);
}


