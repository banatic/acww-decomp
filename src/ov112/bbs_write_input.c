/* bbs_write_input: 27 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_022a0804 @ 0x022a0804, 0x34 bytes, Thumb
 * func_ov112_022a0798 @ 0x022a0798, 0x6c bytes, Thumb
 * func_ov112_022a0768 @ 0x022a0768, 0x30 bytes, Thumb
 * func_ov112_022a0710 @ 0x022a0710, 0x58 bytes, Thumb
 * func_ov112_022a06b8 @ 0x022a06b8, 0x58 bytes, Thumb
 * func_ov112_022a0620 @ 0x022a0620, 0x98 bytes, Thumb
 * func_ov112_022a05b0 @ 0x022a05b0, 0x70 bytes, Thumb
 * func_ov112_022a0548 @ 0x022a0548, 0x68 bytes, Thumb
 * func_ov112_022a051c @ 0x022a051c, 0x2c bytes, Thumb
 * func_ov112_022a04b8 @ 0x022a04b8, 0x64 bytes, Thumb
 * func_ov112_022a03ac @ 0x022a03ac, 0x10c bytes, Thumb
 * func_ov112_022a02f4 @ 0x022a02f4, 0xb8 bytes, Thumb
 * func_ov112_022a029c @ 0x022a029c, 0x58 bytes, Thumb
 * func_ov112_022a0258 @ 0x022a0258, 0x44 bytes, Thumb
 * func_ov112_022a01b0 @ 0x022a01b0, 0xa8 bytes, Thumb
 * func_ov112_022a0144 @ 0x022a0144, 0x6c bytes, Thumb
 * func_ov112_022a00ac @ 0x022a00ac, 0x98 bytes, Thumb
 * func_ov112_022a0068 @ 0x022a0068, 0x44 bytes, Thumb
 * func_ov112_022a0028 @ 0x022a0028, 0x40 bytes, Thumb
 * func_ov112_0229ffdc @ 0x0229ffdc, 0x4c bytes, Thumb
 * func_ov112_0229ffa0 @ 0x0229ffa0, 0x3c bytes, Thumb
 * func_ov112_0229ff5c @ 0x0229ff5c, 0x44 bytes, Thumb
 * func_ov112_0229ff50 @ 0x0229ff50, 0xc bytes, Thumb
 * func_ov112_0229ff38 @ 0x0229ff38, 0x16 bytes, Thumb
 * func_ov112_0229ff1c @ 0x0229ff1c, 0x1c bytes, Thumb
 * func_ov112_0229fefc @ 0x0229fefc, 0x20 bytes, Thumb
 * func_ov112_0229fee4 @ 0x0229fee4, 0x16 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x244];
    int unk_244;
    char pad_248[0x13c];
    int unk_384;
} UnkStruct_022a0768;

typedef struct {
    unsigned short pad_00;
    unsigned short flag;
} Reg;

struct UnkStruct_022a0620 {
    unsigned char pad_00[0x384];
    int unk_384;
    unsigned char pad_388[0x4448 - 0x388];
    int unk_4448;
};

typedef struct UnkStruct_022a02f4 {
    u8 pad_00[0xbd];
    u8 unk_BD;      // 0xbd
    u8 unk_BE;      // 0xbe
    u8 unk_BF;      // 0xbf
    u8 unk_C0;      // 0xc0
    u8 pad_C1[3];   // 0xc1..0xc3
    u16 arr_c4[16]; // 0xc4
} UnkStruct_022a02f4;

extern int func_0208e484(void *);
extern int func_ov002_0220a700(u8 *p);
extern int func_0208e4bc(u8 *p);
extern int func_ov002_0220a6e0(u8 *p);
extern int func_ov002_0220a768(u8 *p, int);
extern int func_ov002_0220a72c(u8 *p, int);
extern void func_ov002_0220a0b4(u8 *p, int, int);
extern unsigned char *func_ov002_022080a0(u8 *p, unsigned char value);
extern int func_ov095_0229bf48(void *ptr);
extern int func_ov002_0220b8ac(void *ptr, int flag);
extern int func_ov095_02299a00(void *self);
extern int func_ov095_0229c448(void *p, int r, int n);
extern void func_ov095_0229c8e4(void *p, int r);
extern void func_ov112_0229f29c(void *self);
extern unsigned char data_021fbe40[];
extern void func_ov095_0229bf3c(void *p);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov112_0229f3e0(void *self);
extern int func_ov112_0229fe70(void *, int);
extern void func_ov112_0229fe50(void *, int);
extern void func_ov112_0229fab4(void *);
extern int func_ov095_0229cda4(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a314(void *);
extern void func_ov112_0229f35c(void *);
extern int func_ov095_0229cf64(void *ptr, int val);
extern void func_ov112_0229f2bc(void *ptr);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov095_0229cce0(void *);
extern int func_ov095_0229c54c(void *, unsigned char, unsigned char);
extern int func_ov095_0229ba44(void *p, int b, int c);
extern int func_ov095_0229bebc(void *p, int b);
extern void func_ov112_0229fd20(void *self);
extern int func_ov112_0229f900(void *self);
extern void func_ov095_0229b3ec(void *ptr);
extern int func_ov095_0229b3a0(void *p, void *q, int _x);
extern void func_ov112_0229f89c(void *self);
extern void func_ov112_0229f668(void *self);
extern void func_0200467c(int cmd);
extern int func_ov095_0229bc00(unsigned char *a, unsigned char *b, int c, unsigned char *d, int e, int f, int g, int h, int i,
                               int j);
extern void func_ov112_0229f6d4(unsigned char *p, unsigned char b);
extern void *func_ov112_0229f6b8(char *p);
extern int func_ov095_0229bb9c(void *receiver, int value);
extern int func_ov095_0229bb98(void *receiver, int value);
extern int func_ov095_0229bb94(void *receiver, int value);
extern int func_ov095_0229bba0(char *a, char *b, void *c, int d);
extern void func_02051bf8(void *p, int size);
extern void func_02051c08(void *dst, void *src, int n);
extern void func_ov095_022999f4(void *receiver);
extern void func_ov112_0229f488(void *p);
extern void func_ov095_0229b394(void *p);
extern int func_02051c8c_unk(void *p, int len);
extern void func_ov095_022999e8(void *receiver);
extern void func_ov095_0229b388(void *p);
extern void func_ov112_0229f45c(void *object, unsigned char flags, int mode);
extern void func_ov112_0229fe60(int a, int b);
extern void func_ov112_0229f1f4(int a);
extern void func_ov112_0229f8e4(int a);
extern void func_02077ed4(void *ptr);
extern void func_ov112_0229efe8(void *this);
extern int func_020984e8(void);
extern int func_02099640(int);
extern void func_0209a8c4(void *);
extern void func_ov112_0229fb7c(int, int);
extern void func_ov002_02208090(int, int);
extern void func_ov112_0229f404(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);

int func_ov112_022a03ac(void *self, int b);
int func_ov112_022a02f4(UnkStruct_022a02f4 *self, int flag);
int func_ov112_022a0258(void *param1, int param2);
int func_ov112_022a01b0(char *p, int mode);
void func_ov112_022a0144(void *arg);
void func_ov112_022a00ac(void *p);
void func_ov112_022a0068(int param);
void func_ov112_022a0028(int param);
void func_ov112_0229ffdc(void *this);
void func_ov112_0229ffa0(void *arg);
void func_ov112_0229ff50(void *receiver);
int func_ov112_0229fefc(int param);

void func_ov112_022a0804(void *self)
{
    if (func_0208e484((char *) self + 0x4448)) {
        if (*(unsigned char *) ((char *) self + 0xc2)) {
            func_ov112_0229ffa0(self);
        } else {
            func_ov112_0229ffdc(self);
        }
    }
}

void func_ov112_022a0798(u8 *self)
{
    if (func_ov002_0220a700(self + 0x427c) != 0) {
        if (func_0208e4bc(self + 0x4448) != 0) {
            int v1 = func_ov002_0220a6e0(self + 0x427c);
            int v2 = func_ov002_0220a768(self + 0x427c, -1);
            int v3 = func_ov002_0220a72c(self + 0x427c, -1);
            func_ov002_0220a0b4(self + 0x4448, v1 + v2, v1 + v3);
        }
    } else {
        func_ov112_0229f3e0((void *) self);
        func_ov002_022080a0(self, 1);
    }
}

void func_ov112_022a0768(UnkStruct_022a0768 *a)
{
    func_ov095_0229bf48(&a->unk_384);
    if (func_ov002_0220b8ac(&a->unk_244, 1) != 0) {
        func_ov112_0229fefc((int) a);
    }
}

int func_ov112_022a0710(void *self)
{
    int r;
    volatile Reg *reg = (volatile Reg *) data_021fbe40;
    if ((reg->flag & 1) == 0) {
        return 0;
    }
    r = func_ov095_02299a00((char *) self + 0x384);
    if (r == -1) {
        return 0;
    }
    func_ov095_0229c448((char *) self + 0x384, r, 9);
    func_ov095_0229c8e4((char *) self + 0x384, r);
    func_ov112_0229f29c(self);
    return 1;
}

int func_ov112_022a06b8(unsigned char *self)
{
    if (((*(unsigned short *) data_021fbe40) & 2) == 0) {
        return 0;
    }
    if (func_ov112_022a02f4((UnkStruct_022a02f4 *) self, 0)) {
        func_ov095_0229bf3c(self + 0x384);
        self[0xc1] = self[0x8d];
        func_ov002_02208098(self, 11);
    } else {
        func_ov112_0229f3e0(self);
        func_ov112_022a0028((int) self);
    }
    return 1;
}

int func_ov112_022a0620(struct UnkStruct_022a0620 *self)
{
    if (((*(struct Global { unsigned char pad_00[2]; unsigned short flag; } *) data_021fbe40).flag & 0x800) == 0) {
        return 0;
    }

    if (func_ov112_0229fe70(self, 0x800)) {
        func_ov112_0229fe50(self, 0x800);
    } else {
        func_ov112_0229fe60((int) self, 0x800);
        func_ov112_0229fab4(self);
    }

    if (func_ov095_0229cda4(&self->unk_384, -1) != 0) {
        if (func_ov112_0229fe70(self, 0x800)) {
            func_ov002_0220a2b4(&self->unk_4448);
            func_ov002_02208098(self, 0xC);
        } else {
            func_ov002_0220a314(&self->unk_4448);
            func_ov002_02208098(self, 0x6);
        }
        func_ov112_0229f35c(self);
    } else {
        func_ov112_0229f35c(self);
    }
    return 1;
}

int func_ov112_022a05b0(void *param)
{
    if (!(((unsigned short *) data_021fbe40)[1] & 0x100)) {
        return 0;
    }

    if (func_ov095_0229cf64((char *) param + 0x384, 0xc)) {
        return 0;
    }

    func_ov112_022a03ac(param, 0x119);
    func_ov095_0229c8e4((char *) param + 0x384, 0x10a);
    func_ov112_0229f2bc(param);

    *((unsigned char *) param + 0xc1) = *((unsigned char *) param + 0x8d);

    func_ov002_02208098(param, 0xf);
    return 1;
}

int func_ov112_022a0548(unsigned char *self)
{
    if (!(((unsigned short *) data_021fbe40)[1] & 0x200)) {
        return 0;
    }

    if (func_ov095_0229cf64((void *) (self + 0x384), 11) != 0) {
        return 0;
    }

    func_ov112_022a03ac((void *) self, 0x118);
    func_ov095_0229c8e4((void *) (self + 0x384), 0x109);
    *(self + 0xc1) = *(self + 0x8d);
    func_ov002_02208098((void *) self, 14);
    return 1;
}

int func_ov112_022a051c(void *param)
{
    if (!(((unsigned short *) data_021fbe40)[1] & 8)) {
        return 0;
    } else {
        func_ov112_0229f3e0(param);
        func_ov112_022a0068((int) param);
        return 1;
    }
}

void *func_ov112_022a04b8(void *self)
{
    int id;
    int tmp;
    void *result;

    func_ov095_0229cce0((char *) self + 0x384);
    id = func_ov095_0229c54c((char *) self + 0x384, data_021f6c58, data_021f6c54);
    if (id == -1) {
        return 0;
    }
    tmp = func_ov095_0229c448((char *) self + 0x384, id, 9);
    result = (void *) func_ov112_022a03ac(self, tmp);
    func_ov095_0229c8e4((char *) self + 0x384, id);
    func_ov095_0229bf3c((char *) self + 0x384);
    return result;
}

int func_ov112_022a03ac(void *self, int b)
{
    int result = 1;
    int ret;

    ret = func_ov095_0229ba44((char *) self + 0x384, b, 6);
    if (ret != 0) {
        func_ov112_0229fd20(self);
        return ret;
    }

    if (func_ov095_0229bebc((char *) self + 0x384, b) != 0) {
        switch (b) {
            case 0x100:
                func_ov112_022a02f4((UnkStruct_022a02f4 *) self, result);
                break;
            case 0x103:
            case 0x104:
            case 0x105:
                if (func_ov112_022a01b0((char *) self, b) == 0) {
                    func_ov112_0229ff50(self);
                }
                result = 2;
                break;
            case 0x118:
                func_ov112_022a0144(self);
                result = 2;
                break;
            case 0x119:
                func_ov112_022a00ac(self);
                result = 2;
                break;
            case 0x113:
                func_ov112_022a0068((int) self);
                result = 3;
                break;
            case 0x115:
                func_ov112_022a0028((int) self);
                result = 3;
                break;
            default:
                result = 2;
                break;
        }
    } else {
        if (func_ov112_022a0258(self, (u16) ((u16) b)) == 0) {
            func_ov112_0229ff50(self);
        }
        if (b == 10) {
            result = 2;
        }
    }

    return result;
}

int func_ov112_022a02f4(UnkStruct_022a02f4 *self, int flag)
{
    if (func_ov112_0229f900(self) != 0) {
        func_ov095_0229b3ec((char *) self + 0x384);
        func_ov112_0229f89c(self);
        goto fail_ret;
    }

    if (self->unk_BD > self->unk_C0) {
        if (func_ov095_0229b3a0((char *) self + 0x384, &self->arr_c4[0], self->unk_BD) != 0) {
            goto fail_ret;
        }
        self->unk_BE = self->unk_BD;
        self->unk_BF = self->unk_BD - 1;
        func_ov112_0229f89c(self);
        goto fail_ret;
    } else {
        if (self->arr_c4[self->unk_C0] != 0) {
            self->unk_BE = self->unk_C0;
            self->unk_BF = self->unk_C0 + 1;
            func_ov112_0229f89c(self);
            goto fail_ret;
        } else {
            if (flag != 0) {
                func_ov112_0229ff50(self);
            }
            return 0;
        }
    }

fail_ret:
    func_0200467c(0x35);
    func_ov112_0229fd20(self);
    func_ov112_0229f668(self);
    return 1;
}

int func_ov112_022a029c(unsigned char *p, int a, int b)
{
    unsigned char c = p[0xbd];
    if (func_ov095_0229bc00(p + 0x384, p + 0xc4, a, &c, 0x60, 0x10, 6, 0xa0, 0, b)) {
        func_ov112_0229f6d4(p, c);
        return 1;
    }
    return 0;
}

int func_ov112_022a0258(void *param1, int param2)
{
    int result;

    if (func_ov112_0229f900(param1)) {
        func_ov112_0229f89c(param1);
        func_ov095_0229b3ec((char *) param1 + 0x384);
    }
    result = func_ov112_022a029c((unsigned char *) param1, param2, 1);
    func_ov112_0229fd20(param1);
    func_ov112_0229f668(param1);
    return result;
}

int func_ov112_022a01b0(char *p, int mode)
{
    void *res;
    volatile int limits[2];

    res = func_ov112_0229f6b8(p);
    if (res == 0) {
        return 0;
    }

    switch (mode) {
        case 0x103:
            res = (void *) func_ov095_0229bb9c(p + 0x384, (int) res);
            break;
        case 0x104:
            res = (void *) func_ov095_0229bb98(p + 0x384, (int) res);
            break;
        case 0x105:
            res = (void *) func_ov095_0229bb94(p + 0x384, (int) res);
            break;
        default:
            break;
    }

    if (res == 0) {
        return 0;
    }

    limits[0] = 0x60;
    limits[1] = 0x2710;
    if (!func_ov095_0229bba0(p + 0x384, p + 0xc4, res, *(unsigned char *) (p + 0xbd))) {
        return 0;
    }

    func_ov112_0229fd20((void *) p);
    func_ov112_0229f668((void *) p);
    return 1;
}

void func_ov112_022a0144(void *arg)
{
    unsigned char b_bf;
    unsigned char b_be;
    unsigned int min;
    unsigned int diff;

    if (func_ov112_0229f900(arg) == 0) {
        return;
    }

    b_bf = *((unsigned char *) arg + 0xbf);
    b_be = *((unsigned char *) arg + 0xbe);
    if (b_be > b_bf) {
        min = b_bf;
        diff = b_be - b_bf;
    } else {
        min = b_be;
        diff = b_bf - b_be;
    }

    func_02051bf8((char *) arg + 0x184, 0x60);
    func_02051c08((char *) arg + 0xC4 + min * 2, (char *) arg + 0x184, diff);
    func_ov112_0229fe60((int) arg, 0x200);
    func_ov095_022999f4((char *) arg + 0x384);
    func_ov112_0229f488(arg);
}

void func_ov112_022a00ac(void *p)
{
    int count;
    int i, j;

    if (func_ov112_0229fe70(p, 0x200) == 0) {
        return;
    }

    if (func_ov112_0229f900(p) != 0) {
        func_ov112_0229f89c(p);
    }

    func_ov095_0229b3ec((char *) p + 0x384);
    func_ov095_0229b394((char *) p + 0x384);

    count = func_02051c8c_unk((char *) p + 0x184, 0x60);

    for (i = 0, j = i; i < count; i++) {
        if (func_ov112_022a029c((unsigned char *) p, (unsigned short) (*(unsigned short *) ((char *) p + i * 2 + 0x184)), j) == 0) {
            if (i == 0) {
                func_ov112_0229ff50((void *) p);
            }
            i = count;
        }
    }

    func_ov095_022999e8((char *) p + 0x384);
    func_ov112_0229fd20(p);
    func_ov112_0229f668(p);
    func_ov095_0229b388((char *) p + 0x384);
}

void func_ov112_022a0068(int param)
{
    func_0200467c(0x29);
    func_ov112_0229fe50((void *) param, 0x2000);
    func_ov112_0229f45c((void *) param, 2, 9);
    func_ov112_0229fe60(param, 0x400);
    func_ov112_0229f1f4(param);
    func_ov112_0229f8e4(param);
    func_ov112_0229fd20((void *) param);
}

void func_ov112_022a0028(int param)
{
    func_0200467c(0x2a);
    func_ov112_0229fe60(param, 0x2000);
    func_ov112_0229f45c((void *) param, 2, 8);
    func_ov112_0229fe60(param, 0x400);
    func_ov112_0229f8e4(param);
    func_ov112_0229fd20((void *) param);
}

void func_ov112_0229ffdc(void *this)
{
    func_ov112_0229f45c(this, 10, 3);
    if (func_ov112_0229fe70(this, 0x2000) != 0) {
        func_0200467c(0x28);
    } else {
        func_02077ed4((char *) this + 0xC4);
        func_0200467c(0x27);
        func_ov112_0229efe8(this);
        func_0209a8c4((void *) func_02099640((int) func_020984e8()));
    }
}

void func_ov112_0229ffa0(void *arg)
{
    if (func_ov112_0229fe70(arg, 0x2000) != 0) {
        func_0200467c(0x29);
    } else {
        func_0200467c(0x2a);
    }

    func_ov112_0229f45c(arg, 6, 4);
    func_ov112_0229fe50(arg, 0x400);
}

void func_ov112_0229ff5c(int param)
{
    func_0200467c(0x28);
    func_ov112_0229fe50((void *) param, 0x40);
    func_ov112_0229f3e0((void *) param);
    func_ov112_0229fb7c(param, 0);
    func_ov002_02208090(param, 0xc);
    func_ov002_022080a0((u8 *) param, 1);
    func_ov112_0229fe60(param, 0x2000);
}

void func_ov112_0229ff50(void *receiver)
{
    func_0200467c(0x34);
}

unsigned char *func_ov112_0229ff38(void *p)
{
    func_ov112_0229f3e0((void *) p);
    return func_ov002_02208098(p, 0);
}

unsigned char *func_ov112_0229ff1c(void *arg)
{
    func_ov002_02207fc0(arg);
    func_ov112_0229f404(arg);
    return func_ov002_02208098(arg, 6);
}

int func_ov112_0229fefc(int param)
{
    if (func_0206fe60() != 0) {
        return (int) func_ov112_0229ff38((void *) param);
    } else {
        return (int) func_ov112_0229ff1c((void *) param);
    }
}

int func_ov112_0229fee4(int param)
{
    func_ov112_0229f3e0((void *) param);
    return (int) func_ov002_02208098((void *) param, 5);
}
