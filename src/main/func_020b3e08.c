/* func_020b3e08 @ 0x020b3e08, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b3f2c(int *p);
extern unsigned int func_020b3eb8(int *p);

int func_020b3e08(int *p, int *a, int *b, unsigned int idx)
{
    int *base;
    unsigned int n;
    int *e;

    base = p + func_020b3f2c(p);
    n = func_020b3eb8(p);

    if (idx < n) {
        e = base + idx;
        *a = ((signed char *) e)[2];
        *b = ((signed char *) e)[3];

        if (*a == 0 && *b == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}