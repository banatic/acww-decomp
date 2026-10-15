/* func_ov134_0229b220 @ 0x0229b220, 0x38c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" int func_020896b8(int, int, int, int, int, int, int);
extern "C" void *func_02089300(int, int, int, int, int, int, int, int, int);
extern "C" void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern "C" int func_ov134_022995c0(void *, int);
extern "C" void func_ov134_022995a0(void *, int);

extern "C" const int data_ov134_0229c134;
extern "C" const int data_ov134_0229c13c;
extern "C" const int data_ov134_0229c144;
extern "C" const int data_ov134_0229c024;
extern "C" const int data_ov134_0229c06c;
extern "C" const int data_ov134_0229c17c;
extern "C" const int data_ov134_0229c14c[];
extern "C" const int data_ov134_0229c1f4;
extern "C" const int data_ov134_0229c214;
extern "C" const int data_ov134_0229c384;
extern "C" const int data_ov134_0229c1b4;
extern "C" const int data_ov134_0229c1d4;

struct OBJ {
    virtual void f0();
    virtual void f4();
    virtual void f8();
};

extern "C" void func_ov134_0229b220(char *a, void *b, char *c)
{
    char *g = (char *) b + 0x80;
    char *h = c + 0x60;
    void *w;
    struct OBJ *o;
    int i;
    int u, v;
    int k;

    if (*(u8 *) (a + 0xa1) == 0) {
        w = (void *) b;
        w = (char *) w + 0x38;
        c += 0x34;
        func_020896b8(1, (int) &data_ov134_0229c134, (int) w, (int) c, -1, 2, 0);
        func_02089300(1, (int) &data_ov134_0229c13c, (int) w, (int) c, -1, 2, 0x1000, *(u16 *) (a + 0x92), 0);
        func_02089300(1, (int) &data_ov134_0229c144, (int) w, (int) c, -1, 2, 0x1000, *(u16 *) (a + 0x94), 0);
    }

    func_02088df8(1, (int) &data_ov134_0229c024, (int) g, (int) h, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    if (func_ov134_022995c0(a, 4) != 0) {
        o = (struct OBJ *) (a + 0x18);
        o->f8();
    }

    if (*(int *) (a + 0x74) != 0) {
        if (func_ov134_022995c0(a, 0x200) != 0) {
            func_ov134_022995a0(a, 0x200);
        } else {
            func_02088df8(1, (int) &data_ov134_0229c06c, *(int *) (a + 0x7c) - 8, *(u8 *) (a + 0xb5), -1, 1, 0x1000, 0x1000, 0,
                          -1, 0, 0);
        }
        func_02088df8(1, *(int *) (a + 0x74), *(int *) (a + 0x7c) - 8, *(u8 *) (a + 0xb5), -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }

    if (*(int *) (a + 0x78) != 0) {
        func_02088df8(1, *(int *) (a + 0x78), *(int *) (a + 0x7c) - 8, *(u8 *) (a + 0xb6), -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }

    if (*(int *) (a + 0x70) != 0) {
        func_02088df8(1, *(int *) (a + 0x70), *(int *) (a + 0x7c), *(int *) (a + 0x80), -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }

    switch (*(u8 *) (a + 0xa0)) {
        case 0:
        case 3:
            func_02088df8(1, (int) &data_ov134_0229c17c, (int) g, (int) h, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            for (i = 0; i < 5; i++) {
                if (*(u8 *) (a + 0xa0) == 3 && (i == 3 || i == 4)) {
                    continue;
                }
                if (i == *(u8 *) (a + 0xb1)) {
                    k = 7;
                } else {
                    k = -1;
                }
                func_02088df8(1, data_ov134_0229c14c[i], (int) g, (int) h, k, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            }
            if (func_ov134_022995c0(a, 8) != 0) {
                k = 0xa;
            } else {
                k = 9;
            }
            func_02088df8(1, data_ov134_0229c14c[5], (int) g, (int) h, k, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            break;
        case 2:
            if (*(u8 *) (a + 0xb1) == 1) {
                u = 7;
                v = 6;
            } else if (*(u8 *) (a + 0xb1) == 2) {
                v = 7;
                u = 6;
            } else {
                u = 6;
                v = u;
            }
            func_02088df8(1, (int) &data_ov134_0229c1f4, (int) g, (int) h, u, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            func_02088df8(1, (int) &data_ov134_0229c214, (int) g, (int) h, v, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            break;
        case 1:
            func_02088df8(1, (int) &data_ov134_0229c384, (int) g, (int) h, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            if (*(u8 *) (a + 0xb1) == 3) {
                u = 7;
                v = 6;
            } else if (*(u8 *) (a + 0xb1) == 4) {
                v = 7;
                u = 6;
            } else {
                u = 6;
                v = u;
            }
            func_02088df8(1, (int) &data_ov134_0229c1b4, (int) g, (int) h, u, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            func_02088df8(1, (int) &data_ov134_0229c1d4, (int) g, (int) h, v, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            break;
    }
}
