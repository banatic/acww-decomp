/* tile_effects: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02044a14 @ 0x02044a14, 0x1a bytes, Thumb
 * func_020449d4 @ 0x020449d4, 0x40 bytes, Thumb
 * func_020449ac @ 0x020449ac, 0x28 bytes, Thumb
 * func_02044958 @ 0x02044958, 0x54 bytes, Thumb
 * func_02044910 @ 0x02044910, 0x48 bytes, Thumb
 * func_020448b8 @ 0x020448b8, 0x56 bytes, Thumb
 * func_0204489c @ 0x0204489c, 0x1a bytes, Thumb
 */

struct TwoInts {
    int first;
    int second;
};

typedef struct {
    int a;
    int b;
} SELF;

extern void func_02044a30(void *a, void *b, int c, int d);
extern void func_0204f794(void *dst, int a, int b);
extern int func_02090c2c(int id, void *buf, int c, void *d);
extern unsigned char data_020e25d4[];
extern int func_0204b3d0(int);
extern int func_020b65c4(void);
extern void func_0205f9d4(int, int, int, int, int);
extern int func_0204e414(void);
extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_020644cc(int size);

void func_02044a14(unsigned int *p0, unsigned int *p1, int a2, int a3)
{
    unsigned int local[2];
    local[0] = p1[0];
    local[1] = p1[1];
    func_02044a30(p0, local, a2, a3);
}

void func_020449d4(unsigned short *kind, int *data)
{
    int id;
    char buf[16];

    switch (*kind) {
        case 0x1f:
            id = 0x77;
            break;
        case 0x20:
            id = 0x78;
            break;
        default:
            id = 0x76;
            break;
    }

    func_0204f794(buf, data[0], data[1]);
    func_02090c2c(id, buf, 0, ((int *) data_020e25d4));
}

void func_020449ac(unsigned int *src)
{
    unsigned int a, b;
    unsigned int local[3];

    a = src[0];
    b = src[1];
    func_0204f794(local, a, b);
    func_02090c2c(0x94, local, 0, (void *) data_020e25d4);
}

void func_02044958(int a, struct TwoInts *b, int c)
{
    if (func_0204b3d0(a)) {
        struct TwoInts L;
        L.first = b->first;
        L.second = b->second;
        func_02044a30((void *) a, &L, 0, c);
        if (c == 0) {
            func_0205f9d4((signed char) b->first, (signed char) b->second, func_020b65c4(), 0xfff1, 0);
        }
    }
}

void func_02044910(int *a, int b)
{
    int c = func_0204e414();

    if (c != 0) {
        int a0 = a[0];
        int a1 = a[1];
        int hx = a0 >> 4;
        int hy = a1 >> 4;
        int low1 = a1 - (hy << 4);
        int low0 = a0 - (hx << 4);
        int res = func_0204f5e0(c, hx, hy, low0, low1, 0);

        if (res != 0) {
            int arr[2];

            arr[0] = a[0];
            arr[1] = a[1];
            func_02044958(res, (struct TwoInts *) arr, b);
        }
    }
}

void func_020448b8(SELF *self)
{
    int result1;
    int result2;
    int flag;
    int vals[2];
    int a;
    int b;
    int ash;
    int bsh;

    result1 = func_0204e414();
    if (result1 == 0) {
        return;
    }

    a = self->a;
    b = self->b;
    ash = a >> 4;
    bsh = b >> 4;
    result2 = func_0204f5e0(result1, ash, bsh, a - (ash << 4), b - (bsh << 4), 0);
    if (result2 == 0) {
        return;
    }

    flag = (func_020644cc(0x50) < 0x46) ? 1 : 0;
    vals[0] = self->a;
    vals[1] = self->b;
    func_02044958(result2, (struct TwoInts *) vals, flag);
}

void func_0204489c(unsigned int *param0)
{
    unsigned int local[3];
    local[0] = param0[0];
    local[1] = param0[1];
    func_02044910((int *) local, 1);
}
