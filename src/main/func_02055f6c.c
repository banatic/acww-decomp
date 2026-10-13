/* func_02055f6c @ 0x02055f6c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_021054e4(void *, int);
extern int func_020658c4(void);
extern int NNSi_G3dModifyMatFlag(void *, int, int);

typedef struct {
    char pad_00[0x5c];
    u32 unk_5C;
} UnkStruct_02055f6c;

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[0xc];
    u8 count;
} UnkStruct_02055f6c_2;

typedef struct {
    char pad_00[4];
    u8 table[6];
    u16 idx;
} UnkStruct_02055f6c_3;

typedef struct {
    char pad_00[0xc];
    u32 flags;
} Elem;

void func_02055f6c(UnkStruct_02055f6c *self)
{
    UnkStruct_02055f6c_2 *in;
    UnkStruct_02055f6c_3 *b;
    int i;

    func_021054e4((char *) self + 8, self->unk_5C);
    in = (UnkStruct_02055f6c_2 *) self->unk_5C;
    b = (UnkStruct_02055f6c_3 *) ((char *) in + in->unk_08);
    for (i = 0; i < ((UnkStruct_02055f6c_2 *) self->unk_5C)->count; i++) {
        u8 *tbl = b->table;
        u16 h = b->idx;
        u8 *base = tbl + h;
        u16 v = *(u16 *) base;
        int w = *(int *) (base + v * i + 4);
        Elem *e = (Elem *) ((char *) b + w);
        if ((e->flags & 0xf) != 0) {
            e->flags &= ~0xf;
            e->flags |= func_020658c4();
        }
    }
    NNSi_G3dModifyMatFlag((void *) self->unk_5C, 0, 0x400);
}
