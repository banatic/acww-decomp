/* func_0209a110 @ 0x0209a110, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);
extern void func_0209a14c(void *p, int r);

int func_0209a110(void *p)
{
    unsigned short v;
    int r = func_02099fe8();
    if (r == -1) {
        return 0;
    }
    v = *(unsigned short *) p;
    if (v == 0xfff1) {
        return 1;
    }
    if (v >= 0xa7 && v <= 0xc6) {
        return 1;
    }
    func_0209a14c(p, r);
    return 1;
}
