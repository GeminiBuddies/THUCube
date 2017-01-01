#include "CubeSolver.cpp"
#include <windows.h>

#include <cstdio>
using namespace std;

namespace CO {

HANDLE h;
WORD wOldColorAttrs;  
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

const char *opName[] = {
    "U ",
    "B ",
    "R ",
    "F ",
    "L ",
    "D ",
    "Ui",
    "Bi",
    "Ri",
    "Fi",
    "Li",
    "Di"
};

WORD color[] = {
	FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_BLUE | FOREGROUND_GREEN,
	BACKGROUND_RED,
	BACKGROUND_GREEN,
	BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN,
	BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_BLUE | BACKGROUND_GREEN,
};

void printOp(Op o) {
	SetConsoleTextAttribute(h, color[(int)o]);  
    printf("%s", opName[(int)o]);
    SetConsoleTextAttribute(h, wOldColorAttrs);
    putchar(' '); 
}

void initCO() {
	h = GetStdHandle(STD_OUTPUT_HANDLE);  
    GetConsoleScreenBufferInfo(h, &csbiInfo);  
    wOldColorAttrs = csbiInfo.wAttributes;  
}

}

using CO::printOp;
using CO::initCO;

char F[6][10];
char *Fptr[] = { F[0], F[1], F[2], F[3], F[4], F[5] };

int main() {
	initCO();
    
    scanf("%s", F[(int)Face::F]);
    scanf("%s", F[(int)Face::B]);
    scanf("%s", F[(int)Face::R]);
    scanf("%s", F[(int)Face::L]);
    scanf("%s", F[(int)Face::U]);
    scanf("%s", F[(int)Face::D]);

    Cube status = Cube(Fptr);
    auto solution = Solve(&status);

    int cnt = 0;
    for (auto i : solution) {
        printOp(i);

        if (!((++cnt) % 5)) putchar('\n');
    }

    return 0;
}
