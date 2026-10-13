/* func_ov003_02232210 @ 0x02232210, 0x204 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_02034184(int *ctx, int y);
extern void func_0203423c(int *ctx);
extern int func_020a7278(void);
extern short func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int FX_Div(int a, int b);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern void func_ov003_02230f60(unsigned char *self);
extern void func_ov003_02235454(unsigned char *self);
extern int func_ov003_02232dd4(unsigned char *self);
extern int func_ov003_02235834(unsigned char *self, int ang, int a);
extern short FX_SinCosTable_[];

int func_ov003_02232210(unsigned char *self)
{
    Vec3 *pos;
    short *p242;
    int ret;
    short ang;
    Vec3 d;
    int ctx[16];
    Vec3 *prev;
    int n;
    int m;

    pos = (Vec3 *) (self + 0x204);
    p242 = (short *) (self + 0x242);
    ret = 0;
    func_02034270(ctx, pos, ret, 1);
    prev = (Vec3 *) (self + 0x1d4);
    func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    if (func_020a7278() != 0 || self[0x251] == 0x11) {
        if (ctx[12] != 0) {
            if (func_02034184(ctx, pos->y) != 0) {
                func_ov003_02230f60(self);
                func_ov003_02235454(self);
                ret = 2;
            } else {
                pos->y = pos->y - 0x200;
                ret = 1;
            }
        }
    }
    if (func_ov003_02232dd4(self) != 0) {
        self[0x24b] = 0;
        n = *p242;
        if (n < 2) {
            ang = (short) (*(short *) (self + 0x23a) - 0xaaa);
        } else {
            m = n + 1;
            if (m % 4 == 0) {
                ang = (short) (*(short *) (self + 0x23a) + 0xaaa);
            } else if (m % 2 == 0) {
                ang = (short) (*(short *) (self + 0x23a) - 0xaaa);
            }
        }
        func_ov003_02235834(self, ang, 0xc000);
        func_0203423c(ctx);
        return 0;
    }
    if (*(signed char *) (self + 0x24d) == 0x1e) {
        n = func_020e908c(pos, prev, 0x28, 0x1000, 0x19a);
    } else {
        n = func_020e908c(pos, prev, 8, 0x1000, 0x52);
    }
    if (n == 0) {
        if (func_020a7278() != 0 && func_ov003_02235834(self, *(short *) (self + 0x23a), 0xc000) == 0) {
            prev->x = prev->x + FX_SinCosTable_[(*(unsigned short *) (self + 0x23a) >> 4) * 2];
            prev->z = prev->z + FX_SinCosTable_[(*(unsigned short *) (self + 0x23a) >> 4) * 2 + 1];
            func_0203423c(ctx);
            return 0;
        }
    } else {
        *(short *) (self + 0x23a) = func_0200322c(pos, prev);
    }
    n = *p242;
    if (n == 0) {
        n = *(short *) (self + 0x23a);
        *(short *) (self + 0x23a) = (short) (n + FX_Div(0x2000, 0x6000));
    } else if (n % 4 == 0) {
        *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) + 0xaaa);
    } else if (n % 2 == 0) {
        *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) - 0xaaa);
    }
    *p242 = (short) (*p242 + 1);
    self[0x24b] = 1;
    func_0203423c(ctx);
    return ret;
}
