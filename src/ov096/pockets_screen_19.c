/* pockets_screen_19: 10 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_022a0e48 @ 0x022a0e48, 0x210 bytes, Thumb
 * func_ov096_022a0da8 @ 0x022a0da8, 0xa0 bytes, Thumb
 * func_ov096_022a0d60 @ 0x022a0d60, 0x48 bytes, Thumb
 * func_ov096_022a0cb8 @ 0x022a0cb8, 0xa8 bytes, Thumb
 * func_ov096_022a0c28 @ 0x022a0c28, 0x90 bytes, Thumb
 * func_ov096_022a0af0 @ 0x022a0af0, 0x138 bytes, Thumb
 * func_ov096_022a0880 @ 0x022a0880, 0x270 bytes, Thumb
 * func_ov096_022a07c8 @ 0x022a07c8, 0xb8 bytes, Thumb
 * func_ov096_022a072c @ 0x022a072c, 0x9c bytes, Thumb
 * func_ov096_022a06d8 @ 0x022a06d8, 0x54 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x8d];
    u8 unk_8D;
    char pad_8E[0xa4 - 0x8e];
    char *unk_A4;
    char *unk_A8;
    char pad_AC[0xb4 - 0xac];
    u8 unk_B4;
    char pad_B5[0xc0 - 0xb5];
    u8 unk_C0;
} UnkStruct_022a0e48;

typedef struct UnkStruct_022a0da8 UnkStruct_022a0da8;

struct UnkStruct_022a0da8 {
    u8 unk_00[0xa4];
    char *unk_A4;
    char *unk_A8;
    u8 p1[8];
    u8 unk_B4;
};

typedef struct {
    char pad_00[0xB5];
    unsigned char unk_B5;
    char pad_B6[0x2418 - 0xB5 - 1];
    void *unk_2418;
} UnkStruct_022a0af0;

typedef struct {
    char pad_00[0xac];
    u16 unk_AC;
    u16 unk_AE;
    u8 unk_B0;
    char pad_B1[3];
    u8 unk_B4;
    u8 unk_B5;
    char pad_B6[3];
    u8 unk_B9;
    char pad_BA[0xc0 - 0xba];
    u8 unk_C0;
    char pad_C1[0x358 - 0xc1];
    char unk_358[0x2418 - 0x358];
    char unk_2418[4];
} UnkStruct_022a0880;

extern int func_0206f56c(void);
extern void func_ov096_0229e898(UnkStruct_022a0e48 *, int, int);
extern int func_ov096_022a18dc(UnkStruct_022a0e48 *, int);
extern void func_ov096_0229ea88(UnkStruct_022a0e48 *);
extern void func_ov096_0229ed44(UnkStruct_022a0e48 *);
extern int func_ov096_0229f75c(UnkStruct_022a0e48 *, char *, char *, int);
extern int func_ov096_0229f4f8(UnkStruct_022a0e48 *, char *, char *, int);
extern int func_ov096_0229ee9c(UnkStruct_022a0e48 *, int, int);
extern int func_ov096_0229f820(UnkStruct_022a0e48 *, int);
extern void func_ov096_0229c414(UnkStruct_022a0e48 *);
extern int func_ov096_0229f650(UnkStruct_022a0e48 *, int);
extern void func_ov096_0229fb9c(UnkStruct_022a0e48 *);
extern int func_ov096_0229f830(UnkStruct_022a0e48 *, int);
extern void func_ov094_022999d8(void);
extern unsigned char *func_ov096_0229f90c(UnkStruct_022a0e48 *, int, int);
extern void func_ov096_0229ec90(UnkStruct_022a0e48 *, int);
extern u8 func_ov096_0229f3d4(UnkStruct_022a0e48 *, char *, char *);
extern int func_ov096_0229e6b0(UnkStruct_022a0e48 *);
extern int func_ov096_0229e71c(UnkStruct_022a0e48 *);
extern int func_ov096_0229e4f8(UnkStruct_022a0e48 *);
extern void func_ov096_0229e29c(UnkStruct_022a0e48 *);
extern void func_ov096_0229e67c(UnkStruct_022a0e48 *);
extern int func_ov096_0229e170(UnkStruct_022a0e48 *, int);
extern int func_ov096_0229e1ec(UnkStruct_022a0e48 *);
extern int func_ov096_0229f460(UnkStruct_022a0e48 *, char *, char *);
extern int func_ov096_0229c310(UnkStruct_022a0e48 *);
extern void func_ov096_0229c348(UnkStruct_022a0e48 *);
extern u8 data_021fbdd8;
extern int func_ov096_0229f4ac(UnkStruct_022a0da8 *, int);
extern void func_ov096_0229c4ec(int);
extern int func_ov002_02208054(int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220b498(void *object);
extern void func_ov096_0229c514(int);
extern void func_ov096_0229d16c(void *self);
extern int func_ov096_0229fb6c(void *self);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_02208aec(void *p, int a, int b);
extern void func_ov002_022090b0(void *p, int n);
extern int func_ov002_02208a8c(void *p, int a, int b);
extern void func_ov094_02299c74(char *, int);
extern int func_ov096_0229ec38(char *, int);
extern void func_ov096_0229fa44(char *, int);
extern void func_ov096_0229f9dc(char *, int);
extern void func_ov096_0229c2ec(char *, int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_022a0af0 *s);
extern int func_ov096_0229c560(UnkStruct_022a0af0 *s, int a, int b);
extern void func_ov096_0229eb14(UnkStruct_022a0af0 *s);
extern void func_ov096_0229dd94(UnkStruct_022a0af0 *s);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov096_0229fbf0(UnkStruct_022a0af0 *s);
extern int func_ov096_0229f150(UnkStruct_022a0af0 *s, unsigned char b);
extern void func_ov096_0229cc74(UnkStruct_022a0af0 *s, unsigned char b, int zero);
extern int func_ov096_0229f810(UnkStruct_022a0af0 *s, unsigned char b);
extern void func_ov096_0229dc08(UnkStruct_022a0af0 *s);
extern int func_ov090_02299078(int zero);
extern int func_ov090_02299098(int zero);
extern void func_ov096_0229db78(UnkStruct_022a0880 *, int);
extern int func_ov096_0229f800(UnkStruct_022a0880 *, unsigned int code);
extern void func_0200467c(int);
extern int func_ov096_0229ef30(UnkStruct_022a0880 *, int, int, int);
extern u16 func_ov096_0229f0dc(UnkStruct_022a0880 *, int);
extern int func_ov096_0229f088(UnkStruct_022a0880 *, int);
extern int func_ov096_0229defc(UnkStruct_022a0880 *, u16 *, int, u16 *, int);
extern int func_ov096_0229f7ac(UnkStruct_022a0880 *, int);
extern void func_ov094_0229aa14(void *, int, int, int);
extern void func_ov096_0229db30(UnkStruct_022a0880 *, int);
extern int func_ov096_0229ee80(UnkStruct_022a0880 *, int);
extern int func_ov096_0229ea5c(UnkStruct_022a0880 *);
extern char data_021fbe40[];
extern int func_ov096_0229c2fc(void *self, int param);
extern int func_ov002_02209044(void *p1, int val, void *p2, unsigned char b);
extern void func_ov096_0229d1a0(void *self);
extern void func_ov096_0229dd44(void *self);
extern void func_ov002_0220a1dc(void *p);
extern void func_ov096_0229dce0(void *self);
extern int func_0208e484(void *);
extern int func_ov096_0229d0e4(void *);
extern void func_ov002_02209114(void *, int, int);

void func_ov096_022a0e48(UnkStruct_022a0e48 *p)
{
    char *a;
    char *b;
    int r;
    u8 q;

    if (func_0206f56c() != 0) {
        func_ov096_0229e898(p, p->unk_B4, 1);
        func_ov096_022a18dc(p, 7);
        return;
    }
    func_ov096_0229ea88(p);
    func_ov096_0229ed44(p);
    a = p->unk_A4 + 8;
    b = p->unk_A8 + 8;
    r = func_ov096_0229f75c(p, a, b, 0);
    if (r == 0x26) {
        r = func_ov096_0229f4f8(p, a, b, 0);
    }
    if (r != 0x26) {
        if (data_021fbdd8 == 0) {
            if (func_ov096_0229ee9c(p, r, p->unk_B4) == 0) {
                if (func_ov096_0229f820(p, r) != 0) {
                    func_ov096_0229c414(p);
                }
                func_ov096_0229f650(p, r);
                if (p->unk_8D == 5) {
                    func_ov096_0229fb9c(p);
                }
                if (func_ov096_0229f830(p, r) != 0 || func_ov096_0229f820(p, r) != 0) {
                    func_ov094_022999d8();
                }
            } else {
                func_ov096_0229f90c(p, p->unk_B4, 4);
            }
        } else {
            func_ov096_0229ec90(p, r);
        }
        return;
    }

    q = func_ov096_0229f3d4(p, a, b);
    if (q != 0x26) {
        if (data_021fbdd8 == 0) {
            if (q == 0x22 || q == 0x23) {
                if (func_ov096_0229e6b0(p) == 0) {
                    func_ov096_0229f90c(p, p->unk_B4, 4);
                    return;
                }
                if (func_ov096_0229e71c(p) != 0) {
                    func_ov096_0229fb9c(p);
                }
            } else if (q == 0x24) {
                p->unk_C0 = (u8) func_ov096_0229e4f8(p);
                if (p->unk_C0 < 1) {
                    func_ov096_0229e29c(p);
                    return;
                }
                if (p->unk_C0 == 1) {
                    func_ov096_0229f90c(p, p->unk_B4, 4);
                    return;
                }
                func_ov096_0229e67c(p);
            } else if (q == 0x25) {
                if (func_ov096_0229e170(p, 0) != 0) {
                    func_ov096_0229e1ec(p);
                    return;
                }
                func_ov096_0229f90c(p, p->unk_B4, 4);
            } else {
                func_ov096_0229f90c(p, p->unk_B4, 4);
            }
        } else {
            func_ov096_0229ec90(p, q);
        }
        return;
    }

    if (func_ov096_0229f460(p, a, b) != 0) {
        if (data_021fbdd8 == 0) {
            if (func_ov096_0229c310(p) != 0) {
                func_ov096_0229c348(p);
                func_ov096_0229fb9c(p);
            } else {
                func_ov096_0229f90c(p, p->unk_B4, 4);
            }
        } else {
            func_ov096_0229ec90(p, 0x21);
        }
        return;
    }
    if (data_021fbdd8 == 0) {
        func_ov096_0229f90c(p, p->unk_B4, 4);
    }
}

void func_ov096_022a0da8(UnkStruct_022a0da8 *self)
{
    int r;
    if (func_0206f56c() != 0) {
        func_ov096_0229e898((UnkStruct_022a0e48 *) self, self->unk_B4, 1);
        func_ov096_022a18dc((UnkStruct_022a0e48 *) self, 7);
    } else {
        func_ov096_0229ea88((UnkStruct_022a0e48 *) self);
        func_ov096_0229ed44((UnkStruct_022a0e48 *) self);
        r = func_ov096_0229f4f8((UnkStruct_022a0e48 *) self, self->unk_A4 + 8, self->unk_A8 + 8, 0);
        if (r != 0x26) {
            if (data_021fbdd8 == 0) {
                if (func_ov096_0229f4ac(self, r) == 0) {
                    func_ov096_0229f90c((UnkStruct_022a0e48 *) self, self->unk_B4, 4);
                }
                func_ov094_022999d8();
                func_ov096_0229fb9c((UnkStruct_022a0e48 *) self);
            } else {
                func_ov096_0229ec90((UnkStruct_022a0e48 *) self, r);
            }
        } else {
            if (data_021fbdd8 == 0) {
                func_ov096_0229f90c((UnkStruct_022a0e48 *) self, self->unk_B4, 4);
            }
        }
    }
}

void func_ov096_022a0d60(int r0)
{
    int r4 = r0;
    if (func_0206f56c()) {
        func_ov096_0229c4ec(r4);
    } else {
        if (func_ov002_02208054(r4, 1)) {
            func_ov002_02208098((void *) (r4), 0x17);
        } else {
            if (func_ov002_0220b498((void *) (r4 + 0x2d9c))) {
                func_ov096_0229c514(r4);
            }
        }
    }
}

void func_ov096_022a0cb8(char *self)
{
    unsigned int ok;
    int n;

    if (func_0206f56c() != 0) {
        func_ov096_0229d16c(self);
        return;
    }
    if (func_ov002_02208054((int) self, 1) != 0) {
        func_ov096_0229fb6c(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov002_02208aec(self + 0x2564, data_021f6c58, data_021f6c54);
    if (n >= 0) {
        func_ov002_022090b0(self + 0x2564, n);
        *(u8 *) (self + 0xbe) = (u8) func_ov002_02208a8c(self + 0x2564, *(u8 *) (self + 0xbd), (u8) n);
        func_ov002_02208098((void *) (self), 0x23);
    } else {
        func_ov096_0229d16c(self);
    }
}

void func_ov096_022a0c28(char *self)
{
    if (func_0206f56c()) {
        func_ov096_022a18dc((UnkStruct_022a0e48 *) self, 7);
        func_ov094_02299c74(self + 0xde0, 0);
        return;
    } else {
        if ((*(unsigned char *) &data_021fbdd8) == 0) {
            func_ov002_02208098((void *) (self), 0);
            func_ov094_02299c74(self + 0xde0, 0);
            return;
        } else {
            if (func_ov096_0229ec38(self, 4) == 0) {
                return;
            }
            func_ov096_0229fa44(self, 0x25);
            *(int *) (self + 0x9c) = -8;
            *(int *) (self + 0xa0) = -8;
            func_ov096_0229f9dc(self, 0x25);
            func_ov096_0229c2ec(self, 0x4000);
            func_ov094_02299c74(self + 0xde0, *(unsigned char *) (self + 0xbf));
        }
    }
}

void func_ov096_022a0af0(UnkStruct_022a0af0 *s)
{
    if (func_ov002_02208014(s) != 0) {
        func_ov096_0229fbf0(s);
        func_ov002_02207d24((char *) s + 0x2418, 1);
    } else {
        if (func_ov096_0229c560(s, func_ov002_02208008(s), 0) != 0) {
            func_ov096_0229eb14(s);
            func_ov096_0229dd94(s);
            func_ov002_02207d24((char *) s + 0x2418, 0);
        } else {
            unsigned short val = (*(struct { char pad2[2]; unsigned short field; } *) data_021fbe40).field;
            if (val & 1) {
                if (func_ov096_0229f830((UnkStruct_022a0e48 *) s, (unsigned char) s->unk_B5) != 0 || func_ov096_0229f820((UnkStruct_022a0e48 *) s, (unsigned char) s->unk_B5) != 0) {
                    if (func_ov096_0229f150(s, s->unk_B5) == 0) {
                        func_ov096_0229cc74(s, s->unk_B5, 0);
                    }
                } else {
                    if (func_ov096_0229f810(s, s->unk_B5) != 0) {
                        func_ov096_0229dc08(s);
                    } else {
                        if (s->unk_B5 == 0x25) {
                            func_ov096_0229cc74(s, 0x25, 0);
                        } else if (s->unk_B5 == 0x24) {
                            func_ov096_0229cc74(s, 0x24, 0);
                        }
                    }
                }
            } else if (val & 0x100) {
                func_ov096_022a18dc((UnkStruct_022a0e48 *) s, func_ov090_02299078(0));
            } else if (val & 0x200) {
                func_ov096_022a18dc((UnkStruct_022a0e48 *) s, func_ov090_02299098(0));
            } else if (val & 2) {
                func_ov096_022a18dc((UnkStruct_022a0e48 *) s, 7);
            } else {
                func_ov002_02207d00((char *) s + 0x2418);
            }
        }
    }
}

void func_ov096_022a0880(UnkStruct_022a0880 *p)
{
    u16 h;
    int v;

    if (func_0206f56c() != 0) {
        func_ov096_0229e898((UnkStruct_022a0e48 *) p, p->unk_B4, 1);
        func_ov096_022a18dc((UnkStruct_022a0e48 *) p, 7);
        return;
    }
    if (func_ov096_0229c560((UnkStruct_022a0af0 *) p, func_ov002_02208008((UnkStruct_022a0af0 *) p), 1) != 0) {
        func_ov096_0229eb14((UnkStruct_022a0af0 *) p);
        func_ov096_0229dd94((UnkStruct_022a0af0 *) p);
        func_ov002_02207d24(p->unk_2418, 0);
        return;
    }
    if (((*(struct { u16 h0; u16 h2; } *) data_021fbe40).h2 & 1) != 0) {
        if (p->unk_B5 == 0x21) {
            if (func_ov096_0229c310((UnkStruct_022a0e48 *) p) == 0) {
                return;
            }
            func_ov096_0229c414((UnkStruct_022a0e48 *) p);
            func_ov096_0229db78(p, p->unk_B5);
            return;
        }
        if (func_ov096_0229f800(p, p->unk_B5) != 0) {
            if (p->unk_B5 == 0x24) {
                p->unk_C0 = (u8) func_ov096_0229e4f8((UnkStruct_022a0e48 *) p);
                func_ov096_0229db78(p, p->unk_B5);
                return;
            }
            if (p->unk_B5 == 0x22) {
                func_ov096_0229c414((UnkStruct_022a0e48 *) p);
                func_ov096_0229db78(p, p->unk_B5);
                return;
            }
            if (p->unk_B5 == 0x25) {
                if (func_ov096_0229e170((UnkStruct_022a0e48 *) p, 1) == 0 && p->unk_B4 == 0x25) {
                    func_0200467c(0x2a);
                    return;
                }
                func_ov096_0229c414((UnkStruct_022a0e48 *) p);
                func_ov096_0229db78(p, p->unk_B5);
            }
            return;
        }
        if (func_ov096_0229ef30(p, p->unk_B5, p->unk_AC, p->unk_B0) != 0) {
            return;
        }
        if (func_ov096_0229f820((UnkStruct_022a0e48 *) p, p->unk_B5) != 0) {
            func_ov096_0229c414((UnkStruct_022a0e48 *) p);
        }
        if (func_ov096_0229f830((UnkStruct_022a0e48 *) p, p->unk_B5) != 0) {
            h = func_ov096_0229f0dc(p, p->unk_B5);
            v = func_ov096_0229f088(p, p->unk_B5);
            if (func_ov096_0229defc(p, &p->unk_AC, p->unk_B0, &h, v) == 0) {
                func_ov094_0229aa14(p->unk_358, func_ov096_0229f7ac(p, p->unk_B5), h, v);
            }
        }
        if (func_ov096_0229f0dc(p, p->unk_B5) == 0xfff1) {
            func_ov096_0229db78(p, p->unk_B5);
            return;
        }
        if (p->unk_B9 != 0x26 && func_ov096_0229e170((UnkStruct_022a0e48 *) p, 1) != 0) {
            p->unk_B9 = p->unk_B5;
            p->unk_AE = p->unk_AC;
        }
        func_ov096_0229db30(p, p->unk_B5);
        return;
    }
    if (((*(struct { u16 h0; u16 h2; } *) data_021fbe40).h2 & 2) != 0) {
        if (func_ov096_0229ee80(p, p->unk_B4) == 0) {
            func_ov096_0229db78(p, p->unk_B4);
        } else if (p->unk_B9 != 0x26) {
            v = p->unk_B4;
            p->unk_B4 = p->unk_B9;
            func_ov096_0229db78(p, p->unk_B4);
            p->unk_B9 = (u8) v;
            func_ov096_0229c2ec((char *) p, 0x2000);
        }
    }
    func_ov096_0229ea5c(p);
    func_ov002_02207d00(p->unk_2418);
}

void func_ov096_022a07c8(void *self)
{
    if (func_0206f56c()) {
        func_ov096_0229e898((UnkStruct_022a0e48 *) self, (unsigned char) (*((unsigned char *) self + 0xb4)), 1);
        func_ov096_022a18dc((UnkStruct_022a0e48 *) self, 7);
        return;
    } else {
        void *ret = (void *) func_ov002_02208008((UnkStruct_022a0af0 *) self);
        if (func_ov096_0229c560((UnkStruct_022a0af0 *) self, (int) ret, 2)) {
            func_ov096_0229eb14((UnkStruct_022a0af0 *) self);
            func_ov096_0229dd94((UnkStruct_022a0af0 *) self);
            func_ov002_02207d24((char *) self + 0x2418, 0);
            return;
        } else {
            unsigned short flags = *(unsigned short *) (data_021fbe40 + 2);
            if (flags & 1) {
                if (func_ov096_0229f150((UnkStruct_022a0af0 *) self, *((unsigned char *) self + 0xb5))) {
                    func_ov096_0229db78((UnkStruct_022a0880 *) self, (unsigned char) (*((unsigned char *) self + 0xb5)));
                } else {
                    func_ov096_0229db30((UnkStruct_022a0880 *) self, (unsigned char) (*((unsigned char *) self + 0xb5)));
                }
                return;
            } else if (flags & 2) {
                func_ov096_0229db78((UnkStruct_022a0880 *) self, (unsigned char) (*((unsigned char *) self + 0xb4)));
                return;
            } else {
                func_ov096_0229ea5c((UnkStruct_022a0880 *) self);
                func_ov002_02207d00((char *) self + 0x2418);
                return;
            }
        }
    }
}

void func_ov096_022a072c(void *self)
{
    if (func_0206f56c()) {
        func_ov096_0229d1a0(self);
        return;
    }
    if (func_ov002_02208014(self)) {
        func_ov096_0229d1a0(self);
        return;
    }
    {
        int v = func_ov002_02208008((UnkStruct_022a0af0 *) self);
        unsigned char b = (unsigned char) func_ov096_0229c2fc(self, 0x00040000);
        if (func_ov002_02209044((unsigned char *) self + 0x2564, v, (unsigned char *) self + 0xbc, b)) {
            func_ov096_0229dd44(self);
            return;
        }
        if ((*(struct { unsigned short pad; unsigned short flags; } *) data_021fbe40).flags & 1) {
            func_ov002_0220a1dc((unsigned char *) self + 0x2500);
            func_ov002_02208098((void *) (self), 0xe);
        } else if ((*(struct { unsigned short pad; unsigned short flags; } *) data_021fbe40).flags & 2) {
            func_ov096_0229dce0(self);
        }
    }
}

void func_ov096_022a06d8(unsigned char *arg)
{
    int t;
    unsigned char *p;

    if (func_0208e484(arg + 0x2500) == 0) {
        return;
    }

    p = arg + arg[0xbc];
    arg[0xbb] = p[0x2951];

    t = func_ov096_0229d0e4(arg);
    func_ov002_02209114(arg + 0x2564, arg[0xbc], t);
    func_ov002_02208098((void *) (arg), 30);
}
