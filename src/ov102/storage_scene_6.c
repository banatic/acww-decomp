/* storage_scene_6: 30 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229e0e4 @ 0x0229e0e4, 0x8 bytes, Thumb
 * func_ov102_0229e0b0 @ 0x0229e0b0, 0x34 bytes, Thumb
 * func_ov102_0229e084 @ 0x0229e084, 0x2c bytes, Thumb
 * func_ov102_0229e050 @ 0x0229e050, 0x32 bytes, Thumb
 * func_ov102_0229e03c @ 0x0229e03c, 0x14 bytes, Thumb
 * func_ov102_0229dff0 @ 0x0229dff0, 0x4c bytes, Thumb
 * func_ov102_0229dfa4 @ 0x0229dfa4, 0x4c bytes, Thumb
 * func_ov102_0229df94 @ 0x0229df94, 0x10 bytes, Thumb
 * func_ov102_0229defc @ 0x0229defc, 0x98 bytes, Thumb
 * func_ov102_0229dea4 @ 0x0229dea4, 0x58 bytes, Thumb
 * func_ov102_0229ddcc @ 0x0229ddcc, 0xd8 bytes, Thumb
 * func_ov102_0229dc44 @ 0x0229dc44, 0x188 bytes, Thumb
 * func_ov102_0229dae0 @ 0x0229dae0, 0x164 bytes, Thumb
 * func_ov102_0229da90 @ 0x0229da90, 0x50 bytes, Thumb
 * func_ov102_0229da20 @ 0x0229da20, 0x70 bytes, Thumb
 * func_ov102_0229d9e0 @ 0x0229d9e0, 0x40 bytes, Thumb
 * func_ov102_0229d9b0 @ 0x0229d9b0, 0x30 bytes, Thumb
 * func_ov102_0229d980 @ 0x0229d980, 0x30 bytes, Thumb
 * func_ov102_0229d928 @ 0x0229d928, 0x58 bytes, Thumb
 * func_ov102_0229d8e0 @ 0x0229d8e0, 0x48 bytes, Thumb
 * func_ov102_0229d88c @ 0x0229d88c, 0x54 bytes, Thumb
 * func_ov102_0229d830 @ 0x0229d830, 0x5c bytes, Thumb
 * func_ov102_0229d7f8 @ 0x0229d7f8, 0x38 bytes, Thumb
 * func_ov102_0229d7b8 @ 0x0229d7b8, 0x40 bytes, Thumb
 * func_ov102_0229d79c @ 0x0229d79c, 0x1c bytes, Thumb
 * func_ov102_0229d760 @ 0x0229d760, 0x3c bytes, Thumb
 * func_ov102_0229d740 @ 0x0229d740, 0x20 bytes, Thumb
 * func_ov102_0229d6b4 @ 0x0229d6b4, 0x8c bytes, Thumb
 * func_ov102_0229d650 @ 0x0229d650, 0x64 bytes, Thumb
 * func_ov102_0229d5e8 @ 0x0229d5e8, 0x68 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229dea4 {
    unsigned char pad_00[0x218c];
    unsigned char sub[0x414];
    unsigned char flag;
} UnkStruct_0229dea4;

typedef struct {
    unsigned char pad_00[0x218c];
    unsigned char sub; // 0x218c
    unsigned char pad_218D[0x24e0 - 0x218d];
    void *ptr0; // 0x24e0
    void *ptr1; // 0x24e4
    unsigned char pad_24E8[0x25a2 - 0x24e8];
    unsigned char state; // 0x25a2
} UnkStruct_0229ddcc;

typedef struct {
    char pad_00[0x218C];
    void *unk_218C;
    char pad_2190[0x25A5 - 0x218C - 4];
    unsigned char unk_25A5;
} UnkStruct_0229dc44;

typedef struct {
    char pad_00[0x25A2];
    unsigned char unk_25A2;
    unsigned char unk_25A3;
    char pad_25A4[1];
    unsigned char unk_25A5;
    char pad_25A6[4];
    unsigned char unk_25AA;
} UnkStruct_0229dae0;

typedef struct UnkStruct_0229d980 UnkStruct_0229d980;

struct UnkStruct_0229d980 {
    char pad_00[0x2274];
    unsigned char unk_2274;
    char pad_2275[0x332];
    unsigned char unk_25A7;
};

typedef struct {
    u8 pad_00[0x25a5];
    u8 unk_25A5;
    u8 unk_25A6;
} UnkStruct_0229d928;

typedef struct {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x332];
    unsigned char unk_25A7;
} UnkStruct_0229d88c;

struct UnkStruct_0229d7b8;

typedef struct UnkStruct_0229d6b4 {
    unsigned char pad_00[0x218c];
    unsigned char sub_218c;
    unsigned char pad_218D[0x34b];
    int unk_24D8;
    int unk_24DC;
    unsigned char pad_24E0[0xc0];
    unsigned char unk_25A0;
    unsigned char unk_25A1;
} UnkStruct_0229d6b4;

struct UnkStruct_0229d650 {
    unsigned char data[0x25ab];
};

extern void func_ov102_0229d470(char *self);
extern void func_ov094_0229a084(char *p);
extern void func_ov094_0229af20(char *p);
extern void func_ov094_0229bbc0(char *p);
extern void func_ov102_0229c534(char *self);
extern void func_ov102_0229ce58(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov094_0229a05c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(char *p, int arg);
extern int data_021fbe94; // 0x021fbe94
extern int func_02002ca4(const void *a, int b, int c);
extern int func_02002c6c(const void *a, int b, int c, int d, int e, int f);
extern void func_ov102_0229c4c0(int a, int b);
extern unsigned char data_ov102_0229eb6c[];
extern unsigned char data_ov102_0229eb90[];
extern int func_02064328(void *, const void *, unsigned int);
extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_ov102_0229d258(void *);
extern void func_ov094_0229ace4(void *, int);
extern const unsigned char data_ov102_0229eb50[];
extern int func_ov094_0229a098(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov102_0229d37c(void *self, int a, int b, int c);
extern void func_ov102_0229c460(void *self, int a);
extern int func_ov102_0229c364(void *self, int a, int b);
extern void func_ov102_0229c318(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov002_02207ce4(unsigned char *ptr, int val);
extern int func_ov102_0229c2a8(void *self, int val);
extern int func_ov102_0229cef8(void *self);
extern int func_0206f56c(void);
extern void func_ov102_0229cc60(void *self, unsigned char b);
extern void func_ov102_0229cb50(void *self);
extern int func_ov002_02207d24(void *obj, int val);
extern void func_ov102_0229cd80(void *self);
extern void func_ov102_0229cf74(void *self);
extern int func_ov102_0229d0b0(void *self, int idx);
extern void func_ov102_0229d508(void *self, unsigned char b, void *p);
extern int func_ov102_0229d320(void *self, int idx);
extern void func_ov094_022999d8(void);
extern void func_ov102_0229cf3c(void *self, int idx);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229dc44 *s);
extern int func_ov102_0229c560(UnkStruct_0229dc44 *s, int a, int b);
extern void func_ov002_02207d00(void *p);
extern void func_ov102_0229cab8(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d464(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d454(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d074(UnkStruct_0229dc44 *s, unsigned char b);
extern void func_ov102_0229ca38(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d438(UnkStruct_0229dc44 *s, unsigned char b);
extern void func_ov102_0229ca78(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d444(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d47c(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d4ac(void *receiver);
extern void func_ov102_0229d4cc(UnkStruct_0229dc44 *s, unsigned char b, int v);
extern int func_ov102_0229c2c0(UnkStruct_0229dc44 *s);
extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;
extern void func_ov102_0229c9fc(UnkStruct_0229dae0 *s, unsigned char b);
extern void func_ov102_0229c9b0(UnkStruct_0229dae0 *s, unsigned char b);
extern void func_ov102_0229d54c(UnkStruct_0229dae0 *s, unsigned char b, int v);
extern int func_0208e4bc(void *p);
extern int func_ov002_02209f64(void *);
extern void func_ov102_0229cf90(unsigned char *, unsigned char);
extern void func_ov102_0229e5b8(unsigned char *);
extern void func_ov102_0229cd38(unsigned char *);
extern int func_0208e484(void *p);
extern void func_ov102_0229ca58(void *p);
extern void func_ov102_0229ca98(char *);
extern int func_ov002_02209f9c(void *p);
extern void func_ov102_0229cdf4(void *self);
extern int func_ov002_02209f70(void *p);
extern void func_ov102_0229cc24(unsigned char *p, unsigned char b);
extern void func_ov102_0229c298(unsigned char *p, int n);
extern void func_ov102_0229c288(void *, int);
extern void func_ov094_022999c0(void);
extern int func_ov002_02209d8c(void *);
extern void func_ov102_0229cd08(void *);
extern int func_ov002_0220b8ac(void *ptr, int value);
extern void func_0208e5cc(void *ptr);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229d7b8 *self, unsigned char value);
extern void func_ov102_0229cfdc(void *);
extern void func_ov102_0229cbcc(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern int func_ov102_0229d1e8(UnkStruct_0229d6b4 *self, unsigned char arg);
extern int func_ov102_0229d178(UnkStruct_0229d6b4 *self, unsigned char arg);
extern void func_ov002_02207cf8(unsigned char *p);
extern void func_ov094_022999cc(void);
extern void func_ov102_0229cc90(void *ptr, unsigned char val);

void func_ov102_0229e084(void *self);
void func_ov102_0229d79c(void *p);
void func_ov102_0229d760(void *p);
void func_ov102_0229d740(void *param);
void func_ov102_0229d6b4(UnkStruct_0229d6b4 *self, int val);
void func_ov102_0229d650(struct UnkStruct_0229d650 *obj, unsigned char val);
void func_ov102_0229d5e8(unsigned char *p, unsigned char v);

void func_ov102_0229e0e4(void *arg0)
{
    func_ov102_0229e084((void *) arg0);
}

void func_ov102_0229e0b0(char *self)
{
    func_ov102_0229d470(self);
    func_ov094_0229a084(self + 0xb54);
    func_ov094_0229af20(self + 0xcc);
    func_ov094_0229bbc0(self + 0xb2c);
    func_ov102_0229c534(self);
}

void func_ov102_0229e084(void *self)
{
    func_ov094_0229a05c((char *) self + 0xb54);
    if (func_ov002_02207d5c((char *) self + 0x218c)) {
        func_ov102_0229ce58(self);
    }
}

void func_ov102_0229e050(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
}

void func_ov102_0229e03c(char *p)
{
    func_ov094_0229a29c(p + 0xb54, 0);
}

void func_ov102_0229dff0(int param0)
{
    int val = data_021fbe94;
    func_02002ca4((const void *) data_ov102_0229eb6c, val, 4);
    func_02002c6c((const void *) data_ov102_0229eb90, val, 4, 0x1b9, 0x1b9, 0x238);
    func_ov102_0229c4c0(param0, 0);
}

void func_ov102_0229dfa4(unsigned char *self)
{
    void *ptr = (*(void **) &data_021fbe94);
    unsigned char buf[0x24];

    func_02064328(buf, data_ov102_0229eb50, self[0x25aa]);
    func_02002d14(buf, ptr, 4, 3, 3, 5);
    func_ov094_0229ace4(self + 0xcc, func_ov102_0229d258(self));
}

int func_ov102_0229df94(int a)
{
    return func_ov094_0229a098((void *) (a + 0xb54));
}

void func_ov102_0229defc(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov102_0229d760(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov102_0229d37c(self, a, b, 1);
    if (n != 0x25) {
        func_ov102_0229d6b4((UnkStruct_0229d6b4 *) self, n);
        return;
    }
    if (a >= 0xc8 && a <= 0xf8 && b >= 0x68 && b <= 0x78) {
        func_ov102_0229c460(self, 1);
        return;
    }
    if (func_ov102_0229c364(self, a, b) != 0) {
        func_ov102_0229c318(self);
    }
}

void func_ov102_0229dea4(UnkStruct_0229dea4 *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
        func_ov002_02207ce4(self->sub, 0x3c);
    } else {
        if (func_ov102_0229c2a8(self, 4) != 0 && func_ov102_0229cef8(self) != 0) {
            func_ov102_0229d650((struct UnkStruct_0229d650 *) self, self->flag);
        } else {
            func_ov002_02207d00((void *) self->sub);
        }
    }
}

void func_ov102_0229ddcc(UnkStruct_0229ddcc *self)
{
    int idx, ret;
    char *p1;

    if (func_0206f56c()) {
        func_ov102_0229cc60(self, self->state);
        func_ov102_0229cb50(self);
        func_ov002_02207d24((char *) self + 0x218c, 0);
        func_ov102_0229c460(self, 0);
        return;
    }

    func_ov102_0229cd80(self);
    func_ov102_0229cf74(self);

    p1 = (char *) self->ptr1 + 8;
    idx = func_ov102_0229d37c(self, (int) ((char *) self->ptr0 + 8), (int) p1, 0);

    if (idx != 0x25) {
        if (data_021fbdd8) {
            goto L_special;
        }
        if (func_ov102_0229d0b0(self, idx) != 0) {
            func_ov102_0229d508(self, self->state, p1);
            return;
        }
        ret = func_ov102_0229d320(self, idx);
        if (ret == 0) {
            func_ov102_0229d508(self, self->state, p1);
            return;
        } else {
            func_ov094_022999d8();
            func_ov102_0229d740(self);
            return;
        }
    L_special:
        func_ov102_0229cf3c(self, idx);
        return;
    } else {
        if (!data_021fbdd8) {
            func_ov102_0229d508(self, self->state, p1);
        }
        return;
    }
}

void func_ov102_0229dc44(UnkStruct_0229dc44 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov102_0229d79c((void *) s);
        func_ov002_02207d24((char *) s + 0x218C, 1);
        return;
    }
    if (func_ov102_0229c560(s, func_ov002_02208008(s), 0) != 0) {
        func_ov102_0229cdf4((void *) s);
        func_ov102_0229cab8(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (func_ov102_0229d0b0((void *) s, (unsigned char) s->unk_25A5) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov102_0229d464(s, s->unk_25A5) != 0 || func_ov102_0229d454(s, s->unk_25A5) != 0) {
                if (func_ov102_0229d074(s, s->unk_25A5) == 0) {
                    func_ov102_0229ca38(s);
                }
            } else if (func_ov102_0229d438(s, s->unk_25A5) != 0) {
                func_ov102_0229ca78(s);
            } else if (func_ov102_0229d444(s, s->unk_25A5) != 0) {
                func_ov102_0229ca78(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov102_0229d464(s, s->unk_25A5) != 0 || func_ov102_0229d454(s, s->unk_25A5) != 0) {
                if (func_ov102_0229d074(s, s->unk_25A5) == 0) {
                    if (func_ov102_0229d464(s, s->unk_25A5) != 0) {
                        r = func_ov102_0229d47c(s);
                    } else {
                        r = func_ov102_0229d4ac(s);
                    }
                    if (r != 0x25) {
                        func_ov102_0229d4cc(s, s->unk_25A5, r);
                        func_ov002_02207d24((char *) s + 0x218C, 1);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if ((val & 8) || (val & 2)) {
        func_ov102_0229cb50((void *) s);
        func_ov102_0229c460((void *) s, 1);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (func_ov102_0229c2c0(s) == 0) {
        func_ov002_02207d00((char *) s + 0x218C);
    }
}

void func_ov102_0229dae0(UnkStruct_0229dae0 *s)
{
    unsigned short val;
    if (func_0206f56c() != 0) {
        func_ov102_0229cc60((void *) s, s->unk_25A2);
        func_ov102_0229cb50((void *) s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        func_ov102_0229c460((void *) s, 0);
        return;
    }
    if (func_ov102_0229c560((UnkStruct_0229dc44 *) s, func_ov002_02208008((UnkStruct_0229dc44 *) s), 1) != 0) {
        func_ov102_0229cdf4((void *) s);
        func_ov102_0229cab8((UnkStruct_0229dc44 *) s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    val = data_021fbe40.field;
    if (val & 1) {
        if (func_ov102_0229d464((UnkStruct_0229dc44 *) s, s->unk_25A5) != 0 ||
            func_ov102_0229d454((UnkStruct_0229dc44 *) s, s->unk_25A5) != 0) {
            if (func_ov102_0229d0b0((void *) s, (unsigned char) s->unk_25A5) == 0) {
                if (func_ov102_0229d074((UnkStruct_0229dc44 *) s, s->unk_25A5) != 0) {
                    func_ov102_0229c9fc(s, s->unk_25A5);
                } else {
                    func_ov102_0229c9b0(s, s->unk_25A5);
                }
            }
        } else if (func_ov102_0229d444((UnkStruct_0229dc44 *) s, s->unk_25A5) != 0) {
            func_ov102_0229ca78((UnkStruct_0229dc44 *) s);
        }
        return;
    }
    if (val & 2) {
        if (func_ov102_0229d454((UnkStruct_0229dc44 *) s, s->unk_25A2) != 0) {
            if (s->unk_25A3 != s->unk_25AA) {
                func_ov102_0229d54c(s, (unsigned char) (s->unk_25A3 + 0x1e), 4);
                return;
            }
        }
        if (func_0208e4bc((char *) s + 0x2274) == 1) {
            func_ov102_0229d54c(s, s->unk_25A2, 4);
        } else {
            func_ov102_0229c9fc(s, s->unk_25A2);
        }
        return;
    }
    if (func_ov102_0229c2c0((UnkStruct_0229dc44 *) s) == 0) {
        func_ov102_0229cd38((unsigned char *) s);
        func_ov002_02207d00((char *) s + 0x218C);
    }
}

void func_ov102_0229da90(unsigned char *a)
{
    if (func_ov002_02209f64(a + 0x2274) == 0) {
        func_ov002_02208098(a, a[0x25a7]);
        if ((unsigned char) (a[0x25a7] + 0xFD) <= 1) {
            func_ov102_0229cf90(a, a[0x25a5]);
        }
        func_ov102_0229e5b8(a);
    }
    func_ov102_0229cd38(a);
}

void func_ov102_0229da20(unsigned char *p)
{
    if (func_0208e484(p + 0x2274) == 0) {
        return;
    }
    if (func_ov102_0229d444((UnkStruct_0229dc44 *) p, p[0x25a5]) != 0) {
        unsigned char val = (unsigned char) (p[0x25a5] - 0x1e);
        if (val == p[0x25aa]) {
            func_ov102_0229ca58(p);
        } else {
            p[0x25aa] = val;
            func_ov102_0229c318(p);
        }
    } else {
        if (p[0x25a5] == 0x24) {
            func_ov102_0229c460(p, 1);
        } else {
            func_ov102_0229ca58(p);
        }
    }
}

void func_ov102_0229d9e0(char *ptr)
{
    if (func_0208e484((void *) (ptr + 0x2274)) != 0) {
        func_ov102_0229ca98(ptr);
        if (*(unsigned char *) (ptr + 0x259f) == 1) {
            func_ov002_02208098((void *) ptr, 4);
        } else {
            func_ov002_02208098((void *) ptr, 3);
        }
    }
}

void func_ov102_0229d9b0(void *arg0)
{
    if (func_ov002_02209f9c((char *) arg0 + 0x2274)) {
        func_ov102_0229d5e8((unsigned char *) arg0, ((unsigned char *) arg0)[0x25a5]);
        func_ov002_02208098(arg0, 9);
    }
}

void func_ov102_0229d980(UnkStruct_0229d980 *self)
{
    if (func_0208e484(&self->unk_2274) != 0) {
        func_ov002_02208098((void *) self, self->unk_25A7);
    }
    func_ov102_0229cd38((unsigned char *) self);
}

void func_ov102_0229d928(UnkStruct_0229d928 *self)
{
    if (func_ov002_02209f9c((char *) self + 0x2274) == 0) {
        if (self->unk_25A5 == self->unk_25A6) {
            func_ov102_0229d320(self, self->unk_25A6);
            func_ov102_0229cdf4(self);
            func_ov002_02208098(self, 3);
            func_ov094_022999d8();
        } else {
            func_ov102_0229d54c((UnkStruct_0229dae0 *) self, (u8) self->unk_25A6, 4);
        }
    } else {
        func_ov102_0229cd38((unsigned char *) self);
    }
}

void func_ov102_0229d8e0(unsigned char *param)
{
    if (func_ov002_02209f70(param + 0x2274) == 0) {
        func_ov102_0229cc24(param, param[0x25a6]);
        func_ov102_0229c298(param, 0x40);
        func_ov002_02208098((void *) param, 0xc);
        func_ov102_0229cdf4((void *) param);
    } else {
        func_ov002_02208098((void *) param, 3);
    }
}

void func_ov102_0229d88c(UnkStruct_0229d88c *self)
{
    if (func_0208e484(&self->unk_2274) != 0) {
        func_ov002_02208098(self, self->unk_25A7);
    }
    if (func_ov002_02209f9c(&self->unk_2274) != 0) {
        if (func_ov102_0229c2a8(self, 0x40) != 0) {
            func_ov102_0229c288(self, 0x40);
            func_ov094_022999c0();
        }
        func_ov102_0229cd38((unsigned char *) self);
    }
}

void func_ov102_0229d830(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x225c)) {
        if (func_ov102_0229c2a8(self, 0x200)) {
            func_ov102_0229c288(self, 0x200);
            func_ov102_0229cd08(self);
        } else {
            func_ov102_0229cc60(self, *((unsigned char *) ((char *) self + 0x25a2)));
            func_ov102_0229d740(self);
            func_ov094_022999d8();
        }
    } else {
        func_ov102_0229cd08(self);
    }
}

void func_ov102_0229d7f8(void *base)
{
    if (func_ov002_0220b8ac((char *) base + 0x22d8, 1)) {
        func_ov002_02208098(base, *(unsigned char *) ((char *) base + 0x25a7));
        func_0208e5cc((char *) base + 0x2274);
    }
}

void func_ov102_0229d7b8(struct UnkStruct_0229d7b8 *self)
{
    unsigned char *timer;

    timer = (unsigned char *) self;
    timer += 0x25a9;
    if (*timer != 0) {
        *timer = *timer - 1;
        return;
    }
    *((unsigned char *) self + 0x8c) = 4;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((void *) ((char *) self + 0x218c), 1);
    func_ov102_0229cb50((void *) self);
}

void func_ov102_0229d79c(void *p)
{
    func_ov102_0229cb50(p);
    func_ov102_0229cfdc(p);
    func_ov002_02208098(p, 0);
}

void func_ov102_0229d760(void *p)
{
    ((unsigned char *) p)[0x25a1] = 0x25;
    func_ov102_0229cbcc(p);
    func_ov002_02207fc0(p);
    func_ov102_0229cdf4(p);
    func_ov002_02208098(p, 3);
    func_ov102_0229cf90((unsigned char *) p, ((unsigned char *) p)[0x25a5]);
}

void func_ov102_0229d740(void *param)
{
    if (func_0206fe60()) {
        func_ov102_0229d79c(param);
    } else {
        func_ov102_0229d760(param);
    }
}

void func_ov102_0229d6b4(UnkStruct_0229d6b4 *self, int val)
{
    unsigned char a;
    unsigned char b;

    self->unk_25A0 = val;
    func_ov002_02208098((void *) self, 1);
    a = (*(unsigned char *) &data_021f6c58);
    b = (*(unsigned char *) &data_021f6c54);

    self->unk_24D8 = func_ov102_0229d1e8(self, self->unk_25A0) - a;
    self->unk_24DC = func_ov102_0229d178(self, self->unk_25A0) - b;

    self->unk_25A1 = val;
    func_ov002_02207cf8(&self->sub_218c);

    if (func_ov102_0229d0b0((void *) self, val) != 0) {
        func_ov102_0229c288((void *) self, 4);
    } else {
        func_ov102_0229c298((unsigned char *) self, 4);
        func_ov094_022999cc();
    }
}

void func_ov102_0229d650(struct UnkStruct_0229d650 *obj, unsigned char val)
{
    obj->data[0x25a2] = val;
    obj->data[0x25a4] = val;
    obj->data[0x25a3] = obj->data[0x25aa];
    func_ov002_02207d24(&obj->data[0x218c], 1);
    func_ov102_0229cc90(obj, val);
    if (obj->data[0x259f] == 1) {
        func_ov002_02208098(obj, 2);
    }
    func_ov102_0229cd80(obj);
    func_ov094_022999c0();
}

void func_ov102_0229d5e8(unsigned char *p, unsigned char v)
{
    p[0x25a2] = v;
    p[0x25a4] = v;
    p[0x25a3] = p[0x25aa];
    func_ov002_02207d24((void *) (p + 0x218c), 1);
    func_ov102_0229cc90((void *) p, v);
    if (p[0x259f] == 1) {
        p[0x25a7] = 4;
    }
    func_ov102_0229cd38(p);
    func_ov094_022999c0();
}
