#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	TILE_X_COUNT = SCENE_INST->Get_MapX() / TILECX;
	TILE_Y_COUNT = SCENE_INST->Get_MapY() / TILECY;
	m_vecTile.clear();
	m_vecTile.reserve(TILE_X_COUNT * TILE_Y_COUNT);

	for (int i = 0; i < TILE_Y_COUNT; ++i)
	{
		for (int j = 0; j < TILE_X_COUNT; ++j)
		{
			float	fX = float((TILECX >> 1) + (TILECX * j));
			float	fY = float((TILECY >> 1) + (TILECY * i));

			CTile* pTile = new CTile;
			pTile->Set_Pos(fX, fY);
			pTile->Initialize();
			m_vecTile.push_back(pTile);
		}
	}

}

void CTileMgr::Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	// for (auto& pTile : m_vecTile)
	// 	pTile->Render(hDC);
	auto oldBrush =  SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));

	int iCullX = abs(int(CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX));
	int iCullY = abs(int(CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY));

	int	iMaxX = iCullX + (WINCX / TILECX) + 2;
	int	iMaxY = iCullY + (WINCY / TILECY) + 2;

	for (int i = iCullY; i < iMaxY; ++i)
	{
		for (int j = iCullX; j < iMaxX; ++j)
		{
			int	iIndex = i * TILE_X_COUNT + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(hDC);

		}
	}
	SelectObject(hDC, oldBrush);
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMgr::Picking_Tile(POINT pt, TILE_DATA _tData)
{
	int	x = pt.x / TILECX;
	int	y = pt.y / TILECY;

	int		iIndex = y * TILE_X_COUNT + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	m_vecTile[iIndex]->Set_Tile_Data(_tData);
}

CTile* CTileMgr::Get_Tile(POINT _pt)
{
	int	x = _pt.x / TILECX;
	int	y = _pt.y / TILECY;

	int		iIndex = y * TILE_X_COUNT + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return nullptr;
	return /*dynamic_cast<CTile*>*/(m_vecTile[iIndex]);
}


void CTileMgr::Save_Tile(SCENE_ID _eID)
{
	Save_Tile(Get_TileFilePath(_eID));
}

void CTileMgr::Load_Tile(SCENE_ID _eID)
{

	Load_Tile(Get_TileFilePath(_eID));
	Update();
}

LPCWSTR CTileMgr::Get_TileFilePath(SCENE_ID _eID)
{
	switch (_eID)
	{
	case SCENE_ID::TOWN:
		return L"../Data/Town.dat";
	case SCENE_ID::ROAD:
		return L"../Data/Road.dat";
	case SCENE_ID::MAGMA:
		return L"../Data/Magma.dat";
	case SCENE_ID::END:
	default:
		return nullptr;
	}

}

void CTileMgr::Save_Tile(LPCWSTR lpFileName)
{
	if (lpFileName == nullptr)
		return;
	HANDLE		hFile = CreateFile(lpFileName,		// 파일 경로와 이름을 명시
		GENERIC_WRITE,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정(null 지정 시 공유하지 않음)
		NULL,					// 보안 속성, NULL인 기본 값 설정 유지
		CREATE_ALWAYS,			// 생성 방식( CREATE_ALWAYS : 파일이 없다면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 불러오기)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성( FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"save Failed", _T("error"), MB_OK);
		return;
	}

	DWORD	dwByte(0);
	TILE_DATA	tTileData{ false, TILE_TYPE::NORMAL, -1};

	for (auto& pTile : m_vecTile)
	{
		tTileData = static_cast<CTile*>(pTile)->Get_Tile_Data();

		WriteFile(hFile, &(pTile->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &tTileData, sizeof(TILE_DATA), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save 완료", L"Success", MB_OKCANCEL);
}

void CTileMgr::Load_Tile(LPCWSTR lpFileName)
{
	if (lpFileName == nullptr)
		return;

	Initialize();

	HANDLE		hFile = CreateFile(lpFileName,		// 파일 경로와 이름을 명시
		GENERIC_READ,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정(null 지정 시 공유하지 않음)
		NULL,					// 보안 속성, NULL인 기본 값 설정 유지
		OPEN_EXISTING,			// 생성 방식( CREATE_ALWAYS : 파일이 없다면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 불러오기)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성( FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
		return;
	}

	DWORD	dwByte(0);
	TILE_DATA	tTileData{ false};
	INFO tInfo{};

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &tTileData, sizeof(TILE_DATA), &dwByte, nullptr);


		if (0 == dwByte)
			break;

		CTile* pTile = new CTile;
		pTile->Initialize();
		pTile->Set_Pos(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_Tile_Data(tTileData);

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}


bool CTileMgr::Collision_Block_Tile(INFO _tInfo)
{
	int	iXIdx =_tInfo.fX / TILECX;
	int	iYIdx = _tInfo.fY / TILECY;

	int	iIndex = iYIdx * TILE_X_COUNT + iXIdx;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return false;

	int iSearchStartX, iSearchStartY, iSearchEndX, iSearchEndY;
	iSearchStartX = (iXIdx - m_iSearchRange / 2) > 0 ? (iXIdx - m_iSearchRange / 2) : 0;
	iSearchEndX = (iXIdx + m_iSearchRange / 2) < TILE_X_COUNT? (iXIdx + m_iSearchRange / 2) : (TILE_X_COUNT-1);

	iSearchStartY = (iYIdx - m_iSearchRange / 2) > 0 ? (iYIdx - m_iSearchRange / 2) : 0;
	iSearchEndY = (iYIdx + m_iSearchRange / 2) < TILE_Y_COUNT ? (iYIdx + m_iSearchRange / 2) : (TILE_Y_COUNT-1);

	for (int y = 0; y <= iSearchEndY; y++)
	{
		for (int x = 0; x <= iSearchEndX; x++)
		{
			CTile* pTile = m_vecTile[y * TILE_X_COUNT + x];
			if (pTile->Get_Tile_Data().bBlock)
			{
				RECT	rc{};
				RECT	tObjCollisionRect = 
				{_tInfo.fX - _tInfo.fCX/2 ,
					_tInfo.fY - _tInfo.fCY / 2 ,
					_tInfo.fX + _tInfo.fCX / 2 ,
					_tInfo.fY + _tInfo.fCY / 2 ,
				};
				if (IntersectRect(&rc, &pTile->Get_CollisionRect(), &tObjCollisionRect))
				{
					return true;
				}
				
			}

		}
	}
	return false;
}

vector<CTile*>* CTileMgr::Get_Tiles(TILE_TYPE _eType)
{
	vector<CTile*>* ret = new vector<CTile*>;
	for (auto& tile : m_vecTile)
	{
		if (tile->Get_Tile_Data().eType == _eType)
			ret->push_back(tile);
	}
	return ret;
}
