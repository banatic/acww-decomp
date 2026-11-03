/* room_object_parts_3: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220d4dc @ 0x0220d4dc, 0x10 bytes, Thumb
 * func_ov004_0220d4d8 @ 0x0220d4d8, 0x2 bytes, Thumb
 * func_ov004_0220d4c8 @ 0x0220d4c8, 0x10 bytes, Thumb
 * func_ov004_0220d4c0 @ 0x0220d4c0, 0x6 bytes, Thumb
 * func_ov004_0220d4bc @ 0x0220d4bc, 0x4 bytes, Thumb
 * func_ov004_0220d4b4 @ 0x0220d4b4, 0x6 bytes, Thumb
 * func_ov004_0220d494 @ 0x0220d494, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    short unk_00;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_0220d4dc;

void func_ov004_0220d4dc(UnkStruct_0220d4dc *p)
{
    p->unk_00 = -1;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_02 = 0;
}

void func_ov004_0220d4d8(void *object) {}

int func_ov004_0220d4c8(short *p)
{
    int ok = 0;
    if (*p != -1) {
        ok = 1;
    }
    return ok;
}

int func_ov004_0220d4c0(void *self)
{
    return *(short *) ((char *) self + 0x0);
}

void *func_ov004_0220d4bc(void *self)
{
    return (char *) self + 0x4;
}

int func_ov004_0220d4b4(void *self)
{
    return *(short *) ((char *) self + 0x2);
}

int func_ov004_0220d494(char *self, int a1, char *a2, int a3)
{
    // DECLS
    // ENDDECLS
    if (a1 >= 0x0 && (u32) a1 < 0x1c) {
        *(u16 *) (self) = a1;
        *(int *) (self + 0x4) = *(int *) (a2);
        *(int *) (self + 0x8) = *(int *) (a2 + 0x4);
        *(int *) (self + 0xc) = *(int *) (a2 + 0x8);
        *(u16 *) (self + 0x2) = a3;
        return 0x1;
    }
    return 0x0;
}
