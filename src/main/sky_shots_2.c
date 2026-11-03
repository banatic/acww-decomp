/* sky_shots_2: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020be9f8 @ 0x020be9f8, 0x24 bytes, Thumb
 * func_020be9dc @ 0x020be9dc, 0x1c bytes, Thumb
 * func_020be9b8 @ 0x020be9b8, 0x22 bytes, Thumb
 * func_020be9b0 @ 0x020be9b0, 0x8 bytes, Thumb
 * func_020be904 @ 0x020be904, 0xac bytes, Thumb
 * func_020be8fc @ 0x020be8fc, 0x8 bytes, Thumb
 * func_020be8a8 @ 0x020be8a8, 0x54 bytes, Thumb
 * func_020be830 @ 0x020be830, 0x78 bytes, Thumb
 * func_020be828 @ 0x020be828, 0x8 bytes, Thumb
 * func_020be7d4 @ 0x020be7d4, 0x54 bytes, Thumb
 * func_020be784 @ 0x020be784, 0x50 bytes, Thumb
 * func_020be758 @ 0x020be758, 0x2c bytes, Thumb
 * func_020be6e4 @ 0x020be6e4, 0x74 bytes, Thumb
 * func_020be6ac @ 0x020be6ac, 0x36 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020be9b8 {
    int unk_00;
    int unk_04;
    int unk_08;
};

struct UnkStruct_020be904 {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char pad_18[6];
    unsigned char unk_1E;
    unsigned char unk_1F;
    unsigned char unk_20;
    unsigned char unk_21;
};

typedef struct {
    int state;   // 0x00
    int pad_04;  // 0x04
    int counter; // 0x08
    int a;       // 0x0c
    int b;       // 0x10
    int c;       // 0x14
} UnkStruct_020be8a8;

typedef struct {
    char pad_00[8];
    int counter;
} UnkStruct_020be830;

typedef struct {
    int state;
    int pad_04;
    int counter;
    int a;
    int b;
    int c;
} UnkStruct_020be7d4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad_0C[12];
    unsigned char unk_18;
} UnkStruct_020be784;

struct UnkStruct_020be758 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned char unk_1E;
    unsigned char unk_1F;
    unsigned char unk_20;
    unsigned char unk_21;
};

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14;
    unsigned char unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned char unk_1E, unk_1F, unk_20, unk_21;
} UnkStruct_020be6e4;

extern int func_020984e8(void);
extern unsigned int func_02099194(const unsigned char *);
extern void func_02099188(int a, unsigned char b);
extern void func_020beb98(void *p, int value);
extern int func_ov003_02220c8c(int flag, int v);
extern void func_020bf2b8(int *out, int a, int b, int c);
extern void func_020be5d0(int *a, int b, int c, int *d);
extern int func_ov003_02219774(void);
extern void func_0203aeec(int a);
extern int func_0203aeac(void);
extern void *func_02098844(void *base, int index);
extern int func_02099a28(void *obj);
extern void *func_0209967c(void *obj);
extern void func_02088768(void *obj, int arg);
extern void func_020871b8(char *addr);
extern void func_0204130c(int a, int b, int c);
extern char data_021dc7bc[];
extern char data_021ebcd2[];
extern unsigned char data_021fbb14[];
extern int func_02095794(int x);
extern int func_0208602c(void);
extern int func_020860c0(int);
extern int func_02087b8c(int a, int b, unsigned char c);
extern fx32 FX_Div(fx32 a, fx32 b);
extern void func_020c14bc(int *a, void *b);
extern int func_02095518(int a, int b, int c);
extern int func_020e8870(void *dst, int val, int size);

void func_020be758(struct UnkStruct_020be758 *p);
void func_020be6e4(UnkStruct_020be6e4 *self);
void func_020be6ac(void *param0, void *param1, void *param2);

void func_020be9f8(void)
{
    int a = func_020984e8();
    unsigned int b = func_02099194((const unsigned char *) a);
    if (b < 16) {
        func_02099188(a, b + 1);
    }
}

int func_020be9dc(void)
{
    if ((unsigned) (int) func_02099194((const unsigned char *) (func_020984e8())) >= 16U) {
        return 1;
    } else {
        return 0;
    }
}

void func_020be9b8(struct UnkStruct_020be9b8 *obj)
{
    obj->unk_08--;
    if (obj->unk_08 > 0) {
        return;
    }
    func_020beb98(obj, obj->unk_04);
    func_020be758((struct UnkStruct_020be758 *) obj);
}

void func_020be9b0(void *argument0)
{
    func_020be6e4((UnkStruct_020be6e4 *) ((void *) argument0));
}

void func_020be904(struct UnkStruct_020be904 *self)
{
    int flag;
    int v;

    func_020be6ac(self, (void *) 0x190, (void *) 0x190);

    if (self->unk_08 > 0) {
        self->unk_08--;
        if (self->unk_08 == 0) {
            flag = (self->unk_21 != 0) ? 1 : 0;
            v = ((self->unk_0C + 0x800) >> 12) - 0x80;
            if (func_ov003_02220c8c(flag, v) == 0) {
                self->unk_1E = 1;
            }
        }
    }

    if (self->unk_1F != 0 || self->unk_20 != 0) {
        int p;
        int local[3];

        p = (self->unk_1F != 0) ? 0x7f9 : 0x7fa;
        func_020bf2b8(local, self->unk_0C, self->unk_10, self->unk_14);
        func_020be5d0(((int *) data_021fbb14), 0, p, local);
        self->unk_1F = 0;
        self->unk_20 = 0;
    }

    if (self->unk_1E != 0) {
        func_ov003_02219774();
        func_020be758((struct UnkStruct_020be758 *) self);
    }
}

void func_020be8fc(void *argument0)
{
    func_020be6e4((UnkStruct_020be6e4 *) ((void *) argument0));
}

void func_020be8a8(UnkStruct_020be8a8 *arg)
{
    int local[4]; // 16 bytes

    func_020be6ac(arg, (void *) 0x50, 0);
    arg->counter--;
    if (arg->counter > 0) {
        return;
    }

    func_0203aeec(0x0a3d);
    func_020bf2b8(local, arg->a, arg->b, arg->c);
    func_020be5d0(((int *) data_021fbb14), 0, 0x07fd, local);
    arg->counter = 0x32;
    arg->state = 6;
}

void func_020be830(UnkStruct_020be830 *s)
{
    int i;
    void *r;

    func_020be6ac((void *) s, (void *) 0x190, (void *) 0x190);
    s->counter -= 1;
    if (s->counter > 0) {
        return;
    }

    func_ov003_02219774();
    func_0203aeac();

    for (i = 0; i < 4; i++) {
        r = func_02098844(data_021dc7bc, i);
        if (r && func_02099a28(r)) {
            func_02088768(func_0209967c(r), 0x14);
        }
    }

    func_020871b8(data_021ebcd2);
    func_0204130c(0x44, 0x63, 0);
    func_020be758((struct UnkStruct_020be758 *) s);
}

void func_020be828(void *argument0)
{
    func_020be6e4((UnkStruct_020be6e4 *) ((void *) argument0));
}

void func_020be7d4(UnkStruct_020be7d4 *self)
{
    int buffer[4];
    func_020be6ac((void *) self, (void *) 0x50, 0);
    if (self->counter > 0) {
        self->counter--;
    } else {
        func_0203aeec(0x5c3);
        func_020bf2b8(buffer, self->a, self->b, self->c);
        func_020be5d0((int *) ((unsigned int) data_021fbb14), 0, 0x800, buffer);
        self->counter = 0x1e;
        self->state = 9;
    }
}

void func_020be784(UnkStruct_020be784 *self)
{
    int r5;
    func_020be6ac((void *) self, (void *) 0x190, (void *) 0x190);
    self->unk_08--;
    if (self->unk_08 > 0) {
        return;
    }
    r5 = func_02095794(self->unk_04);
    if (r5 != 0) {
        func_02087b8c(func_020860c0((int) func_0208602c()), r5, self->unk_18);
    }
    func_ov003_02219774();
    func_0203aeac();
    func_020be758((struct UnkStruct_020be758 *) self);
}

void func_020be758(struct UnkStruct_020be758 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 4;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_14 = 0x1000;
    p->unk_18 = 0;
    p->unk_1A = 0;
    p->unk_1C = 0;
    p->unk_1E = 0;
    p->unk_1F = 0;
    p->unk_20 = 0;
    p->unk_21 = 0;
}

void func_020be6e4(UnkStruct_020be6e4 *self)
{
    void *ptr = (void *) func_02095794(4);
    int local = 0x00080000;
    int v;
    short sv;

    if (ptr != 0) {
        func_020c14bc(&local, ptr);
    }
    v = self->unk_0C - local;
    v = FX_Div(v, 0x00100000);
    v = (v * -10000) >> 12;
    if (v < -5000) {
        v = -5000;
    } else if (v > 5000) {
        v = 5000;
    }
    sv = (short) v;
    func_02095518(4000, sv, 4);
    self->unk_1A = 4000;
    self->unk_1C = sv;
}

void func_020be6ac(void *param0, void *param1, void *param2)
{
    short s1;
    short s2;
    void *p;

    p = (char *) param0 + 0x1a;
    func_020e8870(p, 0, (int) param1);
    p = (char *) param0 + 0x1c;
    func_020e8870(p, 0, (int) param2);
    s1 = *(short *) ((char *) param0 + 0x1a);
    s2 = *(short *) ((char *) param0 + 0x1c);
    func_02095518((short) s1, (short) s2, 4);
}
