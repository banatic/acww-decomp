/* letter_write_scene_10: 14 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_022a1864 @ 0x022a1864, 0x34 bytes, Thumb
 * func_ov122_022a1854 @ 0x022a1854, 0x10 bytes, Thumb
 * func_ov122_022a1850 @ 0x022a1850, 0x2 bytes, Thumb
 * func_ov122_022a1808 @ 0x022a1808, 0x46 bytes, Thumb
 * func_ov122_022a1770 @ 0x022a1770, 0x98 bytes, Thumb
 * func_ov122_022a1764 @ 0x022a1764, 0xc bytes, Thumb
 * func_ov122_022a1738 @ 0x022a1738, 0x2c bytes, Thumb
 * func_ov122_022a1718 @ 0x022a1718, 0x20 bytes, Thumb
 * func_ov122_022a15b8 @ 0x022a15b8, 0x160 bytes, Thumb
 * func_ov122_022a14c0 @ 0x022a14c0, 0xf8 bytes, Thumb
 * func_ov122_022a1380 @ 0x022a1380, 0x140 bytes, Thumb
 * func_ov122_022a132c @ 0x022a132c, 0x54 bytes, Thumb
 * func_ov122_022a12f0 @ 0x022a12f0, 0x3c bytes, Thumb
 * func_ov122_022a1290 @ 0x022a1290, 0x60 bytes, Thumb
 */

#include "types.h"

#define U8(p) (*(unsigned char *) (p))
#define P(a) (*(char **) ((a) + 0xbc))

typedef struct {
    char pad_00[0xbc];
    int unk_BC;
    int unk_C0;
    char pad_C4[0x3ce8 - 0xc4];
} UnkStruct_022a1770;

typedef struct {
    char pad_00[0x3ce8];
    char field_at_3ce8;
} FarField;

struct UnkStruct_022a14c0 {
    u8 pad_00[0xaa];
    u8 unk_AA;
    u8 pad_AB;
    u8 unk_AC;
    u8 pad_AD[0x0f];
    u32 unk_BC;
    u8 sub[1];
};

extern void func_0206e2d0(void *);
extern void func_ov095_0229bf7c(void *, int);
extern void func_ov002_022091cc(void *);
extern void func_ov002_0220af74(int x);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int data_021fbe94;
extern const char data_ov122_022a2798[];
extern const char data_ov122_022a27b0[];
extern const char data_ov122_022a27c8[];
extern int func_02002d14(const void *a, int b, int c, int d, int e, int f);
extern int func_02002c6c(const void *a, int b, int c, int d, int e, int f);
extern int func_ov095_0229c000(void *a, const void *b);
extern void func_ov095_0229bfd8(void *a, int b);
extern int func_02066648(int a);
extern void func_ov002_0220a448(int a, int b);
extern void func_0206e344(void *a, int b);
extern int func_ov095_0229b324(void *receiver);
extern int func_ov122_0229efe8(void *obj, int param);
extern int func_ov002_0220ac4c(void *ptr);
extern int func_ov002_0220ac7c(void *ptr);
extern int func_ov002_0220aacc(void *ptr, int n);
extern void func_ov002_0220a8dc(void *ptr);
extern void func_ov122_0229efd8(char *, int);
extern void func_0206e114(char *, char *, char *);
extern void func_0206e03c(char *, char *, int);
extern void func_0206dff8(char *, char *);
extern int func_ov122_0229f958(char *);
extern void func_0206dfe0(char *, int, int, int);
extern int func_0206e224(char *);
extern void func_0206df58(char *, int, int, int);
extern void func_0206df40(char *, int, int, int);
extern int func_ov095_0229bc00(void *a, void *b, int c, void *d, int e, int f, int g, int h, int i, int j);
extern void func_ov095_0229ce84(void *a, int b);
extern void func_ov095_0229cef4(void *a, int b);
extern void func_ov095_0229bee4(void *a);
extern void func_ov095_0229bed8(void *receiver, int value);
extern int func_ov122_0229f980(struct UnkStruct_022a14c0 *p);
extern int func_ov002_02208054(void *self, int flag);
extern unsigned char *func_ov122_022a0038(void *self);
extern int func_ov095_0229bf48(void *sub);
extern int func_ov002_0220a784(const void *sub, int val);
extern void func_ov122_022a0df8(void *self);
extern void func_ov122_022a0dec(void *self);
extern int func_ov095_0229aff0(void *sub);
extern void func_ov095_0229c22c(void *sub, int a, int b, int c);
extern int func_ov122_0229fc30(void *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229b3ec(void *sub);
extern int func_ov122_0229f540(void *self);
extern void func_ov002_0220a574(void *sub);
extern void func_ov122_0229f940(void *self);
extern int func_ov122_022a1110(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern int func_ov095_0229bf0c(void *ptr);
extern int func_ov095_0229c548(void *ptr);
extern int func_ov095_0229c448(void *ptr, int val, int n);
extern int func_ov122_022a0be4(void *ptr, int val);
extern void func_ov095_0229c8e4(void *ptr, int val);
extern void func_ov122_0229fc2c(void *receiver);
extern int func_ov002_0220a568(void *);
extern unsigned char *func_ov122_022a0054(void *);
extern void func_ov122_0229f4e0(void *);
extern void func_ov122_0229efc8(void *p, int v);
extern int func_ov122_0229fb54(void *unused0);
extern void func_0200467c(int v);
extern void func_ov122_0229f394(void *p);

void func_ov122_022a1850(void *receiver);
void func_ov122_022a15b8(char *a, int flag, int v);
void func_ov122_022a14c0(struct UnkStruct_022a14c0 *p);

void func_ov122_022a1864(void *param)
{
    func_0206e2d0((char *) param + 0x3ce8);
    func_ov095_0229bf7c((char *) param + 0xc0, 6);
    func_ov002_022091cc((char *) param + 0x42b0);
    func_ov122_022a1850(param);
}

void func_ov122_022a1854(int arg0)
{
    func_ov002_0220af74(arg0 + 0x4698);
}

void func_ov122_022a1850(void *receiver) {}

void func_ov122_022a1808(void)
{
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 3);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 3);
    func_020028bc(3, 0, 0, 0);
}

void func_ov122_022a1770(UnkStruct_022a1770 *obj)
{
    int saved;

    saved = data_021fbe94;

    func_02002d14(data_ov122_022a2798, saved, 6, 1, 1, 9);
    func_ov095_0229c000(&obj->unk_C0, data_ov122_022a27b0);
    func_ov122_022a14c0((struct UnkStruct_022a14c0 *) obj);
    func_ov095_0229bfd8(&obj->unk_C0, 6);
    func_02002c6c(data_ov122_022a27c8, saved, 6, 0x13d, 0x13d, 0x1e9);
    func_ov002_0220a448(func_02066648(obj->unk_BC), 4);
    func_0206e344((char *) obj + 0x3ce8, 3);
    func_ov122_022a15b8((char *) obj, 1, 1);
    func_0206e2d0(&((FarField *) obj)->field_at_3ce8);
}

void func_ov122_022a1764(int p0)
{
    func_ov095_0229b324((void *) ((char *) p0 + 192));
}

void func_ov122_022a1738(void *obj)
{
    if (func_ov122_0229efe8(obj, 0x10)) {
        func_ov002_0220ac4c((char *) obj + 0x4698);
    } else {
        func_ov002_0220ac7c((char *) obj + 0x4698);
    }
}

void func_ov122_022a1718(char *p)
{
    func_ov002_0220aacc(p + 0x4698, 0x22);
    func_ov002_0220a8dc(p + 0x4698);
}

void func_ov122_022a15b8(char *a, int flag, int v)
{
    int base, n, mode;

    func_ov122_0229efd8(a, 0x1000);
    if (flag != 0) {
        func_0206e114(a + 0x3ce8, P(a), a + 0x41e0);
        func_0206e03c(a + 0x3ce8, P(a) + 0x58, v);
        func_0206dff8(a + 0x3ce8, P(a) + 0xd8);
    } else {
        switch (U8(a + 0xaa)) {
            case 0:
            case 1:
                func_0206e114(a + 0x3ce8, P(a), a + 0x41e0);
                break;
            case 2:
                func_0206e03c(a + 0x3ce8, P(a) + 0x58, v);
                break;
            case 3:
                func_0206dff8(a + 0x3ce8, P(a) + 0xd8);
                break;
        }
    }
    if (func_ov122_0229f958(a)) {
        mode = 0;
        if (U8(a + 0xad) > U8(a + 0xae)) {
            base = U8(a + 0xae);
            n = U8(a + 0xad) - U8(a + 0xae);
        } else {
            base = U8(a + 0xad);
            n = U8(a + 0xae) - U8(a + 0xad);
        }
    } else {
        mode = 1;
        n = 0;
    }
    if (n != 0) {
        switch (U8(a + 0xaa)) {
            case 0:
                func_0206dfe0(a + 0x3ce8, base, n, mode);
                break;
            case 1: {
                int off = base + (U8(P(a) + 0xf8) + func_0206e224(a + 0x3ce8));
                func_0206dfe0(a + 0x3ce8, off, n, mode);
                break;
            }
            case 2:
                func_0206df58(a + 0x3ce8, base, n, mode);
                break;
            case 3:
                func_0206df40(a + 0x3ce8, base, n, mode);
                break;
        }
    }
    func_ov122_022a14c0((struct UnkStruct_022a14c0 *) a);
}

void func_ov122_022a14c0(struct UnkStruct_022a14c0 *p)
{
    u8 local;
    int r;

    if (p->unk_AA == 2) {
        local = p->unk_AC;
        r = func_ov095_0229bc00(p->sub, (void *) (p->unk_BC + 0x58), 0xa, &local, 0x40, 0x28, 0x4, 0xa0, 0x1, 0x1);
        if (r) {
            func_ov095_0229ce84(p->sub, 0);
        } else {
            func_ov095_0229cef4(p->sub, 0);
        }
    } else {
        func_ov095_0229cef4(p->sub, 0);
    }

    if (func_ov122_0229f958((char *) p)) {
        func_ov095_0229ce84(p->sub, 0xb);
    } else {
        func_ov095_0229cef4(p->sub, 0xb);
    }

    if (func_ov122_0229efe8((void *) p, 0x400)) {
        func_ov095_0229ce84(p->sub, 0xc);
    } else {
        func_ov095_0229cef4(p->sub, 0xc);
    }

    if (func_ov122_0229f958((char *) p)) {
        func_ov095_0229bee4(p->sub);
        func_ov095_0229ce84(p->sub, 6);
    } else {
        if (p->unk_AC == 0) {
            func_ov095_0229bee4(p->sub);
        } else {
            r = func_ov122_0229f980(p);
            func_ov095_0229bed8(p->sub, r);
        }
    }
}

void func_ov122_022a1380(char *self)
{
    int r6, r7, r4;
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov122_022a0038(self);
        return;
    }

    r6 = 0;
    if (func_ov095_0229bf48(self + 0xc0)) {
        r6 = 1;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag != 0) {
        r7 = data_021f6c58;
        r4 = data_021f6c54;

        if (func_ov002_0220a784(self + 0x4698, 9)) {
            func_ov122_022a0df8(self);
            return;
        }

        if (!func_ov122_0229efe8(self, 0x10)) {
            if (func_ov002_0220a784(self + 0x4698, 0)) {
                func_ov122_022a0dec(self);
                return;
            }
        }

        if (func_ov095_0229aff0(self + 0xc0)) {
            func_ov095_0229c22c(self + 0xc0, 9, 6, 1);
            func_ov122_022a15b8((char *) self, 0, 1);
            return;
        }

        if (r4 < 0x48) {
            if (r7 < 0xe0) {
                if (func_ov122_0229fc30(self)) {
                    func_ov002_02208098((void *) (self), 3);
                    func_ov095_0229b3ec(self + 0xc0);
                    func_ov122_022a15b8((char *) self, 1, 1);
                    return;
                }
            } else {
                if (func_ov122_0229f540(self)) {
                    func_ov002_0220a574(self + 0x4010);
                    func_ov002_02208098((void *) (self), 2);
                    func_ov122_0229f940(self);
                    func_ov122_022a15b8((char *) self, 1, 1);
                    return;
                }
            }
        }

        if (r4 >= 0x48) {
            if (r6 == 0) {
                int r = func_ov122_022a1110(self);
                if (r != 0) {
                    if (r == 1) {
                        func_ov002_02208098((void *) (self), 1);
                    }
                }
            }
        }
    }
}

void func_ov122_022a132c(void *param)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (param), 0);
        return;
    }
    if (func_ov095_0229bf0c((char *) param + 0xc0) != 0) {
        int v = func_ov095_0229c548((char *) param + 0xc0);
        int w = func_ov095_0229c448((char *) param + 0xc0, v, 9);
        func_ov122_022a0be4(param, w);
        param = (char *) param + 0xc0;
        func_ov095_0229c8e4(param, v);
    }
}

void func_ov122_022a12f0(void *s)
{
    *((char *) s + 0xab) = 0;
    if (data_021fbdd8 == 0) {
        func_ov122_0229fc2c(s);
        func_ov002_0220a568((char *) s + 0x4010);
        func_ov122_022a0054(s);
    } else {
        func_ov122_0229f4e0(s);
    }
}

void func_ov122_022a1290(char *p)
{
    int r5;

    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (p), 0);
        if (*(unsigned char *) (p + 0xad) == *(unsigned char *) (p + 0xae)) {
            func_ov122_0229efc8(p, 8);
        }
        r5 = 1;
    } else {
        r5 = func_ov122_0229fb54(p);
        if (r5 != 0) {
            func_0200467c(0x15);
        }
    }
    if (r5 != 0) {
        func_ov122_0229f394(p);
        func_ov122_022a15b8((char *) p, 0, 1);
    }
}
