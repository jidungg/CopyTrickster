// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;
DWORD   g_dwTime;
bool    g_bEditMode = false;
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);			
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// 메세지 처리기(함수)
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 운영 체제가 부여하는 고유 식별 번호를 저장, 프로그램 인스턴스라고 불림
                     _In_opt_ HINSTANCE hPrevInstance,	// 전에 실행되었던 인스턴스 핸들(없을 경우 NULL, 호환성을 위해 존재)
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)			 // 실행한 창의 스타일 옵션(모양 /최소화, 최대화 모양 등)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
   
	// 윈도우 생성 모양 지정
	MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame	MainGame;
	MainGame.Initialize();



    // 기본 메시지 루프입니다.
  //  while (GetMessage(&msg, nullptr, 0, 0))
  //  {
		//// 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
  //      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
  //      {
		//	// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용 할 수 있도록 해주는 함수
  //          TranslateMessage(&msg);

		//	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수에게 전달하는 함수
  //          DispatchMessage(&msg);
  //      }
  //  }

	while (true)
	{
		// PM_REMOVE : 메세지 큐로부터 메세지를 읽어옴과 동시에 메세지 큐에서 제거
		// PM_NOREMOVE : 메세지 큐에서 메세지의 존재 여부만 파악, 메세지를 읽어오려면 GetMessage를 다시 호출해야 함
		
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용 할 수 있도록 해주는 함수
				TranslateMessage(&msg);

				// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수에게 전달하는 함수
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

    wcex.cbSize = sizeof(WNDCLASSEX);		// 창 사이즈 저장

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	// 윈도우 스타일을 정의, 어떤 형태를 가질 것인지 지정 

	// CS_HREDRAW : 가로를 다시 그림
	// CS_VREDRAW : 세로를 다시 그림

    wcex.lpfnWndProc    = WndProc;		// 저장해둔 함수가 호출되어 메세지를 처리

    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
	// 윈도우가 특수한 목적으로 사용하는 여분의 공간
	// 일종의 예약 영역이며 사용하지 않는 경우 0

    wcex.hInstance      = hInstance;
	// 이 윈도우 클래스를 사용하는 프로그램의 번호를 설정

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// 윈도우 창이 사용할 아이콘 지정

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	// 윈도우 창에서 사용할 마우스 커서
	
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// 윈도우 작업 영역의 배경 색을 설정

	wcex.lpszMenuName = NULL;	
	//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
	// 메뉴 설정

    wcex.lpszClassName  = szWindowClass;
	// 실행 파일의 이름을 저장, (프로젝트 이름과 일치시켜 작성)
	
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// 윈도우 상단에 작은 아이콘 모양 지정

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT	rc{ 0, 0, WINCX, WINCY };

   // rc = 원래의 rc 크기 + 기본 창 옵션 + 메뉴 바 크기 고려 여부
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, 
							 szTitle, 
							 WS_OVERLAPPEDWINDOW, // 만들고자 하는 윈도우 스타일 지정(기본 값 사용하는 모양)
							CW_USEDEFAULT, 0,	// 생성되는 창의 X,Y 좌표
							rc.right- rc.left, 
							rc.bottom - rc.top,	// 생성되는 창의 가로, 세로 사이즈
							nullptr,	// 부모 윈도우가 있다면 부모 윈도우 핸들 지정
							nullptr,	// 윈도우에서 사용할 메뉴의 핸들
							hInstance, 
							nullptr);		//운영체제가 특수한 목적으로 사용함

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 1. kernel : 메모리를 관리하고 프로그램을 실행
// 2. user : 유저 인터페이스와 윈도우(창)를 관리
// 3. gdi : 화면 처리와 그래픽을 담당

RECT			rc{ 100, 100, 200, 200 };
list<RECT>		BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//case WM_CREATE:
	//	SetTimer(hWnd, 0, 0, 0);
	//	// 타이머를 지정(윈도우 핸들, 타이머 id번호, 타이머 주기, NULL인 경우 설정한 주기대로 WM_TIMER 메세지 발생)
	//	// 3인자 : 0인 경우 1000당 1초의 개념
	//	// 4인자 : 3인자의 주기대로 WM_TIMER 메세지 발생
	//	break;

	//case WM_TIMER:
	//	InvalidateRect(hWnd, 0, TRUE);
	//	// 윈도우 화면 갱신 함수(함수 호출 시, WM_PAINT 메세지를 발생)

	//	// InvalidateRect(갱신할 윈도우의 핸들, 윈도우 안에 갱신할 범위 지정, 참 또는 거짓)
	//	// 2인자 : RECT의 주소를 받으며, NULL인 경우 윈도우 전체 영역에 적용
	//	// 3인자 : TRUE인 경우, 그려져 있지 않는 부분도 갱신
	//	//	      FALSE 인 경우, 새로 그리는 부분만 갱신
	//	break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
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

			//// HDC : 출력에 관한 정보를 저장하는 구조체
   //         HDC hdc = BeginPaint(hWnd, &ps);

			//// 그리기 함수(그리기 함수들을 통해 각종 도형 그리기를 hdc에 그림)

			//// MoveToEx : 커퍼 포인터를 이동시키는 함수
			//// NULL : 커서를 이동하기 전 위치를 output 형식으로 반환
			////MoveToEx(hdc, 100, 100, NULL);
			////
			////// 선 그리기 함수
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

			//// 사각형 그리기 함수
			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			//// 원 그리기 함수
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

// 정보 대화 상자의 메시지 처리기입니다.
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

// 함수 호출 규약

// 함수의 실행이 종료되면 할당되었던 스택을 해제해야 하는데
// 함수를 호출한 호출원(CALLER)에서 정리할 것인지 아니면
// 호출 받은 피호출자(CALLEE)에서 정리 할 지에 대한 약속

// __cdecl : c / c++ 언어의 기본 호출 규약, 호출원(caller)이 스택을 정리
// 정작 자기 자신에게 매개 변수가 얼마나 들어올지 모름(가변 인자 함수), 그 때문에 본인이 stack을 정리 할 수 없음

// __stdcall : winapi의 기본 호출 규약, 피호출자(callee)가 스택을 정리
// - api에서 제공하는 대부분의 함수들이 __stdcall 방식으로 '고정 인자 함수'
// - 매개 변수가 고정되어 있어 피호출자가 어떤 것이 들어올지 알고 있어 스스로 메모리를 정리 가능

// __fastcall : ecx와 edx라는 레지스터를 통해 저장, 레지스터 메모리를 사용하여 동작하기 때문에 함수 호출 속도가 빨라짐
// __thiscall : this 포인터를 매개 변수로 넘겨 받을 때 사용되어지는 호출 규약


// 1. 그리기 숙제
// 2. 스페이스 바를 누를 경우 위로 나가는 총알을 발사하게 만들어라
