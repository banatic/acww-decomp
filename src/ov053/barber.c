/* barber: 10 functions, module ov053
 * mwccarm 1.2/base -O4,s
 * func_ov053_0226073c @ 0x0226073c, 0x20 bytes, Thumb
 * func_ov053_0226071c @ 0x0226071c, 0x20 bytes, Thumb
 * func_ov053_02260620 @ 0x02260620, 0xfc bytes, Thumb
 * func_ov053_02260558 @ 0x02260558, 0xc8 bytes, Thumb
 * func_ov053_02260504 @ 0x02260504, 0x54 bytes, Thumb
 * func_ov053_022604bc @ 0x022604bc, 0x48 bytes, Thumb
 * func_ov053_02260488 @ 0x02260488, 0x34 bytes, Thumb
 * func_ov053_02260474 @ 0x02260474, 0x14 bytes, Thumb
 * func_ov053_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov053_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

typedef struct UnkStruct_02260620_2 UnkStruct_02260620_2;

typedef void (*SubFn)(UnkStruct_02260620_2 *);

typedef struct SubVtbl {
    unsigned char pad_00[8];
    SubFn fn;
} SubVtbl;

struct UnkStruct_02260620_2 {
    SubVtbl *vtbl;
};

typedef struct UnkStruct_02260620 {
    unsigned char pad_00[0x560];
    unsigned char unk_560;
    unsigned char pad_561[0x658 - 0x561];
    UnkStruct_02260620_2 sub;
} UnkStruct_02260620;

typedef struct {
    int a, b, c;
} Tri;

typedef struct Sub658 {
    int pad_00;
} Sub658;

typedef struct UnkStruct_02260420 {
    void *unk_00;
    char pad_04[0x654];
    Sub658 sub658;
} UnkStruct_02260420;

extern int func_02014868(int);
extern int func_020984e8(void);
extern void *func_0201c2a4(UnkStruct_02260620 *self, int r);
extern void func_02016108(UnkStruct_02260620_2 *sub, void *res);
extern int func_ov053_02260ba8(UnkStruct_02260620_2 *sub);
extern void func_ov053_02261524(UnkStruct_02260620 *self, int r);
extern int func_0203dff0(void);
extern Tri *func_02095794(int);
extern void func_0204f818(volatile int *, volatile int *, Tri *);
extern int func_020960f8(int, int);
extern int func_0203e070(void *, int);
extern void func_ov053_02260bb0(void *, int);
extern int func_0203e0a8(void *, int);
extern Tri data_ov053_022617c8;
extern int func_02030818(void *);
extern unsigned short *func_020996e0(int a);
extern unsigned short *func_020996f8(int a);
extern int func_0208602c(void);
extern int func_02086108(int, int);
extern void *func_ov053_02260bfc(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern unsigned char data_ov053_02261b98[];

int func_ov053_02260488(void *receiver);
int func_ov053_02260474(int p);

int func_ov053_0226073c(int param)
{
    int result;
    if (func_02014868(param + 0x618) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov053_0226071c(int param)
{
    if (func_02014868(param + 0x618) == 0) {
        return 1;
    }
    return 0;
}

void func_ov053_02260620(UnkStruct_02260620 *self, unsigned int mode, unsigned char val)
{
    void *res;

    func_020984e8();
    self->unk_560 = val;

    switch (mode) {
        case 3:
            func_ov053_02261524(self, 10);
            break;

        case 1:
            self->unk_560 = val;
            self->sub.vtbl->fn(&self->sub);
            res = func_0201c2a4(self, 4);
            func_02016108(&self->sub, res);
            if (func_ov053_02260ba8(&self->sub) == 4 || func_ov053_02260ba8(&self->sub) == 3) {
                func_ov053_02261524(self, 6);
            } else {
                func_ov053_02261524(self, 2);
            }
            break;

        case 0:
            self->sub.vtbl->fn(&self->sub);
            res = func_0201c2a4(self, 4);
            func_02016108(&self->sub, res);
            func_ov053_02261524(self, 2);
            break;

        case 8:
            if (func_ov053_02260ba8(&self->sub) == 9) {
                func_ov053_02260bb0((void *) (&self->sub), 14);
                func_ov053_02261524(self, 5);
            } else {
                if (func_ov053_02260ba8(&self->sub) != 10) {
                    func_ov053_02260bb0((void *) (&self->sub), 14);
                    func_ov053_02261524(self, 4);
                }
            }
            break;

        default:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
    }
}

int func_ov053_02260558(void *obj)
{
    volatile int a;
    volatile int b;
    Tri t;
    Tri *p;
    int hit;
    int v0, v1;

    if (func_0203dff0() != 0) {
        return 0;
    }
    if (func_ov053_02260474((int) obj) == 0) {
        return 0;
    }
    func_020984e8();
    p = func_02095794(4);
    t.a = p->a;
    t.b = p->b;
    t.c = p->c;
    a = 0;
    b = 0;
    func_0204f818(&a, &b, &t);
    if (func_020960f8(0x25, 4) != 0 || func_020960f8(0x28, 4) != 0) {
        if (func_0203e070(obj, 0) != 0) {
            hit = 0;
            v0 = a;
            v1 = a;
            if (v1 == 4 && b == 0xb) {
                hit = 1;
            }
            if (hit != 0 || (v0 == 5 && b == 0xb)) {
                if (func_ov053_02260488(obj) != 0) {
                    func_ov053_02260bb0((char *) obj + 0x658, 3);
                } else {
                    func_ov053_02260bb0((char *) obj + 0x658, 4);
                }
            } else {
                func_ov053_02260bb0((char *) obj + 0x658, 7);
            }
            return 1;
        }
    }
    return 0;
}

int func_ov053_02260504(void *arg)
{
    volatile Tri t;
    Tri *p;

    if (func_ov053_02260474((int) arg) == 0) {
        return 0;
    }
    p = func_02095794(4);
    t.a = p->a;
    t.b = p->b;
    t.c = p->c;
    if (p->c > data_ov053_022617c8.c) {
        func_ov053_02260bb0((char *) arg + 0x658, 8);
        func_0203e0a8(arg, 0);
        return 1;
    }
    return 0;
}

int func_ov053_022604bc(void *arg)
{
    int *p;
    int local[3];
    int result;

    p = (int *) func_02095794(4);
    local[0] = p[0];
    local[1] = p[1];
    local[2] = p[2];

    if (func_02030818(local)) {
        func_ov053_02260bb0((char *) arg + 0x658, 10);
        func_0203e0a8(arg, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov053_02260488(void *receiver)
{
    int a = func_020984e8();
    if (!(*func_020996e0(a) == 0xfff1 && *func_020996f8(a) == 0xfff1)) {
        return 1;
    }
    return 0;
}

int func_ov053_02260474(int p)
{
    return func_02086108(func_0208602c(), 7);
}

void *func_ov053_02260448(void *this)
{
    *(unsigned int *) this = (unsigned int) data_ov053_02261b98;
    func_ov053_02260bfc((char *) this + 0x658);
    func_0202ee5c(this);
    func_020edf54(this);
    return this;
}

UnkStruct_02260420 *func_ov053_02260420(UnkStruct_02260420 *obj)
{
    obj->unk_00 = ((int *) data_ov053_02261b98);
    func_ov053_02260bfc((void *) (&obj->sub658));
    func_0202ee5c((void *) obj);
    return obj;
}
