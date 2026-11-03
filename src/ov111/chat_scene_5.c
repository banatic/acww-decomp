/* chat_scene_5: 15 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_022a0b20 @ 0x022a0b20, 0x38 bytes, Thumb
 * func_ov111_022a0a5c @ 0x022a0a5c, 0xc4 bytes, Thumb
 * func_ov111_022a09f8 @ 0x022a09f8, 0x64 bytes, Thumb
 * func_ov111_022a09d8 @ 0x022a09d8, 0x1e bytes, Thumb
 * func_ov111_022a0970 @ 0x022a0970, 0x68 bytes, Thumb
 * func_ov111_022a0940 @ 0x022a0940, 0x30 bytes, Thumb
 * func_ov111_022a0910 @ 0x022a0910, 0x30 bytes, Thumb
 * func_ov111_022a08bc @ 0x022a08bc, 0x54 bytes, Thumb
 * func_ov111_022a088c @ 0x022a088c, 0x2e bytes, Thumb
 * func_ov111_022a085c @ 0x022a085c, 0x2e bytes, Thumb
 * func_ov111_022a082c @ 0x022a082c, 0x30 bytes, Thumb
 * func_ov111_022a075c @ 0x022a075c, 0xd0 bytes, Thumb
 * func_ov111_022a0708 @ 0x022a0708, 0x54 bytes, Thumb
 * func_ov111_022a06c8 @ 0x022a06c8, 0x40 bytes, Thumb
 * func_ov111_022a05dc @ 0x022a05dc, 0xec bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xa2];
    volatile unsigned char unk_A2;
    unsigned char pad_A3[9];
    unsigned char unk_AC;
} UnkStruct_022a0b20;

// Twelve cases share one body; case 4 is the odd one out.

typedef struct UnkStruct_022a0a5c {
    char pad_00[0x8d];
    u8 unk_8D;
} UnkStruct_022a0a5c;

struct UnkStruct_022a09f8 {
    u8 pad_00[0x8c];
    u8 byte;
};

struct UnkStruct_022a075c {
    unsigned char pad_00[0xa2];
    unsigned char unk_A2;
    unsigned char pad_A3[0xac - 0xa3];
    unsigned char unk_AC[0x80];
};

typedef struct {
    unsigned char pad_00[0x9F];
    unsigned char unk_9F;
    unsigned char unk_A0;
} UnkStruct_022a06c8;

extern void func_ov095_0229afa4(void *);
extern void func_ov111_0229f084(void *);
extern u16 data_021fbe40[];
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern void *func_020ee45c(struct UnkStruct_022a09f8 *a);
extern void func_ov090_022993cc(void *p, u8 b);
extern void func_ov111_0229f1d8(struct UnkStruct_022a09f8 *a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov111_0229efc8(struct UnkStruct_022a09f8 *a, int b);
extern void func_0206f4f4(char *p);
extern void func_0206f4e4(void);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern const char data_ov111_022a1068[];
extern const char data_ov111_022a0f88[];
extern const char data_ov111_022a1080[];
extern void *data_021fbe94;
extern int func_02002d14(const void *, void *, int, int, int, int);
extern int func_02002c6c(const void *, void *, int, int, int, int);
extern int func_ov095_0229c000(void *, const void *);
extern void func_ov111_0229efec(void *);
extern void func_ov095_0229bfd8(void *, int);
extern int func_ov095_0229b324(void *receiver);
extern void func_ov002_02208090(void *, int);
extern int func_ov111_0229efd8(void *, int);
extern void func_ov095_0229b280(void *);
extern void func_ov095_0229c420(char *p, int v);
extern void func_ov002_02207f20(char *p, int a, int b, int c, int d);
extern void func_02002708(int v);
extern int func_ov002_02207f48(void *param, int flag);
extern void func_ov111_022a01bc(void *param);
extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f3c(int, int);
extern void func_0200277c(int);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208054(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov095_0229bf48(void *);
extern int func_ov095_0229aff0(void *);
extern int func_ov095_0229afac(void *);
extern void func_ov111_022a01dc(void *);
extern void func_ov111_0229f090(void *, int);
extern void func_ov111_0229fd08(void *);
extern int func_ov111_0229f6a8(void *);
extern void func_ov111_022a0198(void *);
extern int func_ov111_0229f600(void *);
extern int func_ov111_0229f6d4(void *);
extern int func_ov095_0229bf0c(void *ptr);
extern int func_ov095_0229c548(void *ptr);
extern int func_ov095_0229c448(void *ptr, int a, int b);
extern void func_ov095_0229c8e4(void *ptr, int a);
extern int func_ov111_0229f730(void *self, int a);
extern void func_ov111_0229f5bc(void *self);
extern void func_ov111_0229efb8(void *self, int arg);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern int func_ov095_02299a54(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a254(void *);
extern int func_ov090_02299078(int);
extern int func_ov090_02299098(int);
extern void func_ov111_0229f164(void *);
extern int func_ov111_0229f3ac(void *);
extern int func_ov111_0229f358(void *);
extern int func_ov111_0229f24c(void *);
extern void func_ov111_022a0204(void *);

int func_ov111_022a09f8(struct UnkStruct_022a09f8 *a, int b, int c);
void func_ov111_022a0910(void *param);
void func_ov111_022a08bc(char *param0);

void func_ov111_022a0b20(UnkStruct_022a0b20 *self)
{
    if (self->unk_A2) {
        self->unk_A2 = self->unk_A2 - 1;
        if (self->unk_A2 == 0) {
            func_ov095_0229afa4(&self->unk_AC);
        }
    }
    func_ov111_0229f084(self);
}

int func_ov111_022a0a5c(UnkStruct_022a0a5c *o)
{
    int r;
    u16 w;

    func_0206f58c();
    if (func_0206f56c()) {
        switch (o->unk_8D) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                return func_ov111_022a09f8((struct UnkStruct_022a09f8 *) o, 7, 1);
            case 4:
                break;
        }
    }
    if (o->unk_8D != 0 && o->unk_8D != 3 && o->unk_8D != 9) {
        return 0;
    }
    r = -1;
    if (func_0206fe60()) {
        r = func_ov090_022990e0();
    } else {
        w = data_021fbe40[1];
        if (w & 4) {
            r = 7;
        } else if (w & 0x800) {
            r = 0;
        } else if (w & 0x400) {
            r = 5;
        }
    }
    return func_ov111_022a09f8((struct UnkStruct_022a09f8 *) o, r, 0);
}

int func_ov111_022a09f8(struct UnkStruct_022a09f8 *a, int b, int c)
{
    void *p = func_020ee45c(a);
    if (b != -1 && b != 4) {
        func_ov090_022993cc(p, (u8) b);
        func_ov111_0229f1d8(a);
        a->byte = 4;
        func_ov002_022080a0((void *) (a), 1);
        if (b == 7) {
            func_ov111_0229efc8(a, 0x10);
        }
        if (c != 0) {
            func_0206f4f4((char *) a + 0x3d16);
        } else {
            func_0206f4e4();
        }
        return 1;
    }
    return 0;
}

void func_ov111_022a09d8(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov111_022a0970(char *self)
{
    void *w = data_021fbe94;
    func_02002d14(data_ov111_022a1068, w, 6, 1, 1, 9);
    func_ov095_0229c000((void *) (self + 0xac), data_ov111_022a0f88);
    func_ov111_0229efec(self);
    self += 0xac;
    func_ov095_0229bfd8(self, 6);
    func_02002c6c(data_ov111_022a1080, w, 6, 0x13d, 0x13d, 0x1e9);
}

void func_ov111_022a0940(void *arg0)
{
    void *receiver = arg0;
    func_ov111_022a09d8();
    func_ov095_0229b324((void *) ((char *) receiver + 0xac));
    func_ov002_02208090(receiver, 1);
    if (func_ov111_0229efd8(receiver, 0x20) == 0) {
        func_ov111_022a0910(receiver);
    }
}

void func_ov111_022a0910(void *param)
{
    func_ov095_0229b280((char *) param + 0xac);
    func_ov111_022a0970((char *) param);
    func_ov002_02208090(param, 2);
    if (func_ov111_0229efd8(param, 0x20) == 0) {
        func_ov111_022a08bc((char *) param);
    }
}

void func_ov111_022a08bc(char *param0)
{
    func_ov095_0229c420(param0 + 0xac, 6);
    func_ov111_0229f084((void *) param0);
    func_ov111_0229efc8((struct UnkStruct_022a09f8 *) param0, 4);
    func_ov002_02207f20(param0, 8, 3, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80((int) param0, 6, 0, 0);
    func_ov002_02208090((void *) param0, 3);
    func_ov111_0229fd08((void *) param0);
}

void func_ov111_022a088c(void *param)
{
    if (func_ov002_02207f48(param, 0) != 0) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov111_022a01bc(param);
    }
    func_ov002_02207e80((int) param, 6, 0, 0);
}

void func_ov111_022a085c(int arg0)
{
    int local_0;
    int local_1;

    local_0 = 0x30;
    func_ov002_02207f04(arg0, 8, 0, 0, local_0);
    func_ov002_02207e80(arg0, 6, 0, 0);
    *(unsigned char *) (arg0 + 0x8c) = 5;
}

void func_ov111_022a082c(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_0200277c(6);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov002_02207e80(param, 6, 0, 0);
    }
}

void func_ov111_022a075c(struct UnkStruct_022a075c *self)
{
    unsigned int flag;
    int result;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov111_022a01dc(self);
        return;
    }
    if (func_ov095_0229bf48(&self->unk_AC) != 0) {
        return;
    }
    flag = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (flag > 0) {
        result = func_ov111_0229f6d4(self);
        if (result != 0) {
            if (result == 1) {
                func_ov002_02208098((void *) (self), 1);
                return;
            }
        } else {
            if (func_ov095_0229aff0(&self->unk_AC) != 0) {
                func_ov111_0229f090(self, 9);
                func_ov111_0229fd08(self);
                return;
            }
            if (func_ov111_0229f6a8(self) != 0) {
                func_ov002_02208098((void *) (self), 0xd);
                return;
            }
            if (self->unk_A2 == 0) {
                if (func_ov095_0229afac(&self->unk_AC) != 0) {
                    func_ov111_022a0198(self);
                    func_ov002_02208098((void *) (self), 0);
                    return;
                }
            }
            if (func_ov111_0229f600(self) != 0) {
                func_ov111_0229efec(self);
                func_ov002_02208098((void *) (self), 2);
                return;
            }
        }
    }
}

void func_ov111_022a0708(void *self)
{
    int tmp;
    int r;

    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (self), 0);
        return;
    }
    if (func_ov095_0229bf0c((char *) self + 0xac) == 0) {
        return;
    }
    tmp = func_ov095_0229c548((char *) self + 0xac);
    r = func_ov095_0229c448((char *) self + 0xac, tmp, 9);
    func_ov111_0229f730(self, r);
    self = (char *) self + 0xac;
    func_ov095_0229c8e4(self, tmp);
}

void func_ov111_022a06c8(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (self), 0);
        if (((UnkStruct_022a06c8 *) self)->unk_9F == ((UnkStruct_022a06c8 *) self)->unk_A0) {
            func_ov111_0229efb8(self, 1);
        }
    } else {
        func_ov111_0229f5bc(self);
    }
    func_ov111_0229fd08(self);
}

void func_ov111_022a05dc(void *p)
{
    int res2;
    int r;
    if (func_ov002_02208014(p) != 0) {
        func_ov111_022a0204(p);
        return;
    }
    res2 = func_ov002_02208008(p);
    r = func_ov095_02299a54((char *) p + 0xac, res2);
    switch (r) {
        case 1:
            func_ov002_0220a2b4((char *) p + 0x3d38);
            func_ov111_0229f164(p);
            break;
        case 2:
            func_ov002_0220a254((char *) p + 0x3d38);
            func_ov111_0229f164(p);
            break;
        case 4:
            func_ov002_0220a2b4((char *) p + 0x3d38);
            func_ov111_0229efc8((struct UnkStruct_022a09f8 *) p, 2);
            func_ov002_02208098((void *) (p), 9);
            func_ov111_0229f164(p);
            break;
        case 0:
        case 3:
        default: {
            unsigned short v;
            if (func_ov111_0229f3ac(p) != 0) {
                return;
            }
            if (func_ov111_0229f358(p) != 0) {
                return;
            }
            if (func_ov111_0229f24c(p) != 0) {
                return;
            }
            v = ((unsigned short *) data_021fbe40)[1];
            if (v & 0x100) {
                int x = func_ov090_02299078(4);
                func_ov111_022a09f8((struct UnkStruct_022a09f8 *) p, x, 0);
            } else if (v & 0x200) {
                int y = func_ov090_02299098(4);
                func_ov111_022a09f8((struct UnkStruct_022a09f8 *) p, y, 0);
            }
            break;
        }
    }
}
