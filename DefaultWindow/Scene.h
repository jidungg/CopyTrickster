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
	//타일매니저는 타일 정보(갈 수 있는지 없는지) 로딩
	//씬에서는 Init에서 맵 요소들 등록.
	//  NPC(위치, ID), 포탈(위치, 연결된 씬), 몹 스포너(위치, 소환할 몹) 등 지정
	//Start 시 등록된 요소들 소환.
	//Update 에서 스포너 시간 업데이트. 
protected:
	SCENE_ID m_eID;
	TCHAR* m_pMapBMPKey;
	HDC m_hMapDC;
	int m_iMapX = 0;
	int m_iMapY = 0;

	vector<CMonsterSpawner*> m_vecMonSpawner;
	vector<ENV_DATA*> m_vecEnvData;
};

