#pragma once

#include <cstdio>
#include <windows.h>

using namespace std;

#include "CubeStatus.cpp"

void printCube(const Cube & cu) {
    printf("    %c%c%c\n", cu[0][0], cu[0][1], cu[0][2]);
    printf("    %c%c%c\n", cu[0][3], cu[0][4], cu[0][5]);
    printf("    %c%c%c\n", cu[0][6], cu[0][7], cu[0][8]);
    printf("%c%c%c %c%c%c %c%c%c %c%c%c\n", cu[4][0], cu[4][1], cu[4][2], cu[3][0], cu[3][1], cu[3][2], cu[2][0], cu[2][1], cu[2][2], cu[1][0], cu[1][1], cu[1][2]);
    printf("%c%c%c %c%c%c %c%c%c %c%c%c\n", cu[4][3], cu[4][4], cu[4][5], cu[3][3], cu[3][4], cu[3][5], cu[2][3], cu[2][4], cu[2][5], cu[1][3], cu[1][4], cu[1][5]);
    printf("%c%c%c %c%c%c %c%c%c %c%c%c\n", cu[4][6], cu[4][7], cu[4][8], cu[3][6], cu[3][7], cu[3][8], cu[2][6], cu[2][7], cu[2][8], cu[1][6], cu[1][7], cu[1][8]);
    printf("    %c%c%c\n", cu[5][0], cu[5][1], cu[5][2]);
    printf("    %c%c%c\n", cu[5][3], cu[5][4], cu[5][5]);
    printf("    %c%c%c\n", cu[5][6], cu[5][7], cu[5][8]);
}

HANDLE h;
WORD wOldColorAttrs;  
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

WORD color[] = {
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_RED,
	BACKGROUND_GREEN,
	BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN,
};

void cPrint(char c, WORD color) {
	SetConsoleTextAttribute(h, color);
	putchar(c);
    SetConsoleTextAttribute(h, wOldColorAttrs);  
}

char ctc[256];

void cPrintCube(const Cube & cu) {
	ctc['W'] = 0; ctc['R'] = 1; ctc['G'] = 2; ctc['B'] = 3; ctc['O'] = 4; ctc['Y'] = 5;
	
	h = GetStdHandle(STD_OUTPUT_HANDLE);  
    GetConsoleScreenBufferInfo(h, &csbiInfo);  
    wOldColorAttrs = csbiInfo.wAttributes;  
    
	cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(cu[0][0], color[ctc[cu[0][0]]]); cPrint(cu[0][1], color[ctc[cu[0][1]]]); cPrint(cu[0][2], color[ctc[cu[0][2]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(cu[0][3], color[ctc[cu[0][3]]]); cPrint(cu[0][4], color[ctc[cu[0][4]]]); cPrint(cu[0][5], color[ctc[cu[0][5]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(cu[0][6], color[ctc[cu[0][6]]]); cPrint(cu[0][7], color[ctc[cu[0][7]]]); cPrint(cu[0][8], color[ctc[cu[0][8]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(cu[4][0], color[ctc[cu[4][0]]]); cPrint(cu[4][1], color[ctc[cu[4][1]]]); cPrint(cu[4][2], color[ctc[cu[4][2]]]); cPrint(cu[3][0], color[ctc[cu[3][0]]]); cPrint(cu[3][1], color[ctc[cu[3][1]]]); cPrint(cu[3][2], color[ctc[cu[3][2]]]); cPrint(cu[2][0], color[ctc[cu[2][0]]]); cPrint(cu[2][1], color[ctc[cu[2][1]]]); cPrint(cu[2][2], color[ctc[cu[2][2]]]); cPrint(cu[1][0], color[ctc[cu[1][0]]]); cPrint(cu[1][1], color[ctc[cu[1][1]]]); cPrint(cu[1][2], color[ctc[cu[1][2]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(cu[4][3], color[ctc[cu[4][3]]]); cPrint(cu[4][4], color[ctc[cu[4][4]]]); cPrint(cu[4][5], color[ctc[cu[4][5]]]); cPrint(cu[3][3], color[ctc[cu[3][3]]]); cPrint(cu[3][4], color[ctc[cu[3][4]]]); cPrint(cu[3][5], color[ctc[cu[3][5]]]); cPrint(cu[2][3], color[ctc[cu[2][3]]]); cPrint(cu[2][4], color[ctc[cu[2][4]]]); cPrint(cu[2][5], color[ctc[cu[2][5]]]); cPrint(cu[1][3], color[ctc[cu[1][3]]]); cPrint(cu[1][4], color[ctc[cu[1][4]]]); cPrint(cu[1][5], color[ctc[cu[1][5]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(cu[4][6], color[ctc[cu[4][6]]]); cPrint(cu[4][7], color[ctc[cu[4][7]]]); cPrint(cu[4][8], color[ctc[cu[4][8]]]); cPrint(cu[3][6], color[ctc[cu[3][6]]]); cPrint(cu[3][7], color[ctc[cu[3][7]]]); cPrint(cu[3][8], color[ctc[cu[3][8]]]); cPrint(cu[2][6], color[ctc[cu[2][6]]]); cPrint(cu[2][7], color[ctc[cu[2][7]]]); cPrint(cu[2][8], color[ctc[cu[2][8]]]); cPrint(cu[1][6], color[ctc[cu[1][6]]]); cPrint(cu[1][7], color[ctc[cu[1][7]]]); cPrint(cu[1][8], color[ctc[cu[1][8]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(cu[5][0], color[ctc[cu[5][0]]]); cPrint(cu[5][1], color[ctc[cu[5][1]]]); cPrint(cu[5][2], color[ctc[cu[5][2]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(cu[5][3], color[ctc[cu[5][3]]]); cPrint(cu[5][4], color[ctc[cu[5][4]]]); cPrint(cu[5][5], color[ctc[cu[5][5]]]); cPrint('\n', wOldColorAttrs); 
	cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(' ', wOldColorAttrs); cPrint(cu[5][6], color[ctc[cu[5][6]]]); cPrint(cu[5][7], color[ctc[cu[5][7]]]); cPrint(cu[5][8], color[ctc[cu[5][8]]]); cPrint('\n', wOldColorAttrs); 
} 
