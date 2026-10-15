/* func_020b0ea8 @ 0x020b0ea8, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_020b0ea8;
typedef struct {
    u16 unk_00;
    short unk_02;
    short unk_04;
    short unk_06;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020b0ea8_2;
typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[2];
    UnkStruct_020b0ea8_2 *e;
} UnkStruct_020b0ea8_3;

extern u64 OS_GetTick(void);
extern int func_02003348(u16 a, int b, UnkStruct_020b0ea8 *v, void *p, int z);

int func_020b0ea8(UnkStruct_020b0ea8_3 *self, u8 *cnt, u64 start)
{
    unsigned int ok;
    UnkStruct_020b0ea8 v;
    int i;
    UnkStruct_020b0ea8_2 *e;

    if (cnt != 0) {
        i = *cnt;
    } else {
        i = 0;
    }
    e = self->e + i;
    ok = 1;
    for (;;) {
        {
            int t2 = ((int) e->unk_06 << 12) >> 4;
            int t1 = ((int) e->unk_04 << 12) >> 4;
            int t0 = ((int) e->unk_02 << 12) >> 4;
            v.x = t0;
            v.y = t1;
            v.z = t2;
        }
        func_02003348(e->unk_00, e->unk_10, &v, &e->unk_08, 0);
        e++;
        i++;
        if (cnt != 0) {
            *cnt = (u8) (*cnt + 1);
        }
        if (i >= self->unk_01) {
            break;
        }
        if (cnt != 0) {
            if ((u32) ((OS_GetTick() - start) * 64 / 33514) > 0x28) {
                ok = 0;
                break;
            }
        }
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}
