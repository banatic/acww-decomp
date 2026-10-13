/* func_020375a0 @ 0x020375a0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020375a0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_020375a0;

typedef struct UnkStruct_020375a0_2 {
    int a;
    int b;
} UnkStruct_020375a0_2;

typedef struct UnkStruct_020375a0_3 {
    UnkStruct_020375a0 a[31];
    UnkStruct_020375a0_2 b[9];
    u8 unk_618;
    u8 pad_619[3];
    int unk_61C;
    u8 pad_620[0x10];
    int unk_630;
} UnkStruct_020375a0_3;

extern void func_0205cab0(UnkStruct_020375a0_3 *s);

int func_020375a0(UnkStruct_020375a0_3 *s)
{
    UnkStruct_020375a0 *p;
    UnkStruct_020375a0_2 *q;
    u32 i;
    u32 j;

    // Walks with pointers rather than indexing s->a[i].
    p = s->a;
    for (i = 0; i < 31; i++) {
        p->unk_00 = 0xffff;
        p->unk_04 = 0;
        p->unk_08 = 0;
        p->unk_0C = 0;
        p->unk_14 = 0;
        p->unk_18 = 0;
        p->unk_1C = 0;
        p->unk_10 = 0;
        p->unk_28 = 0;
        p->unk_2C = 0;
        p->unk_20 = 0;
        p++;
    }
    q = s->b;
    for (j = 0; j < 9; j++) {
        q->a = 0xffff;
        q->b = 0;
        q++;
    }
    s->unk_630 = 0;
    s->unk_618 = 0;
    s->unk_61C = 0;
    func_0205cab0(s);
    return 1;
}
