#include "CubeSolver.cpp"

#include <cstdio>
using namespace std;

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

void printOp(Op o) {
    printf("\n%s \n\n", opName[(int)o]);
}

char F[6][10];
char *Fptr[] = { F[0], F[1], F[2], F[3], F[4], F[5] };

int main() {
    scanf("%s", F[(int)Face::F]);
    scanf("%s", F[(int)Face::B]);
    scanf("%s", F[(int)Face::R]);
    scanf("%s", F[(int)Face::L]);
    scanf("%s", F[(int)Face::U]);
    scanf("%s", F[(int)Face::D]);

    Cube status = Cube(Fptr);
    auto solution = Solve(&status);

    Cube s = Cube(Fptr);
    for (auto i : solution) {
        printOp(i);

        s.Rotate(i);
        printCube(s);
    }

    return 0;
}
