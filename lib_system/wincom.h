#ifndef WINCOM_H
#define WINCOM_H

#include <stdbool.h>
#include <windows.h>

#define Login_id 11
#define Password_id 12
#define AutohorizeBtn_id 13


extern HWND login_field, password_field, autohorize_bt;
extern HWND login_txt, password_txt;



void ClearField (HDC dc, int left, int top, int right, int bottom);
void login_page();

#endif //WINCOM_H