/* func_020be1c4 @ 0x020be1c4, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020be1c4_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020be1c4_3;

typedef struct UnkStruct_020be1c4 {
    u8 pad_00[0x1b30];
    UnkStruct_020be1c4_3 arr[5];
} UnkStruct_020be1c4;

typedef struct UnkStruct_020be1c4_2 {
    int m;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020be1c4_2;

extern UnkStruct_020be1c4_2 data_020d2bb4[];

int func_020be1c4(UnkStruct_020be1c4 *p, int i)
{
    int mode;
    int ok;
    int a;
    int b;
    int c;
    int d;
    int e;

    mode = data_020d2bb4[i].m;
    ok = 0;
    if (mode == 6) {
        ok = 1;
    } else if (i == p->arr[mode].unk_00) {
        ok = 1;
    } else {
        a = (p->arr[0].unk_04 > 0);
        b = (p->arr[1].unk_04 > 0);
        c = (p->arr[2].unk_04 > 0);
        d = (p->arr[3].unk_04 > 0);
        e = (p->arr[4].unk_04 > 0);
        if (mode == 0) {
            ok = (!a && !d);
        } else if (mode == 1) {
            ok = (!b && !e);
        } else if (mode == 2) {
            ok = (!c && !d && !e);
        } else if (mode == 3) {
            ok = (!d && !a && !c && !e);
        } else if (mode == 4) {
            ok = (!e && !b && !c && !d);
        }
    }
    if (!ok) {
        return 5;
    }
    return mode;
}
