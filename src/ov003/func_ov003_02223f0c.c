/* func_ov003_02223f0c @ 0x02223f0c, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    volatile int unk_00;
    int unk_04;
    int unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_02223f0c;

extern UnkStruct_02223f0c data_ov003_0223cfa0[];
extern int data_ov003_02236be8[][4];

extern void func_02090d64(void *self);
extern void func_ov003_02223f6c(UnkStruct_02223f0c *e, void *t);
extern void func_ov003_0222409c(UnkStruct_02223f0c *e, void *t);

void func_ov003_02223f0c(void *self)
{

    int idx;
    char *t = *(char **) ((char *) self + 0xc);
    UnkStruct_02223f0c *e;

    func_02090d64(self);
    *(u8 *) ((char *) self + 0xa) = (u8) data_ov003_0223cfa0[2].unk_00;
    idx = data_ov003_0223cfa0[2].unk_00;
    if (idx < 0) {
        idx = 0;
    }
    e = &data_ov003_0223cfa0[idx];
    func_ov003_02223f6c(e, t);
    *(u8 *) ((char *) self + 0xa) = (u8) idx;
    func_ov003_0222409c(e, t);
    *(int *) (t + 0x44) = data_ov003_02236be8[data_ov003_0223cfa0[idx].unk_00][e->unk_0C];
    *(u8 *) (t + 0x80) = (u8) e->unk_10;
}
