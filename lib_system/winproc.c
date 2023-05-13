#include "winproc.h"

int symbols, entered_symb;
int Difficulty, Time, Mistakes;
bool isMove, isStarted;

int login, password;

extern bool isLogin;

extern HWND time_txt, mistakes_txt;

extern HWND exit_bt, login_bt;

extern HWND login_field, password_field;
extern HWND login_txt, password_txt;
extern HWND autohorize_bt;

extern HDC dc;

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){

    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CHAR:
            isMove = true;
            symbols++;
            entered_symb = wparam;
            break;
        
        case WM_COMMAND:
            switch (LOWORD(wparam)){
                case ExitBtn_id:
                    // save_db();
                    PostQuitMessage(0);
                    break;

                case LogInBtn_id:
                    isLogin = true;
                    break;

                case Login_id:
                    // if (lparam != NULL) {
                        GetWindowText(lparam, login, 100);
                        printf("%s\n%s\n", login, GetLastError());
                    // }
                    break;
                
                case Password_id:
                    GetWindowText(lparam, password, 100);
                    printf("%s\n", password);
                    break;

                case AutohorizeBtn_id:
                    printf("%s\t%s\n", login, password);
                    if(check_user(login, password)) {
                        DestroyWindow(login_field);
                        DestroyWindow(password_field);
                        DestroyWindow(login_txt);
                        DestroyWindow(password_txt);
                        DestroyWindow(autohorize_bt);
                        ClearField(dc, 0, 0, 1080, 600);
                    } else {
                        
                    }

                    break;

                case Difficulty_id:
                    if(HIWORD(wparam) == CBN_SELCHANGE)
                        Difficulty = SendMessage(lparam, CB_GETCURSEL, 0, 0);
                    break;

                case Time_id:
                    char get_time[100];
                    GetWindowText(lparam, get_time, 100);

                    Time = atoi(get_time);

                    if (Time > MAXTIME){
                        SetWindowText(time_txt, "so long");
                    }
                    break;

                case Mistakes_id:
                    char get_mist[100];
                    GetWindowText(lparam, get_mist, 100);

                    Mistakes = atoi(get_mist);

                    if (Mistakes > MAXMISTAKES){
                        SetWindowText(mistakes_txt, "so mach");
                    }
                    break;
            }
            break;
        
        default:
            return DefWindowProc(hwnd, message, wparam, lparam);
            break;
    }
}