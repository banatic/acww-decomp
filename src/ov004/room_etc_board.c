/* room_etc_board: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221ad8c @ 0x0221ad8c, 0x24 bytes, Thumb
 * func_ov004_0221ad88 @ 0x0221ad88, 0x4 bytes, Thumb
 * func_ov004_0221ad58 @ 0x0221ad58, 0x30 bytes, Thumb
 * func_ov004_0221ad40 @ 0x0221ad40, 0x18 bytes, Thumb
 * func_ov004_0221ad0c @ 0x0221ad0c, 0x34 bytes, Thumb
 */

#include "types.h"

struct UnkInner {
    int unk_00;
    void *unk_04;
};

struct UnkOuter {
    char pad_00[0x12c];
    struct UnkInner *unk_12C;
};

struct UnkStruct_0221ad58 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0221ad58_2 {
    char pad_00[0xec];
    char unk_EC[0x40];
    struct UnkStruct_0221ad58 *unk_12C;
};

struct UnkStruct_0221ad0c {
    u16 a, b, c;
};

extern int func_ov004_0221ae7c(void *obj, int mode);
extern void func_0203ee08(struct UnkStruct_0221ad58_2 *obj, char *ptr);
extern int func_0203e020(struct UnkStruct_0221ad58_2 *obj);
extern int data_ov004_02257804[];
extern int func_02003348(int p1, int p2, void *p3, void *p4, int p5);
extern u16 data_ov004_02253238;
extern int data_ov004_022577d0;

void func_ov004_0221ad8c(struct UnkOuter *obj)
{
    if (obj->unk_12C != 0 && obj->unk_12C->unk_04 != 0) {
        func_ov004_0221ae7c(obj, 2);
    }
}

int func_ov004_0221ad88(void *callbackObject)
{
    return 1;
}

void func_ov004_0221ad58(struct UnkStruct_0221ad58_2 *obj)
{
    if (obj->unk_12C && obj->unk_12C->unk_04 == 0) {
        char *p = (char *) obj;
        if (p) {
            p += 0xec;
        }
        func_0203ee08(obj, p);
        func_0203e020(obj);
    }
}

int func_ov004_0221ad40(int index)
{
    if (index >= 0 && (unsigned) index < 0x40) {
        return data_ov004_02257804[index];
    }
    return 0;
}

void func_ov004_0221ad0c(void *self, int a, u16 b, u16 c)
{
    struct UnkStruct_0221ad0c s;
    data_ov004_02253238 = c;
    data_ov004_022577d0 = a;
    s.a = 0;
    s.b = b;
    s.c = 0;
    func_02003348(0x17, 0, self, &s, 0);
}
