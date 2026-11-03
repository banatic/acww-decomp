/* screen_panels_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b37c @ 0x0208b37c, 0x30 bytes, Thumb
 * func_0208b374 @ 0x0208b374, 0x6 bytes, Thumb
 * func_0208b34c @ 0x0208b34c, 0x28 bytes, Thumb
 * func_0208b344 @ 0x0208b344, 0x6 bytes, Thumb
 * func_0208b2cc @ 0x0208b2cc, 0x78 bytes, Thumb
 * func_0208b2b0 @ 0x0208b2b0, 0x1c bytes, Thumb
 * func_0208b234 @ 0x0208b234, 0x7c bytes, Thumb
 * func_0208b22c @ 0x0208b22c, 0x6 bytes, Thumb
 * func_0208b1dc @ 0x0208b1dc, 0x50 bytes, Thumb
 * func_0208b1d4 @ 0x0208b1d4, 0x6 bytes, Thumb
 * func_0208b1b8 @ 0x0208b1b8, 0x1c bytes, Thumb
 * func_0208b1a0 @ 0x0208b1a0, 0x16 bytes, Thumb
 * func_0208b148 @ 0x0208b148, 0x58 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0208b374;

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0208b344;

typedef struct {
    char pad_00[8];
    char unk_08[0xe0 - 8];
    char unk_E0[1];
    char pad_E1[0x348 - 0xe0 - 1];
    unsigned char flag348;
    unsigned char flag349;
} UnkStruct_0208b2cc;

struct UnkStruct_0208b2b0 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0208b234_2 {
    char x;
};

struct UnkStruct_0208b234 {
    char pad_00[0xe0];
    struct UnkStruct_0208b234_2 sub;
    char pad_E1[0x267];
    unsigned char unk_348;
    unsigned char unk_349;
};

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0208b22c;

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0208b1d4;

typedef struct {
    char pad_00[0x2c4];
    char unk_2C4;
    char pad_2C5[0x348 - 0x2c4 - 1];
    unsigned char unk_348;
    unsigned char unk_349;
} Struct0208b148;

extern void func_0208dd40(void *);
extern int func_0208d13c(void *);
extern void func_0208bfd0(void *);
extern void func_0208b9e0(void *);
extern int func_0208d01c(void *);
extern void func_0208dd10(void *);
extern int func_0208dd00(void *);
extern void func_0208dd18(void *);
extern void func_02011f48(int a);
extern void func_02011f74(int a, int b);
extern void func_0208d04c(struct UnkStruct_0208b234_2 *);
extern int func_0208d03c(struct UnkStruct_0208b234_2 *);
extern void func_0208d054(struct UnkStruct_0208b234_2 *);
extern void func_0208bfc0(unsigned char *p);
extern int func_0208bfa0(unsigned char *p);
extern void func_0208bfc8(unsigned char *p);
extern void func_0208b9d8(void *ptr);
extern void func_0208b0d8(void *ptr);
extern void func_0208b9d0(void *);
extern int func_0208b9c0(void *);
extern void func_0208b090(void *);

void func_0208b2b0(struct UnkStruct_0208b2b0 *p);
void func_0208b1a0(int *r4);

void func_0208b37c(void *arg0)
{
    func_0208dd40((char *) arg0 + 8);
    func_0208d13c((char *) arg0 + 0xe0);
    func_0208bfd0((char *) arg0 + 0x1c4);
    func_0208b9e0((char *) arg0 + 0x2c4);
}

void func_0208b374(UnkStruct_0208b374 *p)
{
    p->unk_04 = 0;
}

void func_0208b34c(unsigned char *p)
{
    if (p[0x348] || p[0x349]) {
        func_0208b1a0((int *) p);
    }
}

void func_0208b344(UnkStruct_0208b344 *p)
{
    p->unk_04 = 1;
}

void func_0208b2cc(UnkStruct_0208b2cc *self)
{
    int flag = (self->flag348 != 0) || (self->flag349 != 0);
    int res = !func_0208d01c(&self->unk_E0);
    if (flag || res) {
        func_0208dd10(&self->unk_08);
        if (func_0208dd00(&self->unk_08) != 0) {
            if (flag) {
                func_0208b1a0((int *) self);
            } else {
                func_0208b2b0((struct UnkStruct_0208b2b0 *) self);
            }
        }
    } else {
        func_0208dd18(&self->unk_08);
    }
}

void func_0208b2b0(struct UnkStruct_0208b2b0 *p)
{
    p->unk_04 = 2;
    func_02011f48(1);
    func_02011f74(1, 1);
}

void func_0208b234(struct UnkStruct_0208b234 *p)
{
    int flag;
    int result;

    if (p->unk_348 != 0 || p->unk_349 != 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    result = func_0208d01c((void *) (&p->sub));

    if (flag || result) {
        func_0208d04c(&p->sub);
        if (func_0208d03c(&p->sub) != 0) {
            if (flag) {
                func_0208b1a0((int *) p);
            } else {
                func_02011f48(0);
                func_02011f74(4, 1);
                func_0208b344((UnkStruct_0208b344 *) p);
            }
        }
    } else {
        func_0208d054(&p->sub);
    }
}

void func_0208b22c(UnkStruct_0208b22c *p)
{
    p->unk_04 = 3;
}

void func_0208b1dc(unsigned char *p)
{
    if (p[0x348] != 0 || p[0x349] != 0) {
        func_0208bfc0(p + 0x1c4);
        if (func_0208bfa0(p + 0x1c4) != 0) {
            func_0208b1a0((int *) p);
        }
    } else {
        func_0208bfc8(p + 0x1c4);
    }
    func_0208b0d8((void *) p);
}

void func_0208b1d4(UnkStruct_0208b1d4 *p)
{
    p->unk_04 = 4;
}

void func_0208b1b8(void *param)
{
    func_0208b9d8((char *) param + 0x2c4);
    func_0208b0d8(param);
}

void func_0208b1a0(int *r4)
{
    int r0;
    int r1;

    r0 = 3;
    r1 = 1;
    func_02011f74(r0, r1);
    r0 = 5;
    r4[1] = r0;
}

void func_0208b148(Struct0208b148 *self)
{
    if (self->unk_348 || self->unk_349) {
        func_0208b9d8(&self->unk_2C4);
    } else {
        func_0208b9d0(&self->unk_2C4);
        if (func_0208b9c0(&self->unk_2C4)) {
            func_02011f74(4, 1);
            func_0208b090(self);
        }
    }
    func_0208b0d8(self);
}
