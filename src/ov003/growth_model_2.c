/* growth_model_2: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02223b18 @ 0x02223b18, 0x1a bytes, Thumb
 * func_ov003_02223a90 @ 0x02223a90, 0x88 bytes, Thumb
 * func_ov003_02223a04 @ 0x02223a04, 0x8c bytes, Thumb
 * func_ov003_0222399c @ 0x0222399c, 0x68 bytes, Thumb
 * func_ov003_02223928 @ 0x02223928, 0x74 bytes, Thumb
 * func_ov003_02223870 @ 0x02223870, 0xb8 bytes, Thumb
 * func_ov003_0222378c @ 0x0222378c, 0xe4 bytes, Thumb
 */

typedef struct {
    int x, y;
} XY;

typedef struct {
    int unk_00;
    int unk_04;
    XY xy;
    int unk_10;
    int unk_14;
} UnkStruct_0222378c;

typedef struct {
    int unk_00;
    char pad_04[0xd4 - 4];
    int unk_D4;
} UnkStruct_0222378c_2;

extern void func_020f5948(void *p);
extern void *func_020551e0(void *p);
extern void func_ov003_02222bc0(void *);
extern void func_ov003_02223580(void *);
extern void func_ov003_02223274(void *);
extern void func_ov003_02223208(char *p);
extern void func_ov003_02222b78(char *p);
extern void func_ov003_022231e8(char *p);
extern int func_0204e414(void);
extern int func_ov003_02222af0(UnkStruct_0222378c *b);
extern void *func_0204f5e0(int h, int a, int c, int d, int e, int f);
extern int func_0204b7a0(void *h);
extern void func_ov003_02222cac(UnkStruct_0222378c_2 *q, int a, int *pair, int c, int d, int e);

void func_ov003_0222378c(void *a, UnkStruct_0222378c *b);

void *func_ov003_02223b18(void *p)
{
    func_020f5948((char *) p + 0xe0);
    func_020551e0((char *) p + 8);
    return p;
}

void func_ov003_02223a90(void *p)
{
    int i, j, off;
    char *base;

    func_ov003_02222bc0((char *) p + 0x1e4c);

    for (i = 0; i < 5; i++) {
        *((int *) ((char *) p + i * 0x18 + 0x1dd4)) = 0;
    }

    for (i = 0; i < 3; i++) {
        j = 0;
        base = (char *) p + i * 0x530;
        do {
            func_ov003_02223580(base + j * 0x14c);
            j++;
        } while (j < 4);
    }

    for (i = 0; i < 4; i++) {
        off = i * 0x14c;
        func_ov003_02223580((char *) p + 0xf90 + off);
        func_ov003_02223580((char *) p + 0x18a4 + off);
    }
}

void func_ov003_02223a04(void *p)
{
    int i, j, off;
    char *base;
    int *q;

    for (i = 0; i < 5; i++) {
        q = (int *) ((char *) p + i * 0x18 + 0x1dd4);
        if (*q != 0) {
            func_ov003_0222378c(p, (UnkStruct_0222378c *) q);
        }
    }

    for (i = 0; i < 3; i++) {
        j = 0;
        base = (char *) p + i * 0x530;
        do {
            func_ov003_02223274(base + j * 0x14c);
            j++;
        } while (j < 4);
    }

    for (i = 0; i < 4; i++) {
        off = i * 0x14c;
        func_ov003_02223274((char *) p + 0xf90 + off);
        func_ov003_02223274((char *) p + 0x18a4 + off);
    }
}

void func_ov003_0222399c(char *base)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            func_ov003_02223208(base + i * 0x530 + j * 0x14c);
        }
    }

    for (i = 0; i < 4; i++) {
        func_ov003_02223208(base + 0xf90 + i * 0x14c);
        func_ov003_02223208(base + 0x18a4 + i * 0x14c);
    }
}

void func_ov003_02223928(char *base)
{
    int i, j;
    func_ov003_02222b78(base + 0x1e4c);
    i = 0;
    do {
        j = 0;
        do {
            func_ov003_022231e8(base + i * 0x530 + j * 0x14c);
            j++;
        } while (j < 4);
        i++;
    } while (i < 3);
    i = 0;
    do {
        func_ov003_022231e8(base + 0xf90 + i * 0x14c);
        func_ov003_022231e8(base + 0x18a4 + i * 0x14c);
        i++;
    } while (i < 4);
}

extern void *func_ov003_02223870(void *base, unsigned short *key, int idx, int idx2)
{
    int first;
    unsigned short c;

    first = 0;
    c = *key;
    if (c >= 0x2f && c <= 0x56) {
        first = 1;
    }
    if (first) {
        return (char *) base + 0xa60 + idx * 0x14c;
    } else if (c >= 0x57 && c <= 0x5b) {
        return (char *) base + idx2 * 0x530 + idx * 0x14c;
    } else if (c == 0x69) {
        return (char *) base + 0xa60 + idx * 0x14c;
    } else if (c >= 0x6a && c <= 0x6c) {
        return (char *) base + 0xf90 + idx * 0x14c;
    } else if (c == 0x6d) {
        return (char *) base + 0xf90 + idx * 0x14c;
    } else if (c >= 0x5d && c <= 0x61) {
        return (char *) base + 0xf90 + idx * 0x14c;
    } else if (c >= 0xc8 && c <= 0xcf) {
        return (char *) base + 0x18a4 + idx * 0x14c;
    } else {
        return (char *) base + idx2 * 0x530 + idx * 0x14c;
    }
}

void func_ov003_0222378c(void *a, UnkStruct_0222378c *b)
{
    int pair[2];
    void *h;
    UnkStruct_0222378c_2 *q;
    int n;
    int w;
    int x, y, xh, yh;
    int x2, y2, f10;
    int f14;
    int r;
    XY *p;

    r = func_0204e414();
    if (r == 0) {
        func_ov003_02222af0(b);
        return;
    }
    p = &b->xy;
    x = p->x;
    y = p->y;
    xh = x >> 4;
    yh = y >> 4;
    h = func_0204f5e0(r, xh, yh, x - (xh << 4), y - (yh << 4), 0);
    if (h == 0) {
        func_ov003_02222af0(b);
        return;
    }
    p = &b->xy;
    x2 = p->x;
    y2 = p->y;
    f10 = b->unk_10;
    n = func_0204b7a0(h);
    if (n <= 0 || n > 4) {
        func_ov003_02222af0(b);
        return;
    }
    {
        q = (UnkStruct_0222378c_2 *) func_ov003_02223870(a, (unsigned short *) h, n - 1, (x2 ^ y2) & 1);
        if (q == 0) {
            func_ov003_02222af0(b);
            return;
        }
        if (q->unk_00 == 1) {
            switch (q->unk_D4) {
                case 4:
                case 5:
                case 6:
                case 7:
                    func_ov003_02222af0(b);
                    return;
            }
        }
        f14 = b->unk_14;
        pair[0] = x2;
        pair[1] = y2;
        func_ov003_02222cac(q, b->unk_04, pair, f10, n - 1, f14);
        b->unk_00 = 0;
    }
}
