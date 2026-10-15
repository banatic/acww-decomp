/* func_ov003_02232f78 @ 0x02232f78, 0x200 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern int func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_02034184(int *ctx, int y);
extern void func_0203423c(int *ctx);
extern int func_ov003_02232598(unsigned char *self, int n);
extern void func_ov003_02230f60(unsigned char *self);
extern int func_ov003_02235454(unsigned char *self);
extern int func_ov003_02232dd4(unsigned char *self);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

void func_ov003_02232f78(unsigned char *self, short *p)
{
    Vec3 *pos;
    int speed;
    int kind;
    short ang;
    int n;
    Vec3 d;
    int ctx[16];

    pos = (Vec3 *) (self + 0x204);
    speed = 2;
    kind = *(signed char *) (self + 0x24d);
    func_02034270(ctx, pos, 0, 1);
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
    }
    if (func_ov003_02232dd4(self) != 0) {
        func_0203423c(ctx);
        return;
    }
    if (ctx[12] != 0) {
        if (func_02034184(ctx, pos->y) != 0) {
            func_ov003_02230f60(self);
            func_ov003_02235454(self);
        } else {
            pos->y = pos->y - 0x100;
        }
        func_0203423c(ctx);
        return;
    }
    pos->y = pos->y - 0x200;
    if (kind == 0x35) {
        ang = *(short *) (self + 0x23c);
        func_ov003_0223597c(&d, ang);
    } else {
        if ((unsigned char) (signed char) (kind - 0x36) <= 1) {
            speed = 4;
        }
        ang = *(short *) (self + 0x23a);
        func_ov003_0223597c(&d, ang);
    }
    if (kind == 0x1f) {
        n = *p;
        if (n == 0) {
            ang = (short) (ang + FX_Div(0x2000, 0x6000));
        } else if (n % 0x10 == 0) {
            ang = (short) (ang + 0x71c);
        } else if (n % 8 == 0) {
            ang = (short) (ang - 0x71c);
        }
    } else {
        n = *p;
        if (n == 0) {
            ang = (short) (ang + FX_Div(0x2000, 0x6000));
        } else if (n % 4 == 0) {
            ang = (short) (ang + 0xaaa);
        } else if (n % 2 == 0) {
            ang = (short) (ang - 0xaaa);
        }
    }
    if (kind == 0x35) {
        *(short *) (self + 0x23c) = ang;
        *(short *) (self + 0x23a) = 0;
    } else {
        *(short *) (self + 0x23a) = ang;
    }
    if (kind == 0x1a) {
        pos->z = pos->z + FX_MulFunc(FX_MulFunc(self[0x257] << 12, d.z), 0x400);
        pos->x = pos->x + FX_MulFunc(FX_MulFunc(self[0x257] << 12, d.x), 0x400);
    } else {
        pos->x = pos->x + FX_MulFunc(d.x, (speed * self[0x257]) << 12);
        pos->z = pos->z + FX_MulFunc(d.z, (speed * self[0x257]) << 12);
    }
    *p = (short) (*p + 1);
    func_0203423c(ctx);
}
