/* func_020a22f8 @ 0x020a22f8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef union {
    unsigned char raw;
    struct {
        unsigned char low : 4;
        unsigned char high : 4;
    } bits;
} PackedByte;

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char counter;
    unsigned char pad_A1[0x10d - 0xa1];
    PackedByte unk_10D;
} UnkStruct_020a22f8;

extern int func_020a1acc(UnkStruct_020a22f8 *self, int flag);

int func_020a22f8(UnkStruct_020a22f8 *self)
{
    int v = func_020a1acc(self, 0);
    self->unk_10D.raw = (self->unk_10D.raw & ~0xf0) | ((v & 0xf) << 4);
    if (self->unk_10D.bits.high == 3) {
        return 3;
    }
    self->counter++;
    return 3;
}
