/* func_ov112_022a0fc4 @ 0x022a0fc4, 0x140 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *p, int a);
extern unsigned char *func_ov112_0229ff1c(void *p);
extern int func_ov095_0229bf48(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern int func_ov002_0220a784(void *p, int n);
extern void func_ov112_022a0068(void *p);
extern void func_ov112_022a0028(void *p);
extern int func_ov095_0229aff0(void *p);
extern void func_ov095_0229c22c(void *p, int a, int b, int c);
extern void func_ov112_0229fd20(void *p);
extern int func_ov112_0229f788(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov112_0229fa5c(void *p);
extern void func_ov002_0220a574(void *p);
extern void func_ov112_0229f8e4(void *p);
extern int func_ov112_0229fa2c(void *self);
extern int func_ov112_022a04b8(void *p);

typedef struct UnkStruct_022a0fc4 {
    unsigned char pad_00[0x384];
    unsigned char unk_384;
    unsigned char pad_385[0x3eaf];
    unsigned char unk_4234;
    unsigned char pad_4235[0x47];
    unsigned char unk_427C;
} UnkStruct_022a0fc4;

void func_ov112_022a0fc4(UnkStruct_022a0fc4 *self)
{
    int r4;
    unsigned int isBoth;
    int r6;
    int ret;

    if (func_ov002_02208054(self, 1)) {
        func_ov112_0229ff1c(self);
        return;
    }

    r4 = 0;
    if (func_ov095_0229bf48(&self->unk_384)) {
        r4 = 1;
    }

    isBoth = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (isBoth > 0) {
        r6 = data_021f6c54;

        if (func_ov002_0220a784(&self->unk_427C, 9)) {
            func_ov112_022a0068(self);
            return;
        }

        if (func_ov002_0220a784(&self->unk_427C, 8)) {
            func_ov112_022a0028(self);
            return;
        }

        if (func_ov095_0229aff0(&self->unk_384)) {
            func_ov095_0229c22c(&self->unk_384, 9, 6, 1);
            func_ov112_0229fd20(self);
            return;
        }

        if (func_ov112_0229f788(self)) {
            func_ov002_02208098(self, 3);
            func_ov095_0229b3ec(&self->unk_384);
            func_ov112_0229fd20(self);
            return;
        }

        if (func_ov112_0229fa5c(self)) {
            func_ov002_0220a574(&self->unk_4234);
            func_ov002_02208098(self, 1);
            func_ov112_0229f8e4(self);
            func_ov112_0229fd20(self);
            return;
        }

        if (func_ov112_0229fa2c(self)) {
            func_ov002_0220a574(&self->unk_4234);
            func_ov002_02208098(self, 2);
            func_ov112_0229f8e4(self);
            func_ov112_0229fd20(self);
            return;
        }

        if (r6 >= 0x48 && r4 == 0) {
            ret = func_ov112_022a04b8(self);
            if (ret != 0 && ret == 1) {
                func_ov002_02208098(self, 4);
            }
        }
    }
}