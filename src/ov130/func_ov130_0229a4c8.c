/* func_ov130_0229a4c8 @ 0x0229a4c8, 0x1b0 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[7];
    u8 unk_07;
    u8 unk_08;
    u8 pad_09[1];
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x290 - 0xc];
    u8 sub290[0x800];
    u8 subA90[4];
} UnkStruct_0229a4c8;

extern void func_ov130_0229a678(u8);
extern void *data_ov130_0229aa90[];
extern void func_02064af4(void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_02002b40(void *, u8, int, int);
extern void *data_ov130_0229aa78[];
extern void *func_ov130_022999c0(UnkStruct_0229a4c8 *);
extern void func_0207094c(void *, int);
extern void func_02070adc(void *, u8, int, int, int, int, int);
extern void func_02070a04(void *, int, int);
extern u8 data_ov130_0229a804[];
extern u8 data_ov130_0229a7f4[];
extern void func_ov130_0229a1dc(UnkStruct_0229a4c8 *);
extern void func_ov130_02299c08(UnkStruct_0229a4c8 *);

void func_ov130_0229a4c8(UnkStruct_0229a4c8 *self)
{
    void *elem;

    func_ov130_0229a678(self->unk_0A);
    func_02064af4(data_ov130_0229aa90[self->unk_08], self->sub290, 0x800);

    switch (self->unk_07) {
        case 0:
        case 1:
            func_0206fdd4(self->sub290, 2, 8, 0xd, 9, 0xa);
            break;
        case 2:
            func_0206fdd4(self->sub290, 2, 2, 0xd, 3, 0xa);
            break;
    }
    func_02002b40(self->sub290, self->unk_0A, 0x800, 0);

    func_02064af4(data_ov130_0229aa78[self->unk_08], self->subA90, 0x800);
    func_02002b40(self->subA90, self->unk_0B, 0x800, 0);

    elem = func_ov130_022999c0(self);
    if (self->unk_07 == 6) {
        func_0207094c(elem, 0x51);
    } else {
        func_0207094c(elem, 0xb8);
    }
    func_02070adc(elem, self->unk_0B, 0xec, 4, 0xf, 0, 0);
    func_02070a04(elem, 1, 0);

    elem = func_ov130_022999c0(self);
    switch (self->unk_07) {
        case 2:
            func_0207094c(elem, 0x59);
            break;
        case 4:
            func_0207094c(elem, 0x50);
            break;
        default:
            func_0207094c(elem, 0x54);
            break;
    }
    func_02070adc(elem, self->unk_0B, 0xb0, 0xa, 0xf, 0, 0);
    func_02070a04(elem, 1, 0);

    elem = func_ov130_022999c0(self);
    func_0207094c(elem, data_ov130_0229a804[self->unk_07]);
    func_02070adc(elem, self->unk_0B, 0xc4, 0xa, 0xf, 0, 0);
    func_02070a04(elem, 1, 0);

    if (self->unk_08 == 0 || self->unk_08 == 2) {
        elem = func_ov130_022999c0(self);
        func_0207094c(elem, data_ov130_0229a7f4[self->unk_07]);
        func_02070adc(elem, self->unk_0B, 0xd8, 0xa, 0xf, 0, 0);
        func_02070a04(elem, 1, 0);
    }

    func_ov130_0229a1dc(self);
    func_ov130_02299c08(self);
}
