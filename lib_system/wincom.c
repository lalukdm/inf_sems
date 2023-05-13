#include "wincom.h"

// extern HWND hwnd;


/// @brief Clear come field on window
/// @param dc handle
void ClearField (HDC dc, int left, int top, int right, int bottom){
    SelectObject(dc, GetStockObject(DC_PEN));
    SetDCPenColor(dc,RGB(255, 255, 255));
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(255, 255, 255));
    Rectangle(dc, left, top, right, bottom);
}

void login_page(HWND hwnd) {
    
    login_txt = CreateWindow("static", "Enter login:", 
                                WS_VISIBLE | WS_CHILD, 
                                350, 280, 200, 20, 
                                hwnd, NULL, NULL, NULL);
    password_txt = CreateWindow("static", "Enter password:", 
                                WS_VISIBLE | WS_CHILD, 
                                350, 340, 200, 20, 
                                hwnd, NULL, NULL, NULL);

    login_field = CreateWindow("edit", "11", 
                                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 
                                480, 280, 100, 20, 
                                hwnd, Login_id, NULL, NULL);

    password_field = CreateWindow("edit", "p", 
                                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_PASSWORD, 
                                480, 340, 100, 20, 
                                hwnd, Password_id, NULL, NULL);


    autohorize_bt = CreateWindow("button", "Log In", 
                                WS_VISIBLE | WS_CHILD, 
                                480, 400, 100, 50, 
                                hwnd, AutohorizeBtn_id, NULL, NULL);
}

