/* func_020a5c38 @ 0x020a5c38, 0x4cc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a5c38_2;

struct UnkStruct_020a5c38 {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_020a5c38 *data_020ccf94;

extern int func_020a6170(struct UnkStruct_020a5c38_2 *o, int i);
extern void func_020a617c(struct UnkStruct_020a5c38_2 *o, int i, int v);
extern void func_020a6104(struct UnkStruct_020a5c38_2 *o, int i, int v);
extern int func_020a5bb8(struct UnkStruct_020a5c38_2 *o, int i);
extern void func_020a5bc4(struct UnkStruct_020a5c38_2 *o, int i, int v);
extern unsigned long func_020a5bd8(struct UnkStruct_020a5c38_2 *o);
extern void func_020a5be0(struct UnkStruct_020a5c38_2 *o, unsigned long v);
extern unsigned long OSi_GetSystemErrno(struct UnkStruct_020a5c38_2 *o);
extern void OSi_SetSystemErrno(struct UnkStruct_020a5c38_2 *o, unsigned long v);
extern int func_020a5c08(struct UnkStruct_020a5c38_2 *o);
extern void func_020a5c10(struct UnkStruct_020a5c38_2 *o, unsigned long v);
extern void func_020a5c30(struct UnkStruct_020a5c38_2 *o, unsigned long v);

extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *p);
extern void func_020a76cc(unsigned char *p);
extern void func_020a76c8(unsigned char *p);
extern void func_020a76ac(unsigned char *out, int a, int b, int c);
extern int func_02073dd4(struct UnkStruct_020a5c38 *g, int i);
extern int func_02073918(struct UnkStruct_020a5c38 *g, int i);
extern void func_02073820(struct UnkStruct_020a5c38 *g);
extern void func_020737f0(struct UnkStruct_020a5c38 *g, unsigned char *p, int n);
extern void func_02073770(struct UnkStruct_020a5c38 *g, int a, int b);
extern void func_020a6cd4(void *p);
extern void func_020eae40(void);

void func_020a5c38(struct UnkStruct_020a5c38_2 *self)
{
    struct UnkStruct_020a5c38 *g;
    struct UnkStruct_020a5c38 *h;
    unsigned int i;
    int j;
    unsigned int st;
    int st2;
    int ok;
    int ok2;
    int ok3;
    int ok4;
    int ok5;
    int me;
    int zA, zB, zC, zD, zE, zF, zG;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;

    i = 0;
    zA = 0;
    zB = 0;
    zC = 0;
    zD = 0;
    zE = 0;
    zF = 0;
    zG = 0;

    for (; i < 4; i++) {
        st = func_020a6170(self, i);
        if (st > 3) {
            continue;
        }
        ok = 1;
        for (j = 3; j >= 0; j--) {
            switch (func_020a6170(self, j)) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 7:
                    break;
                default:
                    ok = zC;
                    break;
            }
            if (!ok) {
                break;
            }
        }
        if (ok) {
            if (func_020a5c08(self) != 4) {
                ok = zD;
            }
        }
        if (ok) {
            if (func_020b65c4() == 0x2e || func_020b65c4() == 0x2f || func_020b65c4() == 0xd) {
                ok = zE;
            }
        }
        if (ok) {
            if (func_020b5e84((unsigned char *) func_020b5e10()) == 0x2e ||
                func_020b5e84((unsigned char *) func_020b5e10()) == 0x2f ||
                func_020b5e84((unsigned char *) func_020b5e10()) == 0xd) {
                ok = zF;
            }
        }
        if (ok) {
            func_020a5c10(self, zA);
            OSi_SetSystemErrno(self, i);
            if (st == 0) {
                func_020a5be0(self, zB);
            } else if (st == 1) {
                func_020a5be0(self, 1);
            } else if (st == 2) {
                func_020a5be0(self, 2);
            } else {
                func_020a5be0(self, 3);
            }
            func_020a617c(self, i, 4);
        } else {
            func_020a6104(self, i, st == 0 ? 1 : zG);
        }
    }

    if (func_020a5c08(self) == 0) {
        me = OSi_GetSystemErrno(self);
        j = 3;
        g = data_020ccf94;
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(g, j)) {
                if (j == 0) {
                    func_020a5bc4(self, 0, 0);
                } else {
                    func_020a76cc(&b0);
                    func_020a76ac(&b0, 0, func_020a5bd8(self), OSi_GetSystemErrno(self));
                    func_02073820(g);
                    func_020737f0(g, &b0, 1);
                    func_02073770(g, 0xc, j);
                    func_020a5bc4(self, j, 1);
                    func_020a76c8(&b0);
                }
            }
        }
        func_020a5c10(self, 1);
    }

    if (func_020a5c08(self) == 1) {
        ok2 = 1;
        me = OSi_GetSystemErrno(self);
        j = 3;
        h = data_020ccf94;
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(h, j)) {
                st2 = func_020a5bb8(self, j);
                if (st2 != 2 && st2 != 3) {
                    ok2 = 0;
                    break;
                }
            }
        }
        if (ok2) {
            ok3 = 1;
            for (j = 3; j >= 0; j--) {
                if (j != me && func_02073dd4(h, j)) {
                    if (func_020a5bb8(self, j) == 3) {
                        ok3 = 0;
                        break;
                    }
                }
            }
            if (ok3) {
                for (j = 3; j >= 0; j--) {
                    if (j != me && func_02073dd4(h, j)) {
                        if (j == 0) {
                            func_020a5bc4(self, 0, 5);
                        } else {
                            func_020a76cc(&b1);
                            func_020a76ac(&b1, 5, 4, OSi_GetSystemErrno(self));
                            func_02073820(h);
                            func_020737f0(h, &b1, 1);
                            func_02073770(h, 0xc, j);
                            func_020a5bc4(self, j, 5);
                            func_020a76c8(&b1);
                        }
                    }
                }
                if (func_020a5bd8(self) == 0 || func_02073918(h, me) != 0) {
                    func_020a617c(self, me, 5);
                } else {
                    b2 = 5;
                    h = data_020ccf94;
                    func_02073820(h);
                    func_020737f0(h, &b2, 1);
                    func_02073770(h, 1, me);
                    func_020a617c(self, me, 7);
                }
                if (func_020a5bd8(self) == 0) {
                    func_020a6cd4(0);
                }
                func_020a5c30(self, me);
                func_020a5c10(self, 2);
            } else {
                for (j = 3; j >= 0; j--) {
                    if (j != me && func_02073dd4(h, j)) {
                        if (func_020a5bb8(self, j) == 2) {
                            if (j == 0) {
                                func_020a5bc4(self, 0, 4);
                            } else {
                                func_020a76cc(&b3);
                                func_020a76ac(&b3, 4, 4, OSi_GetSystemErrno(self));
                                func_02073820(h);
                                func_020737f0(h, &b3, 1);
                                func_02073770(h, 0xc, j);
                                func_020a5bc4(self, j, 4);
                                func_020a76c8(&b3);
                            }
                        } else {
                            func_020a5bc4(self, j, 6);
                        }
                    }
                }
                func_020a5c10(self, 3);
            }
        }
    }

    if (func_020a5c08(self) == 2) {
        ok4 = 1;
        me = OSi_GetSystemErrno(self);
        j = 3;
        g = data_020ccf94;
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(g, j)) {
                if (func_020a5bb8(self, j) != 6) {
                    ok4 = 0;
                    break;
                }
            }
        }
        if (ok4) {
            func_020a5c10(self, 4);
        }
    }

    if (func_020a5c08(self) == 3) {
        ok5 = 1;
        me = OSi_GetSystemErrno(self);
        j = 3;
        h = data_020ccf94;
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(h, j)) {
                if (func_020a5bb8(self, j) != 6) {
                    ok5 = 0;
                    break;
                }
            }
        }
        if (ok5) {
            if (func_020a5bd8(self) == 0 || func_02073918(h, me) != 0) {
                func_020a617c(self, me, 6);
            } else {
                b4 = 6;
                h = data_020ccf94;
                func_02073820(h);
                func_020737f0(h, &b4, 1);
                func_02073770(h, 1, me);
                func_020a617c(self, me, 7);
            }
            if (func_020a5bd8(self) == 0) {
                func_020eae40();
            }
            func_020a5c10(self, 4);
        }
    }
}
