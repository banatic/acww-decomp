/* func_ov048_022634cc @ 0x022634cc, 0x3c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_022604c8(void *arg0);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov048_022635f4(void *, int);

int func_ov048_022634cc(void *self)
{
    if (func_ov048_022604c8((void *) self)) {
        return 1;
    }
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564)) {
            func_ov048_022635f4(self, 1);
        }
    }
    return 1;
}
