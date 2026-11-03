/* host_picker: 21 functions, module ov140
 * mwccarm 1.2/base -O4,s
 * func_ov140_0229a570 @ 0x0229a570, 0x20 bytes, Thumb
 * func_ov140_0229a544 @ 0x0229a544, 0x2c bytes, Thumb
 * func_ov140_0229a4a0 @ 0x0229a4a0, 0xa4 bytes, Thumb
 * func_ov140_0229a460 @ 0x0229a460, 0x40 bytes, Thumb
 * func_ov140_0229a41c @ 0x0229a41c, 0x42 bytes, Thumb
 * func_ov140_0229a3fc @ 0x0229a3fc, 0x1e bytes, Thumb
 * func_ov140_0229a384 @ 0x0229a384, 0x78 bytes, Thumb
 * func_ov140_0229a280 @ 0x0229a280, 0x104 bytes, Thumb
 * func_ov140_0229a244 @ 0x0229a244, 0x3c bytes, Thumb
 * func_ov140_0229a1c4 @ 0x0229a1c4, 0x80 bytes, Thumb
 * func_ov140_0229a1a4 @ 0x0229a1a4, 0x1e bytes, Thumb
 * func_ov140_0229a164 @ 0x0229a164, 0x40 bytes, Thumb
 * func_ov140_0229a15c @ 0x0229a15c, 0x8 bytes, Thumb
 * func_ov140_0229a12c @ 0x0229a12c, 0x30 bytes, Thumb
 * func_ov140_0229a100 @ 0x0229a100, 0x2c bytes, Thumb
 * func_ov140_0229a078 @ 0x0229a078, 0x88 bytes, Thumb
 * func_ov140_0229a020 @ 0x0229a020, 0x58 bytes, Thumb
 * func_ov140_02299fc8 @ 0x02299fc8, 0x58 bytes, Thumb
 * func_ov140_02299fb0 @ 0x02299fb0, 0x18 bytes, Thumb
 * func_ov140_02299fa0 @ 0x02299fa0, 0x10 bytes, Thumb
 * func_ov140_02299f90 @ 0x02299f90, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x8dc];
    unsigned char state;
} UnkStruct_0229a4a0;

struct func_ov140_0229a3fc_unk {
    char pad_00[0x9c];
    int a;
    int b;
};

typedef struct {
    char pad_00[0x8af];
    u8 b[6];
    u8 tbl[0x20];
    u8 unk_8D5[6];
    char pad_8DB[2];
    u8 unk_8DD;
    char pad_8DE[2];
    u8 c[6];
    char pad_8E6[2];
    char unk_8E8;
} UnkStruct_0229a280;

typedef struct {
    unsigned char data[0x23];
} Elem;

typedef struct {
    unsigned char pad_00[0x180];
    Elem arr[32];
} ElemContainer;

typedef struct {
    unsigned char pad_00[0xa8];
    int unk_A8;
    unsigned char pad_AC[0x8b5 - 0xac];
    unsigned char unk_8B5[32];
    unsigned char pad_8D5[0x8dd - 0x8d5];
    unsigned char unk_8DD;
    unsigned char unk_8DE;
    unsigned char unk_8DF;
} Main;

typedef struct UnkStructElem {
    char data[0x6c];
} UnkStructElem;

typedef struct UnkStruct_0229a100 {
    unsigned char pad_00[0x8e6];
    unsigned char flag;
    unsigned char pad_8E7[0x11d5];
    UnkStructElem array[3];
} UnkStruct_0229a100;

struct self_0229a020 {
    unsigned char pad_00[0x8de];
    unsigned char unk_8DE;
};

struct UnkStruct_02299fc8 {
    unsigned char pad_00[0x8dd];
    unsigned char unk_8DD;
};

struct UnkStruct_02299fb0 {
    unsigned char pad_00[0x8ac];
    unsigned short flags;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_020b9bbc(const char *a, const char *b, int c, int d, int e);
extern void func_0206fdd4(void *a, int b, int c, int d, int e, int f);
extern void func_02051bf8(u16 *buf, int n);
extern void func_02051c08(void *p, u16 *buf, int n);
extern void func_ov139_02299798(void *p, int i);
extern void func_ov139_022997c0(void *p, int i, u16 *buf);
extern void func_ov139_02299888(unsigned char *a, int b, int c, int d, int e);
extern unsigned int func_020eb844(void);
extern void func_02070b84(UnkStructElem *elem);
extern void func_020708e4(void *handle, unsigned short *digits, int size);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_02070a04(void *handle, int a, int b);

int func_ov140_0229a1a4(int unused, const unsigned char *data);
unsigned int func_ov140_0229a15c(void *receiver);
void func_ov140_0229a078(unsigned char *obj);
void func_ov140_0229a020(struct self_0229a020 *self);
void func_ov140_02299fc8(struct UnkStruct_02299fc8 *self);
int func_ov140_02299fb0(struct UnkStruct_02299fb0 *self, int mask);
void func_ov140_02299fa0(unsigned short *r0, unsigned short r1);
void func_ov140_02299f90(unsigned short *p, unsigned short mask);

void func_ov140_0229a570(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x128c);
    func_ov002_02208098((void *) (self), 3);
}

void func_ov140_0229a544(void *self)
{
    func_ov002_0220a164((char *) self + 0x128c);
    *((unsigned char *) ((char *) self + 0x8ae)) = *((unsigned char *) ((char *) self + 0x8d));
    func_ov002_02208098((void *) (self), 4);
}

int func_ov140_0229a4a0(UnkStruct_0229a4a0 *self, void *arg)
{
    unsigned char cur = self->state;

    if (cur <= 5) {
        if (func_ov002_022088cc(arg)) {
            if (self->state != 0) {
                self->state--;
            }
        } else if (func_ov002_022088bc(arg)) {
            if (self->state < 5) {
                self->state++;
            } else {
                self->state = 6;
            }
        }
    } else {
        if (func_ov002_022088cc(arg)) {
            self->state = 5;
        } else if (func_ov002_022088ac(arg)) {
            if (self->state > 6) {
                self->state--;
            }
        } else if (func_ov002_0220889c(arg)) {
            if (self->state < 8) {
                self->state++;
            }
        }
    }

    return cur != self->state;
}

void func_ov140_0229a460(char *arg)
{
    if (!func_ov140_02299fb0((struct UnkStruct_02299fb0 *) arg, 4)) {
        return;
    }
    if (!func_020b9bbc(arg + 0x14bc, arg + 0xac, 6, 0x800, 0)) {
        return;
    }
    func_ov140_02299f90((unsigned short *) arg, 4);
}

void func_ov140_0229a41c(void *p)
{
    func_0206fdd4((char *) p + 0xac, 6, 8, 0xf, 0x13, 7);
    func_0206fdd4((char *) p + 0xac, 0x11, 8, 0x18, 0x13, 7);
    func_ov140_02299fa0((unsigned short *) p, 4);
}

void func_ov140_0229a3fc(struct func_ov140_0229a3fc_unk *self, int v)
{
    self->a = v;
    if (v == -1) {
        self->b = 9;
    } else {
        self->b = 8;
    }
}

int func_ov140_0229a384(u8 *self)
{
    int changed;
    int i;
    int idx;
    int off;
    int v;
    u8 *base;

    changed = 0;
    base = (u8 *) func_ov140_0229a15c(self);
    idx = self[0x8dd] * 6;
    for (i = 0; i < 6; i++) {
        off = idx;
        off = off * 0x23;
        if (func_ov140_0229a1a4((int) self, (const unsigned char *) (base + 0x180 + off)) == 0) {
            v = 0;
        } else {
            v = (base + off)[0x1a2];
        }
        if (v != (self + i)[0x8e0]) {
            changed = 1;
            (self + i)[0x8e0] = (u8) v;
        }
        idx++;
    }
    return changed;
}

void func_ov140_0229a280(UnkStruct_0229a280 *self)
{
    u16 buf1[6];
    u16 buf2[10];
    void *h;
    int v;
    void *ent;
    int i;
    int j;
    int k;

    func_ov140_0229a41c((void *) self);
    func_02051bf8(buf1, 6);
    func_02051bf8(buf2, 6);
    j = self->unk_8DD * 6;
    h = (void *) func_ov140_0229a15c(self);
    for (i = 0; i < 6; i++) {
        if (j < 0x20) {
            v = self->tbl[j];
            if (v == 0xff || (k = v, k = 0x23 * k, ent = (char *) h + 0x180 + k, func_ov140_0229a1a4((int) self, (const unsigned char *) ent)) == 0) {
                self->b[i] = 0;
                self->c[i] = 0;
                func_ov139_02299798(&self->unk_8E8, i);
            } else {
                self->unk_8D5[i] = v;
                self->b[i] = 1;
                self->c[i] = *(u8 *) ((char *) h + k + 0x1a2);
                func_02051c08((char *) h + 0x190 + k, buf1, 6);
                func_02051c08(ent, buf2, 6);
                func_ov139_022997c0(&self->unk_8E8, i, buf1);
            }
        } else {
            self->b[i] = 0;
            self->c[i] = 0;
            func_ov139_02299798(&self->unk_8E8, i);
        }
        j++;
    }
}

int func_ov140_0229a244(void *p)
{
    char *base;
    int i, count;

    base = (char *) func_ov140_0229a15c(p);
    count = 0;
    i = count;
    for (; i < 0x20; i++) {
        if (func_ov140_0229a1a4((int) p, (const unsigned char *) (base + 0x180 + i * 0x23))) {
            count++;
        }
    }
    return count;
}

void func_ov140_0229a1c4(Main *r5)
{
    ElemContainer *r7;
    int count;
    int i;

    r7 = (ElemContainer *) func_ov140_0229a15c(r5);
    count = 0;
    i = count;

    for (; i < 32; i++) {
        if (func_ov140_0229a1a4((int) r5, (const unsigned char *) (&r7->arr[i])) != 0) {
            count++;
        }
        r5->unk_8B5[i] = i;
    }

    r5->unk_8DD = 0;
    r5->unk_8DE = 5;
    r5->unk_8DF = count;

    func_ov140_0229a020((struct self_0229a020 *) r5);
    func_ov140_0229a078((unsigned char *) r5);
    func_ov140_02299fc8((struct UnkStruct_02299fc8 *) r5);

    if (r5->unk_8DE != 0) {
        r5->unk_A8 = 8;
    }
}

int func_ov140_0229a1a4(int unused, const unsigned char *data)
{
    if (data[32] == 6 && (data[0] || data[1])) {
        return 1;
    }
    return 0;
}

void func_ov140_0229a164(unsigned char *base, int something)
{
    int local;
    int i;
    for (i = 0; i < 6; i++) {
        if (*(base + i + 0x8e0) == 4) {
            local = 8;
        } else {
            local = 14;
        }
        func_ov139_02299888(base + 0x8e8, i, something, 5, local);
    }
}

unsigned int func_ov140_0229a15c(void *receiver)
{
    return func_020eb844();
}

unsigned char *func_ov140_0229a12c(unsigned char *base)
{
    if (base[0x8e6] < 3) {
        goto then_path;
    }
    return base + 0x1b94;
then_path:
    base[0x8e6]++;
    return base + 0x1abc + (base[0x8e6] - 1) * 0x6c;
}

void func_ov140_0229a100(UnkStruct_0229a100 *obj)
{
    int i;
    obj->flag = 0;
    for (i = 0; i < 3; i++) {
        func_02070b84(&obj->array[i]);
    }
}

void func_ov140_0229a078(unsigned char *obj)
{
    unsigned char *p = obj;
    void *handle = (void *) func_ov140_0229a12c((unsigned char *) obj);
    unsigned short digits[3];

    if (p[0x8df] < 10) {
        digits[0] = p[0x8df] + 0xff10;
        digits[1] = 0;
        digits[2] = 0;
    } else {
        digits[0] = (p[0x8df] / 10) + 0xff10;
        digits[1] = (p[0x8df] % 10) + 0xff10;
        digits[2] = 0;
    }

    func_020708e4(handle, digits, 3);
    func_02070a98(handle, 8, 0x1f4, 2, 0xf, 0, 1);
    func_02070a04(handle, 0, 0);
}

void func_ov140_0229a020(struct self_0229a020 *self)
{
    void *p;
    unsigned short buf[2];

    p = (void *) func_ov140_0229a12c((unsigned char *) self);
    buf[0] = self->unk_8DE + 0xff10;
    buf[1] = 0;
    func_020708e4(p, (unsigned short *) buf, 2);
    func_02070a98(p, 8, 0x1f3, 1, 15, 0, 1);
    func_02070a04(p, 0, 0);
}

void func_ov140_02299fc8(struct UnkStruct_02299fc8 *self)
{
    void *obj;
    unsigned short tmp[2];

    obj = (void *) func_ov140_0229a12c((unsigned char *) self);
    tmp[0] = (unsigned short) (self->unk_8DD + 0xff10);
    tmp[1] = 0;
    func_020708e4(obj, (unsigned short *) tmp, 2);
    func_02070a98(obj, 8, 0x1f2, 1, 0xf, 0, 1);
    func_02070a04(obj, 0, 0);
}

int func_ov140_02299fb0(struct UnkStruct_02299fb0 *self, int mask)
{
    if ((self->flags & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov140_02299fa0(unsigned short *r0, unsigned short r1)
{
    r0 = (unsigned short *) ((char *) r0 + 0x8ac);
    *r0 = (unsigned short) (*r0 | r1);
}

void func_ov140_02299f90(unsigned short *p, unsigned short mask)
{
    unsigned short v = p[0x456];
    v &= ~mask;
    p[0x456] = v;
}
