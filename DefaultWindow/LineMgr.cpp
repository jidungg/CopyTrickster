#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*	CLineMgr::m_pInstance = nullptr;
CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& Line : m_LineList)
		Line->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float fX, float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& pLine : m_LineList)
	{
		if (fX >= pLine->Get_Info().tLeft.fX &&
			fX <= pLine->Get_Info().tRight.fX)
		{
			pTarget = pLine;
		}
	}

	if (!pTarget)
		return false;

	float		x1 = pTarget->Get_Info().tLeft.fX;
	float		y1 = pTarget->Get_Info().tLeft.fY;
	float		x2 = pTarget->Get_Info().tRight.fX;
	float		y2 = pTarget->Get_Info().tRight.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ���� ��ο� �̸��� ���
		GENERIC_READ,			// ���� ���� ���(GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,					// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���ؼ� ����(null ���� �� �������� ����)
		NULL,					// ���� �Ӽ�, NULL�� �⺻ �� ���� ����
		OPEN_EXISTING,			// ���� ���( CREATE_ALWAYS : ������ ���ٸ� ����, ������ ���� ����, OPEN_EXISTING : ������ ���� ��쿡�� �ҷ�����)
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�( FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����)
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(������� �ʱ� ������ NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
		return;
	}

	DWORD	dwByte(0);
	LINE	tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tLine.tLeft, tLine.tRight));
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"load �Ϸ�", L"Success", MB_OKCANCEL);
}
