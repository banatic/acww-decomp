/* func_ov003_0222aa50 @ 0x0222aa50, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x54];
    Vec3 unk_54;
    char pad_60[0x24];
    Vec3 unk_84;
    char pad_90[0x14];
} UnkStruct_0222aa50;
extern UnkStruct_0222aa50 data_ov003_0225f4dc[];

int func_ov003_0222aa50(char *p, Vec3 *a, Vec3 *b)
{
    s8 k;
    UnkStruct_0222aa50 *e;
    Vec3 *q;
    if (p == 0) {
        return 0;
    }
    k = *(s8 *) (p + 0x227);
    if (k == -1) {
        return 0;
    }
    e = &data_ov003_0225f4dc[k];
    q = &e->unk_54;
    q->x = a->x;
    q->y = a->y;
    q->z = a->z;
    q = &e->unk_84;
    q->x = b->x;
    q->y = b->y;
    q->z = b->z;
    return 1;
}
