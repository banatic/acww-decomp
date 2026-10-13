/* func_ov004_0223938c @ 0x0223938c, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0223938c {
    int x, y, z;
};

extern int _s32_div_f(int a, int b);
extern int func_ov004_02239354(struct UnkStruct_0223938c *p);

int func_ov004_0223938c(struct UnkStruct_0223938c *self, int d)
{
    int found;
    int sx;
    int sz;
    int i;
    int b;
    int a;
    int c;
    int e;
    struct UnkStruct_0223938c t;

    found = 0;
    sx = 2;
    sz = 2;
    if (d < 0) {
        sx = sx * ~found;
    }
    if (d < 0) {
        d = -d;
    }
    if (d > 0x4000) {
        sz = sz * ~found;
    }
    for (i = 0; i < 0x32; i++) {
        a = self->z;
        b = self->y;
        t.x = self->x + _s32_div_f((sx * i) << 12, 0xa);
        t.y = b;
        t.z = a;
        if (func_ov004_02239354(&t) == 0) {
            found = 1;
            break;
        }
        c = self->z + _s32_div_f((sz * i) << 12, 0xa);
        e = self->y;
        t.x = self->x;
        t.y = e;
        t.z = c;
        if (func_ov004_02239354(&t) == 0) {
            break;
        }
    }
    return found;
}
