#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void	Initialize(); 
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	void		Picking_Tile(POINT pt, TILE_DATA _tData);
	CTile*		Get_Tile(POINT _pt);	
	LPCWSTR		Get_TileFilePath(SCENE_ID _eID);

	void		Save_Tile(LPCWSTR lpFileName);
	void		Load_Tile(LPCWSTR lpFileName);
	void		Save_Tile(SCENE_ID _eID);
	void		Load_Tile(SCENE_ID _eID);
	bool		Collision_Block_Tile(INFO _tInfo);
	vector<CTile*>* Get_Tiles(TILE_TYPE _eType);
	int			Get_MAP_Width() { return TILE_X_COUNT * TILECX; }
	int			Get_MAP_Height() { return TILE_Y_COUNT * TILECY; }
public:
	static CTileMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;

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

private:
	static CTileMgr*	m_pInstance;
	vector<CTile*>		m_vecTile;
	int TILE_X_COUNT = 0;
	int TILE_Y_COUNT = 0;
	int m_iSearchRange = 4;
};
#define TILE_INST CTileMgr::Get_Instance()
