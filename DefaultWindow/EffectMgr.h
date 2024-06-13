#pragma once
#include "Define.h"

class CEffect;
class CEffectMgr
{
public:
	CEffectMgr();
	~CEffectMgr();
#pragma region SingleTon

public:
	static CEffectMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEffectMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CEffectMgr* m_pInstance;
#pragma endregion
public:
	void Initialize();
	void Late_Update();
	void Render(HDC hDC);
	void Release();
	void Push_Effect(POINT _pt, EFFECT_ID _eID);
	void Push_Effect(POINT _pt, EFFECT_ID _eID, DIRECTION _eDir);
	void Push_Rising_Effect(POINT _pt, EFFECT_ID _eID, float _fSpeed = 1.f, DWORD _dwTime = 1000);
	void Push_DamageCount(POINT _pt, bool bCrit, bool bPlayer, int iValue , bool bRising);
	void Push_RecoverCount(POINT _pt, bool bHP, int iValue);
private:
	list < pair<POINT,CEffect* >> m_liCurEffects;
	map<EFFECT_ID, EFFECT_DATA> m_EffectData;
};

#define EFFECT_INST CEffectMgr::Get_Instance()
