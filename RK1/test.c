#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int symbols = 0;
int entered_symb = 0;
int Difficulty, Time, Mistakes;
bool isStarted = false, isMove = false, isMistake = false;

static int words = 0;
static int mist_count = 0;
static bool isEnded = false, isTheEnd = false, isClose = false;

void InitTextField (int line){
    textfield.left = 20;
    textfield.top = 20 + 40 * line;
    textfield.right = textfield.left + 1040;
    textfield.bottom = textfield.top + 400; 
}


int main () {

    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA));
        wcl.lpszClassName = "speedTester";
        wcl.lpfnWndProc = WindowProc;
    RegisterClassA(&wcl);

    hwnd_set = CreateWindow("speedTester", "Speed Tester", 
                            WS_OVERLAPPEDWINDOW, 
                            10, 10, 480, 360, 
                            NULL, NULL, NULL, NULL);

    hwnd = CreateWindow("speedTester", "Speed Tester", 
                            WS_OVERLAPPEDWINDOW, 
                            10, 10, 1080, 720, 
                            NULL, NULL, NULL, NULL);

    dc = GetDC(hwnd);

    HFONT fontRectangle = CreateFont(40, 15, 0, 0, FW_MEDIUM,
                                    FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                    OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                    FF_MODERN, "myFont");

    ShowWindow(hwnd_set, SW_SHOWNORMAL);
    
    InitPointer();

    HWND difficulty = CreateWindow("combobox", "", 
                                WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 
                                220, 10, 100, 150, 
                                hwnd_set, Difficulty_id, NULL, NULL);

        SendMessage(difficulty, CB_ADDSTRING, 0, "easy");
        SendMessage(difficulty, CB_ADDSTRING, 0, "medium");
        SendMessage(difficulty, CB_ADDSTRING, 0, "hard");
        SendMessage(difficulty, CB_SETCURSEL, 0, 0);

    HWND times = CreateWindow("edit", "120", 
                                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 
                                220, 50, 100, 20, 
                                hwnd_set, Time_id, NULL, NULL);

    HWND mistakes = CreateWindow("edit", "15", 
                                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 
                                220, 90, 100, 20, 
                                hwnd_set, Mistakes_id, NULL, NULL);

    HWND difficulty_txt = CreateWindow("static", "Choose difficulty", 
                                WS_VISIBLE | WS_CHILD, 
                                10, 10, 200, 20, 
                                hwnd_set, NULL, NULL, NULL);

    time_txt = CreateWindow("static", "Put the time in seconds", 
                                WS_VISIBLE | WS_CHILD, 
                                10, 50, 200, 20, 
                                hwnd_set, NULL, NULL, NULL);

    mistakes_txt = CreateWindow("static", "Put the number of mistakes", 
                                WS_VISIBLE | WS_CHILD, 
                                10, 90, 200, 20, 
                                hwnd_set, NULL, NULL, NULL);                                                            

    HWND bt_start = CreateWindow("button", "Start", 
                                WS_VISIBLE | WS_CHILD, 
                                10, 130, 100, 50, 
                                hwnd_set, StartBtn_id, NULL, NULL);



    char buffer2[256][128];
    int line_len[256];
    int counter = 0, total_symb = 0;

    char *text_str[counter];
        
    int shown_lines = 0;
    
    MSG msg; 
    while (GetMessage(&msg, NULL, 0 , 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        clock_t start, current_time, end;

        if(isStarted){
            if(!isClose){

                char lib_buf[128][32];
                int lib_len = 0;

                FILE *lib = fopen("textlib.txt", "r");
                for(lib_len; !feof(lib); lib_len++)
                    fscanf(lib, "%s", &lib_buf[lib_len]);
                fclose(lib);

                char difficlty_folder[3][8] = {"easy/", "medium/", "hard/"};
                char dif_buf[32] = "";

                srand(time(NULL));

                strcat(dif_buf, difficlty_folder[Difficulty]);
                strcat(dif_buf, lib_buf[rand() % (lib_len)]);

                char buffer[1024][32];
                int len = 0, total_len = 0;
                
                FILE *text = fopen(dif_buf, "r");
                for(len; !feof(text); len++)
                    fscanf(text, "%s", &buffer[len]);
                fclose(text);
                
                for(int i = 0; i < len; i++) {
                    int strlenth = strlen(buffer[i]);

                    if (total_len + strlenth < 64){
                        for (int j = 0; j < strlenth; j++)
                            buffer2[counter][total_len++] = buffer[i][j];
                        
                        buffer2[counter][total_len++] = ' ';

                    } else {
                        line_len[counter] = total_len;
                        counter++;
                        total_len = 0;
                    }
                    
                }
                line_len[counter] = total_len;

                for (int i = 0; i <= counter; i++)
                    total_symb += line_len[i];

                for (int i = 0; i <= counter; i++)
                    text_str[i] = buffer2[i];


                CloseWindow(hwnd_set);
                ShowWindow(hwnd, SW_SHOWNORMAL);
                ShowPointer(dc);
                
                SetBkMode(dc, TRANSPARENT);
                SetTextColor(dc, RGB(0, 0, 0));
                SelectObject(dc, fontRectangle);	

                for (int i = 0; i <= 5 ; i++){
                    InitTextField(i);
                    DrawText(dc, text_str[i], -1, &textfield, DT_SINGLELINE);
                }

                isClose = true;
                start = clock();
            }
            
            
            if (!isEnded) {
                int line_count, current_total_symb = 0;

                if (isMove){

                    for (int i = 0; i < line_count; i++)
                        current_total_symb += line_len[i];

                    int current_symb = buffer2[line_count][symbols - current_total_symb - 1];
                    
                    if(entered_symb != current_symb){
                        isMistake = true;
                        mist_count++;
                    }

                    if(current_symb == ' ')
                        words++;
                    
                    ClearField(dc, pointer.left, pointer.top, pointer.right, pointer.bottom);
                    ClearField(dc, winrect.left, winrect.bottom / 2, winrect.right, winrect.bottom);
                    MovePointer(line_len[line_count], &line_count);
                    ShowPointer(dc);


                    for (int j = 0; j <= 5; j++) {
                        int div = line_count - shown_lines;

                        if(div == 6){
                            shown_lines += 6;
                            ClearField(dc, winrect.left, winrect.top, winrect.right, winrect.bottom); 
                            InitPointer();
                            ShowPointer(dc);
                        }

                        InitTextField(j);
                        DrawText(dc, text_str[j + shown_lines], -1, &textfield, DT_SINGLELINE);

                        if (line_count % 5 == 0 && symbols >= current_total_symb)
                            j == 0;

                        bool needEnd = ((Mistakes - mist_count) == 0) || ((Time - ((current_time - start) / CLK_TCK)) <= 0);
                        if ((line_count == counter && symbols >= (total_symb - 1)) || needEnd) {
                            end = clock();
                            isEnded = true;
                            break;
                        }
                    }

                    char buf[10] = "";
                    char table[4][20] = {"Symbols: ", "Mistakes left: ", "Time left: ", "Speed: "};

                    itoa(symbols, buf, 10);
                    char *symb = strcat(table[0], buf);
                    itoa(Mistakes - mist_count, buf, 10);
                    char *mist = strcat(table[1], buf);
                    itoa(Time - ((current_time - start) / CLK_TCK), buf, 10);
                    char *time = strcat(table[2], buf);
                    itoa(symbols * (60 / ((current_time - start) / CLK_TCK)), buf, 10);
                    char *speed = strcat(table[3], buf);

                    InitTextField(9);
                    DrawText(dc, symb, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(10);
                    DrawText(dc, mist, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(11);
                    DrawText(dc, time, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(12);
                    DrawText(dc, speed, -1, &textfield, DT_SINGLELINE | DT_CENTER);

                    isMove = false;
                    current_time = clock();
                }

            } else {
                if (!isTheEnd){
                    ClearField(dc, winrect.left, winrect.top, winrect.right, winrect.bottom);
                    char buf[10] = "";
                    char table[6][20] = {"Total symbols: ","Right: ", "Mistakes: ", "Total time: ", "Average speed: ", "Words in min: "};

                    itoa(symbols, buf, 10);
                    char *tsymb = strcat(table[0], buf);
                    itoa((symbols - mist_count), buf, 10);
                    char *rsymb = strcat(table[1], buf);
                    itoa(mist_count, buf, 10);
                    char *tmist = strcat(table[2], buf);
                    itoa((end - start) / CLK_TCK, buf, 10);
                    char *ttime = strcat(table[3], buf);
                    itoa(symbols * (60 / ((end - start) / CLK_TCK)), buf, 10);
                    char *avspd = strcat(table[4], buf);
                    itoa(words * (60 / ((end - start) / CLK_TCK)), buf, 10);
                    char *wspd = strcat(table[5], buf);

                    InitTextField(3);
                    DrawText(dc, "GAME OVER", -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(4);
                    DrawText(dc, tsymb, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(5);
                    DrawText(dc, rsymb, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(6);
                    DrawText(dc, tmist, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(7);
                    DrawText(dc, ttime, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(8);
                    DrawText(dc, avspd, -1, &textfield, DT_SINGLELINE | DT_CENTER);
                    InitTextField(9);
                    DrawText(dc, wspd, -1, &textfield, DT_SINGLELINE | DT_CENTER);

                    isTheEnd = true;
                }

            }
            
        }
               
    }

    return 0;
}
