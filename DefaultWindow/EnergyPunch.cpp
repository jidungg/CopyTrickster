#include "stdafx.h"
#include "EnergyPunch.h"
#include "Player.h"
#include "SoundMgr.h"

CEnergyPunch::CEnergyPunch()
{
	m_dwCoolTime = 15000;
	m_fRange = TILECX;
	m_iConsumptionValue = 30;
}

void CEnergyPunch::Func(CCharacter* _pObj, CCharacter* _pSbj)
{
	DIRECTION _eDir = _pObj->Calc_FDir(_pSbj->Get_Point());
	_pObj->Set_Direction(_eDir);
	(_pObj)->Set_Common_Motion(COMMON_STATE::STRONG_ATTACK);
	EFFECT_INST->Push_Effect(_pObj->Get_RenderPoint(),EFFECT_ID::ENERGY_PUNCH, (DIRECTION)_pObj->FDir_To_Motion_Idx( _eDir));
	SOUND_INST->StopSound(SOUND_RASENGAN);
	SOUND_INST->PlaySoundW(L"rasengan.mp3", SOUND_RASENGAN,1);
	m_iValue = _pObj->Get_Stat()._iAttak;
}

void CEnergyPunch::Motion_Func()
{
	if (m_pSbj == nullptr || m_pSbj->Get_Dead())
		return;
	if (m_pObj == nullptr || m_pObj->Get_Dead())
		return;
	if(m_pObj->TryCritical())
		EVENT_INST->Push_Event(new CDamageEvent(m_pObj, m_pSbj, m_iValue * m_pObj->Get_Stat()._fCritMultiplier, true, EFFECT_ID::SHOCK_WAVE));
	else
		EVENT_INST->Push_Event(new CDamageEvent(m_pObj, m_pSbj, m_iValue,false,EFFECT_ID::NORMAL_HIT));

}

void CEnergyPunch::Motion_End()
{
	m_pSbj = nullptr;
	m_pObj = nullptr;
	m_bRunning = false;
}
