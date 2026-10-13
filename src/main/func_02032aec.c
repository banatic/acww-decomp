/* func_02032aec @ 0x02032aec, 0x164 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u32 unk_04;
    u8 pad_08[4];
    short a[2];
    u8 unk_10;
    u8 pad_11[0x1c - 0x11];
    int c[8];
} UnkStruct_02032aec;

void func_02032aec(UnkStruct_02032aec *self, int ang)
{
    // DECLS
    int i;
    u32 d;
    int base;
    int t;
    int t2;
    int t3;
    // ENDDECLS

    base = ang;
    base = base + 0x8000;
    for (i = 0; i < self->unk_10; i++) {
        d = (u16) (self->a[i] - base);
        if (d < 0x2000 || d >= 0xe000) {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x100;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 8;
            }
        } else if (d < 0x6000) {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x400;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 0x20;
            }
        } else if (d < 0xa000) {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x800;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 0x40;
            }
        } else {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x200;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 0x10;
            }
        }
    }
    if (self->unk_10 == 2) {
        t = (short) ((self->a[0] + self->a[1]) >> 1);
        t2 = (short) (t + 0x7fff);
        t3 = ang - t2;
        if (t3 < 0) {
            t3 = -t3;
        }
        if (t3 < 0x2000) {
            self->unk_04 |= 0x1000;
        }
        if ((short) (self->a[0] + self->a[1]) == 0) {
            self->unk_04 |= 0x2000;
        }
    }
}
