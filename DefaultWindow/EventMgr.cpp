#include "stdafx.h"
#include "EventMgr.h"
#include "Character.h"
#include <cstdarg>
#include <cassert>
#include "SoundMgr.h"
#include "AbstractFactory.h"
#include "ObjItem.h"
#include "ObjMgr.h"
#include "QuestMgr.h"
#include "Monster.h"
#include "DropManager.h"

CEventMgr* CEventMgr::m_pInstance = nullptr;
CEvent::CEvent(EVENT_TYPE _eType) : m_eType(_eType)
{
}

CEvent::~CEvent()
{
	Release();
}

void CEvent::Release()
{

}


void CDamageEvent::Proc_Event()
{
	if (m_pObj== nullptr || m_pSbj== nullptr)return;
	if (m_pObj->Get_Dead() || m_pSbj->Get_Dead())
	{
		m_pObj = nullptr; m_pSbj = nullptr;
		return;
	}
	if (m_bCrit)
	{
		SOUND_INST->StopSound(SOUND_EFFECT);
		SOUND_INST->PlaySoundW(L"etc_critical.wav",SOUND_EFFECT,1);
	}
	else
	{
		SOUND_INST->PlayDamageSound(1);

	}
	m_pSbj->On_Hit(m_pObj, m_iDamage);
	EFFECT_INST->Push_Effect(m_pSbj->Get_RenderPoint(), m_eEffect);
	EFFECT_INST->Push_DamageCount(m_pSbj->Get_RenderPoint(),m_bCrit,m_pObj->Get_ID() == OBJ_PLAYER, m_iDamage, true);
}

void CRecoverEvent::Proc_Event()
{
	if (m_pObj == nullptr)
		return;
	if (m_bHP)
		m_pObj->Recover_HP(m_iRecoverPoint);
	else
		m_pObj->Recover_MP(m_iRecoverPoint);
	EFFECT_INST->Push_RecoverCount(m_pObj->Get_RenderPoint(), m_bHP, m_iRecoverPoint);
	SOUND_INST->StopSound(SOUND_EFFECT);
	SOUND_INST->PlaySoundW(L"skill_hpabsorb_hpup.wav",SOUND_EFFECT,1);
}

void CDeadEvent::Proc_Event()
{
	if (m_pObj == nullptr || m_pSbj == nullptr)return;

	m_pSbj->On_Dead(m_pObj);
	m_pObj->On_Kill(m_pSbj);
	if(m_pSbj->Get_ID() == OBJ_MONSTER)
	{
		QUEST_INST->On_Monster_Killed(((CMonster*)m_pSbj)->Get_Monster_ID());
		MONSTER_ID eMonID =  static_cast<CMonster*>(m_pSbj)->Get_Monster_ID();
		ITEM_ID eITemID = DROP_INST->Get_Drop_Item(eMonID);
		if(eITemID != ITEM_ID::END)
			DROP_INST->Drop_Item(eITemID,m_pSbj->Get_Point());
	}
	if (m_pObj->Get_Dead())m_pObj = nullptr;
	if (m_pSbj->Get_Dead())m_pSbj = nullptr;

}
//=======================================================
CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{
	Release();
}
void CEventMgr::Release()
{
	while (m_qEvents.empty() == false)
	{
		CEvent* pCurEvent = m_qEvents.front();
		Safe_Delete(pCurEvent);
		m_qEvents.pop();
	}
}
//Á÷Á¢
void CEventMgr::Push_Event(CEvent* _pEvent)
{
	m_qEvents.push(_pEvent);
}

void CEventMgr::Proc_Event()
{
	while (m_qEvents.empty() == false)
	{
		CEvent* pCurEvent = m_qEvents.front();
		m_qEvents.pop();
		pCurEvent->Proc_Event();
		Safe_Delete(pCurEvent);
	}
}
