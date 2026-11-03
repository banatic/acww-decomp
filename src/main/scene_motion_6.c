/* scene_motion_6: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02017ee4 @ 0x02017ee4, 0x38 bytes, Thumb
 * func_02017e7c @ 0x02017e7c, 0x68 bytes, Thumb
 * func_02017e20 @ 0x02017e20, 0x5c bytes, Thumb
 * func_02017e00 @ 0x02017e00, 0x20 bytes, Thumb
 * func_02017dd8 @ 0x02017dd8, 0x28 bytes, Thumb
 * func_02017d80 @ 0x02017d80, 0x58 bytes, Thumb
 * func_02017d14 @ 0x02017d14, 0x6c bytes, Thumb
 * func_02017cf8 @ 0x02017cf8, 0x1a bytes, Thumb
 * func_02017cac @ 0x02017cac, 0x4c bytes, Thumb
 * func_02017c70 @ 0x02017c70, 0x3c bytes, Thumb
 * func_02017c18 @ 0x02017c18, 0x58 bytes, Thumb
 * func_02017b44 @ 0x02017b44, 0xd4 bytes, Thumb
 * func_02017af0 @ 0x02017af0, 0x54 bytes, Thumb
 * func_02017ab4 @ 0x02017ab4, 0x3c bytes, Thumb
 */

struct UnkStruct_02017dd8 {
    char pad_00[0x98];
    unsigned char unk_98;
};

struct SomeOtherStruct {
    char pad_00[0x190];
    unsigned int unk_190;
};

struct UnkStruct_02017cf8 {
    unsigned char pad_00[0x98];
    unsigned char unk_98;
};

typedef struct {
    unsigned char unk_00[0x98];
    unsigned char unk_98;
} UnkStruct_02017ab4;

typedef struct {
    unsigned char unk_00[0x28];
    void *unk_28;
} UnkStruct_02017ab4_2;

extern int func_02019de4(void *p);
extern int func_02017f1c(void *p, int q, int r, int s, int t);
extern void func_02019af0(void *p, int q);
extern int func_020164cc(void *, int);
extern int func_02095a28(void);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02012444(int, int, int);
extern int func_02057d34(void *);
extern int func_02057bd4(void);
extern void func_0209129c(int value);
extern void func_02057cb8(void *p);
extern int func_02057bf0(int);
extern unsigned short data_020c80f8;
extern int func_02057c20(void *ptr);
extern int func_02057d0c(int, int);
extern int func_02057cf4(void);
extern int func_0200442c(const void *, int, int, int);
extern int func_02057b90(int, void *);
extern int func_ov004_0222bf50(void);

void func_02017ee4(void *arg0, int arg1)
{
    int result;
    result = func_02019de4(arg0);
    if (func_02017f1c(arg0, arg1, result + 0x22, 0x28, 1) != 0) {
        func_02019af0(arg0, 1);
        ((unsigned char *) arg0)[0x98] = 0x14;
    }
}

void func_02017e7c(void *a0, void *a1)
{
    if (func_020164cc((char *) a1 + 0x334, (int) a1)) {
        if (func_02095a28()) {
            unsigned short g = (*(volatile unsigned short *) &data_020c80f8);
            int f;

            func_02016764((char *) a1 + 0x334, a1, 0x23, (*(volatile unsigned short *) &data_020c80f8), 0, 0x1000, 0, 0);

            f = *(int *) ((char *) a1 + 0x628);
            if (f != 0) {
                func_02012444(f, g, 0);
            }

            *((unsigned char *) a0 + 0x98) = 8;
        }
    }
}

void func_02017e20(unsigned char *param0, unsigned char *param1)
{
    unsigned short v;
    int field;

    if (func_02057d34(param1) != 0) {
        return;
    }

    v = (*(volatile unsigned short *) &data_020c80f8);

    func_02016764(param1 + 0x334, param1, 0, (*(volatile unsigned short *) &data_020c80f8), 0, 0x1000, 0, 0);

    field = *(int *) (param1 + 0x628);
    if (field != 0) {
        func_02012444(field, v, 0);
    }

    param0[0x98] = 9;
}

void func_02017e00(void *param, int event)
{
    if (func_02057bd4() == 0) {
        func_02019af0(param, 1);
        *((char *) param + 0x98) = 0x14;
    }
}

void func_02017dd8(struct UnkStruct_02017dd8 *a, struct SomeOtherStruct *b)
{
    if (((b->unk_190 << 4) >> 16) == 0) {
        func_02019af0((void *) a, 1);
        a->unk_98 = 0x14;
    }
}

void func_02017d80(void *self, void *other)
{
    if (func_020164cc((char *) other + 0x334, (int) other)) {
        func_02016764((char *) other + 0x334, other, 0x2a, 0, 1, 0x1000, 0, 0);
        {
            int val = *((int *) ((char *) self + 0xac));
            if (val != -1) {
                func_0209129c(val);
            }
        }
        *((unsigned char *) self + 0x98) = 0xc;
    }
}

void func_02017d14(void *p0, void *p1)
{
    if (func_020164cc((char *) p1 + 0x334, (int) p1)) {
        unsigned short saved = (*(volatile unsigned short *) &data_020c80f8);
        func_02016764((char *) p1 + 0x334, p1, 0, (unsigned short) ((*(volatile unsigned short *) &data_020c80f8)), 0, 0x1000, 0, 0);
        if (*(unsigned int *) ((char *) p1 + 0x628) != 0) {
            func_02012444(*(unsigned int *) ((char *) p1 + 0x628), (unsigned short) saved, 0);
        }
        func_02057cb8(p1);
        func_02019af0(p0, 1);
        *(unsigned char *) ((char *) p0 + 0x98) = 0x14;
    }
}

void func_02017cf8(struct UnkStruct_02017cf8 *s, int event)
{
    if (func_02057bf0(1)) {
        s->unk_98 = 14;
    }
}

void func_02017cac(char *a, char *b)
{
    if (func_02057bf0(1) != 0) {
        return;
    }
    func_02016764((void *) (b + 0x334), (void *) b, 0x2c, data_020c80f8, 1, 0x1000, 0, 0);
    *(a + 0x98) = 0xf;
}

void func_02017c70(void *param0, void *param1)
{
    int result;
    unsigned char *ptr;

    result = func_020164cc((char *) param1 + 0x334, (int) param1);
    if (result != 0) {
        result = func_02057c20(param1);
        if (result != 0) {
            result = func_02057d0c(3, (int) param1);
            if (result != 0) {
                ptr = (unsigned char *) param0 + 0x98;
                *ptr = 0x10;
            }
        }
    }
}

void func_02017c18(void *a, int b)
{
    if (func_02057bf0(3) == 0) {
        if (func_02057d0c(4, b) != 0) {
            func_02016764((void *) (b + 0x334), (void *) b, 0x2d, (unsigned short) data_020c80f8, 1, 0x1000, 0, 0);
            *((char *) a + 0x98) = 0x11;
        }
    }
}

void func_02017b44(unsigned char *arg0, unsigned char *arg1)
{
    int state;

    if (func_020164cc((void *) (arg1 + 0x334), (int) arg1) == 0) {
        return;
    }

    state = func_02057cf4();

    if (state == 5) {
        goto state5;
    }
    if (state != 7) {
        goto else_block;
    }

    // state == 7
    if (func_02057d0c(7, (int) arg1) == 0) {
        return;
    }
    func_02016764((void *) (arg1 + 0x334), (void *) arg1, 0x2d, (unsigned short) data_020c80f8, 3, 0x1000, 0, 0);
    arg0[0x98] = 0x12;
    goto end;

state5:
    if (func_02057d0c(5, (int) arg1) == 0) {
        return;
    }
    func_02016764((void *) (arg1 + 0x334), (void *) arg1, 0x2e, (unsigned short) data_020c80f8, 1, 0x1000, 0, 0);
    func_0200442c(arg1 + 0x514, 0x4f, 0x7f, 0);
    arg0[0x98] = 5;
    goto end;

else_block:
    func_02016764((void *) (arg1 + 0x334), (void *) arg1, 0x24, (unsigned short) data_020c80f8, 0, 0x1000, 0, 0);
    func_02019af0((void *) arg0, 1);
    arg0[0x98] = 0x14;

end:
    return;
}

void func_02017af0(char *a, int b)
{
    if (func_020164cc((void *) (b + 0x334), b) != 0) {
        if (func_02057d0c(2, b) != 0) {
            func_02016764((void *) (b + 0x334), (void *) b, 0, data_020c80f8, 0, 0x1000, 0, 0);
            a[0x98] = 0x13;
        }
    }
}

void func_02017ab4(UnkStruct_02017ab4 *param1, void *param2)
{
    UnkStruct_02017ab4_2 *ptr;
    ptr = (UnkStruct_02017ab4_2 *) func_02019de4(param1);
    if (func_02057bf0(2) == 0) {
        func_02057b90(9, param2);
        if (func_02057c20(ptr->unk_28) != 0) {
            if (func_ov004_0222bf50() != 0) {
                param1->unk_98 = 9;
            }
        }
    }
}
