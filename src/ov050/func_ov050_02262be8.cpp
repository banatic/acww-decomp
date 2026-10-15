/* func_ov050_02262be8 @ 0x02262be8, 0x200 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov050_02265b1419func_ov050_02262be8Ei
 */

#include "cpp/ov050/Obj_ov050_02265b14.h"

typedef void (Obj_ov050_02265b14::*PMF)(int);

struct E {
    int key;
    PMF fn;
};

extern "C" int func_020984e8(void);
extern "C" int func_02099640(int argument0);
extern "C" void *func_0209ad9c(int, int);
extern "C" void *func_0209b4d4(void *argument0);
extern "C" void func_0206844c(int, unsigned char *, void *);

extern void *data_ov050_02265834;

void Obj_ov050_02265b14::func_ov050_02262be8(int arg)
{
    unsigned int i;
    unsigned char *q;
    int k;
    int r;
    unsigned char c;

    r = func_02099640((int) func_020984e8());

    func_0209b4d4((void *) func_0209ad9c(r, 0));
    unk_D0 = 0xff;
    {
        static E tbl[24] = {{0, &Obj_ov050_02265b14::func_ov050_02262bac},    {3, &Obj_ov050_02265b14::func_ov050_02262b58},
                            {4, &Obj_ov050_02265b14::func_ov050_02262b58},    {7, &Obj_ov050_02265b14::func_ov050_02262b08},
                            {8, &Obj_ov050_02265b14::func_ov050_02262ad8},    {0xe, &Obj_ov050_02265b14::func_ov050_02262acc},
                            {0x12, &Obj_ov050_02265b14::func_ov050_02262ab8}, {0x16, &Obj_ov050_02265b14::func_ov050_02262a28},
                            {0x1a, &Obj_ov050_02265b14::func_ov050_02262a28}, {0x18, &Obj_ov050_02265b14::func_ov050_022629ec},
                            {0x1e, &Obj_ov050_02265b14::func_ov050_02262970}, {0x1f, &Obj_ov050_02265b14::func_ov050_02262910},
                            {0x21, &Obj_ov050_02265b14::func_ov050_022628c8}, {0x25, &Obj_ov050_02265b14::func_ov050_0226288c},
                            {0x27, &Obj_ov050_02265b14::func_ov050_02262850}, {0x28, &Obj_ov050_02265b14::func_ov050_022627d4},
                            {0x29, &Obj_ov050_02265b14::func_ov050_02262798}, {0x2c, &Obj_ov050_02265b14::func_ov050_02262734},
                            {0x2e, &Obj_ov050_02265b14::func_ov050_02262700}, {0x31, &Obj_ov050_02265b14::func_ov050_022626c8},
                            {0x33, &Obj_ov050_02265b14::func_ov050_0226265c}, {0x35, &Obj_ov050_02265b14::func_ov050_02262628},
                            {0x36, &Obj_ov050_02265b14::func_ov050_02262628}, {0xc, &Obj_ov050_02265b14::func_ov050_02262618}};
        i = 0;
        q = &unk_1E;
        goto test;
    body:
        k = tbl[i].key;
        if (k == *q) {

            (this->*((E *) ((char *) tbl + i * sizeof(E)))->fn)(r);
        }
        i++;
    test:
        if (i < 24) {
            goto body;
        }
    }
    if (unk_D0 != 0xff) {
        c = (unsigned char) unk_D0;
        func_0206844c(unk_40, &c, &data_ov050_02265834);
    }
}
