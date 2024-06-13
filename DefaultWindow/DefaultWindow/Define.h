#pragma once

#define			PURE	= 0

#define			WINCX	800
#define			WINCY	600


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}


typedef struct tagInfo
{
	float	fX;		// ���� X
	float	fY;		// ���� Y

	float	fCX;	// ���� ������
	float	fCY;	// ���� ������

}INFO;

extern HWND g_hWnd;