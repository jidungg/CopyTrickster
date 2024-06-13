#pragma once
#include "RisingEffect.h"
class CDamageCount :
    public CRisingEffect
{
public:
    CDamageCount(EFFECT_DATA _data, int _iValue, bool bRising);
    virtual void Render(HDC hdc, POINT _pt)override;

private:
    int m_iValue;
    vector<char> m_vecNumbers;
    int m_iDigits;
    bool m_bRising = true;
};

class CRecoverCount :
    public CRisingEffect
{
public:
    CRecoverCount(EFFECT_DATA _data, int _iValue);
    virtual void Render(HDC hdc, POINT _pt)override;

private:
    int m_iValue;
    vector<char> m_vecNumbers;
    int m_iDigits;
};
