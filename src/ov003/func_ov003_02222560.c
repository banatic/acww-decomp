/* func_ov003_02222560 @ 0x02222560, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02222560 {
    unsigned int a;
    unsigned int b;
} UnkStruct_02222560;

typedef struct UnkStruct_02222560_2 {
    char pad_00[0x18];
    char pad_18[0x30 - 0x18];
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    char pad_48[0xa0 - 0x48];
    unsigned char unk_A0;
    unsigned char unk_A1;
} UnkStruct_02222560_2;

extern void func_0204f794(void *dst, unsigned int a, unsigned int b);

void func_ov003_02222560(UnkStruct_02222560_2 *self, UnkStruct_02222560 *src)
{
    func_0204f794((char *) self + 0x18, src->a, src->b);

    self->unk_3C = 0;
    self->unk_40 = 0x1000;
    self->unk_44 = 0;
    self->unk_30 = 0;
    self->unk_34 = 0;
    self->unk_38 = 0;

    self->unk_A0 = 0;
    self->unk_A1 = 1;
}
