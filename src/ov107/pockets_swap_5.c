/* pockets_swap_5: 46 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229dbf4 @ 0x0229dbf4, 0x8 bytes, Thumb
 * func_ov107_0229dbb4 @ 0x0229dbb4, 0x40 bytes, Thumb
 * func_ov107_0229db7c @ 0x0229db7c, 0x38 bytes, Thumb
 * func_ov107_0229db5c @ 0x0229db5c, 0x1e bytes, Thumb
 * func_ov107_0229db48 @ 0x0229db48, 0x14 bytes, Thumb
 * func_ov107_0229db24 @ 0x0229db24, 0x24 bytes, Thumb
 * func_ov107_0229daa4 @ 0x0229daa4, 0x80 bytes, Thumb
 * func_ov107_0229da04 @ 0x0229da04, 0xa0 bytes, Thumb
 * func_ov107_0229d9e8 @ 0x0229d9e8, 0x1c bytes, Thumb
 * func_ov107_0229d9a0 @ 0x0229d9a0, 0x48 bytes, Thumb
 * func_ov107_0229d908 @ 0x0229d908, 0x98 bytes, Thumb
 * func_ov107_0229d828 @ 0x0229d828, 0xe0 bytes, Thumb
 * func_ov107_0229d7b0 @ 0x0229d7b0, 0x78 bytes, Thumb
 * func_ov107_0229d764 @ 0x0229d764, 0x4c bytes, Thumb
 * func_ov107_0229d720 @ 0x0229d720, 0x44 bytes, Thumb
 * func_ov107_0229d6e8 @ 0x0229d6e8, 0x38 bytes, Thumb
 * func_ov107_0229d6c0 @ 0x0229d6c0, 0x28 bytes, Thumb
 * func_ov107_0229d684 @ 0x0229d684, 0x3c bytes, Thumb
 * func_ov107_0229d634 @ 0x0229d634, 0x50 bytes, Thumb
 * func_ov107_0229d614 @ 0x0229d614, 0x20 bytes, Thumb
 * func_ov107_0229d5e0 @ 0x0229d5e0, 0x34 bytes, Thumb
 * func_ov107_0229d558 @ 0x0229d558, 0x88 bytes, Thumb
 * func_ov107_0229d530 @ 0x0229d530, 0x26 bytes, Thumb
 * func_ov107_0229d508 @ 0x0229d508, 0x26 bytes, Thumb
 * func_ov107_0229d4f0 @ 0x0229d4f0, 0x18 bytes, Thumb
 * func_ov107_0229d4d4 @ 0x0229d4d4, 0x1c bytes, Thumb
 * func_ov107_0229d4a0 @ 0x0229d4a0, 0x34 bytes, Thumb
 * func_ov107_0229d480 @ 0x0229d480, 0x20 bytes, Thumb
 * func_ov107_0229d3f8 @ 0x0229d3f8, 0x88 bytes, Thumb
 * func_ov107_0229d3a0 @ 0x0229d3a0, 0x58 bytes, Thumb
 * func_ov107_0229d394 @ 0x0229d394, 0xc bytes, Thumb
 * func_ov107_0229d388 @ 0x0229d388, 0xc bytes, Thumb
 * func_ov107_0229d36c @ 0x0229d36c, 0x1a bytes, Thumb
 * func_ov107_0229d35c @ 0x0229d35c, 0xe bytes, Thumb
 * func_ov107_0229d31c @ 0x0229d31c, 0x40 bytes, Thumb
 * func_ov107_0229d2d8 @ 0x0229d2d8, 0x44 bytes, Thumb
 * func_ov107_0229d29c @ 0x0229d29c, 0x3c bytes, Thumb
 * func_ov107_0229d260 @ 0x0229d260, 0x3c bytes, Thumb
 * func_ov107_0229d224 @ 0x0229d224, 0x3c bytes, Thumb
 * func_ov107_0229d190 @ 0x0229d190, 0x94 bytes, Thumb
 * func_ov107_0229d15c @ 0x0229d15c, 0x34 bytes, Thumb
 * func_ov107_0229d128 @ 0x0229d128, 0x34 bytes, Thumb
 * func_ov107_0229d0f0 @ 0x0229d0f0, 0x38 bytes, Thumb
 * func_ov107_0229d0bc @ 0x0229d0bc, 0x34 bytes, Thumb
 * func_ov107_0229d098 @ 0x0229d098, 0x24 bytes, Thumb
 * func_ov107_0229d054 @ 0x0229d054, 0x44 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned char b0;                    // 0xb6
    unsigned char pad_B7[8];             // 0xb1..0xb8
    unsigned char b9;                    // 0xbf
    unsigned char pad_C0[0x21cc - 0xba]; // 0xba..
} UnkStruct_0229da04;

struct UnkStruct_0229d9a0 {
    char pad_00[182];
    unsigned char unk_B6;
    char pad_B7[8];
    unsigned char unk_BF;
    char pad_C0[8460];
    char unk_21CC;
};

struct FlagsStruct {
    unsigned short unk_00;
    unsigned short flags;
};

typedef struct {
    unsigned char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char unk_BD;
    unsigned char pad_BE[0x22b4 - 0xbe];
    char unk_22B4[0x2318 - 0x22b4];
    char unk_2318[0x2705 - 0x2318];
    unsigned char table[0x100];
} UnkStruct_0229d764;

typedef struct Something {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    unsigned char pad_A4[0xb6 - (0xa0 + 4)];
    unsigned char unk_B6;
    unsigned char unk_B7;
    unsigned char pad_B8[0xbf - (0xb7 + 1)];
    unsigned char unk_BF;
    unsigned char pad_C0[0x21cc - (0xbf + 1)];
    char unk_21CC;
} Something;

extern void func_ov094_0229a084(int arg);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov107_0229cfe4(void *);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int a, int b);
extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_02208054(void *self, int flag);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_0220a784(void *ptr, int x);
extern void func_ov107_0229cb14(void *param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02207ce4(void *sub, int v);
extern int func_ov002_02207cc0(int object);
extern void func_ov107_0229dea4(void *self);
extern void func_ov107_0229c990(void *self, unsigned char b, int v);
extern void func_ov002_02207d00(void *sub);
extern int func_ov002_02208e28(unsigned char *);
extern void func_ov107_0229cb78(unsigned char *);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern void func_ov002_02209114(unsigned char *, int, int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(unsigned char *self);
extern int func_ov107_0229c824(unsigned char *self, int val);
extern void func_ov107_0229cf90(unsigned char *self);
extern void func_ov107_0229ce1c(unsigned char *self);
extern void func_ov107_0229cca8(unsigned char *self);
extern unsigned short data_021fbe40[];
extern int func_ov002_02209044(char *, int, char *, int);
extern void func_ov002_0220a1dc(char *);
extern void func_ov107_0229cdcc(char *);
extern void func_ov107_0229cd68(char *);
extern int func_0208e484(void *);
extern int func_ov002_02209f64(void *p0);
extern void *func_ov002_0220a720(void *addr, int n);
extern void func_0200467c(int cmd);
extern void func_ov107_0229ccc8(int);
extern int func_0206fe54(void);
extern void func_ov107_0229cd1c(int);
extern int func_ov002_0220909c(void *p);
extern void func_ov002_022096d8(void *p, int x);
extern int func_ov002_02207d24(void *p, int x);
extern int func_0208e4bc(void *p);
extern void func_ov107_0229cce8(void *p);
extern void func_ov107_0229cc14(void *);
extern int func_ov002_02208e18(void *);
extern int func_ov002_0220b8ac(void *ptr, int val);
extern void func_0208e5cc(void *ptr);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov107_0229ce90(void *);
extern int func_ov107_0229c354(void *receiver);
extern int func_ov003_0222ea84(int);
extern void func_ov107_0229cb3c(void *p);
extern int func_02096144(void);
extern void func_ov107_0229cf08(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void func_ov002_02207cf8(char *p);
extern void func_ov094_022999cc(void);
extern unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *dst, const void *src, int a, int b);
extern void func_0208e5c4(void *self);
extern void func_020b9ccc(void *ptr);
extern int func_ov094_0229aee8(int, int unused1, int unused2);
extern int func_ov094_0229a69c(int, int);
extern void func_ov094_0229aa14(int a, int b, int c, int d);
extern void func_ov094_0229a9b4(int a, int b);
extern int func_ov094_0229aba4(char *p, int q);
extern int func_ov094_0229ab90(void *a, int b);
extern void func_ov094_0229a888(void *ptr, int value);
extern int func_ov107_0229c2b4(void *self, int a);
extern int func_ov094_0229a8bc(char *p1, int p2);
extern int func_ov094_0229aaac(void *p0, int p1);
extern int func_ov094_0229aa84(char *p, int v);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229ab1c(char *arg1, int arg2);

void func_ov107_0229db7c(void *self);
void func_ov107_0229d4d4(void *r0);
void func_ov107_0229d4a0(void *self);
void func_ov107_0229d3f8(Something *p, int val);
void func_ov107_0229d394(char *ptr);
int func_ov107_0229d388(unsigned int param1, unsigned int param2);
int func_ov107_0229d31c(int a, int b, int c, int d);
int func_ov107_0229d29c(char *param1, int param2);
int func_ov107_0229d260(void *a, int b);
int func_ov107_0229d190(void *self, void *p);
int func_ov107_0229d15c(char *p1, int p2);
int func_ov107_0229d128(char *param0, int param1);
int func_ov107_0229d0f0(void *p0, void *p1);
int func_ov107_0229d0bc(char *p, int q);
void func_ov107_0229d098(void *self);
void func_ov107_0229d054(char *p0, int p1);

void func_ov107_0229dbf4(void *argument0)
{
    func_ov107_0229db7c(argument0);
}

void func_ov107_0229dbb4(void *p)
{
    func_ov107_0229d394((char *) p);
    func_ov094_0229a084((int) ((char *) p + 0xb94));
    func_ov094_0229af20((char *) p + 0x10c);
    func_ov094_0229bbc0((char *) p + 0xb6c);
    func_ov002_0220af74((char *) p + 0x2828);
}

void func_ov107_0229db7c(void *self)
{
    func_ov002_022091cc((char *) self + 0x2318);
    func_ov094_0229a05c((char *) self + 0xb94);
    if (func_ov002_02207d5c((char *) self + 0x21cc)) {
        func_ov107_0229cfe4(self);
    }
}

void func_ov107_0229db5c(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov107_0229db48(int r0)
{
    func_ov094_0229a29c(r0 + 0xb94, 0);
}

void func_ov107_0229db24(void *arg0)
{
    func_ov094_0229a098((void *) ((char *) arg0 + 0xb94));
    func_ov002_0220af94((void *) ((char *) arg0 + 0x2828));
}

void func_ov107_0229daa4(void *self)
{
    int result;
    int cond;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov107_0229d4a0(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto isfalse;
    }
    if (data_021fbddc == 0) {
        goto isfalse;
    }
    cond = 1;
    goto done;
isfalse:
    cond = 0;
done:
    if (cond == 0) {
        return;
    }
    result = func_ov107_0229d31c((int) self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (result != 0x10) {
        func_ov107_0229d3f8((Something *) self, result);
        return;
    }
    if (func_ov002_0220a784((char *) self + 0x2828, 9) != 0) {
        func_ov107_0229cb14(self);
    }
}

void func_ov107_0229da04(UnkStruct_0229da04 *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov107_0229d15c((char *) self, (unsigned char) self->b0) != 0) {
            func_ov002_02208098((void *) (self), 0);
            func_ov002_02207ce4((char *) self + 0x21cc, 0x3c);
            return;
        } else {
            func_ov002_02208098((void *) (self), 3);
            func_ov107_0229dea4(self);
            return;
        }
    } else {
        if (func_ov107_0229d15c((char *) self, (unsigned char) self->b0) == 0) {
            if (func_ov002_02207cc0((int) ((char *) self + 0x21cc)) != 0) {
                if (self->b9 != 0) {
                    self->b9--;
                    return;
                } else {
                    func_ov107_0229c990(self, self->b0, 1);
                    func_ov002_02208098((void *) (self), 2);
                    return;
                }
            }
        }
        func_ov002_02207d00((char *) self + 0x21cc);
    }
}

void func_ov107_0229d9e8(int arg)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (arg), 4);
    }
}

void func_ov107_0229d9a0(struct UnkStruct_0229d9a0 *self)
{
    if (func_ov002_02207cc0((int) (&self->unk_21CC))) {
        if (self->unk_BF) {
            self->unk_BF--;
        } else {
            func_ov107_0229c990(self, self->unk_B6, 1);
            func_ov002_02208098((void *) (self), 2);
        }
    }
}

void func_ov107_0229d908(unsigned char *p)
{
    int flag;
    int result;
    unsigned char *q;

    if (func_ov002_02208e28(p + 0x2318) == 0) {
        return;
    }
    if (func_ov002_02208054((void *) p, 1) != 0) {
        func_ov107_0229cb78(p);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        result = func_ov002_02208b00(p + 0x2318, data_021f6c58, data_021f6c54);
        if (result < 0) {
            return;
        }
        func_ov002_02209114(p + 0x2318, result, 1);
        q = p + result;
        p[0xbc] = q[0x2705];
        func_ov002_02208098((void *) (p), 0xc);
    }
}

void func_ov107_0229d828(unsigned char *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov107_0229d4d4((void *) self);
        func_ov002_02207d24((void *) (self + 0x21cc), 1);
        return;
    }

    {
        int r = func_ov002_02208008(self);
        if (func_ov107_0229c824(self, r) != 0) {
            func_ov107_0229cf90(self);
            func_ov107_0229ce1c(self);
            func_ov002_02207d24((void *) (self + 0x21cc), 0);
            return;
        }
    }

    if (func_ov107_0229d15c((char *) self, (unsigned char) self[0xb8]) != 0) {
        // nothing
    } else {
        if ((data_021fbe40[1] & 1) != 0) {
            if (func_ov107_0229d388((unsigned int) self, (unsigned char) self[0xb8]) != 0) {
                if (func_ov107_0229d128((char *) self, (unsigned char) self[0xb8]) == 0) {
                    func_ov107_0229c990((void *) self, self[0xb8], 0);
                }
                return;
            } else {
                if (self[0xb8] == 0xf) {
                    func_ov107_0229cca8(self);
                }
                return;
            }
        }
    }

    if ((data_021fbe40[1] & 2) != 0) {
        func_ov107_0229ce90((void *) self);
        func_ov107_0229cb14((void *) self);
        func_ov002_02207d24((void *) (self + 0x21cc), 0);
    } else {
        func_ov002_02207d00((void *) (self + 0x21cc));
    }
}

void func_ov107_0229d7b0(char *param)
{
    if (func_ov002_02208014(param) != 0) {
        func_ov107_0229cb78((unsigned char *) param);
        return;
    } else {
        int v = func_ov002_02208008((unsigned char *) param);
        if (func_ov002_02209044(param + 0x2318, v, param + 0xbd, 0) != 0) {
            func_ov107_0229cdcc(param);
            return;
        } else {
            unsigned short f = (*(struct FlagsStruct *) data_021fbe40).flags;
            if (f & 1) {
                func_ov002_0220a1dc(param + 0x22b4);
                func_ov002_02208098((void *) (param), 7);
                return;
            }
            if (f & 2) {
                func_ov107_0229cd68(param);
            }
        }
    }
}

void func_ov107_0229d764(UnkStruct_0229d764 *self)
{
    if (func_0208e484(self->unk_22B4)) {
        func_ov002_02209114((unsigned char *) self->unk_2318, (unsigned char) self->unk_BD, 1);
        self->unk_BC = self->table[self->unk_BD];
        func_ov002_02208098((void *) (self), 12);
    }
}

void func_ov107_0229d720(void *p0)
{
    if (func_ov002_02209f64((char *) p0 + 0x22b4) == 0) {
        func_ov002_02208098((void *) (p0), *(unsigned char *) ((char *) p0 + 0xbb));
        if (*(unsigned char *) ((char *) p0 + 0xbb) == 5) {
            func_ov107_0229d054((char *) p0, *(unsigned char *) ((char *) p0 + 0xb8));
        }
        func_ov107_0229dea4(p0);
    }
}

void func_ov107_0229d6e8(char *param)
{
    if (func_0208e484(param + 0x22b4)) {
        func_ov002_0220a720(param + 0x2828, 9);
        func_ov002_02208098((void *) (param), 0xf);
        func_0200467c(0x28);
    }
}

void func_ov107_0229d6c0(int r0)
{
    if (func_0208e484((void *) (r0 + 0x22b4))) {
        func_ov107_0229ccc8(r0);
        func_ov002_02208098((void *) (r0), 5);
    }
}

void func_ov107_0229d684(int param)
{
    if (func_ov002_02208e28((unsigned char *) (param + 0x2318)) != 0) {
        if (func_0206fe54() != 0) {
            func_ov107_0229cd1c(param);
            func_ov002_02208098((void *) (param), 6);
        } else {
            func_ov002_02208098((void *) (param), 4);
        }
    }
}

void func_ov107_0229d634(char *param)
{
    if (func_ov002_0220909c(param + 0x2318) == 0) {
        return;
    }
    func_ov002_022096d8(param + 0x2318, 0);
    func_ov002_02207d24(param + 0x21cc, 1);
    if (func_0208e4bc(param + 0x22b4)) {
        func_ov107_0229cce8(param);
    }
    func_ov002_02208098((void *) (param), 0xd);
}

void func_ov107_0229d614(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x2318)) {
        func_ov107_0229cc14(self);
    }
}

void func_ov107_0229d5e0(void *self)
{
    if (func_ov002_0220b8ac((char *) self + 0x270c, 0) != 0) {
        func_ov002_02208098((void *) (self), ((unsigned char *) self)[0xbb]);
        func_0208e5cc((char *) self + 0x22b4);
    }
}

void func_ov107_0229d558(char *p)
{
    if (func_ov002_0220a700(p + 0x2828) != 0) {
        if (func_0208e4bc(p + 0x22B4) != 0) {
            int v4 = func_ov002_0220a6e0(p + 0x2828);
            int v6 = func_ov002_0220a768(p + 0x2828, -1);
            int v2 = func_ov002_0220a72c(p + 0x2828, -1);
            func_ov002_0220a0b4(p + 0x22B4, v4 + v6, v4 + v2);
        }
    } else {
        func_0206fc4c(0);
        p[0x8C] = 3;
        func_ov002_022080a0((void *) (p), 1);
        func_ov002_02207d24(p + 0x21CC, 1);
        func_ov107_0229ce90(p);
    }
}

void func_ov107_0229d530(unsigned char *param)
{
    if (func_ov003_0222ea84(func_ov107_0229c354(param)) != 3) {
        unsigned char *q = param + 0xbe;
        *q = 5;
        func_ov002_02208098((void *) (param), 19);
    }
}

void func_ov107_0229d508(unsigned char *p)
{
    if (p[0xbe] != 0) {
        p[0xbe]--;
    } else {
        func_ov107_0229cb3c(p);
    }
}

void func_ov107_0229d4f0(int arg0)
{
    if (func_02096144() != 0) {
        func_ov107_0229cb3c((void *) arg0);
    }
}

void func_ov107_0229d4d4(void *r0)
{
    void *r4 = r0;
    func_ov107_0229ce90(r4);
    func_ov107_0229d098(r4);
    func_ov002_02208098((void *) (r4), 0);
}

void func_ov107_0229d4a0(void *self)
{
    unsigned char *p = (unsigned char *) self;
    p[0xb7] = 0x10;
    func_ov107_0229cf08(self);
    func_ov002_02207fc0(self);
    func_ov107_0229cf90((unsigned char *) self);
    func_ov002_02208098((void *) (self), 5);
    func_ov107_0229d054((char *) self, ((unsigned char *) self)[0xb8]);
}

void func_ov107_0229d480(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov107_0229d4d4((void *) r4);
    } else {
        func_ov107_0229d4a0((void *) r4);
    }
}

void func_ov107_0229d3f8(Something *p, int val)
{
    unsigned char a;
    unsigned char b;
    int r;

    p->unk_B6 = val;
    func_ov002_02208098((void *) (p), 1);
    a = data_021f6c58;
    b = data_021f6c54;
    r = func_ov107_0229d29c((char *) p, (unsigned char) p->unk_B6);
    p->unk_9C = r - a;
    r = func_ov107_0229d260((void *) p, (unsigned char) p->unk_B6);
    p->unk_A0 = r - b;
    p->unk_B7 = val;
    func_ov002_02207cf8(&p->unk_21CC);
    func_ov002_02207d00((void *) (&p->unk_21CC));
    p->unk_BF = 2;
    if (func_ov107_0229d15c((char *) p, val) == 0) {
        func_ov094_022999cc();
    }
}

void func_ov107_0229d3a0(unsigned char *self, unsigned char byte1, unsigned char byte2)
{
    if (byte2 == 0xff) {
        self[0xbb] = self[0x8d];
    } else {
        self[0xbb] = byte2;
    }
    {
        unsigned char c;
        c = data_021f43ec;
        c = byte1;
        func_ov002_0220b9b8(self + 0x270c, &c, 1, 0);
    }
    func_ov002_02208098((void *) (self), 0xe);
    func_0208e5c4(self + 0x22b4);
}

void func_ov107_0229d394(char *ptr)
{
    func_020b9ccc(ptr + 0xd4);
}

int func_ov107_0229d388(unsigned int param1, unsigned int param2)
{
    if (param2 > 14) {
        return 0;
    } else {
        return 1;
    }
}

int func_ov107_0229d36c(int a1, int a2)
{
    int r4 = a2;
    if (func_ov107_0229d388(a1, a2)) {
        return (unsigned char) r4;
    } else {
        return 0;
    }
}

unsigned char func_ov107_0229d35c(int a, unsigned int b)
{
    if (b <= 14) {
        return (unsigned char) b;
    } else {
        return 16;
    }
}

int func_ov107_0229d31c(int a, int b, int c, int d)
{
    int r6;

    r6 = func_ov094_0229aee8(a + 0x10c, b, c);
    if (r6 == 0x23) {
        goto ret10;
    }
    if (d == 0) {
        goto call3;
    }
    if (func_ov094_0229a69c(a + 0x10c, r6) == 0) {
        goto call3;
    }
    return 0x10;

call3:
    return (int) func_ov107_0229d35c(a, r6);

ret10:
    return 0x10;
}

void func_ov107_0229d2d8(int a, int b, int c, int d)
{
    int e;
    if (func_ov107_0229d388(a, b)) {
        e = func_ov107_0229d36c(a, b);
        func_ov094_0229aa14(a + 0x10c, e, c, d);
        func_ov094_0229a9b4(a + 0x10c, e);
    }
}

int func_ov107_0229d29c(char *param1, int param2)
{
    if (func_ov107_0229d388((unsigned int) param1, param2)) {
        int result = func_ov107_0229d36c((int) param1, param2);
        return func_ov094_0229aba4(param1 + 0x10c, result);
    } else {
        if (param2 == 0xf) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}

int func_ov107_0229d260(void *a, int b)
{
    if (func_ov107_0229d388((unsigned int) a, b)) {
        int x = func_ov107_0229d36c((int) a, b);
        return func_ov094_0229ab90((char *) a + 0x10c, x) - 0x10;
    } else {
        if (b == 15) {
            return 0xb6;
        }
        return 0;
    }
}

void func_ov107_0229d224(void *param)
{
    unsigned char i = 0;
    char *p = (char *) param + 0x10c;
    do {
        if (func_ov107_0229d190(param, (void *) i)) {
            func_ov094_0229a888(p, func_ov107_0229d36c((int) param, (unsigned char) i));
        }
        i = (unsigned char) (i + 1);
    } while (i <= 14);
}

int func_ov107_0229d190(void *self, void *p)
{
    unsigned int id;

    if (func_ov107_0229d128((char *) self, (int) p) != 0) {
        return 0;
    }
    if (func_ov107_0229d0bc((char *) self, (int) p) != 0) {
        return 1;
    }

    id = (unsigned int) func_ov107_0229d0f0(self, p);

    if ((id >= 0x137c && id <= 0x137c) || (id >= 0x1408 && id <= 0x1428) || (id >= 0x1471 && id <= 0x1491)) {
        return 1;
    }
    if (id >= 0x12e8 && id <= 0x131f) {
        if (func_ov107_0229c2b4(self, 0x40) == 0) {
            return 1;
        }
    }
    return 0;
}

int func_ov107_0229d15c(char *p1, int p2)
{
    if (func_ov107_0229d388((unsigned int) p1, p2) != 0) {
        return func_ov094_0229a8bc(p1 + 0x10c, func_ov107_0229d36c((int) p1, p2));
    } else {
        return 0;
    }
}

int func_ov107_0229d128(char *param0, int param1)
{
    if (func_ov107_0229d388((unsigned int) param0, (unsigned int) param1)) {
        return func_ov094_0229a69c((int) (param0 + 0x10c), func_ov107_0229d36c((int) param0, param1));
    } else {
        return 1;
    }
}

int func_ov107_0229d0f0(void *p0, void *p1)
{
    if (func_ov107_0229d388((unsigned int) p0, (unsigned int) p1)) {
        int t = func_ov107_0229d36c((int) p0, (int) p1);
        return func_ov094_0229aaac((char *) p0 + 0x10c, t);
    } else {
        return 0xfff1;
    }
}

int func_ov107_0229d0bc(char *p, int q)
{
    if (func_ov107_0229d388((unsigned int) p, q) != 0) {
        return func_ov094_0229aa84(p + 0x10c, func_ov107_0229d36c((int) p, q));
    } else {
        return 0xf1;
    }
}

void func_ov107_0229d098(void *self)
{
    func_ov094_0229ab5c((char *) self + 0x10c);
    func_ov094_0229b98c((char *) self + 0xb6c);
}

void func_ov107_0229d054(char *p0, int p1)
{
    int temp;
    if (func_ov107_0229d388((unsigned int) p0, (unsigned int) p1) != 0) {
        temp = func_ov107_0229d36c((int) p0, p1);
        func_ov094_0229ab1c(p0 + 0x10c, temp);
        func_ov094_0229b98c((void *) (p0 + 0xb6c));
    } else {
        func_ov107_0229d098((void *) p0);
    }
}
