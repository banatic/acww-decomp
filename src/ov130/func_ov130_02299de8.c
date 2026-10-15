/* func_ov130_02299de8 @ 0x02299de8, 0x224 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[8];
    u8 unk_08;
    u8 unk_09;
    char pad_0A[2];
    int unk_0C;
    char pad_10[0x1c - 0x10];
    int unk_1C;
    int unk_20;
} UnkStruct_02299de8;

typedef struct {
    char pad_00[0x60];
    char unk_60[4];
} UnkStruct_02299de8_2;

extern void func_02088df8(int, void *, int, void *, int, int, int, int, int, int, int, int);
extern int func_020896b8(int, void *, int, void *, int, int, int);

extern char data_ov130_0229ab20;
extern char data_ov130_0229abf0;
extern char data_ov130_0229aae0;
extern char data_ov130_0229abb0;
extern char data_ov130_0229ab70;
extern char data_ov130_0229ab40;
extern char data_ov130_0229ab48;
extern char data_ov130_0229ab50;
extern char data_ov130_0229ab58;
extern char data_ov130_0229ab60;
extern char data_ov130_0229ab68;
extern char data_ov130_0229ab10;
extern char data_ov130_0229ab18;
extern char data_ov130_0229ab00;
extern char data_ov130_0229ab08;

void func_ov130_02299de8(UnkStruct_02299de8 *a, UnkStruct_02299de8_2 *b)
{
    char *w;
    void *t1;
    void *t2;
    char *v;

    w = b->unk_60;
    if (a->unk_08 == 0 || a->unk_08 == 2) {
        t1 = &data_ov130_0229ab20;
        t2 = &data_ov130_0229abf0;
    } else if (a->unk_08 == 4) {
        t1 = &data_ov130_0229aae0;
        t2 = &data_ov130_0229abb0;
    } else {
        t1 = &data_ov130_0229aae0;
        t2 = &data_ov130_0229ab70;
    }
    if (a->unk_09 == 3) {
        w = w + 0xa;
    }
    func_02088df8(1, t1, 0x80, w, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, t2, 0x80, w, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    v = b->unk_60;
    if (a->unk_08 == 4) {
        return;
    }
    if (a->unk_08 == 0 || a->unk_08 == 2) {
        if (a->unk_0C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab40, 0x80, v, -1, 2, 0);
        }
        if (a->unk_0C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab48, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab50, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab58, 0x80, v, -1, 2, 0);
        }
        if (a->unk_20 >= 1000) {
            func_020896b8(1, &data_ov130_0229ab60, 0x80, v, -1, 2, 0);
        }
        if (a->unk_20 >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab68, 0x80, v, -1, 2, 0);
        }
        return;
    }

    {
        if (a->unk_08 == 5) {
            v = v - 8;
        }
        if (a->unk_0C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab10, 0x80, v, -1, 2, 0);
        }
        if (a->unk_0C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab18, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab00, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab08, 0x80, v, -1, 2, 0);
        }
    }
}
