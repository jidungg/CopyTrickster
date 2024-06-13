// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;
DWORD   g_dwTime;
bool    g_bEditMode = false;
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);			
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// �޼��� ó����(�Լ�)
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// � ü���� �ο��ϴ� ���� �ĺ� ��ȣ�� ����, ���α׷� �ν��Ͻ���� �Ҹ�
                     _In_opt_ HINSTANCE hPrevInstance,	// ���� ����Ǿ��� �ν��Ͻ� �ڵ�(���� ��� NULL, ȣȯ���� ���� ����)
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)			 // ������ â�� ��Ÿ�� �ɼ�(��� /�ּ�ȭ, �ִ�ȭ ��� ��)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
   
	// ������ ���� ��� ����
	MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame	MainGame;
	MainGame.Initialize();



    // �⺻ �޽��� �����Դϴ�.
  //  while (GetMessage(&msg, nullptr, 0, 0))
  //  {
		//// �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
  //      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
  //      {
		//	// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ��� �� �� �ֵ��� ���ִ� �Լ�
  //          TranslateMessage(&msg);

		//	// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ����� �����ϴ� �Լ�
  //          DispatchMessage(&msg);
  //      }
  //  }

	while (true)
	{
		// PM_REMOVE : �޼��� ť�κ��� �޼����� �о�Ȱ� ���ÿ� �޼��� ť���� ����
		// PM_NOREMOVE : �޼��� ť���� �޼����� ���� ���θ� �ľ�, �޼����� �о������ GetMessage�� �ٽ� ȣ���ؾ� ��
		
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ��� �� �� �ֵ��� ���ִ� �Լ�
				TranslateMessage(&msg);

				// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ����� �����ϴ� �Լ�
				DispatchMessage(&msg);
			}
		}		
		else
		{

			DWORD	dwTime = GetTickCount();
			if (g_dwTime + 10< dwTime)
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				g_dwTime = dwTime;
				
			 }		
		}
	}


    return (int) msg.wParam;
}	


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);		// â ������ ����

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	// ������ ��Ÿ���� ����, � ���¸� ���� ������ ���� 

	// CS_HREDRAW : ���θ� �ٽ� �׸�
	// CS_VREDRAW : ���θ� �ٽ� �׸�

    wcex.lpfnWndProc    = WndProc;		// �����ص� �Լ��� ȣ��Ǿ� �޼����� ó��

    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
	// �����찡 Ư���� �������� ����ϴ� ������ ����
	// ������ ���� �����̸� ������� �ʴ� ��� 0

    wcex.hInstance      = hInstance;
	// �� ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ�� ����

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// ������ â�� ����� ������ ����

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	// ������ â���� ����� ���콺 Ŀ��
	
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// ������ �۾� ������ ��� ���� ����

	wcex.lpszMenuName = NULL;	
	//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	// �޴� ����

    wcex.lpszClassName  = szWindowClass;
	// ���� ������ �̸��� ����, (������Ʈ �̸��� ��ġ���� �ۼ�)
	
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// ������ ��ܿ� ���� ������ ��� ����

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT	rc{ 0, 0, WINCX, WINCY };

   // rc = ������ rc ũ�� + �⺻ â �ɼ� + �޴� �� ũ�� ��� ����
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, 
							 szTitle, 
							 WS_OVERLAPPEDWINDOW, // ������� �ϴ� ������ ��Ÿ�� ����(�⺻ �� ����ϴ� ���)
							CW_USEDEFAULT, 0,	// �����Ǵ� â�� X,Y ��ǥ
							rc.right- rc.left, 
							rc.bottom - rc.top,	// �����Ǵ� â�� ����, ���� ������
							nullptr,	// �θ� �����찡 �ִٸ� �θ� ������ �ڵ� ����
							nullptr,	// �����쿡�� ����� �޴��� �ڵ�
							hInstance, 
							nullptr);		//�ü���� Ư���� �������� �����

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// 1. kernel : �޸𸮸� �����ϰ� ���α׷��� ����
// 2. user : ���� �������̽��� ������(â)�� ����
// 3. gdi : ȭ�� ó���� �׷����� ���

RECT			rc{ 100, 100, 200, 200 };
list<RECT>		BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//case WM_CREATE:
	//	SetTimer(hWnd, 0, 0, 0);
	//	// Ÿ�̸Ӹ� ����(������ �ڵ�, Ÿ�̸� id��ȣ, Ÿ�̸� �ֱ�, NULL�� ��� ������ �ֱ��� WM_TIMER �޼��� �߻�)
	//	// 3���� : 0�� ��� 1000�� 1���� ����
	//	// 4���� : 3������ �ֱ��� WM_TIMER �޼��� �߻�
	//	break;

	//case WM_TIMER:
	//	InvalidateRect(hWnd, 0, TRUE);
	//	// ������ ȭ�� ���� �Լ�(�Լ� ȣ�� ��, WM_PAINT �޼����� �߻�)

	//	// InvalidateRect(������ �������� �ڵ�, ������ �ȿ� ������ ���� ����, �� �Ǵ� ����)
	//	// 2���� : RECT�� �ּҸ� ������, NULL�� ��� ������ ��ü ������ ����
	//	// 3���� : TRUE�� ���, �׷��� ���� �ʴ� �κе� ����
	//	//	      FALSE �� ���, ���� �׸��� �κи� ����
	//	break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;

	/*	case VK_RIGHT:
			rc.left  += 10;
			rc.right += 10;
			break;

		case VK_LEFT:
			rc.left -= 10;
			rc.right -= 10;
			break;

		case VK_UP:
			rc.top   -= 10;
			rc.bottom -= 10;
			break;

		case VK_DOWN:
			rc.top += 10;
			rc.bottom += 10;
			break;

		case VK_SPACE:
			BulletList.push_back(rc);
			break;*/
		}
		break;

   // case WM_PAINT:
   //     {
   //         PAINTSTRUCT ps;

			//// HDC : ��¿� ���� ������ �����ϴ� ����ü
   //         HDC hdc = BeginPaint(hWnd, &ps);

			//// �׸��� �Լ�(�׸��� �Լ����� ���� ���� ���� �׸��⸦ hdc�� �׸�)

			//// MoveToEx : Ŀ�� �����͸� �̵���Ű�� �Լ�
			//// NULL : Ŀ���� �̵��ϱ� �� ��ġ�� output �������� ��ȯ
			////MoveToEx(hdc, 100, 100, NULL);
			////
			////// �� �׸��� �Լ�
			////LineTo(hdc, 200, 200);
			////LineTo(hdc, 200, 300);

			//// MoveToEx(hdc, 100, 100, NULL);
			//// LineTo(hdc, 200, 100);
			//// LineTo(hdc, 200, 200);
			//// LineTo(hdc, 100, 200);
			//// LineTo(hdc, 100, 100);
			//// LineTo(hdc, 200, 200);
			//// 
			//// MoveToEx(hdc, 100, 200, NULL);
			//// LineTo(hdc, 200, 100);

			//// �簢�� �׸��� �Լ�
			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			//// �� �׸��� �Լ�
			////Ellipse(hdc, 300, 300, 400, 400);

			//for (auto& iter : BulletList)
			//{
			//	Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

			//	iter.top    -= 10;
			//	iter.bottom -= 10;
			//}

   //         EndPaint(hWnd, &ps);
   //     }
   //     break;

    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// �Լ� ȣ�� �Ծ�

// �Լ��� ������ ����Ǹ� �Ҵ�Ǿ��� ������ �����ؾ� �ϴµ�
// �Լ��� ȣ���� ȣ���(CALLER)���� ������ ������ �ƴϸ�
// ȣ�� ���� ��ȣ����(CALLEE)���� ���� �� ���� ���� ���

// __cdecl : c / c++ ����� �⺻ ȣ�� �Ծ�, ȣ���(caller)�� ������ ����
// ���� �ڱ� �ڽſ��� �Ű� ������ �󸶳� ������ ��(���� ���� �Լ�), �� ������ ������ stack�� ���� �� �� ����

// __stdcall : winapi�� �⺻ ȣ�� �Ծ�, ��ȣ����(callee)�� ������ ����
// - api���� �����ϴ� ��κ��� �Լ����� __stdcall ������� '���� ���� �Լ�'
// - �Ű� ������ �����Ǿ� �־� ��ȣ���ڰ� � ���� ������ �˰� �־� ������ �޸𸮸� ���� ����

// __fastcall : ecx�� edx��� �������͸� ���� ����, �������� �޸𸮸� ����Ͽ� �����ϱ� ������ �Լ� ȣ�� �ӵ��� ������
// __thiscall : this �����͸� �Ű� ������ �Ѱ� ���� �� ���Ǿ����� ȣ�� �Ծ�


// 1. �׸��� ����
// 2. �����̽� �ٸ� ���� ��� ���� ������ �Ѿ��� �߻��ϰ� ������
