/* touch_pick_shapes_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b7e9c @ 0x020b7e9c, 0x20 bytes, Thumb
 * func_020b7e84 @ 0x020b7e84, 0x18 bytes, Thumb
 * func_020b7e6c @ 0x020b7e6c, 0x18 bytes, Thumb
 * func_020b7e5c @ 0x020b7e5c, 0x10 bytes, Thumb
 * func_020b7e3c @ 0x020b7e3c, 0x20 bytes, Thumb
 * func_020b7e04 @ 0x020b7e04, 0x36 bytes, Thumb
 * func_020b7dc8 @ 0x020b7dc8, 0x3a bytes, Thumb
 * func_020b7db0 @ 0x020b7db0, 0x18 bytes, Thumb
 * func_020b7d84 @ 0x020b7d84, 0x2a bytes, Thumb
 * func_020b7d6c @ 0x020b7d6c, 0x18 bytes, Thumb
 * func_020b7d3c @ 0x020b7d3c, 0x2e bytes, Thumb
 * func_020b7d24 @ 0x020b7d24, 0x18 bytes, Thumb
 * func_020b7cf4 @ 0x020b7cf4, 0x2e bytes, Thumb
 */

struct UnkStruct_020b7e9c {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
};

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
    int unk_20;
    int unk_24;
} UnkStruct_020b7e84;

struct func_020b7e6c_struct {
    unsigned char pad_00[0x1c];
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int unk_24;
};

struct Struct020b7e3c {
    char pad_00[0x1c];
    int unk_1C;
    int unk_20;
    int unk_24;
};

typedef unsigned char GameBool;

typedef struct UnkStruct_020b7db0 UnkStruct_020b7db0;

typedef struct UnkStruct_020b7db0_2 UnkStruct_020b7db0_2;

struct UnkStruct_020b7db0 {
    char pad_00[0x20];
    void *unk_20;
};

struct UnkStruct_020b7db0_2 {
    char pad_00[0x18];
    void *unk_18;
};

extern void func_020b75b0(void);
extern void func_020b75b4(void);
extern GameBool func_020b8060(int, int, int, int, int, short, int, unsigned char);
extern void func_020b7f24(int, int, int, int, int);
extern int func_020b7ebc(int a, int b, int c, int d, int e, int f);
extern int func_020b7fe0(int p0, int p1, int p2, int p3, int p4, int p5);

void *func_020b7d24(void *r0, void *r1);

void func_020b7e9c(struct UnkStruct_020b7e9c *p, unsigned char param)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_00 = 0xffed4000;
    p->unk_18 = 0;
    p->unk_19 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_14 = 0;
    p->unk_1A = param;
}

void func_020b7e84(UnkStruct_020b7e84 *this)
{
    func_020b7e9c((struct UnkStruct_020b7e9c *) this, 0);
    this->unk_1C = 0;
    this->unk_20 = 0;
    this->unk_24 = 0;
}

void func_020b7e6c(struct func_020b7e6c_struct *ptr)
{
    func_020b7e9c((struct UnkStruct_020b7e9c *) ptr, 0);
    ptr->unk_1C = 0;
    ptr->unk_20 = 0;
    ptr->unk_24 = 0;
}

void *func_020b7e5c(void *p)
{
    func_020b75b0();
    return p;
}

struct Struct020b7e3c *func_020b7e3c(struct Struct020b7e3c *p)
{
    func_020b75b4();
    func_020b7e9c((struct UnkStruct_020b7e9c *) p, 0);
    p->unk_1C = 0;
    p->unk_20 = 0;
    p->unk_24 = 0;
    return p;
}

int func_020b7e04(void *a, char *b)
{
    unsigned int i;
    int flag = 1;
    int one = 1;
    int zero = 0;
    int result;

    for (i = 0; i < 10; i++) {
        result = (int) func_020b7d24(a, b);
        b += 0x44;
        flag = (flag | result) ? one : zero;
    }
    return flag;
}

int func_020b7dc8(int p0, int p1, int p2, int p3, int p4, int p5, short p6, int p7, unsigned char p8)
{
    func_020b8060(p1, p2, p3, p4, p5, p6, p7, p8);
    return func_020b7e04((void *) p0, (char *) p1);
}

int func_020b7db0(UnkStruct_020b7db0 *a, UnkStruct_020b7db0_2 *b)
{
    void *tmp;
    b->unk_18 = 0;
    tmp = a->unk_20;
    if (tmp == 0) {
        a->unk_20 = b;
        return 1;
    } else {
        b->unk_18 = tmp;
        a->unk_20 = b;
        return 1;
    }
}

void func_020b7d84(int p0, int p1, int p2, int p3, int p4, unsigned char p5)
{
    func_020b7f24(p1, p2, p3, p4, p5);
    func_020b7db0((UnkStruct_020b7db0 *) p0, (UnkStruct_020b7db0_2 *) p1);
}

void *func_020b7d6c(void *r0, void *r1)
{
    unsigned int *p0 = (unsigned int *) r0;
    unsigned int *p1 = (unsigned int *) r1;
    unsigned int *p2;

    p1[7] = 0;
    p2 = (unsigned int *) p0[9];
    if (p2 == 0) {
        p0[9] = (unsigned int) p1;
        return (void *) 1;
    }
    p1[7] = (unsigned int) p2;
    p0[9] = (unsigned int) p1;
    return (void *) 1;
}

void *func_020b7d3c(int a, int b, int c, int d, int e, int f, unsigned char g)
{
    int local_f = f;
    int local_g = g;
    func_020b7ebc(b, c, d, e, local_f, local_g);
    return func_020b7d6c((void *) a, (void *) b);
}

void *func_020b7d24(void *r0, void *r1)
{
    int r2;
    r2 = 0;
    *(int *) ((char *) r1 + 0x38) = r2;
    r2 = *(int *) ((char *) r0 + 0x1c);
    if (r2 == 0) {
        *(int *) ((char *) r0 + 0x1c) = (int) r1;
        return (void *) 1;
    }
    *(int *) ((char *) r1 + 0x38) = r2;
    *(int *) ((char *) r0 + 0x1c) = (int) r1;
    return (void *) 1;
}

int func_020b7cf4(int a0, int a1, int a2, int a3, int a4, int a5, unsigned char a6)
{
    func_020b7fe0(a1, a2, a3, a4, a5, a6);
    return (int) func_020b7d24((void *) a0, (void *) a1);
}
