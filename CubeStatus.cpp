//UBRFLD

typedef void (*func)();

class Cube {

public :
    void U();
    void B();
    void R();
    void F();
    void L();
    void D();
    void Ui();
    void Bi();
    void Ri();
    void Fi();
    void Li();
    void Di();

    const char* operator [] (const int & b) const;

    func f[12];
};