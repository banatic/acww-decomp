/* func_ov134_02299734 @ 0x02299734, 0x3e bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299734 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[0xac - 0x8];
    unsigned char unk_AC;
    unsigned char pad_AD[0xb0 - 0xad];
    unsigned char unk_B0;
} UnkStruct_02299734;

extern int func_ov134_022999ac(UnkStruct_02299734 *self);

int func_ov134_02299734(UnkStruct_02299734 *self)
{
    if ((int) self->unk_B0 < (int) self->unk_AC) {
        int res;
        self->unk_B0++;
        res = func_ov134_022999ac(self);
        if (res > 0xa0) {
            self->unk_04 += res - 0xa0;
        }
        return 1;
    }
    return 0;
}
