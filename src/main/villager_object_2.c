/* villager_object_2: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209bb48 @ 0x0209bb48, 0x20 bytes, Thumb
 * func_0209bb30 @ 0x0209bb30, 0x18 bytes, Thumb
 * func_0209baf4 @ 0x0209baf4, 0x3c bytes, Thumb
 * func_0209bae4 @ 0x0209bae4, 0x10 bytes, Thumb
 * func_0209bac0 @ 0x0209bac0, 0x22 bytes, Thumb
 * func_0209ba7c @ 0x0209ba7c, 0x44 bytes, Thumb
 * func_0209b9cc @ 0x0209b9cc, 0xb0 bytes, Thumb
 * func_0209b998 @ 0x0209b998, 0x32 bytes, Thumb
 * func_0209b920 @ 0x0209b920, 0x76 bytes, Thumb
 * func_0209b91c @ 0x0209b91c, 0x2 bytes, Thumb
 * func_0209b914 @ 0x0209b914, 0x6 bytes, Thumb
 * func_0209b90c @ 0x0209b90c, 0x6 bytes, Thumb
 * func_0209b908 @ 0x0209b908, 0x4 bytes, Thumb
 * func_0209b8d0 @ 0x0209b8d0, 0x38 bytes, Thumb
 * func_0209b8c8 @ 0x0209b8c8, 0x8 bytes, Thumb
 * func_0209b8c4 @ 0x0209b8c4, 0x4 bytes, Thumb
 * func_0209b8bc @ 0x0209b8bc, 0x6 bytes, Thumb
 * func_0209b8a4 @ 0x0209b8a4, 0x18 bytes, Thumb
 * func_0209b890 @ 0x0209b890, 0x12 bytes, Thumb
 * func_0209b878 @ 0x0209b878, 0x16 bytes, Thumb
 * func_0209b870 @ 0x0209b870, 0x8 bytes, Thumb
 */

typedef struct {
    char pad_00[0x0C];
    char sub[0x20];
    unsigned short unk_2C;
} UnkStruct_0209bb48;

typedef struct {
    unsigned char pad_00[0x2a];
    unsigned char unk_2A;
} UnkStruct_0209bac0;

typedef struct {
    unsigned char pad_00[42];
    unsigned char unk_2A;
} UnkStruct_0209b914;

typedef struct {
    unsigned char pad_00[42];
    unsigned char unk_2A;
} UnkStruct_0209b90c;

typedef struct {
    unsigned char pad_00[47];
    unsigned char unk_2F;
} UnkStruct_0209b8bc;

extern void func_0209bd80(void *);
extern void *func_0209529c(void *);
extern int func_0209526c(void *addr);
extern void func_0209bd7c(void *addr);
extern void func_0209bd5c(void *);
extern void func_0209bd30(int a, int b, int c, int d);
extern void func_0209bb90(int a, int b);
extern void func_0209bb68(int a, unsigned short *b);
extern void func_02095238(int a);
extern int func_0209bc40(int);
extern int func_020535f0(unsigned short *);
extern void func_0209525c(int, unsigned int);
extern void *func_0209bc20(void *record);
extern void func_0209e474(int);
extern void func_0209bb74(int, int);
extern int func_0209bd44(void *);
extern int func_0209bd04(int);
extern int func_0209bba0(int);
extern int func_0209b64c(int);
extern int func_0209bd10(int);
extern int func_0209bcd4(int *, int);
extern int data_020d1a7c[];

void *func_0209b91c(void *object);
unsigned char func_0209b914(UnkStruct_0209b914 *p);
void func_0209b90c(UnkStruct_0209b90c *p, unsigned char v);
int func_0209b908(int p0);
int func_0209b8d0(int param);
int func_0209b8c4(int p0);
void func_0209b8a4(void *arg0, unsigned char arg1);
void func_0209b870(int p0);

UnkStruct_0209bb48 *func_0209bb48(UnkStruct_0209bb48 *arg)
{
    func_0209bd80(arg);
    func_0209529c(arg->sub);
    arg->unk_2C = 0xFFF1;
    return arg;
}

void *func_0209bb30(void *addr)
{
    void *self = addr;
    func_0209526c((char *) self + 12);
    func_0209bd7c(self);
    return self;
}

void func_0209baf4(void *arg)
{
    func_0209bd5c(arg);
    func_02095238((int) ((char *) arg + 0xc));
    *((unsigned char *) ((char *) arg + 0x2a)) = 7;
    *((unsigned short *) ((char *) arg + 0x2c)) = 0xfff1;
    *((unsigned char *) ((char *) arg + 0x2e)) = 0;
    *((unsigned char *) ((char *) arg + 0x2f)) = 0x18;
    *((unsigned char *) ((char *) arg + 0x30)) = 0;
}

void func_0209bae4(int a, int b, int c)
{
    func_0209bd30(a, b, c, 0);
}

int func_0209bac0(UnkStruct_0209bac0 *a, int b, int c)
{
    func_0209baf4((void *) a);
    func_0209bae4((int) a, b, c);
    a->unk_2A = 0;
    return 0;
}

void func_0209ba7c(void *param)
{
    unsigned short local;
    func_0209bb90((int) func_0209b91c(param), 0);
    local = 0xfff1;
    func_0209bb68((int) func_0209b91c(param), &local);
    func_02095238(func_0209b908((int) param));
    *(unsigned short *) func_0209b8c4((int) param) = 0xfff1;
}

void func_0209b9cc(unsigned int r0, unsigned int r1, unsigned short *r2, unsigned int r3, unsigned char stackbyte)
{
    if (stackbyte != 0) {
        func_0209bac0((UnkStruct_0209bac0 *) r0, r1, (int) r2);
    } else {
        func_0209bb90((int) func_0209b91c((void *) r0), 0);
        func_0209bb68((int) func_0209b91c((void *) r0), r2);
        if (func_0209bc40((int) func_0209b91c((void *) r0)) == 2) {
            if ((int) func_0209b914((UnkStruct_0209b914 *) r0) == 2) {
                unsigned short v = *r2;
                int flag = 0;
                if ((unsigned int) v >= 0x450cU && (unsigned int) v <= 0x45dbU) {
                    flag = 1;
                }
                if (flag != 0) {
                    func_0209b8a4((void *) r0, (unsigned char) func_020535f0(r2));
                }
            }
        }
    }
    if (r3 != 0) {
        func_0209525c(func_0209b908(r0), r3);
        func_0209e474((int) func_0209bc20((void *) (int) func_0209b91c((void *) r0)));
        func_0209bb74((int) func_0209b91c((void *) r0), 0);
    } else {
        func_02095238(func_0209b908(r0));
    }
}

void func_0209b998(void *object)
{
    int r4;
    int r0;

    r4 = (int) func_0209b91c(object);
    r0 = func_0209bd44((void *) r4);
    if (r0 != 0) {
        r0 = func_0209bd04(r4);
        if (r0 == 0) {
            r0 = func_0209bba0(r4);
            if (r0 == 1) {
                func_0209bb90(r4, 2);
            }
        }
    }
}

void func_0209b920(int arg)
{
    int f;
    int limit;
    int idx;
    unsigned int cond;

    f = (int) func_0209b91c((void *) arg);
    if (func_0209bd44((void *) f) == 0) {
        return;
    }
    if (func_0209bd04(f) != 0) {
        return;
    }
    limit = func_0209b8d0((int) func_0209bc40(f));
    idx = (int) func_0209b914((UnkStruct_0209b914 *) arg);
    if (idx >= limit - 1) {
        return;
    }
    if (func_0209bc40(f) == 4) {
        f = func_0209b64c(arg);
    } else {
        f = 1;
    }
    func_0209ba7c((void *) arg);
    if (f != 0) {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        func_0209b90c((UnkStruct_0209b90c *) arg, (unsigned char) (idx + 1));
    }
}

void *func_0209b91c(void *object)
{
    return object;
}

unsigned char func_0209b914(UnkStruct_0209b914 *p)
{
    return p->unk_2A;
}

void func_0209b90c(UnkStruct_0209b90c *p, unsigned char v)
{
    p->unk_2A = v;
}

int func_0209b908(int p0)
{
    return ((int) (p0) + (12));
}

int func_0209b8d0(int param)
{
    if (func_0209bd10(param) == 0) {
        int idx = 0;
        if (func_0209bcd4(&idx, param) != 0) {
            return data_020d1a7c[idx];
        }
    }
    return 0;
}

void *func_0209b8c8(void *record)
{
    return func_0209bc20(record);
}

int func_0209b8c4(int p0)
{
    return ((int) (p0) + (44));
}

unsigned char func_0209b8bc(UnkStruct_0209b8bc *p)
{
    return p->unk_2F;
}

void func_0209b8a4(void *arg0, unsigned char arg1)
{
    unsigned char *ptr;

    func_0209b870((int) arg0);
    ptr = (unsigned char *) arg0 + 0x2f;
    *ptr = arg1;
}

void func_0209b890(unsigned char *p, int bit)
{
    p[0x30] |= (1 << bit);
}

int func_0209b878(unsigned char *param0, unsigned int param1)
{
    if (param1 < 3) {
        if ((param0[0x30] >> param1) & 1) {
            return 1;
        }
    }
    return 0;
}

void func_0209b870(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (48))) + (0)) = 0;
}
