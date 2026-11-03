/* activity_link_jobs: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a307c @ 0x020a307c, 0x8 bytes, Thumb
 * func_020a2dec @ 0x020a2dec, 0x290 bytes, Thumb
 * func_020a2ddc @ 0x020a2ddc, 0x10 bytes, Thumb
 * func_020a2dbc @ 0x020a2dbc, 0x20 bytes, Thumb
 * func_020a2d48 @ 0x020a2d48, 0x74 bytes, Thumb
 * func_020a2c8c @ 0x020a2c8c, 0xbc bytes, Thumb
 * func_020a2c5c @ 0x020a2c5c, 0x30 bytes, Thumb
 * func_020a2948 @ 0x020a2948, 0x314 bytes, Thumb
 * func_020a2924 @ 0x020a2924, 0x22 bytes, Thumb
 * func_020a2650 @ 0x020a2650, 0x2d4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020a2dec {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xe5 - 0xa2];
    unsigned char unk_E5;
    unsigned char unk_E6;
};

struct GG {
    char pad_00[0x64];
    int unk_64;
};

struct Self020a2c8c {
    unsigned char pad_00[0xd0];
    unsigned short unk_D0;
};

typedef struct {
    unsigned char pad_00[0xA1];
    unsigned char unk_A1;
    unsigned char pad_A2[0x69];
    unsigned char unk_10B;
} UnkStruct_020a2c5c;

typedef struct UnkStruct_020a2948 {
    u8 pad_00[0xa1];
    u8 state;
    u8 pad_A2[0xef - 0xa2];
    u8 arr_ef[0x101 - 0xef];
    u8 unk_101;
    u8 pad_102[0x10b - 0x102];
    u8 unk_10B;
    u8 pad_10C[2];
    unsigned char bf_lo : 4;
    unsigned char bf_hi : 4;
} UnkStruct_020a2948;

struct UnkStruct_020a2924 {
    char pad_00[0xa1];
    char unk_A1;
};

struct UnkStruct_020a2650 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xbc - 0xa2];
    void *unk_BC;
    char pad_C0[0xd8 - 0xc0];
    unsigned char unk_D8;
    char pad_D9[0xef - 0xd9];
    unsigned char unk_EF;
    char pad_F0[0x10e - 0xf0];
    unsigned char b_lo : 4;
    unsigned char b_hi : 4;
};

extern void func_020a0244(int);
extern void *data_020ccf94;
extern unsigned char data_020e37f8;
extern char data_020e3c40[];
extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a259c(struct UnkStruct_020a2dec *o, int a);
extern void func_020a02b4(struct UnkStruct_020a2dec *o, unsigned char *p, int a);
extern int func_020a01ec(void);
extern int func_020a2438(struct UnkStruct_020a2dec *o, int a);
extern void func_020a2480(struct UnkStruct_020a2dec *o);
extern int func_020a03e0(struct UnkStruct_020a2dec *o, unsigned char *p, int a, int b, int c, int d, int e, int f);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern void func_02073d74(void *g, int a);
extern int func_02073dd4(void *a, int b);
extern int func_02073918(void *a, int b);
extern int func_02073c90(void *a, int b);
extern int func_02075918(void);
extern int func_02075848(void);
extern void func_020732b4(void *g, int a);
extern int func_020ec920(void);
extern void func_020a1038(struct UnkStruct_020a2dec *o, int a, int b);
extern int func_020a0174(void);
extern int func_020a0848(struct UnkStruct_020a2dec *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a25cc(void *receiver);
extern int func_020682e0(int a);
extern void func_0206844c(int a, unsigned char *p, char *q);
extern void func_020a4e94(struct UnkStruct_020a2dec *o, int a);
extern int func_020a1954(void *a0, int *a1, int a2);
extern int data_020e3c54[];
extern void func_020a01b4(void);
extern char data_021dc7aa;
extern char data_021dc7bc;
extern void func_02074b44(int a, int b, int c);
extern void func_020742fc(void);
extern void *func_020642a4(void *p);
extern void MI_CpuCopy8(void *dest, void *src, int n);
extern int func_0209f180(void *p);
extern void func_020730c8(void);
extern int func_020eb9f0(void *p, int n);
extern unsigned char func_0209877c(void *p);
extern int func_020a11c4(void);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern int func_020ec2d4(void);
extern int func_020e8840(void *);
extern int func_02074308(void);
extern int func_0209ffb0(void *receiver);
extern void func_0209e6ec(void *, int);
extern void func_0209e604(void *);
extern void func_0209f128(void *, int);
extern void func_0203d394(void);
extern int func_020a2120(UnkStruct_020a2948 *, int);
extern int func_020a238c(UnkStruct_020a2948 *);
extern void func_0209fb54(void *);
extern void func_0209fb4c(void *);
extern int func_02075aa4(int, u16);
extern int func_020ec1f8(void);
extern int func_020984e8(void);
extern void func_02098fd0(int, int);
extern int func_020ec260(void);
extern void func_02074294(int);
extern char data_021dc7a8[];
extern char data_021f3ba0[];
extern int func_020757e0(void);
extern int func_020757ac(unsigned char *p);
extern int func_02075774(unsigned char *p);
extern int func_0207570c(void);
extern int func_0208b4f8(void);
extern void func_0208b9b8(int);
extern void func_0208b9b0(int);
extern void *func_020984d4(void);
extern void func_02099a38(void *p);
extern void func_0209ef10(char *p, void *q);

void func_020a307c(int argument0)
{
    func_020a0244((int) argument0);
}

void func_020a2dec(struct UnkStruct_020a2dec *self)
{
    int ok;
    int fl;
    int i;
    void *g;
    unsigned char tmp;

    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020a259c(self, 0)) {
                return;
            }
            self->state = 1;
            return;

        case 1:
        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            func_020a02b4(self, &self->state, 1);
            return;

        case 3:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_020a01ec()) {
                if (!func_020a2438(self, ((struct GG *) data_020ccf94)->unk_64)) {
                    return;
                }
                func_020a2480(self);
                self->state = 4;
            } else {
                self->state = 4;
            }
            return;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            ok = (func_020a01ec() == 0);
            func_020a03e0(self, &self->state, 4, 0x11, 0x17, func_020a01ec() != 0, ok, 1);
            return;

        case 12:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            if (!func_020a01ec()) {
                self->state = 0xd;
            } else {
                self->state = 0xe;
            }
            return;

        case 13:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_E6) {
                return;
            }
            func_02073d74(data_020ccf94, 2);
            self->state = 0x1c;
            return;

        case 14:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            fl = 1;
            i = 3;
            g = data_020ccf94;
            for (; i >= 0; i--) {
                if (func_02073dd4(g, i) && !func_02073918(g, i) && func_02073c90(g, i)) {
                    fl = 0;
                    break;
                }
            }
            if (!fl) {
                return;
            }
            if (!func_02075918()) {
                return;
            }
            self->state = 0xf;
            return;

        case 15:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_E5) {
                return;
            }
            if (!func_02075848()) {
                return;
            }
            func_020732b4(data_020ccf94, 2);
            self->state = 0x10;
            return;

        case 16:
            if ((func_02073044(), func_020ec920())) {
                return;
            }
            func_020a1038(self, data_020e37f8, 0);
            func_020a0174();
            data_020e37f8 = 7;
            self->state = 0x1c;
            return;

        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
            func_020a0848(self, &self->state, 0x11, 0x17, 1, 1);
            return;

        default:
            func_020a25cc(self);
            if (func_020a01ec()) {
                tmp = 6;
                func_0206844c(func_020682e0(0), &tmp, data_020e3c40);
                func_020a4e94(self, 0x11);
            } else {
                func_020a4e94(self, 8);
            }
            return;
    }
}

void func_020a2ddc(void *arg0)
{
    func_020a1954(arg0, data_020e3c54, 0x23);
}

void func_020a2dbc(int param)
{
    int result;

    result = func_020a259c((struct UnkStruct_020a2dec *) param, 1);
    if (result == 0) {
        return;
    }
    func_020a01b4();
    func_020a4e94((struct UnkStruct_020a2dec *) param, 0x1d);
}

void func_020a2d48(unsigned char *param)
{
    unsigned char local[16];
    void *ret;

    *(unsigned short *) (param + 0xd0) = 0x258;
    func_02074b44(1, 2, 0);
    func_020742fc();
    ret = func_020642a4(&data_021dc7aa);
    MI_CpuCopy8(ret, local, 12);
    local[0xd] = 1;
    local[0xc] = 0;
    if (func_0209f180(((char *) data_021dc7a8)) == 0) {
        local[0xc] = 1;
    }
    func_020730c8();
    func_020eb9f0(local, 14);
    param[0x102] = func_0209877c(&data_021dc7bc);
}

void func_020a2c8c(struct Self020a2c8c *self)
{
    char buf[2];
    int v;

    v = func_020a11c4();
    if (v > 0 && v < 4) {
        void *p;

        p = (void *) func_020682e0(0);
        func_02068358(p);
        func_02068434(p);
        buf[0] = 0x26;
        func_0206844c((int) p, (unsigned char *) buf, (char *) (((const char *) data_020e3c54)));
        func_020a4e94((struct UnkStruct_020a2dec *) self, 0);
    } else {
        int flag = 0;
        int w;

        w = func_020ec2d4();
        if (w == 2) {
            self->unk_D0 = 0;
        } else {
            if (func_020ec2d4() == 1) {
                if (func_020e8840(&self->unk_D0) == 0) {
                    flag = 1;
                } else {
                    func_02074308();
                }
            } else {
                flag = 1;
            }
            if (flag) {
                void *p;

                if (func_0209ffb0(self)) {
                    func_020a0174();
                }
                p = (void *) func_020682e0(0);
                buf[1] = 0x25;
                func_0206844c((int) p, (unsigned char *) (&buf[1]), (char *) (((const char *) data_020e3c54)));
                func_02068358(p);
                func_02068434(p);
                func_020a4e94((struct UnkStruct_020a2dec *) self, 0xc);
            }
        }
    }
}

void func_020a2c5c(UnkStruct_020a2c5c *ptr)
{
    ptr->unk_A1 = 0;
    if (func_0209f180(((int *) data_021dc7a8)) == 0) {
        ptr->unk_10B = 1;
    } else {
        ptr->unk_10B = 0;
    }
}

void func_020a2948(UnkStruct_020a2948 *self)
{
    int r;
    int mask;

    switch (self->state) {
        case 0:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else if (func_020a259c((struct UnkStruct_020a2dec *) self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a11c4();
                if (r > 0 && r < 4) {
                    self->state = 2;
                }
            }
            break;
        case 2:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else if (self->unk_101 != 0) {
                if (self->unk_10B == 0) {
                    func_0209e6ec(((int *) data_021dc7a8), 5);
                    func_0209e604(((int *) data_021dc7a8));
                } else {
                    func_0209f128(((int *) data_021dc7a8), 0x12);
                }
                func_0203d394();
                self->state = 3;
            }
            break;
        case 3:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a2120(self, 2);
                if (r == 1) {
                    self->state = 0xb;
                } else if (r == 0) {
                    self->state = 4;
                }
            }
            break;
        case 4:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a238c(self);
                if (r == 1) {
                    self->state = 0xb;
                } else if (r != 3) {
                    func_0209fb54(((int *) data_021f3ba0));
                    self->state = 5;
                }
            }
            break;
        case 5:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a2120(self, self->bf_hi);
                if (r == 1) {
                    self->state = 0xb;
                } else if (r == 0) {
                    self->state = 6;
                }
            }
            break;
        case 6:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = self->arr_ef[func_020a11c4()];
                if (r == 1) {
                    func_0209fb4c(((int *) data_021f3ba0));
                    self->arr_ef[func_020a11c4()] = 0;
                    func_020732b4(data_020ccf94, 2);
                    self->state = 7;
                } else if (r == 2) {
                    self->state = 0x11;
                }
            }
            break;
        case 7:
            func_02073fdc(-1);
            r = func_020a2120(self, self->bf_hi);
            if (r == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
            } else if (r == 0) {
                self->state = 8;
            }
            break;
        case 8:
            if (func_02073fdc(-1) != 0) {
                func_0209fb54(((int *) data_021f3ba0));
                self->state = 0xa;
            } else if (func_02075aa4(1, (u16) (1 << func_020a11c4())) != 0) {
                func_020732b4(data_020ccf94, 0);
                self->state = 9;
            }
            break;
        case 9:
            mask = func_020ec1f8();
            if ((mask & (1 << func_020a11c4())) == 0) {
                if (func_0209ffb0(self) != 0) {
                    func_020a0174();
                }
                self->state = 0x16;
            }
            break;
        case 0xa:
            func_02073fdc(-1);
            r = func_020a2120(self, self->bf_hi);
            if (r == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
            } else if (r == 0) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0x11;
            }
            break;
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
            func_020a0848((struct UnkStruct_020a2dec *) self, (unsigned char *) (&self->state), 0xb, 0x11, (u16) ((u16) (1 << func_020a11c4())), 1);
            break;
        default:
            func_020a25cc(self);
            func_020a4e94((struct UnkStruct_020a2dec *) self, 0xe);
            break;
    }
}

void func_020a2924(struct UnkStruct_020a2924 *s)
{
    func_02074294((func_02098fd0(func_020984e8(), 2), func_020ec260()));
    s->unk_A1 = 0;
}

void func_020a2650(struct UnkStruct_020a2650 *self)
{
    int n;

    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020757e0()) {
                return;
            }
            self->state = 1;
            return;

        case 1:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020757ac(&self->unk_D8)) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 2;
            return;

        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_02075774(&self->unk_D8)) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 3;
            return;

        case 3:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_0207570c()) {
                return;
            }
            self->state = 4;
            return;

        case 4:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            func_0208b9b8((int) func_0208b4f8());
            MI_CpuCopy8((void *) func_020984e8(), self->unk_BC, 0x249c);
            func_02099a38((void *) func_020984e8());
            func_0209ef10(data_021dc7a8, func_020984d4());
            self->state = 5;
            return;

        case 5:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            n = func_020a238c((UnkStruct_020a2948 *) self);
            if (n == 1) {
                self->state = 0xb;
                return;
            }
            if (n == 3) {
                return;
            }
            func_020732b4(data_020ccf94, 2);
            self->state = 6;
            return;

        case 6:
            func_02073fdc(1);
            n = func_020a2120((UnkStruct_020a2948 *) self, self->b_hi);
            if (n == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
                return;
            }
            if (n != 0) {
                return;
            }
            self->state = 7;
            return;

        case 7:
            if (func_02073fdc(1)) {
                func_0209fb54((void *) data_021f3ba0);
                self->state = 0xa;
                return;
            }
            if (!func_02075aa4(1, 1)) {
                return;
            }
            self->state = 8;
            return;

        case 8:
            if (func_02073fdc(1)) {
                func_0209fb54((void *) data_021f3ba0);
                self->state = 0xa;
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            n = self->unk_EF;
            if (n == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 9;
                return;
            }
            if (n != 2) {
                return;
            }
            func_0209fb54((void *) data_021f3ba0);
            self->state = 0xa;
            return;

        case 9:
            if (func_0209ffb0(self)) {
                func_020a0174();
            }
            MI_CpuCopy8(self->unk_BC, (void *) func_020984e8(), 0x249c);
            func_0208b9b0((int) func_0208b4f8());
            self->state = 0x16;
            return;

        case 10:
            func_02073fdc(1);
            n = func_020a2120((UnkStruct_020a2948 *) self, self->b_hi);
            if (n == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
                return;
            }
            if (n != 0) {
                return;
            }
            func_020732b4(data_020ccf94, 0);
            self->state = 0x11;
            return;

        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            func_020a0848((struct UnkStruct_020a2dec *) self, &self->state, 0xb, 0x11, 1, 1);
            return;

        default:
            func_020a4e94((struct UnkStruct_020a2dec *) self, 0);
            return;
    }
}
