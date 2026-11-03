/* scene_command_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02014f60 @ 0x02014f60, 0x18 bytes, Thumb
 * func_02014f04 @ 0x02014f04, 0x5c bytes, Thumb
 * func_02014eb4 @ 0x02014eb4, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[8];
    u32 unk_4C;
    u8 pad_50[0xac - 0x50];
    u8 unk_AC;
} UnkStruct_02014f04;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x8];
    char *unk_4C;
    char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014eb4;

extern int func_0201596c(int, int);
extern u16 data_020c80f8;
extern int func_02019d0c(u32 p1, int p2, int p3, int p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u16 p10, u32 p11);
extern void func_0201600c(UnkStruct_02014f04 *self);
extern void func_02068440(u32 handle);
int func_02019e00(char *arg);
int func_02019de8(char *arg);
void func_02068434(void *arg);
void func_02016004(UnkStruct_02014eb4 *arg);

int func_02014f60(int arg)
{
    int result;
    result = 0;
    if (func_0201596c(arg, 7) != 0) {
        result = 1;
    }
    return result;
}

int func_02014f04(UnkStruct_02014f04 *self)
{
    u32 fc = self->unk_4C;

    if (fc != 0 && self->unk_40 != 0) {
        if (func_02019d0c(fc + 0x564, 0x11, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0) != 0) {
            func_0201600c(self);
            func_02068440(self->unk_40);
            self->unk_AC = 1;
        }
    }
    return 0;
}

int func_02014eb4(UnkStruct_02014eb4 *s)
{
    int result = 0;

    if (s->unk_4C != 0 && s->unk_40 != 0) {
        if (func_02019e00(s->unk_4C + 0x564) == 0x11 && func_02019de8(s->unk_4C + 0x564) != 0) {
            func_02068434(s->unk_40);
            func_02016004(s);
            s->unk_AC = 2;
            result = 1;
        }
    }
    return result;
}
