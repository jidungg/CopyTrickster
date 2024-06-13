#include "stdafx.h"
#include "EffectMgr.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "BmpMgr.h"
#include "RisingEffect.h"
#include "DamageCount.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
}

CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Initialize()
{
	BMP_INST->Insert_Bmp(L"../Image/Effect/cross_explode.bmp",			L"Effect_CROSS_EXPLODE");
	BMP_INST->Insert_Bmp(L"../Image/Effect/charge_attack-sheet.bmp",	L"Effect_Energy_Punch");
	BMP_INST->Insert_Bmp(L"../Image/Effect/shockwave_sheet.bmp",		L"Effect_Shock_Wave");
	BMP_INST->Insert_Bmp(L"../Image/Effect/thunder_sheet.bmp",			L"Effect_Thunder");
	BMP_INST->Insert_Bmp(L"../Image/Effect/thunder_punch.bmp",			L"Effect_Thunder_Punch");
	BMP_INST->Insert_Bmp(L"../Image/Effect/big_explode_sheett.bmp",		L"Effect_Big_Explode");
	BMP_INST->Insert_Bmp(L"../Image/Effect/normal_attack.bmp",			L"Effect_Normal_Hit");
	BMP_INST->Insert_Bmp(L"../Image/Effect/electric_shock.bmp",			L"Effect_Electric_shock");

	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/hp_recover_count-Sheet.bmp",		L"Effect_HP_Recover_Count");
	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/mp_recover_count-Sheet.bmp",		L"Effect_MP_Recover_Count");
	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/recover_sign-Sheet.bmp",			L"Effect_Recover_Sign");
	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/hit_head_up-Sheet.bmp",			L"Effect_Headup_Hit");
	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/monster_damage_count-Sheet.bmp",		L"Effect_Monster_Damage_Count");
	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/player_damage_count-Sheet.bmp",			L"Effect_Player_Damage_Count");
	BMP_INST->Insert_Bmp(L"../Image/Effect/headup/player_damage_count_critical.bmp",L"Effect_Player_Damage_Count_Critical");
	EFFECT_DATA* _tData;
#pragma region CROSS_EXPLODE
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::CROSS_EXPLODE;
		_tData->iRX = 400;
		_tData->iRY = 400;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 100;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 8;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = -100;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_CROSS_EXPLODE");
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}

#pragma endregion

#pragma region SHOCKWAVE
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::SHOCK_WAVE;
		_tData->iRX = 132;
		_tData->iRY = 132;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 50;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 6;
//		tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Shock_Wave");
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion

#pragma region NORMAL_HIT
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::NORMAL_HIT;
		_tData->iRX = 47;
		_tData->iRY = 50;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 100;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Normal_Hit");
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region ENERGY_PUNCH
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::ENERGY_PUNCH;
		_tData->iRX = 100;
		_tData->iRY = 100;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.bMotionCancelable = false;
		tFrame.dwSpeed = 100;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 20;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Energy_Punch");
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region ELECTRIC_SHOCK
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::ELECTRIC_SHOCK;
		_tData->iRX = 100;
		_tData->iRY = 100;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.bMotionCancelable = false;
		tFrame.dwSpeed = 300;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 12;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Electric_shock");
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion

#pragma region PLAYER_DAMAGE_COUNT
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::PLAYER_DAMAGE_COUNT;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Player_Damage_Count");
		_tData->iRX = 16;
		_tData->iRY = 20;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region PLAYER_DAMAGE_COUNT_CRITICAL
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::PLAYER_DAMAGE_COUNT_CRITICAL;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Player_Damage_Count_Critical");
		_tData->iRX = 12;
		_tData->iRY = 15;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region MONSTER_DAMAGE_COUNT
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::MONSTER_DAMAGE_COUNT;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Monster_Damage_Count");
		_tData->iRX = 13;
		_tData->iRY = 16;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region HP_RECOVER_COUNT
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::HP_RECOVER_COUNT;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_HP_Recover_Count");
		_tData->iRX = 13;
		_tData->iRY = 16;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region MP_RECOVER_COUNT
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::MP_RECOVER_COUNT;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_MP_Recover_Count");
		_tData->iRX = 13;
		_tData->iRY = 16;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion

#pragma region PLAYER_CRITICAL
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::PLAYER_CRITICAL;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Headup_Hit");
		_tData->iRX = 100;
		_tData->iRY = 70;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 300;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region PLAYER_DAMAGE_COUNT_CRITICAL_BACK
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::PLAYER_DAMAGE_COUNT_CRITICAL_BACK;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Headup_Hit");
		_tData->iRX = 100;
		_tData->iRY = 70;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 2;
		tFrame.iFrameEnd = 2;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region PLAYER_MISS
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::PLAYER_MISS;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Headup_Hit");
		_tData->iRX = 100;
		_tData->iRY = 70;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 1;
		tFrame.iFrameEnd = 1;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region MONSTER_CRITICAL
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::MONSTER_CIRTICAL;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Headup_Hit");
		_tData->iRX = 100;
		_tData->iRY = 70;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 300;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 0;
		tFrame.iFrameEnd = 0;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
#pragma region MONSTER_MISS
	{
		_tData = new EFFECT_DATA;
		_tData->eID = EFFECT_ID::MONSTER_MISS;
		_tData->hMemDC = BMP_INST->Find_Img(L"Effect_Headup_Hit");
		_tData->iRX = 100;
		_tData->iRY = 70;
		FRAME& tFrame = _tData->tFrame;
		tFrame.bRepeat = false;
		tFrame.dwSpeed = 1000;
		tFrame.dwTime = 0;
		tFrame.iFrameStart = 1;
		tFrame.iFrameEnd = 1;
		//tFrame.iFuncIdx = -1;
		tFrame.iMotion = 0;
		_tData->iRenderOffsetX = 0;
		_tData->iRenderOffsetY = 0;
		m_EffectData.insert({ _tData->eID,*_tData });
		Safe_Delete(_tData);
	}
#pragma endregion
}

void CEffectMgr::Late_Update()
{
	auto& endIter =m_liCurEffects.end();
	for (auto& iter = m_liCurEffects.begin(); iter != endIter; )
	{
		if (iter->second->Move_Frame())
		{
			Safe_Delete(iter->second);
			iter = m_liCurEffects.erase(iter);
		}
		else
		{
			iter++;
		}
	}


}

void CEffectMgr::Render(HDC hDC)
{
	for (auto& effect : m_liCurEffects)
	{
		effect.second->Render(hDC, effect.first);
	}
}

void CEffectMgr::Release()
{
	for (auto& i : m_liCurEffects)
	{
		Safe_Delete(i.second);
	}
	m_liCurEffects.clear();
}


void CEffectMgr::Push_Effect(POINT _pt, EFFECT_ID _eID)
{
	CEffect* pEffect = new CEffect(m_EffectData[_eID], 0);
	m_liCurEffects.push_back({ _pt,pEffect});
}

void CEffectMgr::Push_Effect(POINT _pt, EFFECT_ID _eID, DIRECTION _eDir)
{
	CEffect* pEffect = new CEffect(m_EffectData[_eID], _eDir);
	m_liCurEffects.push_back({ _pt,pEffect });
}

void CEffectMgr::Push_Rising_Effect(POINT _pt, EFFECT_ID _eID, float _fSpeed, DWORD _dwTime)
{
	CEffect* pEffect = new CRisingEffect(m_EffectData[_eID],0,_fSpeed, _dwTime);
	m_liCurEffects.push_back({ _pt,pEffect });
}

void CEffectMgr::Push_DamageCount(POINT _pt, bool bCrit, bool bPlayer, int iValue, bool bRisign)
{
	if (bPlayer)
	{
		if (bCrit)
		{			
			Push_Rising_Effect(_pt, EFFECT_ID::PLAYER_DAMAGE_COUNT_CRITICAL_BACK, 1.f, 2000);
			CEffect* pEffect = new CDamageCount(m_EffectData[EFFECT_ID::PLAYER_DAMAGE_COUNT_CRITICAL], iValue, bRisign);
			m_liCurEffects.push_back({ _pt,pEffect });
			Push_Effect(_pt, EFFECT_ID::PLAYER_CRITICAL);
		}
		else
		{
			CEffect* pEffect = new CDamageCount(m_EffectData[EFFECT_ID::PLAYER_DAMAGE_COUNT], iValue, bRisign);
			m_liCurEffects.push_back({ _pt,pEffect });
		}
	}
	else
	{
		CEffect* pEffect = new CDamageCount(m_EffectData[EFFECT_ID::MONSTER_DAMAGE_COUNT], iValue, bRisign);
		m_liCurEffects.push_back({ _pt,pEffect });
		if(bCrit)
			Push_Effect({ _pt.x, _pt.y - 18 }, EFFECT_ID::MONSTER_CIRTICAL);
	}
	
}

void CEffectMgr::Push_RecoverCount(POINT _pt, bool bHP, int iValue)
{
	CEffect* pEffect;
	if(bHP)
		pEffect = new CDamageCount(m_EffectData[EFFECT_ID::HP_RECOVER_COUNT], iValue, true);
	else
		pEffect = new CDamageCount(m_EffectData[EFFECT_ID::MP_RECOVER_COUNT], iValue, true);

	m_liCurEffects.push_back({ _pt,pEffect });
}
