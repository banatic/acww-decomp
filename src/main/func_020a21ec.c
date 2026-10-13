/* func_020a21ec @ 0x020a21ec, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[0x6c];
    union {
        unsigned char byte;
        struct {
            unsigned char lo : 4;
            unsigned char hi : 4;
        } bits;
    } unk_10D;
    union {
        unsigned char byte;
        struct {
            unsigned char lo : 4;
            unsigned char hi : 4;
        } bits;
    } unk_10E;
} UnkStruct_020a21ec;

extern int func_020a16e0(void);

int func_020a21ec(UnkStruct_020a21ec *self)
{
    int result = 0;

    if (self->unk_10D.bits.lo == 1 || self->unk_10D.bits.hi == 1) {
        result = 1;
    } else if (self->unk_10D.bits.hi != 0 && self->unk_10D.bits.lo != 0) {
        self->unk_10E.byte = (self->unk_10E.byte & ~0xf) | 1;
        self->unk_10E.byte = self->unk_10E.byte & ~0xf0;
        result = 4;
    } else if (self->unk_10D.bits.hi != 0) {
        self->unk_10E.byte = (self->unk_10E.byte & ~0xf) | 1;
        self->unk_10E.byte = self->unk_10E.byte & ~0xf0;
    } else if (self->unk_10D.bits.lo != 0) {
        self->unk_10E.byte = self->unk_10E.byte & ~0xf;
        self->unk_10E.byte = (self->unk_10E.byte & ~0xf0) | 0x10;
    } else {
        int rr = func_020a16e0();
        self->unk_10E.byte = (self->unk_10E.byte & ~0xf) | ((unsigned char) rr & 0xf);
        if (self->unk_10E.bits.lo == 1) {
            self->unk_10E.byte = self->unk_10E.byte & ~0xf0;
        } else {
            self->unk_10E.byte = (self->unk_10E.byte & ~0xf0) | 0x10;
        }
    }

    self->unk_A0 = 6;
    return result;
}
