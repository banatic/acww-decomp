/* func_ov004_022185b0 @ 0x022185b0, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220ff74(void *self, int *t, char *p);
extern char *func_ov004_02218394(void *a, unsigned i);
extern void func_0204f818(char *a, char *b, int *t);
extern char *data_ov004_02250668[];

int func_ov004_022185b0(char *self, void *a)
{
    char *p = data_ov004_02250668[*(int *) (self + 0x784)];
    unsigned i;
    int t[3];
    char *q;

    if (p != 0) {
        for (i = 0; i < 2; i++) {
            func_ov004_0220ff74(self, t, p + 0xc * i);
            q = func_ov004_02218394(a, i);
            func_0204f818(q, q + 4, t);
        }
        return 2;
    }
    return 0;
}
