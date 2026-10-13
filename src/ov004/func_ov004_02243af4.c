/* func_ov004_02243af4 @ 0x02243af4, 0xbc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243af4 {
    char unk_00[0xac];
    short unk_AC;
    char unk_AE[0x172 - 0xae];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243af4;

extern int func_020644cc(int a);
extern void func_02091230(int a, void *b, void *c, int d);

void func_ov004_02243af4(UnkStruct_02243af4 *self, short *n)
{
    struct {
        short t;
        Vec3 v;
    } f;
    short a, ang;
    Vec3 *q;
    unsigned char k, i;

    ang = self->ang;
    f.t = ang;
    a = 0;
    if (self->unk_172 == 0xf) {
        a = (short) (ang + self->unk_AC);
        self->unk_172 = 4;
    } else {
        k = (unsigned char) func_020644cc(5);
        for (i = 0; i < k; i++) {
            a = (short) (a + 0xaaa);
        }
        if (func_020644cc(0x64) > 0x32) {
            a = (short) -a;
        }
        a = (short) (a + f.t);
        self->unk_172 = 4;
    }
    if (self->unk_172 == 4) {
        self->ang = a;
        *n = (short) (func_020644cc(8) + 8);
        q = &self->pos;
        f.v.x = q->x;
        f.v.y = q->y;
        f.v.z = q->z;
        f.t = 0;
        func_02091230(0x1f, &f.v, &f.t, 0);
    }
}
