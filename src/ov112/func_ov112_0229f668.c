/* func_ov112_0229f668 @ 0x0229f668, 0x50 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229f668 {
    unsigned char pad_00[0x98];
    int unk_98;
    int unk_9C;
    unsigned char pad_A0[0x1D];
    unsigned char unk_BD;
    unsigned char pad_BE[6];
    short shorts[1];
    unsigned char pad_C6[0x6B8A];
    int array_6C50[1];
} UnkStruct_0229f668;

extern int func_ov112_0229f630(UnkStruct_0229f668 *self, unsigned char byte);
extern int func_02051d08(short *p, int diff);
extern void func_ov112_0229fab4(UnkStruct_0229f668 *self);

void func_ov112_0229f668(UnkStruct_0229f668 *self)
{
    int val;
    int index;
    short *p;
    int result;

    val = func_ov112_0229f630(self, self->unk_BD);
    self->unk_9C = (val << 4) + 0x28;
    index = self->array_6C50[val];
    p = &self->shorts[index];
    result = func_02051d08(p, self->unk_BD - index);
    self->unk_98 = (unsigned char) (result + 0x30);
    func_ov112_0229fab4(self);
}
