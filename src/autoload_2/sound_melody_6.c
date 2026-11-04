/* sound_melody_6: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f69cc @ 0x020f69cc, 0xb4 bytes, ARM
 * func_020f697c @ 0x020f697c, 0x50 bytes, ARM
 * func_020f6970 @ 0x020f6970, 0xc bytes, ARM
 * func_020f6950 @ 0x020f6950, 0x20 bytes, ARM
 * func_020f6948 @ 0x020f6948, 0x8 bytes, ARM
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa];
    u8 unk_0A; // 0xa
    s8 unk_0B; // 0xb
    u8 unk_0C; // 0xc
    u8 pad_0D; // 0xd
    s8 unk_0E; // 0xe
    s8 unk_0F; // 0xf
} UnkStruct_020f69cc;

typedef struct UnkStruct_020f697c {
    char pad_00[0x14];
    char sub14[0x24];
    signed char unk_38;
    signed char unk_39;
    signed char unk_3A;
    signed char unk_3B;
} UnkStruct_020f697c;

typedef struct UnkStruct_020f697c_2 {
    char pad_00[0x30];
    void *unk_30;
} UnkStruct_020f697c_2;

extern void func_020f6eb4(UnkStruct_020f69cc *self);
extern int func_020f6a80(UnkStruct_020f69cc *self);
extern void func_020f6f3c(UnkStruct_020f69cc *self);
extern void func_020f6ba0(UnkStruct_020f69cc *self);
extern void func_020f70b4(void *);
extern void func_020f6f80(void *, int);
extern UnkStruct_020f697c_2 data_021fd1bc;
extern int data_02138fe4;

int func_020f69cc(UnkStruct_020f69cc *self)
{
    int result;
    int r;

    result = -1;

    if (self->unk_0A == 0) {
        goto out;
    }

    if (self->unk_0E == -1) {
        func_020f6eb4(self);
        goto out;
    }

    r = 0;
    if (self->unk_0C == self->unk_0F) {
        r = func_020f6a80(self);
    }

    if (r != 0) {
        func_020f6f3c(self);
        goto out_load;
    }

    if (self->unk_0C == 0 || self->unk_0C == self->unk_0E) {
        self->unk_0C = 0;
        self->unk_0B = self->unk_0B + 1;
        func_020f6ba0(self);
    }

    self->unk_0C = self->unk_0C + 1;

out_load:
    result = self->unk_0B;

out:
    return result;
}

void func_020f697c(UnkStruct_020f697c *self)
{
    data_021fd1bc.unk_30 = self;
    func_020f70b4(self->sub14);
    func_020f70b4(self);
    func_020f6f80(self, 0);
    self->unk_38 = 0;
    self->unk_39 = -1;
    self->unk_3A = 0;
    self->unk_3B = 0;
}

void *func_020f6970(void)
{
    return &data_02138fe4;
}

void func_020f6950(unsigned char *dst, const unsigned char *src)
{
    int i;
    for (i = 0; i < 16; i++) {
        *(dst + i + 0x28) = src[i];
    }
}

void *func_020f6948(void *p)
{
    return (u8 *) p + 0x28;
}
