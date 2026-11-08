#ifndef ShortWA_H
#define ShortWA_H

#include <windows.h>
#include <stddef.h>

// =========================================================================
// SHORTWA ADATSTRUKTÚRA
// =========================================================================
typedef struct {
    HWND hwnd;          // Az ablak egyedi Windows azonosítója
    HINSTANCE hinstance;// Az alkalmazáspéldány azonosítója
    int width;          // Az ablak szélessége pixelben
    int height;         // Az ablak magassága pixelben
    int is_running;     // A játékhurok futási jelzője (1 = fut, 0 = leállt)
} ShortwaWindow;

// =========================================================================
// 1. AZ ABLAK AGYA (WINDOW PROCEDURE)
// =========================================================================
static inline LRESULT CALLBACK ShortWA_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hWnd); // Megkérjük a Windowst az ablak bezárására
            return 0;
            
        case WM_DESTROY:
            PostQuitMessage(0);  // Bedobjuk a WM_QUIT üzenetet a postaládába
            return 0;
    }
    // KÖTELEZŐ BIZTONSÁGI HÁLÓ: Amit nem kezelünk, azt visszaadjuk a Windowsnak
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// =========================================================================
// 2. A POSTALÁDA ÜRÍTŐ (POLL EVENTS)
// =========================================================================
static inline void Shortwa_PollEvents(ShortwaWindow* win) {
    MSG msg;
    
    // Addig pörgünk, amíg a PeekMessage talál üzenetet a postaládában
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg); // Ez küldi át az üzenetet a ShortWA_WindowProc-nak
        
        // Ha a Windows azt mondja, hogy a folyamat lezárult
        if (msg.message == WM_QUIT) {
            win->is_running = 0; // Leállítjuk a Shortwa ablak futását
        }
    }
}

// =========================================================================
// 3. AZ EGYETLEN SOROS ABLAKNYITÓ (CREATE WINDOW)
// =========================================================================
static inline ShortwaWindow ShortWA_CreateWindow(char* Title, int width, int height) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    // Tervrajz (WNDCLASSEX) inicializálása és kitöltése
    WNDCLASSEX wc = {0}; 
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = ShortWA_WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Alapértelmezett egérnyíl
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "ShortWAWindowC";
    
    // Regisztráció
    RegisterClassEx(&wc);
    
    // Ablak tényleges legyártása a 12 paraméterrel
    HWND hwnd = CreateWindowEx(
        0, 
        "ShortWAWindowC", 
        Title, 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        width, height, 
        NULL, NULL, 
        hInstance, 
        NULL
    );
    
    // Létrehozzuk a tiszta struktúrát (nincs memóriahiba, mert nem mutató!)
    ShortwaWindow wing;
    wing.is_running = (hwnd != NULL) ? 1 : 0; // Csak akkor indul el, ha sikerült a CreateWindowEx
    wing.hinstance = hInstance;
    wing.width = width;
    wing.height = height;
    wing.hwnd = hwnd;
    
    return wing;
}

#endif // ShortWA_H
