/* wireless_icon: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02003df0 @ 0x02003df0, 0x10 bytes, Thumb
 * func_02003de0 @ 0x02003de0, 0x10 bytes, Thumb
 * func_02003dd0 @ 0x02003dd0, 0x10 bytes, Thumb
 * func_02003dc0 @ 0x02003dc0, 0x10 bytes, Thumb
 * func_02003dac @ 0x02003dac, 0x14 bytes, Thumb
 * func_02003da8 @ 0x02003da8, 0x2 bytes, Thumb
 * func_02003d8c @ 0x02003d8c, 0x1c bytes, Thumb
 * func_02003d88 @ 0x02003d88, 0x2 bytes, Thumb
 * func_02003d3c @ 0x02003d3c, 0x4a bytes, Thumb
 * func_02003cf4 @ 0x02003cf4, 0x48 bytes, Thumb
 * func_02003cc0 @ 0x02003cc0, 0x32 bytes, Thumb
 * func_02003c98 @ 0x02003c98, 0x28 bytes, Thumb
 * func_02003c38 @ 0x02003c38, 0x60 bytes, Thumb
 * func_02003bc8 @ 0x02003bc8, 0x70 bytes, Thumb
 * func_02003bc4 @ 0x02003bc4, 0x2 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
} UnkStruct_02003d8c;

struct Param {
    int unk_00;
    int unk_04;
    int unk_08;
};

struct Elem {
    int a;
    int b;
    int c;
};

struct UnkStruct_02003cf4 {
    int x;
    int y;
    struct Elem *arr;
};

typedef struct {
    unsigned char pad_00[0x10];
    int unk_10;
} UnkStruct_02003cc0;

typedef struct {
    char pad_00[0x15];
    unsigned char unk_15;
} UnkStruct_02003c98;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
} UnkStruct_02003c38;

typedef struct UnkStruct_02003bc8 {
    int unk_00;
    int val;
    unsigned int count;
    char pad_0C[9];
    unsigned char flag;
} UnkStruct_02003bc8;

extern unsigned char data_0213ff98[];
extern signed char data_020c7588[];
extern int func_020ec39c(void);
extern struct UnkStruct_02003cf4 data_020d5b3c;
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern int func_020ec1e8(void);
extern int func_0206fd04(void);
extern int func_0206fd10(void);
extern void func_02011f2c(unsigned char c);

void func_02003d8c(UnkStruct_02003d8c *param0);
void func_02003d88(void *object);
void func_02003d3c(int *arg0);
void func_02003cf4(struct Param *p);
int func_02003cc0(UnkStruct_02003cc0 *p);
void func_02003c38(UnkStruct_02003c38 *p);
void func_02003bc8(UnkStruct_02003bc8 *p);
void func_02003bc4(void *receiver);

void func_02003df0(void)
{
    func_02003d8c((UnkStruct_02003d8c *) (((unsigned char *) data_0213ff98)));
}

void func_02003de0(void)
{
    func_02003d88((void *) ((char *) data_0213ff98));
}

void func_02003dd0(void)
{
    func_02003d3c((int *) ((void *) data_0213ff98));
}

void func_02003dc0(void)
{
    func_02003cf4((struct Param *) ((void *) data_0213ff98));
}

void func_02003dac(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned int *p32 = (unsigned int *) r0;

    p32[0] = 3;
    p32[1] = 0;
    p32[2] = 0;
    p32[3] = 0;
    p32[4] = 0;
    p[0x14] = 0;
    p[0x15] = 0;
}

void func_02003da8(void *object) {}

void func_02003d8c(UnkStruct_02003d8c *param0)
{
    param0->unk_00 = 3;
    param0->unk_08 = 0;
    param0->unk_04 = data_020c7588[0];
    param0->unk_0C = 0;
    param0->unk_10 = 0;
    param0->unk_14 = 0;
    param0->unk_15 = 0;
}

void func_02003d88(void *object) {}

void func_02003d3c(int *arg0)
{
    int x = func_02003cc0((UnkStruct_02003cc0 *) arg0);
    if (x != 0) {
        int s = func_020ec39c();
        if (s == 1) {
            *arg0 = 2;
        } else if (s == 2) {
            *arg0 = 1;
        } else if (s == 3) {
            *arg0 = 0;
        } else {
            *arg0 = 3;
        }
    }
    func_02003c38((UnkStruct_02003c38 *) arg0);
    func_02003bc8((UnkStruct_02003bc8 *) arg0);
    func_02003bc4(arg0);
}

void func_02003cf4(struct Param *p)
{
    if (p->unk_08) {
        func_02088df8(0, data_020d5b3c.arr[p->unk_00].a, p->unk_04 + 0x80, 0x60, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

int func_02003cc0(UnkStruct_02003cc0 *p)
{
    unsigned int ok = 0;
    unsigned int v;
    v = (unsigned int) func_020ec1e8();
    if (v != 0) {
        v = (unsigned int) func_020ec1e8();
        if (v != 6) {
            ok = 1;
        }
    }
    if (ok > 0 && p->unk_10 == 0) {
        return 1;
    }
    return 0;
}

int func_02003c98(UnkStruct_02003c98 *obj)
{
    int r = func_020ec1e8();
    return obj->unk_15 == (r == 3 || r == 4);
}

void func_02003c38(UnkStruct_02003c38 *p)
{
    int a;
    int b;

    a = func_0206fd04() != 0;
    b = func_0206fd10();
    if (p->unk_10 > 0) {
        p->unk_10--;
    }
    if (p->unk_14) {
        if (p->unk_0C == 0x1000 && b < 0x1000) {
            p->unk_10 = 0x17;
        }
    } else if (a) {
        p->unk_08 = 0;
        p->unk_04 = (*(const char *) data_020c7588);
        p->unk_10 = 0xe;
    }
    p->unk_14 = a;
    p->unk_0C = b;
}

void func_02003bc8(UnkStruct_02003bc8 *p)
{
    int a, b;

    a = func_02003cc0((UnkStruct_02003cc0 *) p);
    b = func_02003c98((UnkStruct_02003c98 *) p);

    if (a && b) {
        if (p->count < 4) {
            p->count += 1;
            p->val = data_020c7588[p->count];
        }
    } else {
        if (p->count != 0) {
            p->count -= 1;
            p->val = data_020c7588[p->count];
        }
    }

    if (a && !b && p->count == 0) {
        p->flag = !p->flag;
        func_02011f2c(p->flag);
    }
}

void func_02003bc4(void *receiver) {}
