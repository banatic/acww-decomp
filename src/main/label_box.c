/* label_box: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8f74 @ 0x020a8f74, 0x14 bytes, Thumb
 * func_020a8f50 @ 0x020a8f50, 0x24 bytes, Thumb
 * func_020a8f2c @ 0x020a8f2c, 0x24 bytes, Thumb
 * func_020a8f14 @ 0x020a8f14, 0x18 bytes, Thumb
 * func_020a8ef4 @ 0x020a8ef4, 0x20 bytes, Thumb
 * func_020a8eec @ 0x020a8eec, 0x6 bytes, Thumb
 * func_020a8ecc @ 0x020a8ecc, 0x1e bytes, Thumb
 * func_020a8eac @ 0x020a8eac, 0x1e bytes, Thumb
 * func_020a8e8c @ 0x020a8e8c, 0x1e bytes, Thumb
 * func_020a8e4c @ 0x020a8e4c, 0x3e bytes, Thumb
 * func_020a8e04 @ 0x020a8e04, 0x48 bytes, Thumb
 * func_020a8db8 @ 0x020a8db8, 0x4c bytes, Thumb
 */

struct UnkStruct_020a8f74;

struct VTable {
    void *unk_00;
    void *p1;
    void *p2;
    int (*func)(struct UnkStruct_020a8f74 *);
};

struct UnkStruct_020a8f74 {
    struct VTable *vtable;
};

struct UnkStruct_020a8f50 {
    void *unk_00;        // offset 0x00
    char pad_04[0x78];   // offset 0x04, ends at 0x7c
    unsigned int unk_7C; // offset 0x7c
    unsigned int unk_80; // offset 0x80
};

typedef struct {
    void *unk_00;
    char pad_04[0x78];
    int unk_7C;
    int unk_80;
} UnkStruct_020a8f2c;

struct UnkStruct_020a8ef4 {
    void *vtable;
};

typedef struct {
    unsigned char pad_00[128];
    unsigned long unk_80;
} UnkStruct_020a8eec;

typedef struct {
    char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020a8ecc;

typedef struct UnkStruct_020a8eac {
    char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020a8eac;

struct UnkStruct_020a8e4c {
    char pad_00[0x38];
    unsigned char unk_38;
    char pad_39[0x7c - 0x39];
    int unk_7C;
};

typedef struct UnkStruct_020a8e04_2 UnkStruct_020a8e04_2;

typedef struct UnkStruct_020a8e04 {
    char pad_00[0x10];
    int unk_10;
    int unk_14;
    char pad_18[0x64];
    int unk_7C;
    UnkStruct_020a8e04_2 *unk_80;
} UnkStruct_020a8e04;

extern int func_020a8f88(int value);
extern void *func_02050d6c(void *, unsigned int, unsigned int, unsigned int);
extern void *func_02050cb4(void *, int, int, int);
extern void func_02050c84(void *);
extern void func_020edb3c(void *obj) __attribute__((arm));
extern unsigned char data_020e3dac[];
extern void func_02051340(UnkStruct_020a8ecc *obj);
extern void func_020515ac(UnkStruct_020a8ecc *obj);
extern void func_020511f8(UnkStruct_020a8eac *);
extern void func_02051568(void);
extern void func_020512d4(char *p, int arg);
extern void func_0205156c(char *p, int arg);
extern void func_020a8754(int *p);
extern void func_020a8764(int *p, int param);
extern unsigned char func_020a8308(int *p);
extern int func_02068bc8(int);
extern UnkStruct_020a8e04_2 data_021f44dc;
extern void func_020a9228(UnkStruct_020a8e04_2 *p, UnkStruct_020a8e04 *s);
extern void func_020a94a4(UnkStruct_020a8e04_2 *p);
extern void func_020a9354(UnkStruct_020a8e04_2 *p, int n);
extern int func_020a922c(UnkStruct_020a8e04_2 *p, int n);
extern void func_020a9220(UnkStruct_020a8e04_2 *p);

int func_020a8f74(struct UnkStruct_020a8f74 *obj)
{
    return func_020a8f88(obj->vtable->func(obj));
}

struct UnkStruct_020a8f50 *func_020a8f50(struct UnkStruct_020a8f50 *this, unsigned int a1, unsigned int a2, unsigned int a3)
{
    func_02050d6c(this, a1, a2, a3);
    this->unk_00 = ((char *) data_020e3dac);
    this->unk_7C = 0;
    this->unk_80 = 0;
    return this;
}

UnkStruct_020a8f2c *func_020a8f2c(UnkStruct_020a8f2c *param, int argument1, int argument2, int argument3)
{
    func_02050cb4(param, (int) argument1, (int) argument2, (int) argument3);
    param->unk_00 = ((char *) data_020e3dac);
    param->unk_7C = 0;
    param->unk_80 = 0;
    return param;
}

void *func_020a8f14(void *arg)
{
    *(int *) arg = (int) ((int *) data_020e3dac);
    func_02050c84(arg);
    return arg;
}

void *func_020a8ef4(struct UnkStruct_020a8ef4 *obj)
{
    obj->vtable = (void *) data_020e3dac;
    func_02050c84(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020a8eec(UnkStruct_020a8eec *p, unsigned long v)
{
    p->unk_80 = v;
}

void func_020a8ecc(UnkStruct_020a8ecc *obj)
{
    int value = obj->unk_7C;
    if (value == 1) {
        func_02051340(obj);
    } else if (value == 2) {
        func_020515ac(obj);
    }
}

void func_020a8eac(UnkStruct_020a8eac *arg0)
{
    if (arg0->unk_7C == 1) {
        func_020511f8(arg0);
    } else if (arg0->unk_7C == 2) {
        func_02051568();
    }
}

void func_020a8e8c(char *p, int arg)
{
    int state = *(int *) (p + 0x7c);

    if (state == 1) {
        func_020512d4(p, arg);
    } else if (state == 2) {
        func_0205156c(p, arg);
    }
}

/* FAKEMATCH: the empty if keeps both result words loaded before the first compare; the plain condition compares a before loading b */
void func_020a8e4c(struct UnkStruct_020a8e4c *self, int param2)
{
    int local[5];
    int a;
    int b;
    if (self->unk_7C == 1) {
        func_020a8754(local);
        func_020a8764(local, param2);
        a = local[0];
        if ((param2 && param2) && param2) {
        }
        b = local[1];
        if ((a == 0xff) && (b == 0)) {
            self->unk_38 = func_02068bc8((int) func_020a8308(local));
        }
    }
}

void func_020a8e04(UnkStruct_020a8e04 *self)
{
    UnkStruct_020a8e04_2 *ptr = self->unk_80;
    if (!ptr) {
        ptr = &data_021f44dc;
    }
    self->unk_7C = 1;
    func_020a9228(ptr, self);
    func_020a94a4(ptr);
    func_020a9354(ptr, self->unk_10);
    func_020a922c(ptr, self->unk_14);
    func_020a9220(ptr);
    self->unk_7C = 0;
}

int func_020a8db8(void *self)
{
    void *ptr;

    ptr = *(void **) ((char *) self + 0x80);
    if (ptr == 0) {
        ptr = (void *) ((int *) &data_021f44dc);
    }

    *(int *) ((char *) self + 0x7c) = 2;
    func_020a9228((UnkStruct_020a8e04_2 *) ptr, (UnkStruct_020a8e04 *) self);
    func_020a94a4((UnkStruct_020a8e04_2 *) ptr);
    func_020a9354((UnkStruct_020a8e04_2 *) ptr, *(int *) ((char *) self + 0x10));
    func_020a922c((UnkStruct_020a8e04_2 *) ptr, *(int *) ((char *) self + 0x14));
    func_020a9220((UnkStruct_020a8e04_2 *) ptr);

    *(int *) ((char *) self + 0x7c) = 0;
    return *(int *) ((char *) self + 0x68);
}
