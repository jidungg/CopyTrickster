#include "stdafx.h"
#include "BasicAttack.h"
#include "Character.h"

CBasicAttack::CBasicAttack(DWORD dwCoolTime, float fRange)
{
	m_dwCoolTime = dwCoolTime;
	m_fRange = fRange;
}

void CBasicAttack::Func(CCharacter* _pObj, CCharacter* _pSbj)
{
	_pObj->Set_Direction(_pObj->Calc_FDir(_pSbj->Get_Point()));
	STAT& tStat  = _pObj->Get_Stat();
	if (m_bValue = _pObj->TryCritical())
	{
		_pObj->Set_Common_Motion(COMMON_STATE::CRITICAL_ATTACK);
		m_iValue = tStat._iAttak * tStat._fCritMultiplier;
	}
	else
	{
		_pObj->Set_Common_Motion(COMMON_STATE::BASIC_ATTACK);

		m_iValue = tStat._iAttak ;
	}
}

void CBasicAttack::Motion_Func()
{
	EVENT_INST->Push_Event(new CDamageEvent(m_pObj, m_pSbj, m_iValue,m_bValue,m_bValue? EFFECT_ID::SHOCK_WAVE : EFFECT_ID::NORMAL_HIT));
}

void CBasicAttack::Motion_End()
{
	m_pSbj = nullptr;
	m_pObj = nullptr;
	m_bRunning = false;
}
