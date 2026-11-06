/* letter_storage_4: 16 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229d49c @ 0x0229d49c, 0x28 bytes, Thumb
 * func_ov105_0229d468 @ 0x0229d468, 0x34 bytes, Thumb
 * func_ov105_0229d428 @ 0x0229d428, 0x40 bytes, Thumb
 * func_ov105_0229d404 @ 0x0229d404, 0x24 bytes, Thumb
 * func_ov105_0229d3b4 @ 0x0229d3b4, 0x50 bytes, Thumb
 * func_ov105_0229d390 @ 0x0229d390, 0x24 bytes, Thumb
 * func_ov105_0229d354 @ 0x0229d354, 0x3c bytes, Thumb
 * func_ov105_0229d310 @ 0x0229d310, 0x44 bytes, Thumb
 * func_ov105_0229d294 @ 0x0229d294, 0x7c bytes, Thumb
 * func_ov105_0229d230 @ 0x0229d230, 0x64 bytes, Thumb
 * func_ov105_0229d1f0 @ 0x0229d1f0, 0x40 bytes, Thumb
 * func_ov105_0229d1c4 @ 0x0229d1c4, 0x2c bytes, Thumb
 * func_ov105_0229d17c @ 0x0229d17c, 0x48 bytes, Thumb
 * func_ov105_0229d154 @ 0x0229d154, 0x28 bytes, Thumb
 * func_ov105_0229d0f8 @ 0x0229d0f8, 0x5c bytes, Thumb
 * func_ov105_0229d0d4 @ 0x0229d0d4, 0x24 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x2b6];
    unsigned char b;
    char pad_2B7[0xd5c - 0x2b7];
    char arr0d5c[1];
    char pad_D5D[0x23bc - 0xd5c - 1];
    char arr23bc[1];
} UnkStruct_0229d294;

struct UnkStruct_0229d230 {
    char pad_00[0x2b6];
    unsigned char unk_2B6;
    char pad_2B7[3];
    unsigned char unk_2BA;
    char pad_2BB[0x23bc - 0x2bb];
    char sub;
};

struct UnkStruct_0229d1f0 {
    char pad_00[0xac];
    unsigned int unk_AC;
    unsigned int unk_B0;
    char pad_B4[0x200];
    unsigned char unk_2B4;
};

struct UnkStruct_0229d0f8 {
    u8 pad_00[0x2b4];
    u8 unk_2B4;
    u8 pad_2B5[0xAA7];
};

extern void func_ov094_0229a898(void *ptr, int val, int size);
extern void func_ov094_0229b794(void *ptr, int val);
extern int func_ov105_0229d718(char *, int);
extern int func_ov094_0229b788(char *, int);
extern int func_ov105_0229d75c(int, int);
extern int func_ov094_0229b30c(int, int);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern int func_ov105_0229d76c(int parameter0, unsigned int parameter1);
extern void func_ov094_0229b950(char *, int);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_0229b938(int, int);
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;
extern int func_ov105_0229d530(UnkStruct_0229d294 *, unsigned char);
extern int func_ov105_0229d4c4(UnkStruct_0229d294 *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa60(char *, int, int);
extern int func_ov094_0229b9b4(char *, char *, int);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);
extern int func_ov105_0229c340(void *p, int n);
extern void func_ov094_0229b5e8(void *a, unsigned int b, unsigned int c, void *d);
extern int func_ov002_02209f3c(char *);
extern int func_ov002_02209f14(char *);
extern int func_0208e4bc(char *);
extern unsigned int func_ov002_02209d84(void *p);
extern unsigned int func_ov002_02209d7c(void *p);
extern int func_ov094_0229b8d8(u8 *ptr, int arg);
extern int func_02066830(u8 *ptr, int arg);
extern void func_ov094_0229b890(u8 *ptr, int arg);
extern void func_ov105_0229d5dc(void *obj, void *arg1, void *ptr);

void func_ov105_0229d49c(void *self)
{
    func_ov094_0229a898((char *) self + 0x2fc, 0, 0xe);
    func_ov094_0229b794((char *) self + 0xd5c, 4);
}

int func_ov105_0229d468(char *arg1, int arg2)
{
    if (func_ov105_0229d76c((int) arg1, arg2)) {
        return func_ov094_0229b788(arg1 + 0xd5c, func_ov105_0229d718(arg1, arg2));
    } else {
        return 0;
    }
}

int func_ov105_0229d428(int a, int b)
{
    if (func_ov105_0229d76c(a, b) != 0 || func_ov105_0229d75c(a, b) != 0) {
        int c = func_ov105_0229d718((char *) a, b);
        return func_ov094_0229b30c(a + 0xd5c, c);
    } else {
        return 1;
    }
}

void func_ov105_0229d404(void *self)
{
    func_ov094_0229ab5c((char *) self + 0x2fc);
    func_ov094_0229b98c((char *) self + 0xd5c);
}

void func_ov105_0229d3b4(char *arg1, int arg2)
{
    if (func_ov105_0229d76c((int) (arg1), (unsigned int) (arg2)) || func_ov105_0229d75c((int) arg1, arg2)) {
        int ret = func_ov105_0229d718(arg1, arg2);
        func_ov094_0229b950(arg1 + 0xd5c, ret);
        func_ov094_0229ab5c((void *) (arg1 + 0x2fc));
    } else {
        func_ov105_0229d404((void *) arg1);
    }
}

void func_ov105_0229d390(void *arg0)
{
    func_ov094_0229ab0c((char *) arg0 + 0x2fc);
    func_ov094_0229b944((char *) arg0 + 0xd5c);
}

void func_ov105_0229d354(int r4, int r5)
{
    if (func_ov105_0229d76c(r4, r5) == 0) {
        if (func_ov105_0229d75c(r4, r5) == 0) {
            return;
        }
    }
    func_ov094_0229b938(r4 + 0xd5c, func_ov105_0229d718((char *) r4, r5));
}

int func_ov105_0229d310(void *receiver)
{
    int diff;
    int diff2;

    diff = data_021f6c60 - data_021f6c58;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 8) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 8) {
        return 1;
    }

    return 0;
}

void func_ov105_0229d294(UnkStruct_0229d294 *p)
{
    int r6, r4;
    int r2;

    r6 = func_ov105_0229d530(p, p->b) - 0x6d;
    r4 = func_ov105_0229d4c4(p, p->b) - 0x78;
    if (func_0206fe54() != 0) {
        r4 -= 8;
    }
    func_0208aa60(p->arr23bc, r6, r4);
    if (func_ov105_0229d76c((int) p, (unsigned char) p->b) != 0 || func_ov105_0229d75c((int) p, (unsigned char) p->b) != 0) {
        r2 = func_ov105_0229d718((char *) p, (unsigned char) p->b);
        func_ov094_0229b9b4(p->arr0d5c, p->arr23bc, r2);
    }
}

void func_ov105_0229d230(struct UnkStruct_0229d230 *arg)
{
    if (func_ov105_0229d76c((int) arg, (unsigned char) arg->unk_2BA) ||
        func_ov105_0229d75c((int) arg, (unsigned char) arg->unk_2BA)) {
        if (func_ov105_0229d428((int) arg, (unsigned char) arg->unk_2BA) != 0) {
            func_ov002_02207cf0(&arg->sub);
        } else {
            arg->unk_2B6 = arg->unk_2BA;
            func_ov002_02207cf8(&arg->sub);
        }
    } else {
        func_ov002_02207cf0(&arg->sub);
    }
}

void func_ov105_0229d1f0(struct UnkStruct_0229d1f0 *p)
{
    if (func_ov105_0229c340(p, 0x40) != 0) {
        return;
    }
    if (p->unk_2B4 == 0) {
        return;
    }
    if (p->unk_2B4 != 1) {
        return;
    }
    func_ov094_0229b5e8((void *) ((char *) p + 0xd5c), p->unk_AC, p->unk_B0, (void *) ((char *) p + 0xb4));
}

void func_ov105_0229d1c4(unsigned int *r0)
{
    unsigned int r2;
    unsigned int r1;

    r2 = *(unsigned int *) ((unsigned char *) r0 + 0xa4);
    r2 += data_021f6c58;
    *(unsigned int *) ((unsigned char *) r0 + 0xac) = r2;

    r2 = *(unsigned int *) ((unsigned char *) r0 + 0xa8);
    r1 = r2 + data_021f6c54;
    *(unsigned int *) ((unsigned char *) r0 + 0xb0) = r1;
}

void func_ov105_0229d17c(char *p)
{
    *(int *) (p + 0xac) = func_ov002_02209f3c(p + 0x24a4) - 2;
    *(int *) (p + 0xb0) = func_ov002_02209f14(p + 0x24a4) - 4;
    if (func_0208e4bc(p + 0x24a4) == 1) {
        *(int *) (p + 0xb0) -= 0x16;
    }
}

void func_ov105_0229d154(char *obj)
{
    *(unsigned int *) (obj + 0xac) = func_ov002_02209d84((void *) (obj + 0x248c));
    *(unsigned int *) (obj + 0xb0) = func_ov002_02209d7c((void *) (obj + 0x248c));
}

void func_ov105_0229d0f8(struct UnkStruct_0229d0f8 *self, int arg)
{
    int result;
    int temp;

    if (func_ov105_0229d76c((int) self, arg) == 0 && func_ov105_0229d75c((int) self, arg) == 0) {
        return;
    }

    result = func_ov105_0229d718((char *) self, arg);
    self->unk_2B4 = 1;
    temp = func_ov094_0229b8d8((u8 *) self + 0xd5c, result);
    func_02066830((u8 *) self + 0xb4, temp);
    func_ov094_0229b890((u8 *) self + 0xd5c, result);
}

void func_ov105_0229d0d4(void *obj, void *arg1)
{
    if (*(unsigned char *) ((char *) obj + 0x2b4) == 1) {
        func_ov105_0229d5dc(obj, arg1, (char *) obj + 0xb4);
    }
    *(unsigned char *) ((char *) obj + 0x2b4) = 0;
}
