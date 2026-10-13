/* func_0206c05c @ 0x0206c05c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0206c05c {
    char pad_00[0x400];
    u32 unk_400;
    u32 vals_0x404[3];
    u32 count;
    u32 vals_0x414[3];
    void *ptrs_0x420[3];
    u32 vals_0x42c[3];
    u8 flags_0x438[3];
};

extern u32 func_02068bc8(u32);
extern void func_02051694(void *);

void func_0206c05c(struct UnkStruct_0206c05c *self)
{
    int i;
    u32 zero1 = 0;
    u32 zero2 = 0;

    for (i = 0; i < self->count; i++) {
        void *ptr = self->ptrs_0x420[i];
        if (ptr != 0) {
            u8 *byte_base = (u8 *) self + i;
            if (byte_base[0x438] != 0) {
                *(u32 *) ((char *) ptr + 0x10) = self->vals_0x404[i];
                *(u32 *) ((char *) ptr + 0x14) = zero1;
                *(u32 *) ((char *) ptr + 0x30) = self->vals_0x42c[i];
                *(u8 *) ((char *) ptr + 0x38) = (u8) func_02068bc8(self->vals_0x414[i]);
                func_02051694(ptr);
                byte_base[0x438] = (u8) zero2;
            }
        }
    }

    if (self->count < 3) {
        void *ptr = self->ptrs_0x420[self->count];
        if (ptr != 0) {
            *(u32 *) ((char *) ptr + 0x14) = (u32) ((char *) self + self->unk_400);
        }
    }
}
