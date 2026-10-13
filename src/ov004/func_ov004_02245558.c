/* func_ov004_02245558 @ 0x02245558, 0x36 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_02245558;

extern void func_ov004_02245590(void *, UnkStruct_02245558 *, int, int, int, int, int);

void *func_ov004_02245558(void *self, char *p)
{
    UnkStruct_02245558 t;
    int x = *(int *) (p + 8), y = *(int *) (p + 4), z = *(int *) p;
    t.a = z;
    t.b = y;
    t.c = x;
    func_ov004_02245590(self, &t, *(u8 *) (p + 0xc), *(u8 *) (p + 0xd), *(short *) (p + 0xe), *(int *) (p + 0x10),
                        *(u8 *) (p + 0x14));
    return self;
}
