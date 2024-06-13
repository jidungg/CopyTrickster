#pragma once
#include "Define.h"
#include "Obj.h"
#include "EventMgr.h"
#include "EffectMgr.h"



class CCharacter;
class CSkill
{
public:
	CSkill();
	virtual ~CSkill();

	void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC hdc);
	void Release();

	float Get_Range() { return m_fRange; }
	void Use(CCharacter* _pObj, CCharacter* _pSbj);

	void On_Motion_Func();
	void On_Motion_End();
	bool Has_Enough_Mana(CCharacter* _pObj);
	virtual bool Is_Coolling();
	virtual bool Is_Running() { return m_bRunning; }
	virtual void Func(CCharacter* _pObj, CCharacter* _pSbj) PURE;
	DWORD Get_CoolTime() { return m_dwCoolTime; }
	DWORD Get_RemainCoolTime();
	void StopRunning() { m_bRunning = false; }
protected:
	virtual void Motion_Func()PURE;
	virtual void Motion_End()PURE;

	int m_iValue;
	bool m_bValue;
	float m_fRange = 0;
	DWORD m_dwCoolTime;
	DWORD m_dwUsedTime;

	CCharacter* m_pObj;
	CCharacter* m_pSbj;
	bool m_bRunning = false;
	int m_iConsumptionValue = 0;
};

