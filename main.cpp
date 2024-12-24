
#include <windows.h>

#include "sound.h"

using namespace std;

Sound sound;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  switch (message) {
    case WM_LBUTTONDOWN: {
      int x = (short)LOWORD(lParam);
      int y = (short)LOWORD(lParam);

      RECT rect;
      GetWindowRect(hWnd, &rect);
      int winWidth = rect.right - rect.left;
      int winHeight = rect.bottom - rect.top;
      sound.play(x, y, winWidth, winHeight);
    } break;
    case WM_LBUTTONUP: {
      sound.pause();
    } break;

    case WM_MOUSEMOVE: {
      if (wParam & MK_LBUTTON) {
        int x = (short)LOWORD(lParam);
        int y = (short)LOWORD(lParam);

        RECT rect;
        GetWindowRect(hWnd, &rect);
        int winWidth = rect.right - rect.left;
        int winHeight = rect.bottom - rect.top;
        sound.play(x, y, winWidth, winHeight);
      }
    } break;


    case WM_DESTROY:
        sound.destroy();
        PostQuitMessage(0);
        break;
    default:
      return DefWindowProc(hWnd, message, wParam,lParam);
  }
  return 0;
}

// "main function for windows application"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  // windows class

  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = (WNDPROC)WndProc;
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

  HWND hWnd = CreateWindow(
      L"SoundWindowClass", L"Orquesta", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  // display window
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}
