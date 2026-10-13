/* func_ov048_02260c88 @ 0x02260c88, 0x48 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x812];
    unsigned char flag812;
} UnkStruct_02260c88;

extern int func_02073044(UnkStruct_02260c88 *self);
extern int func_020ec920(int arg);
extern int func_ov048_02260f64(UnkStruct_02260c88 *self, int flag);
extern void func_02074120(void);
extern int func_0207417c(int arg);
extern void func_ov048_022616b8(UnkStruct_02260c88 *self, int arg);

void func_ov048_02260c88(UnkStruct_02260c88 *self)
{
    int flag;

    if (func_020ec920(func_02073044(self)) == 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (func_ov048_02260f64(self, flag)) {
        func_02074120();
    } else {
        if (func_0207417c(0)) {
            self->flag812 = 0;
            func_ov048_022616b8(self, 7);
        }
    }
}
