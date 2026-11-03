/* nook_clerk_4: 27 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_022647e8 @ 0x022647e8, 0x4c bytes, Thumb
 * func_ov050_022647d4 @ 0x022647d4, 0x12 bytes, Thumb
 * func_ov050_02264764 @ 0x02264764, 0x70 bytes, Thumb
 * func_ov050_0226466c @ 0x0226466c, 0xf8 bytes, Thumb
 * func_ov050_02264638 @ 0x02264638, 0x34 bytes, Thumb
 * func_ov050_02264544 @ 0x02264544, 0xf4 bytes, Thumb
 * func_ov050_02264510 @ 0x02264510, 0x34 bytes, Thumb
 * func_ov050_022643dc @ 0x022643dc, 0x134 bytes, Thumb
 * func_ov050_02264364 @ 0x02264364, 0x78 bytes, Thumb
 * func_ov050_02264304 @ 0x02264304, 0x60 bytes, Thumb
 * func_ov050_022642b4 @ 0x022642b4, 0x50 bytes, Thumb
 * func_ov050_02264258 @ 0x02264258, 0x5c bytes, Thumb
 * func_ov050_02264254 @ 0x02264254, 0x4 bytes, Thumb
 * func_ov050_02264250 @ 0x02264250, 0x4 bytes, Thumb
 * func_ov050_0226424c @ 0x0226424c, 0x4 bytes, Thumb
 * func_ov050_02264210 @ 0x02264210, 0x3c bytes, Thumb
 * func_ov050_022641e0 @ 0x022641e0, 0x30 bytes, Thumb
 * func_ov050_022641dc @ 0x022641dc, 0x4 bytes, Thumb
 * func_ov050_022641a8 @ 0x022641a8, 0x34 bytes, Thumb
 * func_ov050_02264188 @ 0x02264188, 0x20 bytes, Thumb
 * func_ov050_02264154 @ 0x02264154, 0x34 bytes, Thumb
 * func_ov050_022640e4 @ 0x022640e4, 0x70 bytes, Thumb
 * func_ov050_022640d4 @ 0x022640d4, 0x10 bytes, Thumb
 * func_ov050_02264018 @ 0x02264018, 0xbc bytes, Thumb
 * func_ov050_02263fe4 @ 0x02263fe4, 0x34 bytes, Thumb
 * func_ov050_02263f8c @ 0x02263f8c, 0x58 bytes, Thumb
 * func_ov050_02263f88 @ 0x02263f88, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02264764 {
    unsigned char pad_00[0x564];
    unsigned char unk_564[0x1c8];
    unsigned char unk_72C;
    unsigned char pad_72D;
    unsigned short unk_72E;
    unsigned short unk_730;
} UnkStruct_02264764;

typedef struct {
    char pad_00[0x654];
    int state;
    char pad_658[0xE8];
    unsigned char flag;
} UnkStruct_02264210;

typedef struct {
    u8 pad_00[0x350];
    u8 unk_350;
    u8 pad_351[0x564 - 0x350 - 1];
    u8 unk_564;
    u8 pad_565[0x730 - 0x564 - 1];
    u16 unk_730;
} UnkStruct_02263f8c;

extern int func_ov050_02260510(void *);
extern int func_ov050_022604bc(void *);
extern int func_ov050_022604e0(void *);
extern void func_ov050_02263640(void *, int);
extern int func_0203e0a8(int, int);
extern int func_02019c6c(void *address, int n, unsigned short value);
extern int func_020644cc(int n);
extern int func_0202ea40(UnkStruct_02264764 *self, int *local, int n);
extern unsigned short data_020c80f8;
extern int *func_02095794(int);
extern int func_0201c378(void *, int);
extern int func_0201c2c8(void *, int);
extern int func_020e8b4c(s16, int);
extern int func_ov050_02260498(void *);
extern void func_0201b458(void *, void *, int *);
extern int func_020960f8(int, int);
extern int func_020eaa2c(void *, const void *);
extern void func_ov050_02264834(void *, int);
extern int func_ov050_022606b4(void *);
extern int func_ov050_022605c0(void *);
extern int func_ov050_02260528(void *);
extern int func_ov050_02260718(void *);
extern int func_020e8840(const void *);
extern void func_0201aff4(void *a, int b);
extern int func_02019e00(void *a);
extern int func_02019de8(void *a);
extern int func_02019d0c(void *p, int, int, int, int, int, int, int, int, int, int);
extern int func_ov050_02260474(void *self);
extern void func_0201b044(void *p, void *buf);
extern int func_020eaa6c(void *buf, void *p);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099020(int, int);
extern int func_02014868(void *ptr);
extern int func_020ada40(void);
extern int func_0208602c(void);
extern int func_02086108(int a, int b);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_0203e020(void *ptr);
extern int func_020860d0(int argument0);
extern void func_02087f0c(void *argument0);
extern int func_02087ec0(int x);
extern void *func_ov050_022609d8(void *argument0);
extern void *func_0200338c(void *, int);
extern void func_0204f818(int *a, int *b, const int *c);
extern int func_0203b144(void);
extern int func_02095ab0(void *dst, int val, int size);
extern void *func_0209615c(unsigned int size);
extern const int data_ov050_0226509c[3];

int func_ov050_022647e8(void *arg)
{
    if (func_ov050_02260510(arg) != 0) {
        func_ov050_02263640((char *) arg + 0x658, 0);
    } else {
        if (func_ov050_022604bc(arg) != 0) {
            if (func_ov050_022604e0(arg) != 0) {
                ((char *) arg)[0x740] = 1;
            }
            func_ov050_02263640((char *) arg + 0x658, 0x11);
        }
    }
    return 1;
}

int func_ov050_022647d4(int param)
{
    func_0203e0a8(param, 0);
    return 1;
}

int func_ov050_02264764(UnkStruct_02264764 *self)
{
    int local[2];

    func_02019c6c(&self->unk_564, 1, self->unk_730);
    self->unk_72E = func_020644cc(5) * 20 + 100;
    self->unk_730 = data_020c80f8;
    if (func_ov050_02260510((void *) self) != 0 && func_0202ea40(self, local, 3) != 0) {
        self->unk_72C = 1;
    } else {
        self->unk_72C = 0;
    }
    return 1;
}

int func_ov050_0226466c(void *self)
{
    int *p;
    int triple[3];
    unsigned short val;
    int local[4];
    int r6;
    int r7;
    int r4;
    int tmp;
    p = func_02095794(4);
    triple[0] = p[0];
    r4 = 2;
    triple[1] = p[1];
    triple[r4] = p[r4];
    r6 = func_0201c378(self, 4);
    tmp = func_0201c2c8(self, 4);
    r4 = func_020e8b4c(*((s16 *) (((u8 *) self) + 0x8e)), tmp);
    r7 = func_ov050_02260498(self);
    func_0201b458(local, self, triple);
    val = 0x8b;
    if (func_020960f8(val, 4) || func_020960f8(0x8c, 4)) {
        return 1;
    }
    if (r6 > r7 && func_020eaa2c(local, ((u8 *) self) + 0x5c) != 0) {
        func_ov050_02264834(self, 3);
    } else if (r4 > 0x2000) {
        func_ov050_02264834(self, 2);
    }
    if (func_ov050_022606b4(self) != 0) {
        return 1;
    }
    if (func_ov050_022605c0(self) != 0) {
        if (tmp) {
            return 1;
        } else {
            return 1;
        }
    }
    if (func_ov050_02260528(self) != 0) {
        return 1;
    }
    if (func_ov050_02260718(self) != 0) {
        return 1;
    }
    if ((*((u8 *) (((u8 *) self) + 0x72c))) != 0) {
        if (func_020e8840(((u8 *) self) + 0x72e) == 0) {
            func_ov050_02264834(self, 7);
        }
    }
    return 1;
}

int func_ov050_02264638(int param)
{
    func_02019d0c((void *) (param + 0x564), 3, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov050_02264544(char *self)
{
    int *p;
    int arr[3];
    int r4, r6, r7;
    struct {
        int a, b, c, d;
    } ls;

    if (func_ov050_022606b4((void *) self) != 0) {
        return 1;
    }
    if (func_ov050_022605c0((void *) self) != 0) {
        return 1;
    }
    if (func_ov050_02260528((void *) self) != 0) {
        return 1;
    }
    if (func_ov050_02260718((void *) self) != 0) {
        return 1;
    }

    p = func_02095794(4);
    arr[0] = p[0];
    arr[1] = p[1];
    arr[2] = p[2];

    r6 = func_0201c378((void *) self, 4);
    r4 = func_0201c2c8((void *) self, 4);
    func_020e8b4c((short) (*(short *) (self + 0x8e)), r4);
    r7 = func_ov050_02260498((void *) self);
    func_0201b458(&ls, (void *) self, arr);

    if (func_020960f8(0x8b, 4) != 0 || func_020960f8(0x8c, 4) != 0) {
        return 1;
    }

    if (r6 > r7) {
        if (func_020eaa2c(&ls, (const void *) (self + 0x5c)) != 0) {
            func_ov050_02264834((void *) self, 3);
            return 1;
        }
    }

    func_0201aff4((void *) (self + 0x350), r4);
    if (func_02019e00((void *) (self + 0x564)) == 3) {
        if (func_02019de8((void *) (self + 0x564)) != 0) {
            func_ov050_02264834((void *) self, 1);
        }
    }
    return 1;
}

int func_ov050_02264510(void *param)
{
    func_02019d0c((char *) param + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (int) data_020c80f8, 0);
    return 1;
}

int func_ov050_022643dc(char *self)
{
    int tmp[3];
    int buf[4];
    int *p;
    int r4;
    int r6;

    if (func_020960f8(0x8b, 4) != 0 || func_020960f8(0x8c, 4) != 0) {
        func_ov050_02264834(self, 1);
        return 1;
    }

    if (func_ov050_022606b4(self) != 0) {
        return 1;
    }
    if (func_ov050_022605c0(self) != 0) {
        return 1;
    }
    if (func_ov050_02260528(self) != 0) {
        return 1;
    }
    if (func_ov050_02260718(self) != 0) {
        return 1;
    }

    p = (int *) func_02095794(4);
    tmp[0] = p[0];
    tmp[1] = p[1];
    tmp[2] = p[2];

    r4 = func_0201c378(self, 4);
    func_0201b458(buf, self, (int *) tmp);
    r6 = func_ov050_02260498(self);

    if (r4 > func_ov050_02260474(self)) {
        if (func_02019e00(self + 0x564) == 1) {
            func_02019d0c(self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    } else {
        if (func_02019e00(self + 0x564) == 2) {
            func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    }

    func_0201b044(self + 0x350, buf);

    if (r4 <= r6 || func_020eaa6c(buf, self + 0x5c) != 0) {
        func_ov050_02264834(self, 1);
    }

    return 1;
}

int func_ov050_02264364(void *self)
{
    int size;
    int arg2;
    int a;
    int local;

    size = func_02016104((char *) self + 0x658);
    arg2 = 0;
    if (size != 0) {
        arg2 = func_0201c314(self, size);
    }

    func_020147fc((char *) self + 0x618, 0, arg2, 0);

    a = func_020984e8();
    func_02099640(a);

    if (func_02099020(a, 1) != 0) {
        return 1;
    }

    if (func_ov050_02260510(self) != 0) {
        if (func_0202ea40((UnkStruct_02264764 *) self, (int *) (&local), 3) != 0) {
            ((unsigned char *) self)[0x72c] = 1;
        }
    }
    return 1;
}

int func_ov050_02264304(unsigned char *p)
{
    if (func_02014868(p + 0x618)) {
        return 1;
    }
    if (p[0x73c] != 0 && func_020ada40() == 0) {
        return 1;
    }
    if (func_02086108(func_0208602c(), 5) != 0) {
        func_020b6098(func_020b5e10(), 0);
    } else {
        func_0203e020(p);
    }
    func_ov050_02264834(p, 6);
    return 1;
}

int func_ov050_022642b4(void *p)
{
    int size;
    int r2;

    size = func_02016104((void *) ((char *) p + 0x658));
    r2 = 0;
    if (size != 0) {
        r2 = func_0201c314(p, size);
    }
    func_020147fc((char *) p + 0x618, 0, r2, 1);
    if (func_ov050_02260510(p) != 0) {

        func_02087f0c((void *) func_020860d0(func_0208602c()));
    }
    return 1;
}

int func_ov050_02264258(void *self)
{
    int r5;
    if (func_02014868((char *) self + 0x618) != 0) {
        goto done;
    }

    r5 = func_020860d0((int) func_0208602c());
    if (func_ov050_022604bc(self) != 0 && func_02087ec0(r5) != 0) {
        func_020b6098(func_020b5e10(), 1);
    } else {
        func_020b6098(func_020b5e10(), 0);
    }
    func_ov050_02264834(self, 6);
done:
    return 1;
}

int func_ov050_02264254(void)
{
    return 1;
}

int func_ov050_02264250(void)
{
    return 1;
}

int func_ov050_0226424c(void)
{
    return 1;
}

int func_ov050_02264210(void *param)
{
    UnkStruct_02264210 *p;
    int state;

    p = func_0200338c(func_ov050_022609d8(param), 0);
    state = p->state;
    if (state != 0 && (state == 1 || p->flag == 0)) {
        func_ov050_02264834(param, 1);
    }
    return 1;
}

int func_ov050_022641e0(void *param)
{
    unsigned short *p = (unsigned short *) ((char *) param + 0x730);
    *p = data_020c80f8;
    func_02019c6c((char *) param + 0x564, 1, *p);
    return 1;
}

int func_ov050_022641dc(void)
{
    return 1;
}

int func_ov050_022641a8(int param)
{
    func_02019d0c((void *) (param + 0x564), 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov050_02264188(void *arg)
{
    func_0201aff4((char *) arg + 0x350, func_0201c2c8(arg, 4));
    return 1;
}

int func_ov050_02264154(char *ptr)
{
    func_02019d0c((void *) (ptr + 0x564), 0xa, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov050_022640e4(void *p)
{
    if (func_ov050_022606b4(p)) {
        return 1;
    }
    if (func_ov050_022605c0(p)) {
        return 1;
    }
    if (func_ov050_02260528(p)) {
        return 1;
    }
    if (func_ov050_02260718(p)) {
        return 1;
    }

    if (func_02019e00((char *) p + 0x564) == 10) {
        if (func_02019de8((char *) p + 0x564)) {
            *(unsigned short *) ((char *) p + 0x730) = 24;
            func_ov050_02264834(p, 1);
        }
    }
    return 1;
}

int func_ov050_022640d4(char *p)
{
    p[0x651] = 0;
    return 1;
}

int func_ov050_02264018(unsigned char *self)
{
    int z[4];
    int data[3];
    int gdata[3];
    int tmp[3];
    int a, b, c;

    func_020984e8();
    {
        const int *p = (const int *) func_02095794(4);
        data[0] = p[0];
        data[1] = p[1];
        data[2] = p[2];
    }
    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    z[3] = 0;

    a = data_ov050_0226509c[0];
    gdata[0] = a;
    b = data_ov050_0226509c[1];
    gdata[1] = b;
    c = data_ov050_0226509c[2];
    gdata[2] = c;

    func_0204f818(&z[2], &z[3], gdata);
    func_0204f818(&z[0], &z[1], data);

    switch (self[0x651]) {
        case 0:
            if (func_02014868(self + 0x618) == 0) {
                func_0203b144();
                self[0x651] = 1;
            }
            break;
        case 1:
            tmp[0] = a;
            tmp[1] = b;
            tmp[2] = c;
            func_02095ab0(tmp, 0x266, 4);
            self[0x651] = 2;
            break;
        case 2:
            if (func_0209615c(4) == 0) {
                func_0203e020((void *) self);
                func_ov050_02264834((void *) self, 2);
            }
            break;
        default:
            break;
    }
    return 1;
}

int func_ov050_02263fe4(void *p)
{
    func_02019d0c((char *) p + 0x564, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov050_02263f8c(UnkStruct_02263f8c *p)
{
    if (func_02019e00(&p->unk_564) == 3) {
        if (func_02019de8(&p->unk_564) != 0) {
            func_02019c6c(&p->unk_564, 1, p->unk_730);
        }
    }
    {
        int tmp = func_0201c2c8(p, 4);
        func_0201aff4(&p->unk_350, tmp);
    }
    func_0203e0a8((int) p, 0);
    return 1;
}

int func_ov050_02263f88(void)
{
    return 1;
}
