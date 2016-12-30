#pragma once

#include <cstdio>

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
