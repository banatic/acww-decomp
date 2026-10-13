/* func_ov003_02232874 @ 0x02232874, 0x1d0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_020341c8(int *ctx, int a);
extern int func_02034184(int *ctx, int y);
extern void func_0203423c(int *ctx);
extern int func_020310c8(int a);
extern int func_020644cc(int n);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_ov003_02232dd4(unsigned char *self);
extern int func_ov003_02234984(unsigned char *self);
extern void func_ov003_0222e358(unsigned char *self, int n);
extern void func_ov003_02230f60(unsigned char *self);
extern void func_ov003_02235454(unsigned char *self);
extern int func_ov003_02232598(unsigned char *self, int n);

void func_ov003_02232874(unsigned char *self)
{
    int base;
    volatile Vec3 save;
    int ctx[16];
    Vec3 d;
    short *p242;
    Vec3 *pos;
    int y;
    int n;
    int kind;

    kind = self[0x251];
    switch (kind) {
        case 6:
            func_ov003_02232dd4(self);
            if (func_ov003_02234984(self) != 0) {
                self[0x251] = 0xb;
            }
            break;
        case 0xb:
            p242 = (short *) (self + 0x242);
            pos = (Vec3 *) (self + 0x204);
            save.x = pos->x;
            save.y = pos->y;
            save.z = pos->z;
            y = *(int *) (self + 0x228);
            func_02034270(ctx, pos, 0, 1);
            func_ov003_0222e358(self, 0xc8);
            if (func_ov003_02232dd4(self) == 0) {
                func_ov003_0223597c(&d, *(short *) (self + 0x23a));
                pos->x = pos->x + FX_MulFunc(self[0x257] << 12, d.x);
                pos->z = pos->z + FX_MulFunc(self[0x257] << 12, d.z);
            }
            if (y > 0x1000) {
                pos->y = y + FX_MulFunc(0x59a - FX_MulFunc(0xcd, *p242 << 12), *p242 << 12);
            } else {
                pos->y = y + FX_MulFunc(0x99a - FX_MulFunc(0xcd, *p242 << 12), *p242 << 12);
            }
            if (ctx[12] != 0) {
                y = ctx[15];
            } else {
                y = func_020341c8(ctx, 1);
                y = y + func_020310c8(0);
                if (y > 0x1000) {
                    if (y > 0x4000) {
                        y = func_020310c8(0);
                    } else {
                        pos->x = save.x;
                        pos->z = save.z;
                    }
                }
            }
            if (pos->y < y) {
                base = func_020644cc(3);
                *p242 = 0;
                pos->y = y;
                if (func_02034184(ctx, pos->y) != 0) {
                    func_ov003_02230f60(self);
                    func_ov003_02235454(self);
                } else {
                    self[0x251] = 6;
                    *(short *) (self + 0x244) = 4;
                    *(int *) (self + 0x228) = y;
                    if (func_020644cc(100) > 0x32 && *(int *) (self + 0x21c) - base > 0) {
                        self[0x257] = (unsigned char) (*(int *) (self + 0x21c) - base);
                    } else {
                        self[0x257] = (unsigned char) (base + *(int *) (self + 0x21c));
                    }
                }
            } else {
                *p242 = (short) (*p242 + 1);
            }
            if (func_ov003_02232598(self, 1) != 0) {
                func_ov003_02230f60(self);
            }
            func_0203423c(ctx);
            break;
    }
}
