#include "CubeStatus.cpp"

enum class Faces {
    U = 0,
    B = 1,
    R = 2,
    F = 3,
    L = 4,
    D = 5,
    Ui = 6,
    Bi = 7,
    Ri = 8,
    Fi = 9,
    Li = 10,
    Di = 11
};

string Solve(Cube *status);