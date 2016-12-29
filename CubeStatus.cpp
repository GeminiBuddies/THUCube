#pragma once

#include <utility>
#include <algorithm>

//UBRFLD
class Cube;

enum class Face {
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



constexpr int innerFaceOrder[8] = {
    0, 1, 2, 5, 8, 7, 6, 3
};

constexpr int neighborFace[6][12][2] = {
    {{1, 2}, {1, 1}, {1, 0}, {2, 2}, {2, 1}, {2, 0}, {3, 2}, {3, 1}, {3, 0}, {4, 2}, {4, 1}, {4, 0}},
    {{0, 2}, {0, 1}, {0, 0}, {4, 0}, {4, 3}, {4, 6}, {5, 6}, {5, 7}, {5, 8}, {2, 8}, {2, 5}, {2, 2}},
    {{0, 8}, {0, 5}, {0, 2}, {1, 0}, {1, 3}, {1, 6}, {5, 8}, {5, 5}, {5, 2}, {3, 8}, {3, 5}, {3, 2}},
    {{0, 6}, {0, 7}, {0, 8}, {2, 0}, {2, 3}, {2, 6}, {5, 2}, {5, 1}, {5, 0}, {4, 8}, {4, 5}, {4, 2}},
    {{0, 0}, {0, 3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {5, 0}, {5, 3}, {5, 6}, {1, 8}, {1, 5}, {1, 2}},
    {{4, 6}, {4, 7}, {4, 8}, {3, 6}, {3, 7}, {3, 8}, {2, 6}, {2, 7}, {2, 8}, {1, 6}, {1, 7}, {1, 8}}
};

constexpr int x = -1; // an invalid number

constexpr int edgeNeighbor[6][9][2] = {
    {{x, x}, {1, 1}, {x, x}, {4, 1}, {x, x}, {2, 1}, {x, x}, {3, 1}, {x, x}},
    {{x, x}, {0, 1}, {x, x}, {2, 5}, {x, x}, {4, 3}, {x, x}, {5, 7}, {x, x}},
    {{x, x}, {0, 5}, {x, x}, {3, 5}, {x, x}, {1, 3}, {x, x}, {5, 5}, {x, x}},
    {{x, x}, {0, 7}, {x, x}, {4, 5}, {x, x}, {2, 3}, {x, x}, {5, 1}, {x, x}},
    {{x, x}, {0, 3}, {x, x}, {1, 5}, {x, x}, {3, 3}, {x, x}, {5, 3}, {x, x}},
    {{x, x}, {3, 7}, {x, x}, {4, 7}, {x, x}, {2, 7}, {x, x}, {1, 7}, {x, x}}
};

#define INVI {{x, x}, {x, x}}
constexpr int cornerNeighbor[6][9][2][2] = {
    {{{1, 2}, {4, 0}}, INVI, {{2, 2}, {1, 0}}, INVI, INVI, INVI, {{4, 2}, {3, 0}}, INVI, {{3, 2}, {2, 0}}},
    {{{0, 2}, {2, 2}}, INVI, {{4, 0}, {0, 0}}, INVI, INVI, INVI, {{2, 8}, {5, 8}}, INVI, {{5, 6}, {4, 6}}},
    {{{0, 8}, {3, 2}}, INVI, {{1, 0}, {0, 2}}, INVI, INVI, INVI, {{3, 8}, {5, 2}}, INVI, {{5, 8}, {1, 6}}},
    {{{0, 6}, {4, 2}}, INVI, {{2, 0}, {0, 8}}, INVI, INVI, INVI, {{4, 8}, {5, 0}}, INVI, {{5, 2}, {2, 6}}},
    {{{0, 0}, {1, 2}}, INVI, {{3, 0}, {0, 6}}, INVI, INVI, INVI, {{1, 8}, {5, 6}}, INVI, {{5, 0}, {3, 6}}},
    {{{3, 6}, {4, 8}}, INVI, {{2, 6}, {3, 8}}, INVI, INVI, INVI, {{4, 6}, {1, 8}}, INVI, {{1, 6}, {2, 8}}}
};

constexpr int ecCnt = 4;

constexpr int edgeIndex[] = { 1, 3, 5, 7 };
constexpr int cornerIndex[] = { 0, 2, 6, 8 };



struct PFPos{
    Face face;
    int pos;
    PFPos() {}
    PFPos(Face _face, int _pos) : face(_face), pos(_pos) {}
};

struct PFPosColor {
    Face face;
    int pos;
    char color;

    PFPosColor() {}
    PFPosColor(Face _face, int _pos, char _color) : face(_face), pos(_pos), color(_color) {}

    PFPos getPFPos() {
        return PFPos(face, pos);
    }
};

typedef Face Op;

class Cube {
    void rc(int face);
    void ri(int face);

public:
    void U() { rc(0); }
    void B() { rc(1); }
    void R() { rc(2); }
    void F() { rc(3); }
    void L() { rc(4); }
    void D() { rc(5); }
    void Ui() { ri(0); }
    void Bi() { ri(1); }
    void Ri() { ri(2); }
    void Fi() { ri(3); }
    void Li() { ri(4); }
    void Di() { ri(5); }

    const char* operator [] (const int & b) const;

    void Rotate(Face fa) {
    	int _fa = (int)fa;

        if (_fa < 6) rc(_fa);
		else  ri(_fa - 6);
    }

private:
    typedef char face[9];

    face f[6];

public:
    Cube() {;}
    Cube(char ** F) {
        for (int i = 0; i < 6; ++i) for (int j = 0; j < 9; ++j) f[i][j] = F[i][j];
    }

    PFPos SeekPiece(char domColor, char auxColor);
    PFPos SeekPiece(char domColor, char auxColor, char terColor);

    std::pair<PFPosColor, PFPosColor> CornerGetNeighbor(PFPos piece);
    PFPosColor EdgeGetNeighbor(PFPos piece);
};

void Cube::rc(int face) {
    const int (*nF)[2] = neighborFace[face];

    for (int i = 0; i < 3; ++i) for (int j = 11; j >= 1; --j) std::swap(f[nF[j][0]][nF[j][1]], f[nF[j - 1][0]][nF[j - 1][1]]);
    for (int i = 0; i < 2; ++i) for (int j = 7; j >= 1; --j) std::swap(f[face][innerFaceOrder[j]], f[face][innerFaceOrder[j - 1]]);
}

void Cube::ri(int face) {
    const int (*nF)[2] = neighborFace[face];

    for (int i = 0; i < 3; ++i) for (int j = 1; j < 12; ++j) std::swap(f[nF[j][0]][nF[j][1]], f[nF[j - 1][0]][nF[j - 1][1]]);
    for (int i = 0; i < 2; ++i) for (int j = 1; j < 8; ++j) std::swap(f[face][innerFaceOrder[j]], f[face][innerFaceOrder[j - 1]]);
}

const char* Cube::operator [] (const int & b) const {
    return (const char*)f[b];
}

//Seeking for an edge piece
PFPos Cube::SeekPiece(char domColor, char auxColor)
{
    for (int i = 0; i < 6; ++i) {
        for (int _j = 0; _j < ecCnt; ++_j) {
            int j = edgeIndex[_j];

            if (f[i][j] == domColor) {
                if (f[edgeNeighbor[i][j][0]][edgeNeighbor[i][j][1]] == auxColor) return PFPos((Face)i, j);
            }
        }
    }
}

//Seeking for a cornor piece
PFPos Cube::SeekPiece(char domColor, char auxColor, char terColor)
{
    for (int i = 0; i < 6; ++i) {
        for (int _j = 0; _j < ecCnt; ++_j) {
            int j = cornerIndex[_j];
            
            int si = cornerNeighbor[i][j][0][0], sj = cornerNeighbor[i][j][0][1];
            int ti = cornerNeighbor[i][j][1][0], tj = cornerNeighbor[i][j][1][1];

            if (f[i][j] == domColor) {
                if ((f[si][sj] == auxColor && f[ti][tj] == terColor) || (f[ti][tj] == auxColor && f[si][sj] == terColor)) return PFPos((Face)i, j);
            }
        }
    }
}

std::pair<PFPosColor, PFPosColor> Cube::CornerGetNeighbor(PFPos piece) {
    int i = (int)piece.face, j = piece.pos;

    int si = cornerNeighbor[i][j][0][0], sj = cornerNeighbor[i][j][0][1];
    int ti = cornerNeighbor[i][j][1][0], tj = cornerNeighbor[i][j][1][1];

    return std::make_pair<PFPosColor, PFPosColor>(PFPosColor((Face)si, sj, f[si][sj]), PFPosColor((Face)ti, tj, f[ti][tj]));
}

PFPosColor Cube::EdgeGetNeighbor(PFPos piece) {
    int i = (int)piece.face, j = piece.pos;
    int ff = edgeNeighbor[i][j][0], pp = edgeNeighbor[i][j][1];

    return PFPosColor((Face)ff, pp, f[ff][pp]);
}
