/* func_ov003_02232414 @ 0x02232414, 0x184 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02034270(int *ctx, Vec3 *p, int a, int b);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_02034184(int *ctx, int y);
extern void func_ov003_02230f60(unsigned char *self);
extern void func_ov003_02235454(unsigned char *self);
extern int func_ov003_02232dd4(unsigned char *self);
extern void func_0203423c(int *ctx);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

int func_ov003_02232414(unsigned char *self)
{
    int ret;
    short *p242;
    Vec3 d;
    int ctx[16];
    Vec3 *pos;
    int speed;
    int k;
    int step;
    int a;
    int n;

    pos = (Vec3 *) (self + 0x204);
    p242 = (short *) (self + 0x242);
    speed = 2;
    ret = 1;
    func_02034270(ctx, pos, 0, ret);
    k = *(signed char *) (self + 0x24d);
    func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    if (ctx[12] != 0) {
        if (func_02034184(ctx, pos->y) != 0) {
            func_ov003_02230f60(self);
            func_ov003_02235454(self);
            ret = 0;
        } else {
            pos->y = pos->y - 0x200;
        }
    } else {
        pos->y = pos->y - 0x200;
    }
    if (func_ov003_02232dd4(self) != 0) {
        self[0x24b] = 0;
        func_0203423c(ctx);
        return 1;
    }
    if ((unsigned char) (signed char) (k - 0x36) <= 1) {
        if (self[0x251] == 5) {
            if (*(short *) (self + 0x23e) > 0 && k != 0x37) {
                speed = 0xc;
            } else {
                speed = 7;
            }
        } else {
            speed = 4;
        }
    }
    if (*(signed char *) (self + 0x24d) == 0x37) {
        step = 0x71c;
    } else {
        step = 0xaaa;
    }
    n = *p242;
    if (n == 0) {
        a = *(short *) (self + 0x23a);
        *(short *) (self + 0x23a) = (short) (a + FX_Div(step, 0x2000));
    } else if (n % 4 == 0) {
        *(short *) (self + 0x23a) = (short) (step + *(short *) (self + 0x23a));
    } else if (n % 2 == 0) {
        *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) - step);
    }
    pos->x = pos->x + FX_MulFunc(d.x, (speed * self[0x257]) << 12);
    pos->z = pos->z + FX_MulFunc(d.z, (speed * self[0x257]) << 12);
    *p242 = (short) (*p242 + 1);
    self[0x24b] = 1;
    func_0203423c(ctx);
    return ret;
}
