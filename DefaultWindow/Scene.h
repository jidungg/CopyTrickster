#pragma once

#include "Define.h"



class CMonsterSpawner;
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize();
	virtual void    Start(SCENE_ID _ePrevScene);
	virtual int		Update()	;
	virtual void	Late_Update()	;
	virtual void	Render(HDC hDC)	;
	virtual void    End();
	virtual void	Release();
	
	int Get_MapX() { return m_iMapX; }
	int Get_MapY() { return m_iMapY; }
	SCENE_ID Get_Scene_ID() { return m_eID; }
	void Revive();
	//Ÿ�ϸŴ����� Ÿ�� ����(�� �� �ִ��� ������) �ε�
	//�������� Init���� �� ��ҵ� ���.
	//  NPC(��ġ, ID), ��Ż(��ġ, ����� ��), �� ������(��ġ, ��ȯ�� ��) �� ����
	//Start �� ��ϵ� ��ҵ� ��ȯ.
	//Update ���� ������ �ð� ������Ʈ. 
protected:
	SCENE_ID m_eID;
	TCHAR* m_pMapBMPKey;
	HDC m_hMapDC;
	int m_iMapX = 0;
	int m_iMapY = 0;

	vector<CMonsterSpawner*> m_vecMonSpawner;
	vector<ENV_DATA*> m_vecEnvData;
};

