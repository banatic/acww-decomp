/* func_ov004_022326f4 @ 0x022326f4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057468(void *, int, void *);
extern char data_ov004_02255aa0;

int func_ov004_022326f4(char *self, int a1, int a2)
{
    if (a2 != 0) {
        func_02057468(self + 0x20f4, a1, &data_ov004_02255aa0);
        *(int *) (self + 0x20fc) = a2;
        return 1;
    }
    return 0;
}
