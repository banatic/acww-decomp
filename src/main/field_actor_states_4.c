/* field_actor_states_4: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020087e0 @ 0x020087e0, 0x118 bytes, Thumb
 * func_020087a0 @ 0x020087a0, 0x40 bytes, Thumb
 * func_02008750 @ 0x02008750, 0x50 bytes, Thumb
 * func_02008748 @ 0x02008748, 0x8 bytes, Thumb
 * func_02008738 @ 0x02008738, 0x10 bytes, Thumb
 * func_020086c4 @ 0x020086c4, 0x74 bytes, Thumb
 * func_02008690 @ 0x02008690, 0x34 bytes, Thumb
 * func_020085cc @ 0x020085cc, 0xc4 bytes, Thumb
 */

#include "types.h"

typedef struct T12c {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

struct UnkStruct_020087e0 {
    unsigned char pad_00[0xec];
    unsigned char pad_EC[0x10a - 0xec];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10a - 1];
    T12c *unk_12C;
    unsigned char pad_130[0x7d5 - 0x12c - 4];
    unsigned char unk_7D5;
    unsigned char pad_7D6[0x7f0 - 0x7d5 - 1];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
};

struct UnkStruct_020087a0 {
    unsigned char pad_00[0x800];
    unsigned int unk_800;
};

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct {
    unsigned char pad_00[0x2d8];
    struct {
        unsigned int lo : 12;
        unsigned int mid : 16;
        unsigned int hi : 4;
    } unk_2D8;
    unsigned char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    unsigned char pad_708[0x824 - 0x708];
    int unk_824;
    int unk_828;
    int unk_82C;
    int unk_830;
    int unk_834;
    int unk_838;
} UnkStruct_020085cc;

extern void *data_020ccf94;
extern int data_020d83a4;
extern int func_02073908(void *a, int b);
extern int func_0203e1c4(void);
extern void func_0203ee14(void *self, void *b);
extern unsigned int *func_0200f27c(void *self, int code);
extern void func_020a8164(void *p, void *g);
extern void func_0202f17c(void);
extern unsigned char func_02008258(void *arg0, int index);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_0203ee08(void *self, void *b);
extern void func_0200f268(void *self, int code);
extern int func_0203e19c(void);
extern void func_02010f5c(int);
extern void func_02010d64(void *);
extern int func_0200f554(void *);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020778b0(int destination, int value, ...);
extern int func_02077898(int a);
extern void func_0200850c(void *dst, void *src, int c);
extern void func_020109a0(void *p, int a, int b, unsigned short c);
extern int func_020e8bb0(void *dst, int val, int a, int b, int c);

void func_020087e0(struct UnkStruct_020087e0 *self)
{
    void *b;
    unsigned char *statep;

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        statep = &self->unk_7D5;
        switch (*statep) {
            case 0:
                if (func_0203e1c4() != 0) {
                    *statep = 1;
                    b = (char *) self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee14(self, b);
                    func_0200f27c(self, 0x11);
                    func_020a8164((char *) self + 0xec, &data_020d83a4);
                    self->unk_10A = 0x1e;
                    self->unk_12C->unk_08 = 1;
                    func_0202f17c();
                } else {
                    self->unk_7FC = func_02008258(self, self->unk_7F0);
                    func_0200d4e8(self, 3, 1, -1);
                }
                break;
            case 1:
                if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                    *statep = 2;
                }
                break;
            case 2:
                if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                    b = (char *) self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee08(self, b);
                    func_0200f268(self, 0x11);
                    func_0203e19c();
                    self->unk_7FC = func_02008258(self, self->unk_7F0);
                    func_0200d4e8(self, 3, 1, -1);
                }
                break;
        }
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
}

void func_020087a0(struct UnkStruct_020087a0 *self)
{
    func_02010f5c((int) self);
    if (func_02073908((void *) ((*(unsigned int *) &data_020ccf94)), self->unk_800) != 0) {
        func_02010d64(self);
    } else {
        func_0200f554(self);
        func_02010d64(self);
    }
    func_020087e0((struct UnkStruct_020087e0 *) self);
}

int func_02008750(char *arg0, unsigned short *arg1, int arg2, int arg3)
{
    char local[0x1c];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x85, arg2, arg3);
    *(unsigned short *) (arg0 + 0x822) = *arg1;
    *(unsigned short *) (arg0 + 0x820) = *(unsigned short *) (arg0 + 0x822);
    result = func_0200e894(arg0, local);
    func_0200e91c(local);
    return result;
}

void func_02008748(void *object, unsigned short value)
{
    func_020778b0((int) object, value);
}

void func_02008738(int a, unsigned short *b)
{
    *b = (unsigned short) func_02077898(a);
}

void func_020086c4(void *self, void *message, int previous)
{
    unsigned int tmp[4];
    func_02008748((char *) self + 0x8f0, *(unsigned short *) ((char *) self + 0x820));
    func_0200850c(tmp, self, 0);
    *(unsigned int *) ((char *) self + 0x824) = tmp[0];
    *(unsigned int *) ((char *) self + 0x828) = tmp[1];
    *(unsigned int *) ((char *) self + 0x82c) = tmp[2];
    *(unsigned int *) ((char *) self + 0x830) = 0x1000;
    *(unsigned int *) ((char *) self + 0x834) = 0x1000;
    *(unsigned int *) ((char *) self + 0x838) = 0x1000;
    func_020109a0(self, 0x7e, 3, 0);
}

void func_02008690(void *param1, void *param2)
{
    unsigned short local[2];
    void *sp;

    func_02008738((int) ((char *) param1 + 0x8f0), (unsigned short *) (&local[0]));
    local[1] = local[0];
    func_02008750((char *) param1, (unsigned short *) (&local[1]), 6, (int) param2);
}

void func_020085cc(UnkStruct_020085cc *self)
{
    int r6;
    int r4;
    VecFx32 out;

    func_02010f5c((int) self);

    r6 = self->unk_2D8.mid;
    r4 = 0x1000;

    if (self->unk_704 == 0x7e) {
        if (r6 == 0xa) {
            func_0200f27c((void *) ((unsigned int *) self), 0xd);
        }
    } else {
        int base = self->unk_830;
        if (r6 >= 9) {
            r4 = base - 0x155;
            if (r4 < 0) {
                r4 = 0;
            }
        }
    }

    self->unk_830 = r4;
    self->unk_834 = r4;
    self->unk_838 = r4;

    func_0200850c((void *) (&out), (void *) self, r6);

    func_020e8bb0(&self->unk_824, out.x, 0x800, 0x2000, 0x333);
    func_020e8bb0(&self->unk_828, out.y, 0x800, 0x2000, 0x333);
    func_020e8bb0(&self->unk_82C, out.z, 0x800, 0x2000, 0x333);
}
