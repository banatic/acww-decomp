/* music_volume: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02036378 @ 0x02036378, 0x2 bytes, Thumb
 * func_02036310 @ 0x02036310, 0x66 bytes, Thumb
 * func_020362a0 @ 0x020362a0, 0x6e bytes, Thumb
 * func_02036264 @ 0x02036264, 0x3a bytes, Thumb
 * func_02036228 @ 0x02036228, 0x3a bytes, Thumb
 * func_02036188 @ 0x02036188, 0xa0 bytes, Thumb
 * func_02036124 @ 0x02036124, 0x62 bytes, Thumb
 * func_0203611c @ 0x0203611c, 0x6 bytes, Thumb
 * func_020360d0 @ 0x020360d0, 0x4c bytes, Thumb
 * func_020360a8 @ 0x020360a8, 0x28 bytes, Thumb
 * func_02036034 @ 0x02036034, 0x74 bytes, Thumb
 * func_02036020 @ 0x02036020, 0x12 bytes, Thumb
 * func_0203600c @ 0x0203600c, 0x12 bytes, Thumb
 */

struct UnkStruct_02036310 {
    char pad_00[0xc];
    int state;
};

struct UnkStruct_020362a0 {
    char pad_00[0xc];
    int unk_0C;
};

struct UnkStruct_020362a0_2 {
    char pad_00[0x84];
    int unk_84;
};

typedef struct {
    char pad_00[12];
    int state;
} UnkStruct_02036264;

typedef struct UnkStruct_02036228 {
    unsigned char pad_00[12];
    int state;
} UnkStruct_02036228;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Header;

typedef struct {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
    unsigned char pad2[0x8];
} UnkStruct_02036188;

typedef struct {
    unsigned int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[0x30];
    unsigned int val;
    unsigned char pad2[0x10];
} UnkStruct_02036188_2;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned int state;
} UnkStruct_02036188_3;

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_02036124;

typedef struct {
    unsigned char pad_00[20];
    unsigned char unk_14;
} UnkStruct_0203611c;

typedef struct InnerStruct {
    char pad_00[0xc];
    void *unk_0C;
    char pad_10[4];
    unsigned char unk_14;
    char pad_15[0x1c0 - 0x15];
    int unk_1C0;
} InnerStruct;

typedef struct OuterStruct {
    InnerStruct *obj;
} OuterStruct;

typedef struct Arg1Struct {
    char pad_00[0xc];
    int unk_0C;
} Arg1Struct;

typedef struct Pair {
    int first;
    int second;
} Pair;

struct UnkStruct_020360a8 {
    unsigned char pad_00[0x10];
    unsigned char flag;
    unsigned char pad1[0x1c0 - 0x11];
    int count;
};

struct Block {
    unsigned char pad_00;
    unsigned char val;
    unsigned char pad1[0xe];
};

struct UnkStruct_020360a8_2 {
    struct UnkStruct_020360a8 *inner;
    unsigned char pad_04[0x20];
    struct Block blocks[5];
};

typedef struct {
    char pad_00[5];
    char unk_05;
    char pad_06[10];
} UnkStruct_0203600c;

extern void func_020041dc(void);
extern void func_020041cc(void);
extern void *func_02095794(int size);
extern int func_02034270(void *dst, const void *src, int a, int b);
extern void func_0203423c(void *obj);
extern void func_02036558(void *self, int a, int b, int c);
extern int func_020b65c4(void);
extern Pair data_020da284;
extern void func_02034e28(void *a, Pair b);
extern void func_02035fd8(void *p0, int p1, int p2);

void func_02036378(void *object, void *field) {}

void func_02036310(void *unused, struct UnkStruct_02036310 *s)
{
    if (s->state == 2) {
        func_02036558((void *) s, 0x28, 5, 1);
        s->state = 5;
    } else if (s->state == 3) {
        func_02036558((void *) s, 0x7f, 5, 1);
        s->state = 5;
    } else if (s->state == 4) {
        func_02036558((void *) s, 0, 5, 1);
        s->state = 5;
    } else if (s->state == 5) {
    } else if (s->state == 6) {
        func_02036558((void *) s, 0x7f, 5, 1);
        s->state = 0;
    }
}

void func_020362a0(struct UnkStruct_020362a0_2 *a, struct UnkStruct_020362a0 *b)
{
    if (b->unk_0C == 7) {
        func_02036558((void *) b, 0x28, 5, 1);
        b->unk_0C = 8;
        a->unk_84 = 0;
        func_020041dc();
    } else if (b->unk_0C == 8) {
        return;
    } else if (b->unk_0C == 9) {
        if (a->unk_84 > 0) {
            a->unk_84--;
        }
        if (a->unk_84 <= 0) {
            func_02036558((void *) b, 0x7f, 5, 1);
            b->unk_0C = 0;
            func_020041cc();
        }
    }
}

void func_02036264(int unused, UnkStruct_02036264 *s)
{
    int st;
    st = s->state;
    if (st == 10) {
        func_02036558((void *) s, 0x28, 0xf, 1);
        s->state = 11;
    } else if (st != 11) {
        if (st == 12) {
            func_02036558((void *) s, 0x7f, 0xf, 1);
            s->state = 0;
        }
    }
}

void func_02036228(int unused, UnkStruct_02036228 *p)
{
    int v = p->state;
    if (v == 13) {
        func_02036558((void *) p, 0x28, 0xf, 1);
        p->state = 14;
    } else if (v == 14) {
    } else if (v == 15) {
        func_02036558((void *) p, 0x7f, 0xf, 1);
        p->state = 0;
    }
}

void func_02036188(int unused, UnkStruct_02036188_3 *self)
{
    Header *ptr;
    UnkStruct_02036188 obj1;
    Vec3 vec;
    UnkStruct_02036188_2 obj2;
    unsigned int state;
    unsigned int id;
    unsigned int val;
    unsigned int tx, ty, tz;
    int flag;

    state = self->state;
    flag = 0;
    ptr = (Header *) func_02095794(4);
    if (ptr == 0) {
        goto skip;
    }

    func_02034270(&obj1, ptr, 0, 0);
    id = obj1.unk_34;
    tz = ptr->unk_08 + 0x2000;
    ty = ptr->unk_04;
    tx = ptr->unk_00;
    vec.x = tx;
    vec.y = ty;
    vec.z = tz;
    func_02034270(&obj2, &vec, 0, 0);
    val = obj2.val;
    if (id == 0x13 || id == 0x16 || val == 1) {
        flag = 1;
    }
    func_0203423c(&obj2);
    func_0203423c(&obj1);

skip:
    if (state == 0) {
        if (flag != 0) {
            func_02036558(self, 0x28, 0x3c, 1);
            self->state = 0x10;
        }
    } else if (state == 0x10) {
        if (flag == 0) {
            func_02036558(self, 0x7f, 0x3c, 1);
            self->state = 0;
        }
    }
}

void func_02036124(int param0, UnkStruct_02036124 *param1)
{
    int field = param1->unk_0C;
    int ret = func_020b65c4();
    int flag27 = (ret == 0x27);
    int flag28 = (ret == 0x28);

    if (field == 0) {
        if (flag27 || flag28) {
            func_02036558(param1, 0x40, 0x28, 1);
            param1->unk_0C = 0x11;
        }
    } else if (field == 0x11) {
        if (!flag27 && !flag28) {
            func_02036558(param1, 0x7f, 0x28, 1);
            param1->unk_0C = 0;
        }
    }
}

void func_0203611c(UnkStruct_0203611c *p)
{
    p->unk_14 = 0;
}

void func_020360d0(OuterStruct *a, Arg1Struct *b)
{
    if (a->obj->unk_1C0 > 0) {
        if (a->obj->unk_14 != 0 && a->obj->unk_0C != 0) {
            func_02036558(b, (int) a->obj->unk_0C, 0, 1);
        }
        func_02034e28(a->obj, data_020da284);
        b->unk_0C = 0x12;
    } else {
        b->unk_0C = 0;
    }
}

void func_020360a8(struct UnkStruct_020360a8_2 *p)
{
    struct Block *b;
    struct Block *end;
    char one;

    if (p->inner->count <= 0) {
        return;
    }
    if (p->inner->flag == 0) {
        return;
    }

    b = p->blocks;
    end = (struct Block *) ((char *) p + 0x74);
    one = 1;
    while (b < end) {
        b->val = one;
        b++;
    }
}

void func_02036034(void *p0)
{
    int r1 = 0;
    unsigned char *r2 = *(unsigned char **) p0;
    int r3 = *(int *) (r2 + 0x1c0);
    if (r3 > 0) {
        if (*(unsigned char *) (r2 + 0x12) != 0) {
            unsigned short r4 = *(unsigned short *) (r2 + 4);
            if (r4 != 0xffff) {
                r1 = 1;
            }
        }
    }
    if (r1 != 0) {
        unsigned char *r1p = (unsigned char *) p0 + 0x74;
        unsigned char *r6 = (unsigned char *) p0 + 4;
        int r5 = 0;
        int r4 = 0;
        int r7 = 0;
        while (r1p >= r6) {
            if (*(r1p + 1) == 0) {
                int r3t = *(int *) (r1p + 0xc);
                if (*r1p != 0) {
                    r5 = 1;
                    r7 = *(int *) (r1p + 8);
                }
                if (r3t != 0) {
                    r4 = *(int *) (r1p + 4);
                }
            }
            r1p -= 0x10;
        }
        if (r5 != 0) {
            func_02035fd8((char *) r2 + 0x2b4, r4, r7);
        }
    }
}

void func_02036020(char arr[8][16])
{
    int i;
    int value;
    i = 0;
    value = i;
    do {
        arr[i][4] = value;
        i++;
    } while (i < 8);
}

void func_0203600c(UnkStruct_0203600c *arr)
{
    int i = 0;
    char v = (char) i;
    do {
        arr[i].unk_05 = v;
        i++;
    } while (i < 8);
}
