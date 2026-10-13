/* func_ov003_022349a0 @ 0x022349a0, 0x1e0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02056fcc(unsigned char *p, int a, int b, int c, int d);
extern int func_ov003_02234d70(unsigned char *self);
extern void func_ov003_0222d518(unsigned char *self, int a);
extern int func_020961a8(int a);
extern void func_020eaca0(Vec3 *d, Vec3 *a, unsigned char *b);
extern void func_ov003_022321b8(Vec3 *d, Vec3 *a, int n);
extern void VEC_Add(Vec3 *d, Vec3 *a, Vec3 *b);
extern int func_ov068_022715a0(unsigned char *self, short *p, Vec3 *v);
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022349a0;
extern int func_02073dd4(UnkStruct_022349a0 *p, int a);
extern void func_ov068_022701b0(unsigned char *self, short *ang);
extern void func_ov003_02234840(unsigned char *self, short *p);
extern void func_ov068_0226fea4(unsigned char *self, short *ang, int a, int b, int c, int d);
extern void func_ov003_02234e28(unsigned char *self, short *ang, int a, int b, int c, int d);
extern int FX_MulFunc(int a, int b);
extern UnkStruct_022349a0 *data_020ccf94;

void func_ov003_022349a0(unsigned char *self)
{
    short ang;
    Vec3 v0c;
    Vec3 v18;
    Vec3 *pos;
    short *p242;
    int vy;
    int n;
    unsigned char *t;

    ang = *(short *) (self + 0x23a);
    pos = (Vec3 *) (self + 0x204);
    p242 = (short *) (self + 0x242);
    if (*(signed char *) (self + 0x24d) != 8) {
        if ((unsigned) (*(int *) (self + 0xf0) << 4) >> 16 > 9) {
            func_02056fcc(self + 0xec, 9, 0, *(int *) (self + 0x21c), 0);
        }
    }
    if (func_ov003_02234d70(self) == 2) {
        if (*(signed char *) (self + 0x24d) != 8) {
            func_ov003_0222d518(self, *(int *) (self + 0x21c));
        } else {
            func_ov003_0222d518(self, 0x1000);
        }
        self[0x24a] = 0;
    }
    if (self[0x24a] != 0) {
        if (*(signed char *) (self + 0x24d) != 8) {
            vy = FX_MulFunc(*(int *) (self + 0x21c), 0x1333);
            if (vy != *(int *) (self + 0xfc)) {
                func_ov003_0222d518(self, vy);
            }
        } else {
            t = (unsigned char *) func_020961a8(4);
            if (t != 0) {
                func_020eaca0(&v18, pos, t + 0x5c);
                v0c.x = v18.x;
                v0c.y = v18.y;
                v0c.z = v18.z;
                func_ov003_022321b8(&v0c, &v0c, 3);
                VEC_Add(pos, &v0c, pos);
            }
        }
    } else if (*(signed char *) (self + 0x24d) == 8) {
        if (func_ov068_022715a0(self, p242, &v0c) == 0) {
            return;
        }
    } else {
        if (*(int *) (self + 0x21c) != *(int *) (self + 0xfc)) {
            func_ov003_0222d518(self, *(int *) (self + 0x21c));
        }
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
            func_ov068_022701b0(self, &ang);
        }
    }
    n = *p242;
    vy = 0x44 * n + -10 * (n * n) / 2;
    if (self[0x24c] != 0 && vy >= 0) {
        FX_MulFunc(vy, 0x2000);
    } else if (vy < -0x333) {
        vy = -0x333;
    }
    *p242 = (short) (*p242 + 4);
    func_ov003_02234840(self, p242);
    pos->y = pos->y + vy;
    if (*(signed char *) (self + 0x24d) == 8) {
        func_ov068_0226fea4(self, &ang, 0xaaa, 0x14, 0x3c, self[0x257] << 12);
    } else {
        func_ov003_02234e28(self, &ang, 0x38e, 0x14, 0x3c, self[0x257] << 12);
    }
}
