#pragma once

#include "Logo.h"


class CSceneMgr
{
public:

private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Initialize();
	void	Scene_Change(SCENE_ID eScene);
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	int Get_MapX() { return m_pScene->Get_MapX(); }
	int Get_MapY() { return m_pScene->Get_MapY(); }
	SCENE_ID Get_Scene_ID() { return m_pScene->Get_Scene_ID(); }
	void Revive();
private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	SCENE_ID				m_ePreScene;
	SCENE_ID				m_eCurScene;
	map<SCENE_ID,CScene*> m_vecScene;
};

#define SCENE_INST CSceneMgr::Get_Instance()
// state ����(���� ����) : FSM(���� ���� ��� : �ڽ��� ���� �� �ִ� ������ ������ ���¸� ����)�� ������� �ϴ� ��ü ���¸� ǥ���ϴ� ����, ���� �ϳ��� ���¸��� ���ϵ��� ����� ����
