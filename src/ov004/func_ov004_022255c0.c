/* func_ov004_022255c0 @ 0x022255c0, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov004_022256ec(void *, int);

int func_ov004_022255c0(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov004_022256ec(self, 0);
        }
    }
    return 1;
}
