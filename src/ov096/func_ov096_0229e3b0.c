/* func_ov096_0229e3b0 @ 0x0229e3b0, 0xf4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e4a4(int, int);
extern int func_020984e8(void);
extern void func_02099704(int, unsigned short *);
extern void func_020996d4(int, unsigned short *);
extern void func_020996ec(int, unsigned short *);

int func_ov096_0229e3b0(int a0, int a1, int a2)
{
    int h;
    volatile unsigned short v;
    int r;

    r = func_ov096_0229e4a4(a0, a1);
    h = func_020984e8();
    v = (unsigned short) a2;
    switch (a1) {
        case 2:
            func_02099704(h, (unsigned short *) &v);
            v = (unsigned short) r;
            {
                int ok = 0;
                unsigned short lo = v;
                unsigned short hi = v;
                if (hi >= 0x11a8 && lo <= 0x12a7) {
                    ok = 1;
                }
                if (ok == 0) {
                    r = 0xfff1;
                }
            }
            break;
        case 3:
            func_020996d4(h, (unsigned short *) &v);
            break;
        case 6:
            func_020996d4(h, (unsigned short *) &v);
            r = func_ov096_0229e4a4(a0, 4);
            v = 0xfff1;
            func_020996ec(h, (unsigned short *) &v);
            break;
        case 4:
            func_020996ec(h, (unsigned short *) &v);
            v = (unsigned short) r;
            {
                int ok = 0;
                unsigned short lo = v;
                unsigned short hi = v;
                if (hi >= 0x1429 && lo <= 0x1430) {
                    ok = 1;
                }
                if (ok != 0) {
                    r = 0xfff1;
                }
            }
            break;
        case 5:
            v = (unsigned short) r;
            {
                int ok = 0;
                unsigned short lo = v;
                unsigned short hi = v;
                if (hi >= 0x13a0 && lo <= 0x13a7) {
                    ok = 1;
                }
                if (ok != 0) {
                    r = 0xfff1;
                }
            }
            break;
        case 0:
        case 8:
        default:
            break;
    }
    return r;
}
