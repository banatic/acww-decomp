/* func_0205f2f8 @ 0x0205f2f8, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0205f2f8 {
    u8 data[0xf4];
};

struct UnkStruct_0205f2f8_2 {
    u8 data[0x14];
};

struct UnkStruct_0205f2f8_3 {
    u32 unk_00[9];
    void *p[9];
    u32 arr1[9];
    u16 h1[9];
    u16 pad_7E;
    u32 arr2[9];
    u16 h2[9];
    u8 pad_B6[0x26];
    struct UnkStruct_0205f2f8_2 b[9];
    u8 pad_190[0xfc];
    struct UnkStruct_0205f2f8 a[9];
    u32 arr3[9];
    u16 c[9];
};

extern void func_02055454(struct UnkStruct_0205f2f8 *);
extern void func_0205f0c0(struct UnkStruct_0205f2f8_3 *, int);
extern void func_02055b40(struct UnkStruct_0205f2f8_2 *);
extern void func_020e9b9c(void *);
extern void *data_021c9acc;
extern void *data_021c9ad8;

void func_0205f2f8(struct UnkStruct_0205f2f8_3 *self)
{
    int i;

    for (i = 0; i < 9; i++) {
        func_02055454(&self->a[i]);
        func_0205f0c0(self, i);
        func_02055b40(&self->b[i]);
        self->c[i] = 0xfff1;
    }

    for (i = 0; i < 9; i++) {
        if (self->p[i] != 0) {
            func_020e9b9c(self->p[i]);
            self->p[i] = 0;
            self->arr1[i] = 0;
            self->h1[i] = 0;
            self->arr2[i] = 0;
            self->h2[i] = 0;
            self->arr3[i] = 0;
        }
    }

    if (data_021c9acc != 0) {
        func_020e9b9c(data_021c9acc);
    }

    for (i = 0; i < 9; i++) {
        self->unk_00[i] = 0;
    }

    if (data_021c9ad8 != 0) {
        func_020e9b9c(data_021c9ad8);
    }
}
