/* func_ov004_02232980 @ 0x02232980, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057468(void *, int, void *);
extern char data_ov004_02255a90;

int func_ov004_02232980(char *self, int a1, int a2)
{
    if (a2 != 0) {
        func_02057468(self + 0x10f4, a1, &data_ov004_02255a90);
        *(int *) (self + 0x10fc) = a2;
        return 1;
    }
    return 0;
}
