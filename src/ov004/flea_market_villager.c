/* flea_market_villager: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221ef70 @ 0x0221ef70, 0x20 bytes, Thumb
 * func_ov004_0221ef2c @ 0x0221ef2c, 0x44 bytes, Thumb
 * func_ov004_0221ef00 @ 0x0221ef00, 0x2c bytes, Thumb
 * func_ov004_0221eed8 @ 0x0221eed8, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0221ef2c;

extern int func_ov004_0221ef90(void *arg0);
extern int func_0203e0a8(int, int);
extern UnkStruct_0221ef2c *func_02095794(int);
extern int func_02030818(UnkStruct_0221ef2c *);
extern void *func_ov004_0221f848(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02253bb4[];

int func_ov004_0221ef70(int param)
{
    int result;
    if (func_ov004_0221ef90((void *) param) != 0) {
        func_0203e0a8(param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

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
        func_0203e0a8((int) self, 0);
        return 1;
    }
    return 0;
}

void *func_ov004_0221ef00(void *s)
{
    *(void **) s = &data_ov004_02253bb4;
    func_ov004_0221f848((char *) s + 0x8a8);
    func_0202e5e0(s);
    func_020edf54(s);
    return s;
}

void *func_ov004_0221eed8(char *self)
{
    *(const void **) self = ((void *const *) data_ov004_02253bb4);
    func_ov004_0221f848(self + 0x8a8);
    func_0202e5e0(self);
    return self;
}
