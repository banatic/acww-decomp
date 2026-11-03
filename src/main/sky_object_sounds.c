/* sky_object_sounds: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020be64c @ 0x020be64c, 0x60 bytes, Thumb
 * func_020be628 @ 0x020be628, 0x24 bytes, Thumb
 * func_020be600 @ 0x020be600, 0x26 bytes, Thumb
 * func_020be5d0 @ 0x020be5d0, 0x30 bytes, Thumb
 * func_020be5a0 @ 0x020be5a0, 0x30 bytes, Thumb
 * func_020be568 @ 0x020be568, 0x38 bytes, Thumb
 */

#include "types.h"

typedef union {
    int a;
    int b;
} UnkStruct_020be64c;

typedef struct {
    UnkStruct_020be64c u;
    int y;
    int z;
} Elem;

typedef struct {
    Elem array1[8];
    Elem array2[8];
    char flag;
} UnkStruct_020be64c_2;

struct SomeItem {
    u8 data[12];
};

struct SomeObj {
    struct SomeItem items[8];
    u8 pad_60[0x60];
    u8 flag_C0;
};

typedef struct {
    int a, b, c;
} Src;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_020012dc(void *);
extern void func_020012e8(void *);
extern unsigned char data_0213efe8[];
extern unsigned char data_0213f03c[];
extern int func_0200430c(void *);
extern void func_02004280(struct SomeItem *item);
extern void func_020042a0(char *dst, void *c);
extern void func_02004290(void *entry, int param3);
extern void func_020042b0(struct SomeItem *a, struct SomeItem *b);

UnkStruct_020be64c_2 *func_020be64c(UnkStruct_020be64c_2 *obj)
{
    Elem *p;

    p = obj->array1;
    do {
        p->u.a = (unsigned int) data_0213efe8;
        p->u.b = (unsigned int) data_0213f03c;
        p++;
    } while (p != &obj->array1[8]);

    __cxa_vec_ctor((void *) (&obj->array2[0]), 8, 12, (void (*)(void *)) func_020012e8, (void (*)(void *)) func_020012dc);

    obj->flag = 0;

    for (p = obj->array2; p < &obj->array2[8]; p++) {
        p->u.a = 0;
        p->y = 0;
        p->z = 0;
    }

    return obj;
}

void func_020be628(void *arg0)
{
    unsigned char *p;
    unsigned char *end;
    unsigned char *base;
    unsigned char *q;

    base = (unsigned char *) arg0;
    p = base;
    end = base + 0x60;
    q = base;
    while (p < end) {
        func_0200430c(p);
        p += 0xc;
    }
    q[0xc0] = 1;
}

void func_020be600(struct SomeObj *obj)
{
    struct SomeItem *p;

    obj->flag_C0 = 0;
    for (p = &obj->items[7]; p >= obj->items; p--) {
        func_02004280(p);
    }
}

void func_020be5d0(char *self, int idx, void *c, Src *src)
{
    if (*(unsigned char *) (self + 0xc0)) {
        int off = idx * 0xc;
        volatile char *base = self;
        func_020042a0((char *) base + off, c);
        {
            int v0 = *(volatile int *) &src->a;
            *(int *) (base + off + 0x60) = v0;
        }
        *(int *) (base + off + 0x64) = src->b;
        *(int *) (base + off + 0x68) = src->c;
    }
}

void func_020be5a0(char *self, int idx, int param3, Src *src)
{
    if (*(unsigned char *) (self + 0xc0)) {
        int off = idx * 0xc;
        volatile char *base = self;
        func_02004290((char *) base + off, param3);
        {
            int v0 = *(volatile int *) &src->a;
            *(int *) (base + off + 0x60) = v0;
        }
        *(int *) (base + off + 0x64) = src->b;
        *(int *) (base + off + 0x68) = src->c;
    }
}

void func_020be568(struct SomeObj *obj)
{
    struct SomeItem *a;
    struct SomeItem *b;
    int i;
    if (*(unsigned char *) ((char *) obj + 0xc0) == 0) {
        return;
    }
    a = obj->items;
    b = (struct SomeItem *) ((char *) obj + 0x60);
    for (i = 0; i < 8; i++, a++, b++) {
        func_020042b0(a, i == 7 ? 0 : b);
    }
}
