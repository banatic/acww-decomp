/* talk_page: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206c3fc @ 0x0206c3fc, 0x84 bytes, Thumb
 * func_0206c3b8 @ 0x0206c3b8, 0x42 bytes, Thumb
 * func_0206c368 @ 0x0206c368, 0x50 bytes, Thumb
 * func_0206c34c @ 0x0206c34c, 0x1c bytes, Thumb
 * func_0206c340 @ 0x0206c340, 0xc bytes, Thumb
 * func_0206c2e4 @ 0x0206c2e4, 0x5c bytes, Thumb
 * func_0206c2c4 @ 0x0206c2c4, 0x20 bytes, Thumb
 * func_0206c278 @ 0x0206c278, 0x4c bytes, Thumb
 * func_0206c234 @ 0x0206c234, 0x44 bytes, Thumb
 * func_0206c224 @ 0x0206c224, 0x10 bytes, Thumb
 * func_0206c1cc @ 0x0206c1cc, 0x58 bytes, Thumb
 * func_0206c1a8 @ 0x0206c1a8, 0x24 bytes, Thumb
 * func_0206c19c @ 0x0206c19c, 0xc bytes, Thumb
 * func_0206c154 @ 0x0206c154, 0x48 bytes, Thumb
 * func_0206c124 @ 0x0206c124, 0x30 bytes, Thumb
 * func_0206c0f0 @ 0x0206c0f0, 0x34 bytes, Thumb
 * func_0206c05c @ 0x0206c05c, 0x94 bytes, Thumb
 * func_0206c058 @ 0x0206c058, 0x2 bytes, Thumb
 * func_0206c038 @ 0x0206c038, 0x20 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0206c3b8 {
    char pad_00[0x34];
    char unk_34[0x14];
    int unk_48;
};

typedef struct {
    char pad_00[0x400];
    int used;
    int arr0[3];
    int unk_410;
    char pad_414[0x18];
    int arr1[3];
    char arr_b[3];
} UnkStruct_0206c2e4;

typedef struct {
    unsigned char pad_00[0x414];
    int arr[3];
} UnkStruct_0206c2c4;

typedef struct {
    char buf[0x400];
    unsigned int used;
} UnkStruct_0206c278;

struct UnkStruct_0206c224 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
};

typedef struct {
    u8 pad_00[0x400];
    u32 base;
    void *arr2[3];
    u32 count;
    u8 pad_414[0x18];
    u32 arr1[3];
    u8 pad_438[3];
    u8 flag;
    u8 buf[1];
} UnkStruct_0206c1cc;

typedef struct {
    unsigned char pad_00[0x410];
    unsigned int count;
    int array[3];
} UnkStruct_0206c1a8;

struct UnkStruct_0206c124 {
    char pad_00[0x420];
    int arr[3];
};

typedef struct {
    char pad_00[0x420];
    void *array[3];
} UnkStruct_0206c0f0;

typedef struct {
    char pad_00[0x10];
    int unk_10;
} Elem;

struct UnkStruct_0206c05c {
    char pad_00[0x400];
    u32 unk_400;
    u32 vals_0x404[3];
    u32 count;
    u32 vals_0x414[3];
    void *ptrs_0x420[3];
    u32 vals_0x42c[3];
    u8 flags_0x438[3];
};

extern void func_020a873c(void *a, void *b);
extern void func_020a9334(void *a, int b);
extern int func_02050bf8(unsigned char c);
extern int func_02050c04(unsigned char c);
extern int func_02068114(void);
extern void func_020a8328(char *, int *, int *, int *);
extern void func_020a93e8(struct UnkStruct_0206c3b8 *, int);
extern void *func_0206d5e4(unsigned char *q, int v);
extern void *func_0206d5c0(void *p);
extern void MI_CpuFill8(void *, int, int);
extern u32 func_0206d56c(void *buf, int arg1, u8 flag);
extern void *func_020a9034(int, int, int);
extern void func_0205166c(void *, int);
extern void func_020a8fb8(int value);
extern u32 func_02068bc8(u32);
extern void func_02051694(void *);

void func_0206c340(int a);
void func_0206c2e4(UnkStruct_0206c2e4 *obj, int v);
void func_0206c2c4(UnkStruct_0206c2c4 *s, int v);
void func_0206c124(struct UnkStruct_0206c124 *s);
void func_0206c038(unsigned int *arg0);

void func_0206c3fc(unsigned char *p)
{
    unsigned char local;
    unsigned char *base;
    unsigned int x, val, rem;
    int result;

    func_020a873c(p + 0x34, &local);
    local--;

    base = *(unsigned char **) (p + 0x2c);
    val = *(unsigned int *) (base + 0x1a60);
    x = *(unsigned int *) (base + 0x1a5c);

    if (x != 0 && (rem = (int) (x - 0xAC00) % 28) != 0) {
        if (val == 1) {
            if (local == 6 && rem == 8) {
                result = func_02050bf8(local);
            } else {
                result = func_02050c04(local);
            }
        } else {
            result = func_02050c04(local);
        }
    } else {
        result = func_02050bf8(local);
    }

    func_020a9334(p, result);
}

void func_0206c3b8(struct UnkStruct_0206c3b8 *self)
{
    int a, b, c;
    int ret = ((int) (func_020a8328(self->unk_34, &a, &b, &c), self->unk_34));
    if (func_02068114() == 0) {
        func_020a93e8(self, a << 1);
        func_020a9334((void *) self, c);
        self->unk_48 = c + ((b - c) ^ 1);
    }
}

unsigned char *func_0206c368(unsigned char *p, int q)
{
    unsigned int i;
    int zero = 0;
    *(int *) (p + 0x400) = zero;
    *(int *) (p + 0x410) = zero;
    p[0x43b] = zero;
    func_0206d5e4(p + 0x43c, q);
    func_0206c340((int) p);
    i = 0;
    goto tst;
bdy:
    *(int *) (p + i * 4 + 0x420) = zero;
    i++;
tst:
    if (i < 3) {
        goto bdy;
    }
    return p;
}

void *func_0206c34c(void *p)
{
    func_0206c124((struct UnkStruct_0206c124 *) p);
    func_0206d5c0((char *) p + 0x43c);
    return p;
}

void func_0206c340(int a)
{
    func_0206c2e4((UnkStruct_0206c2e4 *) a, 0);
}

void func_0206c2e4(UnkStruct_0206c2e4 *obj, int v)
{
    unsigned int i;
    int val;
    obj->used = 0;
    MI_CpuFill8(obj, 0, 0x400);
    i = 0;
    val = i;
    goto test;
loop:
    obj->arr0[i] = val;
    obj->arr_b[i] = (char) val;
    obj->arr1[i] = val;
    i++;
test:
    if (i < 3) {
        goto loop;
    }
    obj->unk_410 = 0;
    func_0206c2c4((UnkStruct_0206c2c4 *) obj, v);
}

void func_0206c2c4(UnkStruct_0206c2c4 *s, int v)
{
    unsigned int i = 0;
    goto test;
loop:
    s->arr[i] = v;
    i++;
test:
    if (i < 3) {
        goto loop;
    }
}

int func_0206c278(UnkStruct_0206c278 *obj, char *src, unsigned int n)
{
    int ret;
    unsigned int i;

    ret = (0x400 - obj->used > n) ? 1 : 0;
    if (ret) {
        for (i = 0; i < n; i++) {
            ((char *) obj + obj->used)[i] = src[i];
        }
        {
            unsigned int new_used = obj->used + n;
            obj->used = new_used;
            func_0206c038((unsigned int *) obj);
        }
    }
    return ret;
}

int func_0206c234(char *buf, int val)
{
    signed char b0 = (signed char) val;
    signed char b1 = (signed char) (val >> 8);
    int count = *(int *) (buf + 0x400);
    int flag = (unsigned) (0x400 - count) > 2 ? 1 : 0;
    if (flag) {
        int *ptr = (int *) (buf + 0x400);
        *ptr = *ptr + 1;
        buf[count] = b0;
        count = *ptr;
        *ptr = count + 1;
        buf[count] = b1;
        func_0206c038((unsigned int *) buf);
    }
    return flag;
}

void func_0206c224(int a, struct UnkStruct_0206c224 *s)
{
    func_0206c278((UnkStruct_0206c278 *) a, (char *) s->unk_10, s->unk_08 + 6);
}

void func_0206c1cc(UnkStruct_0206c1cc *self, int arg1)
{
    u32 c;
    if (self->count >= 3) {
        return;
    }
    self->arr1[self->count] = func_0206d56c(self->buf, arg1, self->flag);
    c = self->count;
    self->count = c + 1;
    self->arr2[c] = (void *) ((u8 *) self + self->base);
}

void func_0206c1a8(UnkStruct_0206c1a8 *obj, int value)
{
    unsigned int i = obj->count;
    while (i < 3) {
        obj->array[i] = value;
        i++;
    }
}

void func_0206c19c(unsigned char *r0, unsigned char r1)
{
    r0[0x43b] = r1;
}

void func_0206c154(void *base)
{
    unsigned int i;
    unsigned int offset;
    unsigned int zero;
    void *p;

    i = 0;
    offset = 0x11;
    zero = i;

    do {
        p = func_020a9034(offset, 0x14, 2);
        if (p) {
            *(void **) ((char *) base + i * 4 + 0x420) = p;
            *(int *) ((char *) p + 0x50) = 2;
            *(char *) ((char *) p + 0x39) = 0x0e;
            func_0205166c(p, zero);
        }
        i++;
        offset += 0x28;
    } while (i < 3);
}

void func_0206c124(struct UnkStruct_0206c124 *s)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (s->arr[i] != 0) {
            func_020a8fb8(s->arr[i]);
            s->arr[i] = 0;
        }
    }
}

void func_0206c0f0(UnkStruct_0206c0f0 *param0)
{
    int zero = 0;
    unsigned int i = 0;
    do {
        Elem *elem = (Elem *) param0->array[i];
        if (elem != 0) {
            func_0205166c(elem, zero);
            elem->unk_10 = 0;
        }
        i++;
    } while (i < 3);
}

void func_0206c05c(struct UnkStruct_0206c05c *self)
{
    int i;
    u32 zero1 = 0;
    u32 zero2 = 0;

    for (i = 0; i < self->count; i++) {
        void *ptr = self->ptrs_0x420[i];
        if (ptr != 0) {
            u8 *byte_base = (u8 *) self + i;
            if (byte_base[0x438] != 0) {
                *(u32 *) ((char *) ptr + 0x10) = self->vals_0x404[i];
                *(u32 *) ((char *) ptr + 0x14) = zero1;
                *(u32 *) ((char *) ptr + 0x30) = self->vals_0x42c[i];
                *(u8 *) ((char *) ptr + 0x38) = (u8) func_02068bc8(self->vals_0x414[i]);
                func_02051694(ptr);
                byte_base[0x438] = (u8) zero2;
            }
        }
    }

    if (self->count < 3) {
        void *ptr = self->ptrs_0x420[self->count];
        if (ptr != 0) {
            *(u32 *) ((char *) ptr + 0x14) = (u32) ((char *) self + self->unk_400);
        }
    }
}

void func_0206c058(void) {}

void func_0206c038(unsigned int *arg0)
{
    unsigned int val;
    unsigned char *puVar2;

    val = *(unsigned int *) ((unsigned char *) arg0 + 0x410);
    if (val != 0 && val <= 3) {
        puVar2 = (unsigned char *) arg0 + val;
        puVar2[0x437] = 1;
    }
}
