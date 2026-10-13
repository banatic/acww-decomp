/* func_020404b4 @ 0x020404b4, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    u32 w;
    struct {
        u8 b0, b1, b2, b3;
    } b;
} UnkStruct_020404b4;
typedef union {
    u16 w;
    struct {
        u8 x, y;
    } b;
} UnkStruct_020404b4_2;
typedef struct {
    u8 x, y, kind;
} UnkStruct_020404b4_3;
typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_020404b4_4;
typedef struct {
    u8 k, unk_01, unk_02, unk_03;
} UnkStruct_020404b4_5;

extern char data_021dc7a8[];
extern UnkStruct_020404b4_3 *func_020409c8(void *tbl, int idx);

#pragma opt_loop_invariants off

UnkStruct_020404b4 func_020404b4(UnkStruct_020404b4_4 *p, int b, UnkStruct_020404b4_5 a3)
{
    UnkStruct_020404b4_2 t1, t2;
    UnkStruct_020404b4 d;
    UnkStruct_020404b4_3 *e;
    char *base;
    int i, j;

    base = (char *) data_021dc7a8;
    d.w = 0;
    if (b == 0x45) {
        e = func_020409c8(base + 0x17218, a3.k);
        if (e != 0 && b == e->kind) {
            t1 = *(UnkStruct_020404b4_2 *) e;
            d.b.b3 = t1.b.y;
            d.b.b2 = t1.b.x;
            d.b.b1 = (u8) p->unk_08;
        }
        goto end;
    }
    if (b == 0x60) {
        b = 0x40;
    }
    j = a3.k - 1;
    for (i = 0; i < 2; j++, i++) {
        e = func_020409c8(base + 0x17218, j);
        if (e == 0) {
            continue;
        }
        if (b != e->kind) {
            continue;
        }
        t2 = *(UnkStruct_020404b4_2 *) e;
        d.b.b3 = t2.b.y;
        d.b.b2 = t2.b.x;
        d.b.b1 = (u8) p->unk_08;
        break;
    }
end:
    return d;
}
