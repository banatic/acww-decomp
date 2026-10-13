/* func_020a22b8 @ 0x020a22b8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a1acc(void *self, int value);

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[0x6c];
    union {
        unsigned char byte;
        struct {
            unsigned char mode : 4;
            unsigned char : 4;
        } bits;
    } unk_10D;
} S_020a22b8;

int func_020a22b8(S_020a22b8 *self)
{
    int ret;

    ret = func_020a1acc(self, 1);
    self->unk_10D.byte = (self->unk_10D.byte & ~0xf) | (ret & 0xf);
    if (self->unk_10D.bits.mode == 3) {
        return 3;
    }
    self->unk_A0 = self->unk_A0 + 1;
    return 3;
}
