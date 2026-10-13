/* func_ov004_0224457c @ 0x0224457c, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_0224457c {
    char unk_00[0x4c];
    int unk_4C;
    char unk_50[0x170 - 0x50];
    unsigned char unk_170;
} UnkStruct_0224457c;

extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern int FX_MulFunc(int a, int b);
extern void func_ov004_022444f0(UnkStruct_0224457c *self, short *p);
extern void func_ov004_02244d58(UnkStruct_0224457c *self);
extern void func_ov004_022449ec(UnkStruct_0224457c *self, int a, int b, int c);

void func_ov004_0224457c(UnkStruct_0224457c *self)
{
    Vec3 *q;
    short *h;
    int v;
    char *base;

    q = (Vec3 *) ((char *) self + 0x2c8);
    h = (short *) ((char *) self + 0x168);
    v = *h;
    v = (0x44 - v * 5) * v;
    base = (char *) self + 0xb0;
    if ((((unsigned long) *(unsigned long *) (base + 0xa0) << 4) >> 16) > 9) {
        func_02056fcc(base + 0x9c, 9, 0, self->unk_4C, 0);
    }
    if (self->unk_170 != 0 && v >= 0) {
        v = FX_MulFunc(v, 0x2000);
    } else if (v < -0x333) {
        v = -0x333;
    }
    q->y = q->y + v;
    func_ov004_022444f0(self, h);
    *h = (short) (*h + 4);
    func_ov004_02244d58(self);
    func_ov004_022449ec(self, 0xaaa, 0x14, 0x3c);
}
