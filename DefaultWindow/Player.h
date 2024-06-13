#pragma once
#include "Character.h"
enum class COMMAND_TYPE
{
	ATTACK,
	SKILL,
	MOVE,
	END
};
typedef struct tagCommandData
{
	COMMAND_TYPE eType;
	
}COMMAND;

class CPlayer :	public CCharacter
{
public:
	

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int  Update()override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	void RenderArm(HDC hdc);
	void RenderEar(HDC hdc);
	virtual void Release() override;

	void On_Move() override;
	void On_Noting() override;
	void On_Range() override;
	void On_Hit(CCharacter* _pObj, int _iDamage) override;
	void On_Kill(CCharacter* _pObj) override;
	void On_Dead(CCharacter* _pObj) override;
	void On_Move_End() override;
	void On_Motion_End() override;
	void Offset();
	void Motion_Func() override;
	void Change_Motion() override;
	void Interaction(CObj* _pObj) override;
	void Toggle_Run(){m_bRun = !m_bRun;}
	void Set_Common_Motion(COMMON_STATE _eState) override;
	void Set_Run(bool _bRun) {m_bRun = _bRun;}

	float Get_X_Speed()override;
	float Get_Y_Speed()override;
	CObj** Get_Current_TargetPointer() { return &m_pTarget; }
	void Gain_Exp(int _iExp) { m_iExp += _iExp; }
	void Revive();
	float Get_CooltimeRatio(SKILL_ID _eID);
private:
	bool	m_bRun = false;
	bool m_bRenderArm = true;
	TCHAR* m_pArmFrameKey;
	TCHAR* m_pEarFrameKey;
	int m_iExp = 0;


//DRILLING ===================================================
public:
	void Set_Drill_Mode(bool _bMode) { m_bDrillMode = _bMode; }
	void Toggle_Drill_Mode() { m_bDrillMode = !m_bDrillMode; }
	void Update_Drill_Frame();
	void Update_Drill_Guage();
	void RenderDrill(HDC hdc);
	void End_Drill();
	void Success_Drill();
private:
	bool m_bRenderDrill = false;
	bool m_bDrillMode = false;
	HDC m_hDrillDC;
	HDC m_hDrillUIDC;
	HDC m_hDrillGuageFillDC;
	HDC m_hDrillIndicatorDC;
	FRAME m_tDrillFrame;
	int m_iDrillDepth = 0;
	int m_iDrillMaxDepth = 50;
	int m_iDrillGaugeMax = 1000;
	int m_iDrillGaugeVal = 0;
	int m_iDrillUIX = 150;
	int m_iDrillUIY = 68;
	int m_iDrillFillUIX = 32;
	int m_iDrillFillUIY = 6;
	int m_iDriilGuageWidth = 114;
	int m_iDrillIndicatorPos = 600;
	float m_fDrillGuageRatio;
	POINT m_tDrillFillPoint = {32,50};
	DWORD m_dwMinDrillAnimSpeed = 25;
	DWORD m_dwMaxDrillAnimSpeed = 250;


};
