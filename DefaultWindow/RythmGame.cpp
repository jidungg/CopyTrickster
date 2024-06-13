#include "stdafx.h"
#include "RythmGame.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

CRythmGame::CRythmGame()
{
}

CRythmGame::~CRythmGame()
{
	Release();
}

void CRythmGame::Initialize()
{
	m_hMapDC = BMP_INST->Find_Img(L"RYTHM_Back");
	m_hFrameDC = BMP_INST->Find_Img(L"RYTHM_Frame");
	m_hNormalButtonDC = BMP_INST->Find_Img(L"RYTHM_Normal_Buttons");
	m_hClickButtonDC = BMP_INST->Find_Img(L"RYTHM_Click_Buttons");
	m_hIlustDC = BMP_INST->Find_Img(L"RYTHM_Ilu");
	m_hComboDC1 = BMP_INST->Find_Img(L"Effect_Monster_Damage_Count");;
	m_hComboDC2 = BMP_INST->Find_Img(L"Effect_Player_Damage_Count_Critical");;
	m_iMapX = 800;
	m_iMapY = 600;

	for (int i = 0; i < 4; i++)
	{
		m_vecButtonRects[i] = { m_vecButtonPoints[i].x ,  m_vecButtonPoints[i].y - m_iCorrection/2,
			m_vecButtonPoints[i].x + m_iButtonCX,
			m_vecButtonPoints[i].y + m_iButtonCY + m_iCorrection /2};
	}
	m_pSpawner = new CRythmNoteSpawner;
	m_vecComboNumbs.resize(3);
}

void CRythmGame::Start(SCENE_ID _ePrevScene)
{

	//m_hVideo = MCIWndCreate(g_hWnd,		// 부모 윈도우 핸들
	//	nullptr,	// 인스턴스 핸들
	//	WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,	// 윈도우 모양 설정
	//	L"../Sound/History-of-Super-Mario-bros.-_480p_.wmv");		// 재생할 파일의 경로

	//// 동영상 재생 크기를 설정
	//MoveWindow(m_hVideo, 318, 22, 793-318, 584-22, FALSE);

	////MCIWndPlay(m_hVideo);
	//MCIWndSetVolume(m_hVideo, 0);

	m_pSpawner->Initialize();
	m_pSpawner->Start_Spawn();
}

int CRythmGame::Update()
{

	Key_Input();
	for (auto& iter = m_vecNotes.begin(); iter != m_vecNotes.end(); )
	{
		if ((*iter)->Update())
		{
			if ((*iter)->Get_Type() == NOTE_TYPE::GAME_OVER)
			{
				SOUND_INST->StopSound(SOUND_BGM);
			}
			Safe_Delete(*iter);
			iter = m_vecNotes.erase(iter);

		}
		else if((*iter)->Get_YPos() > WINCY)
		{
			EFFECT_INST->Push_Rising_Effect({ (*iter)->Get_XPos(),(*iter)->Get_YPos()},EFFECT_ID::PLAYER_MISS);
			m_iCombo = 0;
			Safe_Delete(*iter);
			iter = m_vecNotes.erase(iter);

		}
		else
			iter++;
	}
	NOTE_SPAWN eNote = m_pSpawner->Update();
	if ( eNote.eType != NOTE_TYPE::REST && eNote.eType != NOTE_TYPE::END)
	{
		m_vecNotes.push_back(new CRythmNote(Get_XPos(eNote.iCOl),eNote.eType));
	}

	return 0;
}

void CRythmGame::Late_Update()
{
	for (auto& i : m_vecNotes)
	{
		i->Late_Update();
	}



}

void CRythmGame::Render(HDC hDC)
{


	//back
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMapDC, 0, 0, SRCCOPY);
	//frame
	GdiTransparentBlt(hDC,
		0, 0, WINCX, WINCY,
		m_hFrameDC, 0, 0, WINCX, WINCY,
		MAGENTA);
	//normal button dc
	GdiTransparentBlt(hDC,
		0, 0, WINCX, WINCY,
		m_hNormalButtonDC, 0, 0, WINCX, WINCY,
		MAGENTA);
	//normal button dc
	GdiTransparentBlt(hDC,
		318, 22, 793 - 318, 584 - 22,
		m_hIlustDC, 0, 0, 256, 224,
		MAGENTA);

	//BUTTONS
	for (int i = 0; i < 4; i++)
	{
		if (m_vecCurButtonStates[i])
		{
			GdiTransparentBlt(hDC,
				m_vecButtonPoints[i].x, m_vecButtonPoints[i].y,
				m_iButtonCX, m_iButtonCY,
				m_hClickButtonDC,
				m_iButtonCX*i, 0,
				m_iButtonCX, m_iButtonCY,
				MAGENTA);
		}
	}
	//NOTES
	for (auto& i : m_vecNotes)
	{
		i->Render(hDC);
	}
	//HIT EFFECTS
	EFFECT_INST->Render(hDC);

	//COMBO
		//콤보 숫자 
	int tmpCombo = m_iCombo;
	int idx = 0;
	while (idx < 3)
	{
		int iCur = tmpCombo % 10;
		m_vecComboNumbs[idx++]= iCur;
		tmpCombo /= 10;
	}
	m_iComboDigits = m_vecComboNumbs.size();

	int iCharWidt = m_iCOmboCharWidth1, iCharHeight = m_iCOmboCharHeight1;
	HDC hComboDC = m_hComboDC1;
	if (m_iCombo > 10)
	{
		iCharWidt = m_iCOmboCharWidth2; iCharHeight = m_iCOmboCharHeight2;
		hComboDC = m_hComboDC2;
	}
	int iWidth = iCharWidt * m_iComboDigits;
	int ileft = m_tComboPoint.x - iWidth / 2;
	int iTop = m_tComboPoint.y - iCharHeight / 2;

	for (int i = m_iComboDigits - 1; i >= 0; i--)
	{
		GdiTransparentBlt(hDC,
			ileft  + iCharWidt * (m_iComboDigits - i - 1),
			iTop ,
			iCharWidt,
			iCharHeight,
			hComboDC,
			iCharWidt * m_vecComboNumbs[i],
			0,
			iCharWidt,
			iCharHeight,
			MAGENTA);
	}
}

void CRythmGame::End()
{

}

void CRythmGame::Release()
{

	for (auto& i : m_vecNotes)
	{
		Safe_Delete(i);
	}
	m_vecNotes.clear();
	m_pSpawner->Release();
	MCIWndClose(m_hVideo);
}

void CRythmGame::Key_Input()
{
	m_vecCurButtonStates[0] = KEY_INST->Key_Pressing('Z');
	m_vecCurButtonStates[1] = KEY_INST->Key_Pressing('X');
	m_vecCurButtonStates[2] = KEY_INST->Key_Pressing('N');
	m_vecCurButtonStates[3] = KEY_INST->Key_Pressing('M');

	int iPressedIdx = -1;
	if (KEY_INST->Key_Down('Z'))
	{

		iPressedIdx = 0;
	}
	if (KEY_INST->Key_Down('X'))
	{
		iPressedIdx = 1;
	}
	if (KEY_INST->Key_Down('N'))
	{
		iPressedIdx = 2;
	}
	if (KEY_INST->Key_Down('M'))
	{
		iPressedIdx = 3;

	}
	if (iPressedIdx == -1)
		return;
	for (auto& i : m_vecNotes)
	{

		RECT rc;
		if (IntersectRect(&rc, &i->Get_Rect(), &m_vecButtonRects[iPressedIdx]))
		{
			if((rc.bottom - rc.top) >= 25)
				EFFECT_INST->Push_Effect({ (m_vecButtonRects[iPressedIdx].left + m_vecButtonRects[iPressedIdx].right) / 2, (m_vecButtonRects[iPressedIdx].top + m_vecButtonRects[iPressedIdx].bottom) / 2 }
				, EFFECT_ID::PLAYER_CRITICAL);
			else
				EFFECT_INST->Push_Effect({ (m_vecButtonRects[iPressedIdx].left + m_vecButtonRects[iPressedIdx].right) / 2, (m_vecButtonRects[iPressedIdx].top + m_vecButtonRects[iPressedIdx].bottom) / 2 }
				, EFFECT_ID::NORMAL_HIT);
			i->Set_Hit(true);
			m_iCombo++;
			return;
		}
	}

	EFFECT_INST->Push_Rising_Effect({ (m_vecButtonRects[iPressedIdx].left + m_vecButtonRects[iPressedIdx].right) / 2, (m_vecButtonRects[iPressedIdx].top + m_vecButtonRects[iPressedIdx].bottom) / 2 }
	, EFFECT_ID::PLAYER_MISS);
	m_iCombo = 0;
}

//NOte =====================================================================
CRythmNote::CRythmNote(int iXPos, NOTE_TYPE _eType)
{
	m_hNoteDC = BMP_INST->Find_Img(L"RYTHM_Note");
	m_iXPos = iXPos;
	m_eType = _eType;
}

bool CRythmNote::Update()
{
	if (m_bHit)
		return m_bDead;
	m_iYPos += m_iSpeed;
	Update_Rect();
	return m_bDead;
}

void CRythmNote::Update_Rect()
{
	m_tRect = { m_iXPos - m_iXSize / 2, m_iYPos - m_iYSize / 2, m_iXPos + m_iXSize / 2, m_iYPos + m_iYSize / 2 };
}

void CRythmNote::Late_Update()
{	

	if (m_dwSpeed + m_dwHittedTime < g_dwTime && m_bHit)
	{
		m_bDead = true;
	}

}

void CRythmNote::Render(HDC hdc)
{
	GdiTransparentBlt(hdc,
		m_tRect.left, m_tRect.top,
		m_iXSize, m_iYSize,
		m_hNoteDC,
		m_bHit * m_iXSize, 0,
		m_iXSize, m_iYSize,
		MAGENTA);
}

void CRythmNote::Set_Hit(bool bHit)
{
	 m_bHit = bHit; m_dwHittedTime = g_dwTime; 

}
