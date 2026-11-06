/* date_screen_4: 14 functions, module ov138
 * mwccarm 1.2/base -O4,s
 * func_ov138_0229cfb4 @ 0x0229cfb4, 0x8 bytes, Thumb
 * func_ov138_0229cf98 @ 0x0229cf98, 0x1c bytes, Thumb
 * func_ov138_0229cf88 @ 0x0229cf88, 0x10 bytes, Thumb
 * func_ov138_0229cf3c @ 0x0229cf3c, 0x4c bytes, Thumb
 * func_ov138_0229cf1c @ 0x0229cf1c, 0x20 bytes, Thumb
 * func_ov138_0229cefc @ 0x0229cefc, 0x20 bytes, Thumb
 * func_ov138_0229ce68 @ 0x0229ce68, 0x94 bytes, Thumb
 * func_ov138_0229cdd0 @ 0x0229cdd0, 0x98 bytes, Thumb
 * func_ov138_0229cd94 @ 0x0229cd94, 0x3c bytes, Thumb
 * func_ov138_0229cd58 @ 0x0229cd58, 0x3c bytes, Thumb
 * func_ov138_0229ccdc @ 0x0229ccdc, 0x7c bytes, Thumb
 * func_ov138_0229cc44 @ 0x0229cc44, 0x98 bytes, Thumb
 * func_ov138_0229cbec @ 0x0229cbec, 0x58 bytes, Thumb
 * func_ov138_0229cba4 @ 0x0229cba4, 0x48 bytes, Thumb
 */

typedef struct {
    char pad_00[0xfc];
    void *unk_FC;
    char pad_100[0x1c8];
    void *unk_2C8;
} UnkStruct_0229ce68;

struct FlagsStruct {
    unsigned char pad_00[2];
    unsigned short flags;
};

extern void func_ov002_0220af74(void *p);
extern void func_ov134_0229bcac(void *p);
extern void func_ov134_0229bbe8(int arg);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int func_ov134_0229baec(void *p);
extern void func_ov134_0229ba10(void *p, int n);
extern int func_ov134_0229b954(void *);
extern void func_ov002_0220af94(void *receiver);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208054(void *self, int arg);
extern unsigned char *func_ov138_0229c9e0(void *self);
extern int func_ov002_0220a784(void *ptr, int idx);
extern void func_ov138_0229c978(void *self);
extern void func_ov138_0229c950(void *self);
extern int func_ov134_0229ab80(void *ptr, unsigned char a, unsigned char b);
extern void func_ov138_0229c924(void *self, int result);
extern void func_ov138_0229c878(int self);
extern int func_ov134_0229a1f0(int ptr, int b1, int b2);
extern void func_ov138_0229c8f8(int self);
extern void func_ov138_0229c8cc(int self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov134_02299b18(void *p0, unsigned char p1);
extern int func_ov134_02299a84(void *p0);
extern void func_ov134_02299af0(char *p, unsigned char b);
extern int func_ov002_02208014(void *receiver);
extern void *func_ov002_02208008(void *p);
extern int func_ov138_0229c9fc(void *p);
extern int func_ov138_0229c588(void *p, void *x);
extern void func_ov138_0229c6e8(void *p);
extern void func_ov138_0229c654(void *p);
extern int func_ov138_0229c738(void *p);
extern int func_ov134_022997dc(void *, int);
extern void func_ov138_0229c8b4(void *);
extern void func_ov138_0229c564(void *, int);
extern int func_ov138_0229c7a8(void *);
extern int func_ov138_0229c754(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned short data_021fbe40[];
extern void func_ov134_02299a90(void *);
extern int func_ov134_02299a60(void *);
extern void func_ov138_0229c630(void *);

void func_ov138_0229cf88(int arg);

void func_ov138_0229cfb4(int argument0)
{
    func_ov138_0229cf88(argument0);
}

void func_ov138_0229cf98(void *self)
{
    func_ov002_0220af74((char *) self + 0xfc);
    func_ov134_0229bcac((char *) self + 0x2c8);
}

void func_ov138_0229cf88(int arg)
{
    func_ov134_0229bbe8(arg + 0x2c8);
}

void func_ov138_0229cf3c(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
}

void func_ov138_0229cf1c(void *self)
{
    func_ov134_0229baec((char *) self + 0x2c8);
    func_ov134_0229ba10((char *) self + 0x2c8, 0x6c);
}

void func_ov138_0229cefc(void *self)
{
    func_ov134_0229b954((char *) self + 0x2c8);
    self = (char *) self + 0xfc;
    func_ov002_0220af94(self);
}

void func_ov138_0229ce68(UnkStruct_0229ce68 *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov138_0229c9e0(self);
        return;
    }

    {
        unsigned int cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        if (cond > 0) {
            if (func_ov002_0220a784(&self->unk_FC, 6) != 0) {
                func_ov138_0229c978(self);
                return;
            } else {
                if (func_ov002_0220a784(&self->unk_FC, 7) != 0) {
                    func_ov138_0229c950(self);
                    return;
                } else {
                    int result = func_ov134_0229ab80(&self->unk_2C8, data_021f6c58, data_021f6c54);
                    if (result != 6) {
                        func_ov138_0229c924(self, result);
                    }
                }
            }
        }
    }
}

void func_ov138_0229cdd0(int self)
{
    unsigned int ok;
    int r;
    if (func_ov002_02208054((void *) self, 1)) {
        func_ov138_0229c878(self);
        return;
    }
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }
    r = func_ov134_0229a1f0(self + 0x2c8, data_021f6c58, data_021f6c54);
    switch (r) {
        case 0:
            func_ov138_0229c8f8(self);
            break;
        case 1:
            func_ov138_0229c8cc(self);
            break;
        case 3:
            func_ov002_02208098((void *) (self), 2);
            break;
        case 2:
            func_ov002_02208098((void *) (self), 3);
            break;
    }
}

void func_ov138_0229cd94(void *p0)
{
    if (data_021fbdd8) {
        func_ov134_02299b18((char *) p0 + 0x2c8, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) p0 + 0x2c8);
        func_ov002_02208098((void *) (p0), 1);
    }
}

void func_ov138_0229cd58(char *param)
{
    if (data_021fbdd8) {
        func_ov134_02299af0(param + 0x2c8, data_021f6c54);
    } else {
        func_ov134_02299a84((void *) (param + 0x2c8));
        func_ov002_02208098((void *) (param), 1);
    }
}

void func_ov138_0229ccdc(void *p)
{
    unsigned short flags;

    if (func_ov002_02208014(p)) {
        func_ov138_0229c9fc(p);
        return;
    }
    if (func_ov138_0229c588(p, func_ov002_02208008(p))) {
        func_ov138_0229c6e8(p);
        return;
    }
    flags = (*(struct FlagsStruct *) data_021fbe40).flags;
    if ((flags & 1) != 0) {
        func_ov138_0229c654(p);
        return;
    }
    if ((flags & 8) != 0) {
        func_ov138_0229c738(p);
        func_ov138_0229c978(p);
        return;
    }
    if ((flags & 2) != 0) {
        func_ov138_0229c738(p);
        func_ov138_0229c950(p);
    }
}

void func_ov138_0229cc44(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov138_0229c8b4(arg);
        return;
    }
    switch (func_ov134_022997dc((char *) arg + 0x2c8, (int) func_ov002_02208008(arg))) {
        case 2:
            func_ov138_0229c564(arg, 4);
            goto default_case;
        case 3: {
            int v1 = func_ov138_0229c7a8(arg);
            int v2 = func_ov138_0229c754(arg);
            func_ov002_0220a0b4((char *) arg + 0x98, v1, v2);
            return;
        }
        default:
        default_case:
            func_ov138_0229c6e8(arg);
            return;
        case 0: {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                func_ov138_0229c654(arg);
                return;
            }
            if (flags & 2) {
                func_ov138_0229c8cc((int) arg);
            }
            return;
        }
    }
}

void func_ov138_0229cbec(void *self)
{
    if ((*(unsigned short *) data_021fbe40) & 1) {
        func_ov134_02299a90((char *) self + 0x2c8);
        func_ov002_0220a0b4((char *) self + 0x98, (int) ((void *) func_ov138_0229c7a8(self)),
                            (int) ((void *) func_ov138_0229c754(self)));
    } else {
        func_ov134_02299a84((char *) self + 0x2c8);
        func_ov002_02208098((void *) (self), 7);
    }
}

void func_ov138_0229cba4(void *self)
{
    int a;
    int b;
    if (func_ov134_02299a60((char *) self + 0x2c8)) {
        func_ov002_02208098((void *) (self), 5);
        func_ov138_0229c630(self);
    }
    a = func_ov138_0229c7a8(self);
    b = func_ov138_0229c754(self);
    self = (char *) self + 0x98;
    func_ov002_0220a0b4(self, a, b);
}
