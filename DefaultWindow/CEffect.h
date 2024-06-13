#pragma once
#include "Define.h"


class CEffect
{
public:
	CEffect(EFFECT_DATA _data, int _MotionOffset);

	virtual ~CEffect();


	bool Move_Frame();
	virtual void Render(HDC hdc, POINT _pt);
protected:
	EFFECT_DATA m_tData;
};

