#pragma once
#include <queue>
#include "Define.h"


class CCharacter;
class CObj;
class CEvent
{
public:
	CEvent(EVENT_TYPE);
	virtual ~CEvent();

	void Release();

	EVENT_TYPE Get_Type() { return m_eType; }
	virtual void Proc_Event() PURE;
protected:
	EVENT_TYPE m_eType = EVENT_TYPE::END;
};
class CDamageEvent : public CEvent
{
public:
	//직접 크리티컬 데미지를 계산해서 넣을 것.
	CDamageEvent(CCharacter* _pObj,CCharacter* _pSbj, int _iDamage, bool _bCrit, EFFECT_ID _eEffect)
		: CEvent(EVENT_TYPE::DAMAGE), m_pObj(_pObj), m_pSbj(_pSbj), m_iDamage(_iDamage), m_bCrit(_bCrit), m_eEffect(_eEffect)
	{
		
	}
	~CDamageEvent() { Release(); }
	void Proc_Event()override;
private:
	CCharacter* m_pObj =nullptr;
	CCharacter* m_pSbj = nullptr;
	int m_iDamage;
	bool m_bCrit;
	EFFECT_ID m_eEffect;
};
class CRecoverEvent : public CEvent
{
public:
	CRecoverEvent(CCharacter* _pObj, int _iRecover, bool _bHP)
		:CEvent(EVENT_TYPE::RECOVER), m_pObj(_pObj),m_iRecoverPoint(_iRecover), m_bHP(_bHP)
	{

	}
	void Proc_Event()override;
private:
	int m_iRecoverPoint;
	CCharacter* m_pObj;
	bool m_bHP;
};
class CDeadEvent : public CEvent
{
public:
	CDeadEvent(CCharacter* _pObj, CCharacter* _pSbj)
		: CEvent(EVENT_TYPE::DEAD), m_pObj(_pObj), m_pSbj(_pSbj)
	{

	}
	~CDeadEvent() { Release(); }
	void Proc_Event()override;
private:
	CCharacter* m_pObj;
	CCharacter* m_pSbj;
};
class CEventMgr
{
private:
	CEventMgr();
	~CEventMgr();

public:
	static CEventMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEventMgr;

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
	static CEventMgr* m_pInstance;

public:
	void Release();

	void Push_Event(CEvent* _pEvent);
	void Proc_Event();
private:
	queue<CEvent*> m_qEvents;
};
#define EVENT_INST CEventMgr::Get_Instance()

