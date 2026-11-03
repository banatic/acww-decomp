/* activity_card_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a233c @ 0x020a233c, 0x50 bytes, Thumb
 * func_020a22f8 @ 0x020a22f8, 0x44 bytes, Thumb
 * func_020a22b8 @ 0x020a22b8, 0x40 bytes, Thumb
 * func_020a21ec @ 0x020a21ec, 0xcc bytes, Thumb
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

extern int func_020a1acc(UnkStruct_020a22f8 *self, int flag);
extern int func_020a16e0(void);

int func_020a233c(unsigned char *p)
{
    p[0x10d] = (unsigned char) ((p[0x10d] & ~0xf0) | 0x30);
    p[0x10d] = (unsigned char) ((p[0x10d] & ~0x0f) | 0x03);
    p[0x10e] = (unsigned char) ((p[0x10e] & ~0x0f) | 0x03);
    p[0x10e] = (unsigned char) ((p[0x10e] & ~0xf0) | 0x30);
    p[0xa0]++;
    return 3;
}

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

int func_020a22b8(S_020a22b8 *self)
{
    int ret;

    ret = func_020a1acc((UnkStruct_020a22f8 *) self, 1);
    self->unk_10D.byte = (self->unk_10D.byte & ~0xf) | (ret & 0xf);
    if (self->unk_10D.bits.mode == 3) {
        return 3;
    }
    self->unk_A0 = self->unk_A0 + 1;
    return 3;
}

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
