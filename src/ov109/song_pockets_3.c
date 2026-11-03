/* song_pockets_3: 48 functions, module ov109
 * mwccarm 1.2/base -O4,s
 * func_ov109_0229d4b4 @ 0x0229d4b4, 0x8 bytes, Thumb
 * func_ov109_0229d478 @ 0x0229d478, 0x3c bytes, Thumb
 * func_ov109_0229d440 @ 0x0229d440, 0x38 bytes, Thumb
 * func_ov109_0229d420 @ 0x0229d420, 0x1e bytes, Thumb
 * func_ov109_0229d40c @ 0x0229d40c, 0x14 bytes, Thumb
 * func_ov109_0229d3e8 @ 0x0229d3e8, 0x24 bytes, Thumb
 * func_ov109_0229d368 @ 0x0229d368, 0x80 bytes, Thumb
 * func_ov109_0229d2d0 @ 0x0229d2d0, 0x98 bytes, Thumb
 * func_ov109_0229d2a0 @ 0x0229d2a0, 0x30 bytes, Thumb
 * func_ov109_0229d258 @ 0x0229d258, 0x48 bytes, Thumb
 * func_ov109_0229d1b0 @ 0x0229d1b0, 0xa8 bytes, Thumb
 * func_ov109_0229d0d4 @ 0x0229d0d4, 0xdc bytes, Thumb
 * func_ov109_0229d048 @ 0x0229d048, 0x8c bytes, Thumb
 * func_ov109_0229cff8 @ 0x0229cff8, 0x50 bytes, Thumb
 * func_ov109_0229cfb4 @ 0x0229cfb4, 0x44 bytes, Thumb
 * func_ov109_0229cf7c @ 0x0229cf7c, 0x38 bytes, Thumb
 * func_ov109_0229cf54 @ 0x0229cf54, 0x28 bytes, Thumb
 * func_ov109_0229cf18 @ 0x0229cf18, 0x3c bytes, Thumb
 * func_ov109_0229cec8 @ 0x0229cec8, 0x50 bytes, Thumb
 * func_ov109_0229cea8 @ 0x0229cea8, 0x20 bytes, Thumb
 * func_ov109_0229ce78 @ 0x0229ce78, 0x30 bytes, Thumb
 * func_ov109_0229ce14 @ 0x0229ce14, 0x64 bytes, Thumb
 * func_ov109_0229cdf8 @ 0x0229cdf8, 0x1c bytes, Thumb
 * func_ov109_0229cdbc @ 0x0229cdbc, 0x3c bytes, Thumb
 * func_ov109_0229cd9c @ 0x0229cd9c, 0x20 bytes, Thumb
 * func_ov109_0229cd10 @ 0x0229cd10, 0x8c bytes, Thumb
 * func_ov109_0229cccc @ 0x0229cccc, 0x44 bytes, Thumb
 * func_ov109_0229ccc0 @ 0x0229ccc0, 0xc bytes, Thumb
 * func_ov109_0229ccb4 @ 0x0229ccb4, 0xc bytes, Thumb
 * func_ov109_0229cc98 @ 0x0229cc98, 0x1a bytes, Thumb
 * func_ov109_0229cc88 @ 0x0229cc88, 0xe bytes, Thumb
 * func_ov109_0229cc4c @ 0x0229cc4c, 0x3a bytes, Thumb
 * func_ov109_0229cc0c @ 0x0229cc0c, 0x3e bytes, Thumb
 * func_ov109_0229cbd4 @ 0x0229cbd4, 0x36 bytes, Thumb
 * func_ov109_0229cb9c @ 0x0229cb9c, 0x38 bytes, Thumb
 * func_ov109_0229cb10 @ 0x0229cb10, 0x8c bytes, Thumb
 * func_ov109_0229cae0 @ 0x0229cae0, 0x2e bytes, Thumb
 * func_ov109_0229cab0 @ 0x0229cab0, 0x2e bytes, Thumb
 * func_ov109_0229ca7c @ 0x0229ca7c, 0x34 bytes, Thumb
 * func_ov109_0229ca4c @ 0x0229ca4c, 0x2e bytes, Thumb
 * func_ov109_0229ca30 @ 0x0229ca30, 0x1c bytes, Thumb
 * func_ov109_0229c9f0 @ 0x0229c9f0, 0x40 bytes, Thumb
 * func_ov109_0229c988 @ 0x0229c988, 0x68 bytes, Thumb
 * func_ov109_0229c934 @ 0x0229c934, 0x54 bytes, Thumb
 * func_ov109_0229c8f8 @ 0x0229c8f8, 0x3c bytes, Thumb
 * func_ov109_0229c8a4 @ 0x0229c8a4, 0x54 bytes, Thumb
 * func_ov109_0229c85c @ 0x0229c85c, 0x48 bytes, Thumb
 * func_ov109_0229c84c @ 0x0229c84c, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C;
    char pad_218D[0x29d0 - 0x218d];
    unsigned char unk_29D0;
    char pad_29D1[0x29d9 - 0x29d1];
    unsigned char unk_29D9;
} UnkStruct_0229d2d0;

struct UnkStruct_0229cfb4 {
    char pad_00[0x2274];
    char flag_2274;
    char pad_2275[0x29d3 - 0x2275];
    unsigned char byte_d3;
    char pad_29D4[2];
    unsigned char byte_d6;
};

struct Context {
    char pad_00[0x218c];
    char sub[0x830];
    int unk_29BC;
    int unk_29C0;
    char pad_29C4[0xC];
    unsigned char unk_29D0;
    unsigned char unk_29D1;
    char pad_29D2[7];
    unsigned char unk_29D9;
};

typedef struct {
    char pad_00[0xcc];
    int unk_CC;
} UnkStruct_0229cc4c;

typedef struct UnkStruct_0229c988 {
    char pad_00[0xcc];
    char unk_CC;
    char pad_CD[0x218c - 0xcd];
    char unk_218C;
    char pad_218D[0x29d1 - 0x218d];
    unsigned char unk_29D1;
} UnkStruct_0229c988;

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C[1];
    char pad_218D[0x844];
    unsigned char unk_29D1;
    unsigned char unk_29D2;
    unsigned char unk_29D3;
} UnkStruct_0229c934;

typedef struct {
    char pad_00[0x29d3];
    unsigned char unk_29D3;
} UnkStruct_0229c84c;

extern void func_ov094_0229a084(void *ptr);
extern void func_ov094_0229af20(void *ptr);
extern void func_ov094_0229bbc0(void *ptr);
extern void func_ov002_0220af74(void *ptr);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int a, int b);
extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_02208054(void *self, int flag);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_0220a784(void *ptr, int x);
extern void func_ov109_0229c4cc(void *arg);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_02207ce4(void *p, int a);
extern void func_ov109_0229d7b4(void *p);
extern int func_ov002_02207cc0(int);
extern void func_ov109_0229c418(void *p, int a, int b);
extern void func_ov002_02207d00(void *p);
extern int func_0206f56c(void);
extern int func_ov002_02208e28(const void *);
extern void func_ov109_0229c534(const void *);
extern int func_ov002_02208b00(const void *, unsigned char, unsigned char);
extern void func_ov002_02209114(const void *, int, int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(unsigned char *self);
extern int func_ov002_02207d24(unsigned char *addr, int val);
extern int func_ov109_0229c2c4(unsigned char *self, int val);
extern void func_ov109_0229c7b0(unsigned char *self);
extern void func_ov109_0229c638(unsigned char *self);
extern void func_ov109_0229c828(unsigned char *self);
extern unsigned short data_021fbe40[];
extern int func_ov002_02209044(const void *, int, const void *, int);
extern void func_ov109_0229c75c(const void *);
extern void func_ov002_0220a1dc(const void *);
extern int func_ov109_0229c6f8(const void *);
extern int func_0208e484(void *ptr);
extern int func_ov002_02209f64(void *);
extern void *func_ov002_0220a720(void *ptr, unsigned int value);
extern void func_0200467c(unsigned int command);
extern int func_ov109_0229c658(void *);
extern int func_0206fe54(void);
extern void func_ov109_0229c6ac(int);
extern int func_ov002_0220909c(char *a);
extern void func_ov002_022096d8(char *a, int b);
extern int func_0208e4bc(char *a);
extern void func_ov109_0229c678(char *a);
extern void func_ov109_0229c5d4(void *);
extern int func_ov002_02208e18(void *);
extern int func_ov002_0220b8ac(char *p, int v);
extern void func_0208e5cc(char *p);
extern int func_ov002_0220a700(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int x);
extern int func_ov002_0220a72c(void *p, int x);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov109_0229c498(unsigned int p);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void func_ov002_02207cf8(char *p);
extern void func_ov094_022999cc(void);
extern volatile unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *, void *, int, int);
extern void func_0208e5c4(void *);
extern void func_020b9ccc(void *self);
extern int func_ov094_0229aee8(void *ptr, int arg1, int arg2);
extern int func_ov094_0229a69c(void *ptr, int v);
extern void func_ov094_0229aa14(char *a, int val, void *c, void *d);
extern void func_ov094_0229a9b4(char *a, int val);
extern int func_ov094_0229aba4(void *, int);
extern int func_ov094_0229ab90(int a, int b);
extern void func_ov094_0229a888(u8 *p, int v);
extern int func_ov094_0229a8bc(char *ptr, int value);
extern int func_ov094_0229aaac(int, int);
extern int func_ov094_0229aa84(void *a, int b);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229ab1c(void *object, int index);
extern void func_0208aa60(void *dst, int a, int b);
extern void func_ov094_0229abb8(void *dst, void *src, int val);
extern void func_ov002_02207cf0(unsigned char *p);
extern int func_ov109_0229c2ac(void *self, int b);
extern void func_ov094_0229a6bc(void *addr, unsigned int x, unsigned int y);
extern void func_ov002_0220a374(unsigned char *a, int b);

void func_ov109_0229d440(void *self);
void func_ov109_0229cdf8(int arg);
void func_ov109_0229cdbc(void *r0);
void func_ov109_0229cd9c(int r0);
void func_ov109_0229cd10(struct Context *self, int arg);
void func_ov109_0229ccc0(void *self);
int func_ov109_0229ccb4(int unused, unsigned int b);
int func_ov109_0229cc4c(UnkStruct_0229cc4c *p1, int a, int b, int c);
int func_ov109_0229cbd4(int a, int b);
int func_ov109_0229cb9c(int p1, int p2);
int func_ov109_0229cae0(void *a0, void *a1);
int func_ov109_0229cab0(void *a, int b);
int func_ov109_0229ca7c(int a, int b);
int func_ov109_0229ca4c(void *a, int b);
void func_ov109_0229ca30(void *self);
void func_ov109_0229c9f0(void *object, unsigned int index);
void func_ov109_0229c988(UnkStruct_0229c988 *p);
void func_ov109_0229c934(UnkStruct_0229c934 *s);
void func_ov109_0229c8a4(unsigned char *p);
int func_ov109_0229c85c(void *self);
int func_ov109_0229c84c(UnkStruct_0229c84c *p);

void func_ov109_0229d4b4(void *arg0)
{
    func_ov109_0229d440((void *) arg0);
}

void func_ov109_0229d478(void *arg)
{
    char *p;

    func_ov109_0229ccc0(arg);
    func_ov094_0229a084((char *) arg + 0x0b54);
    p = (char *) arg;
    p += 0xcc;
    func_ov094_0229af20(p);
    func_ov094_0229bbc0((char *) arg + 0x0b2c);
    func_ov002_0220af74((char *) arg + 0x27e8);
}

void func_ov109_0229d440(void *self)
{
    func_ov002_022091cc((char *) self + 0x22d8);
    func_ov094_0229a05c((char *) self + 0xb54);
    if (func_ov002_02207d5c((char *) self + 0x218c)) {
        func_ov109_0229c988((UnkStruct_0229c988 *) self);
    }
}

void func_ov109_0229d420(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov109_0229d40c(int a)
{
    func_ov094_0229a29c(a + 0xb54, 0);
}

void func_ov109_0229d3e8(void *self)
{
    func_ov094_0229a098((void *) ((char *) self + 0xb54));
    func_ov002_0220af94((void *) ((char *) self + 0x27e8));
}

void func_ov109_0229d368(void *self)
{
    int result;
    int cond;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov109_0229cdbc(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto isfalse;
    }
    if (data_021fbddc == 0) {
        goto isfalse;
    }
    cond = 1;
    goto done;
isfalse:
    cond = 0;
done:
    if (cond == 0) {
        return;
    }
    result = func_ov109_0229cc4c((UnkStruct_0229cc4c *) ((char *) self), data_021f6c58, data_021f6c54 + 0x10, 1);
    if (result != 0x10) {
        func_ov109_0229cd10((struct Context *) self, result);
        return;
    }
    if (func_ov002_0220a784((char *) self + 0x27e8, 9) != 0) {
        func_ov109_0229c4cc(self);
    }
}

void func_ov109_0229d2d0(UnkStruct_0229d2d0 *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov109_0229cae0(self, (void *) self->unk_29D0) != 0) {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4(&self->unk_218C, 0x3c);
            return;
        }
        func_ov002_02208098(self, 3);
        func_ov109_0229d7b4(self);
        return;
    }
    if (func_ov109_0229cae0(self, (void *) self->unk_29D0) != 0) {
        goto L34a;
    }
    if (func_ov002_02207cc0((int) &self->unk_218C) == 0) {
        goto L34a;
    }
    if (self->unk_29D9 != 0) {
        self->unk_29D9--;
    } else {
        func_ov109_0229c418(self, self->unk_29D0, 1);
        func_ov002_02208098(self, 2);
    }
    goto L352;
L34a:
    func_ov002_02207d00(&self->unk_218C);
L352:;
}

void func_ov109_0229d2a0(int arg0)
{
    if (func_0206f56c() != 0) {
        func_ov002_02208098((void *) arg0, 4);
    } else {
        if (data_021fbdd8 == 0) {
            func_ov002_02208098((void *) arg0, 4);
        }
    }
}

void func_ov109_0229d258(unsigned char *self)
{
    if (func_ov002_02207cc0((int) self + 0x218c) != 0) {
        if (self[0x29d9] != 0) {
            self[0x29d9]--;
        } else {
            func_ov109_0229c418(self, (unsigned char) self[0x29d0], 1);
            func_ov002_02208098(self, 2);
        }
    }
}

void func_ov109_0229d1b0(unsigned char *self)
{
    unsigned int flag;
    int idx;
    unsigned char *base;

    if (func_ov002_02208e28(self + 0x22d8) == 0) {
        return;
    }

    if (func_0206f56c() != 0) {
        func_ov109_0229c534(self);
        return;
    }

    if (func_ov002_02208054((void *) self, 1) != 0) {
        func_ov109_0229c534(self);
        return;
    }

    flag = 0;
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        flag = 1;
    }

    if (flag > 0) {
        idx = func_ov002_02208b00(self + 0x22d8, data_021f6c58, data_021f6c54);
        if (idx < 0) {
            return;
        }
        func_ov002_02209114(self + 0x22d8, idx, 1);
        base = self + idx;
        self[0x29d7] = base[0x26c5];
        func_ov002_02208098((void *) self, 0xc);
    }
}

void func_ov109_0229d0d4(unsigned char *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov109_0229cdf8((int) self);
        func_ov002_02207d24(self + 0x218c, 1);
        return;
    }

    {
        int r = func_ov002_02208008(self);
        if (func_ov109_0229c2c4(self, r) != 0) {
            func_ov109_0229c934((UnkStruct_0229c934 *) self);
            func_ov109_0229c7b0(self);
            func_ov002_02207d24(self + 0x218c, 0);
            return;
        }
    }

    if (func_ov109_0229cae0((void *) self, (void *) self[0x29d3]) != 0) {
        // nothing
    } else {
        if ((data_021fbe40[1] & 1) != 0) {
            if (func_ov109_0229ccb4((int) self, (unsigned char) self[0x29d3]) != 0) {
                if (func_ov109_0229cab0((void *) self, (unsigned char) self[0x29d3]) == 0) {
                    func_ov109_0229c418((void *) self, (unsigned char) self[0x29d3], 0);
                }
                return;
            } else {
                if (self[0x29d3] == 0xf) {
                    func_ov109_0229c638(self);
                }
                return;
            }
        }
    }

    if ((data_021fbe40[1] & 2) != 0) {
        func_ov109_0229c828(self);
        func_ov109_0229c4cc((void *) self);
        func_ov002_02207d24(self + 0x218c, 0);
    } else {
        func_ov002_02207d00((void *) (self + 0x218c));
    }
}

void func_ov109_0229d048(void *arg)
{
    int v;
    unsigned short flags;

    if (func_0206f56c() != 0) {
        func_ov109_0229c534(arg);
        return;
    }
    if (func_ov002_02208014(arg) != 0) {
        func_ov109_0229c534(arg);
        return;
    }
    v = func_ov002_02208008((unsigned char *) arg);
    if (func_ov002_02209044((char *) arg + 0x22d8, v, (char *) arg + 0x29d8, 0) != 0) {
        func_ov109_0229c75c(arg);
        return;
    }
    flags = data_021fbe40[1];
    if (flags & 1) {
        func_ov002_0220a1dc((char *) arg + 0x2274);
        func_ov002_02208098((void *) arg, 7);
        return;
    }
    if (flags & 2) {
        func_ov109_0229c6f8(arg);
        return;
    }
}

void func_ov109_0229cff8(void *p)
{
    unsigned char *base;
    unsigned char *q;
    if (func_0208e484((char *) p + 0x2274) == 0) {
        return;
    }
    base = (unsigned char *) p;
    func_ov002_02209114((const void *) ((char *) p + 0x22d8), (unsigned char) base[0x29d8], 1);
    q = base + base[0x29d8];
    base[0x29d7] = q[0x26c5];
    func_ov002_02208098(p, 0xc);
}

void func_ov109_0229cfb4(struct UnkStruct_0229cfb4 *self)
{
    if (func_ov002_02209f64(&self->flag_2274) != 0) {
        return;
    }
    func_ov002_02208098((void *) self, self->byte_d6);
    if (self->byte_d6 == 5) {
        func_ov109_0229c9f0((void *) self, self->byte_d3);
    }
    func_ov109_0229d7b4((void *) self);
}

void func_ov109_0229cf7c(void *p)
{
    if (func_0208e484((char *) p + 0x2274)) {
        func_ov002_0220a720((char *) p + 0x27e8, 9);
        func_ov002_02208098(p, 15);
        func_0200467c(0x28);
    }
}

void func_ov109_0229cf54(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x2274)) {
        func_ov109_0229c658(arg0);
        func_ov002_02208098(arg0, 5);
    }
}

void func_ov109_0229cf18(int r0)
{
    int r4 = r0;
    if (func_ov002_02208e28((const void *) (r4 + 0x22d8)) != 0) {
        if (func_0206fe54() != 0) {
            func_ov109_0229c6ac(r4);
            func_ov002_02208098((void *) r4, 6);
        } else {
            func_ov002_02208098((void *) r4, 4);
        }
    }
}

void func_ov109_0229cec8(char *obj)
{
    if (func_ov002_0220909c(obj + 0x22d8)) {
        func_ov002_022096d8(obj + 0x22d8, 0);
        func_ov002_02207d24((unsigned char *) (obj + 0x218c), 1);
        if (func_0208e4bc(obj + 0x2274)) {
            func_ov109_0229c678(obj);
        }
        func_ov002_02208098((void *) obj, 0xd);
    }
}

void func_ov109_0229cea8(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x22d8)) {
        func_ov109_0229c5d4(self);
    }
}

void func_ov109_0229ce78(char *arg)
{
    if (func_ov002_0220b8ac(arg + 0x26cc, 1) != 0) {
        func_ov109_0229cd9c((int) arg);
        func_0208e5cc(arg + 0x2274);
    }
}

void func_ov109_0229ce14(unsigned int p)
{
    if (func_ov002_0220a700((void *) (p + 0x27e8)) != 0) {
        if (func_0208e4bc((char *) ((void *) (p + 0x2274))) != 0) {
            int a = func_ov002_0220a6e0((void *) (p + 0x27e8));
            int b = func_ov002_0220a768((void *) (p + 0x27e8), -1);
            int c = func_ov002_0220a72c((void *) (p + 0x27e8), -1);
            func_ov002_0220a0b4((void *) (p + 0x2274), a + b, a + c);
        }
    } else {
        func_ov109_0229c498(p);
    }
}

void func_ov109_0229cdf8(int arg)
{
    func_ov109_0229c828((unsigned char *) arg);
    func_ov109_0229ca30((void *) arg);
    func_ov002_02208098((void *) arg, 0);
}

void func_ov109_0229cdbc(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    p[0x29d1] = 0x10;
    func_ov109_0229c8a4((unsigned char *) r0);
    func_ov002_02207fc0(r0);
    func_ov109_0229c934((UnkStruct_0229c934 *) r0);
    func_ov002_02208098(r0, 5);
    func_ov109_0229c9f0(r0, p[0x29d3]);
}

void func_ov109_0229cd9c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov109_0229cdf8(r4);
    } else {
        func_ov109_0229cdbc((void *) r4);
    }
}

void func_ov109_0229cd10(struct Context *self, int arg)
{
    unsigned char g1;
    unsigned char g2;

    self->unk_29D0 = arg;
    func_ov002_02208098(self, 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;

    self->unk_29BC = func_ov109_0229cbd4((int) self, self->unk_29D0) - g1;
    self->unk_29C0 = func_ov109_0229cb9c((int) self, self->unk_29D0) - g2;
    self->unk_29D1 = arg;
    func_ov002_02207cf8(self->sub);
    func_ov002_02207d00((void *) self->sub);
    self->unk_29D9 = 2;
    if (func_ov109_0229cae0(self, (void *) arg) == 0) {
        func_ov094_022999cc();
    }
}

void func_ov109_0229cccc(unsigned char *obj, unsigned char arg)
{
    char b;

    b = data_021f43ec;
    b = arg;
    func_ov002_0220b9b8(obj + 0x26cc, &b, 1, 0);
    func_ov002_02208098(obj, 0xe);
    func_0208e5c4(obj + 0x2274);
}

void func_ov109_0229ccc0(void *self)
{
    func_020b9ccc((char *) self + 0x94);
}

int func_ov109_0229ccb4(int unused, unsigned int b)
{
    if (b > 14) {
        return 0;
    }
    return 1;
}

unsigned char func_ov109_0229cc98(int a, int b)
{
    if (func_ov109_0229ccb4(a, b)) {
        return (unsigned char) b;
    } else {
        return 0;
    }
}

int func_ov109_0229cc88(int unused, unsigned int b)
{
    if (b <= 14) {
        return (unsigned char) b;
    } else {
        return 16;
    }
}

int func_ov109_0229cc4c(UnkStruct_0229cc4c *p1, int a, int b, int c)
{
    int v;
    v = func_ov094_0229aee8(&p1->unk_CC, a, b);
    if (v == 0x23) {
        goto ret1;
    }
    if (c != 0 && func_ov094_0229a69c(&p1->unk_CC, v) != 0) {
        return 0x10;
    }
    return func_ov109_0229cc88((int) p1, v);
ret1:
    return 0x10;
}

void func_ov109_0229cc0c(char *a, void *b, void *c, void *d)
{
    if (func_ov109_0229ccb4((int) a, (unsigned int) b)) {
        int val;
        val = (int) func_ov109_0229cc98((int) a, (int) b);
        func_ov094_0229aa14(a + 0xcc, val, c, d);
        a += 0xcc;
        func_ov094_0229a9b4(a, val);
    }
}

int func_ov109_0229cbd4(int a, int b)
{
    if (func_ov109_0229ccb4(a, b)) {
        return func_ov094_0229aba4((void *) (a + 0xcc), (int) func_ov109_0229cc98(a, b));
    } else {
        if (b == 15) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}

int func_ov109_0229cb9c(int p1, int p2)
{
    if (func_ov109_0229ccb4(p1, p2)) {
        return func_ov094_0229ab90(p1 + 0xcc, (int) func_ov109_0229cc98(p1, p2)) - 0x10;
    }
    if (p2 == 0xf) {
        return 0xb6;
    }
    return 0;
}

void func_ov109_0229cb10(u8 *self)
{
    volatile u16 h;
    unsigned int hit;
    unsigned int ok;
    u16 v0, v1;
    unsigned char i;

    h = 0xfff1;
    for (i = 0; i <= 0xe; i++) {
        hit = 0;
        if (func_ov109_0229cab0((void *) self, i) == 0) {
            if (func_ov109_0229ca4c((void *) self, i) != 0) {
                hit = 1;
            } else {
                h = (u16) func_ov109_0229ca7c((int) self, i);
                ok = 0;
                v0 = h;
                v1 = h;
                if (v1 >= 0x1323 && v0 <= 0x1368) {
                    ok = 1;
                }
                if (ok == 0) {
                    hit = 1;
                }
            }
        }
        if (hit != 0) {
            func_ov094_0229a888(self + 0xcc, (int) func_ov109_0229cc98((int) self, i));
        }
    }
}

int func_ov109_0229cae0(void *a0, void *a1)
{
    if (func_ov109_0229ccb4((int) a0, (unsigned int) a1)) {
        int value = (int) func_ov109_0229cc98((int) a0, (int) a1);
        return func_ov094_0229a8bc((char *) a0 + 0xcc, value);
    }
    return 0;
}

int func_ov109_0229cab0(void *a, int b)
{
    if (func_ov109_0229ccb4((int) a, b)) {
        int v = (int) func_ov109_0229cc98((int) a, b);
        return func_ov094_0229a69c((char *) a + 0xcc, v);
    }
    return 1;
}

int func_ov109_0229ca7c(int a, int b)
{
    int result;
    if (func_ov109_0229ccb4(a, b) != 0) {
        result = func_ov094_0229aaac(a + 0xcc, (int) func_ov109_0229cc98(a, b));
    } else {
        result = 0x0000fff1;
    }
    return result;
}

int func_ov109_0229ca4c(void *a, int b)
{
    if (func_ov109_0229ccb4((int) a, b) != 0) {
        return func_ov094_0229aa84((char *) a + 0xcc, (int) func_ov109_0229cc98((int) a, b));
    } else {
        return 0xf1;
    }
}

void func_ov109_0229ca30(void *self)
{
    func_ov094_0229ab5c((char *) self + 0xcc);
    func_ov094_0229b98c((char *) self + 0xb2c);
}

void func_ov109_0229c9f0(void *object, unsigned int index)
{
    if (func_ov109_0229ccb4((int) object, index)) {
        func_ov094_0229ab1c((char *) object + 0xcc, func_ov109_0229cc98((int) object, index));
        func_ov094_0229b98c((char *) object + 0xb2c);
    } else {
        func_ov109_0229ca30(object);
    }
}

void func_ov109_0229c988(UnkStruct_0229c988 *p)
{
    int x;
    int b;
    int y;
    int val;

    x = func_ov109_0229cbd4((int) p, (unsigned char) p->unk_29D1) - 0x6d;
    b = func_ov109_0229cb9c((int) p, (unsigned char) p->unk_29D1);
    y = b - 0x78;
    if (func_0206fe54()) {
        y -= 8;
    }
    func_0208aa60(&p->unk_218C, x, y);
    if (func_ov109_0229ccb4((int) p, (unsigned char) p->unk_29D1)) {
        val = (int) func_ov109_0229cc98((int) p, (unsigned char) p->unk_29D1);
        func_ov094_0229abb8(&p->unk_CC, &p->unk_218C, val);
    }
}

void func_ov109_0229c934(UnkStruct_0229c934 *s)
{
    if (func_ov109_0229ccb4((int) s, (unsigned char) s->unk_29D3)) {
        if (func_ov109_0229cab0((void *) s, (unsigned char) s->unk_29D3)) {
            func_ov002_02207cf0(s->unk_218C);
        } else {
            s->unk_29D1 = s->unk_29D3;
            func_ov002_02207cf8((char *) s->unk_218C);
        }
    } else {
        func_ov002_02207cf0(s->unk_218C);
    }
}

void func_ov109_0229c8f8(void *self)
{
    unsigned char c;
    if (func_ov109_0229c2ac(self, 0x20) != 0) {
        return;
    }
    c = ((unsigned char *) self)[0x29cf];
    if (c == 0) {
        return;
    }
    if (c != 1) {
        return;
    }
    func_ov094_0229a6bc((void *) ((char *) self + 0xcc), *(unsigned int *) ((char *) self + 0x29c4),
                        *(unsigned int *) ((char *) self + 0x29c8));
}

void func_ov109_0229c8a4(unsigned char *p)
{
    int a, b;
    a = func_ov109_0229c85c((void *) p);
    b = func_ov109_0229c84c((UnkStruct_0229c84c *) p);
    func_ov002_0220a0b4((void *) (p + 0x2274), a, b);
    if (p[0x29d3] == 0xf) {
        func_ov002_0220a374(p + 0x2274, 7);
    } else {
        func_ov002_0220a374(p + 0x2274, 1);
    }
    func_ov109_0229c658((void *) p);
}

int func_ov109_0229c85c(void *self)
{
    int result = func_ov109_0229cbd4((int) self, (unsigned char) (*((unsigned char *) self + 0x29d3)));
    if (func_ov109_0229c2ac(self, 16) != 0) {
        result += 0x100;
    } else if (func_ov109_0229c2ac(self, 8) != 0) {
        result -= 0x100;
    }
    result += 8;
    return result;
}

int func_ov109_0229c84c(UnkStruct_0229c84c *p)
{
    return func_ov109_0229cb9c((int) p, p->unk_29D3);
}
