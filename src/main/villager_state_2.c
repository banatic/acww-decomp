/* villager_state_2: 33 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020794a4 @ 0x020794a4, 0x4 bytes, Thumb
 * func_020794a0 @ 0x020794a0, 0x4 bytes, Thumb
 * func_02079494 @ 0x02079494, 0xc bytes, Thumb
 * func_02079478 @ 0x02079478, 0x1a bytes, Thumb
 * func_02079468 @ 0x02079468, 0xe bytes, Thumb
 * func_02079464 @ 0x02079464, 0x4 bytes, Thumb
 * func_0207945c @ 0x0207945c, 0x6 bytes, Thumb
 * func_02079450 @ 0x02079450, 0xc bytes, Thumb
 * func_0207944c @ 0x0207944c, 0x4 bytes, Thumb
 * func_02079448 @ 0x02079448, 0x2 bytes, Thumb
 * func_02079444 @ 0x02079444, 0x2 bytes, Thumb
 * func_02079438 @ 0x02079438, 0xa bytes, Thumb
 * func_02079410 @ 0x02079410, 0x26 bytes, Thumb
 * func_02079400 @ 0x02079400, 0xe bytes, Thumb
 * func_020793f0 @ 0x020793f0, 0x10 bytes, Thumb
 * func_020793c4 @ 0x020793c4, 0x2c bytes, Thumb
 * func_020793b4 @ 0x020793b4, 0x10 bytes, Thumb
 * func_02079358 @ 0x02079358, 0x5c bytes, Thumb
 * func_02079350 @ 0x02079350, 0x8 bytes, Thumb
 * func_02079330 @ 0x02079330, 0x20 bytes, Thumb
 * func_0207932c @ 0x0207932c, 0x2 bytes, Thumb
 * func_020792dc @ 0x020792dc, 0x50 bytes, Thumb
 * func_020792c8 @ 0x020792c8, 0x12 bytes, Thumb
 * func_020792b4 @ 0x020792b4, 0x12 bytes, Thumb
 * func_020792a0 @ 0x020792a0, 0x12 bytes, Thumb
 * func_02079280 @ 0x02079280, 0x20 bytes, Thumb
 * func_02079260 @ 0x02079260, 0x20 bytes, Thumb
 * func_02079238 @ 0x02079238, 0x26 bytes, Thumb
 * func_0207921c @ 0x0207921c, 0x1c bytes, Thumb
 * func_02079204 @ 0x02079204, 0x18 bytes, Thumb
 * func_020791ec @ 0x020791ec, 0x18 bytes, Thumb
 * func_020791d4 @ 0x020791d4, 0x18 bytes, Thumb
 * func_020791bc @ 0x020791bc, 0x18 bytes, Thumb
 */

typedef struct {
    short unk_00;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_02079438;

struct UnkStruct_020793f0 {
    unsigned short unk_00;
    unsigned char unk_02;
};

typedef struct {
    char pad_00[0x1d];
    unsigned char flags;
    char pad_1E[0x2c - 0x1d - 1];
} UnkStruct_020792dc;

typedef struct {
    unsigned char pad_00[0x1D];
    unsigned char unk_1D;
    unsigned char pad_1E[0x0E];
} UnkStruct_02079280;

struct Entry {
    unsigned char unk_00[0x1d];
    unsigned char flags;
    unsigned char unk_1E[14];
};

extern int func_020b6680(void);
extern unsigned char data_020e54a8;
extern void func_0207956c(void *p);
extern int data_021d13e4;
extern void func_02079540(UnkStruct_020792dc *p, int a);
extern void func_020794c0(UnkStruct_020792dc *p, int a);

void func_020794a4(unsigned short *p0, int p1)
{
    p0[13] = p1;
}

int func_020794a0(unsigned short *p0)
{
    return p0[13];
}

void func_02079494(void *r0)
{
    unsigned short r1;
    r1 = *(unsigned short *) ((char *) r0 + 0x1a);
    if (r1 != 0) {
        r1 = r1 - 1;
        *(unsigned short *) ((char *) r0 + 0x1a) = r1;
    }
}

void func_02079478(unsigned char *r4)
{
    if (func_020b6680() == 0) {
        r4[0x1d] |= 2;
    }
}

void func_02079468(unsigned char *ptr)
{
    int tmp;
    tmp = ptr[0x1e] * 2;
    if (tmp > 0x20) {
        tmp = 0x20;
    }
    ptr[0x1e] = tmp;
}

int func_02079464(int p0)
{
    return ((int) (p0) + (38));
}

void func_0207945c(unsigned short *d, unsigned short *s)
{
    d[19] = *s;
}

void func_02079450(unsigned short *r0)
{
    *((unsigned short *) ((char *) r0 + 0x26)) = 0xfff1;
}

int func_0207944c(int p0)
{
    return ((int) (p0) + (40));
}

void func_02079448(void *object) {}

void func_02079444(void *object) {}

void func_02079438(UnkStruct_02079438 *p)
{
    p->unk_02 = 0;
    p->unk_00 = 0;
    p->unk_03 = 0;
}

void func_02079410(unsigned char *arg0, int arg1)
{
    unsigned short val;
    unsigned char val2;

    if (arg1 == 0) {
        val2 = arg0[2];
        if (val2 != 0) {
            val2--;
            arg0[2] = val2;
        } else {
            val = *(unsigned short *) arg0;
            if (val != 0) {
                val--;
                *(unsigned short *) arg0 = val;
            }
        }
        val = *(unsigned short *) arg0;
        if (val == 0) {
            arg0[3] = 0;
        }
    }
    return;
}

void func_02079400(unsigned char *r0)
{
    if (r0[2] != 0) {
        r0[3] = r0[3] + 1;
    }
}

void func_020793f0(struct UnkStruct_020793f0 *p)
{
    p->unk_02 = 0x28;
    p->unk_00 = 0x04b0;
}

int func_020793c4(unsigned char *p)
{
    unsigned int ok;
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0) {
        unsigned char v = p[3];
        if (v >= 0xa) {
            return 2;
        }
        if (v >= 7) {
            return 1;
        }
    }
    return 0;
}

int func_020793b4(int value)
{
    if (value >= 0 && value < 8) {
        return 1;
    }
    return 0;
}

void func_02079358(void *p)
{
    int i;
    char *base = (char *) p;

    for (i = 0; i < 8; i++) {
        func_0207956c(base + i * 0x2c);
    }

    base[0x160] = -1;
    base[0x161] = 0;
    base[0x162] = -1;
    base[0x163] = -1;
    base[0x164] = -1;
    *(int *) (base + 0x168) = 0;
    base[0x16c] = -1;
}

int func_02079350(void)
{
    return (int) &data_021d13e4;
}

int func_02079330(int param1, int param2)
{
    int result;
    int temp;

    result = 0;
    temp = param2;
    if (func_020793b4(temp) != 0) {
        result = param1 + (param2 * 0x2c);
    }
    return result;
}

void func_0207932c(void) {}

void func_020792dc(UnkStruct_020792dc *p)
{
    int i = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    do {
        func_02079540(p, a);
        p->flags &= ~1;
        func_020794c0(p, b);
        func_020794a4((unsigned short *) p, c);
        p->flags &= ~4;
        func_02079438((UnkStruct_02079438 *) ((void *) func_0207944c((int) p)));
        p++;
        i++;
    } while (i < 8);
}

void func_020792c8(void)
{
    func_02079358((void *) func_02079350());
}

void func_020792b4(void)
{
    func_02079350();
    func_0207932c();
}

void func_020792a0(void)
{
    func_020792dc((UnkStruct_020792dc *) ((void *) func_02079350()));
}

void func_02079280(void)
{
    UnkStruct_02079280 *p;
    int i;
    p = (UnkStruct_02079280 *) func_02079350();
    for (i = 0; i < 8; i++) {
        p->unk_1D &= ~1;
        p++;
    }
}

void func_02079260(void)
{
    struct Entry *p;
    int i;

    p = (struct Entry *) func_02079350();
    for (i = 0; i < 8; i++) {
        p->flags &= ~4;
        p++;
    }
}

void func_02079238(void)
{
    unsigned char *p;
    int i;
    p = (unsigned char *) func_02079350();
    for (i = 0; i < 8; i++) {
        func_02079438((UnkStruct_02079438 *) ((void *) func_0207944c((int) p)));
        p += 0x2c;
    }
}

void func_0207921c(void)
{
    char *p = (char *) func_02079350();
    p[0x160] = -1;
}

void func_02079204(unsigned char arg0)
{
    unsigned char *ptr;
    ptr = (unsigned char *) func_02079350();
    ptr[0x162] = arg0;
}

int func_020791ec(void)
{
    int result;
    result = func_02079350();
    return ((signed char *) result)[0x162];
}

void func_020791d4(unsigned char r0)
{
    unsigned char *r4;
    r4 = (unsigned char *) func_02079350();
    r4[0x163] = r0;
}

signed char func_020791bc(void)
{
    signed char result;
    result = *(signed char *) ((unsigned int) func_02079350() + 0x163);
    return result;
}
