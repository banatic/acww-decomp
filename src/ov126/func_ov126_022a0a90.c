/* func_ov126_022a0a90 @ 0x022a0a90, 0x50 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a620(void *p, int n);
extern void func_ov126_022a0110(void *receiver);
extern int func_ov126_0229ffdc(void *p);
extern void func_ov126_022a0ae0(void *p, int n);

int func_ov126_022a0a90(unsigned char *p)
{
    if (func_ov002_0220a620(p + 0x3dc4, 6) != 0) {
        func_ov126_022a0110((void *) p);
        return 0;
    }
    {
        unsigned char b = p[0xad];
        if (b == 0 || b == 2) {
            func_ov126_0229ffdc(p);
            func_ov126_022a0ae0(p, 0);
            return 1;
        } else {
            func_ov126_022a0110((void *) p);
            return 0;
        }
    }
}
