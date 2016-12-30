#define DEBUG

#include <bits/stdc++.h>
#include "../CubeStatus.cpp"
#include "../CubeSolver.cpp"
#include "cube.generator.cpp"

#undef DEBUG

using namespace std;

int main()
{
    int cnt; 
    scanf("%d",&cnt);
    Cube t=CubeGenerator(cnt);

    freopen("test.txt","w",stderr);
    for(int i=0;i<6;i++){
        for(int j=0;j<9;j++) fprintf(stderr,"%c",t[i][j]);
        fprintf(stderr,"\n");
    }
    fclose(stderr);
    
    printCube(t);puts("");
    vector<Op> st=Solve(&t);
    for(auto p : st) t.Rotate(p);
    printCube(t);
    return 0;
}
