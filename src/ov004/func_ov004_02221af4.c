/* func_ov004_02221af4 @ 0x02221af4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e1fc(char *self);
extern void func_ov004_02221a64(char *self, int a);
int func_ov004_02221af4(char *self)
{
    int r;
    if (func_0202e1fc(self) == 0) {
        r = 0;
    } else {
        func_ov004_02221a64(self, 2);
        r = 1;
    }
    return r;
}
