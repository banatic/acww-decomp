/* func_02024c98 @ 0x02024c98, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u32 a;
    u32 b;
};

struct FlagStruct {
    char pad_00[8];
    u32 value;
};

struct Sub830 {
    char pad_00[0x830];
    void *ptr;
};

struct UnkStruct_02024c98 {
    char *buf;
    u8 unk_04;
};

struct UnkStruct_02024c98_2 {
    char pad_00[0x40];
    struct FlagStruct *unk_40;
    char pad_44[0xc8 - 0x44];
    struct Pair word64c8;
    char pad_D0[0x100 - 0xd0];
    struct Sub830 *unk_100;
    char buf104[0x122 - 0x104];
    u8 unk_122;
};

extern struct Pair data_020d90a0;
extern char data_020d96c4[];
extern struct Pair data_020d9018;

extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern int func_0208150c(void *);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

void func_02024c98(struct UnkStruct_02024c98_2 *self, struct UnkStruct_02024c98 *out)
{
    struct Pair local;
    int tmp2;

    local = data_020d90a0;

    if (func_0209bc40(func_0202d9c4(self)) == 4) {
        local.a = (u32) data_020d96c4;
    }

    if (self->unk_40 != 0) {
        self->unk_40->value = 1;
    }

    tmp2 = func_020036e8(func_0208150c(self->unk_100->ptr));

    func_0202da38(self, self->buf104, &self->unk_122, 0x1e, tmp2, local.a, ((u8 *) &local)[4], 0, 0);

    out->buf = self->buf104;
    out->unk_04 = self->unk_122;

    self->word64c8 = data_020d9018;
}
