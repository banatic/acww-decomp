/* func_ov004_0221ef2c @ 0x0221ef2c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0221ef2c;
extern UnkStruct_0221ef2c *func_02095794(int);
extern int func_02030818(UnkStruct_0221ef2c *);
extern void func_0203e0a8(void *, int);
int func_ov004_0221ef2c(u8 *self)
{
    UnkStruct_0221ef2c v;
    UnkStruct_0221ef2c *p;
    p = func_02095794(4);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    if (func_02030818(&v) != 0) {
        self[0xa54] = 3;
        func_0203e0a8(self, 0);
        return 1;
    }
    return 0;
}
