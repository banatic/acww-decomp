/* storage_scene_2: 8 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229ca78 @ 0x0229ca78, 0x20 bytes, Thumb
 * func_ov102_0229ca58 @ 0x0229ca58, 0x20 bytes, Thumb
 * func_ov102_0229ca38 @ 0x0229ca38, 0x20 bytes, Thumb
 * func_ov102_0229c9fc @ 0x0229c9fc, 0x3c bytes, Thumb
 * func_ov102_0229c9b0 @ 0x0229c9b0, 0x4c bytes, Thumb
 * func_ov102_0229c8bc @ 0x0229c8bc, 0xf4 bytes, Thumb
 * func_ov102_0229c790 @ 0x0229c790, 0x12c bytes, Thumb
 * func_ov102_0229c740 @ 0x0229c740, 0x50 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229c8bc {
    unsigned char pad_00[0x25a5];
    unsigned char unk_25A5;
};

typedef struct {
    char pad_00[0x25a5];
    u8 unk_25A5;
} SelfType;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *);
extern void func_ov002_0220a374(void *p, int n);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov102_0229c298(struct UnkStruct_0229c8bc *, int);
extern int func_ov002_022088ac(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088bc(void *);

void func_ov102_0229ca78(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x2274);
    func_ov002_02208098(arg0, 6);
}

void func_ov102_0229ca58(void *arg0)
{
    func_ov002_0220a164((char *) arg0 + 0x2274);
    func_ov002_02208098(arg0, 7);
}

void func_ov102_0229ca38(void *self)
{
    func_ov002_0220a374((char *) self + 0x2274, 4);
    func_ov002_02208098(self, 8);
}

void func_ov102_0229c9fc(void *self, unsigned char value)
{
    func_ov002_02207d24((char *) self + 0x218c, 1);
    ((unsigned char *) self)[0x25a6] = value;
    func_ov002_0220a374((char *) self + 0x2274, 5);
    func_ov002_02208098(self, 0xa);
}

void func_ov102_0229c9b0(int arg0, int arg1)
{
    unsigned char *p;

    p = (unsigned char *) arg0;
    func_ov002_02207d24(p + 0x218c, 1);
    p[0x25a7] = p[0x8d];
    p[0x25a6] = (unsigned char) arg1;
    func_ov002_0220a374(p + 0x2274, 6);
    func_ov002_02208098(p, 0xb);
}

void func_ov102_0229c8bc(struct UnkStruct_0229c8bc *a, void *b, int c)
{
    int f;
    int cnt;

    f = a->unk_25A5;
    cnt = 0;
    while (f >= 5) {
        f -= 5;
        cnt++;
    }

    if (func_ov002_022088ac(b) == 0) {
        goto L922;
    }
    if (func_ov002_022088cc(b) != 0) {
        if (cnt != 0) {
            goto L968;
        }
    }
    if (f != 0) {
        goto L914;
    }

    if (c == 1) {
        a->unk_25A5 += 4;
    } else {
        a->unk_25A5 = 0x24;
    }
    func_ov102_0229c298(a, 0x10);
    return;

L914:
    a->unk_25A5--;
    f--;
    goto L968;

L922:
    if (func_ov002_0220889c(b) == 0) {
        goto L968;
    }
    if (func_ov002_022088bc(b) != 0) {
        goto L968;
    }
    if (f != 4) {
        goto L95c;
    }
    if (c == 1) {
        a->unk_25A5 -= 4;
        func_ov102_0229c298(a, 0x20);
        return;
    } else {
        a->unk_25A5 = 0x24;
        return;
    }

L95c:
    a->unk_25A5++;
    f++;
    goto L968;

L968:
    if (func_ov002_022088cc(b) == 0) {
        goto L98a;
    }
    if (cnt > 0) {
        a->unk_25A5 -= 5;
        return;
    } else {
        f += 25;
        a->unk_25A5 = f;
        return;
    }

L98a:
    if (func_ov002_022088bc(b) == 0) {
        return;
    }
    if (cnt >= 2) {
        return;
    }
    a->unk_25A5 += 5;
}

void func_ov102_0229c790(SelfType *self, void *other, int arg2)
{
    int rem = self->unk_25A5 - 15;
    int quot = 0;

    while (rem >= 5) {
        rem -= 5;
        quot++;
    }

    if (func_ov002_022088ac(other) != 0) {
        if (func_ov002_022088cc(other) != 0 && quot != 0) {
            goto L_876;
        }

        if (rem == 0) {
            switch (quot) {
                case 0:
                    self->unk_25A5 = 0x20;
                    break;
                case 1:
                    self->unk_25A5 = 0x23;
                    break;
                case 2:
                default:
                    if (arg2 == 1) {
                        self->unk_25A5 += 4;
                    } else {
                        self->unk_25A5 = 0x24;
                    }
                    break;
            }

            func_ov102_0229c298((struct UnkStruct_0229c8bc *) self, 0x10);
            return;
        } else {
            self->unk_25A5--;
            rem--;
            goto L_876;
        }
    } else {
        if (func_ov002_0220889c(other) != 0) {
            if (func_ov002_022088bc(other) == 0) {
                if (rem == 4) {
                    switch (quot) {
                        case 0:
                            self->unk_25A5 = 0x1e;
                            return;
                        case 1:
                            self->unk_25A5 = 0x21;
                            return;
                        case 2:
                        default:
                            if (arg2 == 1) {
                                self->unk_25A5 -= 4;
                                func_ov102_0229c298((struct UnkStruct_0229c8bc *) self, 0x20);
                            } else {
                                self->unk_25A5 = 0x24;
                            }
                            return;
                    }
                } else {
                    self->unk_25A5++;
                    rem++;
                }
            }
        }
    }

L_876:
    if (func_ov002_022088cc(other) != 0) {
        if (quot > 0) {
            self->unk_25A5 -= 5;
        }
        return;
    }

    if (func_ov002_022088bc(other) != 0) {
        if (quot < 2) {
            self->unk_25A5 += 5;
        } else {
            self->unk_25A5 = rem;
        }
    }
}

void func_ov102_0229c740(void *r5, void *r4)
{
    if (func_ov002_022088cc(r4) != 0) {
        ((unsigned char *) r5)[0x25a5] = 0x21;
    }
    if (func_ov002_0220889c(r4) != 0) {
        ((unsigned char *) r5)[0x25a5] = 0;
        func_ov102_0229c298((struct UnkStruct_0229c8bc *) r5, 0x20);
    } else if (func_ov002_022088ac(r4) != 0) {
        ((unsigned char *) r5)[0x25a5] = 4;
    }
}
