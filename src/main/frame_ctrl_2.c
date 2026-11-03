/* frame_ctrl_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02057078 @ 0x02057078, 0xc bytes, Thumb
 * func_02057060 @ 0x02057060, 0x18 bytes, Thumb
 * func_02057054 @ 0x02057054, 0xc bytes, Thumb
 * func_02056ffc @ 0x02056ffc, 0x58 bytes, Thumb
 * func_02056fcc @ 0x02056fcc, 0x30 bytes, Thumb
 * func_02056f94 @ 0x02056f94, 0x38 bytes, Thumb
 * func_02056f28 @ 0x02056f28, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
} UnkStruct_02056ffc;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char unk_14;
} UnkStruct_02056fcc;

struct UnkStruct_02056f94 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    char pad_0C[8];
    unsigned char unk_14;
};

typedef struct UnkStruct_02056f28 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[4];
    u8 unk_14;
} UnkStruct_02056f28;

extern unsigned char data_020dd184[];
extern void func_020edb3c(void *obj);

void func_02057078(int *out)
{
    *out = (unsigned int) data_020dd184;
}

void *func_02057060(void *obj)
{
    *(void **) obj = (void *) data_020dd184;
    func_020edb3c(obj);
    return obj;
}

void func_02057054(int *ptr)
{
    *ptr = (int) ((int *) data_020dd184);
}

void func_02056ffc(UnkStruct_02056ffc *o)
{
    int field8;
    unsigned char flag;
    int result;

    field8 = o->unk_08;
    o->unk_0C = field8;
    flag = o->unk_14;

    if (flag & 2) {
        int field10 = o->unk_10;
        if (field8 >= field10) {
            result = field8 - field10;
        } else {
            if (!(flag & 1)) {
                int field4 = o->unk_04;
                result = field8 + (field4 - field10);
            } else {
                result = 0;
            }
        }
    } else {
        int field10 = o->unk_10;
        int sum = field8 + field10;
        int field4 = o->unk_04;
        if (sum >= field4) {
            if (!(flag & 1)) {
                result = sum - field4;
            } else {
                result = field4 - 0x1000;
            }
        } else {
            result = sum;
        }
    }
    o->unk_08 = result;
}

void func_02056fcc(UnkStruct_02056fcc *s, unsigned int param1, unsigned char param2, unsigned int param3,
                   unsigned short param4)
{
    if (param4 == 0xFFFF) {
        param4 = (unsigned short) (param1 - 1);
    }
    s->unk_04 = param1 << 12;
    s->unk_08 = param4 << 12;
    s->unk_10 = param3;
    s->unk_14 = param2;
    s->unk_0C = s->unk_08;
}

int func_02056f94(struct UnkStruct_02056f94 *s)
{
    switch (s->unk_14) {
        case 1:
            if (s->unk_08 < (s->unk_04 - 0x1000)) {
                return 0;
            } else {
                return 1;
            }
        case 3:
            if (s->unk_08 != 0) {
                return 0;
            } else {
                return 1;
            }
        default:
            return 0;
    }
}

// The failing paths share one return 0.
int func_02056f28(UnkStruct_02056f28 *a, int b)
{
    int v;
    int lo;
    int hi;
    int flag;

    v = b << 12;
    lo = a->unk_08;
    hi = a->unk_0C;
    if (hi == lo) {
        if (lo == b) {
            return 1;
        }
        return 0;
    }
    flag = (a->unk_14 & 2) ? 1 : 0;
    if (flag != 0) {
        if (hi > lo) {
            if (hi <= v) {
                goto ret0;
            }
            if (lo > v) {
                goto ret0;
            }
            return 1;
        }
        if (v >= hi && v < lo) {
            goto ret0;
        }
        return 1;
    }
    if (hi < lo) {
        if (hi >= v) {
            goto ret0;
        }
        if (lo < v) {
            goto ret0;
        }
        return 1;
    }
    if (v <= hi && v > lo) {
        goto ret0;
    }
    return 1;
ret0:
    return 0;
}
