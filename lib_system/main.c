#include <stdio.h>
#include <stdlib.h>
#include "main.h"


#define MAX_LINE_SIZE 1024
#define MAX_FIELD_SIZE 256
#define MAX_FIELDS 10

HWND login_field, password_field;
HWND login_txt, password_txt;
HWND autohorize_bt;

bool isLogin = false;

void InitTextField (int line){
    textfield.left = 20;
    textfield.top = 20 + 40 * line;
    textfield.right = textfield.left + 1040;
    textfield.bottom = textfield.top + 400; 
}

int main () {

    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA));
        wcl.lpszClassName = "lib_system";
        wcl.lpfnWndProc = WindowProc;
    RegisterClassA(&wcl);

    // hwnd_set = CreateWindow("lib_system", "Speed Tester", 
    //                         WS_OVERLAPPEDWINDOW, 
    //                         10, 10, 480, 360, 
    //                         NULL, NULL, NULL, NULL);

    hwnd = CreateWindow("lib_system", "Библеотека", 
                            WS_OVERLAPPEDWINDOW, 
                            50, 50, 1080, 720, 
                            NULL, NULL, NULL, NULL);

    dc = GetDC(hwnd);



    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    

    // HWND difficulty = CreateWindow("combobox", "", 
    //                             WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 
    //                             220, 10, 100, 150, 
    //                             hwnd_set, Difficulty_id, NULL, NULL);

    //     SendMessage(difficulty, CB_ADDSTRING, 0, "easy");
    //     SendMessage(difficulty, CB_ADDSTRING, 0, "medium");
    //     SendMessage(difficulty, CB_ADDSTRING, 0, "hard");
    //     SendMessage(difficulty, CB_SETCURSEL, 0, 0);

    // HWND times = CreateWindow("edit", "120", 
    //                             WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 
    //                             220, 50, 100, 20, 
    //                             hwnd_set, Time_id, NULL, NULL);

    // HWND mistakes = CreateWindow("edit", "15", 
    //                             WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 
    //                             220, 90, 100, 20, 
    //                             hwnd_set, Mistakes_id, NULL, NULL);

    // HWND difficulty_txt = CreateWindow("static", "Choose difficulty", 
    //                             WS_VISIBLE | WS_CHILD, 
    //                             10, 10, 200, 20, 
    //                             hwnd_set, NULL, NULL, NULL);

    // time_txt = CreateWindow("static", "Put the time in seconds", 
    //                             WS_VISIBLE | WS_CHILD, 
    //                             10, 50, 200, 20, 
    //                             hwnd_set, NULL, NULL, NULL);

    HFONT fontRectangle = CreateFont(40, 15, 0, 0, FW_MEDIUM,
                                FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                FF_MODERN, "myFont");

    HFONT smallFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, RUSSIAN_CHARSET,
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    HFONT bigFont = CreateFont(36, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

    SelectObject(dc, bigFont);
    InitTextField(0);
    DrawText(dc, "Welcome to library system", -1, &textfield, DT_SINGLELINE | DT_CENTER);
    SelectObject(dc, smallFont);

    // HWND hello_txt = CreateWindow("static", "Welcome to lib system", 
    //                             WS_VISIBLE | WS_CHILD, 
    //                             380, 50, 200, 20, 
    //                             hwnd, NULL, NULL, NULL);

    // mistakes_txt = CreateWindow("static", "Put the number of mistakes", 
    //                             WS_VISIBLE | WS_CHILD, 
    //                             10, 90, 200, 20, 
    //                             hwnd_set, NULL, NULL, NULL);                                                            

    exit_bt = CreateWindow("button", "Exit", 
                                WS_VISIBLE | WS_CHILD, 
                                950, 620, 100, 50, 
                                hwnd, ExitBtn_id, NULL, NULL);

    login_bt = CreateWindow("button", "Log In", 
                                WS_VISIBLE | WS_CHILD, 
                                480, 320, 100, 50, 
                                hwnd, LogInBtn_id, NULL, NULL);

    char csv_file[] = "books.csv";
    char line[MAX_LINE_SIZE];
    char field[MAX_FIELD_SIZE];
    char *token;
    char *rest;
    FILE *fp;
    int field_count;
    int i;

    fp = fopen(csv_file, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", csv_file);
        return 1;
    }

    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Parse fields from line
        rest = line;
        field_count = 0;
        while ((token = strtok_r(rest, ";", &rest)) != NULL && field_count < MAX_FIELDS) {
            strcpy(field, token);
            wchar_t *p = &field;
            
            //InitTextField(field_count + 1);
            //DrawText(dc, p, -1, &textfield, DT_SINGLELINE | DT_CENTER);
            printf("Field %d: %s\n", field_count, field);
            field_count++;
        }

        // Print field count
        printf("Fields in line: %d\n", field_count);

        // Print empty line
        printf("\n");
    }

    fclose(fp);
    
    MSG msg; 
    while (GetMessage(&msg, NULL, 0 , 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);


        if (isLogin) {
            DestroyWindow(login_bt);
            puts("login_bt");
            ClearField(dc, 0, 0, 1080, 600);
            login_page(hwnd);

            // isLogin = false;
        }

        
        clock_t start, current_time, end;

    }

    return 0;
}