/* func_0208e95c @ 0x0208e95c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct TableEntry {
    u32 a, b;
};

struct Slot {
    unsigned char data[0x14];
};

struct UnkStruct_0208e95c {
    unsigned char pad_00[0x14];
    struct Slot slot0; // offset 0x14
    struct Slot slot1; // offset 0x28
    u32 unk_3C;        // offset 0x3c
};

extern u32 data_020d0b64[];
extern u32 data_020d0b54[];
extern struct TableEntry data_020d6fcc[];

void func_0208a1f0(void *dst, const void *src);
void func_0208a1ec(void *dst, u32 val);
void *func_0208a144(void *dst);
void *func_0208a1e8(void *dst, u32 val);

void *func_0208e95c(struct UnkStruct_0208e95c *self, int idx)
{
    void *result;
    u32 a = data_020d0b64[idx];
    u32 a1 = a + 1;
    u32 b = data_020d0b54[idx];

    self->unk_3C = idx;

    func_0208a1f0(&self->slot0, &data_020d6fcc[a]);
    func_0208a1ec(&self->slot0, b);
    func_0208a144(&self->slot0);

    func_0208a1f0(&self->slot1, &data_020d6fcc[a1]);
    func_0208a1ec(&self->slot1, b);
    result = func_0208a144(&self->slot1);

    if (idx == 1) {
        func_0208a1e8(&self->slot0, 0);
        return func_0208a1e8(&self->slot1, 0);
    }
    return result;
}
