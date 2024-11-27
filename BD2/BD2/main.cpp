#include "disk_deque.h"
#include <windows.h>
#include <string>

HINSTANCE g_hInst;
HWND g_hMainWnd;
HWND g_hNumeroDi, g_hNumeroPl, g_hNumeroPi, g_hCapacidad, g_hOutput, g_hBtnGenerar;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnGenerateClicked();
std::wstring ConvertToWString(const std::string& str);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    g_hInst = hInstance;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Eliminar fondo blanco
    wc.lpszClassName = TEXT("DiskDequeClass");

    RegisterClass(&wc);

    g_hMainWnd = CreateWindow(wc.lpszClassName, TEXT("Disk Deque GUI"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInstance, NULL);

    ShowWindow(g_hMainWnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindow(TEXT("static"), TEXT("Número de platos:"), WS_VISIBLE | WS_CHILD,
            10, 10, 150, 20, hwnd, NULL, g_hInst, NULL);
        g_hNumeroDi = CreateWindow(TEXT("edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            170, 10, 100, 20, hwnd, NULL, g_hInst, NULL);

        CreateWindow(TEXT("static"), TEXT("Número de superficies:"), WS_VISIBLE | WS_CHILD,
            10, 40, 150, 20, hwnd, NULL, g_hInst, NULL);
        g_hNumeroPl = CreateWindow(TEXT("edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            170, 40, 100, 20, hwnd, NULL, g_hInst, NULL);

        CreateWindow(TEXT("static"), TEXT("Número de sectores por pista:"), WS_VISIBLE | WS_CHILD,
            10, 70, 200, 20, hwnd, NULL, g_hInst, NULL);
        g_hNumeroPi = CreateWindow(TEXT("edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            220, 70, 100, 20, hwnd, NULL, g_hInst, NULL);

        CreateWindow(TEXT("static"), TEXT("Capacidad de sector:"), WS_VISIBLE | WS_CHILD,
            10, 100, 150, 20, hwnd, NULL, g_hInst, NULL);
        g_hCapacidad = CreateWindow(TEXT("edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            170, 100, 100, 20, hwnd, NULL, g_hInst, NULL);

        g_hBtnGenerar = CreateWindow(TEXT("button"), TEXT("Generar Estructura"), WS_VISIBLE | WS_CHILD,
            10, 130, 150, 30, hwnd, (HMENU)1, g_hInst, NULL);

        g_hOutput = CreateWindow(TEXT("edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            10, 170, 560, 200, hwnd, NULL, g_hInst, NULL);
        break;

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT:
        return (INT_PTR)GetStockObject(NULL_BRUSH); // Aplicar el fondo transparente a los controles

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            OnGenerateClicked();
        }
        break;

    case WM_SIZE: {
        RECT rect;
        GetClientRect(hwnd, &rect);

        SetWindowPos(g_hNumeroDi, NULL, 170, 10, rect.right - 180, 20, SWP_NOZORDER);
        SetWindowPos(g_hNumeroPl, NULL, 170, 40, rect.right - 180, 20, SWP_NOZORDER);
        SetWindowPos(g_hNumeroPi, NULL, 220, 70, rect.right - 230, 20, SWP_NOZORDER);
        SetWindowPos(g_hCapacidad, NULL, 170, 100, rect.right - 180, 20, SWP_NOZORDER);
        SetWindowPos(g_hBtnGenerar, NULL, 10, 130, rect.right - 20, 30, SWP_NOZORDER);
        SetWindowPos(g_hOutput, NULL, 10, 170, rect.right - 20, rect.bottom - 180, SWP_NOZORDER);
    }
                break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void OnGenerateClicked() {
    wchar_t buffer[256];

    GetWindowText(g_hNumeroDi, buffer, sizeof(buffer) / sizeof(buffer[0]));
    int numero_di = _wtoi(buffer);

    GetWindowText(g_hNumeroPl, buffer, sizeof(buffer) / sizeof(buffer[0]));
    int numero_pl = _wtoi(buffer);

    GetWindowText(g_hNumeroPi, buffer, sizeof(buffer) / sizeof(buffer[0]));
    int numero_pi = _wtoi(buffer);

    GetWindowText(g_hCapacidad, buffer, sizeof(buffer) / sizeof(buffer[0]));
    int capacidad = _wtoi(buffer);

    int numero_su = 2;

    Disk_Deque disco(numero_di, numero_pi, numero_pl, numero_su, capacidad);
    std::string result = disco.mostrar();
    std::wstring wresult = ConvertToWString(result);
    SetWindowText(g_hOutput, wresult.c_str());
}

std::wstring ConvertToWString(const std::string& str) {
    int len;
    int slength = static_cast<int>(str.length()) + 1;
    len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);
    std::wstring r(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, &r[0], len);
    return r;
}
