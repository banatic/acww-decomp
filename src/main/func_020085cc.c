/* func_020085cc @ 0x020085cc, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern void func_02010f5c(UnkStruct_020085cc *self);
extern unsigned int *func_0200f27c(unsigned int *param0, int param1);
extern void func_0200850c(VecFx32 *out, UnkStruct_020085cc *self, int count);
extern void func_020e8bb0(void *dst, int val, int a, int b, int c);

void func_020085cc(UnkStruct_020085cc *self)
{
    int r6;
    int r4;
    VecFx32 out;

    func_02010f5c(self);

    r6 = self->unk_2D8.mid;
    r4 = 0x1000;

    if (self->unk_704 == 0x7e) {
        if (r6 == 0xa) {
            func_0200f27c((unsigned int *) self, 0xd);
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

    func_0200850c(&out, self, r6);

    func_020e8bb0(&self->unk_824, out.x, 0x800, 0x2000, 0x333);
    func_020e8bb0(&self->unk_828, out.y, 0x800, 0x2000, 0x333);
    func_020e8bb0(&self->unk_82C, out.z, 0x800, 0x2000, 0x333);
}
