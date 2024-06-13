#pragma once
#include "CEffect.h"
class CRisingEffect :
    public CEffect
{
public:
    CRisingEffect(EFFECT_DATA _data, int _iMotionOffset, float _fSpeed, DWORD _dwRisingTime);
    virtual void Render(HDC hdc, POINT _pt)override;
protected:
    float m_fRisingSpeed = 0.5f;
};

