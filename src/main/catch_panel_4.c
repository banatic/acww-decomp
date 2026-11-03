/* catch_panel_4: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208d13c @ 0x0208d13c, 0x10 bytes, Thumb
 * func_0208d12c @ 0x0208d12c, 0x10 bytes, Thumb
 * func_0208d0bc @ 0x0208d0bc, 0x70 bytes, Thumb
 * func_0208d09c @ 0x0208d09c, 0x20 bytes, Thumb
 * func_0208d07c @ 0x0208d07c, 0x20 bytes, Thumb
 * func_0208d054 @ 0x0208d054, 0x28 bytes, Thumb
 * func_0208d04c @ 0x0208d04c, 0x8 bytes, Thumb
 * func_0208d03c @ 0x0208d03c, 0xe bytes, Thumb
 * func_0208d01c @ 0x0208d01c, 0x20 bytes, Thumb
 * func_0208d014 @ 0x0208d014, 0x6 bytes, Thumb
 * func_0208cffc @ 0x0208cffc, 0x18 bytes, Thumb
 * func_0208cfb0 @ 0x0208cfb0, 0x4c bytes, Thumb
 * func_0208cf8c @ 0x0208cf8c, 0x22 bytes, Thumb
 * func_0208cf84 @ 0x0208cf84, 0x6 bytes, Thumb
 * func_0208cf6c @ 0x0208cf6c, 0x18 bytes, Thumb
 * func_0208cf28 @ 0x0208cf28, 0x44 bytes, Thumb
 * func_0208cf00 @ 0x0208cf00, 0x28 bytes, Thumb
 * func_0208ce88 @ 0x0208ce88, 0x78 bytes, Thumb
 * func_0208ce68 @ 0x0208ce68, 0x20 bytes, Thumb
 */

struct VTable {
    int unk_00;
    int unk_04;
    int (*handler)(void *);
};

struct Object {
    struct VTable *vtable;
};

struct UnkStruct_0208d0bc {
    unsigned char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char unk_A5;
    unsigned char unk_A6;
    unsigned char unk_A7;
    unsigned char pad_A8[4];
    unsigned int unk_AC;
    unsigned int unk_B0;
    unsigned int unk_B4;
    unsigned char unk_B8[0x10];
    unsigned int unk_C8;
};

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208d014;

typedef struct {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    char pad_24[0x85];
    unsigned char unk_A9;
} UnkStruct_0208cfb0;

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208cf84;

typedef struct {
    unsigned char pad_00[0xC];
    unsigned char sub[0x14];
    int unk_20;
    unsigned char pad1[0xA9 - 0x20 - sizeof(int)];
    unsigned char unk_A9;
} UnkStruct_0208cf28;

typedef struct {
    int a;
    int b;
} TableEntry;

extern void func_0209df04(void *);
extern void func_0209e200(void *, short);
extern void func_020b8d74(int);
extern const short data_020d0a58[];
extern unsigned char data_020e54a8;
extern char data_020d5b3c[];
extern void func_0208c890(void *obj);
extern void func_0208a1f0(void *sub, void *src);
extern void func_0208a1ec(void *sub, int val);
extern void *func_0208a144(void *sub);
extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern void func_0208cc64(void *);
extern int func_0203ec98(void);
extern int func_02070070(void);
extern int func_0206fd04(void);
extern int func_0206fd10(void);
extern void func_0208cdf8(void *p);
extern void func_0208cd88(void *p);
extern void func_0208cd18(void *p);
extern void func_0208cca8(void *p);

void func_0208cfb0(UnkStruct_0208cfb0 *obj);
void func_0208cf84(UnkStruct_0208cf84 *p);
void func_0208cf28(UnkStruct_0208cf28 *param);
unsigned char func_0208ce88(unsigned char *self);
void func_0208ce68(void *p);

int func_0208d13c(struct Object *obj)
{
    return obj->vtable->handler(obj);
}

unsigned int func_0208d12c(void *arg0)
{
    unsigned int *ptr;
    unsigned int value;

    ptr = (unsigned int *) ((char *) arg0 + 0xb4);
    value = *ptr;
    if (value == 0) {
        return 1;
    }
    return 0;
}

void func_0208d0bc(struct UnkStruct_0208d0bc *p, int a1, int a2)
{
    p->unk_B4 = a1;
    p->unk_C8 = 0;
    if (a1 != 0) {
        func_0209df04(p->unk_B8);
        func_0209e200(p->unk_B8, data_020d0a58[a1]);
        p->unk_AC = 0;
        p->unk_B0 = 0;
        p->unk_A4 = 1;
        p->unk_A5 = 1;
        p->unk_A6 = 1;
        p->unk_A7 = 1;
    }
    if (a2 == 0) {
        int v = (a1 == 0) ? 2 : 1;
        func_020b8d74(v);
    }
}

// placeholder for pool constant if any
void func_0208d09c(void *self)
{
    if (*(int *) ((char *) self + 0xb4) != 0) {
        *(int *) ((char *) self + 0xac) = *(int *) ((char *) self + 0xac) + 1;
        *(char *) ((char *) self + 0xa6) = 1;
    }
}

// placeholder, not used
void func_0208d07c(unsigned char *r0)
{
    unsigned int *r1;
    unsigned int r2;

    r1 = (unsigned int *) (r0 + 0xb4);
    if (*r1 != 0) {
        r1 = (unsigned int *) (r0 + 0xb0);
        r2 = *r1 + 1;
        r1 = (unsigned int *) (r0 + 0xb0);
        *r1 = r2;
        r0[0xa7] = 1;
    }
}

void func_0208d054(unsigned char *arg0)
{
    unsigned char val;
    unsigned char val2;

    val2 = 1;
    arg0[0xa8] = val2;
    val = data_020e54a8;
    if (val != 1) {
        val2 = 0;
    }
    if (val2 == 0) {
        val = 0;
    } else {
        val = 1;
    }
    arg0[0xa9] = val;
    return;
}

void func_0208d04c(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (168))) + (0)) = 0;
}

int func_0208d03c(void *arg)
{
    if (*(int *) ((char *) arg + 0x20) == 0) {
        return 1;
    }
    return 0;
}

int func_0208d01c(void *p)
{
    return ((int) func_0208d12c(p) != 0) && (((int *) ((char *) p + 0xC8))[0] <= 0);
}

void func_0208d014(UnkStruct_0208d014 *p)
{
    p->unk_20 = 0;
}

void func_0208cffc(int param)
{
    if ((int) func_0208ce88((unsigned char *) param)) {
        func_0208cfb0((UnkStruct_0208cfb0 *) param);
    }
}

void func_0208cfb0(UnkStruct_0208cfb0 *obj)
{
    int idx;
    obj->unk_20 = 1;
    func_0208c890(obj);
    if (obj->unk_A9) {
        idx = 0x2b;
    } else {
        idx = 0x26;
    }
    func_0208a1f0(&obj->sub, &data_020d5b3c[idx * 8]);
    func_0208a1ec(&obj->sub, 1);
    func_0208a144(&obj->sub);
    func_0208ce68(obj);
}

void func_0208cf8c(void *param)
{
    void *ptr;
    int result;

    ptr = (void *) ((char *) param + 0xc);
    func_0208a0c8(ptr);
    ptr = (void *) ((char *) param + 0xc);
    result = func_0208a160(ptr);
    if (result != 0) {
        func_0208cf84((UnkStruct_0208cf84 *) param);
    }
}

void func_0208cf84(UnkStruct_0208cf84 *p)
{
    p->unk_20 = 2;
}

void func_0208cf6c(void *arg)
{
    void *r4 = arg;
    if ((int) func_0208ce88((unsigned char *) r4) == 0) {
        func_0208cf28((UnkStruct_0208cf28 *) r4);
    }
}

void func_0208cf28(UnkStruct_0208cf28 *param)
{
    int index;
    param->unk_20 = 3;
    if (param->unk_A9) {
        index = 0x2C;
    } else {
        index = 0x27;
    }
    func_0208a1f0(&param->sub, (void *) (&((TableEntry *) data_020d5b3c)[index]));
    func_0208a1ec(&param->sub, 1);
    func_0208a144(&param->sub);
}

void func_0208cf00(void *param)
{
    void *ptr;
    int result;

    ptr = (void *) ((char *) param + 0xc);
    func_0208a0c8(ptr);
    ptr = (void *) ((char *) param + 0xc);
    result = func_0208a160(ptr);
    if (result != 0) {
        func_0208cc64(param);
        func_0208d014((UnkStruct_0208d014 *) param);
    }
}

unsigned char func_0208ce88(unsigned char *self)
{
    unsigned char r6;
    int a, b, c, d;
    int r4, r7;

    r6 = self[0xa8];
    if (r6 != 0) {
        a = func_0203ec98();
        b = func_02070070();
        r4 = 0;
        if (a != 0 && b == 0) {
            r4 = 1;
        }
        r7 = 0;
        if (a != 0 && b != 0) {
            c = func_0206fd04();
            d = func_0206fd10();
            if (c != 0) {
                if (d < 0x1000) {
                    r7 = 1;
                }
            } else {
                r7 = 1;
            }
        }
        if (r4 != 0 || r7 != 0) {
            r6 = 0;
            if (r4 != 0) {
                *(int *) (self + 0xc8) = 0;
            }
        }
    } else {
        *(int *) (self + 0xc8) = 0;
    }
    return r6;
}

void func_0208ce68(void *p)
{
    func_0208cdf8(p);
    func_0208cd88(p);
    func_0208cd18(p);
    func_0208cca8(p);
}
