/* scene_object_3: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201c2c8 @ 0x0201c2c8, 0x4c bytes, Thumb
 * func_0201c2b0 @ 0x0201c2b0, 0x18 bytes, Thumb
 * func_0201c2a4 @ 0x0201c2a4, 0xc bytes, Thumb
 * func_0201c280 @ 0x0201c280, 0x24 bytes, Thumb
 * func_0201c274 @ 0x0201c274, 0xc bytes, Thumb
 * func_0201c250 @ 0x0201c250, 0x22 bytes, Thumb
 * func_0201c24c @ 0x0201c24c, 0x2 bytes, Thumb
 * func_0201c248 @ 0x0201c248, 0x2 bytes, Thumb
 * func_0201c244 @ 0x0201c244, 0x2 bytes, Thumb
 * func_0201c208 @ 0x0201c208, 0x3a bytes, Thumb
 * func_0201c194 @ 0x0201c194, 0x74 bytes, Thumb
 * func_0201c174 @ 0x0201c174, 0x20 bytes, Thumb
 * func_0201c154 @ 0x0201c154, 0x20 bytes, Thumb
 * func_0201c148 @ 0x0201c148, 0xc bytes, Thumb
 * func_0201c144 @ 0x0201c144, 0x2 bytes, Thumb
 */

struct UnkStruct_0201c280 {
    char pad_00[0x634];
    int unk_634;
};

typedef struct UnkStruct_0201c250 UnkStruct_0201c250;

typedef struct {
    char pad_00[0x78];
    int (*func)(UnkStruct_0201c250 *);
} VTable;

struct UnkStruct_0201c250 {
    VTable *vtable;
};

typedef struct {
    char pad_00[0x94];
    signed short unk_94;
} UnkStruct_0201c208;

typedef struct UnkStruct_0201c174 UnkStruct_0201c174;

typedef struct ObjVtbl ObjVtbl;

struct ObjVtbl {
    char pad_00[0x78];
    int (*func)(UnkStruct_0201c174 *);
};

struct UnkStruct_0201c174 {
    ObjVtbl *vtbl;
};

typedef struct UnkStruct_0201c154 UnkStruct_0201c154;

typedef struct Vtbl Vtbl;

struct Vtbl {
    unsigned char pad_00[0x78];
    int (*method)(UnkStruct_0201c154 *);
};

struct UnkStruct_0201c154 {
    Vtbl *vtbl;
};

extern int func_02096614(unsigned char *, unsigned int *, unsigned int *, int, void *);
extern void *func_0200322c(void *, unsigned int *);
extern void *func_02096190(void *);
extern void *func_0201c314(void *, void *);
extern void func_020160d0(int, struct UnkStruct_0201c280 *);
extern void func_0201af58(void *dest, void *src, int param, int size);
extern int func_0201ae8c(void *data);
extern int func_0201ae40(void *a);
extern int data_021c16c0;
extern int data_021c16b4;
extern int data_020c8178[];
extern int data_020c8190[];
extern unsigned short data_020c80f8;

void *func_0201c2c8(void *arg0, void *arg1)
{
    void *result = 0;
    unsigned char flag = 0;
    unsigned int dataA[2];
    unsigned int dataB[2];

    if (func_02096614(&flag, dataA, dataB, -1, arg1)) {
        arg0 = (unsigned char *) arg0 + 0x5c;
        result = func_0200322c(arg0, dataA);
    } else {
        void *p;

        p = func_02096190(arg1);
        if (p != 0) {
            result = func_0201c314(arg0, p);
        }
    }

    return result;
}

int func_0201c2b0(struct UnkStruct *r4, void *argument1)
{
    int r0;
    int r1;
    int result;

    r0 = (int) func_0201c314((void *) r4, (void *) argument1);
    r1 = *(short *) ((char *) r4 + 0x8e);
    result = r0 - r1;
    result = (result << 16) >> 16;
    return result;
}

int func_0201c2a4(int a, int b)
{
    return (int) func_02096190((void *) b);
}

void func_0201c280(struct UnkStruct_0201c280 *s, int value)
{
    s->unk_634 = value;
    if (s->unk_634 != 0) {
        func_020160d0(s->unk_634, s);
    }
}

unsigned int func_0201c274(void *ptr)
{
    return *(unsigned int *) ((char *) ptr + 0x634);
}

int func_0201c250(UnkStruct_0201c250 *this)
{
    int result = 2;
    int val;

    val = this->vtable->func(this);
    switch (val) {
        case 0:
            result = 0;
            break;
        case 1:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

void func_0201c24c(void) {}

void func_0201c248(void *object)
{
    (void) object;
}

void func_0201c244(void *object)
{
    (void) object;
}

int func_0201c208(UnkStruct_0201c208 *in, int *out, int arg2)
{
    int local[3];
    int ret = 0;
    char *p;

    p = (char *) in;
    p += 0x5c;
    func_0201af58(local, p, arg2, in->unk_94);
    if (func_0201ae8c(local) != 1) {
        out[0] = local[0];
        out[1] = local[1];
        out[2] = local[2];
        ret = 1;
    }
    return ret;
}

int func_0201c194(char *self, int *out)
{
    int ret;
    int *src;
    int m;

    m = func_0201ae40(self + 0x3a8);
    ret = 0;
    src = (int *) (self + 0x5c);
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    switch (m) {
        case 3:
            ret = 1;
            break;
        case 1:
            if (func_0201c208((UnkStruct_0201c208 *) self, (int *) out, (int) (&data_021c16c0))) {
                ret = 2;
            } else {
                ret = 1;
            }
            break;
        case 2:
            if (func_0201c208((UnkStruct_0201c208 *) self, (int *) out, (int) (&data_021c16b4))) {
                ret = 2;
            } else {
                ret = 1;
            }
            break;
    }
    return ret;
}

int func_0201c174(UnkStruct_0201c174 *obj)
{
    int index = obj->vtbl->func(obj);
    if (index >= 2) {
        index = 0;
    }
    return data_020c8178[index];
}

int func_0201c154(UnkStruct_0201c154 *obj)
{
    int res;
    res = obj->vtbl->method(obj);
    if (res >= 2) {
        res = 0;
    }
    return data_020c8190[res];
}

unsigned short func_0201c148(void *object)
{
    (void) object;
    return data_020c80f8;
}

void func_0201c144(void) {}
