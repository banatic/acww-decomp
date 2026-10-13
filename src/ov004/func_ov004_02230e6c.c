/* func_ov004_02230e6c @ 0x02230e6c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020682e0(int a);
extern void func_0206fbf8(int a);
extern void func_ov004_0223121c(char *self, int a);
void func_ov004_02230e6c(char *self)
{
    if (*(int *) (func_020682e0(0) + 4) == 5) {
        func_0206fbf8(0x30);
        func_ov004_0223121c(self, 0xe);
    }
}
