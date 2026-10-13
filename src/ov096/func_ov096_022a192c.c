/* func_ov096_022a192c @ 0x022a192c, 0x9c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(int);
extern int func_ov096_022a18dc(void *, int);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
} UnkStruct_022a192c;

typedef struct {
    volatile unsigned short unk_00;
    volatile unsigned short unk_02;
} GlobalRegs;

extern GlobalRegs data_021fbe40; // linked at 0x021fbe40

int func_ov096_022a192c(UnkStruct_022a192c *self)
{
    unsigned char f;
    int result;
    int ret;

    func_0206f58c();
    if (func_0206f56c() != 0) {
        f = self->unk_8D;
        if (f == 0 || f == 1 || f == 0xa) {
            return func_ov096_022a18dc((void *) self, 7);
        }
    }

    f = self->unk_8D;
    if (f != 0 && f != 0xa) {
        return 0;
    }

    result = -1;
    ret = func_0206fe60();
    if (ret != 0) {
        result = func_ov090_022990e0(ret);
    } else {
        unsigned short val = data_021fbe40.unk_02;
        if (val & 0x800) {
            result = 7;
        } else if (val & 0x400) {
            result = 5;
        } else if (val & 0x4) {
            result = 4;
        }
    }

    return func_ov096_022a18dc((void *) self, result);
}
