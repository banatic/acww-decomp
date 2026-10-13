/* func_ov004_02243544 @ 0x02243544, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243544 {
    char unk_00[0x34];
    Vec3 dst;
    char unk_40[0x98 - 0x40];
    short unk_98;
    char unk_9A[0x172 - 0x9a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243544;

extern void func_ov004_02243484(UnkStruct_02243544 *self);
extern int func_ov004_02244c20(UnkStruct_02243544 *self);
extern void func_ov004_02244f48(Vec3 *out, Vec3 *base, int ang, int r);
extern void *func_020961a8(int a);
extern int func_020644cc(int a);
extern int func_020ea990(Vec3 *a, Vec3 *b);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int FX_MulFunc(int a, int b);

void func_ov004_02243544(UnkStruct_02243544 *self)
{
    Vec3 *p, *q;
    unsigned char k;
    short a;
    char *o;

    if (self->unk_172 == 4) {
        func_ov004_02243484(self);
    } else if (func_ov004_02244c20(self) != 0) {
        o = (char *) func_020961a8(4);
        if (o != 0) {
            k = (unsigned char) (func_020644cc(0x21) + 0x10);
            p = &self->pos;
            q = (Vec3 *) (o + 0x5c);
            if (func_020ea990(q, p) > 0x6000) {
                k = (unsigned char) (k + 0x10);
            }
            self->ang = (short) func_0200322c(p, q);
            a = self->ang;
            func_ov004_02244f48(&self->dst, p, a, FX_MulFunc(k << 12, 0x100));
            self->unk_98 = 1;
            self->unk_172 = 4;
        }
    }
}
