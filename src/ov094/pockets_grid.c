/* pockets_grid: 23 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229a888 @ 0x0229a888, 0x10 bytes, Thumb
 * func_ov094_0229a850 @ 0x0229a850, 0x38 bytes, Thumb
 * func_ov094_0229a804 @ 0x0229a804, 0x4a bytes, Thumb
 * func_ov094_0229a7cc @ 0x0229a7cc, 0x38 bytes, Thumb
 * func_ov094_0229a768 @ 0x0229a768, 0x64 bytes, Thumb
 * func_ov094_0229a6bc @ 0x0229a6bc, 0xac bytes, Thumb
 * func_ov094_0229a69c @ 0x0229a69c, 0x20 bytes, Thumb
 * func_ov094_0229a668 @ 0x0229a668, 0x34 bytes, Thumb
 * func_ov094_0229a634 @ 0x0229a634, 0x34 bytes, Thumb
 * func_ov094_0229a600 @ 0x0229a600, 0x34 bytes, Thumb
 * func_ov094_0229a530 @ 0x0229a530, 0xd0 bytes, Thumb
 * func_ov094_0229a524 @ 0x0229a524, 0xc bytes, Thumb
 * func_ov094_0229a50c @ 0x0229a50c, 0x18 bytes, Thumb
 * func_ov094_0229a4d8 @ 0x0229a4d8, 0x34 bytes, Thumb
 * func_ov094_0229a4c0 @ 0x0229a4c0, 0x18 bytes, Thumb
 * func_ov094_0229a47c @ 0x0229a47c, 0x44 bytes, Thumb
 * func_ov094_0229a464 @ 0x0229a464, 0x18 bytes, Thumb
 * func_ov094_0229a3b0 @ 0x0229a3b0, 0xb4 bytes, Thumb
 * func_ov094_0229a39c @ 0x0229a39c, 0x14 bytes, Thumb
 * func_ov094_0229a38c @ 0x0229a38c, 0x10 bytes, Thumb
 * func_ov094_0229a36c @ 0x0229a36c, 0x1e bytes, Thumb
 * func_ov094_0229a34c @ 0x0229a34c, 0x1e bytes, Thumb
 * func_ov094_0229a328 @ 0x0229a328, 0x24 bytes, Thumb
 */

typedef struct {
    char pad_00[0xa50];
    unsigned int unk_A50;
    char pad_A54[5];
    unsigned char unk_A59;
    char pad_A5A[2];
    unsigned char unk_A5C;
} UnkStruct_0229a6bc;

struct UnkStruct_0229a668 {
    char pad_00[0xa50];
    int unk_A50;
};

typedef struct {
    char pad_00[0xA50];
    int unk_A50;
} GameStruct;

typedef struct {
    int a;
    int b;
} UnkStruct_0229a524;

struct UnkStruct_0229a4c0 {
    unsigned char pad_00[0xa58];
    unsigned char unk_A58;
};

struct UnkStruct_0229a47c {
    char pad_00[0xa54];
    unsigned short unk_A54;
    char pad_A56[4];
    unsigned char unk_A5A;
    unsigned char unk_A5B;
    unsigned char unk_A5C;
};

typedef struct {
    char data[0xA5D];
} UnkStruct_0229a464;

typedef struct UnkStruct_0229a3b0 UnkStruct_0229a3b0;

struct UnkStruct_0229a3b0 {
    unsigned char pad_00[0x184];
    unsigned char buf[0xa54 - 0x184];
    unsigned short unk_A54;
    unsigned char pad_A56[0xa59 - 0xa56];
    unsigned char unk_A59;
    unsigned char unk_A5A;
    unsigned char unk_A5B;
};

extern int func_ov094_0229aba4(int a, unsigned char b);
extern int func_02088d9c(int val);
extern int func_02088d94(int val);
extern char data_ov094_0229bf70[];
extern const int data_ov094_0229bfa8[];
extern int data_ov094_0229bf98[];
extern int func_020896b8(int, int *, int, int, int, int, int);
extern int data_ov094_0229bfa0[];
extern int func_ov094_0229ab7c(unsigned char *p, int a);
extern int func_ov094_0229ab68(unsigned char *p);
extern int func_ov094_0229a8bc(unsigned char *p, unsigned char a);
extern UnkStruct_0229a524 data_ov094_0229bfb0[];
extern int data_ov094_0229bc64[];
extern void func_020b9ccc(unsigned char *p);
extern int func_0206fe60(void);
extern void *func_ov094_0229b048(char *self, unsigned int idx, unsigned int unused);
extern void func_ov094_0229a8cc(void *self, const unsigned char *tab, void *src, int n);
extern void func_ov094_0229a99c(void *self, unsigned short v, int n);
extern const unsigned char data_ov094_0229bc50[];
extern unsigned char data_ov094_0229bc48[];

int func_ov094_0229a668(struct UnkStruct_0229a668 *obj, int x, int y);
void func_ov094_0229a634(GameStruct *obj, int a, int b, int c);
int func_ov094_0229a600(int *p, int b, int c);
void func_ov094_0229a530(unsigned char *p0, int p1, int p2, int p3, int p4);
UnkStruct_0229a524 *func_ov094_0229a524(int unused, int idx);
int func_ov094_0229a50c(unsigned int index);
unsigned char func_ov094_0229a39c(unsigned char *p);
void func_ov094_0229a36c(void *r0, int r1);
int func_ov094_0229a328(int *arr, int bit);

void func_ov094_0229a888(int a, int b)
{
    func_ov094_0229a36c((void *) (a + 0xa48), b);
}

void func_ov094_0229a850(int a, int b, int c)
{
    int s = (int) func_ov094_0229a524(a, 0);
    int i;
    for (i = 0; i <= 14; i++) {
        func_ov094_0229a530((unsigned char *) a, s, i, b + 0x80, c + 0x60);
        s += 8;
    }
}

void func_ov094_0229a804(int param0, int param1, int param2, int param3)
{
    int r5;
    int i;
    r5 = (int) func_ov094_0229a524(param0, 0);
    for (i = 0; i <= 14; i++) {
        if (func_ov094_0229aba4(param0, i) + 0x18 > param3) {
            func_ov094_0229a530((unsigned char *) param0, r5, i, param1 + 0x80, param2 + 0x60);
        }
        r5 += 8;
    }
}

void func_ov094_0229a7cc(int param1, int param2, int param3)
{
    int value;
    int i;
    value = (int) func_ov094_0229a524(param1, 15);
    for (i = 15; i <= 29; i++) {
        func_ov094_0229a530((unsigned char *) param1, value, i, param2 + 0x80, param3 + 0x60);
        value += 8;
    }
}

void func_ov094_0229a768(const void *a, int b, int c)
{
    if (func_ov094_0229a328((int *) ((const char *) a + 0xa40), 0x21)) {
        int tmp = (int) func_ov094_0229a524((int) a, 0x21);
        int x = b + func_02088d9c(tmp) + 0x80;
        int y = c + func_02088d94(tmp) + 0x60;
        func_ov094_0229a668((struct UnkStruct_0229a668 *) a, x, y);
    }
    if (func_ov094_0229a328((int *) ((const char *) a + 0xa40), 0x22)) {
        c += 0xac;
        func_ov094_0229a668((struct UnkStruct_0229a668 *) a, b + 4, c);
    }
}

void func_ov094_0229a6bc(UnkStruct_0229a6bc *self, int b, int c)
{
    int loc[4];
    int p = b + func_02088d9c((int) data_ov094_0229bf70);
    int d = c + func_02088d94((int) data_ov094_0229bf70);
    int k = func_ov094_0229a50c(self->unk_A59);
    if (k != 0) {
        if (k == 0x1000) {
            func_020896b8(1, (int *) data_ov094_0229bf70, b, c, -1, self->unk_A50, 0);
        } else {
            loc[0] = k;
            loc[1] = 0;
            loc[2] = 0;
            loc[3] = k;
            func_020896b8(1, (int *) data_ov094_0229bf70, b, c, -1, self->unk_A50, (int) loc);
        }
    }
    func_ov094_0229a634((GameStruct *) self, p, d, -1);
    if (self->unk_A5C) {
        func_ov094_0229a600((int *) self, p, d);
    }
}

int func_ov094_0229a69c(const char *arg, int extra)
{
    if (func_ov094_0229a328((int *) (arg + 0xa38), extra) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov094_0229a668(struct UnkStruct_0229a668 *obj, int x, int y)
{
    return func_020896b8(1, (int *) data_ov094_0229bfa8, x - 8, y - 8, -1, obj->unk_A50, 0);
}

void func_ov094_0229a634(GameStruct *obj, int a, int b, int c)
{
    func_020896b8(1, data_ov094_0229bf98, a - 8, b - 8, c, obj->unk_A50, 0);
}

int func_ov094_0229a600(int *p, int b, int c)
{
    return func_020896b8(1, data_ov094_0229bfa0, b - 8, c - 8, -1, p[0x294], 0);
}

void func_ov094_0229a530(unsigned char *p0, int p1, int p2, int p3, int p4)
{
    int x = func_02088d9c(p1) + p3;
    int y = func_02088d94(p1) + p4;
    int z = 0;

    if (func_ov094_0229ab7c(p0, p2) != 0) {
        z = func_ov094_0229ab68(p0);
        x += z;
        y += z;
    }

    if (func_ov094_0229a328((int *) (p0 + 0xa40), p2) != 0) {
        func_ov094_0229a668((struct UnkStruct_0229a668 *) p0, x, y);
    }

    if (func_ov094_0229a328((int *) (p0 + 0xa38), p2) != 0) {
        int var = -1;

        if (func_ov094_0229a8bc(p0, (unsigned char) p2) != 0) {
            var = 0xe;
        }

        func_020896b8(1, (int *) p1, p3 + z, p4 + z, var, *(unsigned int *) (p0 + 0xa50), 0);
        func_ov094_0229a634((GameStruct *) p0, x, y, var);

        if (func_ov094_0229ab7c(p0, p2) != 0) {
            func_ov094_0229a600((int *) p0, x, y);
        }
    }
}

UnkStruct_0229a524 *func_ov094_0229a524(int unused, int idx)
{
    return &data_ov094_0229bfb0[idx];
}

int func_ov094_0229a50c(unsigned int index)
{
    if (index >= 10) {
        return 0x1000;
    }
    return data_ov094_0229bc64[index];
}

void func_ov094_0229a4d8(unsigned char *self)
{
    int i;
    for (i = 0; i < 3; i++) {
        func_020b9ccc(self + 0x98c + i * 0x38);
    }
    self[0xa58] = 0;
}

int func_ov094_0229a4c0(struct UnkStruct_0229a4c0 *p)
{
    unsigned char val = p->unk_A58;
    if (val >= 3) {
        return 2;
    } else {
        p->unk_A58 = val + 1;
        return val;
    }
}

void func_ov094_0229a47c(struct UnkStruct_0229a47c *self, unsigned short value, int mode)
{
    self->unk_A54 = value;
    self->unk_A5A = 0;
    if (mode == 1) {
        self->unk_A5B = 0;
    } else {
        self->unk_A5B = 1;
    }
    if (func_0206fe60() != 0) {
        self->unk_A5C = 0;
    }
}

void func_ov094_0229a464(UnkStruct_0229a464 *s)
{
    s->data[0xA59] = 10;
    s->data[0xA5C] = 1;
}

int func_ov094_0229a3b0(UnkStruct_0229a3b0 *self)
{
    unsigned char state = self->unk_A5A;

    if (state < 6) {
        if (data_ov094_0229bc50[state] != 0xff) {
            void *r = func_ov094_0229b048((char *) self->buf, data_ov094_0229bc50[state], self->unk_A5B);
            func_ov094_0229a8cc(self, ((const unsigned char *) data_ov094_0229bf70), r, 8);
        }
        self->unk_A5A++;
    } else if (state < 8) {
        self->unk_A59 = func_ov094_0229a39c((unsigned char *) self);
        self->unk_A5A++;
    } else if (state == 8) {
        func_ov094_0229a99c(self, self->unk_A54, 0);
        self->unk_A59 = 0;
        self->unk_A5A++;
    } else if (state < 12) {
        self->unk_A59 = func_ov094_0229a39c((unsigned char *) self);
        self->unk_A5A++;
    } else {
        func_ov094_0229a464((UnkStruct_0229a464 *) ((void *) self));
        return 1;
    }
    return 0;
}

unsigned char func_ov094_0229a39c(unsigned char *p)
{
    return data_ov094_0229bc48[p[0xa5a] - 6];
}

void func_ov094_0229a38c(int *arr)
{
    int i;
    for (i = 0; i < 2; i++) {
        arr[i] = 0;
    }
}

void func_ov094_0229a36c(void *r0, int r1)
{
    int r2;
    int r3;
    int r4;
    int r5;

    r2 = r1 >> 5;
    r5 = r2 << 2;
    r4 = *(int *) ((char *) r0 + r5);
    r3 = 1;
    r2 = 0x1f;
    r1 &= r2;
    r3 <<= r1;
    r4 |= r3;
    *(int *) ((char *) r0 + r5) = r4;
}

void func_ov094_0229a34c(void *r0, int r1)
{
    int r2 = r1 >> 5;
    int r4 = ((int *) r0)[r2];
    int r3 = 1 << (r1 & 0x1f);
    r4 &= ~r3;
    ((int *) r0)[r2] = r4;
}

int func_ov094_0229a328(int *arr, int bit)
{
    return (arr[bit >> 5] & (1 << (bit & 31))) ? 1 : 0;
}
