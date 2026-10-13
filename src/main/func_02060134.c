/* func_02060134 @ 0x02060134, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02060134_2 {
    u8 unk_00;
    int unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
};

struct UnkStruct_02060134_3 {
    u8 pad_00[0x24];
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
};

struct Vec {
    u32 x, y, z;
};

struct UnkStruct_02060134 {
    u32 a, b, c;
};

extern int func_020606d4(u32 addr, u8 byte1);
extern void func_0203f7d0(void *ptr, struct Vec *vec);
extern void *func_020604f8(struct UnkStruct_02060134_2 *self);
extern void VEC_Subtract(struct UnkStruct_02060134 *a, struct Vec *b, struct UnkStruct_02060134 *c);
extern void func_020eaaa8(struct UnkStruct_02060134 *a, int b);
extern void VEC_Add(struct Vec *a, struct UnkStruct_02060134 *b, struct Vec *c);
extern void func_0203f8d0(struct Vec *a, struct Vec *b);
extern void func_020e96c8(struct UnkStruct_02060134_3 *out, u32 x, u32 y, u32 z);
extern void func_02055e7c(void *a, void *b);

extern unsigned char data_021cad80[];

void func_02060134(struct UnkStruct_02060134_2 *self, struct UnkStruct_02060134_3 *src, void *arg2)
{
    struct UnkStruct_02060134_3 local_data;
    struct Vec vec;
    struct UnkStruct_02060134 tmp;
    struct UnkStruct_02060134_3 out_data;
    void *r6;
    struct UnkStruct_02060134 *tp;
    void *p;

    if (self->unk_04 == 0) {
        return;
    }

    r6 = (void *) func_020606d4((unsigned int) data_021cad80, self->unk_00);

    local_data = *src;

    if (self->unk_04 <= 1) {
        vec.x = local_data.unk_24;
        vec.y = local_data.unk_28;
        vec.z = local_data.unk_2C;
        func_0203f7d0(&self->unk_08, &vec);
    } else {
        vec.x = self->unk_08;
        vec.y = self->unk_0C;
        vec.z = self->unk_10;
        if (self->unk_04 == 6) {
            p = func_020604f8(self);
            if (p != 0) {
                tp = (struct UnkStruct_02060134 *) ((char *) p + 0x120);
                tmp.a = tp->a;
                tmp.b = tp->b;
                tmp.c = tp->c;
                VEC_Subtract(&tmp, &vec, &tmp);
                func_020eaaa8(&tmp, 3);
                tmp.b = 0;
                VEC_Add(&vec, &tmp, &vec);
            }
        }
        func_0203f8d0(&vec, &vec);
        func_020e96c8(&out_data, vec.x, vec.y, vec.z);
        local_data = out_data;
    }

    *(struct UnkStruct_02060134_3 *) ((char *) r6 + 0x64) = local_data;
    func_02055e7c(r6, arg2);
}
