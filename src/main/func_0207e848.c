/* func_0207e848 @ 0x0207e848, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996f8(void);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);

int func_0207e848(void)
{
    unsigned short *p = func_020996f8();
    if (func_0204bcdc(p)) {
        unsigned short local[4];
        int a, b;
        local[0] = 0x13e4;
        a = func_0204bc64(p);
        b = func_0204bc64(local);
        if (a == b) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13e4) {
            return 1;
        } else {
            return 0;
        }
    }
}
