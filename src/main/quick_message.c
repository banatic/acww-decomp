/* quick_message: 28 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02039358 @ 0x02039358, 0x28 bytes, Thumb
 * func_0203931c @ 0x0203931c, 0x3c bytes, Thumb
 * func_02039310 @ 0x02039310, 0xc bytes, Thumb
 * func_02039304 @ 0x02039304, 0xc bytes, Thumb
 * func_020392ec @ 0x020392ec, 0x18 bytes, Thumb
 * func_020392e8 @ 0x020392e8, 0x2 bytes, Thumb
 * func_020392e4 @ 0x020392e4, 0x2 bytes, Thumb
 * func_020392dc @ 0x020392dc, 0x8 bytes, Thumb
 * func_020392a0 @ 0x020392a0, 0x3c bytes, Thumb
 * func_020391fc @ 0x020391fc, 0xa4 bytes, Thumb
 * func_0203919c @ 0x0203919c, 0x60 bytes, Thumb
 * func_02039128 @ 0x02039128, 0x74 bytes, Thumb
 * func_020390b4 @ 0x020390b4, 0x74 bytes, Thumb
 * func_020390a8 @ 0x020390a8, 0xc bytes, Thumb
 * func_0203909c @ 0x0203909c, 0xc bytes, Thumb
 * func_02039084 @ 0x02039084, 0x18 bytes, Thumb
 * func_02039080 @ 0x02039080, 0x2 bytes, Thumb
 * func_0203907c @ 0x0203907c, 0x2 bytes, Thumb
 * func_02039064 @ 0x02039064, 0x18 bytes, Thumb
 * func_02038eec @ 0x02038eec, 0x178 bytes, Thumb
 * func_02038ed0 @ 0x02038ed0, 0x1c bytes, Thumb
 * func_02038e94 @ 0x02038e94, 0x3c bytes, Thumb
 * func_02038e54 @ 0x02038e54, 0x40 bytes, Thumb
 * func_02038e10 @ 0x02038e10, 0x44 bytes, Thumb
 * func_02038de8 @ 0x02038de8, 0x28 bytes, Thumb
 * func_02038db8 @ 0x02038db8, 0x30 bytes, Thumb
 * func_02038d9c @ 0x02038d9c, 0x1c bytes, Thumb
 * func_02038d74 @ 0x02038d74, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x2f4];
    void *array[4];
} UnkStruct_02039358;

typedef struct {
    char data[0xB8];
} UnkStruct_0203931c;

typedef struct {
    char pad_00[4];
    UnkStruct_0203931c elements[4];
    int array1[4];
    int array2[4];
} Object;

typedef struct SomeObj {
    unsigned char pad_00[0x64];
    int count;
} SomeObj;

typedef struct UnkStruct_02038eec {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02038eec;

struct obj {
    void *vtable;
};

extern void func_02039e84(void *ptr);
extern void func_02039e44(UnkStruct_0203931c *p);
extern void func_020edb3c(void *self);
extern unsigned char data_020da5c8[];
extern unsigned int data_020ccf94;
extern int func_02073d90(void *);
extern int func_02073dd4(void *, int);
extern void func_020771cc(int, int, int, int);
extern const char data_021c675e[];
extern const char data_021c676a[];
extern void func_0203a2f0(char *dst, const char *src, int n);
extern void func_0203a2dc(char *dst);
extern void *func_0203a3a4(char *dst, const char *src, int n);
extern void *func_0203a38c(char *dst);
extern void *func_0203a344(void *p);
extern void func_0203a330(void *p);
extern void *func_0203a404(void *p);
extern void *func_0203a3ec(void *p);
extern int func_02051984(void *a, void *b);
extern int func_020a8a70(void *a, void *b, int c, int d);
extern void func_020398e8(int i, void *a, void *b);
extern void *func_020738bc(void *a, void *b);
extern int func_020b65c4(void);
extern void MI_CpuCopy8(void *a, void *b, int c);
extern unsigned char data_020ca154[];
extern unsigned char data_021c675c[];
extern void func_0205195c(void *);
extern int func_020a87e0(void *, void *);
extern int func_02051880(void *, void *);
extern int func_0207762c(void *);
extern int func_020984e8(void);
extern void *func_02094fd4(int *);
extern int func_02099870(int);
extern void *func_02095074(int, int *);
extern int func_020b4980(int *, unsigned char *, int);
extern void func_0200467c(int);
extern void *func_02094fbc(int *);
extern int data_021c6730;
extern unsigned char data_020da5e8[];
extern int func_020960d8(int);
extern int func_0203ec98(void);
extern u16 data_021fbe40[];
extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern void *func_020397a0(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020da674[];
extern void *func_0203977c(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern void func_02039404(void *);
extern int func_02011ec8(void);
extern void func_020393b4(void *);
extern void func_02039380(void *);
extern void func_020393ec(void *);

void func_020391fc(void);
int func_0203919c(char *p);
void func_02038eec(int argument);
void *func_02038e94(void *arg);

void func_02039358(UnkStruct_02039358 *a)
{
    int i = 0;
    do {
        if (a->array[i] != 0) {
            func_02039e84(a->array[i]);
        }
        i++;
    } while (i < 4);
}

void func_0203931c(Object *obj)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_02039e44(&obj->elements[i]);
        obj->array1[i] = 0;
        obj->array2[i] = 0;
    }
}

void func_02039310(void **pp)
{
    *pp = ((char *) data_020da5c8);
}

void func_02039304(int **ptr)
{
    *ptr = ((int *) data_020da5c8);
}

void *func_020392ec(void *self)
{
    *(void **) self = (void *) data_020da5c8;
    func_020edb3c(self);
    return self;
}

void func_020392e8(void *receiver) {}

void func_020392e4(void *receiver) {}

void func_020392dc(void *receiver)
{
    func_020391fc();
}

void func_020392a0(int param1, int param2)
{
    int r5 = param1;
    int r4 = param2;
    void *r6;
    int r0;

    if (r5 < 4) {
        r6 = (void *) data_020ccf94;
        r0 = func_02073d90(r6);
        if (r0 != 0) {
            r0 = func_02073dd4(r6, r5);
            if (r0 != 0) {
                r5 += 0x14;
                func_020771cc(r5, r4, 0, 1);
            }
        }
    }
}

void func_020391fc(void)
{
    SomeObj *obj = (*(SomeObj **) &data_020ccf94);
    int count = obj->count;
    int i, zero;
    struct {
        char m0[0xc];
        char m1[0x18];
        char m2[0x14];
        char m3[0x34];
    } tmp;

    if (!func_02073d90((void *) obj)) {
        return;
    }

    i = 0;
    zero = i;

    for (; i < 4; i++) {
        if (i == count) {
            continue;
        }
        if (!func_02073dd4((void *) obj, i)) {
            continue;
        }
        if (!func_0203919c((char *) i)) {
            continue;
        }

        func_0203a2f0(tmp.m0, data_021c675e, 6);
        func_0203a3a4(tmp.m1, data_021c676a, 0x10);
        func_0203a344(tmp.m2);
        func_0203a404(tmp.m3);
        func_02051984(tmp.m2, tmp.m0);
        func_020a8a70(tmp.m3, tmp.m1, zero, zero);
        func_020398e8(i, tmp.m2, tmp.m3);
        func_0203a3ec(tmp.m3);
        func_0203a330(tmp.m2);
        func_0203a38c(tmp.m1);
        func_0203a2dc(tmp.m0);
    }
}

int func_0203919c(char *p)
{
    char *result;
    unsigned char c;
    int res;

    result = (char *) func_020738bc((*(void **) &data_020ccf94), p + 0x14);
    c = *result;
    if (c) {
        res = func_020b65c4();
        if (res == 0x2e || res == 0x0c || res == 0x0d || res == 0x0e || res == 0x2f) {
            c = 0;
        } else {
            MI_CpuCopy8(result, (void *) data_021c675c, 0x2e);
        }
        MI_CpuCopy8((void *) data_020ca154, result, 1);
    }
    return c;
}

void *func_02039128(void *a, void *b, void *c)
{
    struct {
        char buf1[16];
        char pad1[8];
        char buf2[6];
        char pad2[10];
    } locals;
    int temp;

    func_0203a3a4((char *) locals.buf1, (const char *) data_021c676a, 16);
    func_0203a2f0((char *) locals.buf2, (const char *) data_021c675e, 6);
    func_0205195c(locals.buf1);
    func_0205195c(locals.buf2);
    func_020a87e0(locals.buf1, (char *) c + 0x54);
    func_02051880(locals.buf2, (char *) c + 0x88);
    (*(char *) data_021c675c) = 1;
    temp = func_0207762c(b);
    MI_CpuCopy8(((char *) data_021c675c), a, temp);
    func_0203a2dc((char *) locals.buf2);
    return func_0203a38c((char *) locals.buf1);
}

void func_020390b4(void)
{
    unsigned char local3;
    int local1[8];
    int local2[13];
    int result;

    result = func_020984e8();
    if (data_021c6730 > 0) {
        return;
    }
    if (result == 0) {
        return;
    }

    func_02094fd4(local1);
    func_0203a404((void *) local2);
    func_02095074(func_02099870(result), local1);
    local3 = 0xEF;
    func_020b4980(local2, &local3, 0);
    func_020398e8((*(int **) &data_020ccf94)[0x19], (void *) local1, (void *) local2);
    func_0200467c(0x32);
    data_021c6730 = 0x1e;
    func_0203a3ec((void *) local2);
    func_02094fbc(local1);
}

void func_020390a8(int **ptr)
{
    *ptr = ((int *) data_020da5e8);
}

void func_0203909c(void **ptr)
{
    *ptr = ((char *) data_020da5e8);
}

void *func_02039084(void *p)
{
    *(void **) p = (void *) data_020da5e8;
    func_020edb3c(p);
    return p;
}

void func_02039080(void *receiver) {}

void func_0203907c(void *receiver) {}

void func_02039064(int arg)
{
    if (data_021c6730 > 0) {
        data_021c6730--;
    }
    func_02038eec(arg);
}

void func_02038eec(int argument)
{
    int f0;
    int res5;
    int v8;
    int vc;
    UnkStruct_02038eec *obj;
    u8 cmd;
    int buf1[13];
    int buf2[8];
    int r;
    int d;
    int skip;
    u16 val;
    int r7;
    int r6;
    int r4;
    int r5;
    int r2;

    r = func_020960d8(4);
    v8 = 1;
    if (r != 0x28 && r != 0x2b && r != 8 && r != 9) {
        v8 = 0;
    }

    val = data_021fbe40[1];

    if (val & 4) {
        f0 = 1;
    } else {
        f0 = 0;
    }

    if (val & 0x400) {
        r7 = 1;
    } else {
        r7 = 0;
    }

    if (val & 0x800) {
        r6 = 1;
    } else {
        r6 = 0;
    }

    if (val & 1) {
        r4 = 1;
    } else {
        r4 = 0;
    }

    if (val & 2) {
        r5 = 1;
    } else {
        r5 = 0;
    }

    vc = 1;
    if ((val & 8) == 0 && f0 == 0 && r7 == 0 && r6 == 0 && r4 == 0 && r5 == 0) {
        vc = 0;
    }

    obj = (*(UnkStruct_02038eec **) &data_020ccf94);
    res5 = func_02073d90((void *) obj);
    if (func_0203ec98() == 0) {
        d = 1;
    } else {
        d = 0;
    }

    if (data_021c6730 > 0) {
        return;
    }
    if (v8 == 0 || vc == 0 || res5 == 0 || d == 0) {
        return;
    }

    func_0203a404(buf1);

    skip = 0;
    if (f0 != 0) {
        r2 = 0xf0;
    } else if (r7 != 0) {
        r2 = 0xf1;
    } else if (r6 != 0) {
        r2 = 0xf2;
    } else if (r4 != 0) {
        r2 = 0xf3;
    } else if (r5 != 0) {
        r2 = 0xf4;
    } else {
        r2 = 0xef;
        if (obj->unk_64 != 0) {
            skip = 1;
        }
    }

    if (skip == 0) {
        cmd = (u8) r2;
        func_020b4980((int *) buf1, (unsigned char *) (&cmd), 0);
        func_02094fd4((int *) buf2);
        func_02095074(func_02099870((int) func_020984e8()), (int *) buf2);
        func_020398e8(obj->unk_64, buf2, buf1);
        func_0200467c(0x32);
        data_021c6730 = 0x1e;
        func_02094fbc((int *) buf2);
    }
    func_0203a3ec(buf1);
}

void func_02038ed0(void)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (func_020edf70(0x35c))) != 0) {
        func_02038e94(condition_value0);
    }
}

void *func_02038e94(void *arg)
{
    func_020ee660(arg);
    *((unsigned int *) arg) = (unsigned int) data_020da13c;
    *((unsigned int *) arg) = (unsigned int) data_020da674;
    func_020390a8((int **) ((char *) arg + 0x50));
    func_020397a0((char *) arg + 0x54);
    func_02039310((void **) ((char *) arg + 0x358));
    return arg;
}

void *func_02038e54(void *self)
{
    char *p;
    struct obj *o = (struct obj *) self;
    o->vtable = (void *) data_020da674;
    func_02039304((int **) ((char *) self + 0x358));
    p = (char *) self;
    p += 0x54;
    func_0203977c(p);
    p = (char *) self;
    p += 0x50;
    func_0203909c((void **) p);
    o->vtable = (void *) data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_02038e10(void *this)
{
    *(unsigned int *) this = (unsigned int) ((char *) data_020da674);
    func_02039304((int **) ((char *) this + 0x358));
    func_0203977c((char *) this + 0x54);
    func_0203909c((void **) ((char *) this + 0x50));
    *(unsigned int *) this = (unsigned int) ((char *) data_020da13c);
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}

int func_02038de8(void *param)
{
    void *r4 = param;
    func_02039080((char *) r4 + 0x50);
    func_02039404((char *) r4 + 0x54);
    func_020392e8((char *) r4 + 0x358);
    return 1;
}

int func_02038db8(void *param)
{
    void *r4 = param;
    func_02039064((int) ((char *) param + 0x50));
    if (func_02011ec8() != 0) {
        func_020393b4((char *) r4 + 0x54);
    }
    func_020392dc((char *) r4 + 0x358);
    return 1;
}

int func_02038d9c(void *arg0)
{
    void *r4;
    int r0;

    r4 = arg0;
    r0 = func_02011ec8();
    if (r0 != 0) {
        r4 = (char *) r4 + 0x54;
        func_02039380(r4);
    }
    return 1;
}

int func_02038d74(void *param)
{
    func_020392e4((char *) param + 0x358);
    func_020393ec((char *) param + 0x54);
    func_0203907c((char *) param + 0x50);
    return 1;
}
