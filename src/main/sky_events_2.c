/* sky_events_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bd7a4 @ 0x020bd7a4, 0x194 bytes, Thumb
 * func_020bd6d0 @ 0x020bd6d0, 0xd4 bytes, Thumb
 * func_020bd688 @ 0x020bd688, 0x48 bytes, Thumb
 */

typedef struct UnkStruct_020bd7a4 UnkStruct_020bd7a4;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020bd7a4_2;

struct UnkStruct_020bd7a4 {
    char pad_00[0x2f00];
    int unk_2F00;
    int unk_2F04;
    int unk_2F08;
    int unk_2F0C;
};

typedef struct UnkStruct_020bd6d0 UnkStruct_020bd6d0;

struct UnkStruct_020bd6d0 {
    char pad_00[0x2f19];
    unsigned char unk_2F19;
    char pad_2F1A[2];
    int unk_2F1C;
    int unk_2F20;
    char pad_2F24[8];
    int unk_2F2C;
    char pad_2F30[0x1c];
    int unk_2F4C;
};

extern void *func_020bdc50(UnkStruct_020bd7a4 *p, int a, int b, int c, int d);
extern int func_020644cc(int arg);
extern int data_021f8ab0[];
extern UnkStruct_020bd7a4_2 data_020d2424[];
extern int func_020be0d4(UnkStruct_020bd6d0 *p, int arg);
extern unsigned char data_021f3b28[];
extern void func_020bdc14(void *self, int a);

void func_020bd7a4(UnkStruct_020bd7a4 *p)
{
    int mode;
    int a;
    int b;
    UnkStruct_020bd7a4_2 *e;

    mode = 0;
    a = data_021f8ab0[9];
    b = data_021f8ab0[10];
    if (a == b) {
        if (a == 3) {
            mode = 2;
        } else if (a == 4) {
            mode = 4;
        }
    } else if (a > b) {
        if (b == 3) {
            mode = 3;
        } else if (b <= 3) {
            mode = 1;
        }
    } else {
        if (b == 3) {
            mode = 1;
        } else if (b > 3) {
            mode = 3;
        }
    }

    if (mode == 0) {
        p->unk_2F00 = 0;
        p->unk_2F0C = 0;
        return;
    }

    e = &data_020d2424[mode - 1];
    if (p->unk_2F00 == 0) {
        p->unk_2F00 = 1000;
    }

    if (p->unk_2F0C > 2) {
        if (b >= 3) {
            p->unk_2F08 = p->unk_2F08 + 2;
            if (p->unk_2F08 > 0x6400) {
                p->unk_2F08 = 0x6400;
            }
        } else {
            p->unk_2F08 = p->unk_2F08 - 2;
            if (p->unk_2F08 < 0) {
                p->unk_2F08 = 0;
            }
        }
    } else {
        if (b >= 3) {
            p->unk_2F08 = 0x6400;
        } else {
            p->unk_2F08 = p->unk_2F08 - 2;
            if (p->unk_2F08 < 0) {
                p->unk_2F08 = 0;
            }
        }
    }

    p->unk_2F04 = p->unk_2F04 + (p->unk_2F08 >> 8);

    while (p->unk_2F04 >= p->unk_2F00) {
        func_020bdc50(p, 1, 0x3c, 0, 0);
        p->unk_2F04 = p->unk_2F04 - p->unk_2F00;
        if (p->unk_2F04 <= p->unk_2F00) {
            switch (p->unk_2F0C) {
                case 0:
                    p->unk_2F00 = 0x2af8;
                    p->unk_2F04 = 0;
                    break;
                case 1:
                    p->unk_2F00 = 0x2328;
                    p->unk_2F04 = 0;
                    break;
                default:
                    p->unk_2F00 = e->unk_00 + func_020644cc(e->unk_04);
                    if (p->unk_2F0C < 0x32) {
                        p->unk_2F04 = 0x4b;
                    } else {
                        p->unk_2F04 = 0;
                    }
                    break;
            }
            p->unk_2F0C = p->unk_2F0C + 1;
            if (p->unk_2F0C > 0x32) {
                p->unk_2F0C = 0x32;
            }
            break;
        }
    }
}

void func_020bd6d0(UnkStruct_020bd6d0 *p)
{
    unsigned char s1;
    int s2;
    int r4;
    int r6;
    int r7;

    s1 = p->unk_2F19;
    r4 = 1;
    if (s1 < 0x13 && s1 >= 4) {
        r4 = 0;
    }

    s2 = data_021f8ab0[9];
    r6 = 0;
    if (s2 != 3 && s2 != 4) {
        r6 = 1;
    }

    r7 = 0;
    if (p->unk_2F2C == 0) {
        if (func_020be0d4(p, 9) == 0x3c) {
            r7 = 1;
        }
    }

    if (r4 != 0 && r6 != 0 && r7 != 0) {
        if (p->unk_2F4C > 0) {
            p->unk_2F4C = p->unk_2F4C - 1;
            if (p->unk_2F4C == 0) {
                func_020bdc50((UnkStruct_020bd7a4 *) p, 3, 0x1e, 0, 0);
            }
        } else {
            if (p->unk_2F1C == 0x1e && p->unk_2F1C != p->unk_2F20) {
                int arg = (data_021f3b28[2] == 0) ? 4 : 0x100;
                if (func_020644cc(arg) == 0) {
                    p->unk_2F4C = func_020644cc(0x258);
                }
            }
        }
    } else {
        p->unk_2F4C = 0;
    }
}

void func_020bd688(void *self)
{
    unsigned char b = *(unsigned char *) ((char *) self + 0x2f19);
    int w = *(int *) ((char *) self + 0x0e0c);
    int flag = (w == 4);
    if (b >= 19 || b < 4) {
        if (flag) {
            return;
        }
        func_020bdc50((UnkStruct_020bd7a4 *) self, 4, 0x1f, 0, 0);
    } else {
        if (!flag) {
            return;
        }
        func_020bdc14(self, 4);
    }
}
