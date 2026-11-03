/* player_fish_4: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222a938 @ 0x0222a938, 0x28 bytes, Thumb
 * func_ov003_0222a918 @ 0x0222a918, 0x20 bytes, Thumb
 * func_ov003_0222a8a8 @ 0x0222a8a8, 0x70 bytes, Thumb
 * func_ov003_0222a88c @ 0x0222a88c, 0x1a bytes, Thumb
 * func_ov003_0222a7bc @ 0x0222a7bc, 0xd0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x3c];
    u8 unk_80;
    char pad_81[0x23];
} UnkStruct_0222a938;

typedef struct {
    char pad_00[0x54];
    char unk_54;
    char pad_55[0x4f];
} UnkStruct_0222a918;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xa0 - 0x44];
    u8 unk_A0;
    char pad_A1[3];
} UnkStruct_0222a8a8;

typedef struct {
    char pad_00[0x44];
    int unk_44;
} UnkStruct_0222a88c;

extern UnkStruct_0222a938 data_ov003_0225f4dc[];
extern char data_ov003_0225f530[];
extern void *data_020ccf94;
extern void func_02073820(void *h);
extern void func_020737f0(void *h, char *b, int n);
extern void func_02073770(void *h, int a, int b);
int func_0204fd6c(int a, int b);

int func_ov003_0222a938(int i)
{
    if (i < 0 || i >= 4) {
        return 1;
    }
    {
        UnkStruct_0222a938 *e = &data_ov003_0225f4dc[i];
        if (e->unk_40 != 0) {
            return 1;
        }
    }
    return 0;
}

void *func_ov003_0222a918(int i)
{
    if (i < 0 || i >= 4) {
        return data_ov003_0225f530;
    }
    return &((UnkStruct_0222a918 *) data_ov003_0225f4dc)[i].unk_54;
}

int func_ov003_0222a8a8(int idx)
{
    int r = 0;
    UnkStruct_0222a8a8 *e;
    if (idx < 0 || idx >= 4) {
        return 0;
    }
    e = &((UnkStruct_0222a8a8 *) data_ov003_0225f4dc)[idx];
    if (e->unk_40 != 3 && e->unk_40 != 2) {
        return r;
    }
    if (e->unk_A0 == 0) {
        char b = 1;
        void *h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &b, 1);
        func_02073770(h, 0x2a, 4);
        e->unk_A0 = 1;
        r = 1;
    }
    return r;
}

int func_ov003_0222a88c(UnkStruct_0222a88c *self, void *object)
{
    int r = 0;
    if (func_0204fd6c(self->unk_44, 1) != 0) {
        r = 1;
    }
    return r;
}

void func_ov003_0222a7bc(char *self, int v, int kind)
{
    s16 *a = (s16 *) (self + 0x96);
    s16 *b = (s16 *) (self + 0x98);
    s16 *c = (s16 *) (self + 0x9a);
    switch (kind) {
        case 0xa:
        case 0xb:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x30:
            *c = *c + 0x7fff;
            *b = -v;
            *a = *a + 0x4000;
            break;
        case 0xf:
            *c = *c + 0x6000;
            *b = v;
            *a = *a + 0x4000;
            break;
        case 0x23:
        case 0x24:
        case 0x25:
            *b = v;
            break;
        case 0x35:
        case 0x36:
            *a = *a + 0x4000;
            *b = v;
            break;
        default:
            *c = *c + 0x4000;
            *a = v;
            *a = *a + 0x4000;
            break;
    }
}
