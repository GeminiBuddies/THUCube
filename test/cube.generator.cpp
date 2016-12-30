#include "../CubeStatus.cpp"

#include <bits/stdc++.h>

const char *v[]={
    "WWWWWWWWW",
    "BBBBBBBBB",
    "RRRRRRRRR",
    "GGGGGGGGG",
    "OOOOOOOOO",
    "YYYYYYYYY"
};

Cube CubeGenerator(int cnt){
    Cube c((char **)v);
    std::srand(time(0));
    
    for(;cnt--;c.Rotate(Face(std::rand()%12)));
    return c;
}
