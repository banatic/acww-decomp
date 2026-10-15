/* func_02058f54 @ 0x02058f54, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    char pad_78[0x84 - 0x78];
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    char pad_94[0x98 - 0x94];
    int unk_98;
    char pad_9C[0xd6 - 0x9c];
    u16 count;
} UnkStruct_02058f54;

extern void func_0205967c(UnkStruct_02058f54 *self, void *buf);
extern void func_02059674(UnkStruct_02058f54 *self, int n);
extern int func_020e895c(int *out, int a, int b);
extern void func_020eaca0(int *out, int *in1, int *in2);
extern void VEC_Add(int *a, int *b, int *c);

void func_02058f54(UnkStruct_02058f54 *self)
{
    int a[3];
    int b[3];

    if ((int) self->count < 9) {
        func_0205967c(self, a);
        func_020e895c(&self->unk_60, self->unk_6C, self->unk_90);
        self->unk_64 = a[1] + self->unk_70;
        func_020e895c(&self->unk_68, self->unk_74, self->unk_98);
        self->count++;
        if ((int) self->count >= 9) {
            func_020eaca0(b, &self->unk_60, a);
            self->unk_84 = b[0];
            self->unk_88 = b[1];
            self->unk_8C = b[2];
            func_02059674(self, 0);
        }
    } else if ((int) self->count == 9) {
        func_0205967c(self, &self->unk_60);
        VEC_Add(&self->unk_60, &self->unk_84, &self->unk_60);
    }
}
