/* func_ov004_0222d548 @ 0x0222d548, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c3b4(void *, int);
extern int func_0205650c(void *, int, void *);
extern void func_02056478(void *, int, int, int, int);
extern void *func_02055e00(void *);
extern void func_020563dc(void *, void *);
extern void *data_021c9b24;

int func_ov004_0222d548(char *self)
{
    if (func_ov004_0222c3b4(self + 0x1a4, 0) != 0) {
        if (func_0205650c(self + 0x290, *(int *) (self + 0x148), data_021c9b24) != 0) {
            func_02056478(self + 0x290, func_ov004_0222c3b4(self + 0x1a4, 0), 0, 0x1000, 0);
            func_020563dc(self + 0x290, func_02055e00(self + 0xec));
            return 1;
        }
    }
    return 0;
}
