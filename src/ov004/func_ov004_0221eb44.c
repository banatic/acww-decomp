/* func_ov004_0221eb44 @ 0x0221eb44, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0221eb6c(char *self, int a, int v, int z);
extern void func_ov004_0221eb64(char *self);
int func_ov004_0221eb44(char *self, int a)
{
    int ok = 0;
    int v = *(int *) (self + 8);
    if (v < 5) {
        func_ov004_0221eb6c(self, a, v, 0);
        func_ov004_0221eb64(self);
        ok = 1;
    }
    return ok;
}
