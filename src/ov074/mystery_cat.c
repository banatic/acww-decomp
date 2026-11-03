/* mystery_cat: 10 functions, module ov074
 * mwccarm 1.2/base -O4,s
 * func_ov074_02278b84 @ 0x02278b84, 0x20 bytes, Thumb
 * func_ov074_02278b34 @ 0x02278b34, 0x50 bytes, Thumb
 * func_ov074_02278b20 @ 0x02278b20, 0x12 bytes, Thumb
 * func_ov074_02278b1c @ 0x02278b1c, 0x2 bytes, Thumb
 * func_ov074_02278af8 @ 0x02278af8, 0x24 bytes, Thumb
 * func_ov074_02278adc @ 0x02278adc, 0x1a bytes, Thumb
 * func_ov074_02278a90 @ 0x02278a90, 0x4c bytes, Thumb
 * func_ov074_02278a6c @ 0x02278a6c, 0x22 bytes, Thumb
 * func_ov074_02278a34 @ 0x02278a34, 0x38 bytes, Thumb
 * func_ov074_02278a00 @ 0x02278a00, 0x34 bytes, Thumb
 */

struct Vtbl {
    void (*unk_00)(void *);
    void (*unk_04)(void *);
    void (*unk_08)(void *);
};

struct UnkStruct_02278b34 {
    struct Vtbl *vtbl;
};

struct UnkStruct_02278b34_2 {
    unsigned char pad_00[0x658];
    struct UnkStruct_02278b34 obj;
};

struct UnkStruct_02278b20 {
    int a;
    int b;
};

struct unknown_struct {
    int x;
    int y;
};

extern int func_02014868(void *);
extern void func_ov074_02279778(struct UnkStruct_02278b34_2 *self, int mode);
extern int func_0201c2a4(struct UnkStruct_02278b34_2 *self, int val);
extern void func_02016108(struct UnkStruct_02278b34 *obj, int val);
extern void *func_020b9e58(void *p);
extern int func_0203cfc0(void);
extern int func_020e9948(int a, int b);
extern int func_0203cfa8(unsigned int *data);
extern void *func_02088220(void *record);
extern int func_0203cfb0(void *x, void *y);
extern int func_020b9d3c(void *p, int b, void *c, int d, int e, int f);
extern void *data_ov074_02279b44;
extern unsigned char data_021f3278[];
extern void func_020b9e2c(void *p);
extern void func_020e993c(const void *heap, void *block);
extern void *func_ov074_02278fe4(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern unsigned char data_ov074_02279c68[];

void func_ov074_02278a90(void *a, void *b);

int func_ov074_02278b84(void *arg)
{
    int result;
    int flag = 0;

    if (func_02014868((char *) arg + 0x618) == 0) {
        flag = 1;
    }

    result = flag;
    return result;
}

void func_ov074_02278b34(struct UnkStruct_02278b34_2 *self, int mode)
{
    switch (mode) {
        case 0:
            func_ov074_02279778(self, 0);
            break;
        case 3:
            self->obj.vtbl->unk_08(&self->obj);
            func_02016108(&self->obj, func_0201c2a4(self, 4));
            func_ov074_02279778(self, 4);
            break;
        case 8:
            func_ov074_02279778(self, 2);
            break;
    }
}

struct UnkStruct_02278b20 *func_ov074_02278b20(struct UnkStruct_02278b20 *ptr)
{
    func_020b9e58(&ptr->b);
    return ptr;
}

void func_ov074_02278b1c(void *object) {}

void func_ov074_02278af8(int *out, int param1, int param2)
{
    int temp;
    temp = func_0203cfc0();
    *out = func_020e9948(param1, temp);
    func_ov074_02278a90((void *) out, (void *) param2);
}

int func_ov074_02278adc(void *arg)
{
    int result = 0;
    unsigned int *data;
    if ((data = *(unsigned int **) arg) != 0) {
        result = func_0203cfa8(data);
    }
    return result;
}

void func_ov074_02278a90(void *a, void *b)
{
    void *r;
    int v;

    r = func_02088220(data_021f3278);
    if (r == 0) {
        return;
    }
    if (func_0203cfb0(*(void **) a, r) == 0) {
        return;
    }
    v = func_ov074_02278adc(a);
    if (v == 0) {
        return;
    }
    func_020b9d3c((char *) a + 4, *(int *) ((char *) b + 0x5c), data_ov074_02279b44, v, 0, 0);
}

void func_ov074_02278a6c(struct unknown_struct *a, const void *b)
{
    func_020b9e2c(&a->y);
    if (a->x != 0) {
        func_020e993c(b, (void *) a->x);
    }
}

void *func_ov074_02278a34(void *obj)
{
    *(void **) obj = (void *) data_ov074_02279c68;
    func_ov074_02278b1c((char *) obj + 0x714);
    func_ov074_02278fe4((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

char *func_ov074_02278a00(char *self)
{
    *(char **) self = ((char *) data_ov074_02279c68);
    func_ov074_02278b1c((void *) (self + 0x714));
    func_ov074_02278fe4((void *) (self + 0x658));
    func_0202ee5c((void *) self);
    return self;
}
