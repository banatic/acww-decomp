/* villager_talk_topics_3: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02021f1c @ 0x02021f1c, 0x9c bytes, Thumb
 * func_02021ea8 @ 0x02021ea8, 0x72 bytes, Thumb
 * func_02021e68 @ 0x02021e68, 0x3e bytes, Thumb
 * func_02021e44 @ 0x02021e44, 0x24 bytes, Thumb
 * func_02021df0 @ 0x02021df0, 0x54 bytes, Thumb
 * func_02021dcc @ 0x02021dcc, 0x24 bytes, Thumb
 * func_02021d78 @ 0x02021d78, 0x54 bytes, Thumb
 * func_02021d60 @ 0x02021d60, 0x18 bytes, Thumb
 * func_02021d10 @ 0x02021d10, 0x50 bytes, Thumb
 * func_02021cc8 @ 0x02021cc8, 0x48 bytes, Thumb
 * func_02021cac @ 0x02021cac, 0x1a bytes, Thumb
 * func_02021c4c @ 0x02021c4c, 0x60 bytes, Thumb
 * func_02021c08 @ 0x02021c08, 0x44 bytes, Thumb
 * func_02021ba8 @ 0x02021ba8, 0x60 bytes, Thumb
 * func_02021b8c @ 0x02021b8c, 0x1a bytes, Thumb
 * func_02021b4c @ 0x02021b4c, 0x40 bytes, Thumb
 * func_02021b48 @ 0x02021b48, 0x4 bytes, Thumb
 * func_02021b08 @ 0x02021b08, 0x40 bytes, Thumb
 * func_02021ae4 @ 0x02021ae4, 0x24 bytes, Thumb
 * func_02021a94 @ 0x02021a94, 0x50 bytes, Thumb
 */

struct Data_020c8c78 {
    int a;
    unsigned char b;
};

struct S_02021f1c {
    char pad_00[0x100];
    void *ptr;
    char data[0x20];
    unsigned short val;
};

typedef int (*Pred)(void *self, int elem);

struct UnkStruct_02021df0 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02021df0_2 {
    char pad_00[0x100];
    struct UnkStruct_02021df0 *inner;
};

typedef struct {
    char pad[0x100];
    struct UnkStruct_02021cc8 {
        char pad[0x830];
        char *field_0x830;
    } *sub;
} Arg;

struct UnkStruct_02021c4c {
    char pad_00[0x830];
    void *value;
};

struct UnkStruct_02021c4c_2 {
    char pad_00[0x100];
    struct UnkStruct_02021c4c *b;
};

struct UnkStruct_02021c4c_3 {
    char pad_00[0x40];
    void *unk_40;
};

typedef struct UnkStruct_02021ba8 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02021ba8;

typedef struct UnkStruct_02021ba8_2 {
    char pad_00[0x100];
    UnkStruct_02021ba8 *unk_100;
} UnkStruct_02021ba8_2;

typedef struct UnkStruct_02021b4c {
    char pad_00[0x830];
    int value;
} UnkStruct_02021b4c;

typedef struct UnkStruct_02021b4c_2 {
    char pad_00[0x100];
    UnkStruct_02021b4c *ptr;
} UnkStruct_02021b4c_2;

struct UnkStruct_02021b08 {
    unsigned char pad_00[0x830];
    int value;
};

struct UnkStruct_02021b08_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_02021b08 *inner;
};

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int);
extern void func_0202d694(unsigned short *);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern unsigned int func_0208150c(void *);
extern int func_020036e8(unsigned char *);
extern void func_02015de4(void *, unsigned short *, int, int);
extern struct Data_020c8c78 data_020c8c78;
extern void MI_CpuFill8(void *dstp, unsigned char data, unsigned int size);
extern int func_020644cc(int count);
extern int func_02081e10(int a);
extern void func_0209e474(unsigned int *);
extern int func_0209e3ac(int, unsigned int *, int);
extern int func_0209e380(int, unsigned int *);
extern int func_02081d20(int);
extern int func_02081d64(int);
extern void *func_02015e70(void *a, int b, int c);
extern void func_02015fb0(void *a, int b, int c, int d, int e, int f);
extern int func_02081398(int param1, int param2);
extern void *func_02081d60(void *record);
extern unsigned short *func_02095040(void *record);
extern int memcmp(const void *, const void *, unsigned int);
extern int func_02081c00(int);
extern void *func_020820f8(void *);
extern void *func_02081bc4(void *, void *);
extern void func_02068404(void *, int, void *);
extern void *func_020820e0(void *);
extern unsigned char data_021dc7bc[];
extern int func_0209871c(void *slots, void *key);
extern int func_020814f4(int a);
extern int func_02065f7c(int a);
extern void func_020642fc(void *p);
extern void func_020642bc(void *p, int a);
extern void func_020642f8(void *p);
extern int func_02081aa8(int arg);
extern struct UnkStruct_02021ae4 {
    unsigned short val;
} *func_02081abc(int);

int func_02021f1c(struct S_02021f1c *arg)
{
    int result;
    int ret;
    unsigned short local_val;

    ret = func_020984e8();
    result = 0;
    if (ret != 0) {
        if (func_02098eb8(func_02099734(ret)) != -1) {
            func_0202d694(&local_val);
            arg->val = local_val;
            if (arg->val != 0xfff1) {
                func_02015de4(arg, &arg->val, result, 7);
                func_0202da38(arg, arg->data, &arg->data[30], 30,
                              func_020036e8((unsigned char *) func_0208150c(*(void **) ((char *) arg->ptr + 0x830))),
                              data_020c8c78.a, data_020c8c78.b, result, result);
                result = 1;
            }
        }
    }
    return result;
}

int func_02021ea8(void *self, int *arr, int count, Pred pred)
{
    int found;
    int i;
    int result;
    unsigned char flags[8];

    found = 0;
    result = 0;
    MI_CpuFill8(flags, found, 8);
    for (i = found; i < count; i++) {
        if (arr[i] != 0) {
            if (pred(self, arr[i]) == 1) {
                flags[i] = 1;
                found++;
            }
        }
    }
    if (found > 0) {
        int sel = func_020644cc(found);
        for (i = 0; i < count; i++) {
            if (flags[i] == 1) {
                if (sel == 0) {
                    result = arr[i];
                    break;
                } else {
                    sel--;
                }
            }
        }
    }
    return result;
}

int func_02021e68(int a)
{
    unsigned int data[3];
    int ret;
    int r5;

    data[0] = 0;
    data[1] = 0;
    ret = func_02081e10(a);
    r5 = 0;
    func_0209e474(data);
    if (func_0209e3ac(ret, data, 0x3f) == -1) {
        r5 = func_0209e380(ret, data);
    }
    return r5;
}

int func_02021e44(int unused, int x)
{
    if (func_02081d20(x) > 0 && func_02021e68(x) > 0) {
        return 1;
    }
    return 0;
}

int func_02021df0(struct UnkStruct_02021df0_2 *param0, int param1, int param2)
{
    int result;
    int temp;
    result = func_02021ea8((void *) (param0->inner->unk_830), (int *) (param1), (int) (param2), (Pred) ((((void *) func_02021e44))));
    if (result != 0) {
        temp = func_02081d64(result);
        func_02015e70(param0, temp, 9);
        temp = func_02021e68(result);
        func_02015fb0(param0, temp, 0, 0xa, 0, 0);
    }
    return result;
}

int func_02021dcc(int unused, const void *arg)
{
    if (func_02081d20((int) arg) <= 0 && func_02021e68((int) arg) > 0) {
        return 1;
    }
    return 0;
}

int func_02021d78(int a, int b, int c)
{
    int r5;
    r5 = func_02021ea8((void *) (*(int *) ((char *) *(int **) ((char *) a + 0x100) + 0x830)), (int *) (b), (int) (c), (Pred) ((((void *) func_02021dcc))));
    if (r5 != 0) {
        int t1;
        int t2;
        t1 = func_02081d64(r5);
        func_02015e70((void *) a, t1, 9);
        t2 = func_02021e68(r5);
        func_02015fb0((void *) a, t2, 0, 10, 0, 0);
    }
    return r5;
}

int func_02021d60(int a, int b)
{
    return func_02081398(a, (int) func_02081d60((void *) b));
}

int func_02021d10(int a, int b)
{
    unsigned short *p = (unsigned short *) (a + 0x7dc);
    int flag = 0;
    if (func_02081398(a, (int) func_02081d60((void *) b)) != 0) {
        unsigned short *q = func_02095040(func_02081d60((void *) b));
        if (*q == *p) {
            if (memcmp(q + 1, p + 1, 12) == 0) {
                flag = 1;
            }
        }
    }
    return flag;
}

void *func_02021cc8(Arg *arg, int a, int b)
{
    void *result;
    result =
        (void *) func_02021ea8((void *) ((void *) arg->sub->field_0x830), (int *) (a), (int) (b), (Pred) ((((void *) func_02021d10))));
    if (result != 0) {
        func_02015e70(arg, (int) ((char *) arg->sub->field_0x830 + 0x7dc), 9);
    }
    return result;
}

int func_02021cac(int p1, int p2)
{
    int r;
    r = func_02081c00(p2);
    if (r == 1) {
        return 1;
    } else {
        return 0;
    }
}

void *func_02021c4c(struct UnkStruct_02021c4c_2 *arg, void *p1, void *p2)
{
    void *r5;
    char buf[0x2c];

    r5 = (void *) func_02021ea8((void *) (arg->b->value), (int *) (p1), (int) (p2), (Pred) ((((void *) func_02021cac))));
    if (r5) {
        func_020820f8(buf);
        func_02081bc4(r5, buf);
        func_02068404(((struct UnkStruct_02021c4c_3 *) arg)->unk_40, 1, buf);
        func_02015e70(arg, func_02081d64((int) r5), 9);
        func_020820e0(buf);
    }
    return r5;
}

int func_02021c08(int r0, int r1)
{
    int r5 = (int) func_02081d60((void *) r1);
    int r6 = 0;
    int r4 = 0;
    if (func_02081398((int) ((void *) r0), (int) ((void *) r5)) == 1) {
        r4 = 1;
    }
    if (r4 != 0) {
        if (func_0209871c(data_021dc7bc, (void *) r5) != -1) {
            r6 = 1;
        }
    }
    return r6;
}

int func_02021ba8(UnkStruct_02021ba8_2 *a, int b, int c)
{
    int ret = func_02021ea8((void *) (a->unk_100->unk_830), (int *) (b), (int) (c), (Pred) ((((void *) func_02021c08))));
    if (ret) {
        int r6 = func_02065f7c(func_020814f4(a->unk_100->unk_830));
        int local[4];
        func_020642fc(local);
        func_020642bc(local, r6);
        func_02015e70(a, (int) local, 9);
        func_020642f8(local);
    }
    return ret;
}

int func_02021b8c(int a, int b)
{
    if (func_02081aa8(b) == 1) {
        return 1;
    } else {
        return 0;
    }
}

int func_02021b4c(UnkStruct_02021b4c_2 *a, int b, int c)
{
    int result = func_02021ea8((void *) (a->ptr->value), (int *) (b), (int) (c), (Pred) ((((void *) func_02021b8c))));
    if (result != 0) {
        func_02015e70(a, func_02081d64(result), 9);
    }
    return result;
}

int func_02021b48(void)
{
    return 1;
}

int func_02021b08(struct UnkStruct_02021b08_2 *self, int a1, int a2)
{
    int ret;

    ret = func_02021ea8((void *) (self->inner->value), (int *) (a1), (int) (a2), (Pred) ((((void *) func_02021b48))));
    if (ret != 0) {
        int x = func_02081d64(ret);
        func_02015e70((void *) self, x, 9);
    }
    return ret;
}

int func_02021ae4(int a, int b)
{
    return func_02081abc(b)->val != 0xfff1;
}

unsigned int func_02021a94(unsigned int a, unsigned int arg1, unsigned int arg2)
{
    unsigned int val;
    unsigned int ret;
    unsigned int tmp;
    unsigned int tmp2;

    val = *(unsigned int *) ((char *) *(unsigned int *) ((char *) a + 0x100) + 0x830);
    ret = func_02021ea8((void *) (val), (int *) (arg1), (int) (arg2), (Pred) ((((void *) func_02021ae4))));
    if (ret) {
        tmp = (unsigned int) func_02081d64(ret);
        func_02015e70((void *) a, tmp, 9);
        tmp2 = (unsigned int) func_02081abc(ret);
        func_02015de4((void *) a, (unsigned short *) tmp2, 1, 7);
    }
    return ret;
}
