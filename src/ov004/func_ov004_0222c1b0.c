/* func_ov004_0222c1b0 @ 0x0222c1b0, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222c1b0 {
    unsigned short a, b, c, d;
};

extern void *func_02096718(int a);
extern int func_0200f290(void *p, int a);
extern void func_020112f8(unsigned short *q, void *p);
extern void func_02011138(unsigned short *q, void *p);
extern void func_0200f268(void *p, int a);
extern void func_0200f27c(void *p, int a);
extern int func_020112e4(void *p);
extern int func_020112d0(void *p);
extern int func_020100e8(void *p, struct UnkStruct_0222c1b0 *t, int a, int b, int c);
extern void func_020103c0(void *p, unsigned short *q);

int func_ov004_0222c1b0(int flag)
{
    struct UnkStruct_0222c1b0 t;
    void *p;
    int x;

    p = func_02096718(4);
    if (p != 0) {
        if (flag != 0) {
            if (func_0200f290(p, 0xc) != 0) {
                func_020112f8(&t.c, p);
                t.a = t.c;
                func_02011138(&t.d, p);
                t.b = t.d;
                func_0200f268(p, 0xc);
            } else {
                return 1;
            }
        } else {
            if (func_0200f290(p, 0xc) == 0) {
                t.b = 0xfff1;
                t.a = 0xfff1;
                func_0200f27c(p, 0xc);
            } else {
                return 1;
            }
        }
        x = func_020112e4(p);
        if (func_020100e8(p, &t, x, func_020112d0(p), 1) != 0) {
            func_020103c0(p, &t.b);
        }
        return 1;
    }
    return 0;
}
