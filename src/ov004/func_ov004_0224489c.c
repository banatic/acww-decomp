/* func_ov004_0224489c @ 0x0224489c, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_0224489c {
    char unk_00[0x40];
    Vec3 tgt;
    char unk_4C[0x192 - 0x4c];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_0224489c;

extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020ea990(Vec3 *a, Vec3 *b);

void func_ov004_0224489c(UnkStruct_0224489c *self, short *da, int *dist, Vec3 *t)
{
    Vec3 *p, *s;
    short ang;

    p = &self->pos;
    s = &self->tgt;
    t->x = self->tgt.x;
    t->y = s->y;
    t->z = s->z;
    ang = self->ang;
    *da = (short) (func_0200322c(p, t) - ang);
    if (*da > 0x38e) {
        *da = 0x38e;
    } else if (*da < -0x38e) {
        *da = -0x38e;
    }
    *dist = func_020ea990(t, p);
}
