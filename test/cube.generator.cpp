#include "../CubeStatus.cpp"
#include <bits/stdc++.h>

using namespace std;

char *v[]={
    "WWWWWWWWW",
    "BBBBBBBBB",
    "RRRRRRRRR",
    "GGGGGGGGG",
    "OOOOOOOOO",
    "YYYYYYYYY"
};

Cube CubeGenerator(){
    Cube c((char **)v);
    srand(time(0));
    int cnt;scanf("%d",&cnt);
    for(;cnt--;c.Rotate(Face(rand()%12)));
    return c;
}

/*
int main()
{
    Cube c((char **)v);
    srand(time(0));
    int cnt;scanf("%d",&cnt);
    for(;cnt--;c.Rotate(Face(rand()%12)));
    for(int i=0;i<6;i++) {
        for(int j=0;j<9;j++) putchar(c[i][j]);
        puts("");
    }
    return 0;
}
*/
