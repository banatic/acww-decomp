/* aquarium_swim: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022394ac @ 0x022394ac, 0x16 bytes, Thumb
 * func_ov004_02239474 @ 0x02239474, 0x38 bytes, Thumb
 * func_ov004_02239460 @ 0x02239460, 0x12 bytes, Thumb
 * func_ov004_02239424 @ 0x02239424, 0x3c bytes, Thumb
 * func_ov004_0223938c @ 0x0223938c, 0x98 bytes, Thumb
 * func_ov004_02239354 @ 0x02239354, 0x38 bytes, Thumb
 * func_ov004_022392a0 @ 0x022392a0, 0xb4 bytes, Thumb
 */

struct UnkStruct_0223938c {
    int x, y, z;
};

typedef struct {
    unsigned char b[0x40];
} UnkStruct_02239354;

extern int func_020e92e8(void *p);
extern int data_021cb5a0;
extern int func_020644cc(int n);
extern int func_020ea9e4(int, int);
extern int func_0200322c(int, int);
extern int func_020e89dc(void *, int, int);
extern int _s32_div_f(int a, int b);
extern int func_02034270(UnkStruct_02239354 *, void *, int, int);
extern int func_020341c8(UnkStruct_02239354 *, int);
extern void func_0203423c(UnkStruct_02239354 *);
extern const unsigned char data_ov004_02247927[];
extern char data_ov004_022593dc[];
extern char data_ov004_022593c4[];
extern int func_ov004_02239bb4(int *a, int b, int c);
extern int func_02031168(int *a, int lim, void *tbl, int m, int q);

char *func_ov004_02239460(char *a, char *b);
int func_ov004_02239354(void *a);

int func_ov004_022394ac(char *a, char *b)
{
    int n = (int) func_ov004_02239460(a, b);
    if (n == 0) {
        n = 1;
    }
    return n << 12;
}

short func_ov004_02239474(void *a, void *b)
{
    int s;
    if (func_020e92e8(&data_021cb5a0) > 0) {
        s = 1;
    } else {
        s = -1;
    }
    return (short) (0xb6 * ((int) func_ov004_02239460((char *) b, (char *) a) * (signed char) s));
}

char *func_ov004_02239460(char *a, char *b)
{
    return a + func_020644cc(b - a);
}

int func_ov004_02239424(void *a0, int a1, int a2, int a3)
{
    int r = 1;
    if (func_020ea9e4(a1, a2) > a3) {
        func_020e89dc(a0, func_0200322c(a1, a2), 0x38e);
        r = 0;
    }
    return r;
}

int func_ov004_0223938c(struct UnkStruct_0223938c *self, int d)
{
    int found;
    int sx;
    int sz;
    int i;
    int b;
    int a;
    int c;
    int e;
    struct UnkStruct_0223938c t;

    found = 0;
    sx = 2;
    sz = 2;
    if (d < 0) {
        sx = sx * ~found;
    }
    if (d < 0) {
        d = -d;
    }
    if (d > 0x4000) {
        sz = sz * ~found;
    }
    for (i = 0; i < 0x32; i++) {
        a = self->z;
        b = self->y;
        t.x = self->x + _s32_div_f((sx * i) << 12, 0xa);
        t.y = b;
        t.z = a;
        if (func_ov004_02239354((void *) (&t)) == 0) {
            found = 1;
            break;
        }
        c = self->z + _s32_div_f((sz * i) << 12, 0xa);
        e = self->y;
        t.x = self->x;
        t.y = e;
        t.z = c;
        if (func_ov004_02239354((void *) (&t)) == 0) {
            break;
        }
    }
    return found;
}

int func_ov004_02239354(void *a)
{
    UnkStruct_02239354 s;
    int r = 0;
    func_02034270(&s, a, r, r);
    if (func_020341c8(&s, r) == 0x800) {
        r = 1;
    }
    func_0203423c(&s);
    return r;
}

int func_ov004_022392a0(void *self)
{
    int a[3];
    int ok = 0;
    int lim;
    int v;

    a[0] = *(int *) ((char *) self + 0x1a8);
    a[1] = *(int *) ((char *) self + 0x1ac);
    a[2] = *(int *) ((char *) self + 0x1b0);
    func_ov004_02239bb4(a, ((int) data_ov004_02247927[*(int *) ((char *) self + 0x15c) * 0x11] << 12) >> 7,
                        *(short *) ((char *) self + 0x1c0));
    lim = 0x400;
    if (*((unsigned char *) self + 0x1fc) != 0) {
        lim = 0x1000;
    }
    v = *(int *) ((char *) self + 0x15c);
    if (v == 0x19 || v < 0x11) {
        if (func_02031168(a, lim, data_ov004_022593dc, 0xfc00, 0x3c00) != 0) {
            ok = 1;
        }
    } else {
        if (func_02031168(a, lim, data_ov004_022593c4, 0xfc00, 0x3c00) != 0) {
            ok = 1;
        }
    }
    return ok;
}
