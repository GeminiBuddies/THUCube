#include "../CubeDebugger.cpp"

using namespace std;

char v[6][10];
char *vv[] = { v[0], v[1], v[2], v[3], v[4], v[5] };

char ctf[256];
int main() {
    printf("input a cube (UBRFLD) :\n");

    for (int i = 0; i < 6; ++i) {
        printf(">> ");
        scanf("%s", v[i]);
    }

    Cube c(vv);

    printCube(c);

    char cmd[100]; ctf['U'] = 0; ctf['B'] = 1; ctf['R'] = 2; ctf['F'] = 3; ctf['L'] = 4; ctf['D'] = 5;
    for (;;) {
        printf(">> ");

        if (!~scanf("%s", cmd)) { break; }

        int act = ctf[cmd[0]]; if (cmd[1] == 'i') act += 6;

        c.Rotate((Face)act);

        printCube(c);
    }

    return 0;
}
