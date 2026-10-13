/* func_ov004_022257e8 @ 0x022257e8, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *self);
extern void *data_020ccf94;
extern int func_02073d90(void *a);
extern int func_020b65c4(void);
extern int func_0201c0e0(void *self);
extern void func_ov004_022256ec(void *self, int k);

int func_ov004_022257e8(void *self)
{
    int *f;

    if (func_0202ec58(self) == 0) {
        return 0;
    }
    *(short *) ((char *) self + 0x710) = *(short *) ((char *) self + 0x8e);
    f = (int *) ((char *) self + 0x4e8);
    *f = *f | 2;
    if (func_02073d90(data_020ccf94) != 0 && func_020b65c4() == 0xb) {
        if (func_0201c0e0(self) != 0) {
            func_ov004_022256ec(self, 0);
        } else {
            func_ov004_022256ec(self, 4);
        }
    } else {
        func_ov004_022256ec(self, 0);
    }
    return 1;
}
