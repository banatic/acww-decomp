/* func_ov095_0229b280 @ 0x0229b280, 0xa4 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229b280 {
    u8 pad_00[0x18];
    u8 count;
    u8 pad_19[0x3c - 0x19];
    u8 tiles[0x2c28 - 0x3c];
    u8 data[0x8000];
};

extern u8 func_0203fa58(struct UnkStruct_0229b280 *p);
extern u8 func_0203fa14(int x);
extern void func_02064af4(const void *src, void *dst, unsigned int size);
extern void func_02002a88(void *dst, int a, int b, int c, int d);
extern const u8 data_ov095_0229edf4[];

void func_ov095_0229b280(struct UnkStruct_0229b280 *self)
{
    int i;

    self->count = func_0203fa58(self);

    for (i = 0; i < self->count; i++) {
        self->tiles[i] = func_0203fa14(i);
    }

    func_02064af4(data_ov095_0229edf4, self->data, 0x1000);

    for (i = 0; i < self->count; i++) {
        int b = self->tiles[i] - 1;
        int off = ((b & 0xf) << 6) + ((b >> 4) << 11);
        int n = (i << 1) + 0x109;

        func_02002a88(self->data + off, 8, n, n, n + 1);
        func_02002a88(self->data + (off + 0x400), 8, n + 0x20, n + 0x20, n + 0x21);
    }
}
