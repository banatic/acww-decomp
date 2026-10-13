/* func_ov068_0226fe28 @ 0x0226fe28, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200322c(void *a, void *b);
extern int func_020644cc(int a);

struct UnkStruct_0226fe28 {
    unsigned char pad_00[0x204];
    unsigned char unk_204;
    unsigned char pad_205[0x220 - 0x205];
    unsigned int unk_220;
    unsigned char pad_224[0x228 - 0x224];
    unsigned int unk_228;
    unsigned char pad_22C[0x240 - 0x22c];
    unsigned short unk_240;
    unsigned char pad_242[0x244 - 0x242];
    unsigned short unk_244;
    unsigned char pad_246[0x24a - 0x246];
    unsigned char unk_24A;
    unsigned char pad_24B[0x251 - 0x24b];
    unsigned char unk_251;
    unsigned char pad_252[0x254 - 0x252];
    unsigned char unk_254;
    unsigned char unk_255;
};

void func_ov068_0226fe28(struct UnkStruct_0226fe28 *self, int *count_ptr)
{
    if (*count_ptr <= 0) {
        return;
    }
    if (self->unk_24A != 0) {
        return;
    }
    if (self->unk_254 < self->unk_255) {
        return;
    }

    self->unk_240 = func_0200322c(count_ptr, &self->unk_204);
    self->unk_244 = 0x14 * (func_020644cc(4) + 7);
    self->unk_251 = 7;
    self->unk_24A = 1;
    self->unk_220 = self->unk_228;
}
