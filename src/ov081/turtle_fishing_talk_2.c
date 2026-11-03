/* turtle_fishing_talk_2: 9 functions, module ov081
 * mwccarm 1.2/base -O4,s
 * func_ov081_0227916c @ 0x0227916c, 0x54 bytes, Thumb
 * func_ov081_0227915c @ 0x0227915c, 0x10 bytes, Thumb
 * func_ov081_0227914c @ 0x0227914c, 0x10 bytes, Thumb
 * func_ov081_02279124 @ 0x02279124, 0x28 bytes, Thumb
 * func_ov081_02279068 @ 0x02279068, 0xbc bytes, Thumb
 * func_ov081_02279060 @ 0x02279060, 0x8 bytes, Thumb
 * func_ov081_0227903c @ 0x0227903c, 0x24 bytes, Thumb
 * func_ov081_02279024 @ 0x02279024, 0x18 bytes, Thumb
 * func_ov081_02279004 @ 0x02279004, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} Pair;

typedef struct UnkStruct_02279068 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
    char pad_B4[0xc4 - 0xb4];
    u16 unk_C4;
} UnkStruct_02279068;

extern Pair data_ov081_022796b0;
extern Pair data_ov081_022796a8;
extern Pair data_ov081_022798a4[2];
extern unsigned int data_ov081_022798a0;
extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern int func_02086564(u16 *p);
extern int func_02015330(UnkStruct_02279068 *self, u16 *p, int a, int b, int c);
extern void func_02015de4(UnkStruct_02279068 *self, u16 *p, int a, int b);
extern void func_02015f00(void *, int, int, int, int);
extern void func_0209a050(int a);
extern int func_020155cc(UnkStruct_02279068 *self);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov081_02279868;
extern void *func_0202eb70(void *self);
extern int data_ov081_0227972c;
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

void func_ov081_0227916c(int unused, Pair *dst, int idx)
{
    unsigned int flag = data_ov081_022798a0;
    if ((flag & 1) == 0) {
        data_ov081_022798a4[0] = data_ov081_022796b0;
        data_ov081_022798a4[1] = data_ov081_022796a8;
        data_ov081_022798a0 = flag | 1;
    }
    *dst = data_ov081_022798a4[idx];
}

void func_ov081_0227915c(int a, int b)
{
    func_ov081_0227916c(a, (Pair *) (a + 0xB4), b);
}

void func_ov081_0227914c(char *a, char *b)
{
    func_ov081_0227916c((int) a, (Pair *) (a + 0xBC), (int) b);
}

unsigned short func_ov081_02279124(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        if (value >= 0x12e8 && value <= 0x131f) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}

void func_ov081_02279068(UnkStruct_02279068 *self)
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
        func_ov081_0227914c((char *) self, (char *) 1);
        func_02015de4(self, &self->unk_C4, 2, 7);
        func_02015f00(self, *(int *) (self->unk_B0 + 0x724), 4, 1, 3);
        if (t >= 0) {
            func_0209a050(t);
        }
        code = 0xd;
    } else {
        func_020155cc(self);
    }
    func_0206844c(h, &code, (int) &data_ov081_02279868);
}

void func_ov081_02279060(int argument0)
{
    func_020155cc((UnkStruct_02279068 *) argument0);
}

void *func_ov081_0227903c(void *self)
{
    char *p;
    func_0202eb70(self);
    *((unsigned int *) self) = (unsigned int) &data_ov081_0227972c;
    p = (char *) self;
    p += 0xc4;
    *((unsigned short *) p) = 0xfff1;
    return self;
}

void *func_ov081_02279024(void *p)
{
    *(int *) p = (int) &data_ov081_0227972c;
    func_0202eb20(p);
    return p;
}

void *func_ov081_02279004(void *arg)
{
    *(void **) arg = (void *) &data_ov081_0227972c;
    func_0202eb20(arg);
    func_020edb3c(arg);
    return arg;
}
