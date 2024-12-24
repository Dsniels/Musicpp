
#include <windows.h>

#include "sound.h"

using namespace std;

// "main function for windows application"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  // windows class

  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  // wcex.lpfnWndProc = (WNDPROC)WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = 0;
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = 0;
  wcex.lpszClassName = L"SoundWindowClass";
  wcex.hIconSm = 0;

  // register the window class
  RegisterClassEx(&wcex);

  HWND hWnd =
      CreateWindow(L"SoundWindowClass", L"Orquesta",
                   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                   CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);


//display window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    MSG msg;
    while(GetMessage(&msg, NULL, 0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
