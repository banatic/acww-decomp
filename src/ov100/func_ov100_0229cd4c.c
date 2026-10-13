/* func_ov100_0229cd4c @ 0x0229cd4c, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cd4c;
extern void func_ov100_0229d4a8(struct UnkStruct_0229cd4c *, int, unsigned short, unsigned char);

struct UnkStruct_0229cd4c {
    unsigned char pad_00[0x2918];
    unsigned short unk_2918;
    unsigned char pad_291A[2];
    unsigned char unk_291C;
    unsigned char unk_291D;
};

void func_ov100_0229cd4c(struct UnkStruct_0229cd4c *obj, int param)
{
    struct UnkStruct_0229cd4c *self = obj;
    if (self->unk_291D == 1) {
        func_ov100_0229d4a8(self, param, self->unk_2918, self->unk_291C);
    }
    self->unk_291D = 0;
}
