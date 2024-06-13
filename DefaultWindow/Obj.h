#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_Direction(DIRECTION eDir) { m_eCurDir = eDir;  }
	void		Set_Dead() { m_bDead = true; }
	
	void		Set_X(float _fX) { m_tInfo.fX += _fX; }
	void		Set_Y(float _fY) { m_tInfo.fY += _fY; }
	void		Set_RenderRectX(int _i) { m_tInfo.fRX = _i; }
	void		Set_RenderRectY(int _i) { m_tInfo.fRY = _i; }
	void		Set_RenderOffsetX(int _i) { m_iRenderOffsetX = _i; }
	void		Set_RenderOffsetY(int _i) { m_iRenderOffsetY =_i; }
	void		Set_CollisionRectX(int _i) { m_tInfo.fCX = _i; }
	void		Set_CollisionRectY(int _i) { m_tInfo.fCY =_i; }
	void		Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	virtual void	Set_Common_Motion(COMMON_STATE _eState)PURE;
	DIRECTION Calc_Dir(POINT _tP);
	DIRECTION Calc_Dir(float _fRad);
	DIRECTION Calc_FDir(POINT _tP);
	DIRECTION EDir_To_FDir(DIRECTION _eDir);
	DIRECTION EDir_To_TDir(DIRECTION _eDir);
	int FDir_To_Motion_Idx(DIRECTION _eDir);
	int TDir_To_Motion_Idx(DIRECTION _eDir);

	float Calc_Radius(POINT _tP);

	float Get_Current_Radius();
	INFO		Get_Info() { return m_tInfo; }
	RECT		Get_RenderRect() { return m_tRenderRect; }
	RECT		Get_CollisionRect() { return m_tCollisionRect; }
	float		Get_RX() { return m_tInfo.fRX; }
	float		Get_RY() { return m_tInfo.fRY; }
	float		Get_CX() { return m_tInfo.fCX; }
	float		Get_CY() { return m_tInfo.fCY; }
	bool		Get_Dead() { return m_bDead; }
	RENDERID	Get_RenderID() { return m_eRender; }
	OBJ_ID		Get_ID() { return m_eObjID; }
	POINT		Get_Point() { return { (long)m_tInfo.fX, (long)m_tInfo.fY }; }
	int			Get_RenderOffsetX() { return m_iRenderOffsetX; }
	int			Get_RenderOffsetY() { return m_iRenderOffsetY; }
	POINT		Get_RenderPoint();
	bool		Get_MotionChangable() { return m_tFrame.bMotionCancelable; }

	virtual void On_Collision(CObj* _pObj);
public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Late_Update()PURE;
	virtual void	Render(HDC hDC);
	virtual void	Release()PURE;
	virtual void	Change_Motion() PURE;
	virtual void	On_Motion_End()PURE;
	virtual void	Motion_Func()PURE;
	virtual void	Interaction(CObj* _pObj)PURE;
protected:
	void			Update_Rect();
	virtual void	Move_Frame();
protected:
	RECT		m_tRenderRect;
	int			m_iRenderOffsetX =0;
	int			m_iRenderOffsetY =0;
	RECT		m_tCollisionRect;
	INFO		m_tInfo;
	FRAME		m_tFrame;

	DIRECTION	m_eCurDir;
	DIRECTION	m_ePrevDir;
	RENDERID	m_eRender;

	bool		m_bDead = false;
	bool m_bMotionEnded = true;
	int	m_ePreState;
	int	m_eCurState;
	vector<pair<ANIM_TYPE, FRAME>>* m_vecAnimData;


	OBJ_ID m_eObjID;
	CObj* m_pTarget = nullptr;

};

