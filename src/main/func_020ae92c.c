/* func_020ae92c @ 0x020ae92c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

typedef struct {
    u8 pad_00[12];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
} Func020ae92cCtx;

int func_020ae92c(Func020ae92cCtx *self, const void *src)
{
    u8 buf[8];
    MI_CpuCopy8(src, buf, 8);
    if (self->unk_0E != buf[5] || self->unk_0D != buf[4] || self->unk_0C != buf[3] || self->unk_0F != 0) {
        return 1;
    }
    return 0;
}
