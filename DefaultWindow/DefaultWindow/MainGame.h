#pragma once

#include "Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Release();

private:
	CObj*		m_pPlayer;
	HDC			m_DC;

};

