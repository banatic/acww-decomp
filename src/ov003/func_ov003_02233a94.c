/* func_ov003_02233a94 @ 0x02233a94, 0x1dc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern int func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_020341c8(int *ctx, int a);
extern void func_0203423c(int *ctx);
extern int func_020310c8(int value);
extern int func_020644cc(int n);
extern short func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int func_020e8bb0(int *p, int a, int b, int c, int d);
extern void func_020550e4(unsigned char *p, int a);
extern void func_ov003_02234cc4(unsigned char *self);
extern void func_ov003_022339f0(unsigned char *self);
extern int func_ov003_02235b54(unsigned char *self, int a, int b);
extern int func_ov003_02235454(unsigned char *self);
extern void func_ov003_02230f60(unsigned char *self);
extern int func_ov003_02232598(unsigned char *self, int n);

void func_ov003_02233a94(unsigned char *self)
{
    int spd;
    int hit;
    int ctx[16];
    int state;
    Vec3 *prev;
    Vec3 *pos;
    int vy;
    int r;

    prev = (Vec3 *) (self + 0x1d4);
    pos = (Vec3 *) (self + 0x204);
    spd = 0x1000 / self[0x257];
    hit = 0;
    state = self[0x251];
    if (self[0x24a] != 0) {
        func_ov003_02234cc4(self);
        func_ov003_022339f0(self);
    }
    if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        if (func_020e908c(pos, prev, spd, 0x14000, 0x333) == 0) {
            hit = 1;
        } else {
            *(short *) (self + 0x23a) = func_0200322c(pos, prev);
        }
    } else {
        hit = 1;
        prev->x = pos->x;
        prev->y = pos->y;
        prev->z = pos->z;
    }
    if (self[0x24c] != 0) {
        if (func_020e8bb0(&pos->y, 0x1400, spd, 0x1000, 0xcd) == 0) {
            self[0x24c] = 0;
        }
    } else {
        func_02034270(ctx, pos, 0, 1);
        if (ctx[12] != 0) {
            vy = ctx[15];
            if (self[0x251] == 0x11) {
                func_ov003_02235454(self);
                *(short *) (self + 0x242) = 0;
                func_ov003_02230f60(self);
                func_0203423c(ctx);
                return;
            }
        } else {
            vy = func_020341c8(ctx, 1);
            if (vy > 0x4000) {
                vy = func_020310c8(0);
            } else {
                vy = vy + func_020310c8(0);
            }
        }
        if (func_020e8bb0(&pos->y, vy, spd, 0x1000, 0x266) == 0 && hit != 0 && state != 0xb && state != 9) {
            r = func_020644cc(9);
            *(short *) (self + 0x232) = (short) (0x14 * (r + 2));
            self[0x251] = 0x13;
            func_020550e4(self + 0x50, 0);
            if (vy < 0) {
                func_ov003_02235454(self);
                *(short *) (self + 0x242) = 0;
                func_ov003_02230f60(self);
            } else if (self[0x24a] != 0) {
                self[0x254] = (unsigned char) (self[0x255] - 0xa);
                self[0x24a] = 0;
            }
        }
        func_0203423c(ctx);
    }
    if (state == 9 || state == 0xb) {
        if (func_ov003_02232598(self, 1) != 0) {
            func_ov003_02230f60(self);
        }
    }
}
