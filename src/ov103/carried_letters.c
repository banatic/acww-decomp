/* carried_letters: 17 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229c660 @ 0x0229c660, 0x20 bytes, Thumb
 * func_ov103_0229c640 @ 0x0229c640, 0x20 bytes, Thumb
 * func_ov103_0229c604 @ 0x0229c604, 0x3c bytes, Thumb
 * func_ov103_0229c5b8 @ 0x0229c5b8, 0x4c bytes, Thumb
 * func_ov103_0229c588 @ 0x0229c588, 0x30 bytes, Thumb
 * func_ov103_0229c52c @ 0x0229c52c, 0x5c bytes, Thumb
 * func_ov103_0229c4fc @ 0x0229c4fc, 0x30 bytes, Thumb
 * func_ov103_0229c444 @ 0x0229c444, 0xb8 bytes, Thumb
 * func_ov103_0229c3a0 @ 0x0229c3a0, 0xa4 bytes, Thumb
 * func_ov103_0229c350 @ 0x0229c350, 0x50 bytes, Thumb
 * func_ov103_0229c32c @ 0x0229c32c, 0x24 bytes, Thumb
 * func_ov103_0229c30c @ 0x0229c30c, 0x20 bytes, Thumb
 * func_ov103_0229c2f4 @ 0x0229c2f4, 0x18 bytes, Thumb
 * func_ov103_0229c2e4 @ 0x0229c2e4, 0x10 bytes, Thumb
 * func_ov103_0229c2d4 @ 0x0229c2d4, 0x10 bytes, Thumb
 * func_ov103_0229c228 @ 0x0229c228, 0xac bytes, Thumb
 * func_ov103_0229c180 @ 0x0229c180, 0xa8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229c640 {
    char pad_00[0x2274];
    int unk_2274;
};

struct UnkStruct_0229c588 {
    u8 pad_00[0x2da8];
    u8 state;
};

typedef struct {
    char pad_00[0x2da8];
    unsigned char flag;
} UnkStruct_0229c4fc;

struct UnkStruct_0229c3a0 {
    unsigned char pad_00[0x2da4];
    unsigned char b;
};

struct UnkStruct_0229c350 {
    unsigned char pad_00[0x2da4];
    unsigned char flags;
};

extern void func_ov002_0220a164(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a374(void *, int);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov103_0229cfa0(struct UnkStruct_0229c588 *self);
extern void func_ov002_02208c58(void *p, void *q, int z);
extern int func_ov103_0229ccb4(void *p, int b);
extern int func_ov103_0229cc80(void *p, int b);
extern void func_ov002_02209910(void *p, int a, int b);
extern void func_ov002_0220970c(void *p, int a);
extern void func_ov103_0229c6a0(UnkStruct_0229c4fc *self);
extern void func_ov002_022096d8(void *ptr, int val);
extern int func_ov103_0229cce8(unsigned char *self, int value);
extern int func_0206fe54(void);
extern int func_02065ec0(int value);
extern int func_02065f18(int value);
extern void func_ov002_02208d30(unsigned char *base, int arg);
extern int func_ov002_02208d4c(unsigned char *base, int arg1, int arg2);
extern void func_ov103_0229c7ec(unsigned char *self);
extern int func_ov002_022088ac(void *arg);
extern int func_ov002_0220889c(void *arg);
extern int func_ov002_022088cc(void *arg);
extern int func_ov002_022088bc(void *arg);
extern int func_ov103_0229cdfc(struct UnkStruct_0229c3a0 *self, int b);
extern void func_ov002_02208090(void *p, int n);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_0208f0c4(void *, int);
extern void func_02066688(char *);
extern void *func_ov002_0220b464(char *);
extern void *func_0206e35c(char *);
extern void *func_ov002_0220ba0c(char *);
extern void *func_ov002_02209ac8(char *);
extern void *func_ov002_02209cb4(char *);
extern void func_ov002_02209e38(char *);
extern void *func_ov002_02207e28(char *);
extern void *func_ov094_0229a2d0(char *);
extern void func_ov094_0229bc30(char *);
extern void *func_ov094_0229afe0(char *);
extern void *func_ov002_0220826c(char *);
extern void func_ov002_02207f6c(char *);
extern unsigned char data_ov103_0229e2e0[];

void func_ov103_0229c32c(void *p);
int func_ov103_0229c2f4(unsigned int *arr, unsigned int mask);
void func_ov103_0229c2e4(unsigned char *arg0, unsigned int arg1);
void func_ov103_0229c2d4(unsigned int *p, unsigned int mask);

void func_ov103_0229c660(void *self)
{
    func_ov002_0220a164((char *) self + 0x2274);
    func_ov002_02208098(self, 0xd);
}

void func_ov103_0229c640(struct UnkStruct_0229c640 *self)
{
    func_ov002_0220a374(&self->unk_2274, 4);
    func_ov002_02208098(self, 0xe);
}

void func_ov103_0229c604(void *p, unsigned char v)
{
    func_ov002_02207d24((char *) p + 0x218c, 1);
    *((unsigned char *) ((char *) p + 0x2da6)) = v;
    func_ov002_0220a374((char *) p + 0x2274, 5);
    func_ov002_02208098(p, 0x10);
}

void func_ov103_0229c5b8(void *obj, unsigned char value)
{
    func_ov002_02207d24((char *) obj + 0x218c, 1);
    *((unsigned char *) obj + 0x2da7) = *((unsigned char *) obj + 0x8d);
    *((unsigned char *) obj + 0x2da6) = value;
    func_ov002_0220a374((char *) obj + 0x2274, 6);
    func_ov002_02208098(obj, 0x11);
}

void func_ov103_0229c588(struct UnkStruct_0229c588 *self)
{
    switch (self->state) {
        case 0:
            func_ov103_0229c640((struct UnkStruct_0229c640 *) self);
            break;
        case 1:
            func_ov103_0229c32c((void *) self);
            break;
        case 3:
        default:
            func_ov103_0229cfa0(self);
            break;
    }
}

void func_ov103_0229c52c(unsigned char *self)
{
    func_ov002_02208c58(self + 0x22d8, self + 0x26c0, 0);

    {
        int t = func_ov103_0229ccb4(self, self[0x2da5]);
        int v = func_ov103_0229cc80(self, self[0x2da5]);

        func_ov002_02209910(self + 0x22d8, t, v);
    }

    func_ov002_0220970c(self + 0x22d8, 0);
    func_ov002_02208098(self, 0x14);
}

void func_ov103_0229c4fc(UnkStruct_0229c4fc *self)
{
    self->flag = 3;
    func_ov103_0229c6a0(self);
    func_ov002_022096d8((char *) self + 0x22d8, 0);
    func_ov002_02208098((void *) self, 0x16);
}

void func_ov103_0229c444(unsigned char *self, int value)
{
    int r6;
    int r4_val;

    self[0x2da5] = value;
    func_ov002_02208d30(self + 0x26c0, 3);

    r6 = func_ov103_0229cce8(self, value);

    if (func_0206fe54() != 0) {
        func_ov002_02208d4c(self + 0x26c0, 0, 0);
    }

    r4_val = func_02065ec0(r6);

    if (r4_val != 0) {
        if (r4_val == 7) {
            func_ov002_02208d4c(self + 0x26c0, 0x17, 1);
        } else {
            func_ov002_02208d4c(self + 0x26c0, 0x14, 1);
        }
    }

    if ((func_02065f18(r6) != 0xfff1 && r4_val == 3) || r4_val == 6 || r4_val == 1) {
        func_ov002_02208d4c(self + 0x26c0, 0x15, 2);
    }

    func_ov002_02208d4c(self + 0x26c0, 2, 3);

    func_ov103_0229c7ec(self);
    func_ov002_02207d24((void *) (self + 0x218c), 1);
    func_ov103_0229c52c(self);
}

void func_ov103_0229c3a0(struct UnkStruct_0229c3a0 *self, void *arg, int b)
{
    int r4 = self->b - 11;
    int r6 = r4 >> 1;

    if (func_ov002_022088ac(arg)) {
        if ((r4 & 1) > 0) {
            self->b--;
        }
    } else {
        if (func_ov002_0220889c(arg)) {
            if ((r4 & 1) < 1) {
                self->b++;
            }
        }
    }

    if (func_ov103_0229cdfc(self, self->b) != 0) {
        if (func_ov103_0229c2f4((unsigned int *) self, 0x30) == 0) {
            if (func_ov002_022088cc(arg)) {
                if (r6 > 0) {
                    self->b -= 2;
                }
            } else {
                if (func_ov002_022088bc(arg)) {
                    if (r6 < 4) {
                        self->b += 2;
                    }
                }
            }
        }
    }
}

int func_ov103_0229c350(struct UnkStruct_0229c350 *self, int a1, int a2)
{
    unsigned char old = self->flags;

    func_ov103_0229c2d4((unsigned int *) self, 0x30);
    if (a1 == 0) {
        return 0;
    }

    if (func_ov103_0229cdfc((struct UnkStruct_0229c3a0 *) self, (unsigned char) self->flags) != 0) {
        func_ov103_0229c3a0((struct UnkStruct_0229c3a0 *) self, (void *) a1, a2);
    }

    return old != self->flags;
}

void func_ov103_0229c32c(void *p)
{
    func_ov002_02208090(p, 3);
    func_ov002_022080a0(p, 1);
    func_ov103_0229c2e4((unsigned char *) p, 0x100);
}

void func_ov103_0229c30c(void *p)
{
    func_ov002_02208098(p, 0x18);
    func_0208f0c4((char *) p + 0x2b10, 2);
}

int func_ov103_0229c2f4(unsigned int *arr, unsigned int mask)
{
    if (arr[0x2b88 / 4] & mask) {
        return 1;
    }
    return 0;
}

void func_ov103_0229c2e4(unsigned char *arg0, unsigned int arg1)
{
    *(unsigned int *) (arg0 + 0x2b88) |= arg1;
}

void func_ov103_0229c2d4(unsigned int *p, unsigned int mask)
{
    *((unsigned int *) ((char *) p + 0x2b88)) &= ~mask;
}

char *func_ov103_0229c228(char *self)
{
    *(void **) self = ((char *) data_ov103_0229e2e0);
    func_02066688(self + 0x2ca0);
    func_02066688(self + 0x2ba0);
    func_ov002_0220b464(self + 0x2b10);
    func_0206e35c(self + 0x27e8);
    func_ov002_0220ba0c(self + 0x26cc);
    func_ov002_02209ac8(self + 0x22d8);
    func_ov002_02209cb4(self + 0x2274);
    func_ov002_02209e38(self + 0x225c);
    func_ov002_02207e28(self + 0x218c);
    func_ov094_0229a2d0(self + 0xb54);
    /* the call's address holds ov094's function (PocketsLetters_Destruct) whenever this overlay
     * is loaded, as the next call's, which only ov094 has; the relocation allows ov094, ov119
     * and ov128 */
    func_ov094_0229bc30(self + 0xb2c);
    func_ov094_0229afe0(self + 0xcc);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov103_0229c180(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov103_0229e2e0;
    func_02066688((char *) ((char *) self + 0x2ca0));
    func_02066688((char *) ((char *) self + 0x2ba0));
    func_ov002_0220b464((char *) ((char *) self + 0x2b10));
    func_0206e35c((char *) ((char *) self + 0x27e8));
    func_ov002_0220ba0c((char *) ((char *) self + 0x26cc));
    func_ov002_02209ac8((char *) ((char *) self + 0x22d8));
    func_ov002_02209cb4((char *) ((char *) self + 0x2274));
    func_ov002_02209e38((char *) ((char *) self + 0x225c));
    func_ov002_02207e28((char *) ((char *) self + 0x218c));
    func_ov094_0229a2d0((char *) ((char *) self + 0x0b54));
    /* ov094's function, as in func_ov103_0229c228 */
    func_ov094_0229bc30((char *) self + 0x0b2c);
    func_ov094_0229afe0((char *) ((char *) self + 0xcc));
    func_ov002_0220826c((char *) self);
    return self;
}
