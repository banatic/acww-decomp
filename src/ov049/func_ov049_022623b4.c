/* func_ov049_022623b4 @ 0x022623b4, 0x3c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8e];
    signed short unk_8E;
} SelfType;

extern int func_0201c2c8(SelfType *self, int arg);
extern int func_020e8b4c(int a, int b);
extern void func_ov049_02260500(SelfType *self);
extern void func_ov049_02262a94(SelfType *self, int arg);
extern short data_020c80f0[];

int func_ov049_022623b4(SelfType *self)
{
    int result1;
    int result2;
    short diff;

    result1 = func_0201c2c8(self, 4);
    result2 = func_020e8b4c(self->unk_8E, result1);
    diff = data_020c80f0[0];

    if (result2 >= diff) {
        func_ov049_02262a94(self, 0xb);
    } else {
        func_ov049_02260500(self);
    }
    return 1;
}
