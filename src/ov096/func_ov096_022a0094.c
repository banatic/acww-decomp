/* func_ov096_022a0094 @ 0x022a0094, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(void *ptr);
extern void func_ov096_0229fb4c(void *ptr);

void func_ov096_022a0094(void *self)
{
    if (func_ov002_02208e28((char *) self + 0x2564) != 0) {
        func_ov096_0229fb4c(self);
    }
}
