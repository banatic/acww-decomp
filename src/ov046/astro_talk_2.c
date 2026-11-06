/* astro_talk_2: 9 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_02260e34 @ 0x02260e34, 0x88 bytes, Thumb
 * func_ov046_02260ddc @ 0x02260ddc, 0x58 bytes, Thumb
 * func_ov046_02260d98 @ 0x02260d98, 0x44 bytes, Thumb
 * func_ov046_02260d64 @ 0x02260d64, 0x32 bytes, Thumb
 * func_ov046_02260d50 @ 0x02260d50, 0x12 bytes, Thumb
 * func_ov046_02260d3c @ 0x02260d3c, 0x12 bytes, Thumb
 * func_ov046_02260d18 @ 0x02260d18, 0x22 bytes, Thumb
 * func_ov046_02260cf4 @ 0x02260cf4, 0x22 bytes, Thumb
 * func_ov046_02260cd0 @ 0x02260cd0, 0x22 bytes, Thumb
 */

struct UnkStruct_02260ddc {
    char pad_00[0xDC];
    int unk_DC;
};

struct UnkStruct_02260d98 {
    char pad_00[0xC0];
    int unk_C0;
    char pad_C4[0x18];
    int unk_DC;
};

struct UnkStruct_02260d64;

struct UnkStruct_02260d64 {
    char pad_00[0xdc];
    int unk_DC;
};

struct UnkStruct_02260d50 {
    char pad_00[0xdc];
    int unk_DC;
};

typedef struct UnkStruct_02260d3c UnkStruct_02260d3c;

typedef void (*Func)(UnkStruct_02260d3c *);

struct UnkStruct_02260d3c {
    Func *vtable;
};

extern int data_020ccf94;
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int func_020b1328(int *);
extern void *func_020b1954(void *);
extern int func_020b1394(void *, int);
extern void func_02068404(int, int, void *);
extern void *func_020b193c(void *);
extern void func_020b1310(void);
extern int func_020b1558(void);
extern int func_020b1580(void);
extern void func_020157b0(void *p, int a, int b, int c);
extern int func_02015828(void *p, int a);
extern void func_ov046_02261508(void *p, int a);
extern int func_020644cc(int);
extern int func_ov046_022610fc(struct UnkStruct_02260d64 *);
extern void func_020157c8(void *p, int a, int b);

void func_ov046_02260e34(void *self)
{
    int local0 = 0;
    char local1[0x24];

    if (func_020b1328(&local0) == 0) {
        if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
            *(int *) ((char *) self + 0xdc) = 0x2f;
        } else {
            *(int *) ((char *) self + 0xdc) = 0x11;
        }
    } else {
        if (func_020b1328(&local0) == 1) {
            func_020b1954(local1);
            func_020b1394(local1, local0);
            func_02068404(*(int *) ((char *) self + 0x40), 7, local1);
            *(int *) ((char *) self + 0xdc) = 0x39;
            func_020b193c(local1);
        } else {
            *(int *) ((char *) self + 0xdc) = 0x3a;
        }
        func_020b1310();
    }
}

void func_ov046_02260ddc(struct UnkStruct_02260ddc *self)
{
    if (func_02073d90((int) ((*(void **) &data_020ccf94))) || *(short *) func_0209d358(0, 0x4A)) {
        if (func_020b1558() < 16) {
            self->unk_DC = 0x13;
        } else {
            self->unk_DC = 0x10;
        }
    } else {
        if (func_020b1558() < 16) {
            self->unk_DC = 0x14;
        } else {
            self->unk_DC = 1;
        }
    }
}

void func_ov046_02260d98(struct UnkStruct_02260d98 *p)
{
    p->unk_C0 = func_020b1580();
    if (p->unk_C0 >= 0) {
        func_020157b0(p, 46, (unsigned char) p->unk_C0, 0);
        func_02015828(p, 3);
        func_ov046_02261508(p, 1);
    } else {
        p->unk_DC = 62;
    }
}

void func_ov046_02260d64(struct UnkStruct_02260d64 *param)
{
    int r = func_020644cc(0x65);
    if (r < 0x46) {
        param->unk_DC = func_ov046_022610fc(param);
    } else if (r < 0x55) {
        param->unk_DC = 0x32;
    } else {
        param->unk_DC = 0x33;
    }
}

void func_ov046_02260d50(struct UnkStruct_02260d50 *self)
{
    self->unk_DC = func_ov046_022610fc((struct UnkStruct_02260d64 *) self);
}

void func_ov046_02260d3c(UnkStruct_02260d3c *o)
{
    o->vtable[0x88 / 4](o);
}

void func_ov046_02260d18(void *p)
{
    func_020157c8(p, 0x12, 0);
    func_02015828(p, 2);
    func_ov046_02261508(p, 2);
}

void func_ov046_02260cf4(void *p)
{
    func_020157c8(p, 0x12, 0);
    func_02015828(p, 2);
    func_ov046_02261508(p, 4);
}

void func_ov046_02260cd0(void *p)
{
    func_020157c8(p, 0x2d, 0);
    func_02015828(p, 2);
    func_ov046_02261508(p, 0);
}
