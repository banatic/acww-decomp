/* func_ov068_02268c84 @ 0x02268c84, 0x80 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} Vec;
typedef struct {
    fx32 x;
    volatile fx32 y;
    fx32 z;
} VecV;

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019d0c(void *, int, int, fx32, fx32, int, int, int, int, int, int);
extern unsigned short data_020c80f8;

typedef struct {
    char pad_00[0x1c];
    unsigned char unk_1C;
    char pad_1D[3];
    int unk_20;
} UnkStruct_02268c84;

void func_ov068_02268c84(UnkStruct_02268c84 *a1, void *a2)
{
    VecV v;
    Vec *s;
    if (func_02019e00((char *) a2 + 0x564) == 3) {
        if (func_02019de8((char *) a2 + 0x564) != 0) {
            s = (Vec *) ((char *) a2 + 0x5c);
            v.x = s->x;
            v.y = s->y;
            v.z = s->z;
            v.x = v.x - 0x2000;
            v.z = v.z + 0x8000;
            func_02019d0c((char *) a2 + 0x564, 2, 1, v.x, v.z, 0, 0, 0, 0, data_020c80f8, 0);
            a1->unk_20 = 0xc8;
            a1->unk_1C = 2;
        }
    }
}
