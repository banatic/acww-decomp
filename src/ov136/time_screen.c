/* time_screen: 8 functions, module ov136
 * mwccarm 1.2/base -O4,s
 * func_ov136_0229c650 @ 0x0229c650, 0x18 bytes, Thumb
 * func_ov136_0229c628 @ 0x0229c628, 0x28 bytes, Thumb
 * func_ov136_0229c58c @ 0x0229c58c, 0x9c bytes, Thumb
 * func_ov136_0229c574 @ 0x0229c574, 0x18 bytes, Thumb
 * func_ov136_0229c564 @ 0x0229c564, 0x10 bytes, Thumb
 * func_ov136_0229c554 @ 0x0229c554, 0x10 bytes, Thumb
 * func_ov136_0229c518 @ 0x0229c518, 0x3c bytes, Thumb
 * func_ov136_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229c58c {
    u8 pad_00[0x2b77];
    u8 unk_2B77;
};

struct UnkStruct_0229c4e0 {
    int pad_00;
};

struct UnkStruct_0229c4e0_2 {
    void *vtbl;
    char pad_04[0x90];
    struct UnkStruct_0229c4e0 sub1;
    char pad_98[0x60];
    struct UnkStruct_0229c4e0 sub2;
    char pad_FC[0x1c8];
    struct UnkStruct_0229c4e0 sub3;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *p);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern u8 data_ov136_0229d41c[];
extern u8 data_ov136_0229d418[];
extern u8 data_ov136_0229d424[];
extern u8 data_ov136_0229d420[];
extern char *func_ov134_0229beb0(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern unsigned char data_ov136_0229d510[];

void func_ov136_0229c650(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x94);
    func_ov002_02208098((void *) (self), 0xb);
}

void func_ov136_0229c628(void *obj)
{
    func_ov002_0220a164((char *) obj + 0x94);
    ((unsigned char *) obj)[0x2b76] = ((unsigned char *) obj)[0x8d];
    func_ov002_02208098((void *) (obj), 12);
}

int func_ov136_0229c58c(struct UnkStruct_0229c58c *obj, int key)
{
    u8 orig = obj->unk_2B77;

    if (func_ov002_022088ac(key)) {
        obj->unk_2B77 = data_ov136_0229d41c[obj->unk_2B77];
    } else if (func_ov002_0220889c(key)) {
        obj->unk_2B77 = data_ov136_0229d418[obj->unk_2B77];
    }

    if (orig != obj->unk_2B77) {
        return 1;
    }

    if (func_ov002_022088cc(key)) {
        obj->unk_2B77 = data_ov136_0229d424[obj->unk_2B77];
    } else if (func_ov002_022088bc(key)) {
        obj->unk_2B77 = data_ov136_0229d420[obj->unk_2B77];
    }

    if (orig != obj->unk_2B77) {
        return 1;
    }

    return 0;
}

int func_ov136_0229c574(void *p, int mask)
{
    if (((*(unsigned short *) ((char *) p + 0x2b74)) & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov136_0229c564(unsigned char *p, unsigned short v)
{
    *(unsigned short *) (p + 0x2b74) |= v;
}

void func_ov136_0229c554(char *base, unsigned short mask)
{
    *(unsigned short *) (base + 0x2b74) &= ~mask;
}

void *func_ov136_0229c518(void *p)
{
    *(unsigned int *) p = (unsigned int) ((int *) data_ov136_0229d510);
    func_ov134_0229beb0((char *) p + 0x2c4);
    func_ov002_0220afdc((char *) p + 0xf8);
    func_ov002_02209cb4((char *) p + 0x94);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return p;
}

struct UnkStruct_0229c4e0_2 *func_ov136_0229c4e0(struct UnkStruct_0229c4e0_2 *self)
{
    self->vtbl = (void *) data_ov136_0229d510;
    func_ov134_0229beb0((void *) (&self->sub3));
    func_ov002_0220afdc((void *) (&self->sub2));
    func_ov002_02209cb4((void *) (&self->sub1));
    func_ov002_0220826c((void *) self);
    return self;
}
