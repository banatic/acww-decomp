/* time_screen_3: 35 functions, module ov136
 * mwccarm 1.2/base -O4,s
 * func_ov136_0229cfcc @ 0x0229cfcc, 0x8 bytes, Thumb
 * func_ov136_0229cfb0 @ 0x0229cfb0, 0x1c bytes, Thumb
 * func_ov136_0229cfa0 @ 0x0229cfa0, 0x10 bytes, Thumb
 * func_ov136_0229cf54 @ 0x0229cf54, 0x4c bytes, Thumb
 * func_ov136_0229cf34 @ 0x0229cf34, 0x20 bytes, Thumb
 * func_ov136_0229cf14 @ 0x0229cf14, 0x20 bytes, Thumb
 * func_ov136_0229ce7c @ 0x0229ce7c, 0x98 bytes, Thumb
 * func_ov136_0229ce28 @ 0x0229ce28, 0x54 bytes, Thumb
 * func_ov136_0229ce04 @ 0x0229ce04, 0x24 bytes, Thumb
 * func_ov136_0229cd6c @ 0x0229cd6c, 0x98 bytes, Thumb
 * func_ov136_0229cd30 @ 0x0229cd30, 0x3c bytes, Thumb
 * func_ov136_0229ccf4 @ 0x0229ccf4, 0x3c bytes, Thumb
 * func_ov136_0229cc90 @ 0x0229cc90, 0x64 bytes, Thumb
 * func_ov136_0229cbf8 @ 0x0229cbf8, 0x98 bytes, Thumb
 * func_ov136_0229cba0 @ 0x0229cba0, 0x58 bytes, Thumb
 * func_ov136_0229cb58 @ 0x0229cb58, 0x48 bytes, Thumb
 * func_ov136_0229cb30 @ 0x0229cb30, 0x28 bytes, Thumb
 * func_ov136_0229cab4 @ 0x0229cab4, 0x7c bytes, Thumb
 * func_ov136_0229ca8c @ 0x0229ca8c, 0x28 bytes, Thumb
 * func_ov136_0229ca28 @ 0x0229ca28, 0x62 bytes, Thumb
 * func_ov136_0229ca08 @ 0x0229ca08, 0x20 bytes, Thumb
 * func_ov136_0229c9c8 @ 0x0229c9c8, 0x40 bytes, Thumb
 * func_ov136_0229c9b0 @ 0x0229c9b0, 0x16 bytes, Thumb
 * func_ov136_0229c994 @ 0x0229c994, 0x1c bytes, Thumb
 * func_ov136_0229c974 @ 0x0229c974, 0x20 bytes, Thumb
 * func_ov136_0229c92c @ 0x0229c92c, 0x48 bytes, Thumb
 * func_ov136_0229c900 @ 0x0229c900, 0x2c bytes, Thumb
 * func_ov136_0229c8d4 @ 0x0229c8d4, 0x2c bytes, Thumb
 * func_ov136_0229c8a8 @ 0x0229c8a8, 0x2c bytes, Thumb
 * func_ov136_0229c890 @ 0x0229c890, 0x16 bytes, Thumb
 * func_ov136_0229c854 @ 0x0229c854, 0x3c bytes, Thumb
 * func_ov136_0229c834 @ 0x0229c834, 0x20 bytes, Thumb
 * func_ov136_0229c7d8 @ 0x0229c7d8, 0x5c bytes, Thumb
 * func_ov136_0229c794 @ 0x0229c794, 0x44 bytes, Thumb
 * func_ov136_0229c750 @ 0x0229c750, 0x44 bytes, Thumb
 */

#include "types.h"

struct _FlagsStruct {
    unsigned short pad_00;
    unsigned short flags;
};

typedef struct {
    char pad_00[0x94];
    unsigned char unk_94;
    char pad_95[0x2c4 - 0x94 - 1];
    unsigned char unk_2C4;
    char pad_2C5[0x2b77 - 0x2c4 - 1];
    unsigned char unk_2B77;
} UnkStruct_ov136;

typedef struct UnkStruct_0229ca28 UnkStruct_0229ca28;

struct UnkStruct_0229ca28 {
    char pad_00[0x94];
    char unk_94;
    char pad_95[0xf8 - 0x94 - 1];
    char unk_F8;
};

extern void func_ov002_0220af74(void *);
extern void func_ov134_0229bcac(void *);
extern void func_ov134_0229bbe8(int a);
extern void func_02001c08(unsigned char param);
extern void func_020029e8(int layer, int priority);
extern void func_020028bc(unsigned mode, int a, int b, int c);
extern int func_ov134_0229baec(void *);
extern void func_ov134_0229ba10(void *, int);
extern int func_ov134_0229b954(void *p);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern u8 data_021fbddc;
extern int func_ov002_0220a784(void *p, int a);
extern int func_ov134_0229b168(void *p, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov134_0229aad8(void *p, int a, int b);
extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov134_0229b034(void *ptr);
extern void func_ov134_0229b108(void *ptr, unsigned char a, unsigned char b);
extern int func_ov134_0229b014(void *);
extern int func_ov134_0229a1f0(int ptr, int b1, int b2);
extern void func_ov134_02299b18(char *, unsigned char);
extern int func_ov134_02299a84(char *);
extern void func_ov134_02299af0(void *ptr, unsigned char val);
extern void func_ov136_0229c6e4(void *arg);
extern void func_ov136_0229c650(void *arg);
extern void func_ov136_0229c734(void *arg);
extern int func_ov136_0229c58c(void *arg, int v);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *arg);
extern int func_ov134_022997dc(void *, int);
extern void func_ov136_0229c564(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned short data_021fbe40[];
extern void func_ov134_02299a90(char *);
extern int func_ov134_02299a60(void *);
extern void func_ov136_0229c628(void *);
extern int func_ov002_02209f64(void *p);
extern void func_ov136_0229d184(void *obj);
extern int func_0208e484(void *ptr);
extern int func_ov136_0229c574(void *self, int n);
extern int func_ov134_02299b70(void *ptr);
extern int func_ov134_022997b0(void *ptr);
extern void func_ov136_0229c668(void *);
extern int func_ov002_0220a700(void *s);
extern int func_0208e4bc(void *s);
extern int func_ov002_0220a6e0(void *s);
extern int func_ov002_0220a768(void *s, int arg);
extern int func_ov002_0220a72c(void *s, int arg);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov134_0229a4e4(void *);
extern int func_ov134_0229a24c(void *);
extern int func_ov134_0229a8a0(void *);
extern void func_ov002_02207fc0(void *p);
extern int func_0206fe60(void);
extern void *func_ov002_0220a720(char *ptr, int n);
extern void func_ov002_02208090(char *ptr, int n);
extern void func_ov134_0229bbdc(char *ptr, int *arr);
extern void func_0206f820(int *arr);
extern void func_0206fc4c(int val);
extern void func_ov134_0229a5c8(void *, void *);
extern void func_ov136_0229c554(void *, int);
extern void func_ov134_0229a3e4(void *);
extern void func_ov134_0229a398(void *);
extern int func_ov134_022999ac(char *p);
extern void func_ov134_02299980(char *p, int x);
extern void func_ov002_0220a374(void *p, int n);
extern int func_ov134_022999e0(void *ptr);
extern int data_ov136_0229d428[];
extern void *data_ov136_0229d434[];

void func_ov136_0229cfa0(int a);
void func_ov136_0229c9b0(void *p);
void func_ov136_0229c994(void *p);
void func_ov136_0229c974(int param);
void func_ov136_0229c92c(char *obj);
void func_ov136_0229c900(void *arg0, void *arg1);
void func_ov136_0229c8d4(void *self);
void func_ov136_0229c8a8(void *p);
void func_ov136_0229c890(int param);
void func_ov136_0229c854(char *p);
void func_ov136_0229c834(void *param);
void func_ov136_0229c7d8(void *self);
int func_ov136_0229c794(void *ptr);
void *func_ov136_0229c750(void *a);

void func_ov136_0229cfcc(int argument0)
{
    func_ov136_0229cfa0(argument0);
}

void func_ov136_0229cfb0(void *arg0)
{
    func_ov002_0220af74((char *) arg0 + 0xf8);
    func_ov134_0229bcac((char *) arg0 + 0x2c4);
}

void func_ov136_0229cfa0(int a)
{
    func_ov134_0229bbe8(a + 0x2c4);
}

void func_ov136_0229cf54(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
}

void func_ov136_0229cf34(void *self)
{
    func_ov134_0229baec((char *) self + 0x2c4);
    func_ov134_0229ba10((char *) self + 0x2c4, 0x8b);
}

void func_ov136_0229cf14(void *p)
{
    func_ov134_0229b954((char *) p + 0x2c4);
    p = (char *) p + 0xf8;
    func_ov002_0220af94(p);
}

void func_ov136_0229ce7c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov136_0229c994(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0xf8, 6) != 0) {
        func_ov136_0229c92c((char *) self);
        return;
    }

    a = (*(u8 *) &data_021f6c58);
    b = (*(u8 *) &data_021f6c54);
    if (func_ov134_0229b168(self + 0x2c4, a, b) != 0) {
        func_ov002_02208098((void *) (self), 1);
    }
    n = func_ov134_0229aad8(self + 0x2c4, a, b);
    if (n != 6) {
        func_ov136_0229c900(self, (void *) n);
    }
}

void func_ov136_0229ce28(void *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov134_0229b034((char *) self + 0x2c4) != 0) {
            func_ov002_02208098((void *) (self), 2);
        } else {
            func_ov002_02208098((void *) (self), 0);
        }
    } else {
        func_ov134_0229b108((char *) self + 0x2c4, data_021f6c58, data_021f6c54);
    }
}

void func_ov136_0229ce04(void *self)
{
    if (func_ov134_0229b014((char *) self + 0x2c4)) {
        func_ov002_02208098((void *) (self), 0);
    }
}

void func_ov136_0229cd6c(int self)
{
    unsigned int ok;
    int r;
    if (func_ov002_02208054((void *) self, 1)) {
        func_ov136_0229c854((char *) self);
        return;
    }
    ok = (data_021fbdd8 != 0 && (*(unsigned char *) &data_021fbddc) != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }
    r = func_ov134_0229a1f0(self + 0x2c4, data_021f6c58, data_021f6c54);
    switch (r) {
        case 0:
            func_ov136_0229c8d4((void *) self);
            break;
        case 1:
            func_ov136_0229c8a8((void *) self);
            break;
        case 3:
            func_ov002_02208098((void *) (self), 4);
            break;
        case 2:
            func_ov002_02208098((void *) (self), 5);
            break;
    }
}

void func_ov136_0229cd30(char *p)
{
    if (data_021fbdd8 != 0) {
        func_ov134_02299b18(p + 0x2c4, data_021f6c54);
    } else {
        func_ov134_02299a84(p + 0x2c4);
        func_ov002_02208098((void *) (p), 3);
    }
}

void func_ov136_0229ccf4(void *param)
{
    if (data_021fbdd8) {
        func_ov134_02299af0((char *) param + 0x2C4, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) ((char *) param + 0x2C4));
        func_ov002_02208098((void *) (param), 3);
    }
}

void func_ov136_0229cc90(void *param)
{
    int v;
    unsigned short flags;

    if (func_ov002_02208014(param)) {
        func_ov136_0229c9b0(param);
        return;
    }

    v = func_ov002_02208008(param);
    if (func_ov136_0229c58c(param, v)) {
        func_ov136_0229c6e4(param);
        return;
    }

    flags = (*(struct _FlagsStruct *) data_021fbe40).flags;
    if (flags & 1) {
        func_ov136_0229c650(param);
        return;
    }

    if (flags & 8) {
        func_ov136_0229c734(param);
        func_ov136_0229c92c((char *) param);
    }
}

void func_ov136_0229cbf8(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov136_0229c890((int) arg);
        return;
    }
    switch (func_ov134_022997dc((char *) arg + 0x2c4, func_ov002_02208008(arg))) {
        case 2:
            func_ov136_0229c564(arg, 4);
            goto default_case;
        case 3: {
            int v1 = func_ov136_0229c794(arg);
            int v2 = (int) func_ov136_0229c750(arg);
            func_ov002_0220a0b4((char *) arg + 0x94, v1, v2);
            return;
        }
        default:
        default_case:
            func_ov136_0229c6e4(arg);
            return;
        case 0: {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                func_ov136_0229c650(arg);
                return;
            }
            if (flags & 2) {
                func_ov136_0229c8a8(arg);
            }
            return;
        }
    }
}

void func_ov136_0229cba0(char *self)
{
    if ((*(unsigned short *) data_021fbe40) & 1) {
        unsigned int a;
        unsigned int b;
        func_ov134_02299a90(self + 0x2c4);
        a = (unsigned int) func_ov136_0229c794((void *) self);
        b = (unsigned int) func_ov136_0229c750((void *) self);
        func_ov002_0220a0b4((void *) (self + 0x94), a, b);
    } else {
        func_ov134_02299a84(self + 0x2c4);
        func_ov002_02208098((void *) (self), 9);
    }
}

void func_ov136_0229cb58(void *arg)
{
    int a;
    int b;

    if (func_ov134_02299a60((char *) arg + 0x2c4)) {
        func_ov002_02208098((void *) (arg), 7);
        func_ov136_0229c628(arg);
    }

    a = func_ov136_0229c794(arg);
    b = (int) func_ov136_0229c750(arg);
    arg = (char *) arg + 0x94;
    func_ov002_0220a0b4(arg, a, b);
}

void func_ov136_0229cb30(void *obj)
{
    if (func_ov002_02209f64((char *) obj + 0x94) == 0) {
        func_ov002_02208098((void *) (obj), *((unsigned char *) obj + 0x2b76));
        func_ov136_0229d184(obj);
    }
}

void func_ov136_0229cab4(UnkStruct_ov136 *self)
{
    if (func_0208e484(&self->unk_94) != 0) {
        if (func_ov136_0229c574(self, 2) != 0) {
            if (func_ov134_02299b70(&self->unk_2C4) != 0) {
                func_ov002_02208098((void *) (self), 8);
                return;
            } else {
                if (func_ov134_022997b0(&self->unk_2C4) != 0) {
                    func_ov136_0229c8d4(self);
                    return;
                } else {
                    func_ov002_02208098((void *) (self), 7);
                    func_ov136_0229c628(self);
                }
            }
        } else {
            if (self->unk_2B77 == 2) {
                func_ov136_0229c92c((char *) self);
                return;
            } else {
                func_ov136_0229c900(self, (void *) (self->unk_2B77 + 3));
            }
        }
    }
}

void func_ov136_0229ca8c(void *self)
{
    if (func_0208e484((char *) self + 0x94)) {
        func_ov136_0229c668(self);
        func_ov002_02208098((void *) (self), ((unsigned char *) self)[0x2b76]);
    }
}

void func_ov136_0229ca28(UnkStruct_0229ca28 *p)
{
    if (func_ov002_0220a700(&p->unk_F8) != 0) {
        if (func_0208e4bc(&p->unk_94) != 0) {
            int t1 = func_ov002_0220a6e0(&p->unk_F8);
            int t2 = func_ov002_0220a768(&p->unk_F8, -1);
            int t3 = func_ov002_0220a72c(&p->unk_F8, -1);
            func_ov002_0220a0b4(&p->unk_94, t1 + t2, t1 + t3);
        }
    } else {
        func_ov136_0229c734((void *) p);
        func_ov002_022080a0((void *) (p), 1);
    }
}

void func_ov136_0229ca08(void *arg)
{
    if (func_ov134_0229a4e4((char *) arg + 0x2c4)) {
        func_ov136_0229c834(arg);
    }
}

void func_ov136_0229c9c8(void *self)
{
    if (func_ov134_0229a24c((char *) self + 0x2c4)) {
        int v = func_ov134_0229a8a0((char *) self + 0x2c4);
        if (v == 6) {
            ((char *) self)[0x2b77] = 2;
        } else {
            ((char *) self)[0x2b77] = v - 3;
        }
        func_ov136_0229c974((int) self);
    }
}

void func_ov136_0229c9b0(void *p)
{
    func_ov136_0229c734(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov136_0229c994(void *p)
{
    func_ov136_0229c7d8(p);
    func_ov002_02207fc0(p);
    func_ov002_02208098((void *) (p), 6);
}

void func_ov136_0229c974(int param)
{
    if (func_0206fe60() != 0) {
        func_ov136_0229c9b0((void *) param);
    } else {
        func_ov136_0229c994((void *) param);
    }
}

void func_ov136_0229c92c(char *obj)
{
    int local[2];

    func_ov002_0220a720(obj + 0xf8, 6);
    func_ov002_02208090(obj, 2);
    func_ov002_02208098((void *) (obj), 0xd);
    local[0] = 0;
    local[1] = 0;
    func_ov134_0229bbdc(obj + 0x2c4, local);
    func_0206f820(local);
    func_0206fc4c(1);
}

void func_ov136_0229c900(void *arg0, void *arg1)
{
    func_ov136_0229c734(arg0);
    func_ov134_0229a5c8((char *) arg0 + 0x2c4, arg1);
    func_ov002_02208098((void *) (arg0), 0xe);
}

void func_ov136_0229c8d4(void *self)
{
    func_ov136_0229c734(self);
    func_ov136_0229c554(self, 2);
    func_ov134_0229a3e4((char *) self + 0x2c4);
    func_ov002_02208098((void *) (self), 0xf);
}

void func_ov136_0229c8a8(void *p)
{
    func_ov136_0229c734(p);
    func_ov136_0229c554(p, 2);
    func_ov134_0229a398((char *) p + 0x2c4);
    func_ov002_02208098((void *) (p), 0xf);
}

void func_ov136_0229c890(int param)
{
    func_ov136_0229c734((void *) param);
    func_ov002_02208098((void *) (param), 3);
}

void func_ov136_0229c854(char *p)
{
    func_ov134_02299980(p + 0x2c4, func_ov134_022999ac(p + 0x2c4));
    func_ov136_0229c564((void *) p, 2);
    func_ov136_0229c7d8((void *) p);
    func_ov002_02207fc0((void *) p);
    func_ov002_02208098((void *) (p), 7);
}

void func_ov136_0229c834(void *param)
{
    if (func_0206fe60()) {
        func_ov136_0229c890((int) param);
    } else {
        func_ov136_0229c854((char *) param);
    }
}

void func_ov136_0229c7d8(void *self)
{
    int a = func_ov136_0229c794(self);
    int b = (int) func_ov136_0229c750(self);
    func_ov002_0220a0b4((char *) self + 0x94, a, b);
    if (func_ov136_0229c574(self, 2) != 0 || ((unsigned char *) self)[0x2b77] != 2) {
        func_ov002_0220a374((char *) self + 0x94, 1);
    } else {
        func_ov002_0220a374((char *) self + 0x94, 7);
    }
    func_ov136_0229c668(self);
}

int func_ov136_0229c794(void *ptr)
{
    if (func_ov136_0229c574(ptr, 2) != 0) {
        return func_ov134_022999e0((char *) ptr + 0x2c4);
    } else {
        unsigned char b = ((unsigned char *) ptr)[0x2b77];
        if (b == 2) {
            ptr = (char *) ptr + 0xf8;
            return func_ov002_0220a768(ptr, 6);
        } else {
            return data_ov136_0229d428[b];
        }
    }
}

void *func_ov136_0229c750(void *a)
{
    if (func_ov136_0229c574(a, 2) != 0) {
        return (void *) func_ov134_022999ac((char *) ((char *) a + 0x2c4));
    } else {
        unsigned char b = *(unsigned char *) ((char *) a + 0x2b77);
        if (b == 2) {
            char *p = (char *) a + 0xf8;
            return (void *) func_ov002_0220a72c(p, 6);
        } else {
            return data_ov136_0229d434[b];
        }
    }
}
