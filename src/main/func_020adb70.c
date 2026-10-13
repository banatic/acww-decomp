/* func_020adb70 @ 0x020adb70, 0x238 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 b0 : 6;
    u32 b6 : 19;
    u32 b25 : 1;
    u32 b26 : 6;
} BF;

extern void func_020af750(void *, int, int);
extern int func_02073d90(int);
extern u16 *func_020af854(void *, int, int);
extern u16 *func_020ae8e4(void *, int, int);
extern u16 *func_020adfa4(void *, int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern void func_020af674(void *, int, int, int);
extern int func_020984e8(void);
extern int func_020996a0(int);
extern int func_020adf50(int);
extern void func_020ade0c(int, int);
extern int func_ov004_0224627c(int *, int *, int);
extern void func_020afe94(int, int, int, int);
extern void func_020ae850(void *, u16 *);
extern void func_020afdc8(u16 *, int, int);
extern void func_020adfc0(void *, u16 *);
extern void func_02073820(int);
extern void func_020737f0(int, void *, int);
extern void func_02073770(int, int, int);

extern char data_021f395c[];
extern char data_021f3b44[];
extern char data_021f3b30[];
extern u16 data_021f49f4;
extern int data_020ccf94;
extern u8 data_020e54a8;

void func_020adb70(int a, int b, int c, int d, int mode, u8 f6, int g7)
{
    int t;
    u16 id;
    BF w1;
    int x;
    int y;
    BF w2;
    int ok;
    unsigned int k;
    int h;

    if (a == 0x3f) {
        func_020af750(data_021f395c, b, d);
        if (func_02073d90(data_020ccf94) == 0) {
            return;
        }
        if (f6 == 0) {
            return;
        }
        w1.b0 = a;
        w1.b6 = b;
        w1.b25 = d;
        w1.b26 = c;
        h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &w1, 4);
        func_02073770(h, 0x26, 4);
        return;
    }

    id = data_021f49f4;
    switch (mode) {
        case 0:
            id = *func_020af854(data_021f395c, a, 0);
            break;
        case 1:
            id = *func_020ae8e4(data_021f3b44, a, 0);
            break;
        case 2:
            id = *func_020adfa4(data_021f3b30, a, 0);
            break;
    }

    if (func_0204bcdc(&id) != 0) {
        t = func_0204bc64(&id);
        if (t == func_0204bc64(&data_021f49f4)) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (id == data_021f49f4) ? 1 : 0;
    }
    if (ok != 0) {
        return;
    }

    switch (mode) {
        case 0:
            func_020af674(data_021f395c, a, b, d);
            if (f6 != 0) {
                func_020ade0c(func_020adf50(func_020996a0(func_020984e8())), b);
            }
            if (data_020e54a8 == 1) {
                k = 1;
            } else {
                k = 0;
            }
            if (k != 0) {
                if (func_ov004_0224627c(&x, &y, a) != 0) {
                    if (a == 0x3f) {
                        g7 = 0;
                    }
                    func_020afe94(x, y, c, g7);
                }
            }
            break;
        case 1:
            func_020ae850(data_021f3b44, &id);
            func_020afdc8(&id, c, g7);
            break;
        case 2:
            func_020adfc0(data_021f3b30, &id);
            func_020afdc8(&id, c, g7);
            break;
    }

    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    if (f6 == 0) {
        return;
    }
    w2.b0 = a;
    w2.b6 = b;
    w2.b25 = d;
    w2.b26 = c;
    h = data_020ccf94;
    func_02073820(h);
    func_020737f0(h, &w2, 4);
    func_02073770(h, 0x26, 4);
}
