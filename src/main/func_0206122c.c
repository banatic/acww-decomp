/* func_0206122c @ 0x0206122c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204f86c(int);
extern void func_0204f89c(void *);
extern int func_020614c4(char *);

void *func_0206122c(char *base)
{
    int *p;
    int i;

    p = (int *) func_0204f86c(1);
    if (p != 0) {
        if (p != 0) {
            func_0204f89c(p);
        }
    }
    if (p != 0) {
        for (i = 0; i < 2; i++) {
            int *pt = p + i;
            pt[1] = func_020614c4(base + i * 512);
        }
        p[3] = 0;
    }
    return p;
}
