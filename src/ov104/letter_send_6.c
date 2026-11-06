/* letter_send_6: 11 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229e75c @ 0x0229e75c, 0x5c bytes, Thumb
 * func_ov104_0229e714 @ 0x0229e714, 0x48 bytes, Thumb
 * func_ov104_0229e63c @ 0x0229e63c, 0xd8 bytes, Thumb
 * func_ov104_0229e608 @ 0x0229e608, 0x34 bytes, Thumb
 * func_ov104_0229e54c @ 0x0229e54c, 0xbc bytes, Thumb
 * func_ov104_0229e3b8 @ 0x0229e3b8, 0x194 bytes, Thumb
 * func_ov104_0229e314 @ 0x0229e314, 0xa4 bytes, Thumb
 * func_ov104_0229e280 @ 0x0229e280, 0x94 bytes, Thumb
 * func_ov104_0229e260 @ 0x0229e260, 0x20 bytes, Thumb
 * func_ov104_0229e1d4 @ 0x0229e1d4, 0x8c bytes, Thumb
 * func_ov104_0229e170 @ 0x0229e170, 0x64 bytes, Thumb
 */

struct UnkStruct_0229e714 {
    char pad_00[0xb5];
    unsigned char b5;
    char pad_B6[0x09];
    unsigned char bf;
};

typedef struct UnkStruct_0229e63c {
    char pad_00[0xa8];
    char *unk_A8;
    char *unk_AC;
    char pad_B0[0xb7 - 0xb0];
    unsigned char unk_B7;
} UnkStruct_0229e63c;

typedef struct {
    char pad_00[0xB8];
    unsigned char unk_B8;
    char pad_B9[0x23B8 - 0xB8 - 1];
    void *unk_23B8;
} UnkStruct_0229e3b8;

typedef struct UnkStruct_0229e314 {
    unsigned char pad_00[0xb7];
    unsigned char b7;
    unsigned char b8;
    unsigned char pad_B9[0x23b8 - 0xb9];
    unsigned char sub;
} UnkStruct_0229e314;

typedef struct {
    unsigned char pad_00[2];
    unsigned short flags;
} GF;

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov104_0229c364(void *, int);
extern int func_ov104_0229d6a4(void *receiver);
extern void func_ov104_0229dc20(void *, unsigned char);
extern void func_ov002_022096d8(void *, int);
extern int func_ov002_02207d24(void *, int);
extern int func_ov002_02207cc0(int object);
extern void func_ov104_0229cf14(struct UnkStruct_0229e714 *self, unsigned char val, int flag);
extern void func_ov104_0229d554(void *);
extern void func_ov104_0229d724(void *);
extern int func_ov104_0229d9bc(void *, void *, void *, int);
extern int func_ov104_0229da80(void *, int);
extern int func_ov104_0229da70(void *, int);
extern int func_ov104_0229d7bc(void *, int);
extern int func_ov104_0229d7fc(void *, int);
extern int func_ov104_0229d974(void *, int);
extern int func_ov104_0229db30(void *, int, void *);
extern void func_ov104_0229d6e8(void *, int);
extern void func_ov104_0229dd00(void *);
extern void func_ov094_022999d8(void);
extern int func_ov002_02208054(void *p, int flag);
extern int func_ov002_0220b498(void *object);
extern void func_ov104_0229cbe8(void *p);
extern int func_ov002_02208e28(unsigned char *);
extern void func_ov104_0229cfe4(unsigned char *);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern void func_ov002_02209114(unsigned char *, int, int);
extern void func_0200467c(unsigned int);
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern unsigned char data_021fbddc;
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229cc30(UnkStruct_0229e3b8 *s, int a, int b);
extern void func_ov002_02207d00(void *p);
extern void func_ov104_0229dd54(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229d5c0(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229d304(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229da5c(UnkStruct_0229e3b8 *s, unsigned char b);
extern void func_ov104_0229d178(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229daa0(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229dad8(void *receiver);
extern void func_ov104_0229daf8(UnkStruct_0229e3b8 *s, unsigned char b, int v);
extern void func_ov104_0229d378(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229c9fc(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229ca44(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229d11c(void *self, unsigned char b);
extern void func_ov104_0229d0d4(void *self, unsigned char b);
extern void func_ov104_0229d528(void *self);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220b5ec(unsigned char *, int);
extern int func_ov002_0220b59c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern void func_ov002_0220a1dc(unsigned char *);
extern unsigned short data_021fbe40[2];
extern int func_0208e484(void *);
extern int func_ov002_02209044(char *p1, int p2, char *p3, unsigned char p4);
extern void func_ov104_0229d2b4(char *param);
extern void func_ov104_0229d250(char *param);

void func_ov104_0229e75c(void *arg)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (arg), 6);
        return;
    }
    if (func_ov104_0229c364(arg, 4) == 0) {
        return;
    }
    if (func_ov104_0229d6a4(arg) == 0) {
        return;
    }
    func_ov104_0229dc20(arg, *(unsigned char *) ((char *) arg + 0xb5));
    func_ov002_022096d8((char *) arg + 0x2504, 0);
    func_ov002_02207d24((char *) arg + 0x23b8, 1);
}

void func_ov104_0229e714(struct UnkStruct_0229e714 *self)
{
    if (func_ov002_02207cc0((int) ((char *) self + 0x23b8)) == 0) {
        return;
    }
    if (self->bf != 0) {
        self->bf--;
    } else {
        func_ov104_0229cf14(self, self->b5, 1);
        func_ov002_02208098((void *) (self), 2);
    }
}

void func_ov104_0229e63c(void *obj)
{
    UnkStruct_0229e63c *o;
    char *p1;
    int ret;

    func_ov104_0229d554(obj);
    func_ov104_0229d724(obj);
    o = (UnkStruct_0229e63c *) obj;
    p1 = o->unk_A8 + 8;
    ret = func_ov104_0229d9bc(obj, p1, o->unk_AC + 0x18, 0);

    if (func_ov104_0229da80(obj, ret) != 0) {
        if (func_ov104_0229da70(obj, o->unk_B7) != 0) {
            goto L69e;
        }
    }
L682:
    if (func_ov104_0229da70(obj, ret) == 0) {
        goto L6ac;
    }
    if (func_ov104_0229da80(obj, o->unk_B7) == 0) {
        goto L6ac;
    }
L69e:
    if (func_ov104_0229d7bc(obj, ret) != 0) {
        goto L6ac;
    }
    ret = 0x21;
L6ac:
    if (ret == 0x21) {
        goto L6f4;
    }
    if (data_021fbdd8 != 0) {
        goto L6ea;
    }
    if (func_ov104_0229d7fc(obj, ret) != 0) {
        goto L6d0;
    }
    if (func_ov104_0229d974(obj, ret) != 0) {
        goto L6de;
    }
L6d0:
    func_ov104_0229db30(obj, o->unk_B7, p1);
    goto exit;
L6de:
    func_ov094_022999d8();
    func_ov104_0229dd00(obj);
    goto exit;
L6ea:
    func_ov104_0229d6e8(obj, ret);
    goto exit;
L6f4:
    if (data_021fbdd8 != 0) {
        goto exit;
    }
    func_ov104_0229db30(obj, o->unk_B7, p1);
exit:
    return;
}

void func_ov104_0229e608(void *param)
{
    if (func_ov002_02208054(param, 1)) {
        func_ov002_02208098((void *) (param), 9);
    } else {
        if (func_ov002_0220b498((void *) ((char *) param + 0x2d3c))) {
            func_ov104_0229cbe8(param);
        }
    }
}

void func_ov104_0229e54c(unsigned char *p)
{
    int r;
    int do_x;
    unsigned int flag;
    unsigned char *q;

    if (func_ov002_02208e28(p + 0x2504) == 0) {
        return;
    }
    if (func_ov002_02208054((void *) p, 1) != 0) {
        func_ov104_0229cfe4(p);
        return;
    }
    flag = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (flag == 0) {
        return;
    }
    r = func_ov002_02208b00(p + 0x2504, data_021f6c58, data_021f6c54);
    if (r < 0) {
        return;
    }
    if (func_ov104_0229c364((void *) p, 0x8000) != 0 && r == 0) {
        return;
    }
    q = p + r;
    p[0xbc] = q[0x28f1];
    do_x = 1;
    if (p[0xbc] == 2) {
        do_x = 0;
        func_0200467c(0x24);
    }
    func_ov002_02209114(p + 0x2504, r, do_x);
    func_ov002_02208098((void *) (p), 0x17);
}

void func_ov104_0229e3b8(UnkStruct_0229e3b8 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov104_0229dd54(s);
        func_ov002_02207d24((char *) s + 0x23B8, 1);
        return;
    }
    if (func_ov104_0229cc30(s, func_ov002_02208008(s), 0) != 0) {
        func_ov104_0229d5c0(s);
        func_ov104_0229d304(s);
        func_ov002_02207d24((char *) s + 0x23B8, 0);
        return;
    }
    if (func_ov104_0229d7fc((void *) s, (unsigned char) s->unk_B8) == 0) {
        val = (*(struct {
                  char pad2[2];
                  unsigned short field;
              } *) data_021fbe40)
                  .field;
        if (val & 1) {
            if (func_ov104_0229da80((void *) s, (unsigned char) s->unk_B8) != 0 ||
                func_ov104_0229da70((void *) s, (unsigned char) s->unk_B8) != 0) {
                if (func_ov104_0229d7bc((void *) s, (unsigned char) s->unk_B8) == 0) {
                    func_ov104_0229cf14((struct UnkStruct_0229e714 *) s, s->unk_B8, 0);
                }
            } else if (func_ov104_0229da5c(s, s->unk_B8) != 0) {
                func_ov104_0229d178(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov104_0229da80((void *) s, (unsigned char) s->unk_B8) != 0 ||
                func_ov104_0229da70((void *) s, (unsigned char) s->unk_B8) != 0) {
                if (func_ov104_0229d7bc((void *) s, (unsigned char) s->unk_B8) == 0) {
                    if (func_ov104_0229da80((void *) s, (unsigned char) s->unk_B8) != 0) {
                        r = func_ov104_0229daa0(s);
                    } else {
                        r = func_ov104_0229dad8(s);
                    }
                    if (r != 0x21) {
                        func_ov104_0229daf8(s, s->unk_B8, r);
                        func_ov002_02207d24((char *) s + 0x23B8, 1);
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
    if (val & 2) {
        func_ov104_0229d378(s);
        func_ov104_0229c9fc(s);
        func_ov002_02207d24((char *) s + 0x23B8, 0);
        return;
    }
    if (val & 8) {
        func_ov104_0229d378(s);
        func_ov104_0229ca44(s);
        func_ov002_02207d24((char *) s + 0x23B8, 0);
        return;
    }
    func_ov002_02207d00((char *) s + 0x23B8);
}

void func_ov104_0229e314(UnkStruct_0229e314 *self)
{
    int res;
    unsigned short flags;

    res = func_ov002_02208008((UnkStruct_0229e3b8 *) self);
    if (func_ov104_0229cc30((UnkStruct_0229e3b8 *) self, res, 1)) {
        func_ov104_0229d5c0((UnkStruct_0229e3b8 *) self);
        func_ov104_0229d304((UnkStruct_0229e3b8 *) self);
        func_ov002_02207d24((char *) self + 0x23b8, 0);
    } else {
        flags = (*(GF *) data_021fbe40).flags;
        if (flags & 1) {
            if (func_ov104_0229d7fc(self, (unsigned char) self->b8)) {
                return;
            }
            if (func_ov104_0229d7bc(self, (unsigned char) self->b8)) {
                func_ov104_0229d11c(self, self->b8);
            } else {
                func_ov104_0229d0d4(self, self->b8);
            }
        } else {
            if (flags & 2) {
                func_ov104_0229d11c(self, self->b7);
            } else {
                func_ov104_0229d528(self);
                func_ov002_02207d00((char *) self + 0x23b8);
            }
        }
    }
}

void func_ov104_0229e280(unsigned char *p)
{
    int a;
    int b;

    if (func_0208e4bc(p + 0x24a0) == 0) {
        a = func_ov002_0220b5ec(p + 0x2d3c, 1);
        b = func_ov002_0220b59c(p + 0x2d3c, 1);
        func_ov002_0220a0b4(p + 0x24a0, a, b);
        func_ov002_0220a374(p + 0x24a0, 1);
    }

    if (func_ov002_02208014(p) != 0) {
        func_ov104_0229d378((UnkStruct_0229e3b8 *) p);
        func_ov002_02208098((void *) (p), 5);
    } else {
        if ((data_021fbe40[1] & 1) || (data_021fbe40[1] & 2)) {
            func_ov002_0220a1dc(p + 0x24a0);
            func_ov002_02208098((void *) (p), 10);
        }
    }
}

void func_ov104_0229e260(void *self)
{
    if (func_0208e484((char *) self + 0x24a0)) {
        func_ov104_0229cbe8(self);
    }
}

void func_ov104_0229e1d4(char *param)
{
    int ret;

    if (func_ov002_02208014(param) != 0) {
        func_ov104_0229cfe4((unsigned char *) param);
        return;
    }

    ret = func_ov002_02208008((UnkStruct_0229e3b8 *) param);
    {
        unsigned char b = (unsigned char) func_ov104_0229c364((void *) param, 0x8000);
        if (func_ov002_02209044(param + 0x2504, ret, param + 0xbd, b) != 0) {
            func_ov104_0229d2b4(param);
        } else {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                func_ov002_0220a1dc((unsigned char *) (param + 0x24a0));
                func_ov002_02208098((void *) (param), 0xc);
            } else if (flags & 2) {
                func_ov104_0229d250(param);
            }
        }
    }
}

void func_ov104_0229e170(void *p)
{
    if (func_0208e484((void *) ((char *) p + 0x24a0)) != 0) {
        int flag;
        *(unsigned char *) ((char *) p + 0xbc) =
            *(unsigned char *) ((char *) p + (*(unsigned char *) ((char *) p + 0xbd)) + 0x28f1);
        flag = 1;
        if (*(unsigned char *) ((char *) p + 0xbc) == 2) {
            flag = 0;
            func_0200467c(0x24);
        }
        func_ov002_02209114((unsigned char *) ((char *) p + 0x2504), (unsigned char) (*(unsigned char *) ((char *) p + 0xbd)),
                            flag);
        func_ov002_02208098((void *) (p), 0x17);
    }
}
