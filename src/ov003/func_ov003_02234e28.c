/* func_ov003_02234e28 @ 0x02234e28, 0x244 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234e28;

extern short func_0200322c(Vec3 *a, Vec3 *b);
extern int func_02073dd4(UnkStruct_02234e28 *p, int a);
extern int func_020a7278(void);
extern int func_020961a8(int a);
extern void func_020eaca0(Vec3 *d, Vec3 *a, Vec3 *b);
extern int func_020ea9c8(Vec3 *a);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int func_020644cc(int n);
extern int _ffix(int f);
extern int FX_MulFunc(int a, int b);
extern int func_ov003_02235b54(unsigned char *self, int a, int b);
extern short func_ov003_0223418c(int ang, int a);
extern int func_ov003_022350cc(unsigned char *self);
extern void func_ov003_02235834(unsigned char *self, int ang, int a);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_ov003_02235130(unsigned char *self);
extern void func_ov003_022351c4(unsigned char *self, Vec3 *v, int a);
extern int func_ov003_0223506c(unsigned char *self);
extern int func_ov003_02233c70(int a, int b);
extern Vec3 *func_ov003_022356ec(Vec3 *pos);
extern UnkStruct_02234e28 *data_020ccf94;

void func_ov003_02234e28(unsigned char *self, short *p, int step, int div, unsigned char thresh, int scale)
{
    int r;
    Vec3 *v1d4;
    int k;
    int hit;
    Vec3 d;
    Vec3 w;
    Vec3 *v1c8;
    Vec3 *pos;
    int h;
    int t;
    unsigned char *pb;
    Vec3 *o;
    int c;
    int s;

    s = scale;
    v1c8 = (Vec3 *) (self + 0x1c8);
    v1d4 = (Vec3 *) (self + 0x1d4);
    pos = (Vec3 *) (self + 0x204);
    hit = func_ov003_02235b54(self, 0x50, 0xe38);
    k = self[0x24b];
    r = func_020644cc(100);
    if (hit != 0) {
        *(short *) (self + 0x23a) = func_ov003_0223418c(*(short *) (self + 0x23a), hit);
        v1c8->x = pos->x;
        v1c8->y = pos->y;
        v1c8->z = pos->z;
        h = *(short *) (self + 0x23a);
        func_ov003_02235834(self, h, func_ov003_022350cc(self));
        return;
    }
    if (self[0x24f] % div == 0) {
        if (r > thresh) {
            self[0x24b] = (k == 0) ? 1 : 0;
        }
    }
    if (r > self[0x252]) {
        if (k != 0) {
            *p = (short) (*p + step);
            *(short *) (self + 0x23a) = *p;
        } else {
            *p = (short) (*p - step);
            *(short *) (self + 0x23a) = *p;
        }
    }
    func_ov003_0223597c(&d, *p);
    if (self[0x24a] != 0) {
        t = _ffix(0x45a00400);
        pos->x = pos->x + FX_MulFunc(FX_MulFunc(s, d.x), t);
        pos->z = pos->z + FX_MulFunc(FX_MulFunc(s, d.z), t);
    } else {
        pos->x = pos->x + FX_MulFunc(s, d.x);
        pos->z = pos->z + FX_MulFunc(s, d.z);
    }
    func_020eaca0(&w, v1c8, pos);
    c = func_020ea9c8(&w) > func_ov003_02235130(self);
    if (c) {
        func_ov003_022351c4(self, v1c8, 0xaaa);
    }
    if (func_020e908c(v1c8, v1d4, 0x28, func_ov003_0223506c(self) + 0x19a, func_ov003_0223506c(self)) != 0) {
        return;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
        return;
    }
    pb = &self[0x253];
    if (*pb == 0) {
        h = *(short *) (self + 0x23a);
        *(short *) (self + 0x23a) = (short) (h + func_ov003_02233c70(6, 1));
        v1c8->x = pos->x;
        v1c8->y = pos->y;
        v1c8->z = pos->z;
        if (self[0x24a] != 0) {
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
                o = func_ov003_022356ec(pos);
            } else {
                o = (Vec3 *) func_020961a8(4);
            }
            if (o != 0) {
                *(short *) (self + 0x23a) = func_0200322c((Vec3 *) ((char *) o + 0x5c), pos);
            }
        }
        h = *(short *) (self + 0x23a);
        func_ov003_02235834(self, h, func_ov003_022350cc(self));
    } else {
        *pb = (unsigned char) (*pb - 1);
    }
}
