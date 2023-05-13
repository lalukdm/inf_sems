#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include "db_command.h"


#define ExitBtn_id 0
#define LogInBtn_id 1
#define Difficulty_id 2
#define Time_id 3
#define Mistakes_id 4

RECT textfield;

HWND time_txt, mistakes_txt;
HWND hwnd_set, hwnd;
HWND exit_bt, login_bt;

HDC dc;

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);