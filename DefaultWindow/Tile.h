#pragma once
#include "Obj.h"

enum class TILE_TYPE
{
	NORMAL,
	MONSTER,//MONSTER_ID
	NPC,
	PORTAL,
	ENV,
	END
};

typedef struct tagTileData
{
	bool bBlock;
	TILE_TYPE eType;
	int iOption;
}TILE_DATA;
class CTile 
{
public:
	CTile();
	CTile(TILE_DATA _tData);
	virtual ~CTile();

public:
	void		Set_Tile_Data(TILE_DATA _tData) { m_tTileData = _tData; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Block(bool _bBlock) { m_tTileData.bBlock=_bBlock; };

	TILE_DATA	Get_Tile_Data() { return m_tTileData; }
	INFO		Get_Info() { return m_tInfo; }
	RECT		Get_CollisionRect() { return m_tCollisionRect; }
	POINT		Get_Pos() { return { (int)m_tInfo.fX, (int)m_tInfo.fY }; }
	float		Get_RX() { return m_tInfo.fRX; }
	float		Get_RY() { return m_tInfo.fRY; }
	float		Get_CX() { return m_tInfo.fCX; }
	float		Get_CY() { return m_tInfo.fCY; }
public:

	virtual void Initialize() ;
	virtual int Update() ;
	virtual void Late_Update() ;
	virtual void Render(HDC hDC);
	virtual void Release() ;

	void		Update_Rect();

private:
	TILE_DATA	m_tTileData;

	RECT		m_tCollisionRect;
	INFO		m_tInfo;

};

