#pragma once
#include "Obj.h"
#include "Skill.h"

class CSkillSlot;
class CSkillInventory;
class CCharacter :
    public CObj
{
public:
	CCharacter();
	~CCharacter();
public:
	virtual int Update() override;
	virtual void Update_Move(POINT _pt);
	virtual void On_Range()PURE;
	virtual void On_Move()PURE;
	virtual void On_Noting()PURE;
	virtual void On_Move_End() PURE;
	virtual void On_Hit(CCharacter* _pObj, int _iDamage);
	virtual void On_Kill(CCharacter* _pObj);
	virtual void On_Dead(CCharacter* _pObj);

	void Make_Stop();
	void Change_Motion() override;

	virtual void Set_Data(CHARACTER_DATA* _tData);
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void Set_Dest(POINT _tP) ;
	void Select_Skill(SKILL_ID _eSkill);

	virtual float Get_X_Speed();
	virtual float Get_Y_Speed();
	int	  Get_Attack() { return m_tStat._iAttak; }
	STAT& Get_Stat() { return m_tStat; }
	float Get_CurRange();
	int& Get_HP_Ref() { return m_tStat._iHP; }
	int& Get_MP_Ref() { return m_tStat._iMP; }
	TCHAR* Get_Name() { return m_pName; }

	bool TryCritical();
	void Fit_Direction(POINT _tp);
	bool Is_In_Range(POINT _pt, float _iRange);
	bool Is_In_Range(INFO _tInfo, float _iRange);
	void Use_Skill(SKILL_ID _eID);
	void Consume_Mana(int _iVal);
	void Recover_HP(int _iVal);
	void Recover_MP(int _iVal);
	void AddStat(STAT _tSat);
	void SubStat(STAT _tSat);
	map<SKILL_ID, CSkillSlot*>* Get_Skill_Inven() { return &m_SkillInven; }

	//TMP
	FRAME Get_Frame() { return m_tFrame; }
protected: 

	STAT	m_tStat;
	DWORD	m_dwLastAttackTime;
	float	m_fRange;


	POINT m_tDest;

	SKILL_ID m_eCurSkill = SKILL_ID::BASIC_ATTACK;
	map<SKILL_ID, CSkillSlot*> m_SkillInven;

	TCHAR* m_pName;

	bool m_bPrevSkillRunning;
};

