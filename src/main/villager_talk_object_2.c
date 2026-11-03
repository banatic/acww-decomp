/* villager_talk_object_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02024c98 @ 0x02024c98, 0xa0 bytes, Thumb
 * func_02024c90 @ 0x02024c90, 0x8 bytes, Thumb
 * func_02024bf8 @ 0x02024bf8, 0x98 bytes, Thumb
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

struct Pair_02024bf8 {
    unsigned int x;
    unsigned int y;
};

extern struct Pair data_020d90a0;
extern char data_020d96c4[];
extern struct Pair data_020d9018;
extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern int func_0208150c(void *);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int func_02014f60(int);
extern char data_020c8e50;
extern char data_020c8e5c;
extern struct Pair_02024bf8 data_020d9180;

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

void func_02024c90(int argument0)
{
    func_02014f60((int) argument0);
}

void func_02024bf8(void *p, void *out)
{
    int mode = 2;
    void *data = (void *) &data_020c8e50;
    int res;

    if (func_0209bc40((int) ((unsigned char *) (unsigned int) func_0202d9c4((void *) p))) == 4) {
        data = (void *) &data_020c8e5c;
        mode = 3;
    }

    {
        int *field = *(int **) ((char *) p + 0x40);
        if (field) {
            *(int *) ((char *) field + 8) = 1;
        }
    }

    {
        void **ptr = *(void ***) ((char *) p + 0x100);
        int val = *(int *) ((char *) ptr + 0x830);
        res = func_020036e8(func_0208150c((void *) val));
    }

    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30, res, (int) data, 3, 1, (unsigned char) mode);

    *(void **) out = (char *) p + 0x104;
    *(unsigned char *) ((char *) out + 4) = *(unsigned char *) ((char *) p + 0x122);

    *(struct Pair_02024bf8 *) ((char *) p + 0xc8) = data_020d9180;
}
