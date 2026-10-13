/* func_ov003_022291e4 @ 0x022291e4, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_022291e4;
typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xa4 - 0x44];
} UnkStruct_022291e4_2;

extern UnkStruct_022291e4_2 data_ov003_0225f4dc[];
extern int func_0204fed0(u8 k);
extern int func_0204feac(UnkStruct_022291e4 *p, int *q, u8 k);
extern int func_ov003_02229184(void *a0, u8 k, int t, UnkStruct_022291e4 *p);
extern void func_0204ff00(u8 k, int a, int b, int c, int d);

void func_ov003_022291e4(void *a0, int idx)
{
    UnkStruct_022291e4 p;
    int q;
    int t;
    t = func_0204fed0((u8) idx);
    p.b = 0xffffeccd;
    if (func_0204feac(&p, &q, (u8) idx)) {
        if (func_ov003_02229184(a0, (u8) idx, t, &p)) {
            func_0204ff00((u8) idx, 3, -1, 0, 0);
        } else {
            UnkStruct_022291e4_2 *e = &data_ov003_0225f4dc[idx];
            e->unk_40 = 4;
        }
    }
}
