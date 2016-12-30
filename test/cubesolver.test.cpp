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
    freopen("test.txt","w",stderr);
    for(int i=0;i<6;i++){
        for(int j=0;j<9;j++) fprintf(stderr,"%c",t[i][j]);
        fprintf(stderr,"\n");
    }
    fclose(stderr);
    printCube(t);puts("");
    Solve(&t);
    return 0;
}
