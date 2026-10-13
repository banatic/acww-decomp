/* func_0208e508 @ 0x0208e508, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_020d0b08[];
extern u8 data_020d0af4[];
extern u8 data_020d0ae0[];
extern u64 data_020d6fcc[];

extern void func_0208a1f0(void *obj, void *data);
extern void func_0208a1ec(void *obj, int flag);
extern void func_0208a144(void *obj);

typedef struct {
    u8 pad_00[0xc];
    u32 sub0;
    u8 pad_10[0x2c - 0xc - 4];
    u32 sub1;
    u8 pad_30[0x40 - 0x2c - 4];
    u32 unk_40;
    u8 pad_44[0x49 - 0x44];
    volatile u8 unk_49;
} Parent;

void func_0208e508(Parent *self, int idx)
{
    u32 word = data_020d0b08[idx];
    u32 word_plus_1 = word + 1;
    u8 byte_val = data_020d0af4[idx];
    int flag;

    switch (byte_val) {
        default:
            flag = 0;
            break;
        case 0:
            flag = 1;
            break;
    }

    self->unk_40 = idx;

    func_0208a1f0(&self->sub0, &data_020d6fcc[word]);
    func_0208a1ec(&self->sub0, flag);
    func_0208a144(&self->sub0);

    self->unk_49 = data_020d0ae0[idx];
    if (self->unk_49 != 0) {
        func_0208a1f0(&self->sub1, &data_020d6fcc[word_plus_1]);
        func_0208a1ec(&self->sub1, flag);
        func_0208a144(&self->sub1);
    }
}