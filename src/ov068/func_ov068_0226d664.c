/* func_ov068_0226d664 @ 0x0226d664, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02266e7c(void *);
extern void func_ov068_02266e78(void *, int);

int func_ov068_0226d664(void *self)
{
    if (func_ov068_02266e7c((char *) self + 0x9f4)) {
        func_ov068_02266e78((char *) self + 0x9f4, 0);
        return 1;
    }
    return 0;
}
