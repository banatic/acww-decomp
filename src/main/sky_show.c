/* sky_show: 27 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bcd7c @ 0x020bcd7c, 0x24 bytes, Thumb
 * func_020bcd30 @ 0x020bcd30, 0x4c bytes, Thumb
 * func_020bcce4 @ 0x020bcce4, 0x4c bytes, Thumb
 * func_020bcc70 @ 0x020bcc70, 0x74 bytes, Thumb
 * func_020bcb84 @ 0x020bcb84, 0xec bytes, Thumb
 * func_020bcab0 @ 0x020bcab0, 0xd4 bytes, Thumb
 * func_020bca80 @ 0x020bca80, 0x30 bytes, Thumb
 * func_020bc9c4 @ 0x020bc9c4, 0xbc bytes, Thumb
 * func_020bc98c @ 0x020bc98c, 0x38 bytes, Thumb
 * func_020bc954 @ 0x020bc954, 0x38 bytes, Thumb
 * func_020bc91c @ 0x020bc91c, 0x38 bytes, Thumb
 * func_020bc8e4 @ 0x020bc8e4, 0x38 bytes, Thumb
 * func_020bc8ac @ 0x020bc8ac, 0x38 bytes, Thumb
 * func_020bc870 @ 0x020bc870, 0x3c bytes, Thumb
 * func_020bc838 @ 0x020bc838, 0x38 bytes, Thumb
 * func_020bc800 @ 0x020bc800, 0x38 bytes, Thumb
 * func_020bc7c8 @ 0x020bc7c8, 0x38 bytes, Thumb
 * func_020bc790 @ 0x020bc790, 0x38 bytes, Thumb
 * func_020bc758 @ 0x020bc758, 0x38 bytes, Thumb
 * func_020bc720 @ 0x020bc720, 0x38 bytes, Thumb
 * func_020bc6f4 @ 0x020bc6f4, 0x2c bytes, Thumb
 * func_020bc6c0 @ 0x020bc6c0, 0x34 bytes, Thumb
 * func_020bc68c @ 0x020bc68c, 0x34 bytes, Thumb
 * func_020bc658 @ 0x020bc658, 0x34 bytes, Thumb
 * func_020bc624 @ 0x020bc624, 0x34 bytes, Thumb
 * func_020bc5f8 @ 0x020bc5f8, 0x2c bytes, Thumb
 * func_020bc5c4 @ 0x020bc5c4, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0x2f34];
    volatile int unk_2F34;
} UnkStruct_020bcd30;

typedef struct {
    char pad_00[0x2f38];
    int timers[4];
} UnkStruct_020bcc70;

typedef struct {
    unsigned char pad_00[0x2f38];
    int a;
    int b;
    int c;
    int d;
    int unk_2F48;
} UnkStruct_020bcb84;

typedef struct {
    unsigned char pad_00[0x2f38];
    int a;
    int b;
    int c;
    int d;
    int unk_2F48;
} UnkStruct_020bcab0;

typedef struct {
    unsigned char pad_00[0x2f30];
    int unk_2F30;
    unsigned char pad_2F34[0x2f48 - 0x2f30 - 4];
    int unk_2F48;
} UnkStruct_020bca80;

typedef struct {
    unsigned char pad_00[0x2f2c];
    unsigned int unk_2F2C;
    unsigned char pad_2F30[4];
    unsigned int unk_2F34;
    unsigned int unk_2F38;
    unsigned int unk_2F3C;
    unsigned int unk_2F40;
    unsigned int unk_2F44;
} UnkStruct_020bc9c4;

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc98c;

struct UnkStruct_020bc954 {
    char pad_00[0x2f30];
    int unk_2F30;
};

struct UnkStruct_020bc91c {
    char pad_00[0x2f30];
    int unk_2F30;
};

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc8e4;

typedef struct {
    char pad_00[0x2F30];
    int unk_2F30;
} UnkStruct_020bc8ac;

struct Struct020bc870 {
    char pad_00[0x2f30];
    int unk_2F30;
};

typedef struct {
    unsigned char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc838;

struct UnkStruct_020bc800 {
    char pad_00[0x2f30];
    int unk_2F30;
};

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} Struct020bc7c8;

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} Struct020bc720;

typedef struct UnkStruct_020bc6f4 {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc6f4;

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc6c0;

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc658;

struct Context {
    char pad_00[0x2f30];
    int unk_2F30;
};

extern int func_020644cc(int);
extern int func_020bce60(UnkStruct_020bcd30 *, int);
extern void func_020bcda0(UnkStruct_020bcd30 *, int, int, int);
extern int func_020bcdf8(void *obj, int i);
extern unsigned char data_020d2315[];
extern unsigned char data_020d2378[];

void func_020bcd7c(int *base, int *out)
{
    int val;
    val = base[0x2f48 / 4];
    if (val > 0) {
        val = func_020644cc(val);
    } else {
        val = 0;
    }
    *out = val + 0x41;
}

void func_020bcd30(UnkStruct_020bcd30 *obj)
{
    int v;
    obj->unk_2F34 = obj->unk_2F34 - 1;
    if (obj->unk_2F34 > 0) {
        return;
    }
    v = func_020644cc(4);
    if (func_020bce60(obj, v)) {
        func_020bcda0(obj, v, 1, 0);
        func_020bcd7c((int *) obj, (int *) (&obj->unk_2F34));
    }
}

void func_020bcce4(unsigned char *self)
{
    int *count;
    void *p;

    count = (int *) (self + 0x2f34);
    *count -= 1;
    if (*count > 0) {
        return;
    }

    p = (void *) func_020644cc(4);
    if (func_020bce60((UnkStruct_020bcd30 *) self, (int) p) == 0) {
        return;
    }

    func_020bcda0((UnkStruct_020bcd30 *) self, (int) p, 1, 1);
    func_020bcd7c((int *) self, (int *) (self + 0x2f34));
}

void func_020bcc70(UnkStruct_020bcc70 *obj)
{
    int *timers[4];
    int **q;
    int i;
    int *t;

    timers[0] = &obj->timers[0];
    timers[1] = &obj->timers[1];
    timers[2] = &obj->timers[2];
    timers[3] = &obj->timers[3];
    q = timers;
    for (i = 0; i < 4; i++, q++) {
        t = *q;
        *t = *t - 1;
        if (*t > 0) {
            continue;
        }
        if (func_020bcdf8(obj, i) != 0) {
            func_020bcda0((UnkStruct_020bcd30 *) obj, i, 0, 0);
            func_020bcd7c((int *) obj, t);
        }
    }
}

void func_020bcb84(UnkStruct_020bcb84 *s)
{
    int *ptrs[4];
    int **p;
    int i;
    int all;

    ptrs[0] = &s->a;
    ptrs[1] = &s->b;
    ptrs[2] = &s->c;
    ptrs[3] = &s->d;
    p = ptrs;
    all = 1;
    for (i = 0; i < 4; i++, p++) {
        int *e = *p;
        if (*e > 0) {
            *e = *e - 1;
            if (*e <= 0) {
                if (func_020bcdf8((void *) s, i) != 0) {
                    func_020bcda0((UnkStruct_020bcd30 *) s, i, 0, 0);
                } else {
                    *e = 1;
                }
            }
        }
        all = all & (*e <= 0 ? 1 : 0);
        if (all != 0) {
            all = 1;
        } else {
            all = 0;
        }
    }
    if (all != 0) {
        int n = func_020644cc(4);
        int t = (n + 1) + func_020644cc(3);
        int m = t & 3;
        p = ptrs;
        for (i = 0; i < 4; i++, p++) {
            if (n == i || m == i) {
                **p = s->unk_2F48 + func_020644cc(0x1e);
            }
        }
    }
}

void func_020bcab0(UnkStruct_020bcab0 *s)
{
    int *ptrs[4];
    int **p;
    int i;
    int all;

    ptrs[0] = &s->a;
    ptrs[1] = &s->b;
    ptrs[2] = &s->c;
    ptrs[3] = &s->d;
    p = ptrs;
    all = 1;
    for (i = 0; i < 4; i++, p++) {
        int *e = *p;
        if (*e > 0) {
            *e = *e - 1;
            if (*e <= 0) {
                if (func_020bcdf8((void *) s, i) != 0) {
                    func_020bcda0((UnkStruct_020bcd30 *) s, i, 0, 0);
                } else {
                    *e = 1;
                }
            }
        }
        all = all & (*e <= 0 ? 1 : 0);
        if (all != 0) {
            all = 1;
        } else {
            all = 0;
        }
    }
    if (all != 0) {
        int n = func_020644cc(4);
        p = ptrs;
        for (i = 0; i < 4; i++, p++) {
            if (i != n) {
                **p = s->unk_2F48 + func_020644cc(0x1e);
            }
        }
    }
}

void func_020bca80(UnkStruct_020bca80 *s, int a, int b, int c)
{
    s->unk_2F48 = a;
    s->unk_2F30 = b + (c > 0 ? func_020644cc(c) : 0);
}

void func_020bc9c4(UnkStruct_020bc9c4 *self, int flag)
{
    unsigned char *p;
    unsigned int ret;
    int result;
    int i;
    int idx;
    int v;
    int skip;
    int j;

    if (flag == 0x14) {
        ret = (unsigned int) func_020644cc(0x64);
        p = data_020d2315;
        result = 5;
        for (i = 1; i < 14; i++, p++) {
            if (ret < *p) {
                result = i;
                break;
            }
        }
        self->unk_2F2C = result;
    } else {
        self->unk_2F2C = flag;
    }

    idx = self->unk_2F2C;
    v = data_020d2378[idx];
    if (v > 0) {
        skip = 0;
        j = idx - 1;
        if ((unsigned) j <= 18) {
            if ((1 << j) & 0x4c007) {
                skip = 1;
            }
        }
        if (skip) {
            self->unk_2F34 = (unsigned int) func_020644cc(v);
        } else {
            self->unk_2F38 = (unsigned int) func_020644cc(v);
            self->unk_2F3C = (unsigned int) func_020644cc(v);
            self->unk_2F40 = (unsigned int) func_020644cc(v);
            self->unk_2F44 = (unsigned int) func_020644cc(v);
        }
    }
}

void func_020bc98c(UnkStruct_020bc98c *param)
{
    int value = param->unk_2F30;
    if (value < 0) {
        func_020bca80((UnkStruct_020bca80 *) param, 20, 100, 400);
    } else if (value == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) param, 20);
    }
    func_020bcd30((UnkStruct_020bcd30 *) param);
}

void func_020bc954(struct UnkStruct_020bc954 *ptr)
{
    if (ptr->unk_2F30 < 0) {
        func_020bca80((UnkStruct_020bca80 *) ptr, 100, 100, 500);
    } else if (ptr->unk_2F30 == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) ptr, 20);
    }
    func_020bcd30((UnkStruct_020bcd30 *) ptr);
}

void func_020bc91c(struct UnkStruct_020bc91c *obj)
{
    int val = obj->unk_2F30;
    if (val < 0) {
        func_020bca80((UnkStruct_020bca80 *) obj, 200, 100, 600);
    } else if (val == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) obj, 20);
    }
    func_020bcd30((UnkStruct_020bcd30 *) obj);
}

void func_020bc8e4(UnkStruct_020bc8e4 *arg)
{
    int field = arg->unk_2F30;
    if (field < 0) {
        func_020bca80((UnkStruct_020bca80 *) arg, 0x32, 0x64, 0x190);
    } else if (field == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) arg, 0x14);
    }
    func_020bcc70((UnkStruct_020bcc70 *) arg);
}

void func_020bc8ac(UnkStruct_020bc8ac *p)
{
    int val = p->unk_2F30;
    if (val < 0) {
        func_020bca80((UnkStruct_020bca80 *) p, 0xA0, 0x64, 500);
    } else {
        if (val == 0) {
            func_020bc9c4((UnkStruct_020bc9c4 *) p, 0x14);
        }
    }
    func_020bcc70((UnkStruct_020bcc70 *) p);
}

void func_020bc870(struct Struct020bc870 *p)
{
    int f;
    f = p->unk_2F30;
    if (f < 0) {
        func_020bca80((UnkStruct_020bca80 *) p, 0x12c, 0x64, 0x258);
    } else if (f == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) p, 0x14);
    }
    func_020bcc70((UnkStruct_020bcc70 *) p);
}

void func_020bc838(UnkStruct_020bc838 *arg)
{
    int val;
    val = arg->unk_2F30;
    if (val < 0) {
        func_020bca80((UnkStruct_020bca80 *) arg, 30, 150, 0x190);
    } else {
        if (val == 0) {
            func_020bc9c4((UnkStruct_020bc9c4 *) arg, 20);
        }
    }
    func_020bcb84((UnkStruct_020bcb84 *) arg);
}

void func_020bc800(struct UnkStruct_020bc800 *p)
{
    int f = p->unk_2F30;
    if (f < 0) {
        func_020bca80((UnkStruct_020bca80 *) p, 60, 150, 500);
    } else if (f == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) p, 20);
    }
    func_020bcb84((UnkStruct_020bcb84 *) p);
}

void func_020bc7c8(Struct020bc7c8 *ptr)
{
    if (ptr->unk_2F30 < 0) {
        func_020bca80((UnkStruct_020bca80 *) ptr, 100, 150, 600);
    } else if (ptr->unk_2F30 == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) ptr, 20);
    }
    func_020bcb84((UnkStruct_020bcb84 *) ptr);
}

void func_020bc790(void *arg)
{
    int field = *(int *) ((char *) arg + 0x2f30);
    if (field < 0) {
        func_020bca80((UnkStruct_020bca80 *) arg, 0x28, 0x96, 0x190);
    } else if (field == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) arg, 0x14);
    }
    func_020bcab0((UnkStruct_020bcab0 *) arg);
}

void func_020bc758(void *p)
{
    int field;

    field = *(int *) ((char *) p + 0x2f30);
    if (field < 0) {
        func_020bca80((UnkStruct_020bca80 *) p, 80, 150, 500);
    } else if (field == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) p, 20);
    }
    func_020bcab0((UnkStruct_020bcab0 *) p);
}

void func_020bc720(void *arg)
{
    int val;

    val = ((Struct020bc720 *) arg)->unk_2F30;
    if (val < 0) {
        func_020bca80((UnkStruct_020bca80 *) arg, 0x8c, 0x96, 0x258);
    } else if (val == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) arg, 0x14);
    }
    func_020bcab0((UnkStruct_020bcab0 *) arg);
}

void func_020bc6f4(UnkStruct_020bc6f4 *ptr)
{
    int field = ptr->unk_2F30;
    if (field < 0) {
        func_020bca80((UnkStruct_020bca80 *) ptr, 0, 100, 150);
    } else if (field == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) ptr, 20);
    }
}

void func_020bc6c0(UnkStruct_020bc6c0 *ptr)
{
    int field = ptr->unk_2F30;
    if (field < 0) {
        int zero = 0;
        func_020bca80((UnkStruct_020bca80 *) ptr, zero, 100, zero);
    } else if (field == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) ptr, 15);
    }
    func_020bcc70((UnkStruct_020bcc70 *) ptr);
}

void func_020bc68c(void *obj)
{
    int value;

    value = *((int *) ((char *) obj + 0x2f30));
    if (value < 0) {
        func_020bca80((UnkStruct_020bca80 *) obj, 0, 0xc8, 0);
    } else if (value == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) obj, 4);
    }
    func_020bcd30((UnkStruct_020bcd30 *) obj);
}

void func_020bc658(UnkStruct_020bc658 *s)
{
    int val;

    val = s->unk_2F30;
    if (val < 0) {
        func_020bca80((UnkStruct_020bca80 *) s, 0, 100, 0);
    } else {
        if (val == 0) {
            func_020bc9c4((UnkStruct_020bc9c4 *) s, 0x11);
        }
    }
    func_020bcd30((UnkStruct_020bcd30 *) s);
}

void func_020bc624(void *param)
{
    int value = *(int *) ((char *) param + 0x2f30);
    if (value < 0) {
        func_020bca80((UnkStruct_020bca80 *) param, 0, 100, 0);
    } else if (value == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) param, 1);
    }
    func_020bcc70((UnkStruct_020bcc70 *) param);
}

void func_020bc5f8(struct Context *ctx)
{
    int val = ctx->unk_2F30;
    if (val < 0) {
        func_020bca80((UnkStruct_020bca80 *) ctx, 0, 0xe1, 0);
    } else if (val == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) ctx, 0x13);
    }
}

void func_020bc5c4(void *p)
{
    int i;
    i = *(int *) ((char *) p + 0x2f30);
    if (i < 0) {
        func_020bca80((UnkStruct_020bca80 *) p, 0, 0x64, 0);
    } else if (i == 0) {
        func_020bc9c4((UnkStruct_020bc9c4 *) p, 0x10);
    }
    func_020bcce4((unsigned char *) p);
}
