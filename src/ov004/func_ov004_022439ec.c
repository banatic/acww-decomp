/* func_ov004_022439ec @ 0x022439ec, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022439ec {
    char unk_00[0x22];
    unsigned char unk_22;
    char unk_23[0x58 - 0x23];
    int xmin;
    int zmin;
    int xmax;
    int zmax;
    char unk_68[0x98 - 0x68];
    short unk_98;
    char unk_9A[0xac - 0x9a];
    short unk_AC;
    char unk_AE[0x16c - 0xae];
    int spd;
    char unk_170[0x172 - 0x170];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_022439ec;

extern void func_ov004_02244fb8(Vec3 *out, int a);
extern int FX_MulFunc(int a, int b);
extern int func_ov004_02243980(int a);
extern int func_020644cc(int a);

void func_ov004_022439ec(UnkStruct_022439ec *self, short *n)
{
    Vec3 *v;
    struct {
        Vec3 out, save;
    } f;
    int *lo, *hi;
    int b;

    v = &self->pos;
    f.save.x = v->x;
    f.save.y = v->y;
    f.save.z = v->z;
    hi = &self->xmax;
    lo = (int *) self;
    lo = (int *) ((int) lo + 0x58);
    func_ov004_02244fb8(&f.out, self->ang);
    self->pos.x += FX_MulFunc((*n * self->spd) << 12, f.out.x);
    v->z += FX_MulFunc((*n * self->spd) << 12, f.out.z);
    v->y = 0x200;
    *n = *n - 1;
    if (self->pos.x < self->xmin || self->pos.x > hi[0] || v->z < lo[1] || v->z > hi[1]) {
        b = -0x8000;
        v->x = f.save.x;
        v->y = f.save.y;
        v->z = f.save.z;
        b += func_ov004_02243980(8);
        self->unk_AC = (short) b;
        self->unk_172 = 0xf;
        *n = 0;
    } else if (*n <= 0) {
        self->unk_172 = 0x19;
        if (self->unk_22 != 0) {
            self->unk_98 = (short) func_020644cc(0x3c);
        } else {
            self->unk_98 = (short) func_020644cc(0x12c);
        }
    }
}
