/* gatekeeper_states_7: 21 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_022635f0 @ 0x022635f0, 0x4 bytes, Thumb
 * func_ov048_022635dc @ 0x022635dc, 0x12 bytes, Thumb
 * func_ov048_022635b8 @ 0x022635b8, 0x24 bytes, Thumb
 * func_ov048_022635a8 @ 0x022635a8, 0x10 bytes, Thumb
 * func_ov048_02263570 @ 0x02263570, 0x38 bytes, Thumb
 * func_ov048_0226354c @ 0x0226354c, 0x24 bytes, Thumb
 * func_ov048_02263548 @ 0x02263548, 0x4 bytes, Thumb
 * func_ov048_02263544 @ 0x02263544, 0x4 bytes, Thumb
 * func_ov048_02263508 @ 0x02263508, 0x3c bytes, Thumb
 * func_ov048_022634cc @ 0x022634cc, 0x3c bytes, Thumb
 * func_ov048_022634bc @ 0x022634bc, 0x10 bytes, Thumb
 * func_ov048_02263430 @ 0x02263430, 0x8c bytes, Thumb
 * func_ov048_02263420 @ 0x02263420, 0x10 bytes, Thumb
 * func_ov048_02263300 @ 0x02263300, 0x120 bytes, Thumb
 * func_ov048_022632f0 @ 0x022632f0, 0x10 bytes, Thumb
 * func_ov048_02263284 @ 0x02263284, 0x6c bytes, Thumb
 * func_ov048_02263238 @ 0x02263238, 0x4c bytes, Thumb
 * func_ov048_022631cc @ 0x022631cc, 0x6c bytes, Thumb
 * func_ov048_02263174 @ 0x02263174, 0x58 bytes, Thumb
 * func_ov048_02263084 @ 0x02263084, 0xf0 bytes, Thumb
 * func_ov048_02262f58 @ 0x02262f58, 0x12c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_02263430;

struct UnkStruct_02263300 {
    u8 pad_00[0x618];
    u8 unk_618;
    u8 pad_619[0x658 - 0x618 - 1];
    u8 unk_658;
    u8 pad_659[0x676 - 0x658 - 1];
    u8 unk_676;
    u8 pad_677[0xe6e - 0x676 - 1];
    u16 unk_E6E;
    u8 pad_E70[0xe71 - 0xe6e - 2];
    u8 unk_E71;
};

typedef struct {
    char pad_00[0xe71];
    unsigned char byte;
} FnOv048Struct;

typedef struct {
    char pad_00[0x564];
    int unk_564;
    char pad_568[0xe6e - 0x568];
    unsigned short unk_E6E;
} UnkStruct_022631cc;

extern int func_0203e0a8(int, int);
extern int func_02019c6c(int a, int b, unsigned short c);
extern unsigned short data_020c80f8;
extern int func_ov048_022604c8(void *parameter0);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov048_022635f4(void *, int);
extern int func_020984e8(void);
extern UnkStruct_02263430 *func_02095794(int);
extern int func_02095ab0(void *, int, int);
extern int func_0209615c(int);
extern UnkStruct_02263430 data_ov048_02263974;
extern int func_0203ad88(void);
extern int func_ov004_0222d518(void);
extern int func_020ec1e8(void);
extern void func_02073100(void);
extern int func_020eb7ac(void);
extern void func_020732b4(void *, int);
extern void func_020742b4(void);
extern int func_020e8840(void *);
extern unsigned int func_02073044(void);
extern int func_020ec920(void);
extern void func_ov048_02262618(void *, int, int);
extern void *func_020642a4(const void *);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int func_02099870(void *);
extern void *func_020950a8(int);
extern void func_020730c8(void);
extern int func_020eb9f0(void *, int);
extern void *data_020ccf94;
extern const char data_021dc7aa[];
extern int func_ov004_0222d4f4(void);
extern int func_ov004_02246f90(void);
extern void func_02095eec(int, int);
extern unsigned int data_ov048_02263980[3];
extern int func_02095a8c(int, int);
extern int func_020644cc(int);
extern void *func_0200338c(int, int);
extern int func_02019c20(void *, int, int, int, int, int);
extern int func_ov004_02246f7c(void);
extern unsigned int data_ov048_0226398c[3];
extern int func_02016884(void *, int, void *);
extern void func_0201addc(void *);
extern int func_02041d14(int, int);
extern void func_0200468c(void);
extern int func_020e8858(void *);

int func_ov048_022635f0(void)
{
    return 1;
}

int func_ov048_022635dc(int a1)
{
    func_0203e0a8(a1, 0);
    return 1;
}

int func_ov048_022635b8(int a)
{
    func_02019c6c(a + 0x564, 1, data_020c80f8);
    return 1;
}

int func_ov048_022635a8(void *arg0)
{
    func_ov048_022604c8((void *) arg0);
    return 1;
}

int func_ov048_02263570(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov048_0226354c(void *arg)
{
    if (func_02014868((char *) arg + 0x618) == 0) {
        func_0203e020(arg);
    }
    return 1;
}

int func_ov048_02263548(void)
{
    return 1;
}

int func_ov048_02263544(void)
{
    return 1;
}

int func_ov048_02263508(unsigned char *p)
{
    func_02019d0c(p + 0x564, 3, 1, 0, 0, 0, *(signed short *) (p + 0xe6c), 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov048_022634cc(void *self)
{
    if (func_ov048_022604c8((void *) self)) {
        return 1;
    }
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564)) {
            func_ov048_022635f4(self, 1);
        }
    }
    return 1;
}

int func_ov048_022634bc(char *p)
{
    p[0x0e71] = 0;
    return 1;
}

int func_ov048_02263430(unsigned char *self)
{
    volatile UnkStruct_02263430 saved;
    UnkStruct_02263430 local2;
    UnkStruct_02263430 *ptr;

    func_020984e8();

    ptr = func_02095794(4);
    saved.a = ptr->a;
    saved.b = ptr->b;
    saved.c = ptr->c;

    switch (self[0xe71]) {
        case 0:
            if (func_02014868(self + 0x618) == 0) {
                self[0xe71] = 1;
            }
            break;
        case 1:
            local2.a = data_ov048_02263974.a;
            local2.b = data_ov048_02263974.b;
            local2.c = data_ov048_02263974.c;
            func_02095ab0(&local2, 0x266, 4);
            self[0xe71] = 3;
            break;
        case 3:
            if (func_0209615c(4) == 0) {
                func_0203e020(self);
            }
            break;
        default:
            break;
    }

    return 1;
}

int func_ov048_02263420(unsigned char *p)
{
    p[0xe71] = 0;
    return 1;
}

int func_ov048_02263300(struct UnkStruct_02263300 *self)
{
    u8 buf[0x1c];

    switch (self->unk_E71) {
        case 0:
            if (func_02014868(&self->unk_618) == 0) {
                self->unk_E71 = 1;
            }
            break;
        case 1:
            if (func_0203ad88() == 0) {
                func_ov004_0222d518();
                self->unk_E6E = 0x3c;
                self->unk_E71 = 2;
                if (func_020ec1e8() == 4) {
                    func_02073100();
                    func_020eb7ac();
                    func_020732b4(data_020ccf94, 0);
                    func_020742b4();
                }
            }
            break;
        case 2:
            if (func_020e8840(&self->unk_E6E) == 0) {
                if (self->unk_676 == 0x46 || self->unk_676 == 0x6c) {
                    if (func_020ec1e8() == 3) {
                        func_02073044();
                        if (func_020ec920() != 0) {
                            func_0203e020(self);
                        }
                    } else {
                        void *v;
                        func_ov048_02262618(&self->unk_658, 1, 0);
                        v = (void *) func_020984e8();
                        MI_CpuCopy8(func_020642a4(data_021dc7aa), buf, 12);
                        MI_CpuCopy8(func_020950a8((int) func_02099870(v)), buf + 12, 12);
                        buf[0x18] = 0;
                        func_020730c8();
                        func_020eb9f0(buf, 0x1a);
                        func_020742b4();
                        func_0203e020(self);
                    }
                }
            } else {
                if (func_020ec1e8() == 3) {
                    func_02073044();
                    func_020ec920();
                }
            }
            break;
        default:
            break;
    }
    return 1;
}

int func_ov048_022632f0(FnOv048Struct *p)
{
    p->byte = 0;
    return 1;
}

int func_ov048_02263284(void *p)
{
    unsigned char state = *(unsigned char *) ((char *) p + 0x0e71);
    switch (state) {
        case 0:
            if (func_02014868((void *) ((char *) p + 0x0618)) == 0) {
                *((unsigned char *) ((char *) p + 0x0e71)) = 1;
            }
            break;
        case 1:
            if (func_0203ad88() == 0) {
                func_ov004_0222d4f4();
                *((unsigned short *) ((char *) p + 0x0e6e)) = 0x3c;
                *((unsigned char *) ((char *) p + 0x0e71)) = 2;
            }
            break;
        case 2:
            if (func_020e8840((void *) ((char *) p + 0x0e6e)) == 0) {
                func_0203e020(p);
            }
            break;
    }
    return 1;
}

int func_ov048_02263238(unsigned int p)
{
    unsigned int local[3];

    if (func_02014868((void *) (p + 0x618)) == 0) {
        func_ov004_02246f90();
        local[0] = data_ov048_02263980[0];
        local[1] = data_ov048_02263980[1];
        local[2] = data_ov048_02263980[2];
        func_02095ab0((void *) local, 0x400, 4);
        func_02095eec(1, 4);
        return 1;
    }
    return 0;
}

int func_ov048_022631cc(UnkStruct_022631cc *obj)
{
    if (func_0209615c(4) == 0) {
        func_02095a8c(-0x8000, 4);
        func_02019d0c(&obj->unk_564, 3, 1, 0, 0, 0, -0x4000, 0, 0, data_020c80f8, 0);
        obj->unk_E6E = (unsigned char) (func_020644cc(5) + 5);
        return 1;
    }
    return 0;
}

int func_ov048_02263174(void *arg)
{
    void *p;

    if (func_020e8840((char *) arg + 0xe6e) == 0) {
        p = func_0200338c(0x73, 0);
        func_02019d0c((char *) p + 0x564, 3, 1, 0, 0, 0, 0x4000, 0, 0, data_020c80f8, 0);
        return 1;
    }
    return 0;
}

int func_ov048_02263084(char *self)
{
    char *sub;
    unsigned int buf[3];

    sub = (char *) func_0200338c(0x73, 0) + 0x564;

    if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564) != 0) {
            func_02019c6c((int) (self + 0x564), 1, (u16) ((*(u16 *) &data_020c80f8)));
        }
    }

    if (func_02019e00(sub) == 3) {
        if (func_02019de8(sub) != 0) {
            func_02019d0c(sub, 0, 1, 0, 0, 0, 0xffffc000, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    }

    if (func_02019e00(self + 0x564) == 0 && func_02019e00(sub) == 0) {
        buf[0] = data_ov048_0226398c[0];
        buf[1] = data_ov048_0226398c[1];
        buf[2] = data_ov048_0226398c[2];
        func_02095ab0(buf, 0x666, 4);

        func_02019c20(self + 0x564, 1, 0x81, 1, (*(u16 *) &data_020c80f8), 0);

        self[0xe70] = (char) (func_020644cc(5) + 5);
        *(u16 *) (self + 0xe6e) = 0x16;
        func_ov004_02246f7c();

        return 1;
    }
    return 0;
}

int func_ov048_02262f58(void *arg)
{
    char *base;
    char *p334;
    char *p564;
    char *p2a0;
    char *p3b0;
    int result;

    base = (char *) func_0200338c(0x73, 0);
    p334 = base + 0x334;
    p564 = base + 0x564;
    p2a0 = base + 0x2a0;
    p3b0 = base + 0x3b0;

    if (func_020e8858((char *) arg + 0xe70) == 0 && func_02016884(p334, 0x81, p2a0) == 0 &&
        func_02016884(p334, 0x82, p2a0) == 0) {
        func_02019c20(p564, 1, 0x81, 1, data_020c80f8, 0);
    }

    if (func_02016884((char *) arg + 0x334, 0x81, (char *) arg + 0x2a0) != 0 && func_02019de8((char *) arg + 0x564) != 0) {
        func_02019c20((char *) arg + 0x564, 1, 0x82, 0, data_020c80f8, 0);
    }

    if (func_02016884(p334, 0x81, p2a0) != 0 && func_02019de8(p564) != 0) {
        func_02019c20(p564, 1, 0x82, 0, data_020c80f8, 0);
    }

    if (*(unsigned short *) ((char *) arg + 0xe6e) == 2) {
        func_0201addc((char *) arg + 0x3b0);
        func_0201addc(p3b0);
    }

    if (func_020e8840((char *) arg + 0xe6e) != 0) {
        goto ret0;
    }
    if (*(unsigned int *) ((char *) arg + 0x654) == 8) {
        if (func_02041d14(2, 0xf) != 0) {
            func_0200468c();
            result = 1;
        } else {
            goto ret0;
        }
    } else {
        result = 1;
    }
    goto done;
ret0:
    result = 0;
done:
    return result;
}
