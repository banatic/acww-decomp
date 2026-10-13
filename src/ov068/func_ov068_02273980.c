/* func_ov068_02273980 @ 0x02273980, 0x74 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_02063414(void *, int, int, int, int, int, int, int, int, int);

unsigned short func_ov068_02273980(void)
{
    volatile unsigned short out[2];
    int x;
    unsigned int ok;
    unsigned short a, b;

    x = func_020984e8();
    func_02063414((void *) out, 0x1323, 0x46, 0, 0, x, 0, 0xa, 0, 1);
    ok = 0;
    b = out[0];
    a = out[0];
    if (a >= 0x1323 && b <= 0x1368) {
        ok = 1;
    }
    if (ok == 0) {
        func_02063414((void *) &out[1], 0x1323, 0x46, 0, 0, 0, 1, 0xa, 0, 1);
        out[0] = out[1];
    }
    return out[0];
}
