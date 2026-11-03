/* turtle_insects_talk: 9 functions, module ov082
 * mwccarm 1.2/base -O4,s
 * func_ov082_022791b0 @ 0x022791b0, 0x54 bytes, Thumb
 * func_ov082_022791a0 @ 0x022791a0, 0x10 bytes, Thumb
 * func_ov082_02279190 @ 0x02279190, 0x10 bytes, Thumb
 * func_ov082_02279168 @ 0x02279168, 0x28 bytes, Thumb
 * func_ov082_022790a8 @ 0x022790a8, 0xc0 bytes, Thumb
 * func_ov082_022790a0 @ 0x022790a0, 0x8 bytes, Thumb
 * func_ov082_0227907c @ 0x0227907c, 0x24 bytes, Thumb
 * func_ov082_02279064 @ 0x02279064, 0x18 bytes, Thumb
 * func_ov082_02279044 @ 0x02279044, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct Pair {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_022790a8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
    char pad_B4[0xc4 - 0xb4];
    u16 unk_C4;
} UnkStruct_022790a8;

struct UnkStruct_0227907c {
    void *unk_00;
    unsigned char pad_04[0xC0];
    unsigned short unk_C4;
};

typedef struct UnkStruct_02279044 {
    void *unk_00;
} UnkStruct_02279044;

extern Pair data_ov082_02279710;
extern Pair data_ov082_02279708;
extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern int func_02086564(u16 *p);
extern int func_02015330(UnkStruct_022790a8 *self, u16 *p, int a, int b, int c);
extern void func_02015de4(UnkStruct_022790a8 *self, u16 *p, int a, int b);
extern void func_02015fb0(UnkStruct_022790a8 *self, int a, int b, int c, int d, int e);
extern void func_0209a050(int a);
extern int func_020155cc(UnkStruct_022790a8 *self);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov082_022798c8;
extern void *func_0202eb70(struct UnkStruct_0227907c *self);
extern unsigned char data_ov082_0227978c[];
extern void *func_0202eb20(void *);
extern void func_020edb3c(UnkStruct_02279044 *);

void func_ov082_022791b0(int unused, Pair *out, int index)
{
    static int init_flag;
    static Pair table[2];

    if (!(init_flag & 1)) {
        table[0] = data_ov082_02279710;
        table[1] = data_ov082_02279708;
        init_flag |= 1;
    }

    *out = table[index];
}

void func_ov082_022791a0(int a, int b)
{
    func_ov082_022791b0(a, (Pair *) (a + 0xb4), b);
}

void func_ov082_02279190(int p0, int p1)
{
    func_ov082_022791b0(p0, (Pair *) ((p0 + 188)), p1);
}

unsigned short func_ov082_02279168(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;
    unsigned short limit_lo;
    unsigned short limit_hi;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        limit_lo = 0x12b0;
        limit_hi = 0x12e7;
        if (value >= limit_lo && value <= limit_hi) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}

void func_ov082_022790a8(UnkStruct_022790a8 *self)
{
    u8 code;
    int h;
    int t;

    h = self->unk_40;
    self->unk_C4 = 0xfff1;
    *(int *) (self->unk_B0 + 0x724) = 0;
    code = 0xc;
    if (func_0206fc6c() != 0) {
        t = func_0206fc8c();
        self->unk_C4 = (u16) func_0209a034(t);
        *(int *) (self->unk_B0 + 0x724) = func_02086564(&self->unk_C4);
        func_02015330(self, &self->unk_C4, 0, 4, 0);
        func_ov082_02279190((int) self, 1);
        func_02015de4(self, &self->unk_C4, 2, 7);
        func_02015fb0(self, *(int *) (self->unk_B0 + 0x724) >> 12, 4, 3, 0, 0);
        if (t >= 0) {
            func_0209a050(t);
        }
        code = 0xd;
    } else {
        func_020155cc(self);
    }
    func_0206844c(h, &code, (int) &data_ov082_022798c8);
}

void func_ov082_022790a0(int arg0)
{
    func_020155cc((UnkStruct_022790a8 *) arg0);
}

struct UnkStruct_0227907c *func_ov082_0227907c(struct UnkStruct_0227907c *self)
{
    func_0202eb70(self);
    self->unk_00 = (void *) data_ov082_0227978c;
    self->unk_C4 = 0xFFF1;
    return self;
}

void *func_ov082_02279064(void *p)
{
    *(unsigned int *) p = (unsigned int) data_ov082_0227978c;
    func_0202eb20(p);
    return p;
}

UnkStruct_02279044 *func_ov082_02279044(UnkStruct_02279044 *self)
{
    self->unk_00 = (void *) ((char *) data_ov082_0227978c);
    func_0202eb20((void *) self);
    func_020edb3c(self);
    return self;
}
