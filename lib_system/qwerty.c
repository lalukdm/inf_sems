#include <Windows.h>
int main() 
{
    setlocale(LC_ALL, "Russian"); // устанавливаем локаль для корректного отображения кириллицы
    // Создаем окно
    HWND hWnd = CreateWindow("STATIC", "Привет, мир!", WS_VISIBLE | WS_SYSMENU, 50, 50, 200, 100, NULL, NULL, NULL, NULL);
// Создаем шрифт
HFONT hFont = CreateFont(42, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Palatino Linotype");


// Устанавливаем шрифт окна
SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);


// Запустить цикл сообщений
MSG Msg;
while (GetMessage(&Msg, NULL, 0, 0))
{
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
}


return 0;


}