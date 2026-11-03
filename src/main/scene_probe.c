/* scene_probe: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201af14 @ 0x0201af14, 0x6 bytes, Thumb
 * func_0201af0c @ 0x0201af0c, 0x6 bytes, Thumb
 * func_0201ae8c @ 0x0201ae8c, 0x80 bytes, Thumb
 * func_0201ae44 @ 0x0201ae44, 0x48 bytes, Thumb
 * func_0201ae40 @ 0x0201ae40, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char unk_00;
} UnkStruct_0201af14;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0201af0c;

typedef struct {
    char data[12];
} UnkStruct_0201ae44;

typedef struct {
    char data[12];
} GEntry;

struct Param {
    char pad_00[0x5C];
    char unk_5C;
    char pad_5D[0x94 - 0x5C - 1];
    short unk_94;
};

extern volatile u8 data_020e54a8;
extern int func_02030890(void *self);
extern int func_ov004_0223c5a4(void *self);
extern int func_02034270(void *buf, void *self, int a, int b);
extern int func_020341c8(void *buf, int a);
extern int func_0203104c(void *self);
extern void func_0203423c(void *buf);
extern GEntry data_021c16e4[];
extern void func_0201af58(void *out, void *in, GEntry *entry, short s);

void func_0201af14(UnkStruct_0201af14 *p)
{
    p->unk_00 = 0;
}

void func_0201af0c(UnkStruct_0201af0c *p)
{
    p->unk_00 = 0;
}

int func_0201ae8c(void *self)
{
    char buf[0x40];
    int result;
    int flag = (data_020e54a8 == 1) ? 1 : 0;

    if (flag != 0) {
        if (func_02030890(self) != -1) {
            return 1;
        }
        if (func_ov004_0223c5a4(self) != 0) {
            return 1;
        }
        return 0;
    }

    func_02034270(buf, self, 0, 0);
    if (*(int *) (buf + 0x30) != 0) {
        goto set1;
    }
    if (func_020341c8(buf, 1) > 0) {
        goto set1;
    }
    if (func_0203104c(self) == 0) {
        goto set0;
    }
set1:
    result = 1;
    goto tail;
set0:
    result = 0;
tail:
    func_0203423c(buf);
    return result;
}

void func_0201ae44(unsigned char *flags, struct Param *p)
{
    int i;
    for (i = 0; i < 2; i++) {
        UnkStruct_0201ae44 tmp;
        func_0201af58(&tmp, &p->unk_5C, &data_021c16e4[i], p->unk_94);
        if (func_0201ae8c(&tmp)) {
            *flags |= (1 << i);
        }
    }
}

int func_0201ae40(unsigned char *p0)
{
    return p0[0];
}
