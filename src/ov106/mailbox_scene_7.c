/* mailbox_scene_7: 11 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229e6c4 @ 0x0229e6c4, 0x70 bytes, Thumb
 * func_ov106_0229e67c @ 0x0229e67c, 0x48 bytes, Thumb
 * func_ov106_0229e544 @ 0x0229e544, 0x138 bytes, Thumb
 * func_ov106_0229e4fc @ 0x0229e4fc, 0x48 bytes, Thumb
 * func_ov106_0229e430 @ 0x0229e430, 0xcc bytes, Thumb
 * func_ov106_0229e2dc @ 0x0229e2dc, 0x154 bytes, Thumb
 * func_ov106_0229e1d8 @ 0x0229e1d8, 0x104 bytes, Thumb
 * func_ov106_0229e134 @ 0x0229e134, 0xa4 bytes, Thumb
 * func_ov106_0229e114 @ 0x0229e114, 0x20 bytes, Thumb
 * func_ov106_0229e078 @ 0x0229e078, 0x9c bytes, Thumb
 * func_ov106_0229e014 @ 0x0229e014, 0x64 bytes, Thumb
 */

typedef struct UnkStruct_0229e544 {
    char pad_00[0xac];
    void *unk_AC;
    void *unk_B0;
    char pad_B4[3];
    unsigned char unk_B7;
} UnkStruct_0229e544;

typedef struct UnkStruct_0229e430 {
    unsigned char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char pad_BD[0x2247];
    char unk_2304[1];
    unsigned char pad_2305[0x3ec];
    unsigned char arr26f1[1];
} UnkStruct_0229e430;

typedef struct {
    char pad_00[0xB8];
    unsigned char unk_B8;
    char pad_B9[0x21B8 - 0xB8 - 1];
    void *unk_21B8;
} UnkStruct_0229e2dc;

struct GlobalFlags {
    unsigned char pad_00[2];
    unsigned short flags;
};

struct OV106Flags {
    unsigned short pad_00;
    unsigned short flags;
};

typedef struct {
    unsigned char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char unk_BD;
    unsigned char pad_BE[0x22a0 - 0xbe];
    char unk_22A0;
    unsigned char pad_22A1[0x2304 - 0x22a1];
    char unk_2304;
    unsigned char pad_2305[0x26f1 - 0x2305];
    unsigned char unk_26F1[1];
} UnkStruct_0229e014;

extern int func_0206f56c(void);
extern int func_ov106_0229c364(void *, int);
extern int func_ov106_0229cf8c(void *receiver);
extern void func_ov106_0229d5c4(void *, unsigned char);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_022096d8(void *, int);
extern int func_ov002_02207d24(void *, int);
extern unsigned char data_021fbdd8;
extern int func_ov002_02207cc0(int object);
extern void func_ov106_0229c798(const unsigned char *, unsigned char, int);
extern void func_ov106_0229cd60(UnkStruct_0229e544 *, int);
extern void func_ov106_0229c378(UnkStruct_0229e544 *);
extern void func_ov106_0229ce38(UnkStruct_0229e544 *);
extern void func_ov106_0229d00c(UnkStruct_0229e544 *);
extern int func_ov106_0229d2e4(UnkStruct_0229e544 *, void *, void *, int);
extern int func_ov106_0229d3a0(UnkStruct_0229e544 *, int);
extern int func_ov106_0229d390(UnkStruct_0229e544 *, int);
extern void func_ov106_0229d518(UnkStruct_0229e544 *, int, int);
extern int func_ov106_0229d090(UnkStruct_0229e544 *, int);
extern int func_ov106_0229d0d0(UnkStruct_0229e544 *, int);
extern int func_ov106_0229d29c(UnkStruct_0229e544 *, int);
extern void func_ov106_0229d4e4(UnkStruct_0229e544 *, int, void *);
extern void func_ov106_0229cfd0(UnkStruct_0229e544 *, int);
extern void func_ov106_0229d73c(UnkStruct_0229e544 *);
extern void func_ov094_022999d8(void);
extern int func_ov002_02208054(void *, int);
extern int func_ov002_0220b498(void *object);
extern void func_ov106_0229c418(void *);
extern void func_ov106_0229c458(void *);
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208e28(const char *);
extern int func_ov002_02208b00(const char *, unsigned char, unsigned char);
extern void func_ov106_0229c868(const void *);
extern void func_0200467c(int);
extern void func_ov002_02209114(const char *, int, int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229e2dc *s);
extern int func_ov106_0229c4a0(UnkStruct_0229e2dc *s, int a, int b);
extern void func_ov002_02207d00(void *p);
extern void func_ov106_0229d790(UnkStruct_0229e2dc *s);
extern void func_ov106_0229cea8(UnkStruct_0229e2dc *s);
extern void func_ov106_0229cbdc(UnkStruct_0229e2dc *s);
extern int func_ov106_0229d384(UnkStruct_0229e2dc *s, unsigned char b);
extern void func_ov106_0229ca1c(UnkStruct_0229e2dc *s);
extern int func_ov106_0229d48c(UnkStruct_0229e2dc *s);
extern void func_ov106_0229d4ac(UnkStruct_0229e2dc *s, unsigned char b, int v);
extern void func_ov106_0229cc50(UnkStruct_0229e2dc *s);
extern void func_ov106_0229c9a0(void *self, unsigned char b);
extern void func_ov106_0229c958(void *self, unsigned char b);
extern void func_ov106_0229ce0c(void *self);
extern unsigned short data_021fbe40[];
extern int func_0208e4bc(char *ptr);
extern int func_ov002_0220b5ec(char *ptr, int val);
extern int func_ov002_0220b59c(char *ptr, int val);
extern void func_ov002_0220a0b4(char *ptr, int a, int b);
extern void func_ov002_0220a374(char *ptr, int val);
extern void func_ov002_0220a1dc(char *ptr);
extern int func_0208e484(void *);
extern int func_ov002_02209044(const void *, int, const void *, unsigned char);
extern void func_ov106_0229cb58(const void *);
extern int func_ov106_0229caf4(const void *);

void func_ov106_0229e6c4(void *param)
{
    if (func_0206f56c()) {
        func_ov002_02208098((void *) (param), 6);
        return;
    }
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (param), 6);
        return;
    }
    if (func_ov106_0229c364(param, 4) == 0) {
        return;
    }
    if (func_ov106_0229cf8c(param) == 0) {
        return;
    }
    func_ov106_0229d5c4(param, *((unsigned char *) param + 0xB5));
    func_ov002_022096d8((char *) param + 0x2304, 0);
    func_ov002_02207d24((char *) param + 0x21B8, 1);
}

void func_ov106_0229e67c(unsigned char *obj)
{
    if (func_ov002_02207cc0((int) (obj + 0x21b8)) == 0) {
        return;
    }
    if (obj[0xbf] != 0) {
        obj[0xbf]--;
    } else {
        func_ov106_0229c798(obj, obj[0xb5], 1);
        func_ov002_02208098((void *) (obj), 2);
    }
}

void func_ov106_0229e544(UnkStruct_0229e544 *param)
{
    void *r6;
    int r4;

    if (func_0206f56c()) {
        func_ov106_0229cd60(param, param->unk_B7);
        func_ov106_0229c378(param);
        func_ov002_02207d24((char *) param + 0x21b8, 0);
        return;
    }

    func_ov106_0229ce38(param);
    func_ov106_0229d00c(param);
    r6 = (void *) ((char *) param->unk_AC + 8);
    r4 = func_ov106_0229d2e4(param, r6, (char *) param->unk_B0 + 0x18, 0);

    if (r4 == 0x20) {
        goto label20;
    }
    if (data_021fbdd8 != 0) {
        goto gflag_nonzero;
    }

    if (func_ov106_0229d3a0(param, param->unk_B7) != 0 && func_ov106_0229d390(param, r4) != 0) {
        func_ov106_0229d518(param, param->unk_B7, 4);
        return;
    }

    if (func_ov106_0229d390(param, param->unk_B7) != 0 && func_ov106_0229d3a0(param, r4) != 0 &&
        func_ov106_0229d090(param, r4) == 0) {
        func_ov106_0229d518(param, param->unk_B7, 4);
        return;
    }

    if (func_ov106_0229d0d0(param, r4) != 0 || func_ov106_0229d29c(param, r4) == 0) {
        func_ov106_0229d4e4(param, param->unk_B7, r6);
    } else {
        func_ov094_022999d8();
        func_ov106_0229d73c(param);
    }
    goto end;

gflag_nonzero:
    if (func_ov106_0229d3a0(param, param->unk_B7) != 0 && func_ov106_0229d390(param, r4) != 0) {
        goto end;
    }
    func_ov106_0229cfd0(param, r4);
    goto end;

label20:
    if (data_021fbdd8 == 0) {
        func_ov106_0229d4e4(param, param->unk_B7, r6);
    }
end:
    return;
}

void func_ov106_0229e4fc(void *arg)
{
    if (func_0206f56c() != 0) {
        func_ov106_0229c418(arg);
        return;
    }
    if (func_ov002_02208054(arg, 1) != 0) {
        func_ov002_02208098((void *) (arg), 9);
        return;
    }
    if (func_ov002_0220b498((void *) ((char *) arg + 0x2b3c)) != 0) {
        func_ov106_0229c458(arg);
    }
}

void func_ov106_0229e430(UnkStruct_0229e430 *self)
{
    int r1;
    unsigned int flag;
    int res;
    int r6;

    r1 = func_ov002_02208e28(self->unk_2304);
    if (r1 == 0) {
        return;
    }

    if (func_0206f56c() != 0) {
        func_ov106_0229c868(self);
        return;
    }

    if (func_ov002_02208054((void *) self, 1) != 0) {
        func_ov106_0229c868(self);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag == 0) {
        return;
    }

    res = func_ov002_02208b00(self->unk_2304, data_021f6c58, data_021f6c54);
    if (res < 0) {
        return;
    }

    if (func_ov106_0229c364((void *) self, 0x10000) != 0 && res == 0) {
        return;
    }

    self->unk_BC = self->arr26f1[res];
    r6 = 1;
    if (self->unk_BC == 2) {
        r6 = 0;
        func_0200467c(0x24);
    }

    func_ov002_02209114(self->unk_2304, res, r6);
    func_ov002_02208098((void *) (self), 0x17);
}

void func_ov106_0229e2dc(UnkStruct_0229e2dc *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov106_0229d790(s);
        func_ov002_02207d24((char *) s + 0x21B8, 1);
        return;
    }
    if (func_ov106_0229c4a0(s, func_ov002_02208008(s), 0) != 0) {
        func_ov106_0229cea8(s);
        func_ov106_0229cbdc(s);
        func_ov002_02207d24((char *) s + 0x21B8, 0);
        return;
    }
    if (func_ov106_0229d0d0((UnkStruct_0229e544 *) s, (unsigned char) s->unk_B8) == 0) {
        val = (*(struct {
                  char pad2[2];
                  unsigned short field;
              } *) data_021fbe40)
                  .field;
        if (val & 1) {
            if (func_ov106_0229d3a0((UnkStruct_0229e544 *) s, (unsigned char) s->unk_B8) != 0 ||
                func_ov106_0229d390((UnkStruct_0229e544 *) s, (unsigned char) s->unk_B8) != 0) {
                if (func_ov106_0229d090((UnkStruct_0229e544 *) s, (unsigned char) s->unk_B8) == 0) {
                    func_ov106_0229c798((const unsigned char *) s, s->unk_B8, 0);
                }
            } else if (func_ov106_0229d384(s, s->unk_B8) != 0) {
                func_ov106_0229ca1c(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov106_0229d390((UnkStruct_0229e544 *) s, (unsigned char) s->unk_B8) != 0) {
                if (func_ov106_0229d090((UnkStruct_0229e544 *) s, (unsigned char) s->unk_B8) == 0) {
                    r = func_ov106_0229d48c(s);
                    if (r != 0x20) {
                        func_ov106_0229d4ac(s, s->unk_B8, r);
                        func_ov002_02207d24((char *) s + 0x21B8, 1);
                    }
                }
            }
            return;
        }
    }
    val = (*(struct {
              char pad2[2];
              unsigned short field;
          } *) data_021fbe40)
              .field;
    if ((val & 8) || (val & 2)) {
        func_ov106_0229cc50(s);
        func_ov106_0229c378((UnkStruct_0229e544 *) s);
        func_ov002_02207d24((char *) s + 0x21B8, 0);
        return;
    }
    func_ov002_02207d00((char *) s + 0x21B8);
}

void func_ov106_0229e1d8(void *self)
{
    if (func_0206f56c() != 0) {
        func_ov106_0229cd60((UnkStruct_0229e544 *) self, (unsigned char) (((unsigned char *) self)[0xB7]));
        func_ov106_0229cc50((UnkStruct_0229e2dc *) self);
        func_ov106_0229c378((UnkStruct_0229e544 *) self);
        func_ov002_02207d24((char *) self + 0x21B8, 0);
        return;
    } else {
        if (func_ov106_0229c4a0((UnkStruct_0229e2dc *) self, func_ov002_02208008((UnkStruct_0229e2dc *) self), 1) != 0) {
            func_ov106_0229cea8((UnkStruct_0229e2dc *) self);
            func_ov106_0229cbdc((UnkStruct_0229e2dc *) self);
            func_ov002_02207d24((char *) self + 0x21B8, 0);
            return;
        } else {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                if (func_ov106_0229d3a0((UnkStruct_0229e544 *) self, (unsigned char) (((unsigned char *) self)[0xB8])) != 0) {
                    if (func_ov106_0229d390((UnkStruct_0229e544 *) self, (unsigned char) (((unsigned char *) self)[0xB7])) !=
                        0) {
                        if (func_ov106_0229d090((UnkStruct_0229e544 *) self,
                                                (unsigned char) (((unsigned char *) self)[0xB8])) == 0) {
                            return;
                        }
                    }
                }
                if (func_ov106_0229d0d0((UnkStruct_0229e544 *) self, (unsigned char) (((unsigned char *) self)[0xB8])) != 0) {
                    return;
                }
                if (func_ov106_0229d090((UnkStruct_0229e544 *) self, (unsigned char) (((unsigned char *) self)[0xB8])) != 0) {
                    func_ov106_0229c9a0(self, ((unsigned char *) self)[0xB8]);
                    return;
                } else {
                    func_ov106_0229c958(self, ((unsigned char *) self)[0xB8]);
                    return;
                }
            } else {
                if (flags & 2) {
                    func_ov106_0229c9a0(self, ((unsigned char *) self)[0xB7]);
                    return;
                } else {
                    func_ov106_0229ce0c(self);
                    func_ov002_02207d00((char *) self + 0x21B8);
                }
            }
        }
    }
}

void func_ov106_0229e134(char *self)
{
    if (func_0206f56c() != 0) {
        func_ov106_0229c418((void *) self);
        return;
    }
    if (func_0208e4bc(self + 0x22a0) == 0) {
        int v1, v2;
        v1 = func_ov002_0220b5ec(self + 0x2b3c, 1);
        v2 = func_ov002_0220b59c(self + 0x2b3c, 1);
        func_ov002_0220a0b4(self + 0x22a0, v1, v2);
        func_ov002_0220a374(self + 0x22a0, 1);
    }
    if (func_ov002_02208014(self) != 0) {
        func_ov106_0229cc50((UnkStruct_0229e2dc *) self);
        func_ov002_02208098((void *) (self), 5);
        return;
    } else {
        unsigned short flags;
        flags = (*(struct GlobalFlags *) data_021fbe40).flags;
        if ((flags & 1) != 0 || (flags & 2) != 0) {
            func_ov002_0220a1dc(self + 0x22a0);
            func_ov002_02208098((void *) (self), 10);
        }
    }
}

void func_ov106_0229e114(void *arg)
{
    if (func_0208e484((char *) arg + 0x22a0) != 0) {
        func_ov106_0229c458(arg);
    }
}

void func_ov106_0229e078(char *self)
{
    int a;
    unsigned char b;

    if (func_0206f56c() != 0) {
        func_ov106_0229c868(self);
        return;
    }
    if (func_ov002_02208014(self) != 0) {
        func_ov106_0229c868(self);
        return;
    }
    a = func_ov002_02208008((UnkStruct_0229e2dc *) self);
    b = (unsigned char) func_ov106_0229c364((void *) self, 0x10000);
    if (func_ov002_02209044(self + 0x2304, a, self + 0xbd, b) != 0) {
        func_ov106_0229cb58(self);
        return;
    }
    if ((*(struct OV106Flags *) data_021fbe40).flags & 1) {
        func_ov002_0220a1dc((char *) (self + 0x22a0));
        func_ov002_02208098((void *) (self), 0xc);
        return;
    }
    if ((*(struct OV106Flags *) data_021fbe40).flags & 2) {
        func_ov106_0229caf4(self);
        return;
    }
}

void func_ov106_0229e014(UnkStruct_0229e014 *self)
{
    if (func_0208e484(&self->unk_22A0) == 0) {
        return;
    }
    self->unk_BC = self->unk_26F1[self->unk_BD];
    {
        int flag = 1;
        if (self->unk_BC == 2) {
            flag = 0;
            func_0200467c(0x24);
        }
        func_ov002_02209114((const char *) (&self->unk_2304), self->unk_BD, flag);
    }
    func_ov002_02208098((void *) (self), 0x17);
}
