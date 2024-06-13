#pragma once
#include "Scene.h"
class CIntro :
    public CScene
{
public:
	virtual void	Initialize();
	virtual void    Start(SCENE_ID _ePrevScene);
	virtual int		Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void    End();
	virtual void	Release();
private:
	HDC m_hLoadingDC;
	HDC m_hGameStartButtonDC;
	RECT m_tButtonRect;
	int m_iButtonState = 0;
	int m_iButtonWidth = 244;
	int m_iButtonHeight = 80;
};

