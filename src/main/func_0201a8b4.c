/* func_0201a8b4 @ 0x0201a8b4, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0201a8b4 {
    u8 pad_00[8];
    u8 sub[0x12];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[4];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[4];
    u8 unk_2A;
    u8 pad_2B[0x31];
    s32 unk_5C;
    u8 unk_60;
} UnkStruct_0201a8b4;

typedef struct UnkStruct_0201a8b4_2 {
    u8 pad_00[0x5c];
    u8 sub2[0x30];
    s16 unk_8C;
    s16 unk_8E;
} UnkStruct_0201a8b4_2;

typedef struct {
    u8 data[12];
} LocalType;

extern int func_020ea9e4(void *, void *);
extern int func_020e8870(void *, int, s16);

extern int func_0201ac10(UnkStruct_0201a8b4 *a, void *b, void *c, int d);
extern int func_0201abd0(UnkStruct_0201a8b4 *a, void *b, void *c, int d);
extern int func_0201ad8c(UnkStruct_0201a8b4 *a, void *b);
extern int func_0201ab94(UnkStruct_0201a8b4 *a, void *b, void *c, int d);
extern int func_0201a814(UnkStruct_0201a8b4 *a, int value);

void func_0201a8b4(UnkStruct_0201a8b4 *a, UnkStruct_0201a8b4_2 *b)
{
    int r6 = 0;
    int r7 = 0;
    int ret_ac, ret_40814;
    LocalType local;

    ret_ac = func_020ea9e4(a->sub, b->sub2);
    a->unk_2A = 0;
    if (a->unk_5C != 0) {
        int abs_ret = ret_ac < 0 ? -ret_ac : ret_ac;
        if (abs_ret >= a->unk_5C) {
            goto exit_label;
        }
    }

    ret_ac = func_0201ac10(a, a->sub, b->sub2, b->unk_8E);
    if (a->unk_60 != 0) {
        if (func_0201a814(a, ret_ac) == 0) {
            goto exit_label;
        }
    }

    r6 = func_0201abd0(a, a->sub, b->sub2, b->unk_8E);
    if (func_0201ad8c(a, &local) == 0) {
        goto exit_label;
    }
    r7 = func_0201ab94(a, a->sub, &local, b->unk_8C);
    a->unk_2A = 1;

exit_label:
    if (a->unk_22 != r6) {
        func_020e8870(&a->unk_22, r6, a->unk_24);
    }
    if (a->unk_1A != r7) {
        func_020e8870(&a->unk_1A, r7, a->unk_1C);
    }
    if (a->unk_22 != r6 || a->unk_1A != r7) {
        a->unk_2A = 0;
    }
}
