/* func_02092f48 @ 0x02092f48, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Bits {
    u16 b0 : 5;
    u16 b1 : 5;
    u16 b2 : 5;
    u16 b3 : 1;
};

struct Stack {
    u16 unk_00;
    union {
        u16 raw;
        struct Bits bits;
    } unk_02;
    union {
        u16 raw;
        struct Bits bits;
    } unk_04;
    u16 unk_06;
};

struct UnkStruct_02092f48 {
    u8 pad_00[0x5a];
    u16 unk_5A;
};

extern void func_02094ef4(struct UnkStruct_02092f48 *);
extern u16 func_020bbf00(int);

void func_02092f48(struct UnkStruct_02092f48 *self)
{
    struct Stack s;

    func_02094ef4(self);

    s.unk_00 = func_020bbf00(3);
    s.unk_06 = s.unk_00;
    s.unk_02.raw = s.unk_06;
    s.unk_04.raw = 0x7fff;

    s.unk_02.bits.b0 = (s.unk_04.bits.b0 * s.unk_02.bits.b0) / 31;
    s.unk_02.bits.b1 = (s.unk_04.bits.b1 * s.unk_02.bits.b1) / 31;
    s.unk_02.bits.b2 = (s.unk_04.bits.b2 * s.unk_02.bits.b2) / 31;

    self->unk_5A = s.unk_02.raw;
}
