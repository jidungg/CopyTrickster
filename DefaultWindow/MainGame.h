#pragma once

#include "Player.h"
#include "ObjMgr.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

	void		Load_Resources();
private:
#pragma region ����
	//CObj*		m_pPlayer;
	//list<CObj*>	m_BulletList;
#pragma endregion ����
	

	HDC			m_DC;
	DWORD		m_dwTime;
	int			m_iFps;
	TCHAR		m_szFPS[32];

};

// ������ ����
// : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ������ ����

// https://refactoring.guru/ko/design-patterns

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ ��Ŵ, ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ ��
// �ݺ��� ���� : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����

// �޵����� ����(������) : ��ȣ�ۿ��ϴ� ��ü���� ���� ������ ���踦 �ΰ� ���� ��� ������ �������� �����Ͽ� �����ϴ� ��ü�� �δ� ����
// �� �� �ٰ� �ƴ� 1 �� N�� ���踦 ����

// �̱��� ���� : �� �ϳ��� �ν��Ͻ�(��ü)�� �����Ͽ� ����ϴ� ����, �Ȱ��� �ν��Ͻ��� ��� �������� �ʰ� ������ ������� ��ü�� �ҷ��ͼ� ����ϴ� ����
