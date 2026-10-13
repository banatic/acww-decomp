/* func_ov004_02239b80 @ 0x02239b80, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022392a0(void);
extern void func_ov004_022399ec(void *);
extern void func_ov004_02239858(void *);

void func_ov004_02239b80(char *self)
{
    if (func_ov004_022392a0() != 0) {
        func_ov004_022399ec(self);
    } else {
        *(char *) (self + 0x1fc) = 0;
        *(char *) (self + 0x1fd) = 0;
        func_ov004_02239858(self);
    }
}
