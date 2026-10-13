/* func_ov004_022323b0 @ 0x022323b0, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02232450(void);
extern void func_02032180(void *p);

int func_ov004_022323b0(char *self)
{
    if (func_ov004_02232450()) {
        func_02032180(self);
        func_02032180(self + 0x9c);
    }
    return 1;
}
