/* func_ov066_0226a418 @ 0x0226a418, 0x1c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

struct func_ov066_0226a418_s {
    unsigned char pad_00[2];
    unsigned char count;
    unsigned int unk_04;
};

unsigned int func_ov066_0226a418(struct func_ov066_0226a418_s *self, unsigned int value)
{
    if (value < self->count) {
        return value * 224 + self->unk_04;
    } else {
        return 0;
    }
}
