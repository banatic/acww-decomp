/* music_list_input_3: 2 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a12c @ 0x0229a12c, 0x4e bytes, Thumb
 * func_ov144_0229a0fc @ 0x0229a0fc, 0x30 bytes, Thumb
 */

struct UnkStruct_0229a0fc {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x30];
    unsigned char unk_BE;
    unsigned char pad_BF[5];
    unsigned char unk_C4[1];
};

extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a2b4(void *p);
extern int func_ov144_0229a208(void *self);
extern int func_ov144_0229a198(void *self);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov144_0229a0fc(struct UnkStruct_0229a0fc *self, int a, int b);

void func_ov144_0229a12c(void *self)
{
    unsigned char val;
    int a;
    int b;
    val = *(unsigned char *) ((char *) self + 0xc1);
    if (val == 9) {
        func_ov002_0220a314((char *) self + 0xc4);
    } else if (val <= 8) {
        func_ov002_0220a314((char *) self + 0xc4);
    } else {
        func_ov002_0220a2b4((char *) self + 0xc4);
    }
    a = func_ov144_0229a208(self);
    b = func_ov144_0229a198(self);
    func_ov144_0229a0fc((struct UnkStruct_0229a0fc *) self, a, b);
}

void func_ov144_0229a0fc(struct UnkStruct_0229a0fc *self, int a, int b)
{
    func_ov002_0220a05c(self->unk_C4, a, b, 3, 1);
    self->unk_BE = self->unk_8D;
    func_ov002_02208098(self, 6);
}
