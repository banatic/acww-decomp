/* func_ov004_0222dd5c @ 0x0222dd5c, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_common_subs off
extern void *func_ov004_0222c3c4(void *, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, void *, int, int, int, int);
extern void func_02055050(void *);
extern void *data_021c9b24;

void func_ov004_0222dd5c(char *self, int idx)
{
    char *a = self + 0x908 + idx * 0xa4;
    if (func_ov004_0222c3c4(a, 0) != 0) {
        if (func_02055140(self + 0x290 + idx * 0xb8, data_021c9b24) != 0) {
            int k = idx * 0xb8;
            char *b = self + 0x290 + k;
            func_02055060(b, func_ov004_0222c3c4(a, 0), 1, 0x1000, 0, 0);
            func_02055050(b);
            *(int *) (self + k + 0x33c) = 0;
        }
    }
}
