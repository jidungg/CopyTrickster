#pragma once
#include "Scene.h"
#include "Button.h"
#include "RythmNoteSpawner.h"

class CRythmNote
{
public :
	CRythmNote(int iXPos, NOTE_TYPE _eType);

	bool Update();
	void Update_Rect();
	void Late_Update();
	void Render(HDC hdc);
	RECT Get_Rect() { return m_tRect; }
	void Set_Hit(bool bHit);
	bool Get_Dead() { return m_bDead; }
	NOTE_TYPE Get_Type() { return m_eType; }
	int Get_YPos() { return m_iYPos; }
	int Get_XPos() { return m_iXPos; }
private:
	RECT m_tRect;
	int m_iXPos;
	int m_iYPos = -30;

	int m_iXSize = 29;
	int m_iYSize = 27;
	int m_iSpeed = 4;
	bool m_bHit = false;
	HDC m_hNoteDC;
	DWORD m_dwSpeed = 200;
	DWORD m_dwHittedTime = 0;
	bool m_bDead = false;
	NOTE_TYPE m_eType;
};
class CRythmGame :
    public CScene
{
public:
	CRythmGame();
	~CRythmGame();
public:
	virtual void	Initialize();
	virtual void    Start(SCENE_ID _ePrevScene);
	virtual int		Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void    End();
	virtual void	Release();

	void Key_Input();
	int Get_XPos(int iCol) { return m_vecButtonPoints[iCol].x + m_iButtonCX / 2; }
private:
	HDC m_hFrameDC;
	HDC m_hNormalButtonDC;
	HDC m_hClickButtonDC;
	HDC m_hIlustDC;

	int m_iButtonCX = 73;
	int m_iButtonCY = 20;
	int m_iCorrection = 20;

	bool m_vecCurButtonStates[4] = {false,};
	DWORD m_vecPressedTime[4] = {0,};
	POINT m_vecButtonPoints[4] = { {8,547},{84,547},{160,547},{236,547} };
	RECT m_vecButtonRects[4];
	DWORD m_dwSpeed =100;
	
	list<CRythmNote*> m_vecNotes;

	int m_iScore;

	CRythmNoteSpawner* m_pSpawner;

	DWORD m_dwSceneStarTime;

	HWND		m_hVideo;

	HDC m_hComboDC1;
	HDC m_hComboDC2;
	POINT m_tComboPoint = { 158,100 };
	int m_iCombo = 0;
	vector<int> m_vecComboNumbs;
	int m_iComboDigits;
	int m_iCOmboCharWidth1 = 13;
	int m_iCOmboCharHeight1 = 16;
	int m_iCOmboCharWidth2 = 12;
	int m_iCOmboCharHeight2 = 15;

};

