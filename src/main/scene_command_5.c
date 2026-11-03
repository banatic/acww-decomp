/* scene_command_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02015094 @ 0x02015094, 0x18 bytes, Thumb
 * func_02015038 @ 0x02015038, 0x5c bytes, Thumb
 * func_02014fe8 @ 0x02014fe8, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[8];
    u32 unk_4C;
    u8 pad_50[0xac - 0x50];
    u8 unk_AC;
} UnkStruct_02015038;

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[0x8];
    unsigned int unk_4C;
    unsigned char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014fe8;

extern int func_0201596c(int param, int mode);
extern u16 data_020c80f8;
extern int func_02019d0c(u32 p1, int p2, int p3, int p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u16 p10, u32 p11);
extern void func_0201600c(UnkStruct_02015038 *self);
extern void func_02068440(u32 handle);
extern int func_02019e00(unsigned int);
extern int func_02019de8(unsigned int);
extern void func_02068434(unsigned int);
extern void func_02016004(UnkStruct_02014fe8 *);

int func_02015094(int param)
{
    int result = 0;

    if (func_0201596c(param, 6)) {
        result = 1;
    }

    return result;
}

int func_02015038(UnkStruct_02015038 *self)
{
    u32 fc = self->unk_4C;

    if (fc != 0 && self->unk_40 != 0) {
        if (func_02019d0c(fc + 0x564, 0x10, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0) != 0) {
            func_0201600c(self);
            func_02068440(self->unk_40);
            self->unk_AC = 1;
        }
    }
    return 0;
}

int func_02014fe8(UnkStruct_02014fe8 *p)
{
    int result = 0;
    if (p->unk_4C == 0) {
        goto done;
    }
    if (p->unk_40 == 0) {
        goto done;
    }
    if (func_02019e00(p->unk_4C + 0x564) != 0x10) {
        goto done;
    }
    if (func_02019de8(p->unk_4C + 0x564) == 0) {
        goto done;
    }
    func_02068434(p->unk_40);
    func_02016004(p);
    p->unk_AC = 2;
    result = 1;
done:
    return result;
}
