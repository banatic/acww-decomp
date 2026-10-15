/* func_ov003_02233178 @ 0x02233178, 0x238 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233178;

extern int func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_020341c8(int *ctx, int a);
extern int func_02034184(int *ctx, int y);
extern void func_0203423c(int *ctx);
extern int func_020310c8(int a);
extern int func_02073dd4(UnkStruct_02233178 *p, int a);
extern int func_020a7278(void);
extern void func_020550e4(unsigned char *p, int a);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_ov003_02235b54(unsigned char *self, int a, int b);
extern void func_ov003_02230f60(unsigned char *self);
extern int func_ov003_02235454(unsigned char *self);
extern int func_ov003_02235834(unsigned char *self, int ang, int a);
extern UnkStruct_02233178 *data_020ccf94;

void func_ov003_02233178(unsigned char *self, short *p)
{
    volatile Vec3 save;
    Vec3 d;
    int ctx[16];
    Vec3 *pos;
    int vy;
    int st;
    int k;
    int n;

    pos = (Vec3 *) (self + 0x204);
    save.x = pos->x;
    save.y = pos->y;
    save.z = pos->z;
    func_02034270(ctx, pos, 0, 1);
    if (*(signed char *) (self + 0x24d) == 0x35) {
        *(short *) (self + 0x23a) = 0;
        func_ov003_0223597c(&d, *(short *) (self + 0x23c));
    } else {
        func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    }
    if (self[0x251] == 5 || func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        pos->x = pos->x + FX_MulFunc((self[0x257] + 2) << 12, d.x);
        pos->z = pos->z + FX_MulFunc((self[0x257] + 2) << 12, d.z);
    }
    st = self[0x251];
    if (st == 9 || st == 0xb) {
        switch (*(signed char *) (self + 0x24d)) {
            case 0x18:
            case 0x1f:
            case 0x35:
            case 0x36:
            case 0x37:
                n = *p;
                pos->y = pos->y - 0xa * n * n;
                break;
            default:
                n = *p;
                pos->y = pos->y + (0xa0 - 0xb * n) * n;
                break;
        }
    } else {
        n = *p;
        pos->y = pos->y + (0xc8 - 0xb * n) * n;
    }
    if (ctx[12] != 0) {
        vy = ctx[15];
    } else {
        vy = func_020341c8(ctx, 0);
        if (vy > 0x4000) {
            vy = 0;
            pos->x = save.x;
            pos->z = save.z;
        }
    }
    if (pos->y <= vy && *p > 0) {
        if (func_02034184(ctx, pos->y) != 0) {
            func_ov003_02230f60(self);
            func_ov003_02235454(self);
        } else {
            if (self[0x251] == 0xb) {
                k = *(signed char *) (self + 0x24d);
                if (k == 0x1f) {
                    self[0x257] = 4;
                } else if (k == 0x31) {
                    *(short *) (self + 0x232) = 0;
                    if ((unsigned) (*(int *) (self + 0xf4) << 4) >> 16 != 1) {
                        func_020550e4(self + 0x50, 1);
                    }
                }
                self[0x251] = 9;
            } else {
                self[0x251] = 4;
                if (*(signed char *) (self + 0x24d) == 0x31) {
                    func_020550e4(self + 0x50, 1);
                }
                k = *(signed char *) (self + 0x24d);
                if (k == 0x31 || k == 0x1e) {
                    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() != 0) {
                        func_ov003_02235834(self, *(short *) (self + 0x23a), 0xc000);
                    }
                }
            }
            self[0x254] = 0;
            *p = 0;
            pos->y = vy + func_020310c8(0);
            if (*(signed char *) (self + 0x24d) != 0x35) {
                *(short *) (self + 0x238) = 0;
            }
        }
    } else {
        *p = (short) (*p + 2);
    }
    func_0203423c(ctx);
}
