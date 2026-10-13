/* func_ov004_02237834 @ 0x02237834, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02239460(int, int);

void func_ov004_02237834(char *self)
{
    if (func_ov004_02239460(0, 0x64) < 0xf) {
        *(char *) (self + 0x257) = 1;
        *(char *) (self + 0x258) = func_ov004_02239460(8, 0xd);
        *(int *) (self + 0x158) = 0;
    }
}
