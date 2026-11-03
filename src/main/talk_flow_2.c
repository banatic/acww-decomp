/* talk_flow_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02066f2c @ 0x02066f2c, 0x60 bytes, Thumb
 * func_02066f20 @ 0x02066f20, 0xc bytes, Thumb
 * func_02066dc4 @ 0x02066dc4, 0x15c bytes, Thumb
 * func_02066db0 @ 0x02066db0, 0x14 bytes, Thumb
 * func_02066cd4 @ 0x02066cd4, 0xdc bytes, Thumb
 */

struct UnkStruct_02066f2c {
    char pad_00[0x8];
    int unk_08;
    int unk_0C;
    char pad_10[0xC];
    char unk_1C;
    char pad_1D[0x7F];
    int unk_9C;
    char pad_A0[0x198C];
    char unk_1A2C;
    char pad_1A2D[0x46B];
    unsigned char unk_1E98;
};

typedef struct {
    char pad_00[0x8];
    int unk_08;
    int unk_0C;
    char pad_10[0x684 - 0x10];
    char unk_684[4];
    char pad_688[0x13b8 - 0x688];
    char unk_13B8[4];
    char pad_13BC[0x13e8 - 0x13bc];
    int unk_13E8;
    char pad_13EC[0x149c - 0x13ec];
    char unk_149C[4];
    char pad_14A0[0x1a2c - 0x14a0];
    char unk_1A2C[4];
    char pad_1A30[0x1e98 - 0x1a30];
    unsigned char unk_1E98;
} UnkStruct_02066cd4;

extern short data_020def1c[];
extern void func_02068d74(void *ptr, int val);
extern void func_020689b4(void *ptr);
extern int func_020a94d8(void *arg);
extern int func_020a9cf8(void *arg);
extern int func_020a9d14(void *arg);
extern void func_020671b0(void *arg);
extern int func_02068cbc(void *arg);
extern int func_02068c9c(void *arg);
extern void func_02068d2c(void *arg);
extern int func_02067dbc(void *arg);
extern int func_020676ac(void *arg);
extern void func_02068d20(void *arg);
extern int func_02068c6c(void *arg);
extern void func_02068d14(void *arg);
extern int func_02068c3c(void *arg);
extern void func_02066abc(void *arg);
extern void func_02068d38(void *arg);
extern void func_0200467c(int cmd);
extern int func_02067d7c(void *);
extern void func_0206bd2c(void *);
extern void func_02068ae4(void *, int);
extern void func_0206c05c(void *);
extern void func_02068a04(void *);
extern void func_02067540(void *);
extern void func_020680d0(void *);

void func_02066f2c(struct UnkStruct_02066f2c *self)
{
    int flag = 0;
    if (self->unk_0C > 0) {
        self->unk_0C--;
    } else {
        flag = 1;
    }
    self->unk_9C = data_020def1c[self->unk_0C];
    func_02068d74(&self->unk_1C, self->unk_9C);
    if (flag) {
        if (self->unk_1E98 == 0) {
            func_020689b4(&self->unk_1A2C);
        }
        self->unk_08 = 3;
    }
}

void func_02066f20(char *p)
{
    func_02068d38((void *) (p + 0x1c));
}

void func_02066dc4(unsigned char *s)
{
    int f;
    int flag2, flag3, flag4, flag5;

    func_020a94d8(s + 0x149c);

    f = *(int *) (s + 0x13e8);
    if (f == 2) {
        flag2 = 1;
    } else {
        flag2 = 0;
    }
    if (f == 3) {
        flag3 = 1;
    } else {
        flag3 = 0;
    }
    if (f == 4) {
        flag4 = 1;
    } else {
        flag4 = 0;
    }
    if (f == 5) {
        flag5 = 1;
    } else {
        flag5 = 0;
    }

    if (func_020a9cf8(s + 0xb4) != 0) {
        func_020671b0(s);
    }

    if (flag2 || flag3 || flag4) {
        if (s[0x1e93] == 0 && func_020a9d14(s + 0xb4) != 0) {
            if (s[0x1e92] != 0) {
                func_02066abc(s);
                return;
            } else {
                if (func_02068cbc(s + 0x1c) != 0) {
                    s += 0x1c;
                    func_02068d2c(s);
                    return;
                } else {
                    if (func_02068c9c(s + 0x1c) != 0) {
                        if (func_02067dbc(s) != 0 || func_020676ac(s) != 0) {
                            func_02068d20(s + 0x1c);
                            if (s[0x1e9a] == 0) {
                                func_0200467c(0x10);
                            }
                            if (s[0x18] != 0 || s[0x1490] != 0) {
                                func_0200467c(0x13);
                            }
                            return;
                        } else {
                            return;
                        }
                    } else {
                        if (func_02068c6c(s + 0x1c) != 0) {
                            s += 0x1c;
                            func_02068d14(s);
                            return;
                        } else {
                            if (func_02068c3c(s + 0x1c) != 0) {
                                func_02066abc(s);
                                return;
                            } else {
                                return;
                            }
                        }
                    }
                }
            }
        } else {
            if (func_02068cbc(s + 0x1c) != 0) {
                return;
            } else {
                s += 0x1c;
                func_02068d38(s);
                return;
            }
        }
    } else {
        if (flag5 && func_020a9d14(s + 0xb4) != 0) {
            func_02066abc(s);
        }
    }
}

void func_02066db0(void *arg0)
{
    void *r4 = arg0;
    func_02068d38((char *) arg0 + 0x1c);
    *(unsigned int *) ((char *) r4 + 0xc) = 1;
}

void func_02066cd4(UnkStruct_02066cd4 *p)
{
    int val, b3, b2, b4, b5, b0, bc, r7;

    if (func_02067d7c(p)) {
        func_0206bd2c(&p->unk_13B8);
    }
    func_02068ae4(&p->unk_1A2C, 0);
    func_020a94d8(&p->unk_149C);
    func_0206c05c(&p->unk_684);
    if (p->unk_1E98 == 0) {
        func_02068a04(&p->unk_1A2C);
    }
    val = p->unk_13E8;
    b3 = (val == 3);
    b2 = (val == 2);
    b4 = (val == 4);
    b5 = (val == 5);
    b0 = (val == 0);
    bc = (p->unk_0C == 0);
    r7 = 1;
    if (!bc && !b2 && !b4 && !b5 && !b0) {
        r7 = 0;
    }
    if (b3) {
        p->unk_0C = 0;
    }
    if (r7) {
        if (bc) {
            func_02067540(p);
        }
        p->unk_08 = 2;
        func_020680d0(p);
    }
}
