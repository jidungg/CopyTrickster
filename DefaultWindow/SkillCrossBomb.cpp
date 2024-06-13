#include "stdafx.h"
#include "SkillCrossBomb.h"
#include "Character.h"

CSkillCrossBomb::CSkillCrossBomb()
{
	m_dwCoolTime = 5000;
	m_fRange = 800;
}

void CSkillCrossBomb::Func(CCharacter* _pObj, CCharacter* _pSbj)
{
	DIRECTION _eDir = m_pObj->Calc_FDir(m_pSbj->Get_Point());
	m_pObj->Set_Direction(_eDir);
	STAT& tStat = _pObj->Get_Stat();
	(m_pObj)->Set_Common_Motion(COMMON_STATE::STRONG_ATTACK);
	if (m_bValue = _pObj->TryCritical())
	{
		_pObj->Set_Common_Motion(COMMON_STATE::CRITICAL_ATTACK);
		m_iValue = tStat._iAttak * tStat._fCritMultiplier;
	}
	else
	{
		_pObj->Set_Common_Motion(COMMON_STATE::BASIC_ATTACK);

		m_iValue = tStat._iAttak;
	}
	m_iValue = m_pObj->Get_Stat()._iAttak * 3;
}

void CSkillCrossBomb::Motion_Func()
{

	EFFECT_INST->Push_Effect(m_pSbj->Get_Point(), EFFECT_ID::CROSS_EXPLODE);
	EVENT_INST->Push_Event(new CDamageEvent(m_pObj, m_pSbj, m_iValue, m_bValue, m_bValue ? EFFECT_ID::SHOCK_WAVE : EFFECT_ID::NORMAL_HIT));
}

void CSkillCrossBomb::Motion_End()
{
	m_pSbj = nullptr;
	m_pObj = nullptr;
	m_bRunning = false;
}
