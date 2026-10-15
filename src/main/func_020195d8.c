/* func_020195d8 @ 0x020195d8, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[14];
    u32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
} UnkStruct_020195d8;

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u16 unk_1C;
} InfoStruct;

extern InfoStruct *func_02019de4(void *);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_0201aff4(void *, int);
extern void func_0201b044(void *, void *);
extern void func_0201afd4(void *, void *);
extern void func_0201b350(void *, int);
extern void func_020123ec(u32, u32, int);
extern void func_02019a58(void *, int, int, int);
extern void func_02019af0(void *, int);

extern u8 data_021fbee8[];
extern u16 data_020c80f8;

int func_020195d8(UnkStruct_020195d8 *out, u8 *p)
{
    InfoStruct *info;
    u32 v;

    info = func_02019de4(out);
    func_0201b1a4((u8 *) p + 0x350, p, 3, info->unk_1A, info->unk_1C);
    func_0201aff4((u8 *) p + 0x350, info->unk_18);
    func_0201b044((u8 *) p + 0x350, data_021fbee8);
    func_0201afd4((u8 *) p + 0x350, data_021fbee8);
    func_0201b350((u8 *) p + 0x3aa, -2);

    v = *(u32 *) (p + 0x628);
    if (v != 0) {
        func_020123ec(v, data_020c80f8, 0);
    }

    out->unk_04 = out->unk_1C;
    out->unk_05 = out->unk_14;
    func_02019a58((u8 *) out + 6, info->unk_1A, info->unk_18, info->unk_1C);
    func_02019af0(out, 0);

    return 0;
}
