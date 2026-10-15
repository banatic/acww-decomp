/* func_02013abc @ 0x02013abc, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0201b1a0(void *);
extern int func_020912d4(int, void *, void *, int);
extern int func_02056f28(void *, int);
extern void func_02013bb0(void *, void *);

typedef struct {
    u8 flag;
    u8 pad_01[3];
    u32 p;
} UnkStruct_02013abc;

struct Pair {
    u32 unk_00, unk_04, unk_08;
};

struct UnkStruct_02013abc_2 {
    s16 s;
    s16 unk_02;
    u32 w1;
    u32 w2;
    u32 w3;
};

void func_02013abc(UnkStruct_02013abc *self, char *other)
{
    int v;
    int r4;
    int r0;
    struct UnkStruct_02013abc_2 tmp;
    v = func_0201b1a0(other + 0x350);
    if (self->flag == 0) {
        goto end;
    }
    if ((unsigned) (v - 1) > 2) {
        goto end;
    }

    tmp.s = *(s16 *) (other + 0x8e);
    if (self->p == 0) {
        func_020912d4(0x28, other + 0x490, &tmp, 0);
        func_020912d4(0x28, other + 0x484, &tmp, 0);
    } else {
        r4 = func_02056f28(other + 0x188, 1);
        r0 = func_02056f28(other + 0x188, 9);
        if (r4 == 0 && r0 == 0) {
            goto end;
        }
        tmp.w1 = ((r4 != 0) ? (struct Pair *) (other + 0x490) : (struct Pair *) (other + 0x484))->unk_00;
        tmp.w2 = ((r4 != 0) ? (struct Pair *) (other + 0x490) : (struct Pair *) (other + 0x484))->unk_04;
        tmp.w3 = ((r4 != 0) ? (struct Pair *) (other + 0x490) : (struct Pair *) (other + 0x484))->unk_08;
        tmp.unk_02 = (s16) (*(s16 *) (other + 0x8e) + 0x8000);
        tmp.w2 = *(u32 *) (other + 0x60);
        if (v == 2) {
            func_020912d4(0, &tmp.w1, &tmp.unk_02, 0);
        }
        func_020912d4(0x28, &tmp.w1, &tmp, 0);
        func_02013bb0(self, other);
    }
end:
    self->p = v;
}
