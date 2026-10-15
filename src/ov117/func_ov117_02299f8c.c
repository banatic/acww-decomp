/* func_ov117_02299f8c @ 0x02299f8c, 0xa8 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e414(void);
extern int func_0204f3e4(void *hand, int *a, int *b, int *c, int *d, short *e, short *f, int g, int h);
extern void func_0204f800(int *outx, int *outy, int a, int b, int c, int d);
extern void *func_020b3b50(void *obj);
extern void func_020b3c58(void *hand, int *a, int *b, int *c, int *d);
extern void func_ov117_0229a2a4(void *p, int md, int x, int y, int z);

void func_ov117_02299f8c(void *param)
{
    short s;
    int x, y;
    int a, b, c, d;
    int e, f, g, h;
    void *hand;

    hand = func_0204e414();
    if (hand == 0) {
        return;
    }

    s = 0x5011;
    if (func_0204f3e4(hand, &a, &b, &c, &d, &s, &s, 0x800, 0) == 0) {
        return;
    }

    func_0204f800(&x, &y, a, b, c, d);

    x = x * 2;
    y = y * 2;
    x = x + 1;
    y = y + 1;

    hand = func_020b3b50(&s);
    if (hand != 0) {
        func_020b3c58(hand, &e, &f, &g, &h);
        x += e >> 11;
        y += f >> 11;
    }

    func_ov117_0229a2a4(param, 0xd, x, y, 0);
}
