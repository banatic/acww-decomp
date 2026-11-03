/* mailbox_scene_4: 18 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229d6a4 @ 0x0229d6a4, 0x20 bytes, Thumb
 * func_ov106_0229d60c @ 0x0229d60c, 0x98 bytes, Thumb
 * func_ov106_0229d5c4 @ 0x0229d5c4, 0x48 bytes, Thumb
 * func_ov106_0229d57c @ 0x0229d57c, 0x48 bytes, Thumb
 * func_ov106_0229d518 @ 0x0229d518, 0x64 bytes, Thumb
 * func_ov106_0229d4e4 @ 0x0229d4e4, 0x32 bytes, Thumb
 * func_ov106_0229d4ac @ 0x0229d4ac, 0x38 bytes, Thumb
 * func_ov106_0229d48c @ 0x0229d48c, 0x20 bytes, Thumb
 * func_ov106_0229d454 @ 0x0229d454, 0x38 bytes, Thumb
 * func_ov106_0229d414 @ 0x0229d414, 0x40 bytes, Thumb
 * func_ov106_0229d3e8 @ 0x0229d3e8, 0x2c bytes, Thumb
 * func_ov106_0229d3bc @ 0x0229d3bc, 0x2c bytes, Thumb
 * func_ov106_0229d3b0 @ 0x0229d3b0, 0xc bytes, Thumb
 * func_ov106_0229d3a0 @ 0x0229d3a0, 0x10 bytes, Thumb
 * func_ov106_0229d390 @ 0x0229d390, 0x10 bytes, Thumb
 * func_ov106_0229d384 @ 0x0229d384, 0xc bytes, Thumb
 * func_ov106_0229d360 @ 0x0229d360, 0x24 bytes, Thumb
 * func_ov106_0229d340 @ 0x0229d340, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229d60c {
    char pad_00[0xa4];
    int x;
    int y;
    char pad_AC[0x09];
    unsigned char b5;
    unsigned char b6;
    char pad_B7[0x08];
    unsigned char bf;
    char pad_C0[0x20f8];
    char region[1];
} UnkStruct_0229d60c;

struct UnkStruct_0229d4ac {
    unsigned char pad_00[0xac];
    int unk_AC;
    int unk_B0;
};

struct UnkStruct_0229d3bc {
    unsigned char pad_00[0xbe];
    unsigned char flag;
    unsigned char pad_BF[0x3ef5];
    unsigned char data[4];
};

extern int func_0206fe60(void);
extern void func_ov106_0229d6c4(int arg);
extern void func_ov106_0229d724(int arg);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov106_0229d170(void *self, int);
extern int func_ov106_0229d128(void *self, int);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207d00(void *);
extern int func_ov106_0229d0d0(void *self, int);
extern void func_ov106_0229c344(void *self, int);
extern void func_ov106_0229c354(void *self, int);
extern void func_ov094_022999cc(void);
extern int func_ov002_02207d24(void *ptr, int value);
extern void func_ov106_0229cd88(void *ptr, int value);
extern void func_ov106_0229ce38(void *ptr);
extern void func_ov094_022999c0(void);
extern void func_ov106_0229ce0c(u8 *);
extern void func_ov002_02209d68(void *, int, int);
extern int func_ov002_02209d38(void *, int, int, int);
extern int func_ov002_02209d8c(void *);
extern void func_ov106_0229cde4(void *);
extern int func_0209a1e8(void);
extern int func_02065ec0(void *p);
extern unsigned char data_021f43ec;
extern void func_ov002_0220b830(void *arg1, void *arg2, int arg3);
extern void func_ov002_02207e9c(void *arg1, int arg2, int arg3);
extern void func_0200467c(int cmd);
extern void *func_ov002_0220a720(void *ptr, int val);
extern void func_020b9ccc(void *p);

int func_ov106_0229d48c(int param);
int func_ov106_0229d390(unsigned int a, unsigned int b);

void func_ov106_0229d6a4(int arg)
{
    if (func_0206fe60() != 0) {
        func_ov106_0229d724(arg);
    } else {
        func_ov106_0229d6c4(arg);
    }
}

void func_ov106_0229d60c(UnkStruct_0229d60c *self, int val)
{
    unsigned char g58;
    unsigned char g54;

    self->b5 = val;
    func_ov002_02208098((void *) (self), 1);
    g58 = data_021f6c58;
    g54 = data_021f6c54;
    self->x = func_ov106_0229d170(self, self->b5) - g58;
    self->y = func_ov106_0229d128(self, self->b5) - g54;
    self->b6 = val;
    func_ov002_02207cf8(self->region);
    func_ov002_02207d00(self->region);
    self->bf = 2;
    if (func_ov106_0229d0d0(self, val)) {
        func_ov106_0229c344(self, 4);
    } else {
        func_ov106_0229c354(self, 4);
        func_ov094_022999cc();
    }
}

void func_ov106_0229d5c4(void *p, int val)
{
    ((unsigned char *) p)[0xb7] = (unsigned char) val;
    func_ov002_02207d24((char *) p + 0x21b8, 1);
    func_ov106_0229cd88(p, val);
    if (((unsigned char *) p)[0xb4] == 1) {
        func_ov002_02208098((void *) (p), 4);
    }
    func_ov106_0229ce38(p);
    func_ov094_022999c0();
}

void func_ov106_0229d57c(u8 *self, int val)
{
    self[0xB7] = (u8) val;
    func_ov002_02207d24((void *) (self + 0x21b8), 1);
    func_ov106_0229cd88((void *) self, val);
    if (self[0xB4] == 1) {
        self[0xBB] = 8;
    }
    func_ov106_0229ce0c(self);
    func_ov094_022999c0();
}

void func_ov106_0229d518(char *self, int p2, int p3)
{
    int a, b;
    self[0xB7] = (char) p2;
    func_ov002_02209d68(self + 0x2288, *(int *) (self + 0xac), *(int *) (self + 0xb0));
    a = func_ov106_0229d170(self, p2);
    b = func_ov106_0229d128(self, p2);
    func_ov002_02209d38(self + 0x2288, a, b, p3);
    func_ov002_02209d8c(self + 0x2288);
    func_ov106_0229cde4(self);
    func_ov002_02208098((void *) (self), 0x15);
}

void func_ov106_0229d4e4(void *a, int b, int c)
{
    int v = 0x20;
    if (c >= 0xc0) {
        if (func_ov106_0229d390((unsigned int) a, b)) {
            v = func_ov106_0229d48c((int) a);
        }
    }
    if (v != 0x20) {
        b = v;
    }
    func_ov106_0229d518((char *) a, b, 4);
}

void func_ov106_0229d4ac(struct UnkStruct_0229d4ac *self, int a, int b)
{
    func_ov106_0229cd88(self, a);
    self->unk_AC = func_ov106_0229d170(self, a);
    self->unk_B0 = func_ov106_0229d128(self, a);
    func_ov106_0229d518((char *) self, b, 4);
}

int func_ov106_0229d48c(int param)
{
    int r = func_0209a1e8();
    if (r == -1) {
        return 0x20;
    } else {
        return (unsigned char) (r + 11);
    }
}

int func_ov106_0229d454(void *base)
{
    char *p = (char *) base + 0x2bb4;
    int i;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p)) {
            i += 0x15;
            return (unsigned char) i;
        }
        p += 0x100;
    }
    return 0x20;
}

void func_ov106_0229d414(void *obj, char c)
{
    char local;
    local = data_021f43ec;
    local = c;
    func_ov002_0220b830((char *) obj + 0x26f8, &local, 1);
    func_ov002_02208098((void *) (obj), 0x1a);
    func_ov002_02207e9c(obj, 0, 0);
}

void func_ov106_0229d3e8(void *self)
{
    func_0200467c(0x27);
    func_ov002_0220a720((char *) self + 0x3fb4, 3);
    func_ov002_02208098((void *) (self), 0x1f);
    ((char *) self)[0xbe] = 0;
}

void func_ov106_0229d3bc(struct UnkStruct_0229d3bc *p)
{
    func_0200467c(0x28);
    func_ov002_0220a720(p->data, 4);
    func_ov002_02208098((void *) (p), 0x1f);
    p->flag = 1;
}

void func_ov106_0229d3b0(void *p)
{
    func_020b9ccc((char *) p + 0xc0);
}

int func_ov106_0229d3a0(int a, unsigned int b)
{
    if (b >= 0xb && b <= 0x14) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov106_0229d390(unsigned int a, unsigned int b)
{
    if (b >= 0x15 && b <= 0x1e) {
        return 1;
    }
    return 0;
}

int func_ov106_0229d384(int param1, int param2)
{
    if (param2 == 31) {
        return 1;
    }
    return 0;
}

unsigned char func_ov106_0229d360(unsigned int arg0, unsigned int x)
{
    if (x >= 11 && x <= 20) {
        x -= 11;
        return (unsigned char) x;
    } else if (x >= 21 && x <= 30) {
        x += 14;
        return (unsigned char) x;
    }
    return 0;
}

unsigned char func_ov106_0229d340(unsigned char r0, unsigned char r1)
{
    if (r1 <= 9) {
        return (unsigned char) (r1 + 11);
    }
    if (r1 >= 0x23 && r1 <= 0x2c) {
        return (unsigned char) (r1 - 14);
    }
    return 0x20;
}
