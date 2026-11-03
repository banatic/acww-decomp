/* key_repeat: 14 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_022089e0 @ 0x022089e0, 0xc bytes, Thumb
 * func_ov002_022089d4 @ 0x022089d4, 0xc bytes, Thumb
 * func_ov002_022089bc @ 0x022089bc, 0x18 bytes, Thumb
 * func_ov002_02208938 @ 0x02208938, 0x84 bytes, Thumb
 * func_ov002_0220892c @ 0x0220892c, 0xc bytes, Thumb
 * func_ov002_02208918 @ 0x02208918, 0x12 bytes, Thumb
 * func_ov002_02208904 @ 0x02208904, 0x12 bytes, Thumb
 * func_ov002_022088f0 @ 0x022088f0, 0x12 bytes, Thumb
 * func_ov002_022088dc @ 0x022088dc, 0x12 bytes, Thumb
 * func_ov002_022088cc @ 0x022088cc, 0x10 bytes, Thumb
 * func_ov002_022088bc @ 0x022088bc, 0x10 bytes, Thumb
 * func_ov002_022088ac @ 0x022088ac, 0x10 bytes, Thumb
 * func_ov002_0220889c @ 0x0220889c, 0x10 bytes, Thumb
 * func_ov002_02208880 @ 0x02208880, 0x1a bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02208938 {
    u8 pad_00[4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
};

extern int data_ov002_0220bb14;
extern void func_020edb3c(void *a);
extern u16 data_021fbe40[2];

void func_ov002_022089e0(char **ptr)
{
    *ptr = ((char *) &data_ov002_0220bb14);
}

void func_ov002_022089d4(int *p)
{
    *p = (int) &data_ov002_0220bb14;
}

void *func_ov002_022089bc(void *p)
{
    void *v = (void *) &data_ov002_0220bb14;
    *(void **) p = v;
    func_020edb3c(p);
    return p;
}

void func_ov002_02208938(struct UnkStruct_02208938 *p)
{
    u8 old_e;
    u8 *pF;

    old_e = p->unk_0E;

    p->unk_0E = (u8) (data_021fbe40[0] & 0xF0);

    pF = &p->unk_0F;
    p->unk_0F = (u8) (p->unk_0F | (u8) (data_021fbe40[1] & 0xF0));

    if (p->unk_0E == 0 || old_e != p->unk_0E) {
        p->unk_0F = (u8) (data_021fbe40[1] & 0xF0);
        p->unk_0A = p->unk_04;
        p->unk_0C = p->unk_04;
    } else {
        if (p->unk_0C > 0) {
            p->unk_0C--;
        } else {
            *pF = (u8) (*pF | (p->unk_0E & 0xF0));
            p->unk_0A = (s16) (p->unk_0A - p->unk_08);
            if (p->unk_0A < p->unk_06) {
                p->unk_0A = p->unk_06;
            }
            p->unk_0C = p->unk_0A;
        }
    }
}

unsigned char func_ov002_0220892c(unsigned char *r0)
{
    r0[0x10] = r0[0xf];
    r0[0xf] = 0;
    return r0[0x10];
}

int func_ov002_02208918(void *this)
{
    if ((*(unsigned char *) ((char *) this + 0x10) & 0x40) != 0) {
        return 1;
    }
    return 0;
}

int func_ov002_02208904(unsigned char *p)
{
    if (p[0x10] & 0x80) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov002_022088f0(void *self)
{
    if ((*(unsigned char *) ((char *) self + 0x10) & 0x20) != 0) {
        return 1;
    }
    return 0;
}

int func_ov002_022088dc(void *p)
{
    return (*(unsigned char *) ((char *) p + 0x10) & 0x10) ? 1 : 0;
}

int func_ov002_022088cc(int param)
{
    if ((param & 0x40) != 0) {
        return 1;
    }
    return 0;
}

int func_ov002_022088bc(int param)
{
    if ((param & 0x80) != 0) {
        return 1;
    }
    return 0;
}

int func_ov002_022088ac(int param)
{
    if ((param & 0x20) != 0) {
        return 1;
    }
    return 0;
}

int func_ov002_0220889c(int param)
{
    if ((param & 0x10) != 0) {
        return 1;
    }
    return 0;
}

void func_ov002_02208880(void *r0, unsigned short r1, unsigned short r2, unsigned short r3)
{
    unsigned char r4 = 0;
    ((unsigned char *) r0)[0xe] = r4;
    ((unsigned char *) r0)[0xf] = r4;
    ((unsigned char *) r0)[0x10] = r4;
    ((unsigned short *) r0)[0x5] = r4; // offset 0xa
    ((unsigned short *) r0)[0x6] = r4; // offset 0xc
    ((unsigned short *) r0)[0x2] = r1; // offset 4
    ((unsigned short *) r0)[0x3] = r2; // offset 6
    ((unsigned short *) r0)[0x4] = r3; // offset 8
}
