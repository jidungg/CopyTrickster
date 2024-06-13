#include "stdafx.h"
#include "Intro.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "MouseMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

void CIntro::Initialize()
{
	m_hLoadingDC = BMP_INST->Find_Img(L"UI_Loading_Ilu3");
	m_hGameStartButtonDC = BMP_INST->Find_Img(L"UI_GameStart");
	m_tButtonRect = {
		WINCX / 2 - m_iButtonWidth / 2 ,
		WINCY / 2,
		WINCX / 2 + m_iButtonWidth / 2,
		WINCY / 2 + m_iButtonHeight
	};
}

void CIntro::Start(SCENE_ID _ePrevScene)
{
	SOUND_INST->PlayBGM(L"trickster_new.mp3", 0.2);

}

int CIntro::Update()
{
	POINT pt = MOUSE_INST->Get_Mouse_Point();
	if (PtInRect(&m_tButtonRect, pt))
	{
		if (KEY_INST->Key_Pressing(VK_LBUTTON))
		{
			m_iButtonState = (int)BUTTON_STATE::PRESSED;
		}
		else if (KEY_INST->Key_Up(VK_LBUTTON))
		{
			m_iButtonState = (int)BUTTON_STATE::HOVER;
			SOUND_INST->StopSound(SOUND_BGM);
			SOUND_INST->PlaySoundW(L"ui_user_ok.wav",CHANNELID::SOUND_CLICK,1);
			SCENE_INST->Scene_Change(SCENE_ID::TOWN);
		}
		else
		{
			m_iButtonState = (int)BUTTON_STATE::HOVER;
		}
	}
	else
	{
		m_iButtonState = (int)BUTTON_STATE::NORMAL;
	}

	return 0;
}

void CIntro::Late_Update()
{
}

void CIntro::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY,
		m_hLoadingDC, 0, 0,
		SRCCOPY);
	GdiTransparentBlt(hDC,
		m_tButtonRect.left, m_tButtonRect.top, m_iButtonWidth, m_iButtonHeight,
		m_hGameStartButtonDC,
		m_iButtonState*m_iButtonWidth,0,m_iButtonWidth,m_iButtonHeight,
		MAGENTA);
}

void CIntro::End()
{
}

void CIntro::Release()
{
}
