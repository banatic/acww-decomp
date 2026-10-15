/* func_020f1c6c @ 0x020f1c6c, 0xd0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct VTable {
    u8 pad_00[0x28];
    void (*fn)(void *, int, int);
} VTable;
typedef struct UnkStruct_020f1c6c {
    VTable *vtbl;
} UnkStruct_020f1c6c;

typedef struct {
    u8 pad_00[0x2c];
    UnkStruct_020f1c6c *obj2c;
    u8 pad_30[4];
    u8 sub34[0x34];
    int unk_68;
    u8 pad_6C[9];
    u8 unk_75;
} Self5;

extern int func_0210fc7c(void *sub, int mode, int zero);
extern int NNS_SndArcStrmGetTimeLength(void *sub);
extern void func_020f162c(Self5 *self, int mode, int val);

void func_020f1c6c(Self5 *self, unsigned int mode)
{
    UnkStruct_020f1c6c *p;

    switch (mode) {
        case 0:
        case 1:
            func_0210fc7c(&self->sub34, mode, 0);
            if (mode != 0) {
                return;
            }
            self->unk_68 = NNS_SndArcStrmGetTimeLength(&self->sub34);
            return;
        default:
            break;
    }

    p = self->obj2c;
    p->vtbl->fn(p, 0, mode);

    if (mode >= 0xb0 && mode <= 0xf5) {
        func_020f162c(self, mode, 0);
        return;
    }

    func_020f162c(self, mode, 0x7f);
    if (mode < 0x16) {
        return;
    }
    if (mode <= 0x2d) {
        self->unk_75 = 1;
    }
}
