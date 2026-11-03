/* tile_event: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02220e20 @ 0x02220e20, 0x120 bytes, Thumb
 * func_ov003_02220db4 @ 0x02220db4, 0x6c bytes, Thumb
 * func_ov003_02220d50 @ 0x02220d50, 0x64 bytes, Thumb
 * func_ov003_02220c8c @ 0x02220c8c, 0xc4 bytes, Thumb
 * func_ov003_02220bf0 @ 0x02220bf0, 0x9c bytes, Thumb
 * func_ov003_02220bb0 @ 0x02220bb0, 0x40 bytes, Thumb
 * func_ov003_02220b44 @ 0x02220b44, 0x6c bytes, Thumb
 */

typedef struct {
    int x, y;
} UnkStruct_02220e20;

typedef struct {
    int x, y, z;
} UnkStruct_02220e20_2;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02220d50;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int a, b;
} Pair;

typedef struct {
    char pad_00[0x5c];
    Vec3 unk_5C;
} Src;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02220c8c;

extern int func_ov003_022213f8(int *data, int a1, int *pair, int *dest, int a5, int a6, int a7, int a8);
extern int data_ov003_0223cfe4[];
extern void *func_0204e414(void);
extern void func_0204f818(int *x, int *y, int z);
extern int func_0204eda8(void *p, int x, int y);
extern int func_ov003_0222139c(void *data, int a, int *pair, int *arr, int b, int c, int d, int e);
extern void func_0204f794(int *out, int a, int b);
extern void *func_020961a8(int arg);
extern int func_020644e4(int value);
extern int func_02073d90(void *g);
extern UnkStruct_02220c8c *data_020ccf94;
extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_02045cec(int *, int);
extern int func_0204ee7c(int, int, int);
extern unsigned char data_ov003_02236670[];

void func_ov003_02220e20(int a0, int id, UnkStruct_02220e20 *p2, UnkStruct_02220e20_2 *p3)
{
    volatile unsigned short t = 0xfff1;
    unsigned int h, g, f, e, d, c, b, a;
    unsigned short lo, hi;
    int pair[2];
    int dest[3];

    t = (unsigned short) id;
    h = 1;
    g = 1;
    f = 1;
    e = 1;
    d = 1;
    c = 1;
    b = 1;
    a = 0;
    lo = t;
    hi = t;
    if (hi <= 5) {
        a = 1;
    }
    if (a == 0) {
        if (!(lo >= 6 && lo <= 0xb)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(lo >= 0xc && lo <= 0x11)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
            d = 0;
        }
    }
    if (d == 0) {
        if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
              (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
            e = 0;
        }
    }
    if (e == 0) {
        if (lo != 0x1a) {
            f = 0;
        }
    }
    if (f == 0) {
        if (lo != 0xa4) {
            g = 0;
        }
    }
    if (g == 0) {
        if (lo != 0x1d) {
            h = 0;
        }
    }
    if (h != 0 || (lo >= 0x14fe && lo <= 0x1517) || id == 0x1567) {
        id = 0x1408;
    }

    dest[0] = p3->x;
    dest[1] = p3->y;
    dest[2] = p3->z;
    pair[0] = p2->x;
    pair[1] = p2->y;
    func_ov003_022213f8(data_ov003_0223cfe4, a0, pair, dest, 9, id, 0, 0);
}

int func_ov003_02220db4(int p1, int p2)
{
    void *p;
    int L0, L1;
    int pair[2];
    int arr[3];
    int err;

    p = func_0204e414();
    if (p == 0) {
        return 0;
    }

    L0 = 0;
    L1 = 0;
    func_0204f818(&L0, &L1, p2);
    err = (func_0204eda8(p, L0, L1) == 0) ? 0xfc : 0xfd;

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    pair[0] = L0;
    pair[1] = L1;

    return func_ov003_0222139c(((char *) data_ov003_0223cfe4), p1, pair, arr, 0xa, err, 0, 0);
}

void func_ov003_02220d50(int a1, int a2, UnkStruct_02220d50 *s)
{
    int val = 0;
    int pair[2];
    int buffer[3];
    int dest[3];
    void *ptr;

    func_0204f794(buffer, s->unk_00, s->unk_04);

    ptr = func_020961a8(4);
    if (ptr) {
        val = (func_020644e4(*(short *) ((char *) ptr + 0x8e)) << 29) >> 16;
    }

    dest[0] = buffer[0];
    dest[1] = buffer[1];
    dest[2] = buffer[2];

    pair[0] = s->unk_00;
    pair[1] = s->unk_04;

    func_ov003_022213f8(data_ov003_0223cfe4, a1, pair, dest, 11, a2, val, 0);
}

int func_ov003_02220c8c(int a0, int a1)
{
    int a, b;
    Pair pp;
    Vec3 v20;
    int out2[3];
    Vec3 vv;
    Src *p;
    Vec3 *sv;
    UnkStruct_02220c8c *g;
    int k, x, t;

    v20.x = 0;
    v20.y = 0;
    v20.z = 0;
    a = 0;
    b = 0;
    p = (Src *) func_020961a8(4);
    if (p != 0) {
        sv = &p->unk_5C;
        t = p->unk_5C.x;
        v20.x = t;
        v20.y = sv->y;
        v20.z = sv->z;
        v20.x = t + ((a1 << 12) >> 4);
        func_0204f818(&a, &b, (int) (&v20));
        b = (b / 16) * 16 + 1;
        func_0204f794(out2, a, b);
        v20.z = out2[2];
    }
    v20.y = 0xa000;
    if (a0 == 0) {
        k = 0x156b;
    } else {
        k = 0x137b;
    }
    g = data_020ccf94;
    if (func_02073d90(g) != 0) {
        x = g->unk_64;
    } else {
        x = 0;
    }
    vv.x = v20.x;
    vv.y = v20.y;
    vv.z = v20.z;
    pp.a = a;
    pp.b = b;
    return func_ov003_022213f8((int *) (((int *) data_ov003_0223cfe4)), x, (int *) (&pp), (int *) (&vv), 0xc, k, 0, 0);
}

int func_ov003_02220bf0(int *pos)
{
    int result;
    int a;
    int d;
    int c;
    int temp[2];
    int i;

    a = (int) func_0204e414();
    result = 2;
    if (a == 0) {
        return result;
    }

    c = 0;
    d = 0;

    for (i = 0; i < 9; i++) {
        unsigned char byte = data_ov003_02236670[i];
        int x = pos[0] + (((int) byte >> 4) - 8);
        int y = pos[1] + (((int) byte & 0xf) - 8);
        int xq = x >> 4;
        int yq = y >> 4;
        int xm = x - (xq << 4);
        int ym = y - (yq << 4);
        unsigned short *p = (unsigned short *) func_0204f5e0(a, xq, yq, xm, ym, d);
        if (p != 0 && *p == 0xfff1) {
            temp[0] = x;
            temp[1] = y;
            if (func_02045cec(temp, c) < 0) {
                if (func_0204ee7c(a, x, y) != 0) {
                    pos[0] = x;
                    pos[1] = y;
                    result = 0;
                }
                break;
            }
        }
    }

    return result;
}

void func_ov003_02220bb0(int p0, int p1, int *p2, int *p3)
{
    int local3[3];
    int local2[2];
    local3[0] = p3[0];
    local3[1] = p3[1];
    local3[2] = p3[2];
    local2[0] = p2[0];
    local2[1] = p2[1];
    func_ov003_022213f8(((int *) data_ov003_0223cfe4), p0, local2, local3, 13, p1, 0, 0);
}

int func_ov003_02220b44(int param0, int param1)
{
    void *handle;
    int a, b;
    int pair[2];
    int zeros[3];
    int flag;

    handle = func_0204e414();
    if (handle == 0) {
        return 0;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, param1);
    flag = (func_0204eda8(handle, a, b) == 0) ? 0xfc : 0xfd;

    zeros[0] = 0;
    zeros[1] = 0;
    zeros[2] = 0;
    pair[0] = a;
    pair[1] = b;

    return func_ov003_0222139c((void *) ((unsigned char *) data_ov003_0223cfe4), param0, pair, zeros, 14, flag, 0, 0);
}
