/* func_ov004_02243248 @ 0x02243248, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243248 {
    char unk_00[0x16c];
    int unk_16C;
    char unk_170[0x172 - 0x170];
    short unk_172;
    char unk_174[0x190 - 0x174];
    short unk_190;
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243248;

extern void func_ov004_02244fb8(Vec3 *out, int ang);
extern int FX_MulFunc(int a, int b);
extern int func_02034270(void *w, Vec3 *v, int a, int b);
extern int func_020341c8(void *w, int a);
extern void func_0203423c(void *w);

void func_ov004_02243248(UnkStruct_02243248 *self, short *p)
{
    Vec3 d;
    char w[0x40];
    Vec3 *q;
    int spd, ok, t;

    q = &self->pos;
    spd = (self->unk_16C + 2) << 12;
    func_ov004_02244fb8(&d, self->ang);
    q->x = q->x + FX_MulFunc(spd, d.x);
    q->z = q->z + FX_MulFunc(spd, d.z);
    t = *p;
    q->y = q->y + (0x19 - t) * (t << 2);
    func_02034270(w, q, 0, 1);
    if (q->y <= func_020341c8(w, 0)) {
        ok = 1;
    } else {
        ok = 0;
    }
    func_0203423c(w);
    if (ok != 0 && *p > 0) {
        self->unk_172 = 4;
        *(short *) ((char *) self + 0x9c) = 0;
        *p = 0;
        self->unk_190 = 0;
    } else {
        *p = (short) (*p + 2);
    }
}
