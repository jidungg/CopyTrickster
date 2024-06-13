#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);
	
	m_hBitmap = (HBITMAP)LoadImage(NULL,	// ���α׷� �ν��Ͻ� �ڵ�(���Ϸκ��� �о���� NULL��)
								pFilePath,  // ������ ��θ� ����								
								IMAGE_BITMAP,// � Ÿ���� �о���� ����(��Ʈ�� ����)
								0, 0,			// �̹��� ����, ���� ������(���Ͽ��� �б� ������ ������ �������� ����)
								LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ϸ� �̹��� �о���� LR_CREATEDIBSECTION : �о�� ������ DIB���·� ��ȯ

	// SelectObject : �غ��� dc�� gdi ������Ʈ�� �ҷ��� ��Ʈ���� �����ϱ� ���� ���
	// gdi ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release()
{
	// ���� dc�� ���õ� gdi ������Ʈ�� ���� �� �� ����
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);
}
