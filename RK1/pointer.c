#include "pointer.h"

extern RECT pointer;
extern bool isMistake;

void InitPointer (){
    pointer.left = 20;
    pointer.top = 20;
    pointer.right = pointer.left + pointerWidth;
    pointer.bottom = pointer.top + pointerHeight; 
}

void MovePointer (int len, int* line){
    pointer.left += pointerWidth + 1;
    if (pointer.left > (20 + (pointerWidth + 1) * (len - 1))) {
        pointer.left = 20;
        pointer.top += 40;
        (*line)++;
    }
    pointer.right = pointer.left + pointerWidth;
    pointer.bottom = pointer.top + pointerHeight; 
}

void ShowPointer (HDC dc){
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(0, 255, 0));
    SelectObject(dc, GetStockObject(DC_PEN));
    if (isMistake)
        SetDCBrushColor(dc, RGB(255, 0, 0));
    else
        SetDCBrushColor(dc, RGB(0, 255, 0));
    Rectangle(dc, pointer.left, pointer.top, pointer.right, pointer.bottom);
    isMistake = false;
}

void ClearField (HDC dc, int left, int top, int right, int bottom){
    SelectObject(dc, GetStockObject(DC_PEN));
    SetDCPenColor(dc,RGB(255, 255, 255));
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(255, 255, 255));
    Rectangle(dc, left, top, right, bottom);
}