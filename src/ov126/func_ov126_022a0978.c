/* func_ov126_022a0978 @ 0x022a0978, 0xd8 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a0978_2 {
    char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7;
    unsigned char unk_A8;
    char pad_A9[4];
    unsigned char unk_AD;
    char pad_AE[0x19c - 0xae];
    char sub_19c;
    char pad_19D[0x3dc4 - 0x19d];
    char sub_3dc4;
    char pad_3DC5[0x4248 - 0x3dc5];
    char sub_4248;
} UnkStruct_022a0978;

extern int func_02051ca8(void *p, int b);
extern void func_ov002_0220a63c(void *p, int a);
extern void func_ov002_0220a658(void *p, int a);
extern void func_ov095_0229ce84(void *p, int a);
extern void func_ov095_0229cef4(void *p, int a);
extern void func_ov095_0229bee4(void *p);
extern void func_ov095_0229bed8(void *p, int a);
extern int func_ov126_022a0740(UnkStruct_022a0978 *self);
extern int func_ov126_0229f7c8(UnkStruct_022a0978 *self, int a);
extern int func_ov126_022a0904(UnkStruct_022a0978 *self);

void func_ov126_022a0978(UnkStruct_022a0978 *self)
{
    if (self->unk_AD == 0 || self->unk_AD == 2) {
        if (func_02051ca8(&self->sub_4248, self->unk_A6) == 0) {
            func_ov002_0220a658(&self->sub_3dc4, 6);
        } else {
            func_ov002_0220a63c(&self->sub_3dc4, 6);
        }
    }
    func_ov095_0229cef4(&self->sub_19c, 0);
    if (func_ov126_022a0740(self) != 0) {
        func_ov095_0229ce84(&self->sub_19c, 0xb);
    } else {
        func_ov095_0229cef4(&self->sub_19c, 0xb);
    }
    if (func_ov126_0229f7c8(self, 8) != 0) {
        func_ov095_0229ce84(&self->sub_19c, 0xc);
    } else {
        func_ov095_0229cef4(&self->sub_19c, 0xc);
    }
    if (func_ov126_022a0740(self) != 0) {
        func_ov095_0229bee4(&self->sub_19c);
        func_ov095_0229ce84(&self->sub_19c, 6);
    } else {
        if (self->unk_A8 == 0) {
            func_ov095_0229bee4(&self->sub_19c);
        } else {
            int v = func_ov126_022a0904(self);
            func_ov095_0229bed8(&self->sub_19c, v);
        }
    }
}
