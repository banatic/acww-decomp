/* func_ov004_0224657c @ 0x0224657c, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern void func_ov004_02246598(char *self);
int func_ov004_0224657c(char *self)
{
    if (func_020b65c4() != 0x1f) {
        func_ov004_02246598(self);
    }
    return 1;
}
