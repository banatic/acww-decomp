/* vram_copy_task: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba01c @ 0x020ba01c, 0x20 bytes, Thumb
 * func_020ba004 @ 0x020ba004, 0x16 bytes, Thumb
 * func_020b9fd0 @ 0x020b9fd0, 0x32 bytes, Thumb
 * func_020b9f80 @ 0x020b9f80, 0x50 bytes, Thumb
 * func_020b9f30 @ 0x020b9f30, 0x50 bytes, Thumb
 * func_020b9eec @ 0x020b9eec, 0x44 bytes, Thumb
 * func_020b9ed8 @ 0x020b9ed8, 0x12 bytes, Thumb
 * func_020b9ec4 @ 0x020b9ec4, 0x14 bytes, Thumb
 * func_020b9e80 @ 0x020b9e80, 0x42 bytes, Thumb
 * func_020b9e58 @ 0x020b9e58, 0x28 bytes, Thumb
 * func_020b9e40 @ 0x020b9e40, 0x18 bytes, Thumb
 * func_020b9e2c @ 0x020b9e2c, 0x14 bytes, Thumb
 * func_020b9e08 @ 0x020b9e08, 0x22 bytes, Thumb
 * func_020b9df4 @ 0x020b9df4, 0x12 bytes, Thumb
 * func_020b9d3c @ 0x020b9d3c, 0xb6 bytes, Thumb
 */

struct data {
    unsigned char pad_00[0xe];
    unsigned char type;
    unsigned char pad_0F;
    int value;
};

struct UnkStruct_020b9f30 {
    int pad_00;
};

struct UnkStruct_020b9f30_2 {
    unsigned char pad_00[0xc];
    unsigned char a;
    unsigned char pad_0D;
    unsigned char b;
    unsigned char c;
    struct UnkStruct_020b9f30 sub;
};

struct UnkStruct_020b9eec_3 {
    int pad_00;
};

struct UnkStruct_020b9eec {
    char data[0x10];
    struct UnkStruct_020b9eec_3 sub;
};

struct UnkStruct_020b9eec_2 {
    int unk_00;
    int unk_04;
};

typedef struct {
    char pad[12];
} SubObject;

typedef struct {
    void *unk_00;
    char pad[12];
    SubObject sub1;
    SubObject sub2;
} UnkStruct_020b9e58;

extern void func_020ba1cc(void *);
extern void func_020ba1b0(void *);
extern char data_020e5928;
extern void func_020ba1bc(void *ptr);
extern void func_020ba13c(void *p);
extern void func_020ba184(void *p);
extern void func_020ba160(void *p);
extern void func_020ba1a8(void *, int, int, int);
extern unsigned char func_020ba12c(void *);
extern int func_020b9978(void *);
extern int func_020ba128(void *object);
extern char func_020ba118(struct UnkStruct_020b9eec_3 *sub);
extern int func_020b9960(int arg);
extern int func_02057a8c(unsigned char *);
extern int func_02057a7c(unsigned char *);
extern char data_020e591c[];
extern int func_02057a50(void *, int);
extern int func_020579f0(void *, int);
extern int func_02057988(void *, int);
extern int func_02057918(void *, int);
extern int func_02057a60(void *);

void func_020b9ed8(void *arg0);
void func_020b9ec4(int arg);

void *func_020ba01c(void *self)
{
    func_020ba1cc(self);
    *(void **) self = &data_020e5928;
    func_020ba1b0((char *) self + 0x10);
    return self;
}

void func_020ba004(void *ptr)
{
    void *p;
    p = ptr;
    func_020ba1bc(p);
    p = (char *) p + 0x10;
    func_020ba1b0(p);
}

int func_020b9fd0(struct data *obj)
{
    switch (obj->type) {
        case 0:
            func_020ba13c(&obj->value);
            break;
        case 1:
            func_020ba184(&obj->value);
            break;
        case 2:
            func_020ba160(&obj->value);
            break;
    }
    return 1;
}

int func_020b9f80(void *p0, int p1, int p2, int p3, unsigned char p4)
{
    func_020b9ed8(p0);
    ((unsigned char *) p0)[0xe] = 1;
    func_020ba1a8((char *) p0 + 0x10, p2, p1, p3);
    ((unsigned char *) p0)[0xf] = func_020ba12c((char *) p0 + 0x10);
    ((unsigned char *) p0)[0xc] = p4;
    if (func_020b9978(p0)) {
        return 1;
    }
    func_020ba004(p0);
    return 0;
}

int func_020b9f30(struct UnkStruct_020b9f30_2 *p0, int p1, int p2, int p3, unsigned char arg4)
{
    func_020b9ed8(p0);
    p0->b = 2;
    func_020ba1a8(&p0->sub, p2, p1, p3);
    p0->c = func_020ba128(&p0->sub);
    p0->a = arg4;
    if (func_020b9978(p0)) {
        return 1;
    } else {
        func_020ba004(p0);
        return 0;
    }
}

int func_020b9eec(struct UnkStruct_020b9eec *a, struct UnkStruct_020b9eec_2 *b, int c)
{
    func_020b9ed8((void *) a);
    a->data[0xe] = 0;
    func_020ba1a8((void *) (&a->sub), 0, (int) b, b->unk_04);
    a->data[0xf] = func_020ba118(&a->sub);
    a->data[0xc] = c;
    if (func_020b9978((void *) a) != 0) {
        return 1;
    }
    func_020ba004((void *) a);
    return 0;
}

void func_020b9ed8(void *arg0)
{
    void *r4;

    r4 = arg0;
    func_020b9ec4((int) r4);
    *(unsigned char *) ((unsigned int) r4 + 0xd) = 1;
}

void func_020b9ec4(int arg)
{
    func_020b9960(arg);
    func_020ba004((void *) arg);
}

int func_020b9e80(unsigned int a0, unsigned char *a1, int a2, unsigned int a3)
{
    unsigned char *base;
    unsigned char *p;
    unsigned int off;
    unsigned short c;
    unsigned short v;
    unsigned char *q;
    int r1v;
    int r2v;

    base = a1;
    off = *(unsigned int *) (base + 8);
    base += off;
    p = base + 4;
    c = *(unsigned short *) (base + 10);
    v = *(unsigned short *) (p + c);
    off = *(unsigned int *) (p + c + v * a2 + 4);
    q = base + off;
    r1v = func_02057a8c(q);
    r2v = func_02057a7c(q);
    return func_020b9f80((void *) a0, a3, r2v, r1v, 2);
}

UnkStruct_020b9e58 *func_020b9e58(UnkStruct_020b9e58 *obj)
{
    func_020ba1cc(obj);
    obj->unk_00 = data_020e591c;
    func_020ba1b0(&obj->sub1);
    func_020ba1b0(&obj->sub2);
    return obj;
}

void func_020b9e40(void *arg0)
{
    void *r4 = arg0;
    func_020ba1b0((char *) r4 + 0x10);
    func_020ba1b0((char *) r4 + 0x1c);
}

void func_020b9e2c(int x)
{
    func_020b9960(x);
    func_020b9e40((void *) x);
}

int func_020b9e08(void *arg0)
{
    unsigned char *p = (unsigned char *) arg0;
    if (p[0xe] == 3) {
        func_020ba184(p + 0x10);
        func_020ba160(p + 0x1c);
    }
    return 1;
}

void func_020b9df4(unsigned char *r4)
{
    unsigned char r0;

    func_020b9e2c((int) r4);
    r0 = 1;
    r4[0xd] = r0;
}

int func_020b9d3c(void *self, void *other, int arg2, void *arg3, int arg4, int arg5)
{
    unsigned char *s = (unsigned char *) self;
    unsigned char *node;
    int val2;
    unsigned char *p;
    int a;
    int b;
    unsigned char *ptr2;
    unsigned char *ptr;
    int c;
    void *ptr3;
    int d;
    int v0;
    int prod;
    unsigned short off;
    unsigned short val;
    ptr3 = arg3;
    func_020b9df4((unsigned char *) self);
    ptr2 = ((unsigned char *) other) + 8;
    node = ((unsigned char *) other) + (*((unsigned int *) ptr2));
    val2 = (long) arg5;
    v0 = func_02057a50(other, arg2);
    off = *((unsigned short *) (((unsigned char *) node) + 0xa));
    val = *((unsigned short *) ((((unsigned char *) node) + 4) + off));
    prod = val;
    prod = v0 * prod;
    p = ((((unsigned char *) node) + 4) + off) + prod;
    node = ((unsigned char *) node) + (*((unsigned int *) (p + 4)));
    a = func_020579f0(ptr3, arg4);
    b = func_02057988(ptr3, arg5);
    ptr = node;
    c = func_02057a8c((unsigned char *) ptr);
    d = func_02057918(arg3, val2);
    off = 3;
    s[0xe] = off;
    func_020ba1a8(s + 0x10, func_02057a7c((unsigned char *) ptr), a, c);
    func_020ba1a8(s + 0x1c, func_02057a60(ptr), b, d);
    s[0xf] = (unsigned char) ((int) func_020ba12c(s + 0x10) + func_020ba128(s + 0x1c));
    s[0xc] = 0;
    if (func_020b9978(s) != 0) {
        return 1;
    } else {
        func_020b9e40(s);
        return 0;
    }
}
