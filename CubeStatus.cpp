//UBRFLD

class Cube;

typedef void (Cube::*func)();

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

class Cube {
    typedef char face[9];

    int neighborFace[6][12][2] = {
        {{1, 2}, {1, 1}, {1, 0}, {2, 2}, {2, 1}, {2, 0}, {3, 2}, {3, 1}, {3, 0}, {4, 2}, {4, 1}, {4, 0}},
        {{0, 2}, {0, 1}, {0, 0}, {4, 0}, {4, 3}, {4, 6}, {5, 6}, {5, 7}, {5, 8}, {2, 8}, {2, 5}, {2, 2}},
        {{0, 8}, {0, 5}, {0, 2}, {1, 0}, {1, 3}, {1, 6}, {5, 8}, {5, 5}, {5, 2}, {3, 8}, {3, 5}, {3, 2}},
        {{0, 6}, {0, 7}, {0, 8}, {2, 0}, {2, 3}, {2, 6}, {5, 2}, {5, 1}, {5, 0}, {4, 8}, {4, 5}, {4, 2}},
        {{0, 0}, {0, 3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {5, 0}, {5, 3}, {5, 6}, {1, 8}, {1, 5}, {1, 2}},
        {{4, 6}, {4, 7}, {4, 8}, {3, 6}, {3, 7}, {3, 8}, {2, 6}, {2, 7}, {2, 8}, {1, 6}, {1, 7}, {1, 8}}
    };

    void rc(int face);
    void ri(int face);

public :
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

    func f[12] = {
        U, B, R, F, L, D,    
        Ui, Bi, Ri, Fi, Li, Di
    };

    void Rotate(Face fa) {
        (this->*f[(int)fa])();
    }
};

void Cube::rc(int face) {
    
}

void Cube::ri(int face) {
    
}
