/* room_cells_2: 25 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02053370 @ 0x02053370, 0x10 bytes, Thumb
 * func_0205336c @ 0x0205336c, 0x2 bytes, Thumb
 * func_02053358 @ 0x02053358, 0x14 bytes, Thumb
 * func_02053340 @ 0x02053340, 0x18 bytes, Thumb
 * func_02053314 @ 0x02053314, 0x2c bytes, Thumb
 * func_02053304 @ 0x02053304, 0x10 bytes, Thumb
 * func_02053300 @ 0x02053300, 0x2 bytes, Thumb
 * func_020532d0 @ 0x020532d0, 0x30 bytes, Thumb
 * func_02053278 @ 0x02053278, 0x56 bytes, Thumb
 * func_020531fc @ 0x020531fc, 0x7c bytes, Thumb
 * func_02053108 @ 0x02053108, 0xf4 bytes, Thumb
 * func_020530d4 @ 0x020530d4, 0x34 bytes, Thumb
 * func_020530b0 @ 0x020530b0, 0x24 bytes, Thumb
 * func_02053088 @ 0x02053088, 0x26 bytes, Thumb
 * func_0205307c @ 0x0205307c, 0xc bytes, Thumb
 * func_02053060 @ 0x02053060, 0x1c bytes, Thumb
 * func_02053050 @ 0x02053050, 0x10 bytes, Thumb
 * func_02053010 @ 0x02053010, 0x40 bytes, Thumb
 * func_02052ff4 @ 0x02052ff4, 0x1c bytes, Thumb
 * func_02052fdc @ 0x02052fdc, 0x18 bytes, Thumb
 * func_02052fd0 @ 0x02052fd0, 0xc bytes, Thumb
 * func_02052fc0 @ 0x02052fc0, 0x10 bytes, Thumb
 * func_02052fb4 @ 0x02052fb4, 0xc bytes, Thumb
 * func_02052f3c @ 0x02052f3c, 0x78 bytes, Thumb
 * func_02052f14 @ 0x02052f14, 0x26 bytes, Thumb
 */

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_02053278;

typedef struct {
    UnkStruct_02053278 e[4];
    unsigned char mask[1];
    unsigned char val[2];
} UnkStruct_02053278_2;

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} Nib;

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_02053108;

typedef struct {
    UnkStruct_02053108 e[4];
    unsigned char mask[1];
    unsigned char val[2];
} UnkStruct_02053108_2;

typedef struct {
    char data[0x48];
} Struct0x48;

typedef struct {
    char data[0x48];
} UnkStruct_02052f3c;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern char data_021c87b4[];
extern Struct0x48 data_021c89fc[];
extern Struct0x48 data_021c884c[];
extern unsigned char data_020d20cc;
extern int func_020b67e8(int);
extern int func_020b6818(int);
extern int func_02060ee0(int, int);
extern int func_02061220(int);
extern int func_020b6694(int);
extern int func_020b66c4(int);
extern int func_020b6744(int);
extern int func_020b6774(int);
extern unsigned char data_021ebcd4[];

void func_02053358(unsigned short *p);
void func_020532d0(unsigned char *p);
void func_02053088(void *p);
int func_02052f3c(int param);

int func_02053370(int arg)
{
    func_02053358((unsigned short *) arg);
    return arg;
}

void func_0205336c(void *object) {}

void func_02053358(unsigned short *p)
{
    unsigned int i;
    for (i = 0; i < 16; i++) {
        p[i] = 0xffff;
    }
}

int func_02053340(unsigned short *arr, int bit, int index)
{
    int idx = index & 0xF;
    int val = arr[idx];
    int shift = bit & 0xF;
    if ((val >> shift) & 1) {
        return 1;
    } else {
        return 0;
    }
}

void func_02053314(unsigned short *arr, int bit, int idx, int flag)
{
    int b = bit & 0xF;
    int i = idx & 0xF;
    if (flag) {
        arr[i] |= (1 << b);
    } else {
        arr[i] &= ~(1 << b);
    }
}

int func_02053304(int param)
{
    func_020532d0((unsigned char *) param);
    return param;
}

void func_02053300(void *object) {}

void func_020532d0(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 4; i++) {
        p[i] &= ~0xF;
        p[i] &= ~0xF0;
    }
    p[4] = 0;
    for (i = 0; i < 2; i++) {
        (p + i)[5] = 0;
    }
}

int func_02053278(UnkStruct_02053278_2 *t, int a, int b)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if ((((int) t->mask[i >> 3] >> (i & 7)) & 1) != 0) {
            if (a == t->e[i].lo && b == t->e[i].hi) {
                return ((int) t->val[i >> 1] >> ((i & 1) * 4)) & 0xf;
            }
        }
    }
    return -1;
}

int func_020531fc(unsigned char *p, int a, int b)
{
    unsigned int i;
    Nib *n;
    unsigned char *used;
    unsigned char *nib;

    for (i = 0; i < 4; i++) {
        if (((*(p + (i >> 3) + 4) >> (i & 7)) & 1) != 0) {
            n = (Nib *) (p + i);
            if (a == n->lo) {
                if (b == n->hi) {
                    n->lo = 0;
                    n->hi = 0;
                    used = p + 4;
                    used[i >> 3] &= ~(1 << (i & 7));
                    nib = p + 5;
                    nib[i >> 1] &= ~(0xf << ((i & 1) << 2));
                    return 1;
                }
            }
        }
    }
    return 0;
}

int func_02053108(UnkStruct_02053108_2 *t, int a, int b, unsigned int value)
{
    unsigned int i;

    if (value >= 16) {
        return 0;
    }

    if (func_02053278((UnkStruct_02053278_2 *) t, a, b) == -1) {
        for (i = 0; i < 4; i++) {
            if ((((int) t->mask[i >> 3] >> (i & 7)) & 1) == 0) {
                int shift = (i & 1) << 2;
                unsigned int shv;
                t->e[i].lo = a;
                t->e[i].hi = b;
                t->val[i >> 1] &= ~(0x0f << shift);
                shv = value << shift;
                value = shv;
                t->val[i >> 1] |= shv;
                t->mask[i >> 3] |= (1 << (i & 7));
                return 1;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if ((((int) t->mask[i >> 3] >> (i & 7)) & 1) != 0) {
                if (a == t->e[i].lo && b == t->e[i].hi) {
                    int shift = (i & 1) << 2;
                    unsigned int shv;
                    t->val[i >> 1] &= ~(0x0f << shift);
                    shv = value << shift;
                    value = shv;
                    t->val[i >> 1] |= shv;
                    return 1;
                }
            }
        }
    }
    return 0;
}

char *func_020530d4(char *arg)
{
    __cxa_vec_ctor((void *) (arg), 2, 32, (((void (*)(void *))(int (*)(void *)) func_02053370)),
                   (void (*)(void *)) func_0205336c);
    func_02053304((int) (arg + 0x40));
    func_02053088(arg);
    return arg;
}

void *func_020530b0(void *param)
{
    func_02053300((char *) param + 0x40);
    __cxa_vec_cleanup((void *) (param), 2, 0x20, (void (*)(void *)) func_0205336c);
    return param;
}

void func_02053088(void *p)
{
    unsigned int i;

    i = 0;
    do {
        func_02053358((unsigned short *) ((char *) p + (i << 5)));
        i++;
    } while (i < 2);
    func_020532d0((unsigned char *) ((char *) p + 0x40));
}

int func_0205307c(void *a, int b, int c, int d)
{
    return func_02053340((unsigned short *) ((char *) a + (d << 5)), b, c);
}

void func_02053060(int a, int b, int c, int d, unsigned char e)
{
    func_02053314((unsigned short *) (a + (d << 5)), b, c, e);
}

void func_02053050(void)
{
    func_02053088(data_021c87b4);
}

void func_02053010(void)
{
    unsigned i;

    for (i = 0; i < 8; i++) {
        func_02053088((void *) (&data_021c89fc[i]));
    }

    for (i = 0; i < 6; i++) {
        func_02053088((void *) (&data_021c884c[i]));
    }

    func_02053050();
}

int func_02052ff4(int argument0)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (func_02052f3c((int) argument0))) != 0) {
        func_02053088(condition_value0);
        return 1;
    }
    return 0;
}

int func_02052fdc(unsigned char arg)
{
    return func_02052ff4((unsigned char) (data_020d20cc + arg));
}

int func_02052fd0(int arg, int argument1, int argument2)
{
    return func_02053278((UnkStruct_02053278_2 *) (arg + 0x40), (int) argument1, (int) argument2);
}

int func_02052fc0(unsigned char *p, int b, int c, int d)
{
    return func_02053108((UnkStruct_02053108_2 *) (p + 0x40), b, c, d);
}

int func_02052fb4(int a, int argument1, int argument2)
{
    return func_020531fc((unsigned char *) (a + 0x40), (int) argument1, (int) argument2);
}

int func_02052f3c(int param)
{
    if (func_020b67e8(param)) {
        int a = func_02060ee0((unsigned int) data_021ebcd4, func_020b6818(param));
        if (a) {
            return func_02061220(a);
        }
    } else {
        if (func_020b6694(param)) {
            return (int) &((UnkStruct_02052f3c *) data_021c89fc)[func_020b66c4(param)];
        } else {
            if (func_020b6744(param)) {
                return (int) &((UnkStruct_02052f3c *) data_021c884c)[func_020b6774(param)];
            } else {
                if (param == 10) {
                    return (int) ((UnkStruct_02052f3c *) data_021c87b4);
                }
            }
        }
    }
    return 0;
}

int func_02052f14(int a, int b, int c, int d)
{
    int result;
    result = func_02052f3c(d);
    if (result) {
        return func_0205307c((void *) result, a, b, c);
    } else {
        return 0;
    }
}
