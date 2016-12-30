#define DEBUG

#include <bits/stdc++.h>
#include "../CubeStatus.cpp"
#include "../CubeSolver.cpp"
#include "cube.generator.cpp"

#undef DEBUG

using namespace std;

int main()
{
    Cube t=CubeGenerator();
    printCube(t);puts("");
    Solve(&t);
    return 0;
}
