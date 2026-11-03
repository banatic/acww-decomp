/* activity_save: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a0848 @ 0x020a0848, 0x2b0 bytes, Thumb
 * func_020a05e8 @ 0x020a05e8, 0x260 bytes, Thumb
 * func_020a03e0 @ 0x020a03e0, 0x208 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xef];
    unsigned char localReady[4];
    unsigned char pad_F3[1];
    unsigned char participantReady[4];
} UnkStruct_020a0848;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a0848_2;

typedef struct {
    unsigned char pad_00[0xef];
    unsigned char arr[4];
    unsigned char pad_F3[0x10e - 0xf3];
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_020a05e8;

typedef struct UnkStruct_020a03e0 UnkStruct_020a03e0;

struct UnkStruct_020a03e0 {
    char pad_00[0xb8];
    void *unk_B8;
    char pad_BC[0xef - (0xb8 + 4)];
    unsigned char unk_EF;
    char pad_F0[0x10e - (0xef + 1)];
    struct {
        unsigned char lo : 4;
        unsigned char hi : 4;
    } unk_10E;
};

extern int func_02073fdc(int firstBase);
extern void func_02074078(void);
extern int func_020ec260(void);
extern int func_02075aa4(int firstBase, int secondBase);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern void func_020750fc(void);
extern void func_020750f4(void);
extern void func_0207428c(void);
extern int func_0209ffb0(UnkStruct_020a0848 *s);
extern int func_02075848(void);

// Its own body ignores self, but the ROM caller preserves this input in r0.
extern void func_020a261c(UnkStruct_020a0848 *self);
extern void func_020a25e8(UnkStruct_020a0848 *s);
extern UnkStruct_020a0848_2 *func_020682e0(int firstBase);
extern void func_02116a1c(int firstBase);
extern int func_020a238c(UnkStruct_020a05e8 *s);
extern void func_0209fb54(void *p);
extern void func_020a2468(UnkStruct_020a05e8 *s);
extern void func_020a0b94(void *receiver);
extern void func_02088368(void);
extern int func_020a2120(UnkStruct_020a05e8 *s, int n);
extern int func_02073dd4(void *g, int i);
extern int func_02073918(void *g, int i);
extern void func_020a1224(UnkStruct_020a05e8 *s);
extern unsigned short func_020740dc(void);
extern void func_0209fb4c(void *p);
extern void *data_020ccf94;
extern char data_021f3ba0[];
extern int func_020a19c0(int unused, int idx);
extern void func_020a24ac(void *receiver);
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern unsigned char data_021dc7a8[];

int func_020a0848(UnkStruct_020a0848 *self, unsigned char *state, int firstBase, int secondBase, int participantMask,
                  unsigned char postMessage)
{
    unsigned char currentState;
    int allReady;
    int missingMask;
    int lost;
    int i;

    currentState = *state;
    if (currentState == firstBase) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_020ec260() == 0) {
            if (func_02075aa4(2, participantMask) != 0) {
                *state = firstBase + 1;
            }
        } else {
            if (func_02075aa4(2, 1) != 0) {
                *state = firstBase + 1;
            }
        }
    } else if (currentState == firstBase + 1) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if ((func_02073044(), func_020ebf70()) != 0) {
            *state = firstBase + 2;
        }
    } else if (currentState == firstBase + 2) {
        if (func_020ec260() == 0) {
            allReady = 1;
            missingMask = 0;
            func_020750fc();
            for (i = 3; i >= 0; i--) {
                if (i != 0) {
                    int bit = 1 << i;
                    if ((participantMask & bit) != 0) {
                        if (self->participantReady[i] == 0) {
                            allReady = 0;
                            missingMask |= bit;
                            missingMask = (unsigned short) missingMask;
                        }
                    }
                }
            }
            lost = func_02073fdc(missingMask);
            func_020750f4();
            if (lost != 0) {
                func_02074078();
                return 0x20;
            }
            if (allReady != 0) {
                func_0207428c();
                func_0209ffb0(self);
                *state = firstBase + 3;
            }
        } else {
            if (func_02073fdc(participantMask) != 0) {
                func_02074078();
                return 0x20;
            }
            if (self->localReady[0] != 0) {
                if (func_02075848() != 0) {
                    *state = firstBase + 3;
                }
            }
        }
    } else if (currentState == firstBase + 3) {
        if (func_020ec260() == 0) {
            *state = firstBase + 4;
        } else {
            if (func_02073fdc(participantMask) != 0) {
                func_02074078();
                return 0x20;
            }
            if ((func_02073044(), func_020ebf70()) != 0) {
                func_0207428c();
                func_0209ffb0(self);
                *state = firstBase + 4;
            }
        }
    } else if (currentState == firstBase + 4) {
        if (postMessage != 0) {
            func_020a261c(self);
        }
        *state = firstBase + 5;
    }

    // The first chain may advance state into the second chain this frame.
    currentState = *state;
    if (currentState == secondBase) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_020ec260() == 0) {
            if (func_02075aa4(2, participantMask) == 0) {
                goto end;
            }
            *state = secondBase + 1;
            goto end;
        }
        if (func_02075848() == 0) {
            goto end;
        }
        *state = secondBase + 1;
        goto end;
    }
    if (currentState == secondBase + 1) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if ((func_02073044(), func_020ebf70()) == 0) {
            goto end;
        }
        *state = secondBase + 2;
        goto end;
    }
    if (currentState == secondBase + 2) {
        if (func_020ec260() == 0) {
            allReady = 1;
            missingMask = 0;
            func_020750fc();
            for (i = 3; i >= 0; i--) {
                if (i != 0) {
                    int bit = 1 << i;
                    if ((participantMask & bit) != 0) {
                        if (self->participantReady[i] == 0) {
                            allReady = 0;
                            missingMask |= bit;
                            missingMask = (unsigned short) missingMask;
                        }
                    }
                }
            }
            lost = func_02073fdc(missingMask);
            func_020750f4();
            if (lost != 0) {
                func_02074078();
                return 0x20;
            }
            if (allReady == 0) {
                goto end;
            }
            func_0207428c();
            func_0209ffb0(self);
            *state = secondBase + 3;
            goto end;
        }
        func_0207428c();
        func_0209ffb0(self);
        *state = secondBase + 3;
        goto end;
    }
    if (currentState == secondBase + 3) {
        if (postMessage != 0) {
            func_020a25e8(self);
        }
        *state = secondBase + 4;
        goto end;
    }
    if (currentState == secondBase + 4) {
        if (func_020682e0(0)->unk_04 == 0) {
            func_02116a1c(0);
        }
    }
end:
    return 0x20;
}

int func_020a05e8(UnkStruct_020a05e8 *self, unsigned char *state, int p2, int base, unsigned char p4, unsigned char p5, int p6,
                  unsigned char p7, int p8)
{
    unsigned char st;
    int r;
    void *gb;
    void *ga;

    st = *state;
    if (st == base) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a238c(self);
        if (r == 1) {
            *state = p4;
            goto end;
        }
        if (r == 3) {
            goto end;
        }
        func_0209fb54(data_021f3ba0);
        if (p7 != 0) {
            func_020a2468(self);
            func_020a0b94(self);
            func_02088368();
        }
        *state = base + 1;
        goto end;
    }
    if (st == base + 1) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120(self, self->hi);
        if (r == 1) {
            *state = p4;
            goto end;
        }
        if (r != 0) {
            goto end;
        }
        *state = base + 2;
        goto end;
    }
    if (st == base + 2) {
        int f;
        int i;
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        f = 1;
        i = 3;
        ga = data_020ccf94;
        for (; i >= 0; i--) {
            if (func_02073dd4(ga, i) == 0) {
                continue;
            }
            if (func_02073918(ga, i) != 0) {
                continue;
            }
            if (self->arr[i] == 0) {
                f = 0;
                break;
            }
            if (self->arr[i] == 2) {
                f = 2;
                break;
            }
        }
        if (f != 0) {
            if (p2 == 0) {
                f = 0;
            } else if (p2 == 2) {
                f = 2;
            }
        }
        if (f == 1) {
            func_020a1224(self);
            *state = base + 3;
            goto end;
        }
        if (f == 2) {
            *state = p5;
        }
        goto end;
    }
    if (st == base + 3) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        if ((func_02073044(), func_020ebf70()) == 0) {
            goto end;
        }
        if (func_02075aa4(1, (unsigned short) (func_020740dc())) == 0) {
            goto end;
        }
        func_0209fb4c(data_021f3ba0);
        *state = base + 4;
        goto end;
    }
    if (st == base + 4) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120(self, self->hi);
        if (r == 1) {
            *state = p4;
            goto end;
        }
        if (r != 0) {
            goto end;
        }
        *state = base + 5;
        goto end;
    }
    if (st == base + 5) {
        int f;
        int i;
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        f = 1;
        i = 3;
        gb = data_020ccf94;
        for (; i >= 0; i--) {
            if (func_02073dd4(gb, i) == 0) {
                continue;
            }
            if (func_02073918(gb, i) != 0) {
                continue;
            }
            if (self->arr[i] == 0) {
                f = 0;
                break;
            }
            if (self->arr[i] == 2) {
                f = 2;
                break;
            }
        }
        if (f == 1) {
            *state = base + 6;
            goto end;
        }
        if (f == 2) {
            *state = p5;
        }
        goto end;
    }
    if (st == base + 6) {
        unsigned short m;
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        m = func_020740dc();
        if (p6 < 4) {
            m = (unsigned short) (m | (1 << p6));
        }
        if (func_02075aa4(1, (unsigned short) m) != 0) {
            *state = base + 7;
        }
    }
end:
    return 0x20;
}

int func_020a03e0(UnkStruct_020a03e0 *p, unsigned char *q, int a, int b, unsigned char c, unsigned char d, unsigned char e,
                  int f)
{
    int r;
    unsigned char v;
    int lf = f;

    if (*q == a) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a238c((UnkStruct_020a05e8 *) p);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r == 3) {
            goto out;
        }
        MI_CpuCopy8((void *) data_021dc7a8, p->unk_B8, 0x173fc);
        *q = (unsigned char) (a + 1);
        goto out;
    }
    if (*q == a + 1) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a19c0((int) p, p->unk_10E.lo);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r != 0) {
            goto out;
        }
        if (d) {
            func_020a2468((UnkStruct_020a05e8 *) ((int) p));
        }
        func_020a24ac(p);
        if (d) {
            func_020a0b94(p);
            func_02088368();
        }
        func_0209fb54((void *) ((unsigned char *) data_021f3ba0));
        *q = (unsigned char) (a + 2);
        goto out;
    }
    if (*q == a + 2) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120((UnkStruct_020a05e8 *) p, p->unk_10E.hi);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r != 0) {
            goto out;
        }
        *q = (unsigned char) (a + 3);
        goto out;
    }
    if (*q == a + 3) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_02075aa4(1, 1) == 0) {
            goto out;
        }
        *q = (unsigned char) (a + 4);
        goto out;
    }
    if (*q == a + 4) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        v = p->unk_EF;
        if (v == 1) {
            func_020a1224((UnkStruct_020a05e8 *) p);
            func_0209fb4c((void *) ((unsigned char *) data_021f3ba0));
            *q = (unsigned char) (a + 5);
            goto out;
        }
        if (v == 2) {
            *q = (unsigned char) c;
            goto out;
        }
        goto out;
    }
    if (*q == a + 5) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120((UnkStruct_020a05e8 *) p, p->unk_10E.hi);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r != 0) {
            goto out;
        }
        if (e) {
            MI_CpuCopy8(p->unk_B8, (void *) data_021dc7a8, 0x173fc);
        }
        *q = (unsigned char) (a + 6);
        goto out;
    }
    if (*q == a + 6) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_02075aa4(1, 1) == 0) {
            goto out;
        }
        *q = (unsigned char) (a + 7);
        goto out;
    }
    if (*q == a + 7) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        v = p->unk_EF;
        if (v == 1) {
            *q = (unsigned char) (a + 8);
            goto out;
        }
        if (v == 2) {
            *q = (unsigned char) c;
            goto out;
        }
        goto out;
    }
out:
    return 0x20;
}
