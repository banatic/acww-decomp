/* gatekeeper_talk_lines_2: 25 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02262678 @ 0x02262678, 0x6 bytes, Thumb
 * func_ov048_02262670 @ 0x02262670, 0x6 bytes, Thumb
 * func_ov048_02262658 @ 0x02262658, 0x16 bytes, Thumb
 * func_ov048_02262618 @ 0x02262618, 0x40 bytes, Thumb
 * func_ov048_02262588 @ 0x02262588, 0x90 bytes, Thumb
 * func_ov048_0226254c @ 0x0226254c, 0x3a bytes, Thumb
 * func_ov048_02262444 @ 0x02262444, 0x108 bytes, Thumb
 * func_ov048_0226242c @ 0x0226242c, 0x18 bytes, Thumb
 * func_ov048_022623f0 @ 0x022623f0, 0x3c bytes, Thumb
 * func_ov048_022623b8 @ 0x022623b8, 0x38 bytes, Thumb
 * func_ov048_02262390 @ 0x02262390, 0x26 bytes, Thumb
 * func_ov048_02262378 @ 0x02262378, 0x16 bytes, Thumb
 * func_ov048_02262368 @ 0x02262368, 0x10 bytes, Thumb
 * func_ov048_02262358 @ 0x02262358, 0x10 bytes, Thumb
 * func_ov048_02262320 @ 0x02262320, 0x38 bytes, Thumb
 * func_ov048_022622ec @ 0x022622ec, 0x34 bytes, Thumb
 * func_ov048_022622bc @ 0x022622bc, 0x30 bytes, Thumb
 * func_ov048_02262298 @ 0x02262298, 0x22 bytes, Thumb
 * func_ov048_0226224c @ 0x0226224c, 0x4c bytes, Thumb
 * func_ov048_022621e8 @ 0x022621e8, 0x64 bytes, Thumb
 * func_ov048_022621d8 @ 0x022621d8, 0x10 bytes, Thumb
 * func_ov048_022621c8 @ 0x022621c8, 0x10 bytes, Thumb
 * func_ov048_022621a0 @ 0x022621a0, 0x28 bytes, Thumb
 * func_ov048_0226213c @ 0x0226213c, 0x64 bytes, Thumb
 * func_ov048_02262114 @ 0x02262114, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02262678;

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02262670;

typedef struct {
    char data[0x24];
} UnkStruct_0226254c;

typedef struct {
    int a;
    unsigned char b;
} UnkStruct_02262444;

struct UnkStruct_022623f0 {
    char pad_00[0x40];
    void *unk_40;
};

typedef struct {
    char pad_00[0xb8];
    int unk_B8;
} UnkStruct_022623b8;

struct UnkStruct_02262320 {
    char pad_00[0xb8];
    void *unk_B8;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_022621a0;

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x810 - 0x44];
    unsigned char unk_810;
} UnkStruct_0226213c;

typedef struct UnkStruct_02262114 UnkStruct_02262114;

struct UnkStruct_02262114 {
    unsigned char pad_00[0xe6e];
    unsigned short val;
};

typedef struct UnkStruct_02262114_2 UnkStruct_02262114_2;

struct UnkStruct_02262114_2 {
    unsigned char pad_00[0xb8];
    UnkStruct_02262114 *sub;
};

extern int func_020749c4(void);
extern int func_020a0174(void);
extern void func_020a0194(void);
extern void func_020a01b4(void);
extern void func_02074b44(int, int, int);
extern void func_02015fb0(int, int, int, int, int, int);
extern int func_020984e8(void);
extern int func_02099658(int);
extern void *func_02077d00(void *entries);
extern void *func_02077c3c(void *object);
extern int func_02077e50(void *friend_data);
extern int data_ov048_0226472c;
extern int data_ov048_02263d20;
extern UnkStruct_02262444 data_ov048_022641a8[11];
extern int func_020a12e8(void);
extern int func_0202e9fc(void);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_0209dcac(void);
extern int func_ov004_0222d4d4(void);
extern int func_ov004_0222d518(void);
extern void func_ov048_022616b8(void *p, int b);
extern void *data_020ccf94;
extern int func_02073918(void *a, int b);
extern void func_0206844c(void *a, char *b, void *c);
extern void func_ov048_022635f4(int, int);
extern void func_0207428c(void);
extern unsigned char func_020ec1e8(void);
extern void func_02068364(void *p, int v);
extern void func_02068440(void *p);
extern void func_02068358(void *p);
extern void func_02068434(void *p);
extern void func_020157a4(void *a, void *b, void *c, int d);
extern int func_02015828(void *a, int b);
extern void func_020157c8(void *p, int a, int b);
extern void func_020732b4(void *p, int x);
extern void func_02073100(void);
extern int func_020eb704(int val);
extern unsigned char func_ov048_022609fc(void *receiver);
extern int func_02099664(int);
extern void *func_02077bcc(void *record);
extern unsigned long long func_020eb694(int record);
extern int func_ov048_02260a60(void *arg0);

void func_ov048_02262390(void *self, int flag);

void func_ov048_02262678(UnkStruct_02262678 *p, unsigned long v)
{
    p->unk_B0 = v;
}

unsigned long func_ov048_02262670(UnkStruct_02262670 *p)
{
    return p->unk_B0;
}

int func_ov048_02262658(void *receiver)
{
    int result = func_020749c4();
    if (result) {
        result = func_020a0174();
    }
    return result;
}

void func_ov048_02262618(int p1, unsigned int p2, int p3)
{
    switch (p2) {
        case 0:
            break;
        case 3:
        case 4:
            func_020a0194();
            break;
        case 1:
        case 2:
            func_020a01b4();
            break;
    }
    func_02074b44(p2, 4, p3);
}

void func_ov048_02262588(int a, unsigned long long d)
{
    unsigned long long q1 = d / 100000000ULL;
    unsigned long long p1 = q1 * 100000000ULL;
    unsigned long long rem = d - p1;
    unsigned long long q2 = rem / 10000ULL;

    func_02015fb0(a, (unsigned int) q1, 5, 4, 6, 0);
    func_02015fb0(a, (unsigned int) q2, 8, 4, 6, 0);

    {
        unsigned long long p2 = q2 * 10000ULL;
        unsigned int final = (unsigned int) ((d - p2) - p1);
        func_02015fb0(a, final, 9, 4, 6, 0);
    }
}

int func_ov048_0226254c(void *receiver)
{
    UnkStruct_0226254c *base;
    int i;
    base = func_02077d00((void *) func_02099658((int) func_020984e8()));
    for (i = 0; i < 32; i++) {
        if (func_02077e50(func_02077c3c(&base[i]))) {
            return 1;
        }
    }
    return 0;
}

void func_ov048_02262444(void *a, void *b)
{
    int saved;
    int v;
    int idx;

    if (!(data_ov048_0226472c & 1)) {
        v = data_ov048_02263d20;
        data_ov048_022641a8[0].a = v;
        data_ov048_022641a8[1].a = v;
        data_ov048_022641a8[2].a = v;
        data_ov048_022641a8[3].a = v;
        data_ov048_022641a8[4].a = v;
        data_ov048_022641a8[5].a = v;
        data_ov048_022641a8[6].a = v;
        data_ov048_022641a8[7].a = v;
        data_ov048_022641a8[9].a = v;
        data_ov048_022641a8[10].a = v;
        data_ov048_0226472c |= 1;
    }

    ((unsigned char *) a)[0x811] = 0;
    ((unsigned char *) a)[0x810] = 0;

    saved = func_020984e8();

    if (func_020a12e8() != 0) {
        func_ov048_02262678((UnkStruct_02262678 *) a, 8);
    } else {
        if ((int) func_ov048_02262670((UnkStruct_02262670 *) a) == 6) {
            if (func_ov004_0222d4d4() == 0) {
                func_ov004_0222d518();
            }
        } else if ((int) func_ov048_02262670((UnkStruct_02262670 *) a) == 7 ||
                   (int) func_ov048_02262670((UnkStruct_02262670 *) a) == 9 ||
                   (int) func_ov048_02262670((UnkStruct_02262670 *) a) == 10) {
            // empty
        } else {
            if (func_0202e9fc() == 0) {
                func_ov048_02262678((UnkStruct_02262678 *) a, 5);
            } else {
                if (func_02099020(saved, 5) == 0) {
                    func_ov048_02262678((UnkStruct_02262678 *) a, 0);
                    func_02098ff8(saved, 5);
                } else {
                    v = func_0209dcac() + 1;
                    func_ov048_02262678((UnkStruct_02262678 *) a, v);
                }
            }
        }
    }

    idx = *(int *) ((unsigned char *) a + 0xb0);
    if (idx >= 0 && idx < 11) {
        ((unsigned char *) b)[4] = data_ov048_022641a8[idx].b;
        *(int *) b = data_ov048_022641a8[*(int *) ((unsigned char *) a + 0xb0)].a;
    }
}

void func_ov048_0226242c(void *p)
{
    func_ov048_02262390(p, 0);
    func_ov048_022616b8(p, 0x15);
}

void func_ov048_022623f0(struct UnkStruct_022623f0 *p)
{
    char buf[8];

    buf[0] = func_02073918(data_020ccf94, 0) ? 0x10 : 0xf;
    func_0206844c(p->unk_40, buf, (*(void **) &data_ov048_02263d20));
}

void func_ov048_022623b8(UnkStruct_022623b8 *self)
{
    func_ov048_022635f4(self->unk_B8, 7);
    func_0207428c();
    if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
        func_ov048_022616b8(self, 20);
    } else {
        func_ov048_02262658(self);
    }
}

void func_ov048_02262390(void *self, int flag)
{
    void *p = *(void **) ((char *) self + 0x40);
    if (flag) {
        func_02068364(p, 1);
    } else {
        func_02068364(p, 0);
    }
    func_02068440(p);
}

void func_ov048_02262378(void *self)
{
    void *p = *(void **) ((char *) self + 0x40);
    func_02068358(p);
    func_02068434(p);
}

void func_ov048_02262368(int *a1)
{
    func_ov048_022635f4(a1[0x2e], 5);
}

void func_ov048_02262358(void *self)
{
    func_ov048_022635f4((int) (*(void **) ((char *) self + 0xb8)), 6);
}

void func_ov048_02262320(struct UnkStruct_02262320 *self)
{
    func_ov048_02262390(self, 1);
    func_ov048_02262618((int) self, 4, 2);
    *(unsigned short *) ((char *) self->unk_B8 + 0xe6e) = 0x960;
    func_ov048_022616b8(self, 10);
}

void func_ov048_022622ec(void *arg)
{
    int two = 2;
    char *ptr;
    func_ov048_02262390(arg, 1);
    func_ov048_02262618((int) arg, two, two);
    ptr = *(char **) ((char *) arg + 0xB8);
    *(short *) (ptr + 0x0E6E) = 200;
    func_ov048_022616b8(arg, 1);
}

void func_ov048_022622bc(void *p)
{
    func_020157a4(p, (char *) p + 0x30c, (char *) p + 0x2f0, 0);
    func_02015828(p, 4);
    func_ov048_022616b8(p, 3);
}

void func_ov048_02262298(void *p)
{
    func_020157c8(p, 0x3c, 0);
    func_02015828(p, 2);
    func_ov048_022616b8(p, 2);
}

void func_ov048_0226224c(void *self)
{
    func_ov048_02262390(self, 1);
    if (func_020ec1e8() == 2) {
        func_020732b4(data_020ccf94, 1);
    } else {
        func_ov048_02262618((int) self, 2, 1);
    }
    *(unsigned short *) ((char *) *(void **) ((char *) self + 0xb8) + 0xe6e) = 0xc8;
    func_ov048_022616b8(self, 4);
}

void func_ov048_022621e8(void *self)
{
    int val;

    func_020732b4((void *) ((*(int *) &data_020ccf94)), 1);
    if ((int) func_020ec1e8() != 4) {
        func_ov048_02262320((struct UnkStruct_02262320 *) self);
    } else {
        func_ov048_02262390(self, 1);
        val = *(int *) ((char *) self + 0x3ec);
        func_02073100();
        func_020eb704(val);
        *(short *) (*(char **) ((char *) self + 0xb8) + 0xe6e) = 0x960;
        func_ov048_022616b8(self, 5);
    }
}

void func_ov048_022621d8(char *self)
{
    func_ov048_022635f4(*(int *) (self + 0xb8), 8);
}

void func_ov048_022621c8(void *param)
{
    func_ov048_022635f4(*(int *) ((char *) param + 0xb8), 0xa);
}

void func_ov048_022621a0(UnkStruct_022621a0 *self)
{
    char tmp;
    tmp = func_ov048_022609fc(self);
    func_0206844c((void *) self->unk_40, &tmp, (void *) data_ov048_02263d20);
}

void func_ov048_0226213c(UnkStruct_0226213c *p)
{
    unsigned char local[8];
    unsigned long long ret;

    if (p->unk_810) {
        ret = func_020eb694((int) func_02077bcc((void *) func_02099664((int) func_020984e8())));
        func_ov048_02262588((int) p, ret);
        local[0] = 0x76;
        func_0206844c(p->unk_40, (char *) (&local[0]), (void *) ((*(unsigned int *) &data_ov048_02263d20)));
    } else {
        local[1] = (unsigned char) func_ov048_02260a60((void *) p);
        func_0206844c(p->unk_40, (char *) (&local[1]), (void *) ((*(unsigned int *) &data_ov048_02263d20)));
    }
}

void func_ov048_02262114(UnkStruct_02262114_2 *self)
{
    func_ov048_02262390((void *) self, 1);
    self->sub->val = 0xc8;
    func_ov048_022616b8((void *) self, 8);
}
