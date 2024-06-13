#include "stdafx.h"
#include "ThunderPunch.h"
#include "Character.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CThunderPunch::CThunderPunch()
{
	m_dwCoolTime = 15000;
	m_fRange = 1000;
	m_iConsumptionValue =50;
	m_hEffectDC = BMP_INST->Find_Img(L"Effect_Thunder_Punch");
}

CThunderPunch::~CThunderPunch()
{
}

void CThunderPunch::Update()
{
	if (bThrust == false)
		return;
	if (bAttacked == true)
		return;
	if (m_bRunning == false)
		return;
	if (m_pObj == nullptr || m_pSbj == nullptr)
		return;


	POINT tObjPt = m_pObj->Get_Point();
	POINT tSbjPt = m_pSbj->Get_Point();
	float fDistX = tSbjPt.x - tObjPt.x;
	float fDistY = tSbjPt.y - tObjPt.y;
	float fDist = sqrtf(fDistX * fDistX + fDistY * fDistY);
	m_fXSpeed = m_fSpeed * (fDistX / fDist);
	m_fYSpeed = m_fSpeed * (fDistY / fDist);

	m_tNext = tObjPt;
	m_tNext.x += m_fXSpeed;
	m_tNext.y += m_fYSpeed;
	if (m_pObj->Is_In_Range(m_pSbj->Get_Info(), m_fSpeed))
	{
		m_tNext.x = tSbjPt.x;
		m_tNext.y = tSbjPt.y;
		m_pObj->Set_Pos(m_tNext.x, m_tNext.y);

		if (m_pObj->TryCritical())
			EVENT_INST->Push_Event(new CDamageEvent(m_pObj, m_pSbj, m_iValue * m_pObj->Get_Stat()._fCritMultiplier, true, EFFECT_ID::SHOCK_WAVE));
		else
			EVENT_INST->Push_Event(new CDamageEvent(m_pObj, m_pSbj, m_iValue, false, EFFECT_ID::NORMAL_HIT));
		EFFECT_INST->Push_Effect(tSbjPt,EFFECT_ID::ELECTRIC_SHOCK);
		bThrust = false;
		bAttacked = true;
		return;
	}
	m_pObj->Set_Pos(m_tNext.x, m_tNext.y);
}

void CThunderPunch::Late_Update()
{
}

void CThunderPunch::Render(HDC hdc)
{
	if (m_bRunning == false)
		return;
	RECT tPlayerRect = m_pObj->Get_RenderRect();
	FRAME tPlayerFrame = m_pObj->Get_Frame();
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hdc,
		tPlayerRect.left + iScrollX,
		tPlayerRect.top + iScrollY,
		100,
		100,
		m_hEffectDC,
		100 * tPlayerFrame.iFrameStart,
		100 * tPlayerFrame.iMotion,
		100,
		100,
		MAGENTA);
}

void CThunderPunch::Func(CCharacter* _pObj, CCharacter* _pSbj)
{
	DIRECTION _eDir = _pObj->Calc_FDir(_pSbj->Get_Point());
	_pObj->Set_Direction(_eDir);
	(_pObj)->Set_Common_Motion(COMMON_STATE::STRONG_ATTACK);
	SOUND_INST->StopSound(SOUND_CHIDORI);
	SOUND_INST->PlaySoundW(L"chidori3.mp3", SOUND_CHIDORI, 0.1);
	m_iValue = _pObj->Get_Stat()._iAttak * 5;


}

void CThunderPunch::Motion_Func()
{
	if(bAttacked == false)
		bThrust = true;

}

void CThunderPunch::Motion_End()
{
	m_pSbj = nullptr;
	m_pObj = nullptr;
	m_bRunning = false;
	bThrust = false;
	bAttacked = false;
}
