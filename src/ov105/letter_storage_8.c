/* letter_storage_8: 11 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229e804 @ 0x0229e804, 0x5c bytes, Thumb
 * func_ov105_0229e7bc @ 0x0229e7bc, 0x48 bytes, Thumb
 * func_ov105_0229e728 @ 0x0229e728, 0x94 bytes, Thumb
 * func_ov105_0229e6f4 @ 0x0229e6f4, 0x34 bytes, Thumb
 * func_ov105_0229e638 @ 0x0229e638, 0xbc bytes, Thumb
 * func_ov105_0229e4a8 @ 0x0229e4a8, 0x190 bytes, Thumb
 * func_ov105_0229e374 @ 0x0229e374, 0x134 bytes, Thumb
 * func_ov105_0229e2e0 @ 0x0229e2e0, 0x94 bytes, Thumb
 * func_ov105_0229e2c0 @ 0x0229e2c0, 0x20 bytes, Thumb
 * func_ov105_0229e230 @ 0x0229e230, 0x90 bytes, Thumb
 * func_ov105_0229e1cc @ 0x0229e1cc, 0x64 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x2b5];
    unsigned char byte_at_2b5;
    unsigned char pad_2B6[0x0d];
    unsigned char byte_at_2c3;
    unsigned char pad_2C4[0x20f8];
    unsigned char arr[1];
} UnkStruct_0229e7bc;

typedef struct {
    char pad_00[0x2BA];
    unsigned char unk_2BA;
    char pad_2BB[0x23BC - 0x2BA - 1];
    void *unk_23BC;
} UnkStruct_0229e4a8;

typedef struct {
    char pad_00[0x2B7];
    unsigned char unk_2B7;
    unsigned char unk_2B8;
    char pad_2B9[1];
    unsigned char unk_2BA;
    char pad_2BB[5];
    unsigned char unk_2C0;
    char pad_2C1[0x23BC - 0x2C0 - 1];
    void *unk_23BC;
    char pad2[0x24A4 - 0x23BC - 4];
    char unk_24A4;
} UnkStruct_0229e374;

typedef struct Sub24A4 {
    int pad_00;
} Sub24A4;

typedef struct Sub2D40 {
    int pad_00;
} Sub2D40;

typedef struct UnkStruct_0229e2e0 {
    char pad_00[0x24a4];
    Sub24A4 sub24A4;
    char pad_24A8[0x898];
    Sub2D40 sub2D40;
} UnkStruct_0229e2e0;

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov105_0229c340(void *self, int arg);
extern int func_ov105_0229d310(void *receiver);
extern void func_ov105_0229d970(void *self, unsigned char arg);
extern void func_ov002_022096d8(char *ptr, int arg);
extern int func_ov002_02207cc0(int);
extern void func_ov105_0229cadc(void *p, int i, int j);
extern void func_ov105_0229d1c4(unsigned char *);
extern void func_ov105_0229d390(unsigned char *);
extern int func_ov105_0229d69c(unsigned char *, int, int, int);
extern int func_ov105_0229d468(unsigned char *, int);
extern int func_ov105_0229d650(unsigned char *, int);
extern void func_ov105_0229d82c(unsigned char *, unsigned char, int);
extern void func_ov105_0229d354(unsigned char *, int);
extern void func_ov105_0229db14(unsigned char *);
extern void func_ov094_022999d8(void);
extern int func_ov002_02208054(char *p, int n);
extern int func_ov002_0220b498(void *);
extern void func_ov105_0229c710(char *p);
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208e28(void *);
extern int func_ov002_02208b00(void *, int, int);
extern void func_ov002_02209114(void *, int, int);
extern void func_ov105_0229cbb0(void *);
extern void func_0200467c(int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229c758(UnkStruct_0229e4a8 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov105_0229db70(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229d230(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229cf48(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229d76c(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d75c(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d428(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d750(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d73c(UnkStruct_0229e4a8 *s, unsigned char b);
extern void func_ov105_0229cd7c(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229d78c(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229d7d4(void *receiver);
extern void func_ov105_0229d7f4(UnkStruct_0229e4a8 *s, unsigned char b, int v);
extern void func_ov105_0229c330(UnkStruct_0229e4a8 *s, int v);
extern void func_ov105_0229cfc0(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229c668(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229c354(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229ccf4(UnkStruct_0229e374 *s, unsigned char b);
extern void func_ov105_0229cca8(UnkStruct_0229e374 *s, unsigned char b);
extern void func_ov105_0229d870(UnkStruct_0229e374 *s, unsigned char b, int v);
extern int func_0208e4bc(void *p);
extern void func_ov105_0229d17c(UnkStruct_0229e374 *s);
extern int func_ov002_0220b5ec(void *p, int flag);
extern int func_ov002_0220b59c(void *p, int flag);
extern void func_ov002_0220a0b4(void *p, int v1, int v2);
extern void func_ov002_0220a374(void *p, int flag);
extern void func_ov002_0220a1dc(void *p);
extern unsigned short data_021fbe40[2];
extern int func_0208e484(void *ptr);
extern int func_ov002_02209044(unsigned char *a, int b, unsigned char *c, unsigned char d);
extern void func_ov105_0229cebc(unsigned char *self);
extern void func_ov105_0229ce54(unsigned char *self);

void func_ov105_0229e804(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 6);
        return;
    }
    if (func_ov105_0229c340(self, 4) != 0) {
        if (func_ov105_0229d310(self) != 0) {
            func_ov105_0229d970(self, ((unsigned char *) self)[0x2b5]);
            func_ov002_022096d8((char *) self + 0x2508, 0);
            func_ov002_02207d24((void *) ((char *) self + 0x23bc), 1);
        }
    }
}

void func_ov105_0229e7bc(UnkStruct_0229e7bc *self)
{
    if (func_ov002_02207cc0((int) self->arr)) {
        if (self->byte_at_2c3 != 0) {
            self->byte_at_2c3--;
        } else {
            func_ov105_0229cadc(self, self->byte_at_2b5, 1);
            func_ov002_02208098(self, 2);
        }
    }
}

void func_ov105_0229e728(unsigned char *self)
{
    unsigned int r4;
    int x;
    int y;

    func_ov105_0229d1c4(self);
    func_ov105_0229d390(self);
    r4 = *(unsigned int *) (self + 0xac) + 8;
    x = func_ov105_0229d69c(self, r4, *(unsigned int *) (self + 0xb0) + 0x18, 0);

    if (x == 0x40) {
        goto x_eq_0x40;
    }

    if (data_021fbdd8 != 0) {
        goto flag_nonzero;
    }

    if (func_ov105_0229d468(self, x) != 0) {
        goto call_d82c;
    }

    y = func_ov105_0229d650(self, x);
    if (y != 0) {
        goto ext_block;
    }

call_d82c:
    func_ov105_0229d82c(self, self[0x2b7], r4);
    return;

ext_block:
    func_ov094_022999d8();
    func_ov105_0229db14(self);
    return;

flag_nonzero:
    func_ov105_0229d354(self, x);
    return;

x_eq_0x40:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov105_0229d82c(self, self[0x2b7], r4);
    return;
}

void func_ov105_0229e6f4(char *param0)
{
    if (func_ov002_02208054(param0, 1) != 0) {
        func_ov002_02208098((void *) param0, 9);
    } else {
        if (func_ov002_0220b498((void *) (param0 + 0x2d40)) != 0) {
            func_ov105_0229c710(param0);
        }
    }
}

void func_ov105_0229e638(unsigned char *self)
{
    int r;
    unsigned int ok;
    unsigned int flag;
    unsigned char *p;

    if (func_ov002_02208e28(self + 0x2508) == 0) {
        return;
    }

    if (func_ov002_02208054((char *) self, 1) != 0) {
        func_ov105_0229cbb0(self);
        return;
    }

    ok = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (ok != 0) {
        r = func_ov002_02208b00(self + 0x2508, data_021f6c58, data_021f6c54);
        if (r >= 0) {
            if (func_ov105_0229c340(self, 0x800) != 0 && r == 0) {
                return;
            }

            p = self + r;
            self[0x2be] = p[0x28f5];

            flag = 1;
            if (self[0x2be] == 2) {
                flag = 0;
                func_0200467c(0x24);
            }

            func_ov002_02209114(self + 0x2508, r, flag);
            func_ov002_02208098(self, 0x17);
        }
    }
}

void func_ov105_0229e4a8(UnkStruct_0229e4a8 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov105_0229db70(s);
        func_ov002_02207d24((char *) s + 0x23BC, 1);
        return;
    }
    if (func_ov105_0229c758(s, func_ov002_02208008(s), 0) != 0) {
        func_ov105_0229d230(s);
        func_ov105_0229cf48(s);
        func_ov002_02207d24((char *) s + 0x23BC, 0);
        return;
    }
    if (func_ov105_0229d468((unsigned char *) s, (unsigned char) s->unk_2BA) == 0) {
        val = (*(struct {
                  char pad2[2];
                  unsigned short field;
              } *) data_021fbe40)
                  .field;
        if (val & 1) {
            if (func_ov105_0229d76c(s, s->unk_2BA) != 0 || func_ov105_0229d75c(s, s->unk_2BA) != 0) {
                if (func_ov105_0229d428(s, s->unk_2BA) == 0) {
                    func_ov105_0229cadc((void *) s, (unsigned char) s->unk_2BA, 0);
                }
            } else if (func_ov105_0229d750(s, s->unk_2BA) != 0 || func_ov105_0229d73c(s, s->unk_2BA) != 0) {
                func_ov105_0229cd7c(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov105_0229d76c(s, s->unk_2BA) != 0 || func_ov105_0229d75c(s, s->unk_2BA) != 0) {
                if (func_ov105_0229d428(s, s->unk_2BA) == 0) {
                    if (func_ov105_0229d76c(s, s->unk_2BA) != 0) {
                        r = func_ov105_0229d78c(s);
                    } else {
                        r = func_ov105_0229d7d4(s);
                    }
                    if (r != 0x40) {
                        func_ov105_0229d7f4(s, s->unk_2BA, r);
                        func_ov002_02207d24((char *) s + 0x23BC, 1);
                        func_ov105_0229c330(s, 0x1000);
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
        func_ov105_0229cfc0(s);
        func_ov105_0229c668(s);
        func_ov002_02207d24((char *) s + 0x23BC, 0);
        return;
    }
    if (func_ov105_0229c354(s) == 0) {
        func_ov002_02207d00((char *) s + 0x23BC);
    }
}

void func_ov105_0229e374(UnkStruct_0229e374 *s)
{
    unsigned short val;
    if (func_ov105_0229c758((UnkStruct_0229e4a8 *) s, func_ov002_02208008((UnkStruct_0229e4a8 *) s), 1) != 0) {
        func_ov105_0229d230((UnkStruct_0229e4a8 *) s);
        func_ov105_0229cf48((UnkStruct_0229e4a8 *) s);
        func_ov002_02207d24((char *) s + 0x23BC, 0);
        return;
    }
    val = (*(struct {
              char pad2[2];
              unsigned short field;
          } *) data_021fbe40)
              .field;
    if (val & 1) {
        if (func_ov105_0229d76c((UnkStruct_0229e4a8 *) s, s->unk_2BA) != 0 ||
            func_ov105_0229d75c((UnkStruct_0229e4a8 *) s, s->unk_2BA) != 0) {
            if (func_ov105_0229d468((unsigned char *) s, (unsigned char) s->unk_2BA) == 0) {
                if (func_ov105_0229d428((UnkStruct_0229e4a8 *) s, s->unk_2BA) != 0) {
                    func_ov105_0229ccf4(s, s->unk_2BA);
                } else {
                    func_ov105_0229cca8(s, s->unk_2BA);
                }
            }
        } else if (func_ov105_0229d73c((UnkStruct_0229e4a8 *) s, s->unk_2BA) != 0) {
            func_ov105_0229cd7c((UnkStruct_0229e4a8 *) s);
        }
        return;
    }
    if (val & 2) {
        if (func_ov105_0229d75c((UnkStruct_0229e4a8 *) s, s->unk_2B7) != 0) {
            if (s->unk_2B8 != s->unk_2C0) {
                func_ov105_0229d870(s, (unsigned char) (s->unk_2B8 + 0x3e), 4);
                return;
            }
        }
        if (func_0208e4bc((char *) s + 0x24A4) == 1) {
            func_ov105_0229d870(s, s->unk_2B7, 4);
        } else {
            func_ov105_0229ccf4(s, s->unk_2B7);
        }
        return;
    }
    if (func_ov105_0229c354((UnkStruct_0229e4a8 *) s) == 0) {
        func_ov105_0229d17c(s);
        func_ov002_02207d00((char *) s + 0x23BC);
    }
}

void func_ov105_0229e2e0(UnkStruct_0229e2e0 *self)
{
    int v1;
    int v2;

    if (func_0208e4bc(&self->sub24A4) == 0) {
        v1 = func_ov002_0220b5ec(&self->sub2D40, 1);
        v2 = func_ov002_0220b59c(&self->sub2D40, 1);
        func_ov002_0220a0b4(&self->sub24A4, v1, v2);
        func_ov002_0220a374(&self->sub24A4, 1);
    }
    if (func_ov002_02208014(self) != 0) {
        func_ov105_0229cfc0((UnkStruct_0229e4a8 *) self);
        func_ov002_02208098(self, 5);
    } else {
        if ((data_021fbe40[1] & 1) || (data_021fbe40[1] & 2)) {
            func_ov002_0220a1dc(&self->sub24A4);
            func_ov002_02208098(self, 10);
        }
    }
}

void func_ov105_0229e2c0(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x24a4)) {
        func_ov105_0229c710((char *) ptr);
    }
}

void func_ov105_0229e230(unsigned char *self)
{
    int r4;
    unsigned char d;
    if (func_ov002_02208014(self) != 0) {
        func_ov105_0229cbb0((void *) self);
        return;
    }
    r4 = func_ov002_02208008((UnkStruct_0229e4a8 *) self);
    d = (unsigned char) func_ov105_0229c340((void *) self, 0x800);
    if (func_ov002_02209044(self + 0x2508, r4, self + 0x2bf, d) != 0) {
        func_ov105_0229cebc(self);
        return;
    }
    if (data_021fbe40[1] & 1) {
        func_ov002_0220a1dc((void *) (self + 0x24a4));
        func_ov002_02208098((void *) self, 0xc);
    } else if (data_021fbe40[1] & 2) {
        func_ov105_0229ce54(self);
    }
}

void func_ov105_0229e1cc(void *base)
{
    int flag;

    if (func_0208e484((char *) base + 0x24A4) == 0) {
        return;
    }

    *((unsigned char *) ((char *) base + 0x2BE)) =
        *((unsigned char *) ((char *) base + *((unsigned char *) ((char *) base + 0x2BF)) + 0x28F5));
    flag = 1;
    if (*((unsigned char *) ((char *) base + 0x2BE)) == 2) {
        flag = 0;
        func_0200467c(0x24);
    }
    func_ov002_02209114((char *) base + 0x2508, (unsigned char) (*((unsigned char *) ((char *) base + 0x2BF))), flag);
    func_ov002_02208098(base, 0x17);
}
