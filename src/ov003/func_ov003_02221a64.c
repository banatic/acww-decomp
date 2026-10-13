/* func_ov003_02221a64 @ 0x02221a64, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y;
} UnkStruct_02221a64;

extern void func_0204f794(void *, int, int);
extern int func_0204eda8(void *, int, int);
extern void func_ov003_02224140(int, int, int, int);
extern int func_02045cec(int *, int);
extern void *func_02045bac(int);

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[6];
    fx32 unk_10, unk_14;
    char pad_18[0x18];
    fx32 unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
} UnkStruct_02221a64_2;

void func_ov003_02221a64(UnkStruct_02221a64_2 *self, UnkStruct_02221a64 *p, void *c)
{
    int loc[2];
    int h;
    func_0204f794((char *) self + 0x18, p->x, p->y);
    if (func_0204eda8(c, p->x, p->y) == 0) {
        self->unk_08 = 0xfc;
    } else {
        self->unk_08 = 0xfd;
    }
    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;
    self->unk_30 = 0;
    self->unk_34 = 0;
    self->unk_38 = 0;
    func_ov003_02224140(p->x, p->y, 0xfff1, 0);
    loc[0] = self->unk_10;
    loc[1] = self->unk_14;
    h = func_02045cec(loc, 0);
    if (h >= 0) {
        *(unsigned short *) ((char *) func_02045bac(h) + 0xa) = 0xfff1;
    }
}
