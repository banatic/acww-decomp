/* session_3: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02073e30 @ 0x02073e30, 0xd0 bytes, Thumb
 * func_02073de4 @ 0x02073de4, 0x4a bytes, Thumb
 * func_02073de0 @ 0x02073de0, 0x4 bytes, Thumb
 * func_02073dd4 @ 0x02073dd4, 0xc bytes, Thumb
 * func_02073db4 @ 0x02073db4, 0x1e bytes, Thumb
 * func_02073d90 @ 0x02073d90, 0x22 bytes, Thumb
 * func_02073d80 @ 0x02073d80, 0x10 bytes, Thumb
 * func_02073d78 @ 0x02073d78, 0x8 bytes, Thumb
 * func_02073d74 @ 0x02073d74, 0x4 bytes, Thumb
 * func_02073d70 @ 0x02073d70, 0x4 bytes, Thumb
 * func_02073d6c @ 0x02073d6c, 0x4 bytes, Thumb
 * func_02073d68 @ 0x02073d68, 0x4 bytes, Thumb
 * func_02073d64 @ 0x02073d64, 0x4 bytes, Thumb
 * func_02073d28 @ 0x02073d28, 0x3a bytes, Thumb
 * func_02073d10 @ 0x02073d10, 0x16 bytes, Thumb
 * func_02073cf0 @ 0x02073cf0, 0x20 bytes, Thumb
 * func_02073cd0 @ 0x02073cd0, 0x20 bytes, Thumb
 * func_02073cb8 @ 0x02073cb8, 0x18 bytes, Thumb
 * func_02073ca8 @ 0x02073ca8, 0x10 bytes, Thumb
 * func_02073c90 @ 0x02073c90, 0x16 bytes, Thumb
 * func_02073c74 @ 0x02073c74, 0x1c bytes, Thumb
 * func_02073c58 @ 0x02073c58, 0x1a bytes, Thumb
 * func_02073c48 @ 0x02073c48, 0x10 bytes, Thumb
 * func_02073c04 @ 0x02073c04, 0x44 bytes, Thumb
 * func_02073bf4 @ 0x02073bf4, 0xe bytes, Thumb
 * func_02073bf0 @ 0x02073bf0, 0x4 bytes, Thumb
 * func_02073bcc @ 0x02073bcc, 0x22 bytes, Thumb
 * func_02073bac @ 0x02073bac, 0x20 bytes, Thumb
 * func_02073b9c @ 0x02073b9c, 0x10 bytes, Thumb
 * func_02073b84 @ 0x02073b84, 0x18 bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02073de4;

struct UnkStruct_02073d90 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
    unsigned char pad_68[4];
    unsigned char unk_6C;
};

struct UnkStruct_02073d80 {
    unsigned int pad_00;
    unsigned short unk_04;
};

typedef struct {
    char pad_00[8];
    char *base;
    char pad_0C[0x64 - 0xc];
    int limit;
} UnkStruct_02073d28;

typedef struct {
    char pad_00[0x18];
    int array[1];
} UnkStruct_02073c74;

struct UnkStruct_02073c04 {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x64 - 0x24 - 4];
    int unk_64;
};

extern unsigned int func_02073044(void);
extern int func_020ebeb8(int a, int b, int c, int d, int e, int f, unsigned short g, int h, int i, int j, unsigned short k,
                         int l);
extern int func_02077b28(int a);
extern void func_02073180(void *a, int b);
extern int func_02077a64(void);
extern void func_02073168(void *a, int b);
extern unsigned int func_020ec2d4(void);
extern int func_020ebf70(void);
extern int func_02073918(UnkStruct_02073d28 *p, int idx);
extern int func_02077b58(int);
extern void func_020739b8(void *arg);

unsigned char func_02073dd4(const unsigned char *data, int index);
int func_02073d70(unsigned char *p0);

int func_02073e30(void *p1, int p2, int p3, int p4, int p5, int p6, unsigned short p7, int p8, int p9, unsigned short p10)
{
    func_02073044();
    if (func_020ebeb8(p2, p3, p4, 0, p5, p6, p7, 0, p8, p9, p10, 0) != 0) {
        if (func_02073d70((unsigned char *) p1) != 2) {
            if (p2 != 0 || p5 != 0 || p8 != 0) {
                if (p3 != 0 || p6 != 0 || p9 != 0) {
                    if (p2 != 0 && p3 != 0) {
                        func_02077b28(p2);
                    }
                    if (p5 != 0 && p6 != 0) {
                        func_02077b28(p5);
                    }
                    if (p8 != 0 && p9 != 0) {
                        func_02077b28(p8);
                    }
                    func_02073180(p1, 0);
                    func_02077a64();
                    func_02073168(p1, 0x258);
                }
            }
        } else {
            func_02073180(p1, 0);
            func_02073168(p1, 0);
        }
        return 1;
    }
    return 0;
}

int func_02073de4(void *ptr)
{
    UnkStruct_02073de4 *self = (UnkStruct_02073de4 *) ptr;
    int r4 = self->unk_64;
    if ((int) func_02073dd4((const unsigned char *) ptr, r4) == 0) {
        goto ret1;
    }
    if (r4 == 0) {
        if (func_020ec2d4() <= 1) {
            goto ret1;
        }
        func_02073044();
        if (func_020ebf70() != 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        func_02073044();
        if (func_020ebf70() != 0) {
            return 1;
        } else {
            return 0;
        }
    }
ret1:
    return 1;
}

void func_02073de0(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (p0) + (p1)) = p2;
}

unsigned char func_02073dd4(const unsigned char *data, int index)
{
    if (index < 4) {
        return data[index];
    } else {
        return 0;
    }
}

void func_02073db4(int a)
{
    int i;
    int j = 0;
    int k = 3;

    for (i = 3; i >= 0; i--) {
        func_02073de0(a, i, j);
    }
}

int func_02073d90(struct UnkStruct_02073d90 *s)
{
    if ((int) func_02073dd4((const unsigned char *) s, s->unk_64) != 0) {
        if (s->unk_6C >= 2) {
            return 1;
        }
    }
    return 0;
}

short func_02073d80(struct UnkStruct_02073d80 *s)
{
    return s->unk_04 & 0x7fff;
}

void func_02073d78(unsigned short *p0)
{
    p0[2] = ((int) (p0[2]) + (1));
}

void func_02073d74(unsigned char *p0, int p1)
{
    p0[6] = p1;
}

int func_02073d70(unsigned char *p0)
{
    return p0[6];
}

void func_02073d6c(unsigned char *p0, int p1)
{
    p0[7] = p1;
}

int func_02073d68(unsigned char *p0)
{
    return p0[7];
}

void func_02073d64(int *p0, int p1)
{
    p0[2] = p1;
}

char *func_02073d28(UnkStruct_02073d28 *p, int idx)
{
    if (idx >= 4) {
        return p->base;
    }
    if (func_02073918(p, idx) != 0) {
        return 0;
    }
    if (idx < p->limit) {
        return p->base + (idx << 12);
    }
    return p->base + ((idx - 1) << 12);
}

int func_02073d10(int a, int b)
{
    int c;
    c = func_02077b58(b);
    return *(int *) ((char *) a + (c << 2) + 0xc);
}

void func_02073cf0(int arg0, int arg1, int arg2)
{
    int i;
    int *ptr;
    int result;

    i = arg1;
    result = func_02077b58(i);
    ptr = (int *) (arg0 + 0xc);
    ptr[result] += arg2;
}

void func_02073cd0(int *ptr, int x, int y)
{
    ptr += 3;
    ptr[func_02077b58(x)] -= y;
}

void func_02073cb8(int *arr, int n)
{
    int idx = func_02077b58(n);
    *(arr + idx + 3) = 3;
}

void func_02073ca8(int *ptr)
{
    int *p = ptr + 3;
    int i;
    for (i = 2; i >= 0; i--) {
        *p++ = 3;
    }
}

int func_02073c90(int *a, int b)
{
    int c;
    c = func_02077b58(b);
    return *(int *) ((char *) a + (c << 2) + 0x18);
}

void func_02073c74(UnkStruct_02073c74 *s, int key, int value)
{
    s->array[func_02077b58(key)] = value;
}

void func_02073c58(int *r0, int r1)
{
    int *r4;
    int r0_val;
    int r1_val;

    r4 = r0;
    r0_val = r1;
    r0_val = func_02077b58(r0_val);
    r4 = (int *) ((char *) r4 + 0x18);
    r1_val = r0_val << 2;
    r0_val = *(int *) ((char *) r4 + r1_val);
    r0_val = r0_val + 1;
    *(int *) ((char *) r4 + r1_val) = r0_val;
}

void func_02073c48(int *ptr)
{
    int i;
    int *p = ptr + 6;
    for (i = 2; i >= 0; i--) {
        *p++ = 0;
    }
}

int func_02073c04(struct UnkStruct_02073c04 *self, int param1, int param2)
{
    if (param1 >= 4) {
        return self->unk_24;
    }
    if (func_02073918((UnkStruct_02073d28 *) self, param1) != 0) {
        return 0;
    }
    if (param1 < self->unk_64) {
        return self->unk_24 + ((param2 + param1 * 3) << 12);
    } else {
        return self->unk_24 + ((param2 + (param1 - 1) * 3) << 12);
    }
}

int func_02073bf4(int *r0, int r1, int r2)
{
    int r3;
    int r0_out;

    r3 = r0[9]; // offset 0x24 = 36 = 9 * 4
    r0_out = r2 + (r1 * 3);
    r0_out = r0_out << 12;
    return r3 + r0_out;
}

void func_02073bf0(int *p0, int p1)
{
    p0[9] = p1;
}

unsigned int func_02073bcc(char *a1, int a2, int a3)
{
    char *base;
    base = a1 + func_02077b58(a2) * 12;
    return *(unsigned int *) (base + a3 * 4 + 0x28);
}

void func_02073bac(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r2;
    int r6 = r3;
    int r0_2 = r1;
    int result = func_02077b58(r0_2);
    int r1_2 = result * 12;
    int r0_3 = r5 + r1_2;
    int r0_4 = r0_3 + (r4 << 2);
    *(int *) (r0_4 + 0x28) = r6;
}

void func_02073b9c(int a, int b, int c)
{
    func_02073bac(a, b, c, 0);
}

void func_02073b84(void *arg)
{
    int *p;
    int i;
    p = (int *) ((char *) arg + 0x28);
    for (i = 4; i >= 0; i--) {
        *p++ = 0;
    }
    func_020739b8(arg);
}
