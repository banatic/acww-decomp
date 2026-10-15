/* func_ov144_0229a0fc @ 0x0229a0fc, 0x30 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

struct UnkStruct_0229a0fc {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x30];
    unsigned char unk_BE;
    unsigned char pad_BF[5];
    unsigned char unk_C4[1];
};

void func_ov144_0229a0fc(struct UnkStruct_0229a0fc *self, int a, int b)
{
    func_ov002_0220a05c(self->unk_C4, a, b, 3, 1);
    self->unk_BE = self->unk_8D;
    func_ov002_02208098(self, 6);
}
