/* pockets_swap_2: 12 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229cba4 @ 0x0229cba4, 0x70 bytes, Thumb
 * func_ov107_0229cb78 @ 0x0229cb78, 0x2c bytes, Thumb
 * func_ov107_0229cb3c @ 0x0229cb3c, 0x3c bytes, Thumb
 * func_ov107_0229cb14 @ 0x0229cb14, 0x28 bytes, Thumb
 * func_ov107_0229caa8 @ 0x0229caa8, 0x6c bytes, Thumb
 * func_ov107_0229c9e4 @ 0x0229c9e4, 0xc4 bytes, Thumb
 * func_ov107_0229c990 @ 0x0229c990, 0x54 bytes, Thumb
 * func_ov107_0229c894 @ 0x0229c894, 0xfc bytes, Thumb
 * func_ov107_0229c824 @ 0x0229c824, 0x70 bytes, Thumb
 * func_ov107_0229c7b0 @ 0x0229c7b0, 0x74 bytes, Thumb
 * func_ov107_0229c740 @ 0x0229c740, 0x70 bytes, Thumb
 * func_ov107_0229c720 @ 0x0229c720, 0x1e bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
    char pad_BA[0x2112];
    char unk_21CC[1];
    char pad_21CD[0x14b];
    char unk_2318[0x3e8];
    char unk_2700[1];
} UnkStruct_0229cba4;

struct UnkStruct_0229cb3c {
    unsigned char pad_00[0x8C];
    unsigned char unk_8C;
    unsigned char pad_8D[0xB9 - 0x8D];
    unsigned char unk_B9;
};

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
} UnkStruct_0229caa8;

typedef struct {
    char pad_00[0xb9];
    volatile u8 unk_B9;
} UnkStruct_0229c9e4;

struct UnkStruct_0229c894 {
    unsigned char pad_00[0xb8];
    unsigned char unk_B8;
};

struct UnkStruct_0229c7b0 {
    unsigned char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_0229c7b0_2 {
    unsigned char pad_00[0xac];
    int unk_AC;
    unsigned char pad_B0[0xb9 - (0xac + 4)];
    unsigned char unk_B9;
};

typedef struct {
    char pad_00[0xAC];
    int unk_AC;
    char pad_B0[0xBE - 0xAC - 4];
    char unk_BE;
} UnkStruct_0229c740;

extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov107_0229d29c(void *self, unsigned char b);
extern int func_ov107_0229d260(void *self, unsigned char b);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov107_0229cce8(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_0206fc80(int);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov107_0229ce90(struct UnkStruct_0229cb3c *);
extern void *func_ov002_0220a720(void *addr, int val);
extern void func_0200467c(unsigned int cmd);
extern int func_0206f6a4(void);
extern void func_02061e2c(unsigned short *dst, unsigned short *src);
extern int func_0209a19c(void);
extern int func_020984e8(void);
extern int func_020996ac(int argument0);
extern int func_0203cd2c(int a, void *b, int c, int d);
extern int func_ov107_0229d0f0(UnkStruct_0229caa8 *p, unsigned char b);
extern void func_0206f698(int value);
extern void func_ov107_0229d2d8(UnkStruct_0229caa8 *p, unsigned char b, int c, int d);
extern unsigned char func_0206f9c0(void);
extern int func_0206fca4(void);
extern int func_ov002_02208d4c(void *p, int a, int b);
extern int func_ov094_022999e4(int id);
extern void func_ov002_02208d30(void *addr, int a);
extern int func_ov107_0229d388(void *obj, int val);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088bc(void *p);
extern void func_ov002_0220a314(void *p);
extern void func_ov107_0229c2a4(struct UnkStruct_0229c894 *self, int n);
extern int func_ov107_0229c2b4(struct UnkStruct_0229c894 *self, int n);
extern void func_ov107_0229c294(void *, int);
extern void func_ov002_0220a2b4(void *);
extern int func_020435a0(int, int);
extern int func_02043568(int, int);
extern void func_ov107_0229d480(void *);
extern void func_ov107_0229d3a0(void *, int, int);
extern struct UnkStruct_0229c7b0 *data_020ccf94;
extern int func_020431c8(int);
extern void func_020431b8(int);
extern void func_ov107_0229c2c8(void *, int);
extern void func_ov107_0229c670(void *p);

void func_ov107_0229cba4(UnkStruct_0229cba4 *self, int flag)
{
    int ret1, ret2;

    func_ov002_02208c58(self->unk_2318, self->unk_2700, 0);
    ret1 = func_ov107_0229d29c(self, self->unk_B9);
    ret2 = func_ov107_0229d260(self, self->unk_B9);

    if (flag != 0) {
        func_ov002_02209874(self->unk_2318, self->unk_21CC);
    } else {
        func_ov002_02209910(self->unk_2318, ret1, ret2);
    }

    func_ov002_0220970c(self->unk_2318, 0);
    func_ov002_02208098((void *) (self), 0xb);
}

void func_ov107_0229cb78(void *self)
{
    char *p;
    p = (char *) self + 0xbc;
    *p = 4;
    func_ov107_0229cce8(self);
    func_ov002_022096d8((char *) self + 0x2318, 0);
    func_ov002_02208098((void *) (self), 0xd);
}

void func_ov107_0229cb3c(struct UnkStruct_0229cb3c *self)
{
    func_0206fc80(self->unk_B9);
    func_0206fc4c(1);
    self->unk_8C = 3;
    func_ov002_022080a0((void *) (self), 1);
    func_ov002_02207d24((char *) self + 0x21CC, 1);
    func_ov107_0229ce90(self);
}

void func_ov107_0229cb14(void *param)
{
    func_ov002_0220a720((char *) param + 0x2828, 9);
    func_ov002_02208098((void *) (param), 15);
    func_0200467c(0x28);
}

void func_ov107_0229caa8(UnkStruct_0229caa8 *param)
{
    unsigned short local[2];
    int val;
    int flag;
    int res;

    local[0] = (unsigned short) func_0206f6a4();
    func_02061e2c(&local[1], local);
    val = local[1];
    flag = 0;
    if (val == 0x156b) {
        val = func_0209a19c();
        flag = 1;
    }

    res = func_020996ac((int) func_020984e8());
    func_0203cd2c(res, &local[1], 0, 1);

    func_0206f698(func_ov107_0229d0f0(param, param->unk_B9));
    func_ov107_0229d2d8(param, param->unk_B9, val, flag);
}

void func_ov107_0229c9e4(UnkStruct_0229c9e4 *self)
{
    volatile u16 t;
    unsigned int ok;
    u16 lo;
    u16 hi;
    int id;
    int k;

    func_0206f9c0();
    id = func_ov107_0229d0f0((UnkStruct_0229caa8 *) self, self->unk_B9);
    t = id;
    k = func_0206fca4();
    ok = 0;
    lo = t;
    hi = t;
    if (hi >= 0x12b0 && lo <= 0x12e7) {
        ok = 1;
    }
    if (ok != 0) {
        func_ov002_02208d4c((char *) self + 0x2700, 0x10, 0);
    } else if (lo >= 0x12e8 && lo <= 0x131f) {
        func_ov002_02208d4c((char *) self + 0x2700, 0x10, 2);
    } else if (k == 0x2a) {
        func_ov002_02208d4c((char *) self + 0x2700, 0x10, 3);
    }
    if (func_ov094_022999e4(id) != 0) {
        if (k == 0x2a) {
            func_ov002_02208d4c((char *) self + 0x2700, 1, 1);
        } else {
            func_ov002_02208d4c((char *) self + 0x2700, 0x10, 1);
        }
    }
    func_ov002_02208d4c((char *) self + 0x2700, 2, 4);
}

void func_ov107_0229c990(void *obj, int val, int flag)
{
    *(unsigned char *) ((char *) obj + 0xb9) = val;
    func_ov002_02208d30((char *) obj + 0x2700, 4);
    if (func_ov107_0229d388(obj, val)) {
        func_ov107_0229c9e4((UnkStruct_0229c9e4 *) obj);
        func_ov107_0229ce90((struct UnkStruct_0229cb3c *) obj);
        if (flag == 0) {
            func_ov002_02207d24((char *) obj + 0x21cc, 1);
        }
        func_ov107_0229cba4((UnkStruct_0229cba4 *) obj, flag);
    }
}

void func_ov107_0229c894(struct UnkStruct_0229c894 *self, void *p)
{
    int b = self->unk_B8;
    int count = 0;

    while (b >= 5) {
        b -= 5;
        count++;
    }

    if (func_ov002_022088ac(p) != 0) {
        if (func_ov002_022088cc(p) == 0 || count == 0) {
            if (b == 0) {
                self->unk_B8 += 4;
                func_ov107_0229c2a4(self, 8);
            } else {
                self->unk_B8 -= 1;
            }
        }
    } else {
        if (func_ov002_0220889c(p) != 0 && func_ov002_022088bc(p) == 0) {
            if (b == 4) {
                self->unk_B8 -= 4;
                func_ov107_0229c2a4(self, 0x10);
            } else {
                self->unk_B8 += 1;
            }
        }
    }

    if (func_ov107_0229c2b4(self, 0x18) != 0) {
        return;
    }

    if (func_ov002_022088cc(p) != 0) {
        if (count > 0) {
            self->unk_B8 -= 5;
            return;
        }
    } else {
        if (func_ov002_022088bc(p) != 0) {
            if (count < 2) {
                self->unk_B8 += 5;
            } else {
                self->unk_B8 = 0xf;
                func_ov002_0220a314((char *) self + 0x22b4);
            }
        }
    }
    return;
}

int func_ov107_0229c824(void *obj, int p1)
{
    unsigned char orig = *(unsigned char *) ((char *) obj + 0xb8);
    func_ov107_0229c294(obj, 0x18);
    if (p1 == 0) {
        return 0;
    }
    if (func_ov107_0229d388(obj, (unsigned char) (*(unsigned char *) ((char *) obj + 0xb8))) != 0) {
        func_ov107_0229c894((struct UnkStruct_0229c894 *) obj, (void *) p1);
    } else {
        if (*(unsigned char *) ((char *) obj + 0xb8) == 0xf && func_ov002_022088cc((void *) p1) != 0) {
            *(unsigned char *) ((char *) obj + 0xb8) = 0xe;
            func_ov002_0220a2b4((char *) obj + 0x22b4);
        }
    }
    if (orig == *(unsigned char *) ((char *) obj + 0xb8)) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov107_0229c7b0(struct UnkStruct_0229c7b0_2 *self)
{
    int result;

    result = func_ov107_0229d0f0((UnkStruct_0229caa8 *) self, self->unk_B9);

    if (func_0206fca4() == 0x29) {
        self->unk_AC = func_020435a0(data_020ccf94->unk_64, result);
    } else {
        self->unk_AC = func_02043568(data_020ccf94->unk_64, result);
    }

    if (self->unk_AC == -1) {
        func_ov107_0229d480(self);
        func_ov107_0229d3a0(self, 3, 0xff);
    } else {
        func_ov002_02208098((void *) (self), 0x15);
    }
}

void func_ov107_0229c740(UnkStruct_0229c740 *p)
{
    int ret = func_020431c8(p->unk_AC);
    switch (ret) {
        case 1:
            func_ov107_0229c2c8(p, 0);
            func_ov107_0229caa8((UnkStruct_0229caa8 *) p);
            func_020431b8(p->unk_AC);
            p->unk_BE = 0xa;
            func_ov002_02208098((void *) (p), 0x13);
            p->unk_AC = -1;
            break;
        case 2:
            func_020431b8(p->unk_AC);
            func_ov107_0229d480(p);
            func_ov107_0229d3a0(p, 3, 0xff);
            p->unk_AC = -1;
            break;
        default:
            break;
    }
}

void func_ov107_0229c720(void *p)
{
    func_ov107_0229c2c8(p, 1);
    func_ov002_02208098((void *) (p), 0x10);
    func_ov107_0229c670(p);
}
