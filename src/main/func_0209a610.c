/* func_0209a610 @ 0x0209a610, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *p);
extern int func_0209a654(const void *p);
extern int func_0209dcdc(const void *p, const void *q);

int func_0209a610(unsigned char *a, unsigned char *b)
{
    unsigned int local;
    unsigned char *p = b;

    if (p == 0) {
        func_0209df64(&local);
        p = (unsigned char *) &local;
    }

    if (func_0209a654(a) != 0) {
        int res = func_0209dcdc(p, a + 0xb6);
        if (res >= 0 && res < 3) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
