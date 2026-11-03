/* tune_editor_states_2: 10 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_0229a944 @ 0x0229a944, 0x8 bytes, Thumb
 * func_ov143_0229a91c @ 0x0229a91c, 0x28 bytes, Thumb
 * func_ov143_0229a914 @ 0x0229a914, 0x8 bytes, Thumb
 * func_ov143_0229a8dc @ 0x0229a8dc, 0x38 bytes, Thumb
 * func_ov143_0229a868 @ 0x0229a868, 0x74 bytes, Thumb
 * func_ov143_0229a7fc @ 0x0229a7fc, 0x6c bytes, Thumb
 * func_ov143_0229a76c @ 0x0229a76c, 0x90 bytes, Thumb
 * func_ov143_0229a6f8 @ 0x0229a6f8, 0x74 bytes, Thumb
 * func_ov143_0229a67c @ 0x0229a67c, 0x7c bytes, Thumb
 * func_ov143_0229a5cc @ 0x0229a5cc, 0xb0 bytes, Thumb
 */

#include "types.h"

struct FlagsStruct {
    char pad_00[2];
    unsigned short flags;
};

typedef struct UnkStruct_0229a5cc UnkStruct_0229a5cc;

struct UnkStruct_0229a5cc {
    unsigned char pad_00[0xa0];
    unsigned char *array; // 0xa0
    unsigned char unk_A4; // 0xa4
    unsigned char pad_A5[0xac - 0xa5];
};

extern void func_020b9ccc(void *);
extern void func_ov143_02299a38(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov143_02299bd0(void *parameter0);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int data_021fbe94;
extern const unsigned char data_ov143_0229b260[];
extern const unsigned char data_ov143_0229b274[];
extern const unsigned char data_ov143_0229b288[];
extern const unsigned char data_ov143_0229b2a0[];
extern int func_02002c6c(const unsigned char *, int, int, int, int, int);
extern int func_02002d14(const unsigned char *, int, int, int, int, int);
extern int func_02002ca4(const unsigned char *, int, int);
extern int func_02064af4(const unsigned char *, const unsigned char *, int);
extern int func_02002b40(const unsigned char *, int, int, int);
extern void func_ov002_0220af94(void *receiver);
extern char data_ov143_0229b220;
extern char data_ov143_0229b234;
extern char data_ov143_0229b24c;
extern int func_ov002_02208054(void *self, int a);
extern void func_ov143_0229a300(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov143_02299ed8(void *self, int a, int b);
extern int func_ov143_02299e18(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov143_0229a230(void *self);
extern void func_ov143_0229a200(void *self);
extern void func_ov143_0229a2e0(void *self);
extern int _s32_div_f(int diff, int b);
extern unsigned char func_ov143_022997b0(void *self, unsigned char clamp);
extern void func_0206e9ac(int value);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern int func_ov143_02299c14(void *, int);
extern void func_ov143_0229a31c(void *);
extern void func_ov143_02299fd0(void *);
extern void func_ov143_02299f6c(void *);
extern void func_ov143_0229a014(void *);
extern struct FlagsStruct data_021fbe40;
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern unsigned char func_ov143_022997d8(UnkStruct_0229a5cc *self, unsigned char b);
extern int func_ov143_0229a0b0(UnkStruct_0229a5cc *self);
extern int func_ov143_0229a030(UnkStruct_0229a5cc *self);
extern void func_ov002_0220a0b4(void *s, int a, int b);
extern void func_ov143_02299f48(UnkStruct_0229a5cc *self);

void func_ov143_0229a914(void *arg0);

void func_ov143_0229a944(void *arg0)
{
    func_ov143_0229a914((void *) arg0);
}

void func_ov143_0229a91c(void *self)
{
    func_020b9ccc((char *) self + 0x119c);
    func_ov143_02299a38(self);
    func_ov002_0220af74((char *) self + 0x110);
}

void func_ov143_0229a914(void *arg0)
{
    func_ov143_02299bd0((void *) arg0);
}

void func_ov143_0229a8dc(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov143_0229a868(unsigned char *arg0)
{
    int g = data_021fbe94;
    func_02002c6c(data_ov143_0229b260, g, 6, 0x11, 0x11, 0x9c);
    func_02002d14(data_ov143_0229b274, g, 6, 1, 1, 6);
    func_02002ca4(data_ov143_0229b288, g, 6);
    func_02064af4(data_ov143_0229b2a0, arg0 + 0x99c, 0x800);
    func_02002b40(arg0 + 0x99c, 4, 0x800, 0);
}

void func_ov143_0229a7fc(int arg0)
{
    int r4;
    func_ov002_0220af94((void *) (arg0 + 0x110));
    r4 = data_021fbe94;
    func_02002c6c((const unsigned char *) (&data_ov143_0229b220), r4, 8, 0xc0, 0xc0, 0xff);
    func_02002c6c((const unsigned char *) (&data_ov143_0229b234), r4, 8, 0x140, 0x140, 0x1bf);
    func_02002d14((const unsigned char *) (&data_ov143_0229b24c), r4, 8, 4, 4, 0xd);
}

void func_ov143_0229a76c(char *self)
{
    unsigned int ok;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov143_0229a300(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov143_02299ed8(self, data_021f6c58, data_021f6c54);
    if (n != 0x16) {
        func_ov143_02299e18(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x110, 1) != 0) {
        func_ov143_0229a230(self);
        return;
    }
    if (func_ov002_0220a784(self + 0x110, 2) != 0) {
        func_ov143_0229a200(self);
    }
}

void func_ov143_0229a6f8(unsigned char *self)
{
    int diff, r1;
    unsigned char idx;
    unsigned char *base;
    unsigned char old, cur;

    if ((*(unsigned char *) &data_021fbdd8) == 0) {
        func_ov143_0229a2e0(self);
        return;
    }

    diff = *(int *) (self + 0xa8) - (*(unsigned char *) &data_021f6c54);
    r1 = self[0xa5] + _s32_div_f(diff, 3);
    if (r1 < 0) {
        r1 = 0;
    } else if (r1 > 0xf) {
        r1 = 0xf;
    }

    idx = self[0xa4];
    base = *(unsigned char **) (self + 0xa0);
    old = base[idx];

    cur = func_ov143_022997b0(self, (unsigned char) r1);
    if (old == cur) {
        return;
    }

    func_0206e9ac((int) cur);
    base = *(unsigned char **) (self + 0xa0);
    base[idx] = cur;
}

void func_ov143_0229a67c(void *p)
{
    if (func_ov002_02208014(p)) {
        func_ov143_0229a31c(p);
        return;
    }
    {
        int tmp = func_ov002_02208008(p);
        if (func_ov143_02299c14(p, tmp)) {
            func_ov143_02299fd0(p);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40.flags;
        if (flags & 1) {
            func_ov143_02299f6c(p);
            return;
        }
        if (flags & 2) {
            func_ov143_0229a014(p);
            func_ov143_0229a200(p);
            return;
        }
        if (flags & 8) {
            func_ov143_0229a014(p);
            func_ov143_0229a230(p);
        }
    }
}

void func_ov143_0229a5cc(UnkStruct_0229a5cc *self)
{
    if ((*(unsigned short *) &data_021fbe40) & 1) {
        void *p = (void *) func_ov002_02208008((void *) self);
        if (p) {
            unsigned char r6 = self->unk_A4;
            unsigned char r4 = func_ov143_022997d8(self, self->array[r6]);
            unsigned char r7 = r4;

            if (func_ov002_022088cc(p)) {
                if (r4 < 15) {
                    r4 = (unsigned char) (r4 + 1);
                }
            } else if (func_ov002_022088bc(p)) {
                if (r4 != 0) {
                    r4 = (unsigned char) (r4 - 1);
                }
            }

            if (r4 != r7) {
                self->array[r6] = func_ov143_022997b0((void *) self, r4);
                func_0206e9ac((unsigned char) self->array[r6]);
                {
                    int a = func_ov143_0229a0b0(self);
                    int b = func_ov143_0229a030(self);
                    func_ov002_0220a0b4((char *) self + 0xac, a, b);
                }
            }
        }
    } else {
        func_ov143_0229a2e0((void *) self);
        func_ov143_02299f48(self);
    }
}
