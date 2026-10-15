/* func_ov004_0220d150 @ 0x0220d150, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct _S {
    unsigned char pad_00[0x18];
    unsigned char count;
};

struct UnkStruct_0220d150 {
    char pad_00[0x14];
    signed char c;
    char pad_15[3];
    struct _S *unk_18;
};

extern void func_020b36c8(struct UnkStruct_0220d150 *self);
extern void *func_020b3658(struct UnkStruct_0220d150 *self);
extern int func_ov004_0220d140(void);
extern void NNSi_G3dModifyMatFlag(struct _S *a, int b, int c);
extern int func_020b365c(void *a, int b, int c);
extern void NNS_G3dMdlSetMdlEmi(struct _S *a, int b, int c);

void func_ov004_0220d150(struct UnkStruct_0220d150 *self)
{
    int i;
    int v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int value;
    void *o;

    if (self->c != -1) {
        func_020b36c8(self);
        o = func_020b3658(self);
        if (o != 0) {
            NNSi_G3dModifyMatFlag(self->unk_18, 1, 0x400);
            v6 = func_ov004_0220d140();
            v7 = func_020b365c(o, ((v6 >> 10) & 0x1f) << 12, 0x1f000);
            v8 = func_020b365c(o, (v6 & 0x1f) << 12, 0x1f000);
            v9 = func_020b365c(o, ((v6 >> 5) & 0x1f) << 12, 0x1f000);
            v10 = ((v7 >> 12) << 10) | ((v8 >> 12) | ((v9 >> 12) << 5));
            v7 = (unsigned short) v10;
            for (i = 0; i < self->unk_18->count; i++) {
                if (i == self->c) {
                    value = v7;
                } else {
                    value = v6;
                }
                NNS_G3dMdlSetMdlEmi(self->unk_18, i, value);
            }
        } else {
            NNSi_G3dModifyMatFlag(self->unk_18, 0, 0x400);
        }
    }
}
