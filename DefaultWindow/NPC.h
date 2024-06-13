#pragma once
#include "Character.h"
class CNPC :
    public CCharacter
{
    enum STATE {IDLE, WALK, HELLO, NOD, BLINK, ST_END};
public:
    CNPC();
    ~CNPC();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Release() override;
    void On_Motion_End() override;
    void Motion_Func() override;
    void Interaction(CObj* _pObj) override;

    // CCharacter을(를) 통해 상속됨
    void On_Range() override;
    void On_Move() override;
    void On_Noting() override;
    void On_Move_End() override;

    // CCharacter을(를) 통해 상속됨
    void Set_Common_Motion(COMMON_STATE _eState) override;
    void Set_Data(CHARACTER_DATA* _tData) override;
    void Set_Ilust_DC(HDC _hdc) { m_hNPCLiustDC= _hdc; }
    list<QUEST_ID>* Get_Quests() { return &m_QuestList; }
    list<ITEM_ID>* Get_StoreList() { return &m_StoreItems; }
    NPC_ID Get_NPC_ID() { return m_eNPCID; }
    HDC Get_Illust_DC() { return m_hNPCLiustDC; }
    wstring& Get_Conversation_Str() { return m_strConversation; }
    void Clear_Quest(QUEST_ID);
private:
    NPC_ID m_eNPCID;
    wstring m_strConversation;
    list<QUEST_ID> m_QuestList;
    list<ITEM_ID> m_StoreItems;
    HDC m_hNPCLiustDC;

};

