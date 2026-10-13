/* func_020ac588 @ 0x020ac588, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020ac588 {
    u32 pad_00;        // 0x00
    char *base;        // 0x04
    char pad_08[0x16]; // 0x08..0x1d
    u16 unk_1E;        // 0x1e
} UnkStruct_020ac588;

extern __arm void MI_CpuCopy8(void *dst, const void *src, int size);
extern void func_020ac89c(void *dst, int size);
extern void func_020ac478(UnkStruct_020ac588 *self, int a, int b);
extern void func_020ac470(UnkStruct_020ac588 *self, int a);

void func_020ac588(UnkStruct_020ac588 *self)
{
    MI_CpuCopy8(self->base + 0x29e, self->base + 0x39e, 0x22);
    MI_CpuCopy8(self->base + 0x2de, self->base + 0x3de, 0x22);
    MI_CpuCopy8(self->base + 0x25e, self->base + 0x35e, 0x22);
    func_020ac89c(self->base + 0x25e, 0x22);
    func_020ac89c(self->base + 0x29e, 0x22);
    func_020ac89c(self->base + 0x2de, 0x22);
    func_020ac89c(self->base + 0x31e, 0x22);
    func_020ac478(self, 0xd, 0x14);
    func_020ac470(self, 0xd);
    self->unk_1E = 3;
}
