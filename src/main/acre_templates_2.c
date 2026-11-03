/* acre_templates_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204d934 @ 0x0204d934, 0x2c bytes, Thumb
 * func_0204d924 @ 0x0204d924, 0x10 bytes, Thumb
 * func_0204d8e4 @ 0x0204d8e4, 0x3e bytes, Thumb
 * func_0204d8b0 @ 0x0204d8b0, 0x32 bytes, Thumb
 * func_0204d888 @ 0x0204d888, 0x28 bytes, Thumb
 * func_0204d858 @ 0x0204d858, 0x30 bytes, Thumb
 * func_0204d828 @ 0x0204d828, 0x30 bytes, Thumb
 * func_0204d7f8 @ 0x0204d7f8, 0x30 bytes, Thumb
 * func_0204d7a8 @ 0x0204d7a8, 0x50 bytes, Thumb
 * func_0204d708 @ 0x0204d708, 0x9e bytes, Thumb
 */

struct Entry {
    unsigned short *ptr;
    int count;
};

typedef struct {
    int a;
    int b;
} Pair;

extern void func_020e993c(int a, int b);
extern void *data_021c80c8;
extern unsigned short *func_020e9968(int, unsigned int, int);
extern Pair data_020cb764[];
extern void func_02064828(int, int, int, int);
extern void *func_020e9958(void *, int);

int func_0204d708(int a0, int a1, int a2, int a3, void *a4);

void func_0204d934(int *p, int arg)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (*p != 0) {
            func_020e993c(arg, *p);
            *p = 0;
            *(p + 1) = 0;
            p += 2;
        }
    }
}

int func_0204d924(int r0, int r1)
{
    if (r1 >= 0 && r1 < 4) {
        return 1;
    }
    return 0;
}

int func_0204d8e4(int a, int b, int c)
{
    int r4 = 0;
    int r1;
    int r2;
    int r0;

    if (func_0204d924(a, b) != 0) {
        r1 = a + (b << 3);
        r2 = *(int *) r1;
        if (r2 != 0) {
            r0 = *(int *) (r1 + 4);
            if (c < r0) {
                r1 = 0;
                while (r1 < c) {
                    r4 += *(unsigned short *) r2;
                    r2 += 2;
                    r1++;
                }
            }
        }
    }
    return r4;
}

unsigned short func_0204d8b0(struct Entry *a, int b, int c)
{
    unsigned short result = 0;
    if (func_0204d924((int) a, b)) {
        struct Entry *e = &a[b];
        if (e->ptr != 0 && c < e->count) {
            result = e->ptr[c];
        }
    }
    return result;
}

int func_0204d888(int a, int b)
{
    int result = 0;
    if (data_021c80c8 != 0) {
        if ((int) func_0204d8b0((struct Entry *) data_021c80c8, a, b) > 0) {
            result = 1;
        }
    }
    return result;
}

unsigned short *func_0204d858(int heapID, int align)
{
    unsigned short *buf;
    int i;

    buf = func_020e9968(heapID, 0x200, align);
    if (buf) {
        for (i = 0; i < 0x100; i++) {
            buf[i] = 0xfff1;
        }
    }
    return buf;
}

int func_0204d828(int a, int b, int c, int d, int e)
{
    int t;
    Pair *p;
    t = func_0204d8e4(a, c, d);
    p = &data_020cb764[c];
    func_02064828(p->b, b, e, t);
    return 1;
}

int func_0204d7f8(int a, int b, int c, int d)
{
    int result = 0;

    if (data_021c80c8) {
        result = func_0204d708((int) data_021c80c8, a, b, c, (void *) d);
    }
    return result;
}

int func_0204d7a8(int p1, int p2, int p3, int p4)
{
    int result = 0;
    if ((*(int *) &data_021c80c8)) {
        result = (int) func_0204d858(p3, p4);
        if (result != 0) {
            if (func_0204d708((*(int *) &data_021c80c8), result, p1, p2, (void *) p3) == 0) {
                func_020e993c(p3, result);
                result = 0;
            }
        }
    }
    return result;
}

int func_0204d708(int a0, int a1, int a2, int a3, void *a4)
{
    int sp4 = a0;
    int r7 = a2;
    int r6 = a1;
    int sp8 = a3;
    int n = (int) func_0204d8b0((struct Entry *) sp4, r7, a3);
    int spc = 0;
    if (r6 != 0 && n > 0 && (n & 3) == 0) {
        if (func_0204d924(sp4, r7) != 0) {
            int sp10 = (int) func_020e9958(a4, n);
            void *p = (void *) sp10;
            if (p != 0) {
                if (func_0204d828(sp4, (int) p, r7, sp8, n) != 0) {
                    int r2 = n >> 2;
                    int r1 = 0;
                    int flag = 0;
                    int ok;
                    unsigned char b2, b3;
                    while (r1 < r2) {
                        b3 = ((unsigned char *) p)[3];
                        ok = flag;
                        b2 = ((unsigned char *) p)[2];
                        if (b2 < 0x10 && b3 < 0x10) {
                            ok = 1;
                        }
                        if (ok != 0) {
                            unsigned short v = *(unsigned short *) p;
                            int idx = ((b3 << 4) + b2) << 1;
                            *(unsigned short *) (r6 + idx) = v;
                        }
                        p = (char *) p + 4;
                        r1++;
                    }
                }
                func_020e993c((int) a4, (int) ((void *) sp10));
                spc = 1;
            }
        }
    }
    return spc;
}
