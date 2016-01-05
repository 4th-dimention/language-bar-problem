/*
 * Experiments with language/layout stuff for win32.
 * 04.01.2016 (dd.mm.yyyy)
 * Allen Webster
 */

// TOP

#include <Windows.h>

struct Win32Vars{
    int keep_playing;
} win32;

LRESULT WinCallback(
  HWND   hwnd,
  UINT   uMsg,
  WPARAM wParam,
  LPARAM lParam
                    ){
    LRESULT result = 0;
    switch(uMsg){
    case WM_QUIT:
    case WM_DESTROY:
    {
        win32.keep_playing = 0;
    }break;
    
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    {
        SetCapture(hwnd);
    }break;
        
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    {
        ReleaseCapture();
    }break;
    
    default:
    {
        result = DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }break;
    }
    return(result);
}

int WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nCmdShow
            ){
    WNDCLASS winclass = {};
    winclass.style = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = WinCallback;
    winclass.hInstance = hInstance;
    winclass.lpszClassName = "lang-test-class";
    
    ATOM winclassatom = RegisterClass(&winclass);
    
    if (winclassatom == 0){
        return(1);
    }
    
    HWND window = CreateWindow(
        "lang-test-class",
        "lang test window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        400,
        0,
        0,
        hInstance,
        0);

    if (window == 0){
        return(2);
    }
    
    ShowWindow(window, SW_SHOW);

    // NOTE(allen): This is here to investigate what happens when the layout
    // is changed in code. I observed the language bar updating what it displayed
    // on Windows 7. If you only have one layout loaded, nothing will happen here.
    HKL locales[2];
    int locale_count = GetKeyboardLayoutList(2, locales);
    if (locale_count > 1){
        ActivateKeyboardLayout(locales[1], 0);
    }
    
    for (win32.keep_playing = 1; win32.keep_playing;){
        MSG msg;
        GetMessage(&msg, window, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return(0);
}

// BOTTOM


