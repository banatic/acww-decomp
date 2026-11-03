/* scene_base_2: 34 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201610c @ 0x0201610c, 0x2 bytes, Thumb
 * func_02016108 @ 0x02016108, 0x4 bytes, Thumb
 * func_02016104 @ 0x02016104, 0x4 bytes, Thumb
 * func_020160d8 @ 0x020160d8, 0x2a bytes, Thumb
 * func_020160d4 @ 0x020160d4, 0x4 bytes, Thumb
 * func_020160d0 @ 0x020160d0, 0x4 bytes, Thumb
 * func_020160b4 @ 0x020160b4, 0x1a bytes, Thumb
 * func_0201607c @ 0x0201607c, 0x38 bytes, Thumb
 * func_02016024 @ 0x02016024, 0x58 bytes, Thumb
 * func_02016014 @ 0x02016014, 0x10 bytes, Thumb
 * func_0201600c @ 0x0201600c, 0x8 bytes, Thumb
 * func_02016004 @ 0x02016004, 0x8 bytes, Thumb
 * func_02015ff4 @ 0x02015ff4, 0x10 bytes, Thumb
 * func_02015fb0 @ 0x02015fb0, 0x42 bytes, Thumb
 * func_02015f38 @ 0x02015f38, 0x78 bytes, Thumb
 * func_02015f00 @ 0x02015f00, 0x38 bytes, Thumb
 * func_02015ed0 @ 0x02015ed0, 0x30 bytes, Thumb
 * func_02015ea0 @ 0x02015ea0, 0x30 bytes, Thumb
 * func_02015e70 @ 0x02015e70, 0x30 bytes, Thumb
 * func_02015e40 @ 0x02015e40, 0x30 bytes, Thumb
 * func_02015e10 @ 0x02015e10, 0x30 bytes, Thumb
 * func_02015de4 @ 0x02015de4, 0x2a bytes, Thumb
 * func_02015dd4 @ 0x02015dd4, 0x10 bytes, Thumb
 * func_02015dd0 @ 0x02015dd0, 0x2 bytes, Thumb
 * func_02015dc8 @ 0x02015dc8, 0x8 bytes, Thumb
 * func_02015dc0 @ 0x02015dc0, 0x8 bytes, Thumb
 * func_02015db8 @ 0x02015db8, 0x8 bytes, Thumb
 * func_02015da0 @ 0x02015da0, 0x16 bytes, Thumb
 * func_02015d90 @ 0x02015d90, 0x10 bytes, Thumb
 * func_02015d78 @ 0x02015d78, 0x16 bytes, Thumb
 * func_02015d68 @ 0x02015d68, 0x10 bytes, Thumb
 * func_02015d60 @ 0x02015d60, 0x6 bytes, Thumb
 * func_02015d44 @ 0x02015d44, 0x1c bytes, Thumb
 * func_02015d04 @ 0x02015d04, 0x40 bytes, Thumb
 */

typedef void (*FuncPtr)(void *);

typedef struct VirtualObj {
    FuncPtr *vtable;
} VirtualObj;

typedef struct SomeObj {
    unsigned char pad_00[0x50];
    void *unk_50;
} SomeObj;

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
} UnkStruct_020160b4;

typedef struct {
    char pad_00[0x4c];
    void *unk_4C;
    void *unk_50;
    char pad_54;
    unsigned char unk_55;
} UnkStruct_0201607c;

typedef struct {
    char pad_00[0x564];
    int unk_564;
} UnkStruct_02016024;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
} UnkStruct_02016024_2;

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char unk_54;
} UnkStruct_02016014;

struct Arg0 {
    char pad_00[0x40];
    int unk_40;
};

typedef struct {
    char data[0x44];
} UnkStruct_02015fb0;

struct UnkStruct_02015f38 {
    char pad_00[0x40];
    int unk_40;
};

struct UnkStruct_02015ea0 {
    char pad_00[0x40];
    int unk_40;
};

typedef struct {
    char pad_00[0x40];
    unsigned int unk_40;
} GUnknownStruct;

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
} UnkStruct_02015e40;

typedef struct {
    unsigned char data[0x20];
} UnkStruct_02015e40_2;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02015e10;

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
} UnkStruct_02015dd4;

typedef struct {
    unsigned char pad_00[0x4c];
    int unk_4C;
    int unk_50;
} UnkStruct_02015da0;

typedef struct {
    unsigned char pad_00[0x4c];
    unsigned int unk_4C;
    unsigned int unk_50;
} UnkStruct_02015d78;

typedef struct {
    unsigned char pad_00[0x55];
    unsigned char unk_55;
} UnkStruct_02015d68;

typedef struct {
    unsigned char pad_00[85];
    unsigned char unk_55;
} UnkStruct_02015d60;

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char unk_54;
} UnkStruct_02015d04;

extern void *func_0201c274(void *);
extern int func_0206837c(void *);
extern int func_020823e8(void *);
extern int func_02019e00(void *p);
extern int func_02019c90(void *p, int n, unsigned char c, unsigned short s);
extern unsigned short data_020c80f8;
extern void *func_020b5630(void *p);
extern int func_020b45d0(void *p, int a, int b, int c, int d, int e);
extern void *func_020b5618(void *p);
extern void *func_020a8228(void *);
extern int func_020b4a20(void *, void *, void *);
extern int func_020a89dc(void *, void *);
extern void *func_020a8210(void *);
extern void func_020683b4(int, int, void *, int);
extern unsigned char data_020d8d0c[];
extern int func_020b4508(void *, int, int);
extern int func_020b44bc(void *, void *);
extern void func_02068404(void *, void *, void *);
extern int func_020b44a4(void *, int);
extern void *func_020641c8(void *);
extern void func_02064210(unsigned int, void *);
extern void *func_020641b0(void *);
extern void *func_02094fd4(void *);
extern void *func_02095074(void *, void *);
extern void *func_02094fbc(void *);
extern int func_02003618(void *, void *);
extern void *func_02062f90(void *, void *);
extern void *func_02062f4c(void *);
extern int func_020683e4(int a, int b, int c, int d);
extern int func_020b65c4(void);
extern unsigned char func_020a13d0(void);
extern int func_020952ec(void);
extern void func_0201ad18(int a, int b, int c, int d, void *e, int f, int g, int h);
extern int data_021fbee8;

int func_02015ff4(void *arg0);
int func_02015da0(UnkStruct_02015da0 *ptr, int index);

void func_0201610c(void *object)
{
    (void) object;
}

void func_02016108(int *p0, int p1)
{
    p0[18] = p1;
}

int func_02016104(int *p0)
{
    return p0[18];
}

void func_020160d8(SomeObj *obj, void *value)
{
    void *ret;
    obj->unk_50 = value;
    if (obj->unk_50) {
        ret = func_0201c274(obj->unk_50);
        if (ret) {
            ((VirtualObj *) ret)->vtable[2](ret);
            ((VirtualObj *) obj->unk_50)->vtable[35](obj->unk_50);
        }
    }
}

int func_020160d4(int *p0)
{
    return p0[20];
}

void func_020160d0(int *p0, int p1)
{
    p0[19] = p1;
}

int func_020160b4(UnkStruct_020160b4 *obj)
{
    int ret = 0;
    if (obj->unk_40) {
        ret = func_0206837c(obj->unk_40);
    }
    return ret;
}

int func_0201607c(UnkStruct_0201607c *self)
{
    switch (self->unk_55) {
        case 0:
            if (self->unk_4C) {
                return func_020823e8((char *) self->unk_4C + 0xea);
            }
            break;
        case 1:
            if (self->unk_50) {
                return func_020823e8((char *) self->unk_50 + 0xea);
            }
            break;
        default:
            break;
    }
    return 5;
}

int func_02016024(int a, int b, int c)
{
    UnkStruct_02016024 *r4;
    UnkStruct_02016024_2 *r6;
    int result;

    r4 = (UnkStruct_02016024 *) func_02015da0((UnkStruct_02015da0 *) a, c);
    if (r4 == 0) {
        return (int) r4;
    }
    r6 = (UnkStruct_02016024_2 *) func_0201c274(r4);
    if (r6 == 0) {
        return (int) r6;
    }
    result = func_02015ff4(r6);
    if (result != 0) {
        return result;
    }
    if (r6->unk_5C == b) {
        result = func_02019e00(&r4->unk_564);
        if (result == 8) {
            return result;
        }
    }
    result = func_02019c90(&r4->unk_564, 2, (unsigned char) b, data_020c80f8);
    r6->unk_5C = b;
    return result;
}

int func_02016014(UnkStruct_02016014 *self, int arg2)
{
    return func_02016024((int) self, arg2, (unsigned char) self->unk_54);
}

void func_0201600c(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (96))) + (0)) = 1;
}

void func_02016004(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (96))) + (0)) = 0;
}

int func_02015ff4(void *arg0)
{
    if (*(unsigned char *) ((char *) arg0 + 0x60) == 1) {
        return 1;
    }
    return 0;
}

void func_02015fb0(struct Arg0 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    UnkStruct_02015fb0 local;
    if (arg1 < 0) {
        return;
    }
    func_020b5630(&local);
    func_020b45d0(&local, arg1, arg3, arg4, arg5, 0);
    func_02068404((void *) arg0->unk_40, (void *) arg2, &local);
    func_020b5618(&local);
}

void func_02015f38(struct UnkStruct_02015f38 *p1, int p2, int p3, int p4, unsigned char p5, int p6, int p7)
{
    int saved_arg4;
    unsigned char temp;
    int buf1[0x10];
    int buf2[0x17];
    int r4;

    saved_arg4 = p4;
    if (p2 < 0) {
        return;
    }

    func_020b5630(buf1);
    r4 = 7;
    func_020b45d0(buf1, p2, saved_arg4, p6, p7, 0);
    if (p5 != 0) {
        func_020a8228(buf2);
        temp = 0x1c;
        func_020b4a20(buf2, &temp, (void *) data_020d8d0c);
        func_020a89dc(buf1, buf2);
        r4 = 0;
        func_020a8210(buf2);
    }
    func_020683b4(p1->unk_40, p3, buf1, r4);
    func_020b5618(buf1);
}

void func_02015f00(void *r5, int r4, int r6, int r7, int kind)
{
    char sp[0x44];

    if (r4 >= 0) {
        func_020b5630(sp);
        func_020b4508(sp, r4, r7);
        func_02068404(*(void **) ((char *) r5 + 0x40), (void *) r6, sp);
        func_020b5618(sp);
    }
}

void func_02015ed0(void *param0, void *param1, void *param2)
{
    char sp[0x60];
    void *r5 = param0;
    void *r4 = param1;
    void *r6 = param2;

    func_020a8228(sp);
    func_020b44bc(sp, r4);
    func_02068404(*(void **) ((char *) r5 + 0x40), r6, sp);
    func_020a8210(sp);
}

void func_02015ea0(struct UnkStruct_02015ea0 *arg0, int arg1, int arg2)
{
    char buffer[0x60];

    func_020a8228(buffer);
    func_020b44a4(buffer, arg1);
    func_02068404((void *) arg0->unk_40, (void *) arg2, buffer);
    func_020a8210(buffer);
}

void *func_02015e70(GUnknownStruct *param0, unsigned int param1, unsigned int param2)
{
    char buffer[0x20];
    func_020641c8(buffer);
    func_02064210(param1, buffer);
    func_02068404((void *) param0->unk_40, (void *) param2, buffer);
    return func_020641b0(buffer);
}

void func_02015e40(UnkStruct_02015e40 *a, void *b, void *c)
{
    UnkStruct_02015e40_2 local;

    func_02094fd4(&local);
    func_02095074(b, &local);
    func_02068404(a->unk_40, c, &local);
    func_02094fbc(&local);
}

void func_02015e10(UnkStruct_02015e10 *p, void *arg1, void *arg2)
{
    char local[0x20];

    func_02094fd4(local);
    func_02003618(arg1, local);
    func_02068404(p->unk_40, arg2, local);
    func_02094fbc(local);
}

void func_02015de4(void *arg0, int arg1, void *arg2, void *arg3)
{
    unsigned char local_28[0x28];

    func_02062f90(local_28, (void *) arg1);
    func_020683b4(*(unsigned int *) ((char *) arg0 + 0x40), (int) arg2, local_28, (int) arg3);
    func_02062f4c(local_28);
    return;
}

int func_02015dd4(UnkStruct_02015dd4 *p, int b, int c, int d, const void *end)
{
    return func_020683e4(p->unk_40, b, c, d);
}

void func_02015dd0(void) {}

void func_02015dc8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (84))) + (0)) = 2;
}

void func_02015dc0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (84))) + (0)) = 0;
}

void func_02015db8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (84))) + (0)) = 1;
}

int func_02015da0(UnkStruct_02015da0 *ptr, int index)
{
    switch (index) {
        case 0:
            return ptr->unk_4C;
        case 1:
            return ptr->unk_50;
        default:
            return 0;
    }
}

int func_02015d90(void *ptr)
{
    return func_02015da0((UnkStruct_02015da0 *) ptr, (unsigned char) (((unsigned char *) ptr)[0x54]));
}

unsigned int func_02015d78(UnkStruct_02015d78 *r0, int r1)
{
    switch (r1) {
        case 0:
            return r0->unk_4C;
        case 1:
            return r0->unk_50;
        default:
            return 0;
    }
}

int func_02015d68(UnkStruct_02015d68 *ptr)
{
    return (int) func_02015d78((UnkStruct_02015d78 *) ptr, (unsigned char) ptr->unk_55);
}

unsigned char func_02015d60(UnkStruct_02015d60 *p)
{
    return p->unk_55;
}

int func_02015d44(void)
{
    if (func_020b65c4() == 0x2f) {
        return func_020a13d0();
    } else {
        return func_020952ec();
    }
}

void func_02015d04(UnkStruct_02015d04 *self)
{
    int ret0 = func_02015da0((UnkStruct_02015da0 *) self, (unsigned char) self->unk_54);
    if (ret0 != 0) {
        int ret1 = func_02015d44();
        func_0201ad18(ret0 + 0x3b0, 4, 0, 0, &data_021fbee8, ret1, 0, 0);
    }
}
