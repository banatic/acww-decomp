/* func_02095bdc @ 0x02095bdc, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02095bdc {
    u8 pad_00[0x7f0];
    int a;
    int b0;
    int b1;
    int d;
    u8 pad_800[0x8eb - 0x800];
    s8 e;
} UnkStruct_02095bdc;

extern volatile u8 data_020e54a8;
extern UnkStruct_02095bdc *func_02096718(int n);
extern int func_02008258(UnkStruct_02095bdc *p, int v);
extern int func_020094a0(UnkStruct_02095bdc *p, u8 k, int c, int d, int e, int f);
extern void func_020110c4(u16 *x, UnkStruct_02095bdc *p);
extern int func_0204bcdc(u16 *x);
extern int func_0204bc64(u16 *x);
extern int func_0200fc90(UnkStruct_02095bdc *p);
extern void func_ov003_02217c5c(UnkStruct_02095bdc *p, int a, int b, int c, int d, int e, int f, int h);
extern void func_0200d4e8(UnkStruct_02095bdc *p, int a, int b, int c);

int func_02095bdc(void)
{
    UnkStruct_02095bdc *p;
    int v;
    int n;
    int t;
    int t2;
    u16 x[2];

    p = func_02096718(4);
    if (p != 0) {
        v = p->a;
        n = p->e;
        p->e = 0;
        if (v == 0x2c || v == 0x29 || v == 0x2a) {
            return 1;
        }
        p->d = func_02008258(p, v);
        if (n > 0) {
            func_020094a0(p, (u8) (n + 3), 0, 0, 6, -1);
        } else {
            t = (data_020e54a8 == 0);
            if (t) {
                func_020110c4(x, p);
                if (func_0204bcdc(x)) {
                    x[1] = 0xfff1;
                    t2 = (func_0204bc64(&x[0]) == func_0204bc64(&x[1]));
                } else {
                    t2 = (x[0] == 0xfff1);
                }
                if (!t2 && !func_0200fc90(p) && v != 0x39) {
                    func_ov003_02217c5c(p, 2, 2, 0, 0, 0, 6, -1);
                    goto done;
                }
            }
            func_0200d4e8(p, 3, 5, -1);
        }
    done:;
    } else {
        return 0;
    }
}
