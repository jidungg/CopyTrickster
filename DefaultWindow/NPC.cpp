#include "stdafx.h"
#include "NPC.h"
#include "UIMgr.h"

CNPC::CNPC()
{
    m_eRender = RENDER_GAMEOBJECT;

}

CNPC::~CNPC()
{
    Release();
}

void CNPC::Initialize()
{

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = g_dwTime;
	m_tFrame.dwSpeed = 200;
	m_dwLastAttackTime = 0;

	m_ePreState = ST_END;
	m_eCurState = IDLE;
	m_eCurDir = DIR_DOWN;
	m_eRender = RENDER_GAMEOBJECT;
	m_eObjID = OBJ_NPC;
}

int CNPC::Update()
{
	__super::Update_Rect();
	return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
}

void CNPC::Late_Update()
{
    Change_Motion();

    __super::Move_Frame();
}

void CNPC::Release()
{
}


void CNPC::On_Motion_End()
{
}

void CNPC::Motion_Func()
{
}

void CNPC::Interaction(CObj* _pObj)
{
	if (_pObj->Get_ID() != OBJ_PLAYER)
		return;
	UI_INST->TurnOn_NPC_Conversation_UI(this);
	Fit_Direction(_pObj->Get_Point());
}

void CNPC::On_Range()
{
}

void CNPC::On_Move()
{
}

void CNPC::On_Noting()
{
}

void CNPC::On_Move_End()
{
}
void CNPC::Set_Common_Motion(COMMON_STATE _eState)
{
	switch (_eState)
	{
	case COMMON_STATE::IDLE:
	case COMMON_STATE::BATTLE:
	case COMMON_STATE::DEAD:
		m_eCurState = IDLE;
		break;
	case COMMON_STATE::MOVE:
		m_eCurState = WALK;
		break;
	case COMMON_STATE::BASIC_ATTACK:
	case COMMON_STATE::CRITICAL_ATTACK:
	case COMMON_STATE::STRONG_ATTACK:
		m_eCurState = HELLO;
		break;
	case COMMON_STATE::HIT:
		m_eCurState = NOD;
		break;
	case COMMON_STATE::DODGE:
		m_eCurState = BLINK;
		break;
	case COMMON_STATE::END:
		break;
	default:
		break;
	}
}

void CNPC::Set_Data(CHARACTER_DATA* _tData)
{
	CCharacter::Set_Data(_tData);
	NPC_DATA* pNPCData = ((NPC_DATA*)_tData);
	m_strConversation =  pNPCData->strConversation;
	m_QuestList = pNPCData->QuestList;
	m_hNPCLiustDC = pNPCData->hNPCLiustDC;
}

void CNPC::Clear_Quest(QUEST_ID _eID)
{
	for (auto iter = m_QuestList.begin(); iter != m_QuestList.end(); iter++)
	{
		if ((*iter) == _eID)
		{
			m_QuestList.erase(iter);
			return;
		}
	}
}
