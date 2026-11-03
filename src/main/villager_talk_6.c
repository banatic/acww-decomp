/* villager_talk_6: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201de64 @ 0x0201de64, 0xbc bytes, Thumb
 * func_0201dda8 @ 0x0201dda8, 0xbc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0201dda8 {
    char pad_00[0x100];
    void *unk_100;
    char arr104[0x1E];
    unsigned char unk_122;
    char pad_123[0x71];
    unsigned char bits;
    char pad_195[3];
    int counter;
} UnkStruct_0201dda8;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201dda8_2;

typedef struct {
    u32 unk_00;
    unsigned char unk_04;
} Global;

extern u32 func_0208150c(u32);
extern u32 func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, u32, int base, int offset, int scale, int multiplier, int selected);
extern u32 func_0207cec0(void *, u32);
extern void func_02015e10(void *, u32, u32);
extern struct {
    u32 a;
    u8 b;
} data_020c8d18;
extern int data_021e5a2c[1];

void func_0201de64(void *self, void *out)
{
    int i;
    u32 v;

    v = *(u32 *) (*(u32 *) ((char *) self + 0x100) + 0x830);

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, func_020036e8((unsigned char *) func_0208150c(v)),
                  data_020c8d18.a, 1, 5, data_020c8d18.b);

    *(u32 *) out = (u32) ((char *) self + 0x104);
    *(u8 *) ((char *) out + 4) = *(u8 *) ((char *) self + 0x122);

    for (i = 0; i < 8; i++) {
        if ((*(u8 *) ((char *) self + 0x194) >> i) & 1) {
            func_02015e10(self, func_0208150c(func_0207cec0(((u32 *) data_021e5a2c), i)), 0);
            *(u8 *) ((char *) self + 0x194) &= ~(1 << i);
            (*(u32 *) ((char *) self + 0x198))--;
            break;
        }
    }
}

void func_0201dda8(UnkStruct_0201dda8 *self, UnkStruct_0201dda8_2 *out)
{
    int i;
    int result1, result2;

    result1 = (int) func_020036e8((unsigned char *) (int) func_0208150c(*(int *) ((char *) self->unk_100 + 0x830)));
    result2 = (*(Global *) &data_020c8d18).unk_00;

    func_0202da38(self, &self->arr104, &self->unk_122, 0x1e, result1, result2, 1, 6, (*(Global *) &data_020c8d18).unk_04);

    out->ptr = &self->arr104;
    out->byte = self->unk_122;

    i = 0;
    while (i < 8) {
        if ((self->bits >> i) & 1) {
            int r;
            r = (int) func_0208150c((int) func_0207cec0((void *) data_021e5a2c, i));
            func_02015e10((void *) self, r, 0);
            self->bits &= ~(1 << i);
            self->counter--;
            break;
        }
        i++;
    }
}
